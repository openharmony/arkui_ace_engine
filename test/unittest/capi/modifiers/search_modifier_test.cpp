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

#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
Ark_Resource ArkResStr(Ark_String* name, int id = -1,
    NodeModifier::ResourceType type = NodeModifier::ResourceType::MEDIA, const char* module = "",
    const char* bundle = "")
{
    return {
        .id = ArkValue<Ark_Number>(id),
        .type = ArkValue<Ark_Number>(static_cast<int>(type)),
        .moduleName = ArkValue<Ark_String>(module),
        .bundleName = ArkValue<Ark_String>(bundle),
        .params = {
            .tag = ARK_TAG_OBJECT,
            .value = {
                .array = name,
                .length = name ? 1 : 0
            }
        }
    };
}
// attrs
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
const auto INPUT_FILTER_ATTR("inputFilter");
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

// custom colors
const auto CUSTOM_COLOR_STRING("#FF123456");
const int CUSTOM_COLOR_INT(0xFF123456);
const float CUSTOM_COLOR_FLOAT(0.1f);
const auto CHECK_FLOAT_COLOR("#00000000");
const auto CHECK_COLOR_COLOR("#FF008000");
const auto RES_NAME(ArkValue<Ark_String>("aa.bb.cc"));

const Ark_ResourceColor COLOR_COLOR = { .selector = 0, .value0 = Ark_Color::ARK_COLOR_GREEN };
const Ark_ResourceColor COLOR_INT = { .selector = 1, .value1 = ArkValue<Ark_Number>(CUSTOM_COLOR_INT) };
const Ark_ResourceColor COLOR_FLOAT = { .selector = 1, .value1 = ArkValue<Ark_Number>(CUSTOM_COLOR_FLOAT) };
const Ark_ResourceColor COLOR_STRING = { .selector = 2, .value2 = ArkValue<Ark_String>(CUSTOM_COLOR_STRING) };

const Opt_ResourceColor OPT_COLOR_COLOR = { .tag = ARK_TAG_OBJECT, .value = COLOR_COLOR };
const Opt_ResourceColor OPT_COLOR_INT = { .tag = ARK_TAG_OBJECT, .value = COLOR_INT };
const Opt_ResourceColor OPT_COLOR_FLOAT = { .tag = ARK_TAG_OBJECT, .value = COLOR_FLOAT };
const Opt_ResourceColor OPT_COLOR_STRING = { .tag = ARK_TAG_OBJECT, .value = COLOR_STRING };

//  default colors
const Opt_ResourceStr OPT_RESOURCE_STR = { .tag = ARK_TAG_OBJECT,
    .value = {
        .selector = 0,
        .value0 = RES_NAME
    }
};
const Opt_ResourceStr OPT_RESOURCE_RESOURCE = {
    .tag = ARK_TAG_OBJECT,
    .value = {
        .selector = 1,
        .value1 = ArkResStr(const_cast<Ark_String*>(&RES_NAME))
    }
};

const Opt_Union_String_Resource OPT_UNION_RESOURCE_STR = {
    .tag = ARK_TAG_OBJECT,
    .value = {
        .selector = 0,
        .value0 = RES_NAME
    }
};

const Opt_Union_String_Resource OPT_UNION_RESOURCE_RESOURCE = {
    .tag = ARK_TAG_OBJECT,
    .value = {
        .selector = 1,
        .value1 = ArkResStr(const_cast<Ark_String*>(&RES_NAME))
    }
};

// icon
const auto CHECK_DEFAULT_BLACK_COLOR("#FF000000");

// length values
const Ark_Int32 AINT32_POS(1234);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const auto ALEN_PX_POS = ArkValue<Ark_Length>(AINT32_POS);
const auto ALEN_PX_NEG = ArkValue<Ark_Length>(AINT32_NEG);
const auto ALEN_VP_POS = ArkValue<Ark_Length>(AFLT32_POS);
const auto ALEN_VP_NEG = ArkValue<Ark_Length>(AFLT32_NEG);
const auto OPT_LEN_PX_POS = ArkValue<Opt_Length>(AINT32_POS);
const auto OPT_LEN_PX_NEG = ArkValue<Opt_Length>(AINT32_NEG);
const auto OPT_LEN_VP_POS = ArkValue<Opt_Length>(AFLT32_POS);
const auto OPT_LEN_VP_NEG = ArkValue<Opt_Length>(AFLT32_NEG);

// default length
const std::string CHECK_DEFAULT_PX("0.00px");
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
const auto ERROR_TEXT("test_error_text");
PreviewText PREVIEW_TEXT = { .offset = 1234, .value = "test_offset" };
const auto EMPTY_TEXT("");

// check resource
const Ark_String STR_NAME = ArkValue<Ark_String>("min_font_size");
const std::string CHECK_RESOURCE_STR("aa.bb.cc");

// check styles
const std::string BUTTON_STYLE_INPUT("CancelButtonStyle.INPUT");

// test types
typedef std::pair<Ark_Length, std::string> LengthTest;
typedef std::pair<Opt_Length, std::string> OptLengthTest;
typedef std::pair<Ark_Number, std::string> ArkNumberTest;
typedef std::pair<Opt_ResourceColor, std::string> ColorTest;
typedef std::pair<std::string, std::string> CheckCaretValue;
typedef std::pair<std::string, std::string> CheckSearchButtonOptions;
typedef std::pair<Ark_CaretStyle, CheckCaretValue> TestCaretStyle;
typedef std::pair<Opt_SearchButtonOptions, CheckSearchButtonOptions> TestSearchButtonOption;
typedef std::tuple<std::string, std::string, std::string> TripleCheckValues;
typedef std::pair<Opt_ResourceStr, std::string> ResourceSRC;
typedef std::pair<Opt_Union_String_Resource, std::string> UnionResourceString;
typedef std::pair<Opt_FontStyle, std::string> ArkFontStyleTest;
typedef std::pair<Ark_CancelButtonStyle, std::string> ArkCancelButtonStyleTest;
typedef std::pair<Ark_CopyOptions, std::string> ArkCopyOptionsTest;
typedef std::pair<Ark_Int32, Ark_Int32> ArkNumberIntTest;
typedef std::pair<float, float> ArkNumberFloatTest;
typedef std::pair<Opt_Union_FontWeight_Number_String, std::string> ArkFontWeightTest;
typedef std::pair<Type_SearchAttribute_searchIcon_Arg0, TripleCheckValues> SearchIconTest;
typedef std::tuple<Ark_Boolean, bool> OneBoolStep;
typedef std::pair<Opt_Type_SearchInterface_setSearchOptions_Arg0, TripleCheckValues> OptionsTest;
typedef std::pair<Union_Number_String_Resource, std::string> OneUnionNumStrResStep;
typedef std::pair<Ark_TextDecorationType, std::string> DecorationTypeTest;
typedef std::pair<Ark_TextDecorationStyle, std::string> DecorationStyleTest;
typedef std::pair<Ark_SearchType, std::string> ArkSearchTypeTest;
typedef std::pair<Ark_TextAlign, std::string> TextAlignTest;
typedef std::pair<Ark_String, std::string> FontFeatureTest;
typedef std::pair<Ark_EnterKeyType, std::string> EnterKeyTypeTest;

// common testPlans
const std::vector<OptLengthTest> OPT_LENGTH_TEST_PLAN = {
    { OPT_LEN_PX_POS, CHECK_POSITIVE_VALUE_INT },
    { OPT_LEN_PX_NEG, CHECK_DEFAULT_PX },
    { OPT_LEN_VP_NEG, CHECK_DEFAULT_PX },
    { OPT_LEN_VP_POS, CHECK_POSITIVE_VALUE_FLOAT }
};
const std::vector<OptLengthTest> TEST_PLAN_OPT_LENGTH_PX = {
    { OPT_LEN_PX_POS, CHECK_POSITIVE_VALUE_INT },
    { OPT_LEN_PX_NEG, CHECK_DEFAULT_PX },
    { OPT_LEN_VP_NEG, CHECK_DEFAULT_PX },
    { OPT_LEN_VP_POS, CHECK_POSITIVE_VALUE_FLOAT_PX }
};
const std::vector<OptLengthTest> ICON_SIZE_TEST_PLAN = {
    { OPT_LEN_PX_POS, CHECK_ICON_MAX_VALUE_INT },
    { OPT_LEN_PX_NEG, CHECK_DEFAULT_PX },
    { OPT_LEN_VP_NEG, CHECK_DEFAULT_PX },
    { OPT_LEN_VP_POS, CHECK_POSITIVE_VALUE_FLOAT_PX }
};
const std::vector<LengthTest> INDENT_LENGTH_TEST_PLAN = {
    { ALEN_PX_POS, CHECK_POSITIVE_VALUE_INT },
    { ALEN_PX_NEG, CHECK_NEGATIVE_VALUE_INT },
    { ALEN_VP_NEG, CHECK_NEGATIVE_VALUE_FLOAT },
    { ALEN_VP_POS, CHECK_POSITIVE_VALUE_FLOAT }
};
const std::vector<ArkNumberIntTest> INT_NUMBER_TEST_PLAN = {
    { AINT32_POS, AINT32_POS },
    { AINT32_NEG, AINT32_NEG },
};
const std::vector<ArkNumberFloatTest> FLOAT_NUMBER_TEST_PLAN = {
    { AFLT32_POS, AFLT32_POS },
    { AFLT32_NEG, AFLT32_NEG },
};
const std::vector<ArkNumberTest> ARK_NUMBER_TEST_PLAN = {
    { ArkValue<Ark_Number>(20), "20" },
    { ArkValue<Ark_Number>(0), "0"},
    { ArkValue<Ark_Number>(22.5f), "22"},
    { ArkValue<Ark_Number>(-20), "INF"},
    { ArkValue<Ark_Number>(0.0f), "0"},
    { ArkValue<Ark_Number>(-22.5f), "INF"}
};
const std::vector<ColorTest> COLOR_TEST_PLAN = {
    { OPT_COLOR_COLOR, CHECK_COLOR_COLOR },
    { OPT_COLOR_INT, CUSTOM_COLOR_STRING },
    { OPT_COLOR_FLOAT, CHECK_FLOAT_COLOR },
    { OPT_COLOR_STRING, CUSTOM_COLOR_STRING },
};

const std::vector<ResourceSRC> RESOURCE_TEST_PLAN = {
    { OPT_RESOURCE_STR, CHECK_RESOURCE_STR },
    { OPT_RESOURCE_RESOURCE, CHECK_RESOURCE_STR }
};
const std::vector<UnionResourceString> UNION_RESOURCE_STRING_PLAN = {
    { OPT_UNION_RESOURCE_STR, CHECK_RESOURCE_STR },
    { OPT_UNION_RESOURCE_RESOURCE, CHECK_RESOURCE_STR }
};

const std::vector<OneBoolStep> BOOL_TEST_PLAN = {
    { false, false },
    { true, true },
    { 0, false },
    { -25, true },
    { 0, false },
    { 25, true },
    { false, false }
};

const std::vector<ArkCancelButtonStyleTest> BUTTON_STYLE_TEST_PLAN = {
    { Ark_CancelButtonStyle::ARK_CANCEL_BUTTON_STYLE_CONSTANT, "CancelButtonStyle.CONSTANT" },
    { Ark_CancelButtonStyle::ARK_CANCEL_BUTTON_STYLE_INVISIBLE, "CancelButtonStyle.INVISIBLE" },
    { Ark_CancelButtonStyle::ARK_CANCEL_BUTTON_STYLE_INPUT, "CancelButtonStyle.INPUT" },
};

const std::vector<ArkCopyOptionsTest> COPY_OPTION_TEST_PLAN = {
    { Ark_CopyOptions::ARK_COPY_OPTIONS_NONE, "CopyOptions.None" },
    { Ark_CopyOptions::ARK_COPY_OPTIONS_IN_APP, "CopyOptions.InApp" },
    { static_cast<Ark_CopyOptions>(4), "CopyOptions.Local" },
    { Ark_CopyOptions::ARK_COPY_OPTIONS_LOCAL_DEVICE, "CopyOptions.Local" },
    { Ark_CopyOptions::ARK_COPY_OPTIONS_CROSS_DEVICE, "CopyOptions.Distributed" },
};

const std::vector<ArkFontStyleTest> FONT_STYLE_TEST_PLAN = {
    { ArkValue<Opt_FontStyle>(Ark_FontStyle::ARK_FONT_STYLE_NORMAL), "FontStyle.Normal" },
    { ArkValue<Opt_FontStyle>(Ark_FontStyle::ARK_FONT_STYLE_ITALIC), "FontStyle.Italic" },
    { ArkValue<Opt_FontStyle>(static_cast<Ark_FontStyle>(2)), "FontStyle.Normal" },
};

// Font.fontWeight apply only FontWeight enum values
const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN = {
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_LIGHTER),
        "FontWeight.Lighter" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_NORMAL),
        "FontWeight.Normal" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_REGULAR),
        "FontWeight.Regular" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_MEDIUM),
        "FontWeight.Medium" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_BOLD),
        "FontWeight.Bold" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_BOLDER),
        "FontWeight.Bolder" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(100)), "100" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(200)), "200" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(300)), "300" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(400)), "400" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(500)), "500" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(600)), "600" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(700)), "700" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(800)), "800" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(900)), "900" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(ArkValue<Ark_Number>(1000)), "FontWeight.Normal" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("lighter")), "FontWeight.Lighter" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("normal")), "FontWeight.Normal" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("regular")), "FontWeight.Regular" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("medium")), "FontWeight.Medium" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("bold")), "FontWeight.Bold" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("bolder")), "FontWeight.Bolder" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("100")), "100" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("200")), "200" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("300")), "300" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("400")), "400" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("500")), "500" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("600")), "600" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("700")), "700" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("800")), "800" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("900")), "900" },
    { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(ArkValue<Ark_String>("1000")), "FontWeight.Normal" },
};

const std::vector<TextDeleteDirection> DELETE_DIRECTION_TEST_PLAN = {
    TextDeleteDirection::FORWARD,
    TextDeleteDirection::BACKWARD,
};

const std::vector<OneUnionNumStrResStep> UNION_NUM_STR_RES_TEST_PLAN = {
    { ArkUnion<Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(123)), "123.00vp" },
    { ArkUnion<Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(-123)), "0.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("5.6vp")), "5.60vp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("-5.6vp")), "0.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("45px")), "45.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("-45px")), "0.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(1.23f)), "1.23vp" },
    { ArkUnion<Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(-1.23f)), "0.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("45fp")), "45.00fp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("10%")), "0.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("45dp")), "45.00fp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("-10%")), "0.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("undefVal")), "0.00fp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("45.3fp")), "45.30fp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("")), "0.00fp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("qw111vp")), "0.00vp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("qw111")), "0.00fp" },
};

const std::vector<OneUnionNumStrResStep> UNION_NUM_STR_RES_TEST_PLAN_WITH_PERCENT = {
    { ArkUnion<Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(123)), "123.00vp" },
    { ArkUnion<Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(-123)), "0.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("5.6vp")), "5.60vp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("-5.6vp")), "0.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("45px")), "45.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("-45px")), "0.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(1.23f)), "1.23vp" },
    { ArkUnion<Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(-1.23f)), "0.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("45fp")), "45.00fp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("10%")), "10.00%" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("45dp")), "45.00fp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("-10%")), "0.00px" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("undefVal")), "0.00fp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("45.3fp")), "45.30fp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("")), "0.00fp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("qw111vp")), "0.00vp" },
    { ArkUnion<Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("qw111")), "0.00fp" },
};

const std::vector<DecorationTypeTest> TEXT_DECORATION_TYPE_TEST_PLAN = {
    { Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE, "TextDecorationType.None" },
    { Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_UNDERLINE, "TextDecorationType.Underline" },
    { Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_OVERLINE, "TextDecorationType.Overline" },
    { Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_LINE_THROUGH, "TextDecorationType.LineThrough" },
    { static_cast<Ark_TextDecorationType>(-100), "TextDecorationType.None" },
    { static_cast<Ark_TextDecorationType>(3), "TextDecorationType.LineThrough" },
    { static_cast<Ark_TextDecorationType>(100), "TextDecorationType.None" },
};

const std::vector<DecorationStyleTest> TEXT_DECORATION_STYLE_TEST_PLAN = {
    { Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_SOLID, "TextDecorationStyle.SOLID" },
    { Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DOUBLE, "TextDecorationStyle.DOUBLE" },
    { Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DOTTED, "TextDecorationStyle.DOTTED" },
    { Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DASHED, "TextDecorationStyle.DASHED" },
    { Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_WAVY, "TextDecorationStyle.WAVY" },
    { static_cast<Ark_TextDecorationStyle>(-100), "TextDecorationStyle.SOLID" },
    { static_cast<Ark_TextDecorationStyle>(3), "TextDecorationStyle.DASHED" },
    { static_cast<Ark_TextDecorationStyle>(100), "TextDecorationStyle.SOLID" },
};

const std::vector<ArkSearchTypeTest> SEARCH_TYPE_TEST_PLAN = {
    { Ark_SearchType::ARK_SEARCH_TYPE_NORMAL, "SearchType.NORMAL" },
    { Ark_SearchType::ARK_SEARCH_TYPE_EMAIL, "SearchType.EMAIL" },
    { Ark_SearchType::ARK_SEARCH_TYPE_URL, "SearchType.NORMAL" },
    { Ark_SearchType::ARK_SEARCH_TYPE_NUMBER, "SearchType.NUMBER" },
    { Ark_SearchType::ARK_SEARCH_TYPE_PHONE_NUMBER, "SearchType.PHONE_NUMBER" },
    // Work incorrect: should be NUMBER_DECIMAL, but in pattern return NORMAL
    { Ark_SearchType::ARK_SEARCH_TYPE_NUMBER_DECIMAL, "SearchType.NORMAL" },
    { static_cast<Ark_SearchType>(-100), "SearchType.NORMAL" },
    { static_cast<Ark_SearchType>(3), "SearchType.PHONE_NUMBER" },
    { static_cast<Ark_SearchType>(100), "SearchType.NORMAL" },
};

const std::vector<TextAlignTest> TEXT_ALIGN_TEST_PLAN = {
    { Ark_TextAlign::ARK_TEXT_ALIGN_CENTER, "TextAlign.Center" },
    { Ark_TextAlign::ARK_TEXT_ALIGN_START, "TextAlign.Start" },
    { Ark_TextAlign::ARK_TEXT_ALIGN_END, "TextAlign.End" },
    { Ark_TextAlign::ARK_TEXT_ALIGN_JUSTIFY, "TextAlign.Justify" },
    { static_cast<Ark_TextAlign>(-100), "TextAlign.Start" },
    { static_cast<Ark_TextAlign>(3), "TextAlign.Justify" },
    { static_cast<Ark_TextAlign>(100), "TextAlign.Start" },
};

const std::vector<FontFeatureTest> FONT_FEATURE_TEST_PLAN = {
    {ArkValue<Ark_String>("\"ss01\" on"), "\"ss01\" 1"},
    {ArkValue<Ark_String>("\"ss01\" off"), "\"ss01\" 0"},
    {ArkValue<Ark_String>("\"ss01\" 1"), "\"ss01\" 1"},
    {ArkValue<Ark_String>("\"ss01\" 0"), "\"ss01\" 0"},
    {ArkValue<Ark_String>("ss01 1"), EMPTY_TEXT},
    {ArkValue<Ark_String>("\"ss01\" on, \"ss02\" on"), "\"ss01\" 1,\"ss02\" 1"},
    {ArkValue<Ark_String>("\"ss01\" on, \"ss02\" off"), "\"ss01\" 1,\"ss02\" 0"},
    {ArkValue<Ark_String>("\"ss01\" on, ss02 off"), "\"ss01\" 1"},
    {ArkValue<Ark_String>("ss01 on, ss02 off"), EMPTY_TEXT},
    {ArkValue<Ark_String>("\"ss01\" on"), "\"ss01\" 1"},
    {ArkValue<Ark_String>("\"incorrect\" on"), EMPTY_TEXT},
    {ArkValue<Ark_String>("\"ss01\" on"), "\"ss01\" 1"},
    {ArkValue<Ark_String>("invalid"), EMPTY_TEXT},
};

const std::vector<EnterKeyTypeTest> ENTER_KEY_TYPE_TEST_PLAN = {
    { Ark_EnterKeyType::ARK_ENTER_KEY_TYPE_NEXT, "EnterKeyType.Next" },
    { Ark_EnterKeyType::ARK_ENTER_KEY_TYPE_DONE, "EnterKeyType.Done" },
    { Ark_EnterKeyType::ARK_ENTER_KEY_TYPE_PREVIOUS, "EnterKeyType.PREVIOUS" },
    { Ark_EnterKeyType::ARK_ENTER_KEY_TYPE_NEW_LINE, "EnterKeyType.NEW_LINE" },
    { Ark_EnterKeyType::ARK_ENTER_KEY_TYPE_SEND, "EnterKeyType.Send" },
    { Ark_EnterKeyType::ARK_ENTER_KEY_TYPE_GO, "EnterKeyType.Go" },
    { Ark_EnterKeyType::ARK_ENTER_KEY_TYPE_SEARCH, "EnterKeyType.Search" },
    { static_cast<Ark_EnterKeyType>(-100), "EnterKeyType.Search" },
    { static_cast<Ark_EnterKeyType>(3), "EnterKeyType.Search" },
    { static_cast<Ark_EnterKeyType>(100), "EnterKeyType.Search" },
};

// events
bool g_isEditChangeTest(true);
std::string g_EventTestString("");
std::string g_EventErrorTestString("");
int32_t g_EventTestOffset(0);
int32_t g_startValue(0);
int32_t g_endValue(0);
float g_scrollX(0);
float g_scrollY(0);
TextDeleteDirection g_deleteDirection(TextDeleteDirection::FORWARD);

GENERATED_ArkUISearchEventsReceiver recv {
    .onEditChange = [](Ark_Int32 nodeId, const Ark_Boolean isEditChange) { g_isEditChangeTest = isEditChange; },
    .onSubmit =
        [](Ark_Int32 nodeId, Ark_String value) {
            g_EventTestString = Convert<std::string>(value);
        },
    .onChange =
        [](Ark_Int32 nodeId, const Ark_String value, const Opt_PreviewText previewText) {
            g_EventTestOffset = PREVIEW_TEXT.offset;
            g_EventTestString.append(CHECK_TEXT).append(PREVIEW_TEXT.value);
        },
    .onTextSelectionChange =
        [](Ark_Int32 nodeId, Ark_Number selectionStart, Ark_Number selectionEnd) {
            g_startValue = Convert<int32_t>(selectionStart);
            g_endValue = Convert<int32_t>(selectionEnd);
        },
    .onContentScroll =
        [](Ark_Int32 nodeId, Ark_Number totalOffsetX, Ark_Number totalOffsetY) {
            g_scrollX = Convert<float>(totalOffsetX);
            g_scrollY = Convert<float>(totalOffsetY);
        },
    .onCopy =
        [](Ark_Int32 nodeId, Ark_String value) {
            auto textString = Convert<std::string>(value);
            g_EventTestString = textString;
        },
    .onCut =
        [](Ark_Int32 nodeId, Ark_String value) {
            g_EventTestString = Convert<std::string>(value);
            ;
        },
    .onWillInsert =
        [](Ark_Int32 nodeId, const Ark_InsertValue data) {
            g_EventTestString = Convert<std::string>(data.insertValue);
            g_EventTestOffset = Convert<int32_t>(data.insertOffset);
        },
    .onDidInsert =
        [](Ark_Int32 nodeId, const Ark_InsertValue data) {
            g_EventTestString = Convert<std::string>(data.insertValue);
            g_EventTestOffset = Convert<int32_t>(data.insertOffset);
        },
    .onWillDelete =
        [](Ark_Int32 nodeId, const Ark_DeleteValue data) {
            g_EventTestString = Convert<std::string>(data.deleteValue);
            g_EventTestOffset = Convert<int32_t>(data.deleteOffset);
            auto willDeleteDirection = OptConvert<TextDeleteDirection>(data.direction);
            if (willDeleteDirection) {
                g_deleteDirection = willDeleteDirection.value();
            }
        },
    .onDidDelete =
        [](Ark_Int32 nodeId, const Ark_DeleteValue data) {
            g_EventTestString = Convert<std::string>(data.deleteValue);
            g_EventTestOffset = Convert<int32_t>(data.deleteOffset);
            auto didDeleteDirection = OptConvert<TextDeleteDirection>(data.direction);
            if (didDeleteDirection) {
                g_deleteDirection = didDeleteDirection.value();
            }
        },
    .inputFilter =
        [](Ark_Int32 nodeId, const Ark_String data) {
            g_EventErrorTestString = Convert<std::string>(data);
            g_EventTestString = g_EventErrorTestString;
        }
};

const GENERATED_ArkUISearchEventsReceiver* getSearchEventsReceiverTest()
{
    return &recv;
};
const GENERATED_ArkUIEventsAPI* GetArkUiEventsAPITest()
{
    static const GENERATED_ArkUIEventsAPI eventsImpl = { .getSearchEventsReceiver = getSearchEventsReceiverTest };
    return &eventsImpl;
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

        fullAPI_->setArkUIEventsAPI(GetArkUiEventsAPITest());
    }
};

/**
 * @tc.name: setCancelButtonTestDefault
 * @tc.desc: Check the default values of cancelButton
 *
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setCancelButtonTestDefault, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCancelButton, nullptr);
    // default
    auto fullJsonDefault = GetJsonValue(node_);
    auto defaultCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJsonDefault, CANCEL_BUTTON_ATTR);
    auto defaultButtonIconStyleAttr = defaultCancelButtonAttrs->GetString(CANCEL_BUTTON_STYLE_ATTR);
    auto defaultCancelButtonIconAttrs = defaultCancelButtonAttrs->GetValue(CANCEL_BUTTON_ICON_ATTR);
    auto defaultCancelButtonIconSrc = defaultCancelButtonIconAttrs->GetString(CANCEL_BUTTON_ICON_SRC_ATTR);
    auto defaultCancelButtonIconColor = defaultCancelButtonIconAttrs->GetString(CANCEL_BUTTON_ICON_COLOR_ATTR);
    auto defaultCancelButtonIconSize = defaultCancelButtonIconAttrs->GetString(CANCEL_BUTTON_ICON_SIZE_ATTR);
    EXPECT_EQ(defaultButtonIconStyleAttr, BUTTON_STYLE_INPUT);
    EXPECT_EQ(defaultCancelButtonIconSrc, EMPTY_TEXT);
    EXPECT_EQ(defaultCancelButtonIconColor, CHECK_DEFAULT_BLACK_COLOR);
    EXPECT_EQ(defaultCancelButtonIconSize, CHECK_DEFAULT_PX);
}

/**
 * @tc.name: setCancelButtonTestIconSize
 * @tc.desc: Check set size functionality of setCancelButton
 *
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setCancelButtonTestIconSize, TestSize.Level1)
{
    Type_SearchAttribute_cancelButton_Arg0 attrs;
    attrs.selector = 0;
    for (auto testSize : ICON_SIZE_TEST_PLAN) {
        attrs.value0.icon.value.size = testSize.first;
        modifier_->setCancelButton(node_, &attrs);
        auto fullJson = GetJsonValue(node_);
        auto customCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, CANCEL_BUTTON_ATTR);
        auto customCancelButtonIconAttrs = customCancelButtonAttrs->GetValue(CANCEL_BUTTON_ICON_ATTR);
        auto customCancelButtonIconSize = customCancelButtonIconAttrs->GetString(CANCEL_BUTTON_ICON_SIZE_ATTR);
        EXPECT_EQ(customCancelButtonIconSize, testSize.second);
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
    Type_SearchAttribute_cancelButton_Arg0 attrs;
    attrs.selector = 0;
    for (auto testStyleButton : BUTTON_STYLE_TEST_PLAN) {
        attrs.value0.style = ArkValue<Opt_CancelButtonStyle>(testStyleButton.first);
        modifier_->setCancelButton(node_, &attrs);
        auto fullJson = GetJsonValue(node_);
        auto customCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, CANCEL_BUTTON_ATTR);
        auto customButtonIconStyleAttr = customCancelButtonAttrs->GetString(CANCEL_BUTTON_STYLE_ATTR);
        EXPECT_EQ(customButtonIconStyleAttr, testStyleButton.second);
    }
}

/**
 * @tc.name: setCopyOptionTest
 * @tc.desc: Check the functionality of setCopyOption
 * In the documentation default value is Local, but in return value is Distributed
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setCopyOptionTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCopyOption, nullptr);

    auto checkVal = GetStringAttribute(node_, COPY_OPTION_ATTR);
    EXPECT_EQ(checkVal, COPY_OPTION_TEST_PLAN.at(3).second);
    for (const auto& [value, expectVal] : COPY_OPTION_TEST_PLAN) {
        modifier_->setCopyOption(node_, value);
        checkVal = GetStringAttribute(node_, COPY_OPTION_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSearchIconTest
 * @tc.desc: Check the functionality of setSearchIcon
 *
 * This test disabled because set icon src and icon color doesn't correspond in JSON after set it in SearchPattern
 *
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, DISABLED_setSearchIconTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSearchIcon, nullptr);
    // default
    auto fullJson = GetJsonValue(node_);
    auto defaultSearchIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, SEARCH_ICON_ATTR);
    auto defaultSearchIconSrc = defaultSearchIconAttrs->GetString(SEARCH_ICON_SRC_ATTR);
    auto defaultSearchIconColor = defaultSearchIconAttrs->GetString(SEARCH_ICON_COLOR_ATTR);
    auto defaultSearchIconSize = defaultSearchIconAttrs->GetString(SEARCH_ICON_SIZE_ATTR);
    EXPECT_EQ(defaultSearchIconSrc, EMPTY_TEXT);
    EXPECT_EQ(defaultSearchIconColor, CHECK_DEFAULT_BLACK_COLOR);
    EXPECT_EQ(defaultSearchIconSize, CHECK_DEFAULT_PX);
    // custom
    std::vector<SearchIconTest> testSearchIcon;
    for (auto testLength : TEST_PLAN_OPT_LENGTH_PX) {
        for (auto ColorTest : COLOR_TEST_PLAN) {
            for (auto testSrc : RESOURCE_TEST_PLAN) {
                Type_SearchAttribute_searchIcon_Arg0 attrs = {
                    .selector = 0,
                    .value0 = {
                        .color = ColorTest.first,
                        .size = testLength.first,
                        .src = testSrc.first
                    }
                };
                TripleCheckValues checkIconValues = {
                    testSrc.second,
                    ColorTest.second,
                    testLength.second
                };
                SearchIconTest searchIconTest = {
                    attrs, checkIconValues
                };
                testSearchIcon.push_back(searchIconTest);
            }
        }
    }

    for (auto iconAttrs : testSearchIcon) {
        modifier_->setSearchIcon(node_, &iconAttrs.first);
        fullJson = GetJsonValue(node_);
        auto customSearchIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, SEARCH_ICON_ATTR);
        auto customSearchIconSrc = customSearchIconAttrs->GetString(SEARCH_ICON_SRC_ATTR);
        auto customSearchIconColor = customSearchIconAttrs->GetString(SEARCH_ICON_COLOR_ATTR);
        auto customSearchIconSize = customSearchIconAttrs->GetString(SEARCH_ICON_SIZE_ATTR);
        std::string checkSrc;
        std::string checkColor;
        std::string checkSize;
        std::tie(checkSrc, checkColor, checkSize) = iconAttrs.second;
        EXPECT_EQ(customSearchIconSrc, checkSrc);
        EXPECT_EQ(customSearchIconColor, checkColor);
        EXPECT_EQ(customSearchIconSize, checkSize);
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
    modifier_->setFontColor(node_, &COLOR_COLOR);
    auto fontColorColor = GetStringAttribute(node_, FONT_COLOR_ATTR);
    EXPECT_EQ(fontColorColor, CHECK_COLOR_COLOR);
    //int
    modifier_->setFontColor(node_, &COLOR_INT);
    auto fontColorInt = GetStringAttribute(node_, FONT_COLOR_ATTR);
    EXPECT_EQ(fontColorInt, CUSTOM_COLOR_STRING);
    // float
    modifier_->setFontColor(node_, &COLOR_FLOAT);
    auto fontColorColorFloat = GetStringAttribute(node_, FONT_COLOR_ATTR);
    EXPECT_EQ(fontColorColorFloat, CHECK_FLOAT_COLOR);
    // string
    modifier_->setFontColor(node_, &COLOR_STRING);
    auto fontColorColorString = GetStringAttribute(node_, FONT_COLOR_ATTR);
    EXPECT_EQ(fontColorColorString, CUSTOM_COLOR_STRING);
}

/**
 * @tc.name: setSearchButtonTest
 * @tc.desc: Check the functionality of setSearchButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setSearchButtonTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSearchButton, nullptr);
    // default
    auto fullJson = GetJsonValue(node_);
    auto defaultCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUTTON_OPTIONS_ATTR);
    auto defaultCaretColor = defaultCaretStyle->GetString(BUTTON_OPTIONS_COLOR_ATTR);
    auto defaultCaretWidth = defaultCaretStyle->GetString(BUTTON_OPTIONS_SIZE_ATTR);
    EXPECT_EQ(defaultCaretColor, CHECK_DEFAULT_BLACK_COLOR);
    EXPECT_EQ(defaultCaretWidth, CHECK_DEFAULT_VP);
    // custom
    std::vector<TestSearchButtonOption> testSearchButton;
    for (auto testLength : OPT_LENGTH_TEST_PLAN) {
        for (auto ColorTest : COLOR_TEST_PLAN) {
            Ark_SearchButtonOptions buttonOptions = { .fontColor = ColorTest.first, .fontSize = testLength.first };
            Opt_SearchButtonOptions options = { .tag = ARK_TAG_OBJECT, .value = buttonOptions };
            CheckSearchButtonOptions checkSearchButtonOptions = { ColorTest.second, testLength.second };
            TestSearchButtonOption testSearchButtonOption = { options, checkSearchButtonOptions };
            testSearchButton.push_back(testSearchButtonOption);
        }
    }
    auto checkText = ArkValue<Ark_String>(CHECK_TEXT);
    for (auto buttonOptions : testSearchButton) {
        modifier_->setSearchButton(node_, &checkText, &buttonOptions.first);
        auto fullJson = GetJsonValue(node_);
        auto customButtonOptions = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUTTON_OPTIONS_ATTR);
        auto searchButtonColor = customButtonOptions->GetString(BUTTON_OPTIONS_COLOR_ATTR);
        auto searchButtonSize = customButtonOptions->GetString(BUTTON_OPTIONS_SIZE_ATTR);
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
    // custom
    for (auto length : INDENT_LENGTH_TEST_PLAN) {
        modifier_->setTextIndent(node_, &length.first);
        auto indentValue = GetStringAttribute(node_, TEXT_INDENT_ATTR);
        EXPECT_EQ(indentValue, length.second);
    }
}

/**
 * @tc.name: setInputFilterTest
 * @tc.desc: Check the functionality of setInputFilter
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setInputFilterTest, TestSize.Level1)
{
    g_EventTestString = "";
    g_EventErrorTestString = "";
    ASSERT_NE(modifier_->setInputFilter, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Opt_Callback func = {};
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();

    auto sendString = ArkValue<Ark_String>(ERROR_TEXT);
    auto sendResource = ArkUnion<Ark_ResourceStr, Ark_String>(sendString);
    modifier_->setInputFilter(node_, &sendResource, &func);
    textFieldEventHub->FireOnInputFilterError(ERROR_TEXT);
    auto filterValue = GetStringAttribute(node_, INPUT_FILTER_ATTR);
    EXPECT_EQ(filterValue, ERROR_TEXT);
    EXPECT_EQ(g_EventTestString, ERROR_TEXT);
    EXPECT_EQ(g_EventErrorTestString, ERROR_TEXT);
}

/**
 * @tc.name: setEnableKeyboardOnFocusTest
 * @tc.desc: Check the functionality of setEnableKeyboardOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setEnableKeyboardOnFocusTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnableKeyboardOnFocus, nullptr);

    auto fullJson = GetJsonValue(node_);
    auto checkVal = GetAttrValue<bool>(fullJson, ENABLE_KEYBOARD_ON_FOCUS);
    EXPECT_EQ(checkVal, false);

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        modifier_->setEnableKeyboardOnFocus(node_, value);
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
    modifier_->setPlaceholderColor(node_, &COLOR_COLOR);
    auto placeholderColorColor = GetStringAttribute(node_, PLACEHOLDER_COLOR_ATTR);
    EXPECT_EQ(placeholderColorColor, CHECK_COLOR_COLOR);
    //int
    modifier_->setPlaceholderColor(node_, &COLOR_INT);
    auto placeholderColorInt = GetStringAttribute(node_, PLACEHOLDER_COLOR_ATTR);
    EXPECT_EQ(placeholderColorInt, CUSTOM_COLOR_STRING);
    // float
    modifier_->setPlaceholderColor(node_, &COLOR_FLOAT);
    auto placeholderColorFloat = GetStringAttribute(node_, PLACEHOLDER_COLOR_ATTR);
    EXPECT_EQ(placeholderColorFloat, CHECK_FLOAT_COLOR);
    // string
    modifier_->setPlaceholderColor(node_, &COLOR_STRING);
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
    auto defaultCaretColor = defaultCaretStyle->GetString(CARET_STYLE_COLOR_ATTR);
    auto defaultCaretWidth = defaultCaretStyle->GetString(CARET_STYLE_WIDTH_ATTR);
    EXPECT_EQ(defaultCaretColor, CHECK_DEFAULT_BLACK_COLOR);
    EXPECT_EQ(defaultCaretWidth, CHECK_DEFAULT_PX);

    std::vector<TestCaretStyle> testPlanCaretStyle;
    for (auto testLength : OPT_LENGTH_TEST_PLAN) {
        for (auto ColorTest : COLOR_TEST_PLAN) {
            Ark_CaretStyle arkCaretStyle = { .color = ColorTest.first, .width = testLength.first };
            CheckCaretValue caretValue = { ColorTest.second, testLength.second };
            TestCaretStyle testCaretStyle = { arkCaretStyle, caretValue };
            testPlanCaretStyle.push_back(testCaretStyle);
        }
    }

    for (auto caretStyle : testPlanCaretStyle) {
        modifier_->setCaretStyle(node_, &caretStyle.first);
        auto value = GetStringAttribute(node_, CARET_STYLE_ATTR);
        auto fullJson = GetJsonValue(node_);
        auto customCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, CARET_STYLE_ATTR);
        auto caretColor = customCaretStyle->GetString(CARET_STYLE_COLOR_ATTR);
        auto caretWidth = customCaretStyle->GetString(CARET_STYLE_WIDTH_ATTR);
        EXPECT_EQ(caretColor, caretStyle.second.first);
        EXPECT_EQ(caretWidth, caretStyle.second.second);
    }
}

/**
 * @tc.name: selectedBackgroundColorTest
 * @tc.desc: Check the functionality of selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, selectedBackgroundColorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedBackgroundColor, nullptr);
    // default
    auto selectedBackgroundColor = GetStringAttribute(node_, SELECTED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(selectedBackgroundColor, CHECK_DEFAULT_BLACK_COLOR);
    // color
    modifier_->setSelectedBackgroundColor(node_, &COLOR_COLOR);
    auto selectedBackgroundColorColor = GetStringAttribute(node_, SELECTED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(selectedBackgroundColorColor, CHECK_COLOR_COLOR);
    //int
    modifier_->setSelectedBackgroundColor(node_, &COLOR_INT);
    auto selectedBackgroundColorInt = GetStringAttribute(node_, SELECTED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(selectedBackgroundColorInt, CUSTOM_COLOR_STRING);
    // float
    modifier_->setSelectedBackgroundColor(node_, &COLOR_FLOAT);
    auto selectedBackgroundColorFloat = GetStringAttribute(node_, SELECTED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(selectedBackgroundColorFloat, CHECK_FLOAT_COLOR);
    // string
    modifier_->setSelectedBackgroundColor(node_, &COLOR_STRING);
    auto selectedBackgroundColorString = GetStringAttribute(node_, SELECTED_BACKGROUND_COLOR_ATTR);
    EXPECT_EQ(selectedBackgroundColorString, CUSTOM_COLOR_STRING);
}

/**
 * @tc.name: setOnTextSelectionChangeTest
 * @tc.desc: Check the functionality of setOnTextSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setOnTextSelectionChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnTextSelectionChange, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();

    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        modifier_->setOnTextSelectionChange(node_, func);
        textFieldEventHub->FireOnSelectionChange(value, value);
        EXPECT_EQ(g_startValue, expectVal);
        EXPECT_EQ(g_endValue, expectVal);
    }
}

/**
 * @tc.name: setOnCopyTest
 * @tc.desc: Test Seacrh setOnCopy event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setOnCopyTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnCopy, nullptr);
    g_EventTestString = EMPTY_TEXT;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    textFieldEventHub->FireOnCopy(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    Ark_Function func = {};
    modifier_->setOnCopy(node_, func);
    textFieldEventHub->FireOnCopy(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, CHECK_TEXT);
}

/**
 * @tc.name: setOnCutTest
 * @tc.desc: Test Seacrh setOnCut event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setOnCutTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnCut, nullptr);
    g_EventTestString = EMPTY_TEXT;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    textFieldEventHub->FireOnCut(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    Ark_Function func = {};
    modifier_->setOnCut(node_, func);
    textFieldEventHub->FireOnCut(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, CHECK_TEXT);
}

/**
 * @tc.name: setOnContentScrollTest
 * @tc.desc: Check the functionality of setOnContentScroll
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setOnContentScrollTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnContentScroll, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();

    for (const auto& [value, expectVal] : FLOAT_NUMBER_TEST_PLAN) {
        modifier_->setOnContentScroll(node_, func);
        textFieldEventHub->FireOnScrollChangeEvent(value, value);
        EXPECT_EQ(g_scrollX, expectVal);
        EXPECT_EQ(g_scrollY, expectVal);
    }
}

/**
 * @tc.name: setOnEditChangeTest
 * @tc.desc: Test Seacrh setOnEditChange event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setOnEditChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};
    modifier_->setOnEditChange(node_, func);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    EXPECT_EQ(g_isEditChangeTest, true);
    ASSERT_NE(textFieldEventHub, nullptr);
    textFieldEventHub->FireOnEditChanged(false);
    EXPECT_EQ(g_isEditChangeTest, false);
    textFieldEventHub->FireOnEditChanged(true);
    EXPECT_EQ(g_isEditChangeTest, true);
}
/**
 * @tc.name: setOnSubmitTest
 * @tc.desc: Test Seacrh setOnSubmit event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setOnSubmitTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnSubmit, nullptr);
    g_EventTestString = EMPTY_TEXT;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};
    modifier_->setOnSubmit(node_, func);
    auto searchEventHub = frameNode->GetEventHub<SearchEventHub>();
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    ASSERT_NE(searchEventHub, nullptr);
    searchEventHub->UpdateSubmitEvent(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, CHECK_TEXT);
    searchEventHub->UpdateSubmitEvent(EMPTY_TEXT);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
}

/**
 * @tc.name: setOnChangeTest
 * @tc.desc: Test Seacrh setOnChange event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setOnChangeTest, TestSize.Level1)
{
    g_EventTestString = "";
    g_EventTestOffset = 0;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    Ark_Function func = {};
    modifier_->setOnChange(node_, func);
    textFieldEventHub->FireOnChange(CHECK_TEXT, PREVIEW_TEXT);
    std::string checkString = CHECK_TEXT;
    checkString.append(PREVIEW_TEXT.value);
    EXPECT_EQ(g_EventTestString, checkString);
    EXPECT_EQ(g_EventTestOffset, PREVIEW_TEXT.offset);
}

/**
 * @tc.name: setSelectionMenuHidden
 * @tc.desc: Test Radio setSelectionMenuHidden.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setSelectionMenuHidden, TestSize.Level1)
{
    auto fullJsonDefault = GetJsonValue(node_);
    auto checkVal = GetAttrValue<bool>(fullJsonDefault, SELECTION_MENU_HIDDEN_ATTR);
    EXPECT_EQ(checkVal, false);
    modifier_->setSelectionMenuHidden(node_, true);
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
    ASSERT_NE(modifier_->setMaxLength, nullptr);
    auto checkVal = GetStringAttribute(node_, MAX_LENGTH_ATTR);
    EXPECT_EQ(checkVal, "INF");
    for (const auto &[value, expectVal]: ARK_NUMBER_TEST_PLAN) {
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
HWTEST_F(SearchModifierTest, setMinFontSizeTest, TestSize.Level1)
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
HWTEST_F(SearchModifierTest, setMaxFontSizeTest, TestSize.Level1)
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
HWTEST_F(SearchModifierTest, setLetterSpacingTest, TestSize.Level1)
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
        modifier_->setEnablePreviewText(node_, value);
        auto fullJson = GetJsonValue(node_);
        checkVal = GetAttrValue<bool>(fullJson, ENABLE_PREVIEW_TEXT);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setOnWillInsertTest
 * @tc.desc: Test Seacrh setOnWillInsert event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setOnWillInsertTest, TestSize.Level1)
{
    g_EventTestString = "";
    g_EventTestOffset = 0;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    InsertValueInfo checkValueDefault;
    textFieldEventHub->FireOnWillInsertValueEvent(checkValueDefault);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    Ark_Function func = {};
    modifier_->setOnWillInsert(node_, func);
    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        InsertValueInfo checkValue = { .insertOffset = value, .insertValue = CHECK_TEXT };
        textFieldEventHub->FireOnWillInsertValueEvent(checkValue);
        EXPECT_EQ(g_EventTestString, CHECK_TEXT);
        EXPECT_EQ(g_EventTestOffset, expectVal);
    }
}

/**
 * @tc.name: setOnDidInsertTest
 * @tc.desc: Test Seacrh setOnDidInsert event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setOnDidInsertTest, TestSize.Level1)
{
    g_EventTestString = "";
    g_EventTestOffset = 0;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    InsertValueInfo checkValueDefault;
    textFieldEventHub->FireOnDidInsertValueEvent(checkValueDefault);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    Ark_Function func = {};
    modifier_->setOnDidInsert(node_, func);
    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        InsertValueInfo checkValue = { .insertOffset = value, .insertValue = CHECK_TEXT };
        textFieldEventHub->FireOnDidInsertValueEvent(checkValue);
        EXPECT_EQ(g_EventTestString, CHECK_TEXT);
        EXPECT_EQ(g_EventTestOffset, expectVal);
    }
}

/**
 * @tc.name: setOnWillDeleteTest
 * @tc.desc: Test Seacrh setOnWillDelete event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setOnWillDeleteTest, TestSize.Level1)
{
    g_EventTestString = "";
    g_EventTestOffset = 0;
    g_deleteDirection = TextDeleteDirection::FORWARD;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    DeleteValueInfo checkValueDefault;
    textFieldEventHub->FireOnWillDeleteEvent(checkValueDefault);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    EXPECT_EQ(g_deleteDirection, TextDeleteDirection::FORWARD);
    Ark_Function func = {};
    modifier_->setOnWillDelete(node_, func);
    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        for (const auto& deleteDirection : DELETE_DIRECTION_TEST_PLAN) {
            DeleteValueInfo checkValue = {
                .deleteOffset = value, .deleteValue = CHECK_TEXT, .direction = deleteDirection
            };
            textFieldEventHub->FireOnWillDeleteEvent(checkValue);
            EXPECT_EQ(g_EventTestString, CHECK_TEXT);
            EXPECT_EQ(g_EventTestOffset, expectVal);
            EXPECT_EQ(g_deleteDirection, deleteDirection);
        }
    }
}

/**
 * @tc.name: setOnDidDeleteTest
 * @tc.desc: Test Seacrh setOnDidlDelete event.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setOnDidDeleteTest, TestSize.Level1)
{
    g_EventTestString = "";
    g_EventTestOffset = 0;
    g_deleteDirection = TextDeleteDirection::FORWARD;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    DeleteValueInfo checkValueDefault;
    textFieldEventHub->FireOnDidDeleteValueEvent(checkValueDefault);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    EXPECT_EQ(g_deleteDirection, TextDeleteDirection::FORWARD);
    Ark_Function func = {};
    modifier_->setOnDidDelete(node_, func);
    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        for (const auto& deleteDirection : DELETE_DIRECTION_TEST_PLAN) {
            DeleteValueInfo checkValue = {
                .deleteOffset = value, .deleteValue = CHECK_TEXT, .direction = deleteDirection
            };
            textFieldEventHub->FireOnDidDeleteValueEvent(checkValue);
            EXPECT_EQ(g_EventTestString, CHECK_TEXT);
            EXPECT_EQ(g_EventTestOffset, expectVal);
            EXPECT_EQ(g_deleteDirection, deleteDirection);
        }
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
        auto checkSize = placeholderFont->GetString(PLACEHOLDER_FONT_SIZE);
        auto checkFamily = placeholderFont->GetString(PLACEHOLDER_FONT_FAMILY);
        auto checkWeight = placeholderFont->GetString(PLACEHOLDER_FONT_WEIGHT);
        if (checkWeight.empty()) {
            checkWeight = placeholderFont->GetString(PLACEHOLDER_FONT_WEIGHT_ENUM);
        }
        auto checkStyle = placeholderFont->GetString(PLACEHOLDER_FONT_STYLE);
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
        auto checkSize = placeholderFont->GetString(PLACEHOLDER_FONT_SIZE);
        auto checkFamily = placeholderFont->GetString(PLACEHOLDER_FONT_FAMILY);
        auto checkWeight = placeholderFont->GetString(PLACEHOLDER_FONT_WEIGHT);
        if (checkWeight.empty()) {
            checkWeight = placeholderFont->GetString(PLACEHOLDER_FONT_WEIGHT_ENUM);
        }
        auto checkStyle = placeholderFont->GetString(PLACEHOLDER_FONT_STYLE);
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
HWTEST_F(SearchModifierTest, DISABLED_setPlaceholderFontTestFamily, TestSize.Level1)
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
        auto checkSize = placeholderFont->GetString(PLACEHOLDER_FONT_SIZE);
        auto checkFamily = placeholderFont->GetString(PLACEHOLDER_FONT_FAMILY);
        auto checkWeight = placeholderFont->GetString(PLACEHOLDER_FONT_WEIGHT);
        if (checkWeight.empty()) {
            checkWeight = placeholderFont->GetString(PLACEHOLDER_FONT_WEIGHT_ENUM);
        }
        auto checkStyle = placeholderFont->GetString(PLACEHOLDER_FONT_STYLE);
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
HWTEST_F(SearchModifierTest, setPlaceholderFontTestSize, TestSize.Level1)
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
        auto checkSize = placeholderFont->GetString(PLACEHOLDER_FONT_SIZE);
        auto checkFamily = placeholderFont->GetString(PLACEHOLDER_FONT_FAMILY);
        auto checkWeight = placeholderFont->GetString(PLACEHOLDER_FONT_WEIGHT);
        if (checkWeight.empty()) {
            checkWeight = placeholderFont->GetString(PLACEHOLDER_FONT_WEIGHT_ENUM);
        }
        auto checkStyle = placeholderFont->GetString(PLACEHOLDER_FONT_STYLE);
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
        auto checkSize = textFont->GetString(TEXT_FONT_SIZE_ATTR);
        auto checkFamily = textFont->GetString(TEXT_FONT_FAMILY_ATTR);
        auto checkWeight = textFont->GetString(TEXT_FONT_WEIGHT_ATTR);
        auto checkStyle = textFont->GetString(TEXT_FONT_STYLE_ATTR);
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
        auto checkSize = textFont->GetString(TEXT_FONT_SIZE_ATTR);
        auto checkFamily = textFont->GetString(TEXT_FONT_FAMILY_ATTR);
        auto checkWeight = textFont->GetString(TEXT_FONT_WEIGHT_ATTR);
        auto checkStyle = textFont->GetString(TEXT_FONT_STYLE_ATTR);
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
HWTEST_F(SearchModifierTest, DISABLED_setTextFontTestFontFamily, TestSize.Level1)
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
        auto checkSize = textFont->GetString(TEXT_FONT_SIZE_ATTR);
        auto checkFamily = textFont->GetString(TEXT_FONT_FAMILY_ATTR);
        auto checkWeight = textFont->GetString(TEXT_FONT_WEIGHT_ATTR);
        auto checkStyle = textFont->GetString(TEXT_FONT_STYLE_ATTR);
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
HWTEST_F(SearchModifierTest, setTextFontTestFontSize, TestSize.Level1)
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
        auto checkSize = textFont->GetString(TEXT_FONT_SIZE_ATTR);
        auto checkFamily = textFont->GetString(TEXT_FONT_FAMILY_ATTR);
        auto checkWeight = textFont->GetString(TEXT_FONT_WEIGHT_ATTR);
        auto checkStyle = textFont->GetString(TEXT_FONT_STYLE_ATTR);
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
HWTEST_F(SearchModifierTest, setLineHeightTest, TestSize.Level1)
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
HWTEST_F(SearchModifierTest, setEnterKeyTypeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnterKeyType, nullptr);
    auto checkVal = GetStringAttribute(node_, ENTER_KEY_TYPE_ATTR);
    EXPECT_EQ(checkVal, "EnterKeyType.Search");

    for (const auto &[value, expectVal]: ENTER_KEY_TYPE_TEST_PLAN) {
        modifier_->setEnterKeyType(node_, value);
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
    ASSERT_NE(modifier_->setTextAlign, nullptr);

    auto checkVal = GetStringAttribute(node_, TEXT_ALIGN_ATTR);
    EXPECT_EQ(checkVal, "TextAlign.Start");
    for (const auto &[value, expectVal]: TEXT_ALIGN_TEST_PLAN) {
        modifier_->setTextAlign(node_, value);
        checkVal = GetStringAttribute(node_, TEXT_ALIGN_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setTypeTest
 * @tc.desc: Check the functionality of setType
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest, setTypeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setType, nullptr);
    auto checkVal = GetStringAttribute(node_, TYPE_ATTR);
    EXPECT_EQ(checkVal, "SearchType.NORMAL");
    for (const auto &[value, expectVal]: SEARCH_TYPE_TEST_PLAN) {
        modifier_->setType(node_, value);
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
    auto defaultType = defaultDecoration->GetString(DECORATION_TYPE_ATTR);
    auto defaultStyle = defaultDecoration->GetString(DECORATION_STYLE_ATTR);
    auto defaultColor = defaultDecoration->GetString(DECORATION_COLOR_ATTR);
    EXPECT_EQ(defaultType, "TextDecorationType.None");
    EXPECT_EQ(defaultStyle, "TextDecorationStyle.SOLID");
    EXPECT_EQ(defaultColor, CHECK_DEFAULT_BLACK_COLOR);

    for (const auto &[decorationType, expectDecorationType]: TEXT_DECORATION_TYPE_TEST_PLAN) {
        for (const auto &[decorationStyle, expectDecorationStyle]: TEXT_DECORATION_STYLE_TEST_PLAN) {
            for (const auto &[decorationColor, expectColor] : COLOR_TEST_PLAN) {
                Ark_TextDecorationOptions options = {
                    .color = decorationColor,
                    .type = decorationType,
                    .style = ArkValue<Opt_TextDecorationStyle>(decorationStyle)
                };
                modifier_->setDecoration(node_, &options);
                auto decorationJSON = GetStringAttribute(node_, DECORATION_ATTRS);
                auto decoration = JsonUtil::ParseJsonString(decorationJSON);
                auto type = decoration->GetString(DECORATION_TYPE_ATTR);
                auto style = decoration->GetString(DECORATION_STYLE_ATTR);
                auto color = decoration->GetString(DECORATION_COLOR_ATTR);
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
HWTEST_F(SearchModifierTest, setFontFeatureTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setFontFeature, nullptr);
    auto checkVal = GetStringAttribute(node_, FONT_FEATURE_ATTR);
    EXPECT_EQ(checkVal, EMPTY_TEXT);
    for (const auto &[value, expectVal]: FONT_FEATURE_TEST_PLAN) {
        modifier_->setFontFeature(node_, &value);
        checkVal = GetStringAttribute(node_, FONT_FEATURE_ATTR);
        EXPECT_EQ(checkVal, expectVal);
    }
}
} // namespace OHOS::Ace::NG
