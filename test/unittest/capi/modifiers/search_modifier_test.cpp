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

#include "core/components/search/search_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "generated/type_helpers.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;

namespace {
// attrs
const auto SEARCH_VALUE_OPTION("value");
const auto SEARCH_ICON_OPTION("icon");
const auto SEARCH_PLACEHOLDER_OPTION("placeholder");
const auto BUTTON_OPTIONS_ATTR("searchButtonOption");
const auto BUTTON_OPTIONS_COLOR_ATTR("fontColor");
const auto BUTTON_OPTIONS_SIZE_ATTR("fontSize");
const auto CANCEL_BUTTON_ATTR("cancelButton");
const auto CANCEL_BUTTON_ICON_ATTR("icon");
const auto CANCEL_BUTTON_ICON_COLOR_ATTR("color");
const auto CANCEL_BUTTON_ICON_SIZE_ATTR("size");
const auto CANCEL_BUTTON_ICON_SRC_ATTR("src");
const auto CANCEL_BUTTON_STYLE_ATTR("style");
const auto CARET_STYLE_ATTR("caretStyle");
const auto CARET_STYLE_COLOR_ATTR("color");
const auto CARET_STYLE_WIDTH_ATTR("width");
const auto COPY_OPTION_ATTR("copyOption");
const auto DECORATION_ATTRS("decoration");
const auto DECORATION_TYPE_ATTR("type");
const auto DECORATION_STYLE_ATTR("style");
const auto DECORATION_COLOR_ATTR("color");
const auto ENABLE_KEYBOARD_ON_FOCUS("enableKeyboardOnFocus");
const auto ENABLE_PREVIEW_TEXT("enablePreviewText");
const auto ENTER_KEY_TYPE_ATTR("enterKeyType");
const auto FONT_COLOR_ATTR("fontColor");
const auto FONT_FEATURE_ATTR("fontFeature");
const auto LETTER_SPACING_ATTR("letterSpacing");
const auto LINE_HEIGHT_ATTR("lineHeight");
const auto MAX_FONT_SIZE_ATTR("maxFontSize");
const auto MAX_LENGTH_ATTR("maxLength");
const auto MIN_FONT_SIZE_ATTR("minFontSize");
const auto PLACEHOLDER_FONT_ATTRS("placeholderFont");
const auto PLACEHOLDER_FONT_SIZE("size");
const auto PLACEHOLDER_FONT_FAMILY("fontFamily");
const auto PLACEHOLDER_FONT_WEIGHT_ENUM("fontWeight");
const auto PLACEHOLDER_FONT_WEIGHT("weight");
const auto PLACEHOLDER_FONT_STYLE("style");
const auto PLACEHOLDER_COLOR_ATTR("placeholderColor");
const auto SEARCH_ICON_ATTR("searchIcon");
const auto SEARCH_ICON_SRC_ATTR("src");
const auto SEARCH_ICON_COLOR_ATTR("color");
const auto SEARCH_ICON_SIZE_ATTR("size");
const auto SELECTED_BACKGROUND_COLOR_ATTR("selectedBackgroundColor");
const auto SELECTION_MENU_HIDDEN_ATTR("selectionMenuHidden");
const auto TEXT_ALIGN_ATTR("textAlign");
const auto TEXT_FONT_ATTRS("textFont");
const auto TEXT_FONT_SIZE_ATTR("fontSize");
const auto TEXT_FONT_FAMILY_ATTR("fontFamily");
const auto TEXT_FONT_WEIGHT_ATTR("fontWeight");
const auto TEXT_FONT_STYLE_ATTR("fontStyle");
const auto TEXT_INDENT_ATTR("textIndent");
const auto TYPE_ATTR("type");
const auto ENABLE_HAPTIC_FEEDBACK_ATTR("enableHapticFeedback");
const auto MIN_FONT_SCALE_ATTR("minFontScale");
const auto MAX_FONT_SCALE_ATTR("maxFontScale");
const auto HALF_LEADING_ATTR("halfLeading");
const auto STOP_BACK_PRESS_ATTR("stopBackPress");

const auto MIN_FONT_SCALE_DEFAULT_VALUE = "0.000000";
const auto MAX_FONT_SCALE_DEFAULT_VALUE = "2.000000";
const auto HALF_LEADING_DEFAULT_VALUE = "false";
const auto STOP_BACK_PRESS_DEFAULT_VALUE = "true";

// custom colors
const auto CUSTOM_COLOR_STRING("#FF123456");
const int CUSTOM_COLOR_INT(0xFF123456);
const auto CHECK_COLOR_COLOR("#FF008000");
const auto TEST_STRING("testString");

const Ark_ResourceColor COLOR_COLOR = Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(Ark_Color::ARK_COLOR_GREEN);
const Ark_ResourceColor COLOR_INT = Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(CUSTOM_COLOR_INT);
const Ark_ResourceColor COLOR_STRING = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(CUSTOM_COLOR_STRING);

const Opt_ResourceColor OPT_COLOR_COLOR = Converter::ArkValue<Opt_ResourceColor>(COLOR_COLOR);
const Opt_ResourceColor OPT_COLOR_INT = Converter::ArkValue<Opt_ResourceColor>(COLOR_INT);
const Opt_ResourceColor OPT_COLOR_STRING = Converter::ArkValue<Opt_ResourceColor>(COLOR_STRING);

const auto RES_NAME = NamedResourceId(TEST_STRING, ResourceType::MEDIA);

//  default colors
const auto OPT_RESOURCE_RESOURCE = CreateResourceUnion<Opt_ResourceStr>(RES_NAME);
const auto OPT_UNION_RESOURCE_STR = Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(TEST_STRING);
const auto OPT_UNION_RESOURCE_RESOURCE = CreateResourceUnion<Opt_Union_String_Resource>(RES_NAME);

// icon
const auto CHECK_DEFAULT_BLACK_COLOR("#FF000000");
const auto CHECK_DEFAULT_BLACK_COLOR_ARRAY("[#FF000000,]");

// length values
const Ark_Int32 AINT32_POS(1234);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const auto ALEN_VP_POS = ArkValue<Ark_Length>(AFLT32_POS);
const auto ALEN_VP_NEG = ArkValue<Ark_Length>(AFLT32_NEG);
const auto OPT_LEN_VP_POS = ArkValue<Opt_Length>(AFLT32_POS);
const auto OPT_LEN_VP_NEG = ArkValue<Opt_Length>(AFLT32_NEG);

// default length
const std::string CHECK_DEFAULT_PX("0.00px");
const std::string CHECK_MAX_ICON_PX("32.00px");
const std::string CHECK_DEFAULT_VP("0.00vp");

// check length
const std::string CHECK_POSITIVE_VALUE_INT("1234.00px");
const std::string CHECK_ICON_MAX_VALUE_INT("32.00px");
const std::string CHECK_NEGATIVE_VALUE_INT("-2147483648.00px");
const std::string CHECK_POSITIVE_VALUE_FLOAT("1.23vp");
const std::string CHECK_POSITIVE_VALUE_FLOAT_PX("1.23px");
const std::string CHECK_NEGATIVE_VALUE_FLOAT("-5.68vp");

// check text
const auto CHECK_TEXT("test_text");
PreviewText PREVIEW_TEXT = { .offset = 1234, .value = u"test_offset" };
const auto EMPTY_TEXT("");
const auto ICON_DEFAULT_TEXT("0");
const auto ICON_DEFAULT_SRC("resource:///ohos_test_image.svg");

// check resource
const Ark_String STR_NAME = ArkValue<Ark_String>("min_font_size");
const std::string CHECK_RESOURCE_STR("testString");

// check styles
const std::string BUTTON_STYLE_INPUT("CancelButtonStyle.INPUT");

const uint32_t FLOAT_RES_0_ID = 1001;
const uint32_t FLOAT_RES_1_ID = 1002;
const double FLOAT_RES_0_VALUE = 0.705f;
const Ark_Resource FLOAT_RES_0 = CreateResource(FLOAT_RES_0_ID, ResourceType::FLOAT);
const double FLOAT_RES_1_VALUE = 1.2f;
const Ark_Resource FLOAT_RES_1 = CreateResource(FLOAT_RES_1_ID, ResourceType::FLOAT);

// test types
typedef std::pair<Ark_Length, std::string> LengthTest;
typedef std::pair<Opt_Length, std::string> OptLengthTest;
typedef std::pair<Opt_ResourceColor, std::string> ColorTest;
typedef std::pair<std::string, std::string> CheckCaretValue;
typedef std::pair<std::string, std::string> CheckSearchButtonOptions;
typedef std::pair<Opt_SearchButtonOptions, CheckSearchButtonOptions> TestSearchButtonOption;
typedef std::tuple<std::string, std::string, std::string> TripleCheckValues;
typedef std::pair<Opt_ResourceStr, std::string> ResourceSRC;
typedef std::pair<Opt_Union_String_Resource, std::string> UnionResourceString;
typedef std::pair<Opt_FontStyle, std::string> ArkFontStyleTest;
typedef std::pair<Ark_CancelButtonStyle, std::string> ArkCancelButtonStyleTest;
typedef std::pair<Ark_Int32, Ark_Int32> ArkNumberIntTest;
typedef std::pair<float, float> ArkNumberFloatTest;
typedef std::pair<Opt_Union_FontWeight_I32_String, std::string> ArkFontWeightTest;
typedef std::pair<Ark_Union_IconOptions_SymbolGlyphModifier, TripleCheckValues> SearchIconTest;
typedef std::tuple<Ark_Boolean, bool> OneBoolStep;
typedef std::pair<Opt_SearchOptions, TripleCheckValues> OptionsTest;
typedef std::pair<Ark_TextDecorationType, std::string> DecorationTypeTest;
typedef std::pair<Ark_TextDecorationStyle, std::string> DecorationStyleTest;

// common testPlans
const std::vector<OptLengthTest> OPT_LENGTH_TEST_PLAN = {
    { OPT_LEN_VP_NEG, CHECK_DEFAULT_PX },
    { OPT_LEN_VP_POS, CHECK_POSITIVE_VALUE_FLOAT }
};
const std::vector<OptLengthTest> TEST_PLAN_OPT_LENGTH_PX = {
    { OPT_LEN_VP_NEG, CHECK_DEFAULT_PX },
    { OPT_LEN_VP_POS, CHECK_POSITIVE_VALUE_FLOAT_PX }
};
const std::vector<OptLengthTest> ICON_SIZE_TEST_PLAN = {
    { OPT_LEN_VP_NEG, CHECK_DEFAULT_PX },
    { OPT_LEN_VP_POS, CHECK_POSITIVE_VALUE_FLOAT_PX }
};
const std::vector<ArkNumberIntTest> INT_NUMBER_TEST_PLAN = {
    { AINT32_POS, AINT32_POS },
    { AINT32_NEG, AINT32_NEG },
};
const std::vector<ArkNumberFloatTest> FLOAT_NUMBER_TEST_PLAN = {
    { AFLT32_POS, AFLT32_POS },
    { AFLT32_NEG, AFLT32_NEG },
};
const std::vector<ColorTest> COLOR_TEST_PLAN = {
    { OPT_COLOR_COLOR, CHECK_COLOR_COLOR },
    { OPT_COLOR_INT, CUSTOM_COLOR_STRING },
    { OPT_COLOR_STRING, CUSTOM_COLOR_STRING },
};

const std::vector<ResourceSRC> RESOURCE_TEST_PLAN = {
    { ArkUnion<Opt_ResourceStr, Ark_String>(""), ICON_DEFAULT_SRC },
    { ArkUnion<Opt_ResourceStr, Ark_String>("test/string/2"), "test/string/2" }
};
const std::vector<UnionResourceString> UNION_RESOURCE_STRING_PLAN = {
    { OPT_UNION_RESOURCE_STR, CHECK_RESOURCE_STR }
};

const std::vector<OneBoolStep> BOOL_TEST_PLAN = {
    { false, false },
    { true, true },
    { false, false }
};

const std::vector<ArkCancelButtonStyleTest> BUTTON_STYLE_TEST_PLAN = {
    { Ark_CancelButtonStyle::ARK_CANCEL_BUTTON_STYLE_CONSTANT, "CancelButtonStyle.CONSTANT" },
    { Ark_CancelButtonStyle::ARK_CANCEL_BUTTON_STYLE_INVISIBLE, "CancelButtonStyle.INVISIBLE" },
    { Ark_CancelButtonStyle::ARK_CANCEL_BUTTON_STYLE_INPUT, "CancelButtonStyle.INPUT" },
};

const std::vector<ArkFontStyleTest> FONT_STYLE_TEST_PLAN = {
    { ArkValue<Opt_FontStyle>(Ark_FontStyle::ARK_FONT_STYLE_NORMAL), "FontStyle.Normal" },
    { ArkValue<Opt_FontStyle>(Ark_FontStyle::ARK_FONT_STYLE_ITALIC), "FontStyle.Italic" },
    { ArkValue<Opt_FontStyle>(static_cast<Ark_FontStyle>(-1)), "FontStyle.Normal" },
};

// Font.fontWeight apply only FontWeight enum values
const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN = {
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_LIGHTER), "FontWeight.Lighter" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_NORMAL), "FontWeight.Normal" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR), "FontWeight.Regular" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_MEDIUM), "FontWeight.Medium" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD), "FontWeight.Bold" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLDER), "FontWeight.Bolder" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(100), "100" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(200), "200" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(300), "300" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(400), "400" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(500), "500" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(600), "600" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(700), "700" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(800), "800" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(900), "900" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("lighter"), "FontWeight.Lighter" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("normal"), "FontWeight.Normal" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("regular"), "FontWeight.Regular" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("medium"), "FontWeight.Medium" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("bold"), "FontWeight.Bold" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("bolder"), "FontWeight.Bolder" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("100"), "100" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("200"), "200" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("300"), "300" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("400"), "400" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("500"), "500" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("600"), "600" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("700"), "700" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("800"), "800" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("900"), "900" },
    { ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("1000"), "FontWeight.Normal" },
};

const std::vector<TextDeleteDirection> DELETE_DIRECTION_TEST_PLAN = {
    TextDeleteDirection::FORWARD,
    TextDeleteDirection::BACKWARD,
};

const std::vector<std::pair<Opt_Union_F64_String_Resource, std::string>> UNION_NUM_STR_RES_TEST_PLAN = {
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(123.), "123.00vp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(-123.), "0.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("5.6vp"), "5.60vp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("-5.6vp"), "0.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("45px"), "45.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("-45px"), "0.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(1.23), "1.23vp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(-1.23), "0.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("45fp"), "45.00fp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("10%"), "0.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("45dp"), "45.00fp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("-10%"), "0.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("undefVal"), "0.00fp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("45.3fp"), "45.30fp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(""), "0.00fp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("qw111vp"), "0.00vp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("qw111"), "0.00fp" },
};

const std::vector<std::pair<Opt_Union_F64_String_Resource, std::string>> UNION_NUM_STR_RES_TEST_PLAN_WITH_PERCENT = {
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(123.), "123.00vp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(-123.), "0.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("5.6vp"), "5.60vp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("-5.6vp"), "0.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("45px"), "45.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("-45px"), "0.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(1.23), "1.23vp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(-1.23), "0.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("45fp"), "45.00fp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("10%"), "10.00%" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("45dp"), "45.00fp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("-10%"), "0.00px" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("undefVal"), "0.00fp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("45.3fp"), "45.30fp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(""), "0.00fp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("qw111vp"), "0.00vp" },
    { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("qw111"), "0.00fp" },
};

const std::vector<DecorationTypeTest> TEXT_DECORATION_TYPE_TEST_PLAN = {
    { Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE, "TextDecorationType.None" },
    { Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_UNDERLINE, "TextDecorationType.Underline" },
    { Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_OVERLINE, "TextDecorationType.Overline" },
    { Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_LINE_THROUGH, "TextDecorationType.LineThrough" },
    { static_cast<Ark_TextDecorationType>(-100), "TextDecorationType.None" },
    { Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_LINE_THROUGH, "TextDecorationType.LineThrough" },
    { static_cast<Ark_TextDecorationType>(100), "TextDecorationType.None" },
};

const std::vector<DecorationStyleTest> TEXT_DECORATION_STYLE_TEST_PLAN = {
    { Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_SOLID, "TextDecorationStyle.SOLID" },
    { Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DOUBLE, "TextDecorationStyle.DOUBLE" },
    { Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DOTTED, "TextDecorationStyle.DOTTED" },
    { Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DASHED, "TextDecorationStyle.DASHED" },
    { Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_WAVY, "TextDecorationStyle.WAVY" },
    { static_cast<Ark_TextDecorationStyle>(-100), "TextDecorationStyle.SOLID" },
    { Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DASHED, "TextDecorationStyle.DASHED" },
    { static_cast<Ark_TextDecorationStyle>(100), "TextDecorationStyle.SOLID" },
};

std::vector<std::tuple<std::string, Ark_Boolean, std::string>> testFixtureBooleanValidValues = {
    { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
    { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
};

} // namespace

class SearchModifierTest : public ModifierTestBase<GENERATED_ArkUISearchModifier,
                               &GENERATED_ArkUINodeModifiers::getSearchModifier, GENERATED_ARKUI_SEARCH> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<SearchTheme>();
        SetupTheme<TextFieldTheme>();
        SetupTheme<IconTheme>();
        AddResource(FLOAT_RES_0_ID, FLOAT_RES_0_VALUE);
        AddResource(FLOAT_RES_1_ID, FLOAT_RES_1_VALUE);
    }
};

/**
 * @tc.name: setSearchOptionsDefault
 * @tc.desc: Check the default values of setSearchOptions
 *
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setSearchOptionsDefault, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSearchOptions, nullptr);
    // default
    auto jsonValue = GetJsonValue(node_);
    auto value = GetAttrValue<std::string>(jsonValue, SEARCH_VALUE_OPTION);
    auto placeholder = GetAttrValue<std::string>(jsonValue, SEARCH_PLACEHOLDER_OPTION);
    auto icon = GetAttrValue<std::string>(jsonValue, SEARCH_ICON_OPTION);
    EXPECT_EQ(value, EMPTY_TEXT);
    EXPECT_EQ(placeholder, EMPTY_TEXT);
    EXPECT_EQ(icon, ICON_DEFAULT_TEXT);
}

/**
 * @tc.name: setSearchOptionsValidValues
 * @tc.desc: Check the default values of setSearchOptions
 * DISABLED because icon attribute return only default value
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setSearchOptionsValidValues, TestSize.Level1)
{
    Ark_SearchOptions options = {};
    options.value = ArkUnion<Opt_Union_String_Bindable, Ark_String>(TEST_STRING);
    options.placeholder = ArkUnion<Opt_ResourceStr, Ark_String>(TEST_STRING);
    options.icon = ArkValue<Opt_String>(TEST_STRING);
    auto optOptions = ArkValue<Opt_SearchOptions>(options);
    modifier_->setSearchOptions(node_, &optOptions);
    // default
    auto jsonValue = GetJsonValue(node_);
    auto value = GetAttrValue<std::string>(jsonValue, SEARCH_VALUE_OPTION);
    auto placeholder = GetAttrValue<std::string>(jsonValue, SEARCH_PLACEHOLDER_OPTION);
    auto icon = GetAttrValue<std::string>(jsonValue, SEARCH_ICON_OPTION);
    EXPECT_EQ(value, TEST_STRING);
    EXPECT_EQ(placeholder, TEST_STRING);
    EXPECT_EQ(icon, TEST_STRING);
}

/**
 * @tc.name: setCancelButtonTestDefault
 * @tc.desc: Check the default values of cancelButton
 *
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setCancelButtonTestDefault, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCancelButton, nullptr);
    // default
    auto fullJsonDefault = GetJsonValue(node_);
    auto defaultCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJsonDefault, CANCEL_BUTTON_ATTR);
    auto defaultButtonIconStyleAttr = GetAttrValue<std::string>(defaultCancelButtonAttrs, CANCEL_BUTTON_STYLE_ATTR);
    auto defaultCancelButtonIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(defaultCancelButtonAttrs,
        CANCEL_BUTTON_ICON_ATTR);
    auto defaultCancelButtonIconSrc = GetAttrValue<std::string>(defaultCancelButtonIconAttrs,
        CANCEL_BUTTON_ICON_SRC_ATTR);
    auto defaultCancelButtonIconColor = GetAttrValue<std::string>(defaultCancelButtonIconAttrs,
        CANCEL_BUTTON_ICON_COLOR_ATTR);
    auto defaultCancelButtonIconSize = GetAttrValue<std::string>(defaultCancelButtonIconAttrs,
        CANCEL_BUTTON_ICON_SIZE_ATTR);
    EXPECT_EQ(defaultButtonIconStyleAttr, BUTTON_STYLE_INPUT);
    EXPECT_EQ(defaultCancelButtonIconSrc, EMPTY_TEXT);
    EXPECT_EQ(defaultCancelButtonIconColor, CHECK_DEFAULT_BLACK_COLOR_ARRAY);
    EXPECT_EQ(defaultCancelButtonIconSize, CHECK_DEFAULT_PX);
}

/*
 * @tc.name: setFontColorTestValidColorValues
 * @tc.desc: Check the functionality of SearchModifier.setCancelButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setCancelButtonTestValidColorValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLACK), "#FF000000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BROWN), "#FFA52A2A" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_GRAY), "#FF808080" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_GREEN), "#FF008000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_GREY), "#FF808080" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_ORANGE), "#FFFFA500" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_PINK), "#FFFFC0CB" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_YELLOW), "#FFFFFF00" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_TRANSPARENT), "#00000000" },
    };

    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions attrs;
    auto& value = WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(attrs)).icon).color;
    for (const auto &[color, expected]: testPlan) {
        value = ArkValue<Opt_ResourceColor>(color);
        modifier_->setCancelButton(node_, &attrs);
        jsonValue = GetJsonValue(node_);
        auto customCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, CANCEL_BUTTON_ATTR);
        auto customCancelButtonIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(customCancelButtonAttrs,
            CANCEL_BUTTON_ICON_ATTR);
        auto resultStr = GetAttrValue<std::string>(customCancelButtonIconAttrs, CANCEL_BUTTON_ICON_COLOR_ATTR);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setFontColorTestValidNumberValues
 * @tc.desc: Check the functionality of SearchModifier.setCancelButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setCancelButtonTestValidNumberValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xffffffff), "#FFFFFFFF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xff000000), "#FF000000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xff0000ff), "#FF0000FF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xffa52a2a), "#FFA52A2A" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xff808080), "#FF808080" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xff008000), "#FF008000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xffffa500), "#FFFFA500" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xffffc0cb), "#FFFFC0CB" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xffff0000), "#FFFF0000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0xffffff00), "#FFFFFF00" },
#ifdef WRONG_COLOR
        { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x00000000), "#00000000" },
#endif
    };

    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions attrs;
    auto& value = WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(attrs)).icon).color;
    for (const auto &[color, expected]: testPlan) {
        value = ArkValue<Opt_ResourceColor>(color);
        modifier_->setCancelButton(node_, &attrs);
        jsonValue = GetJsonValue(node_);
        auto customCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, CANCEL_BUTTON_ATTR);
        auto customCancelButtonIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(customCancelButtonAttrs,
            CANCEL_BUTTON_ICON_ATTR);
        auto resultStr = GetAttrValue<std::string>(customCancelButtonIconAttrs, CANCEL_BUTTON_ICON_COLOR_ATTR);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setFontColorTestValidStringValues
 * @tc.desc: Check the functionality of SearchModifier.setCancelButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setCancelButtonTestValidStringValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#FFFFFFFF"), "#FFFFFFFF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ff000000"), "#FF000000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ff0000ff"), "#FF0000FF" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ffa52a2a"), "#FFA52A2A" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ff808080"), "#FF808080" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ff008000"), "#FF008000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ffffa500"), "#FFFFA500" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ffffc0cb"), "#FFFFC0CB" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ffff0000"), "#FFFF0000" },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#ffffff00"), "#FFFFFF00" },
#ifdef WRONG_COLOR
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#00000000"), "#00000000" },
#endif
    };

    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions attrs;
    auto& value = WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(attrs)).icon).color;
    for (const auto &[color, expected]: testPlan) {
        value = ArkValue<Opt_ResourceColor>(color);
        modifier_->setCancelButton(node_, &attrs);
        jsonValue = GetJsonValue(node_);
        auto customCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, CANCEL_BUTTON_ATTR);
        auto customCancelButtonIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(customCancelButtonAttrs,
            CANCEL_BUTTON_ICON_ATTR);
        auto resultStr = GetAttrValue<std::string>(customCancelButtonIconAttrs, CANCEL_BUTTON_ICON_COLOR_ATTR);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setFontColorTestInvalidStringValues
 * @tc.desc: Check the functionality of SearchModifier.setCancelButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setCancelButtonTestTestInvalidStringValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("undefined"), CHECK_DEFAULT_BLACK_COLOR },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("GGTTSSPP"), CHECK_DEFAULT_BLACK_COLOR },
    };

    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions attrs;
    auto& value = WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(attrs)).icon).color;
    for (const auto &[color, expected]: testPlan) {
        value = ArkValue<Opt_ResourceColor>(color);
        modifier_->setCancelButton(node_, &attrs);
        jsonValue = GetJsonValue(node_);
        auto customCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, CANCEL_BUTTON_ATTR);
        auto customCancelButtonIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(customCancelButtonAttrs,
            CANCEL_BUTTON_ICON_ATTR);
        auto resultStr = GetAttrValue<std::string>(customCancelButtonIconAttrs, CANCEL_BUTTON_ICON_COLOR_ATTR);
        EXPECT_EQ(resultStr, expected);
    }
}

/**
 * @tc.name: setCancelButtonTestIconSize
 * @tc.desc: Check set size functionality of setCancelButton
 *
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setCancelButtonTestIconSize, TestSize.Level1)
{
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions attrs;
    auto& value = WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(attrs)).icon).size;
    for (auto testSize : ICON_SIZE_TEST_PLAN) {
        value = testSize.first;
        modifier_->setCancelButton(node_, &attrs);
        auto fullJson = GetJsonValue(node_);
        auto customCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, CANCEL_BUTTON_ATTR);
        auto customCancelButtonIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(customCancelButtonAttrs,
            CANCEL_BUTTON_ICON_ATTR);
        auto customCancelButtonIconSize = GetAttrValue<std::string>(customCancelButtonIconAttrs,
            CANCEL_BUTTON_ICON_SIZE_ATTR);
        EXPECT_EQ(customCancelButtonIconSize, testSize.second);
    }
}

/**
 * @tc.name: setCancelButtonTestIconSrc
 * @tc.desc: Check set src functionality of setCancelButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setCancelButtonTestIconSrc, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions attrs;
    auto& value = WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(attrs)).icon).src;
    for (const auto &[src, expected] : RESOURCE_TEST_PLAN) {
        value = ArkValue<Opt_ResourceStr>(src);
        modifier_->setCancelButton(node_, &attrs);
        auto jsonValue = GetJsonValue(node_);
        auto customCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, CANCEL_BUTTON_ATTR);
        auto customCancelButtonIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(customCancelButtonAttrs,
            CANCEL_BUTTON_ICON_ATTR);
        auto resultStr = GetAttrValue<std::string>(customCancelButtonIconAttrs, CANCEL_BUTTON_ICON_SRC_ATTR);
        EXPECT_EQ(resultStr, expected);
    }
}

/**
 * @tc.name: setCancelButtonTestStyle
 * @tc.desc: Check set style functionality of setCancelButton
 *
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setCancelButtonTestStyle, TestSize.Level1)
{
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions attrs;
    auto& value = WriteToUnion<Ark_CancelButtonOptions>(WriteTo(attrs)).style;
    for (auto testStyleButton : BUTTON_STYLE_TEST_PLAN) {
        value = ArkValue<Opt_CancelButtonStyle>(testStyleButton.first);
        modifier_->setCancelButton(node_, &attrs);
        auto fullJson = GetJsonValue(node_);
        auto customCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, CANCEL_BUTTON_ATTR);
        auto customButtonIconStyleAttr = GetAttrValue<std::string>(customCancelButtonAttrs, CANCEL_BUTTON_STYLE_ATTR);
        EXPECT_EQ(customButtonIconStyleAttr, testStyleButton.second);
    }
}

/**
 * @tc.name: setCopyOptionTest
 * @tc.desc: Check the functionality of setCopyOption
 * In the documentation default value is Local, but in return value is Distributed
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setCopyOptionTest, TestSize.Level1)
{
    const auto defaultValue = "CopyOptions.Local";
    ASSERT_NE(modifier_->setCopyOption, nullptr);

    const std::vector<std::pair<Opt_CopyOptions, std::string>> COPY_OPTION_TEST_PLAN = {
        { ArkValue<Opt_CopyOptions>(ARK_COPY_OPTIONS_NONE), "CopyOptions.None" },
        { ArkValue<Opt_CopyOptions>(ARK_COPY_OPTIONS_LOCAL_DEVICE), "CopyOptions.Local" },
        { ArkValue<Opt_CopyOptions>(ARK_COPY_OPTIONS_IN_APP), "CopyOptions.InApp" },
        { ArkValue<Opt_CopyOptions>(INVALID_ENUM_VAL<Ark_CopyOptions>), defaultValue },
        { ArkValue<Opt_CopyOptions>(ARK_COPY_OPTIONS_NONE), "CopyOptions.None" },
        { ArkValue<Opt_CopyOptions>(), defaultValue },
    };

    auto checkVal = GetStringAttribute(node_, COPY_OPTION_ATTR);
    EXPECT_EQ(checkVal, defaultValue);
    for (const auto& [value, expectVal] : COPY_OPTION_TEST_PLAN) {
        modifier_->setCopyOption(node_, &value);
        checkVal = GetStringAttribute(node_, COPY_OPTION_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}


HWTEST_F(SearchModifierTest, DISABLED_setSearchIconTestDefaultValues, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);
    auto defaultSearchIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, SEARCH_ICON_ATTR);
    auto defaultSearchIconSrc = GetAttrValue<std::string>(defaultSearchIconAttrs, SEARCH_ICON_SRC_ATTR);
    auto defaultSearchIconColor = GetAttrValue<std::string>(defaultSearchIconAttrs, SEARCH_ICON_COLOR_ATTR);
    auto defaultSearchIconSize = GetAttrValue<std::string>(defaultSearchIconAttrs, SEARCH_ICON_SIZE_ATTR);
    EXPECT_EQ(defaultSearchIconSrc, ICON_DEFAULT_SRC);
    EXPECT_EQ(defaultSearchIconColor, CHECK_DEFAULT_BLACK_COLOR_ARRAY);
    EXPECT_EQ(defaultSearchIconSize, CHECK_DEFAULT_PX);
}

/**
 * @tc.name: setSearchIconTest
 * @tc.desc: Check the functionality of setSearchIcon
 * This test disabled because set icon src and color always return default value
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setSearchIconTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSearchIcon, nullptr);

    for (const auto &[testLength, expectLength] : TEST_PLAN_OPT_LENGTH_PX) {
        auto attrs = ArkUnion<Opt_Union_IconOptions_SymbolGlyphModifier, Ark_IconOptions>(
            Ark_IconOptions {
                .color = Converter::ArkValue<Opt_ResourceColor>(),
                .size = testLength,
                .src = Converter::ArkValue<Opt_ResourceStr>(),
            });
        modifier_->setSearchIcon(node_, &attrs);
        auto jsonValue = GetJsonValue(node_);
        auto customSearchIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, SEARCH_ICON_ATTR);
        auto customSearchIconSize = GetAttrValue<std::string>(customSearchIconAttrs, SEARCH_ICON_SIZE_ATTR);
        EXPECT_EQ(customSearchIconSize, expectLength);
    }
    for (const auto &[testColor, expectColor] : COLOR_TEST_PLAN) {
        auto attrs = ArkUnion<Opt_Union_IconOptions_SymbolGlyphModifier, Ark_IconOptions>(
            Ark_IconOptions {
                .color = testColor,
                .size = Converter::ArkValue<Opt_Length>(),
                .src = Converter::ArkValue<Opt_ResourceStr>(),
            });
        modifier_->setSearchIcon(node_, &attrs);
        auto jsonValue = GetJsonValue(node_);
        auto customSearchIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, SEARCH_ICON_ATTR);
        auto customSearchIconColor = GetAttrValue<std::string>(customSearchIconAttrs, SEARCH_ICON_COLOR_ATTR);
        EXPECT_EQ(customSearchIconColor, expectColor);
    }
    for (const auto &[testSrc, expectSrc] : RESOURCE_TEST_PLAN) {
        auto attrs = ArkUnion<Opt_Union_IconOptions_SymbolGlyphModifier, Ark_IconOptions>(
            Ark_IconOptions {
                .color = Converter::ArkValue<Opt_ResourceColor>(),
                .size = Converter::ArkValue<Opt_Length>(),
                .src = testSrc,
            });
        modifier_->setSearchIcon(node_, &attrs);
        auto jsonValue = GetJsonValue(node_);
        auto customSearchIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, SEARCH_ICON_ATTR);
        auto customSearchIconSrc = GetAttrValue<std::string>(customSearchIconAttrs, SEARCH_ICON_SRC_ATTR);
        EXPECT_EQ(customSearchIconSrc, expectSrc);
    }
}

/**
 * @tc.name: setFontColorTest
 * @tc.desc: Check the functionality of setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setFontColorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontColor, nullptr);
    // default
    auto fontColor = GetStringAttribute(node_, FONT_COLOR_ATTR);
    EXPECT_EQ(fontColor, CHECK_DEFAULT_BLACK_COLOR);
    // //color
    modifier_->setFontColor(node_, &OPT_COLOR_COLOR);
    auto fontColorColor = GetStringAttribute(node_, FONT_COLOR_ATTR);
    EXPECT_EQ(fontColorColor, CHECK_COLOR_COLOR);
    //int
    modifier_->setFontColor(node_, &OPT_COLOR_INT);
    auto fontColorInt = GetStringAttribute(node_, FONT_COLOR_ATTR);
    EXPECT_EQ(fontColorInt, CUSTOM_COLOR_STRING);
    // string
    modifier_->setFontColor(node_, &OPT_COLOR_STRING);
    auto fontColorColorString = GetStringAttribute(node_, FONT_COLOR_ATTR);
    EXPECT_EQ(fontColorColorString, CUSTOM_COLOR_STRING);
}

/**
 * @tc.name: setSearchButtonTest
 * @tc.desc: Check the functionality of setSearchButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setSearchButtonTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSearchButton, nullptr);
    // default
    auto fullJson = GetJsonValue(node_);
    auto defaultCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUTTON_OPTIONS_ATTR);
    auto defaultCaretColor = GetAttrValue<std::string>(defaultCaretStyle, BUTTON_OPTIONS_COLOR_ATTR);
    auto defaultCaretWidth = GetAttrValue<std::string>(defaultCaretStyle, BUTTON_OPTIONS_SIZE_ATTR);
    EXPECT_EQ(defaultCaretColor, CHECK_DEFAULT_BLACK_COLOR);
    EXPECT_EQ(defaultCaretWidth, CHECK_DEFAULT_VP);
    // custom
    std::vector<TestSearchButtonOption> testSearchButton;
    for (auto testLength : OPT_LENGTH_TEST_PLAN) {
        for (auto ColorTest : COLOR_TEST_PLAN) {
            Ark_SearchButtonOptions buttonOptions = { .fontColor = ColorTest.first, .fontSize = testLength.first };
            Opt_SearchButtonOptions options = Converter::ArkValue<Opt_SearchButtonOptions>(buttonOptions);
            CheckSearchButtonOptions checkSearchButtonOptions = { ColorTest.second, testLength.second };
            TestSearchButtonOption testSearchButtonOption = { options, checkSearchButtonOptions };
            testSearchButton.push_back(testSearchButtonOption);
        }
    }
    auto checkText = ArkValue<Opt_String>(CHECK_TEXT);
    for (auto buttonOptions : testSearchButton) {
        modifier_->setSearchButton(node_, &checkText, &buttonOptions.first);
        auto fullJson = GetJsonValue(node_);
        auto customButtonOptions = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUTTON_OPTIONS_ATTR);
        auto searchButtonColor = GetAttrValue<std::string>(customButtonOptions, BUTTON_OPTIONS_COLOR_ATTR);
        auto searchButtonSize = GetAttrValue<std::string>(customButtonOptions, BUTTON_OPTIONS_SIZE_ATTR);
        EXPECT_EQ(searchButtonColor, buttonOptions.second.first);
        EXPECT_EQ(searchButtonSize, buttonOptions.second.second);
    }
}

/**
 * @tc.name: setTextIndent
 * @tc.desc: Check the functionality of setTextIndent
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setTextIndentTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextIndent, nullptr);
    // default
    auto indentValueDefault = GetStringAttribute(node_, TEXT_INDENT_ATTR);
    EXPECT_EQ(indentValueDefault, CHECK_DEFAULT_VP);

    const std::vector<std::pair<Opt_Dimension, std::string>> INDENT_LENGTH_TEST_PLAN = {
        { ArkValue<Opt_Dimension>("0vp"), "0.00vp" },
        { ArkValue<Opt_Dimension>("1.23px"), "1.23px" },
        { ArkValue<Opt_Dimension>("-5.64fp"), "-5.64fp" },
        { ArkValue<Opt_Dimension>("10%"), "10.00%" },
        { ArkValue<Opt_Dimension>(2.3f), "2.30fp" },
    };
    // custom
    for (auto length : INDENT_LENGTH_TEST_PLAN) {
        modifier_->setTextIndent(node_, &length.first);
        auto indentValue = GetStringAttribute(node_, TEXT_INDENT_ATTR);
        EXPECT_EQ(indentValue, length.second);
    }
}

/**
 * @tc.name: setEnableKeyboardOnFocusTest
 * @tc.desc: Check the functionality of setEnableKeyboardOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setEnableKeyboardOnFocusTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnableKeyboardOnFocus, nullptr);

    auto fullJson = GetJsonValue(node_);
    auto checkVal = GetAttrValue<bool>(fullJson, ENABLE_KEYBOARD_ON_FOCUS);
    EXPECT_EQ(checkVal, true);

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        auto inputValue = ArkValue<Opt_Boolean>(value);
        modifier_->setEnableKeyboardOnFocus(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        checkVal = GetAttrValue<bool>(fullJson, ENABLE_KEYBOARD_ON_FOCUS);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPlaceholderColorTest
 * @tc.desc: Check the functionality of setPlaceholderColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setPlaceholderColorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPlaceholderColor, nullptr);
    // default
    auto placeholderColor = GetStringAttribute(node_, PLACEHOLDER_COLOR_ATTR);
    EXPECT_EQ(placeholderColor, CHECK_DEFAULT_BLACK_COLOR);
    // color
    modifier_->setPlaceholderColor(node_, &OPT_COLOR_COLOR);
    auto placeholderColorColor = GetStringAttribute(node_, PLACEHOLDER_COLOR_ATTR);
    EXPECT_EQ(placeholderColorColor, CHECK_COLOR_COLOR);
    //int
    modifier_->setPlaceholderColor(node_, &OPT_COLOR_INT);
    auto placeholderColorInt = GetStringAttribute(node_, PLACEHOLDER_COLOR_ATTR);
    EXPECT_EQ(placeholderColorInt, CUSTOM_COLOR_STRING);
    // string
    modifier_->setPlaceholderColor(node_, &OPT_COLOR_STRING);
    auto placeholderColorString = GetStringAttribute(node_, PLACEHOLDER_COLOR_ATTR);
    EXPECT_EQ(placeholderColorString, CUSTOM_COLOR_STRING);
}

/**
 * @tc.name: setCaretStyleTest
 * @tc.desc: Check the functionality of setCaretStyle
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setCaretStyleTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCaretStyle, nullptr);
    auto fullJsonDefault = GetJsonValue(node_);
    auto defaultCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(fullJsonDefault, CARET_STYLE_ATTR);
    auto defaultCaretColor = GetAttrValue<std::string>(defaultCaretStyle, CARET_STYLE_COLOR_ATTR);
    auto defaultCaretWidth = GetAttrValue<std::string>(defaultCaretStyle, CARET_STYLE_WIDTH_ATTR);
    EXPECT_EQ(defaultCaretColor, CHECK_DEFAULT_BLACK_COLOR);
    EXPECT_EQ(defaultCaretWidth, CHECK_DEFAULT_PX);

    using TestCaretStyle = std::pair<Opt_CaretStyle, CheckCaretValue>;
    std::vector<TestCaretStyle> testPlanCaretStyle;
    for (auto testLength : OPT_LENGTH_TEST_PLAN) {
        for (auto ColorTest : COLOR_TEST_PLAN) {
            Ark_CaretStyle arkCaretStyle = { .color = ColorTest.first, .width = testLength.first };
            CheckCaretValue caretValue = { ColorTest.second, testLength.second };
            TestCaretStyle testCaretStyle = { ArkValue<Opt_CaretStyle>(arkCaretStyle), caretValue };
            testPlanCaretStyle.push_back(testCaretStyle);
        }
    }

    for (auto caretStyle : testPlanCaretStyle) {
        modifier_->setCaretStyle(node_, &caretStyle.first);
        auto value = GetStringAttribute(node_, CARET_STYLE_ATTR);
        auto fullJson = GetJsonValue(node_);
        auto customCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, CARET_STYLE_ATTR);
        auto caretColor = GetAttrValue<std::string>(customCaretStyle, CARET_STYLE_COLOR_ATTR);
        auto caretWidth = GetAttrValue<std::string>(customCaretStyle, CARET_STYLE_WIDTH_ATTR);
        EXPECT_EQ(caretColor, caretStyle.second.first);
        EXPECT_EQ(caretWidth, caretStyle.second.second);
    }
}

/**
 * @tc.name: selectedBackgroundColorTest
 * @tc.desc: Check the functionality of selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_selectedBackgroundColorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedBackgroundColor, nullptr);
    // default
    auto selectedBackgroundColor = GetStringAttribute(node_, SELECTED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(selectedBackgroundColor, CHECK_DEFAULT_BLACK_COLOR);
    // color
    modifier_->setSelectedBackgroundColor(node_, &OPT_COLOR_COLOR);
    auto selectedBackgroundColorColor = GetStringAttribute(node_, SELECTED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(selectedBackgroundColorColor, CHECK_COLOR_COLOR);
    //int
    modifier_->setSelectedBackgroundColor(node_, &OPT_COLOR_INT);
    auto selectedBackgroundColorInt = GetStringAttribute(node_, SELECTED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(selectedBackgroundColorInt, CUSTOM_COLOR_STRING);
    // string
    modifier_->setSelectedBackgroundColor(node_, &OPT_COLOR_STRING);
    auto selectedBackgroundColorString = GetStringAttribute(node_, SELECTED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(selectedBackgroundColorString, CUSTOM_COLOR_STRING);
}

/**
 * @tc.name: setSelectionMenuHidden
 * @tc.desc: Test Radio setSelectionMenuHidden.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setSelectionMenuHidden, TestSize.Level1)
{
    auto fullJsonDefault = GetJsonValue(node_);
    auto checkVal = GetAttrValue<bool>(fullJsonDefault, SELECTION_MENU_HIDDEN_ATTR);
    EXPECT_EQ(checkVal, false);
    auto inputValue = ArkValue<Opt_Boolean>(true);
    modifier_->setSelectionMenuHidden(node_, &inputValue);
    auto fullJson = GetJsonValue(node_);
    checkVal = GetAttrValue<bool>(fullJson, SELECTION_MENU_HIDDEN_ATTR);
    EXPECT_EQ(checkVal, true);
}

/**
 * @tc.name: setMaxLengthTest
 * @tc.desc: Check the functionality of setMaxLength.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setMaxLengthTest, TestSize.Level1)
{
    const auto defaultValue = "INF";
    ASSERT_NE(modifier_->setMaxLength, nullptr);
    auto checkVal = GetStringAttribute(node_, MAX_LENGTH_ATTR);
    EXPECT_EQ(checkVal, defaultValue);
    const std::vector<std::pair<Opt_Int32, std::string>> testPlan = {
        { ArkValue<Opt_Int32>(20), "20"},
        { ArkValue<Opt_Int32>(0), "0"},
        { ArkValue<Opt_Int32>(-20), defaultValue},
    };
    for (const auto &[value, expectVal]: testPlan) {
        modifier_->setMaxLength(node_, &value);
        checkVal = GetStringAttribute(node_, MAX_LENGTH_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setMinFontSizeTest
 * @tc.desc: Check the functionality of setMinFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setMinFontSizeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMinFontSize, nullptr);
    auto checkVal = GetStringAttribute(node_, MIN_FONT_SIZE_ATTR);
    EXPECT_EQ(checkVal, "0.00px");

    for (const auto &[value, expectVal]: UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setMinFontSize(node_, &value);
        checkVal = GetStringAttribute(node_, MIN_FONT_SIZE_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setMaxFontSizeTest
 * @tc.desc: Check the functionality of setMaxFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setMaxFontSizeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaxFontSize, nullptr);

    auto checkVal = GetStringAttribute(node_, MAX_FONT_SIZE_ATTR);
    EXPECT_EQ(checkVal, "0.00px");

    for (const auto &[value, expectVal]: UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setMaxFontSize(node_, &value);
        checkVal = GetStringAttribute(node_, MAX_FONT_SIZE_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setLetterSpacingTest
 * @tc.desc: Check the functionality of setLetterSpacing
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setLetterSpacingTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLetterSpacing, nullptr);

    auto checkVal = GetStringAttribute(node_, LETTER_SPACING_ATTR);
    EXPECT_EQ(checkVal, "0.00px");

    for (const auto &[value, expectVal]: UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setLetterSpacing(node_, &value);
        checkVal = GetStringAttribute(node_, LETTER_SPACING_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setEnablePreviewTextTest
 * @tc.desc: Check the functionality of setEnablePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setEnablePreviewTextTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnablePreviewText, nullptr);
    auto fullJsonDefault = GetJsonValue(node_);
    auto checkVal = GetAttrValue<bool>(fullJsonDefault, ENABLE_PREVIEW_TEXT);
    EXPECT_EQ(checkVal, true);

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        auto inputValue = ArkValue<Opt_Boolean>(value);
        modifier_->setEnablePreviewText(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        checkVal = GetAttrValue<bool>(fullJson, ENABLE_PREVIEW_TEXT);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPlaceholderFontTestStyle
 * @tc.desc: Check the functionality of setPlaceholderFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setPlaceholderFontTestStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPlaceholderFont, nullptr);

    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto fontOpt = ArkValue<Opt_Font>(font);
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        fontOpt = ArkValue<Opt_Font>(font);
        modifier_->setPlaceholderFont(node_, &fontOpt);
        auto placeholderFontJSON = GetStringAttribute(node_, PLACEHOLDER_FONT_ATTRS);
        auto placeholderFont = JsonUtil::ParseJsonString(placeholderFontJSON);
        auto checkSize = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_SIZE);
        auto checkFamily = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_FAMILY);
        auto checkWeight = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_WEIGHT);
        if (checkWeight.empty()) {
            checkWeight = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_WEIGHT_ENUM);
        }
        auto checkStyle = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_STYLE);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setPlaceholderFontTestWeight
 * @tc.desc: Check the functionality of setPlaceholderFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setPlaceholderFontTestWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPlaceholderFont, nullptr);

    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto fontOpt = ArkValue<Opt_Font>(font);
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        fontOpt = ArkValue<Opt_Font>(font);
        modifier_->setPlaceholderFont(node_, &fontOpt);
        auto placeholderFontJSON = GetStringAttribute(node_, PLACEHOLDER_FONT_ATTRS);
        auto placeholderFont = JsonUtil::ParseJsonString(placeholderFontJSON);
        auto checkSize = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_SIZE);
        auto checkFamily = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_FAMILY);
        auto checkWeight = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_WEIGHT);
        if (checkWeight.empty()) {
            checkWeight = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_WEIGHT_ENUM);
        }
        auto checkStyle = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_STYLE);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setPlaceholderFontTestFamily
 * @tc.desc: Check the functionality of setPlaceholderFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setPlaceholderFontTestFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPlaceholderFont, nullptr);

    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto fontOpt = ArkValue<Opt_Font>(font);
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto family : UNION_RESOURCE_STRING_PLAN) {
        font.family = family.first;
        fontOpt = ArkValue<Opt_Font>(font);
        modifier_->setPlaceholderFont(node_, &fontOpt);
        auto placeholderFontJSON = GetStringAttribute(node_, PLACEHOLDER_FONT_ATTRS);
        auto placeholderFont = JsonUtil::ParseJsonString(placeholderFontJSON);
        auto checkSize = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_SIZE);
        auto checkFamily = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_FAMILY);
        auto checkWeight = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_WEIGHT);
        if (checkWeight.empty()) {
            checkWeight = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_WEIGHT_ENUM);
        }
        auto checkStyle = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_STYLE);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setPlaceholderFontTestSize
 * @tc.desc: Check the functionality of setPlaceholderFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setPlaceholderFontTestSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPlaceholderFont, nullptr);

    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto fontOpt = ArkValue<Opt_Font>(font);
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto size : OPT_LENGTH_TEST_PLAN) {
        font.size = size.first;
        fontOpt = ArkValue<Opt_Font>(font);
        modifier_->setPlaceholderFont(node_, &fontOpt);
        auto placeholderFontJSON = GetStringAttribute(node_, PLACEHOLDER_FONT_ATTRS);
        auto placeholderFont = JsonUtil::ParseJsonString(placeholderFontJSON);
        auto checkSize = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_SIZE);
        auto checkFamily = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_FAMILY);
        auto checkWeight = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_WEIGHT);
        if (checkWeight.empty()) {
            checkWeight = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_WEIGHT_ENUM);
        }
        auto checkStyle = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_STYLE);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setTextFontTestStyle
 * @tc.desc: Check the functionality of setTextFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setTextFontTestStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextFont, nullptr);

    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto fontOpt = ArkValue<Opt_Font>(font);
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        fontOpt = ArkValue<Opt_Font>(font);
        modifier_->setTextFont(node_, &fontOpt);
        auto textFontJSON = GetStringAttribute(node_, TEXT_FONT_ATTRS);
        auto textFont = JsonUtil::ParseJsonString(textFontJSON);
        auto checkSize = GetAttrValue<std::string>(textFont, TEXT_FONT_SIZE_ATTR);
        auto checkFamily = GetAttrValue<std::string>(textFont, TEXT_FONT_FAMILY_ATTR);
        auto checkWeight = GetAttrValue<std::string>(textFont, TEXT_FONT_WEIGHT_ATTR);
        auto checkStyle = GetAttrValue<std::string>(textFont, TEXT_FONT_STYLE_ATTR);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setTextFontTestFontWeight
 * @tc.desc: Check the functionality of setTextFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setTextFontTestFontWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextFont, nullptr);

    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto fontOpt = ArkValue<Opt_Font>(font);
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        fontOpt = ArkValue<Opt_Font>(font);
        modifier_->setTextFont(node_, &fontOpt);
        auto textFontJSON = GetStringAttribute(node_, TEXT_FONT_ATTRS);
        auto textFont = JsonUtil::ParseJsonString(textFontJSON);
        auto checkSize = GetAttrValue<std::string>(textFont, TEXT_FONT_SIZE_ATTR);
        auto checkFamily = GetAttrValue<std::string>(textFont, TEXT_FONT_FAMILY_ATTR);
        auto checkWeight = GetAttrValue<std::string>(textFont, TEXT_FONT_WEIGHT_ATTR);
        auto checkStyle = GetAttrValue<std::string>(textFont, TEXT_FONT_STYLE_ATTR);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setTextFontTestFontFamily
 * @tc.desc: Check the functionality of setTextFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setTextFontTestFontFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextFont, nullptr);

    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto fontOpt = ArkValue<Opt_Font>(font);
    auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto family : UNION_RESOURCE_STRING_PLAN) {
        font.family = family.first;
        fontOpt = ArkValue<Opt_Font>(font);
        modifier_->setTextFont(node_, &fontOpt);
        auto textFontJSON = GetStringAttribute(node_, TEXT_FONT_ATTRS);
        auto textFont = JsonUtil::ParseJsonString(textFontJSON);
        auto checkSize = GetAttrValue<std::string>(textFont, TEXT_FONT_SIZE_ATTR);
        auto checkFamily = GetAttrValue<std::string>(textFont, TEXT_FONT_FAMILY_ATTR);
        auto checkWeight = GetAttrValue<std::string>(textFont, TEXT_FONT_WEIGHT_ATTR);
        auto checkStyle = GetAttrValue<std::string>(textFont, TEXT_FONT_STYLE_ATTR);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setTextFontTestFontSize
 * @tc.desc: Check the functionality of setTextFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setTextFontTestFontSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextFont, nullptr);

    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = OPT_LENGTH_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    auto fontOpt = ArkValue<Opt_Font>(font);
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    for (auto size : OPT_LENGTH_TEST_PLAN) {
        font.size = size.first;
        fontOpt = ArkValue<Opt_Font>(font);
        modifier_->setTextFont(node_, &fontOpt);
        auto textFontJSON = GetStringAttribute(node_, TEXT_FONT_ATTRS);
        auto textFont = JsonUtil::ParseJsonString(textFontJSON);
        auto checkSize = GetAttrValue<std::string>(textFont, TEXT_FONT_SIZE_ATTR);
        auto checkFamily = GetAttrValue<std::string>(textFont, TEXT_FONT_FAMILY_ATTR);
        auto checkWeight = GetAttrValue<std::string>(textFont, TEXT_FONT_WEIGHT_ATTR);
        auto checkStyle = GetAttrValue<std::string>(textFont, TEXT_FONT_STYLE_ATTR);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}
/**
 * @tc.name: setLineHeightTest
 * @tc.desc: Check the functionality of setLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setLineHeightTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLineHeight, nullptr);

    auto checkVal = GetStringAttribute(node_, LINE_HEIGHT_ATTR);
    EXPECT_EQ(checkVal, "0.00vp");

    for (const auto &[value, expectVal]: UNION_NUM_STR_RES_TEST_PLAN_WITH_PERCENT) {
        modifier_->setLineHeight(node_, &value);
        checkVal = GetStringAttribute(node_, LINE_HEIGHT_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setEnterKeyTypeTest
 * @tc.desc: Check the functionality of setEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setEnterKeyTypeTest, TestSize.Level1)
{
    const auto defaultValue = "EnterKeyType.Search";
    ASSERT_NE(modifier_->setEnterKeyType, nullptr);
    auto checkVal = GetStringAttribute(node_, ENTER_KEY_TYPE_ATTR);
    EXPECT_EQ(checkVal, defaultValue);

    const std::vector<std::pair<Opt_EnterKeyType, std::string>> ENTER_KEY_TYPE_TEST_PLAN = {
        { ArkValue<Opt_EnterKeyType>(ARK_ENTER_KEY_TYPE_NEXT), "EnterKeyType.Next" },
        { ArkValue<Opt_EnterKeyType>(ARK_ENTER_KEY_TYPE_DONE), "EnterKeyType.Done" },
        { ArkValue<Opt_EnterKeyType>(ARK_ENTER_KEY_TYPE_PREVIOUS), "EnterKeyType.PREVIOUS" },
        { ArkValue<Opt_EnterKeyType>(ARK_ENTER_KEY_TYPE_NEW_LINE), "EnterKeyType.NEW_LINE" },
        { ArkValue<Opt_EnterKeyType>(ARK_ENTER_KEY_TYPE_SEND), "EnterKeyType.Send" },
        { ArkValue<Opt_EnterKeyType>(ARK_ENTER_KEY_TYPE_SEARCH), "EnterKeyType.Search" },
        { ArkValue<Opt_EnterKeyType>(ARK_ENTER_KEY_TYPE_GO), "EnterKeyType.Go" },
        { ArkValue<Opt_EnterKeyType>(INVALID_ENUM_VAL<Ark_EnterKeyType>), defaultValue },
    };

    for (const auto &[value, expectVal]: ENTER_KEY_TYPE_TEST_PLAN) {
        modifier_->setEnterKeyType(node_, &value);
        checkVal = GetStringAttribute(node_, ENTER_KEY_TYPE_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setTextAlignTest
 * @tc.desc: Check the functionality of setTextAlign
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setTextAlignTest, TestSize.Level1)
{
    const auto defaultValue = "TextAlign.Start";
    ASSERT_NE(modifier_->setTextAlign, nullptr);

    auto checkVal = GetStringAttribute(node_, TEXT_ALIGN_ATTR);
    EXPECT_EQ(checkVal, defaultValue);

    const std::vector<std::pair<Opt_TextAlign, std::string>> TEXT_ALIGN_TEST_PLAN = {
        { ArkValue<Opt_TextAlign>(ARK_TEXT_ALIGN_CENTER), "TextAlign.Center" },
        { ArkValue<Opt_TextAlign>(ARK_TEXT_ALIGN_START), "TextAlign.Start" },
        { ArkValue<Opt_TextAlign>(ARK_TEXT_ALIGN_END), "TextAlign.End" },
        { ArkValue<Opt_TextAlign>(ARK_TEXT_ALIGN_JUSTIFY), "TextAlign.Justify" },
        { ArkValue<Opt_TextAlign>(INVALID_ENUM_VAL<Ark_TextAlign>), defaultValue },
    };

    for (const auto &[value, expectVal]: TEXT_ALIGN_TEST_PLAN) {
        modifier_->setTextAlign(node_, &value);
        checkVal = GetStringAttribute(node_, TEXT_ALIGN_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setTypeTest
 * @tc.desc: Check the functionality of setType
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setTypeTest, TestSize.Level1)
{
    const auto defaultValue = "SearchType.NORMAL";
    ASSERT_NE(modifier_->setType, nullptr);
    auto checkVal = GetStringAttribute(node_, TYPE_ATTR);
    EXPECT_EQ(checkVal, defaultValue);

    const std::vector<std::pair<Opt_SearchType, std::string>> SEARCH_TYPE_TEST_PLAN = {
        { ArkValue<Opt_SearchType>(ARK_SEARCH_TYPE_NORMAL), "SearchType.NORMAL" },
        { ArkValue<Opt_SearchType>(ARK_SEARCH_TYPE_EMAIL), "SearchType.EMAIL" },
        { ArkValue<Opt_SearchType>(ARK_SEARCH_TYPE_URL), "SearchType.NORMAL" },
        { ArkValue<Opt_SearchType>(ARK_SEARCH_TYPE_NUMBER), "SearchType.NUMBER" },
        // Work incorrect: should be NUMBER_DECIMAL, but in pattern return NORMAL
        { ArkValue<Opt_SearchType>(ARK_SEARCH_TYPE_NUMBER_DECIMAL), "SearchType.NORMAL" },
        { ArkValue<Opt_SearchType>(ARK_SEARCH_TYPE_PHONE_NUMBER), "SearchType.PHONE_NUMBER" },
        { ArkValue<Opt_SearchType>(INVALID_ENUM_VAL<Ark_SearchType>), defaultValue },
    };

    for (const auto &[value, expectVal]: SEARCH_TYPE_TEST_PLAN) {
        modifier_->setType(node_, &value);
        checkVal = GetStringAttribute(node_, TYPE_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setDecorationTest
 * @tc.desc: Check the functionality of setDecoration
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setDecorationTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDecoration, nullptr);
    auto defaultDecorationJSON = GetStringAttribute(node_, DECORATION_ATTRS);
    auto defaultDecoration = JsonUtil::ParseJsonString(defaultDecorationJSON);
    auto defaultType = GetAttrValue<std::string>(defaultDecoration, DECORATION_TYPE_ATTR);
    auto defaultStyle = GetAttrValue<std::string>(defaultDecoration, DECORATION_STYLE_ATTR);
    auto defaultColor = GetAttrValue<std::string>(defaultDecoration, DECORATION_COLOR_ATTR);
    EXPECT_EQ(defaultType, "TextDecorationType.None");
    EXPECT_EQ(defaultStyle, "TextDecorationStyle.SOLID");
    EXPECT_EQ(defaultColor, CHECK_DEFAULT_BLACK_COLOR);

    for (const auto &[decorationType, expectDecorationType]: TEXT_DECORATION_TYPE_TEST_PLAN) {
        for (const auto &[decorationStyle, expectDecorationStyle]: TEXT_DECORATION_STYLE_TEST_PLAN) {
            for (const auto &[decorationColor, expectColor] : COLOR_TEST_PLAN) {
                Ark_TextDecorationOptions options = {
                    .color = decorationColor,
                    .type = ArkValue<Opt_TextDecorationType>(decorationType),
                    .style = ArkValue<Opt_TextDecorationStyle>(decorationStyle)
                };
                auto inputValue = ArkValue<Opt_TextDecorationOptions>(options);
                modifier_->setDecoration(node_, &inputValue);
                auto decorationJSON = GetStringAttribute(node_, DECORATION_ATTRS);
                auto decoration = JsonUtil::ParseJsonString(decorationJSON);
                auto type = GetAttrValue<std::string>(decoration, DECORATION_TYPE_ATTR);
                auto style = GetAttrValue<std::string>(decoration, DECORATION_STYLE_ATTR);
                auto color = GetAttrValue<std::string>(decoration, DECORATION_COLOR_ATTR);
                EXPECT_EQ(type, expectDecorationType);
                EXPECT_EQ(style, expectDecorationStyle);
                EXPECT_EQ(color, expectColor);
            }
        }
    }
}

/**
 * @tc.name: setFontFeatureTest
 * @tc.desc: Check the functionality of setFontFeature
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setFontFeatureTest, TestSize.Level1)
{
    const auto defaultValue = "";
    ASSERT_NE(modifier_->setFontFeature, nullptr);
    auto checkVal = GetStringAttribute(node_, FONT_FEATURE_ATTR);
    EXPECT_EQ(checkVal, defaultValue);

    const std::vector<std::pair<Opt_String, std::string>> FONT_FEATURE_TEST_PLAN = {
        {ArkValue<Opt_String>("\"ss01\" on"), "\"ss01\" 1"},
        {ArkValue<Opt_String>("\"ss01\" off"), "\"ss01\" 0"},
        {ArkValue<Opt_String>("\"ss01\" 1"), "\"ss01\" 1"},
        {ArkValue<Opt_String>("\"ss01\" 0"), "\"ss01\" 0"},
        {ArkValue<Opt_String>("ss01 1"), defaultValue},
        {ArkValue<Opt_String>("\"ss01\" on, \"ss02\" on"), "\"ss01\" 1,\"ss02\" 1"},
        {ArkValue<Opt_String>("\"ss01\" on, \"ss02\" off"), "\"ss01\" 1,\"ss02\" 0"},
        {ArkValue<Opt_String>("\"ss01\" on, ss02 off"), "\"ss01\" 1"},
        {ArkValue<Opt_String>("ss01 on, ss02 off"), defaultValue},
        {ArkValue<Opt_String>("\"ss01\" on"), "\"ss01\" 1"},
        {ArkValue<Opt_String>("\"incorrect\" on"), defaultValue},
        {ArkValue<Opt_String>("\"ss01\" on"), "\"ss01\" 1"},
        {ArkValue<Opt_String>("invalid"), defaultValue},
    };

    for (const auto &[value, expectVal]: FONT_FEATURE_TEST_PLAN) {
        modifier_->setFontFeature(node_, &value);
        checkVal = GetStringAttribute(node_, FONT_FEATURE_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setsetEnableHapticFeedbackTest
 * @tc.desc: Check the functionality of setsetEnableHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setEnableHapticFeedbackTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnableKeyboardOnFocus, nullptr);

    auto fullJson = GetJsonValue(node_);
    auto checkVal = GetAttrValue<bool>(fullJson, ENABLE_HAPTIC_FEEDBACK_ATTR);
    EXPECT_EQ(checkVal, true);

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        auto inputValue = ArkValue<Opt_Boolean>(value);
        modifier_->setEnableHapticFeedback(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        checkVal = GetAttrValue<bool>(fullJson, ENABLE_HAPTIC_FEEDBACK_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

#ifdef WRONG_OLD_SDK
/*
 * @tc.name: setOnChangeEventValueImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setOnChangeEventValueImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::string value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_String parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::Convert<std::string>(parameter)
        };
    };

    Callback_String_Void arkCallback = Converter::ArkValue<Callback_String_Void>(checkCallback, contextId);

    modifier_->set_onChangeEvent_value(node_, &arkCallback);

    PreviewText previewText {.offset = -1, .value = u""};
    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnChange({u"test", previewText});
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, "test");
    eventHub->FireOnChange({u"test_2", previewText});
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, "test_2");
}
#endif

/*
 * @tc.name: setMinFontScaleDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setMinFontScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, MIN_FONT_SCALE_ATTR);
    EXPECT_EQ(resultStr, MIN_FONT_SCALE_DEFAULT_VALUE) << "Default value for attribute 'minFontScale'";
}

/*
 * @tc.name: setMinFontScaleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setMinFontScaleTestValidValues, TestSize.Level1)
{
    std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureMinFontScaleNumValidValues = {
        { "0.1", Converter::ArkValue<Ark_Float64>(0.1), "0.100000" },
        { "0.89", Converter::ArkValue<Ark_Float64>(0.89), "0.890000" },
        { "1", Converter::ArkValue<Ark_Float64>(1.), "1.000000" },
    };

    auto checkValue = [this](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_F64_Resource& value) {
        auto inputValueMinFontScale = value;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, MIN_FONT_SCALE_ATTR);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };
    for (auto& [input, value, expected] : testFixtureMinFontScaleNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(value));
    }

    const auto scaleRes = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(FLOAT_RES_0);
    modifier_->setMinFontScale(node_, &scaleRes);
    auto checkVal2 = GetStringAttribute(node_, MIN_FONT_SCALE_ATTR);
    EXPECT_EQ(checkVal2, "0.705000");
}

/*
 * @tc.name: setMinFontScaleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setMinFontScaleTestInvalidValues, TestSize.Level1)
{
    // Initial setup
    auto initValueMinFontScale = ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(1.0);
    auto checkValue = [this, &initValueMinFontScale](const std::string& input, const Opt_Union_F64_Resource& value) {
        auto inputValueMinFontScale = initValueMinFontScale;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        inputValueMinFontScale = value;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, MIN_FONT_SCALE_ATTR);
        EXPECT_EQ(resultStr, MIN_FONT_SCALE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_F64_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_F64_Resource>());
}

/*
 * @tc.name: setMaxFontScaleDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setMaxFontScaleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, MAX_FONT_SCALE_ATTR);
    EXPECT_EQ(resultStr, MAX_FONT_SCALE_DEFAULT_VALUE) << "Default value for attribute 'maxFontScale'";
}

/*
 * @tc.name: setMaxFontScaleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setMaxFontScaleTestValidValues, TestSize.Level1)
{
    std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureMaxFontScaleNumValidValues = {
        { "1", Converter::ArkValue<Ark_Float64>(1.0), "1.000000" },
        { "1.5", Converter::ArkValue<Ark_Float64>(1.5), "1.500000" },
        { "1.99", Converter::ArkValue<Ark_Float64>(1.99), "1.990000" },
    };
    auto checkValue = [this](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_F64_Resource& value) {
        auto inputValueMaxFontScale = value;
        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, MAX_FONT_SCALE_ATTR);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };
    for (auto& [input, value, expected] : testFixtureMaxFontScaleNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(value));
    }

    const auto scaleRes = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(FLOAT_RES_1);
    modifier_->setMaxFontScale(node_, &scaleRes);
    auto checkVal2 = GetStringAttribute(node_, MAX_FONT_SCALE_ATTR);
    EXPECT_EQ(checkVal2, "1.200000");
}

/*
 * @tc.name: setMaxFontScaleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setMaxFontScaleTestInvalidValues, TestSize.Level1)
{
    // Initial setup
    auto initValueMaxFontScale = ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(1.0);
    auto checkValue = [this, &initValueMaxFontScale](const std::string& input, const Opt_Union_F64_Resource& value) {
        auto inputValueMaxFontScale = initValueMaxFontScale;
        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        inputValueMaxFontScale = value;
        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, MAX_FONT_SCALE_ATTR);
        EXPECT_EQ(resultStr, MAX_FONT_SCALE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_F64_Resource, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_F64_Resource>());
}

/*
 * @tc.name: setHalfLeadingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setHalfLeadingTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, HALF_LEADING_ATTR);
    EXPECT_EQ(resultStr, HALF_LEADING_DEFAULT_VALUE) << "Default value for attribute 'halfLeading'";
}

/*
 * @tc.name: setHalfLeadingTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setHalfLeadingTestValidValues, TestSize.Level1)
{
    Opt_Boolean initValueHalfLeading;
    // Initial setup
    initValueHalfLeading = ArkValue<Opt_Boolean>(std::get<1>(testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueHalfLeading](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueHalfLeading = initValueHalfLeading;

        inputValueHalfLeading = value;
        modifier_->setHalfLeading(node_, &inputValueHalfLeading);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, HALF_LEADING_ATTR);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHalfLeading, attribute: halfLeading";
    };

    for (auto& [input, value, expected] : testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setHalfLeadingTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setHalfLeadingTestInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueHalfLeading;

    // Initial setup
    initValueHalfLeading = ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false));

    auto checkValue = [this, &initValueHalfLeading](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueHalfLeading = initValueHalfLeading;

        modifier_->setHalfLeading(node_, &inputValueHalfLeading);
        inputValueHalfLeading = value;
        modifier_->setHalfLeading(node_, &inputValueHalfLeading);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, HALF_LEADING_ATTR);
        EXPECT_EQ(resultStr, HALF_LEADING_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setHalfLeading, attribute: halfLeading";
    };
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setStopBackPressTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setStopBackPressTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, STOP_BACK_PRESS_ATTR);
    EXPECT_EQ(resultStr, STOP_BACK_PRESS_DEFAULT_VALUE) << "Default value for attribute 'stopBackPress'";
}

/*
 * @tc.name: setStopBackPressTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setStopBackPressTestValidValues, TestSize.Level1)
{
    Opt_Boolean initValueHalfLeading;
    // Initial setup
    initValueHalfLeading = ArkValue<Opt_Boolean>(std::get<1>(testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueHalfLeading](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueHalfLeading = initValueHalfLeading;

        inputValueHalfLeading = value;
        modifier_->setStopBackPress(node_, &inputValueHalfLeading);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, STOP_BACK_PRESS_ATTR);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setStopBackPress, attribute: stopBackPress";
    };

    for (auto& [input, value, expected] : testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setStopBackPressTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setStopBackPressTestInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueHalfLeading;

    // Initial setup
    initValueHalfLeading = ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true));

    auto checkValue = [this, &initValueHalfLeading](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueHalfLeading = initValueHalfLeading;

        modifier_->setStopBackPress(node_, &inputValueHalfLeading);
        inputValueHalfLeading = value;
        modifier_->setStopBackPress(node_, &inputValueHalfLeading);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, STOP_BACK_PRESS_ATTR);
        EXPECT_EQ(resultStr, STOP_BACK_PRESS_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setStopBackPress, attribute: stopBackPress";
    };
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}
} // namespace OHOS::Ace::NG
