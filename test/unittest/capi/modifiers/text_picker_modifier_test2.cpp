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
#include "core/components/picker/picker_theme.h"
#include "core/components/picker/picker_text_component.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace  {
// callback data
const int32_t CONTEXT_ID = 123;
const int32_t INVOKE_POS_0 = 0;
const int32_t INVOKE_POS_1 = 1;
const int32_t INVOKE_POS_2 = 2;

const auto ATTRIBUTE_DEFAULT_PICKER_ITEM_HEIGHT_NAME = "defaultPickerItemHeight";
const auto ATTRIBUTE_CAN_LOOP_NAME = "canLoop";
const auto ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME = "disappearTextStyle";
const auto ATTRIBUTE_TEXT_STYLE_NAME = "textStyle";
const auto ATTRIBUTE_SELECTED_TEXT_STYLE_NAME = "selectedTextStyle";
const auto ATTRIBUTE_FONT_NAME = "font";
const auto ATTRIBUTE_COLOR_NAME = "color";
const auto ATTRIBUTE_FONT_SIZE_NAME = "size";
const auto ATTRIBUTE_FONT_WEIGHT_NAME = "weight";
const auto ATTRIBUTE_FONT_STYLE_NAME = "style";
const auto ATTRIBUTE_FONT_FAMILY_NAME = "family";
const auto ATTRIBUTE_SELECTED_NAME = "selected";
const auto ATTRIBUTE_SELECTEDS_NAME = "selecteds";
const auto ATTRIBUTE_SELECTED_NAME_INDEX = "selectedIndex";
const auto ATTRIBUTE_DIVIDER_NAME = "divider";
const auto ATTRIBUTE_STROKE_WIDTH_NAME = "strokeWidth";
const auto ATTRIBUTE_START_MARGIN_NAME = "startMargin";
const auto ATTRIBUTE_END_MARGIN_NAME = "endMargin";
const auto ATTRIBUTE_GRADIENT_HEIGHT_NAME = "gradientHeight";

const auto RES_STR_1_ID = IntResourceId { 111, Converter::ResourceType::STRING };
const auto RES_STR_2_ID = IntResourceId { 222, Converter::ResourceType::STRING };
const auto RES_STR_3_ID = IntResourceId { 333, Converter::ResourceType::STRING };
const auto RES_PIC_1_ID = IntResourceId { 444, Converter::ResourceType::STRING };
const auto RES_PIC_2_ID = IntResourceId { 555, Converter::ResourceType::STRING };
const auto RES_PIC_3_ID = IntResourceId { 666, Converter::ResourceType::STRING };

// Expected values
static const std::string EXPECTED_TRUE("true");
static const std::string EXPECTED_FALSE("false");
const std::string COLOR_WHITE = "#FFFFFFFF";
const std::string COLOR_BLACK = "#FF000000";
const std::string COLOR_TRANSPARENT = "#00000000";

// Default values
const auto ATTRIBUTE_DEFAULT_PICKER_ITEM_HEIGHT_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_CAN_LOOP_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "14.00px";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = COLOR_BLACK;
const auto ATTRIBUTE_SELECTED_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_SELECTEDS_DEFAULT_VALUE = "[]";
const auto ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE = "[]";
const auto ATTRIBUTE_DIVIDER_STROKE_WIDTH_INITIAL_VALUE = "0.00px";
const auto ATTRIBUTE_DIVIDER_COLOR_INITIAL_VALUE = COLOR_WHITE;
const auto ATTRIBUTE_DIVIDER_MARGIN_INITIAL_VALUE = "0.00px";
const auto ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE = "1.00px";
const auto ATTRIBUTE_DIVIDER_COLOR_DEFAULT_VALUE = COLOR_BLACK;
const auto ATTRIBUTE_DIVIDER_MARGIN_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_GRADIENT_HEIGHT_DEFAULT_VALUE = "0.00px";

// Test plans
typedef std::pair<Ark_Union_Number_String, std::string> PickerItemHeightTestStep;
const std::vector<PickerItemHeightTestStep> PICKER_ITEM_HEIGHT_TEST_PLAN = {
    { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(1), "1.00vp" },
    { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(3.3f), "3.30vp" },
    { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(-3.3f), "-3.30vp" },
    { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("3.3px"), "3.30px" },
    { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("3.3vp"), "3.30vp" },
    { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("345vp"), "345.00vp" },
    { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("25%"), "25.00%" },
    { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-10px"), "-10.00px" }
};

const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const auto CHECK_AFLT32_POS = "1.23vp";

const auto RES_CONTENT_STR = "aa.bb.cc";
const auto RES_CONTENT = Converter::ArkValue<Ark_String>(RES_CONTENT_STR);
const auto RES_NAME = NamedResourceId{"res_name", Converter::ResourceType::STRING};
const Opt_Union_String_Resource OPT_UNION_RESOURCE_RESOURCE = CreateResourceUnion<Opt_Union_String_Resource>(RES_NAME);
const std::string CHECK_RESOURCE_STR(RES_CONTENT_STR);

typedef std::pair<Opt_Union_String_Resource, std::string> UnionStringResourceTestStep;
const std::vector<UnionStringResourceTestStep> UNION_RESOURCE_STRING_PLAN = {
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(RES_CONTENT), CHECK_RESOURCE_STR },
    { OPT_UNION_RESOURCE_RESOURCE, CHECK_RESOURCE_STR }
};

typedef std::pair<Opt_Length, std::string> OptLengthTestStep;
const std::vector<OptLengthTestStep> FONT_SIZE_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(AFLT32_POS), CHECK_AFLT32_POS },
    { Converter::ArkValue<Opt_Length>(AFLT32_NEG), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
};

typedef std::pair<Opt_FontStyle, std::string> ArkFontStyleTestStep;
const std::vector<ArkFontStyleTestStep> FONT_STYLE_TEST_PLAN = {
    { Converter::ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_NORMAL), "FontStyle.Normal" },
    { Converter::ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_ITALIC), "FontStyle.Italic" },
    { Converter::ArkValue<Opt_FontStyle>(static_cast<Ark_FontStyle>(-1)), "FontStyle.Normal" },
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

typedef std::tuple<Ark_ResourceColor, std::string> ColorTestStep;
const std::vector<ColorTestStep> COLOR_BLACK_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), COLOR_BLACK },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), COLOR_BLACK }
};
const std::vector<ColorTestStep> COLOR_TRANSPARENT_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), COLOR_TRANSPARENT }
};

auto array1 = std::array {
    Converter::ArkValue<Ark_Number>(1),
    Converter::ArkValue<Ark_Number>(2),
    Converter::ArkValue<Ark_Number>(3)
};
Converter::ArkArrayHolder<Array_Number> holder1(array1);
Array_Number arrayNumber1 = holder1.ArkValue();

auto array2 = std::array {
    Converter::ArkValue<Ark_Number>(9),
    Converter::ArkValue<Ark_Number>(1),
};
Converter::ArkArrayHolder<Array_Number> holder2(array2);
Array_Number arrayNumber2 = holder2.ArkValue();

auto array3 = std::array {
    Converter::ArkValue<Ark_Number>(2),
    Converter::ArkValue<Ark_Number>(-2),
    Converter::ArkValue<Ark_Number>(2),
    Converter::ArkValue<Ark_Number>(1),
    Converter::ArkValue<Ark_Number>(2),
};
Converter::ArkArrayHolder<Array_Number> holder3(array3);
Array_Number arrayNumber3 = holder3.ArkValue();

auto array4 = std::array {
    Converter::ArkValue<Ark_Number>(6),
    Converter::ArkValue<Ark_Number>(5),
    Converter::ArkValue<Ark_Number>(4),
    Converter::ArkValue<Ark_Number>(3),
    Converter::ArkValue<Ark_Number>(2),
    Converter::ArkValue<Ark_Number>(1)
};
Converter::ArkArrayHolder<Array_Number> holder4(array4);
Array_Number arrayNumber4 = holder4.ArkValue();
auto array5 = std::array<Ark_Number, 0> {};
Converter::ArkArrayHolder<Array_Number> holder5(array5);
Array_Number arrayNumber5 = holder5.ArkValue();

typedef std::tuple<Ark_Union_Number_Array_Number, std::string> SelectedIndexTestStep;
const std::vector<SelectedIndexTestStep> SELECTED_INDEX_TEST_PLAN = {
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(1), "1" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(-33), "0" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(2), "2" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(33), "0" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber1), "1" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber2), "0" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber3), "2" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber4), "0" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber5), "0" }
};

const std::vector<SelectedIndexTestStep> SELECTEDS_INDEX_TEST_PLAN = {
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(1), "[\"1\",\"0\",\"0\",\"0\",\"0\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(-33), "[\"0\",\"0\",\"0\",\"0\",\"0\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(2), "[\"2\",\"0\",\"0\",\"0\",\"0\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(33), "[\"0\",\"0\",\"0\",\"0\",\"0\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber1),
        "[\"1\",\"2\",\"0\",\"0\",\"0\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber2),
        "[\"0\",\"1\",\"0\",\"0\",\"0\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber3),
        "[\"2\",\"0\",\"2\",\"1\",\"2\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber4),
        "[\"0\",\"0\",\"0\",\"0\",\"2\",\"1\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber5),
        "[\"0\",\"0\",\"0\",\"0\",\"0\"]" }
};

const std::vector<SelectedIndexTestStep> SELECTEDS_INDEX_CASCADE_TEST_PLAN = {
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(1), "[\"1\",\"0\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(-33), "[\"0\",\"0\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(2), "[\"2\",\"0\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(33), "[\"0\",\"0\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber1), "[\"1\",\"2\",\"3\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber2), "[\"0\",\"1\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber3),
        "[\"2\",\"0\",\"2\",\"1\",\"2\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber4),
        "[\"0\",\"0\",\"4\",\"3\",\"2\",\"1\"]" },
    { Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arrayNumber5), "[\"0\",\"0\"]" }
};

typedef std::pair<Opt_Length, std::string> OptLengthTestStep;
const std::vector<OptLengthTestStep> DIVIDER_STROKE_WIDTH_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(10._px), "10.00px" },
    { Converter::ArkValue<Opt_Length>("-55.00%"), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(0._px), "0.00px" },
    { Converter::ArkValue<Opt_Length>(-20._px), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(15.4f), "15.40vp" },
    { Converter::ArkValue<Opt_Length>("55.00%"), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(22.11_px), "22.11px" },
    { Converter::ArkValue<Opt_Length>("99.00%"), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(13.0_vp), "13.00vp" },
    { Converter::ArkValue<Opt_Length>(-3.12_px), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE }
};
const std::vector<OptLengthTestStep> DIVIDER_MARGIN_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(10._px), "10.00px" },
    { Converter::ArkValue<Opt_Length>("-55.00%"), "0.00vp" },
    { Converter::ArkValue<Opt_Length>(0._px), "0.00px" },
    { Converter::ArkValue<Opt_Length>(-20._px), "0.00vp" },
    { Converter::ArkValue<Opt_Length>(15.4f), "15.40vp" },
    { Converter::ArkValue<Opt_Length>("55.00%"), "0.00vp" },
    { Converter::ArkValue<Opt_Length>(22.11_px), "22.11px" },
    { Converter::ArkValue<Opt_Length>("99.00%"), "0.00vp" },
    { Converter::ArkValue<Opt_Length>(13.0_vp), "13.00vp" },
    { Converter::ArkValue<Opt_Length>(-3.12_px), "0.00vp" }
};

typedef std::pair<Ark_Length, std::string> ArkLengthTestStep;
const std::vector<ArkLengthTestStep> GRADIENT_HEIGHT_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(1.0_px), "1.00px" },
    { Converter::ArkValue<Ark_Length>(0.5f), "0.50vp" },
    { Converter::ArkValue<Ark_Length>(-20.0f), "0.00px" },
    { Converter::ArkValue<Ark_Length>("99.00%"), "99.00%" },
    { Converter::ArkValue<Ark_Length>(0.7_vp), "0.70vp" },
    { Converter::ArkValue<Ark_Length>(-0.7_vp), "0.00px" },
    { Converter::ArkValue<Ark_Length>("30.00%"), "30.00%" },
};
} // namespace

class TextPickerModifierTest2 : public ModifierTestBase<GENERATED_ArkUITextPickerModifier,
    &GENERATED_ArkUINodeModifiers::getTextPickerModifier, GENERATED_ARKUI_TEXT_PICKER> {
    public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<PickerTheme>();
        SetupTheme<TextTheme>();
        AddResource(RES_STR_1_ID, "str1");
        AddResource(RES_STR_2_ID, "str2");
        AddResource(RES_STR_3_ID, "str3");
        AddResource(RES_PIC_1_ID, "pic1");
        AddResource(RES_PIC_2_ID, "pic2");
        AddResource(RES_PIC_3_ID, "pic3");
    }
};

static std::vector<std::tuple<std::string, std::vector<std::string>, std::string, int32_t, bool, bool,
    std::string, std::string, std::string>> textPickerOptionsAsStringArray = {
    {"single-column-picker#0", {"aa", "bb", "cc"}, "bb", -1, true, true,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "bb", "0"},
    {"single-column-picker#1", {"aa", "bb", "cc"}, "bb", 1, true, true,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "bb", "1"},
    {"single-column-picker#2", {"aa", "bb", "cc"}, "aa", 2, true, true,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "aa", "2"},
    {"single-column-picker#1", {"aa", "bb", "cc"}, "cc", 1, true, true,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "cc", "1"},
    {"single-column-picker#3", {"aa", "bb", "cc"}, "bb", 1, false, false,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "aa", "0"},
    {"single-column-picker#4", {"aa", "bb", "cc"}, "cc", 0, true, false,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "cc", "2"},
    {"single-column-picker#5", {"aa", "bb", "cc"}, "dd", 1, true, false,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "dd", "0"},
    {"single-column-picker#6", {"aa", "bb", "cc"}, "", 2, false, true,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "aa", "2"},
    {"single-column-picker#7", {"aa", "bb", "cc"}, "", 3, false, true,
        "[\"icon:,text:aa\",\"icon:,text:bb\",\"icon:,text:cc\"]", "aa", "0"},
};

typedef std::tuple<std::string, std::vector<std::vector<std::string>>, std::vector<std::string>,
    std::vector<int32_t>, bool, bool, std::string, std::vector<std::string>,
    std::vector<std::string>> multu_array_test_data;

static std::vector<multu_array_test_data> textPickerOptionsAsStringMultiArray = {
    {"multi-column-picker#0", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {}, {}, false, false,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"aa\"", "\"dd\""}, {"\"0\"", "\"0\""}},
    {"multi-column-picker#1", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb", "ee"}, {}, true, false,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"ee\""}, {"\"1\"", "\"1\""}},
    {"multi-column-picker#2", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb", "ee"}, {}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"ee\""}, {"\"0\"", "\"0\""}},
    {"multi-column-picker#3", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb", "ee"}, {1, 2}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"ee\""}, {"\"1\"", "\"2\""}},
    {"multi-column-picker#4", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {}, {2, 1}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"aa\"", "\"dd\""}, {"\"2\"", "\"1\""}},
    {"multi-column-picker#5", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {}, {}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"aa\"", "\"dd\""}, {"\"0\"", "\"0\""}},
    {"multi-column-picker#6", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb"}, {}, true, false,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"dd\""}, {"\"1\"", "\"0\""}},
    {"multi-column-picker#7", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb"}, {}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"dd\""}, {"\"0\"", "\"0\""}},
    {"multi-column-picker#8", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb"}, {2}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"dd\""}, {"\"2\"", "\"0\""}},
    {"multi-column-picker#9", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"hh", "gg"}, {}, true, false,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"aa\"", "\"dd\""}, {"\"0\"", "\"0\""}},
    {"multi-column-picker#10", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb", "ee", "hh"}, {}, true, false,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"ee\""}, {"\"1\"", "\"1\""}},
    {"multi-column-picker#11", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"bb", "ee"}, {3, 3}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"bb\"", "\"ee\""}, {"\"0\"", "\"0\""}},
    {"multi-column-picker#12", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"aa", "dd"}, {1, 1, 1}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"aa\"", "\"dd\""}, {"\"1\"", "\"1\""}},
    {"multi-column-picker#13", { {"aa", "bb", "cc"}, {"dd", "ee", "ff"} }, {"cc", "ff"}, {-1, -1}, true, true,
        "[[\"aa\",\"bb\",\"cc\"],[\"dd\",\"ee\",\"ff\"]]", {"\"cc\"", "\"ff\""}, {"\"0\"", "\"0\""}}
};

static std::string g_cascade1 =
    "[{\"text\":\"Category 1\", "
    "\"children\":[{\"text\":\"Subcategory 1\", "
    "\"children\":[{\"text\":\"Subcategory 2\"},{\"text\":\"Subcategory 3\"}]},"
    "{\"text\":\"item1\", "
    "\"children\":[{\"text\":\"item2\"},{\"text\":\"item3\"}]}]},"
    "{\"text\":\"Category 2\", \"children\":[{\"text\":\"Subcategory 1\", "
    "\"children\":[{\"text\":\"Subcategory 2\"},{\"text\":\"Subcategory 3\"}]},"
    "{\"text\":\"item1\", \"children\":[{\"text\":\"item2\"},{\"text\":\"item3\"}]}]}]";

typedef std::tuple<std::string, std::string, std::vector<std::string>, std::vector<int32_t>, bool, bool,
    std::string, std::vector<std::string>, std::vector<std::string>> cascade_test_data;

static std::vector<cascade_test_data> textPickerOptionsAsCascadeArray = {
    {"cascade-picker#1", "", {}, {}, false, false, g_cascade1,
        {"\"Category 1\"", "\"Subcategory 1\"", "\"Subcategory 2\""}, {"\"0\"", "\"0\"", "\"0\""}}
};

template<typename T>
void checkVectors(std::vector<T> actual, std::vector<T> expected)
{
    ASSERT_EQ(actual.size(), expected.size());
    for (int i = 0; i < actual.size(); i++) {
        EXPECT_EQ(actual.at(i), expected.at(i));
    }
}

/**
 * @tc.name: setDefaultItemHeight1
 * @tc.desc: Check the functionality of TextPickerModifier.DefaultPickerItemHeight1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setDefaultItemHeight1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDefaultPickerItemHeight1, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_DEFAULT_PICKER_ITEM_HEIGHT_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_DEFAULT_PICKER_ITEM_HEIGHT_DEFAULT_VALUE);

    for (const auto &[height, expected] : PICKER_ITEM_HEIGHT_TEST_PLAN) {
        auto heightOpt = Converter::ArkValue<Opt_Union_Number_String>(height);
        modifier_->setDefaultPickerItemHeight1(node_, &heightOpt);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_DEFAULT_PICKER_ITEM_HEIGHT_NAME);
        EXPECT_EQ(checkVal, expected);
    }

    auto heightOpt = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());
    modifier_->setDefaultPickerItemHeight1(node_, &heightOpt);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_DEFAULT_PICKER_ITEM_HEIGHT_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_DEFAULT_PICKER_ITEM_HEIGHT_DEFAULT_VALUE);
}

/**
 * @tc.name: setCanLoop1
 * @tc.desc: Check the functionality of TextPickerModifier.CanLoop1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setCanLoop1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCanLoop1, nullptr);

    auto checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_CAN_LOOP_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_CAN_LOOP_DEFAULT_VALUE);

    auto arkCanLoop = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    modifier_->setCanLoop1(node_, &arkCanLoop);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_CAN_LOOP_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_CAN_LOOP_DEFAULT_VALUE);

    arkCanLoop = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setCanLoop1(node_, &arkCanLoop);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_CAN_LOOP_NAME);
    EXPECT_EQ(checkVal, EXPECTED_TRUE);

    arkCanLoop = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setCanLoop1(node_, &arkCanLoop);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_CAN_LOOP_NAME);
    EXPECT_EQ(checkVal, EXPECTED_FALSE);
}

/**
 * @tc.name: setDisappearTextStyle1Default
 * @tc.desc: Check the functionality of TextPickerModifier.DisappearTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setDisappearTextStyle1Default, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
    auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
    auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkColor, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
    EXPECT_EQ(checkFamily, "");
    EXPECT_EQ(checkStyle, "FontStyle.Normal");
    EXPECT_EQ(checkWeight, "FontWeight.Normal");
}

/**
 * @tc.name: setDisappearTextStyle1Undefined
 * @tc.desc: Check the functionality of TextPickerModifier.DisappearTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setDisappearTextStyle1Undefined, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle1, nullptr);

    auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(Ark_Empty());
    modifier_->setDisappearTextStyle1(node_, &pickerStyleOpt);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
    auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
    auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkColor, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
    EXPECT_EQ(checkFamily, "");
    EXPECT_EQ(checkStyle, "FontStyle.Normal");
    EXPECT_EQ(checkWeight, "FontWeight.Normal");
}

/**
 * @tc.name: setDisappearTextStyle1Style
 * @tc.desc: Check the functionality of TextPickerModifier.DisappearTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setDisappearTextStyle1Style, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle1, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setDisappearTextStyle1Weight
 * @tc.desc: Check the functionality of TextPickerModifier.DisappearTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setDisappearTextStyle1Weight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle1, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setDisappearTextStyle1Family
 * @tc.desc: Check the functionality of TextPickerModifier.DisappearTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, DISABLED_setDisappearTextStyle1Family, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle1, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto family : UNION_RESOURCE_STRING_PLAN) {
        font.family = family.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setDisappearTextStyle1Size
 * @tc.desc: Check the functionality of TextPickerModifier.DisappearTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setDisappearTextStyle1Size, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle1, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setDisappearTextStyle1Color
 * @tc.desc: Check the functionality of TextPickerModifier.DisappearTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setDisappearTextStyle1Color, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle1, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_BLACK_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setTextStyle1Default
 * @tc.desc: Check the functionality of TextPickerModifier.TextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setTextStyle1Default, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
    auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
    auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkColor, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
    EXPECT_EQ(checkFamily, "");
    EXPECT_EQ(checkStyle, "FontStyle.Normal");
    EXPECT_EQ(checkWeight, "FontWeight.Normal");
}

/**
 * @tc.name: setTextStyle1Undefined
 * @tc.desc: Check the functionality of TextPickerModifier.TextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setTextStyle1Undefined, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);

    auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(Ark_Empty());
    modifier_->setTextStyle1(node_, &pickerStyleOpt);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
    auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
    auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkColor, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
    EXPECT_EQ(checkFamily, "");
    EXPECT_EQ(checkStyle, "FontStyle.Normal");
    EXPECT_EQ(checkWeight, "FontWeight.Normal");
}

/**
 * @tc.name: setTextStyle1Style
 * @tc.desc: Check the functionality of TextPickerModifier.TextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setTextStyle1Style, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setTextStyle1Weight
 * @tc.desc: Check the functionality of TextPickerModifier.TextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setTextStyle1Weight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setTextStyle1Family
 * @tc.desc: Check the functionality of TextPickerModifier.TextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, DISABLED_setTextStyle1Family, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto family : UNION_RESOURCE_STRING_PLAN) {
        font.family = family.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setTextStyle1Size
 * @tc.desc: Check the functionality of TextPickerModifier.TextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setTextStyle1Size, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setTextStyle1Color
 * @tc.desc: Check the functionality of TextPickerModifier.TextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setTextStyle1Color, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_BLACK_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectedTextStyle1Default
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setSelectedTextStyle1Default, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
    auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
    auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkColor, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
    EXPECT_EQ(checkFamily, "");
    EXPECT_EQ(checkStyle, "FontStyle.Normal");
    EXPECT_EQ(checkWeight, "FontWeight.Normal");
}

/**
 * @tc.name: setSelectedTextStyle1Undefined
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setSelectedTextStyle1Undefined, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle1, nullptr);

    auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(Ark_Empty());
    modifier_->setSelectedTextStyle1(node_, &pickerStyleOpt);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
    auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
    auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
    auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
    auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
    auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
    auto checkColor = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkColor, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    EXPECT_EQ(checkSize, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
    EXPECT_EQ(checkFamily, "");
    EXPECT_EQ(checkStyle, "FontStyle.Normal");
    EXPECT_EQ(checkWeight, "FontWeight.Normal");
}

/**
 * @tc.name: setSelectedTextStyle1Style
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setSelectedTextStyle1Style, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle1, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto style : FONT_STYLE_TEST_PLAN) {
        font.style = style.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setSelectedTextStyle1Weight
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setSelectedTextStyle1Weight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle1, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setSelectedTextStyle1Family
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, DISABLED_setSelectedTextStyle1Family, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle1, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto family : UNION_RESOURCE_STRING_PLAN) {
        font.family = family.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setSelectedTextStyle1Size
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setSelectedTextStyle1Size, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle1, nullptr);
    Ark_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_PickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::string>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_STYLE_NAME);
        auto checkFamily = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_FAMILY_NAME);
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setSelectedTextStyle1Color
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedTextStyle1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setSelectedTextStyle1Color, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle1, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_BLACK_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        auto pickerStyleOpt = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle1(node_, &pickerStyleOpt);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/*
 * @tc.name: setOnChange1Test
 * @tc.desc: Check the functionality of TextPickerModifier.setOnChange1
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setOnChange1Test, TestSize.Level1)
{
    const std::vector<std::string> values = {"aa", "bb"};
    const std::vector<double> indexes = {0.0, 1.0};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textPickerEventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(textPickerEventHub, nullptr);
    static std::optional<std::tuple<int32_t, std::vector<std::string>,  std::vector<double>>> checkInvoke;
    auto developerCallback = [](const Ark_Int32 resourceId, const Ark_Union_String_Array_String values,
        const Ark_Union_Number_Array_Number selecteds) {
        std::vector<std::string> stdValues;
        if (auto pickerValueOpt = Converter::OptConvert<PickerValueType>(values); pickerValueOpt) {
            auto pickerValue = pickerValueOpt.value();
            if (auto value = std::get_if<std::string>(&pickerValue); value) {
                    stdValues.push_back(*value);
            } else {
                stdValues = std::move(std::get<std::vector<std::string>>(pickerValue));
            }
        }
        std::vector<uint32_t> stdSelecteds;
        std::vector<double> stdDoubleSelecteds;
        if (auto pickerSelectedOpt = Converter::OptConvert<PickerSelectedType>(selecteds); pickerSelectedOpt) {
            auto pickerSelected = pickerSelectedOpt.value();
            if (auto selected = std::get_if<uint32_t>(&pickerSelected); selected) {
                stdSelecteds.push_back(*selected);
            } else {
                stdSelecteds = std::move(std::get<std::vector<uint32_t>>(pickerSelected));
            }
        }
        for (auto index: stdSelecteds) {
            stdDoubleSelecteds.push_back(static_cast<double>(index));
        }
        checkInvoke = { resourceId, stdValues, stdDoubleSelecteds };
    };
    auto func = ArkValue<OnTextPickerChangeCallback>(developerCallback, CONTEXT_ID);
    textPickerEventHub->FireChangeEvent(values, indexes);
    ASSERT_FALSE(checkInvoke.has_value());
    auto funcOpt = Converter::ArkValue<Opt_OnTextPickerChangeCallback>(func);
    modifier_->setOnChange1(node_, &funcOpt);
    textPickerEventHub->FireChangeEvent(values, indexes);
    ASSERT_TRUE(checkInvoke.has_value());
    EXPECT_EQ(std::get<INVOKE_POS_0>(checkInvoke.value()), CONTEXT_ID);
    checkVectors(std::get<INVOKE_POS_1>(checkInvoke.value()), values);
    checkVectors(std::get<INVOKE_POS_2>(checkInvoke.value()), indexes);

    checkInvoke = std::nullopt;
    funcOpt = Converter::ArkValue<Opt_OnTextPickerChangeCallback>(Ark_Empty());
    modifier_->setOnChange1(node_, &funcOpt);
    textPickerEventHub->FireChangeEvent(values, indexes);
    ASSERT_FALSE(checkInvoke.has_value());
}

/*
 * @tc.name: setOnScrollStop1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setOnScrollStop1, TestSize.Level1)
{
    const std::vector<std::string> values = {"ab", "cd"};
    const std::vector<double> indexes = {0.0, 1.0};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textPickerEventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(textPickerEventHub, nullptr);
    static std::optional<std::tuple<int32_t, std::vector<std::string>,  std::vector<double>>> checkInvoke;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Union_String_Array_String values,
        const Ark_Union_Number_Array_Number selecteds) {
        std::vector<std::string> stdValues;
        if (auto pickerValueOpt = Converter::OptConvert<PickerValueType>(values); pickerValueOpt) {
            auto pickerValue = pickerValueOpt.value();
            if (auto value = std::get_if<std::string>(&pickerValue); value) {
                    stdValues.push_back(*value);
            } else {
                stdValues = std::move(std::get<std::vector<std::string>>(pickerValue));
            }
        }
        std::vector<uint32_t> stdSelecteds;
        std::vector<double> stdDoubleSelecteds;
        if (auto pickerSelectedOpt = Converter::OptConvert<PickerSelectedType>(selecteds); pickerSelectedOpt) {
            auto pickerSelected = pickerSelectedOpt.value();
            if (auto selected = std::get_if<uint32_t>(&pickerSelected); selected) {
                stdSelecteds.push_back(*selected);
            } else {
                stdSelecteds = std::move(std::get<std::vector<uint32_t>>(pickerSelected));
            }
        }
        for (auto index: stdSelecteds) {
            stdDoubleSelecteds.push_back(static_cast<double>(index));
        }
        checkInvoke = { resourceId, stdValues, stdDoubleSelecteds };
    };
    auto arkCallback = ArkValue<TextPickerScrollStopCallback>(checkCallback, CONTEXT_ID);
    textPickerEventHub->FireScrollStopEvent(values, indexes);
    ASSERT_FALSE(checkInvoke.has_value());
    auto arkCallbackOpt = Converter::ArkValue<Opt_TextPickerScrollStopCallback>(arkCallback);
    modifier_->setOnScrollStop1(node_, &arkCallbackOpt);
    textPickerEventHub->FireScrollStopEvent(values, indexes);
    ASSERT_TRUE(checkInvoke.has_value());
    EXPECT_EQ(std::get<INVOKE_POS_0>(checkInvoke.value()), CONTEXT_ID);
    checkVectors(std::get<INVOKE_POS_1>(checkInvoke.value()), values);
    checkVectors(std::get<INVOKE_POS_2>(checkInvoke.value()), indexes);

    checkInvoke = std::nullopt;
    arkCallbackOpt = Converter::ArkValue<Opt_TextPickerScrollStopCallback>(Ark_Empty());
    modifier_->setOnScrollStop1(node_, &arkCallbackOpt);
    textPickerEventHub->FireScrollStopEvent(values, indexes);
    ASSERT_FALSE(checkInvoke.has_value());
}

/**
 * @tc.name: setDivider1StrokeWidth
 * @tc.desc: Check the functionality of TextPickerModifier.Divider1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setDivider1StrokeWidth, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDivider1, nullptr);
    Ark_DividerOptions options;

    for (const auto &[length, expected] : DIVIDER_STROKE_WIDTH_TEST_PLAN) {
        options.strokeWidth = length;
        auto unionOptions = Converter::ArkValue<Opt_DividerOptions>(options);
        modifier_->setDivider1(node_, &unionOptions);
        auto fullJson = GetJsonValue(node_);
        auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DIVIDER_NAME);
        auto checkStrokeWidth = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_STROKE_WIDTH_NAME);
        auto checkColor = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_COLOR_NAME);
        auto checkStartMargin =  GetAttrValue<std::string>(dividerObject, ATTRIBUTE_START_MARGIN_NAME);
        auto checkEndMargin = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_END_MARGIN_NAME);
        EXPECT_EQ(checkStrokeWidth, expected);
        EXPECT_EQ(checkColor, ATTRIBUTE_DIVIDER_COLOR_INITIAL_VALUE);
        EXPECT_EQ(checkStartMargin, ATTRIBUTE_DIVIDER_MARGIN_INITIAL_VALUE);
        EXPECT_EQ(checkEndMargin, ATTRIBUTE_DIVIDER_MARGIN_INITIAL_VALUE);
    }
}

/**
 * @tc.name: setDivider1Color
 * @tc.desc: Check the functionality of TextPickerModifier.Divider1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setDivider1Color, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDivider1, nullptr);
    Ark_DividerOptions options;
    Opt_ResourceColor resColor;

    for (const auto &[color, expected] : COLOR_TRANSPARENT_TEST_PLAN) {
        resColor.value = color;
        options.color = resColor;
        auto unionOptions = Converter::ArkValue<Opt_DividerOptions>(options);
        modifier_->setDivider1(node_, &unionOptions);
        auto fullJson = GetJsonValue(node_);
        auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DIVIDER_NAME);
        auto checkStrokeWidth = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_STROKE_WIDTH_NAME);
        auto checkColor = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_COLOR_NAME);
        auto checkStartMargin =  GetAttrValue<std::string>(dividerObject, ATTRIBUTE_START_MARGIN_NAME);
        auto checkEndMargin = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_END_MARGIN_NAME);
        EXPECT_EQ(checkStrokeWidth, ATTRIBUTE_DIVIDER_STROKE_WIDTH_INITIAL_VALUE);
        EXPECT_EQ(checkColor, expected);
        EXPECT_EQ(checkStartMargin, ATTRIBUTE_DIVIDER_MARGIN_INITIAL_VALUE);
        EXPECT_EQ(checkEndMargin, ATTRIBUTE_DIVIDER_MARGIN_INITIAL_VALUE);
    }
}

/**
 * @tc.name: setDivider1StartMargin
 * @tc.desc: Check the functionality of TextPickerModifier.Divider1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setDivider1StartMargin, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDivider1, nullptr);
    Ark_DividerOptions options;

    for (const auto &[length, expected] : DIVIDER_MARGIN_TEST_PLAN) {
        options.startMargin = length;
        auto unionOptions = Converter::ArkValue<Opt_DividerOptions>(options);
        modifier_->setDivider1(node_, &unionOptions);
        auto fullJson = GetJsonValue(node_);
        auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DIVIDER_NAME);
        auto checkStrokeWidth = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_STROKE_WIDTH_NAME);
        auto checkColor = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_COLOR_NAME);
        auto checkStartMargin =  GetAttrValue<std::string>(dividerObject, ATTRIBUTE_START_MARGIN_NAME);
        auto checkEndMargin = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_END_MARGIN_NAME);
        EXPECT_EQ(checkStrokeWidth, ATTRIBUTE_DIVIDER_STROKE_WIDTH_INITIAL_VALUE);
        EXPECT_EQ(checkColor, ATTRIBUTE_DIVIDER_COLOR_INITIAL_VALUE);
        EXPECT_EQ(checkStartMargin, expected);
        EXPECT_EQ(checkEndMargin, ATTRIBUTE_DIVIDER_MARGIN_INITIAL_VALUE);
    }
}

/**
 * @tc.name: setDivider1EndMargin
 * @tc.desc: Check the functionality of TextPickerModifier.Divider1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setDivider1EndMargin, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDivider1, nullptr);
    Ark_DividerOptions options;

    for (const auto &[length, expected] : DIVIDER_MARGIN_TEST_PLAN) {
        options.endMargin = length;
        auto unionOptions = Converter::ArkValue<Opt_DividerOptions>(options);
        modifier_->setDivider1(node_, &unionOptions);
        auto fullJson = GetJsonValue(node_);
        auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DIVIDER_NAME);
        auto checkStrokeWidth = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_STROKE_WIDTH_NAME);
        auto checkColor = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_COLOR_NAME);
        auto checkStartMargin =  GetAttrValue<std::string>(dividerObject, ATTRIBUTE_START_MARGIN_NAME);
        auto checkEndMargin = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_END_MARGIN_NAME);
        EXPECT_EQ(checkStrokeWidth, ATTRIBUTE_DIVIDER_STROKE_WIDTH_INITIAL_VALUE);
        EXPECT_EQ(checkColor, ATTRIBUTE_DIVIDER_COLOR_INITIAL_VALUE);
        EXPECT_EQ(checkStartMargin, ATTRIBUTE_DIVIDER_MARGIN_INITIAL_VALUE);
        EXPECT_EQ(checkEndMargin, expected);
    }
}

/**
 * @tc.name: setDivider1Undefined
 * @tc.desc: Check the functionality of TextPickerModifier.Divider1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setDivider1Undefined, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDivider1, nullptr);
    auto unionOptions = Converter::ArkValue<Opt_DividerOptions>();
    modifier_->setDivider1(node_, &unionOptions);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DIVIDER_NAME);
    auto checkStrokeWidth = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_STROKE_WIDTH_NAME);
    auto checkColor = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_COLOR_NAME);
    auto checkStartMargin = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_START_MARGIN_NAME);
    auto checkEndMargin = GetAttrValue<std::string>(dividerObject, ATTRIBUTE_END_MARGIN_NAME);
    EXPECT_EQ(checkStrokeWidth, ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE);
    EXPECT_EQ(checkColor, ATTRIBUTE_DIVIDER_COLOR_DEFAULT_VALUE);
    EXPECT_EQ(checkStartMargin, ATTRIBUTE_DIVIDER_MARGIN_DEFAULT_VALUE);
    EXPECT_EQ(checkEndMargin, ATTRIBUTE_DIVIDER_MARGIN_DEFAULT_VALUE);
}

/**
 * @tc.name: setGradientHeight1
 * @tc.desc: Check the functionality of TextPickerModifier.GradientHeight1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setGradientHeight1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setGradientHeight1, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_GRADIENT_HEIGHT_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_GRADIENT_HEIGHT_DEFAULT_VALUE);

    for (const auto &[height, expected] : GRADIENT_HEIGHT_TEST_PLAN) {
        auto heightOpt = Converter::ArkValue<Opt_Length>(height);
        modifier_->setGradientHeight1(node_, &heightOpt);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_GRADIENT_HEIGHT_NAME);
        EXPECT_EQ(checkVal, expected);
    }
    auto heightOpt = Converter::ArkValue<Opt_Length>(Ark_Empty());
    modifier_->setGradientHeight1(node_, &heightOpt);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_GRADIENT_HEIGHT_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_GRADIENT_HEIGHT_DEFAULT_VALUE);
}

/**
 * @tc.name: setSelectedIndex1
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedIndex1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setSelectedIndex1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedIndex1, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTED_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_SELECTED_DEFAULT_VALUE);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    std::vector<OHOS::Ace::NG::RangeContent> range;
    for (auto i = 0; i < 5; i++) {
        OHOS::Ace::NG::RangeContent content;
        content.icon_ = "";
        content.text_ = "text";
        range.emplace_back(content);
    }
    TextPickerModelNG::SetRange(frameNode, range);

    for (const auto &[index, expected] : SELECTED_INDEX_TEST_PLAN) {
        auto indexOpt = Converter::ArkValue<Opt_Union_Number_Array_Number>(index);
        modifier_->setSelectedIndex1(node_, &indexOpt);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTED_NAME);
        EXPECT_EQ(checkVal, expected);
    }

    auto indexOpt = Converter::ArkValue<Opt_Union_Number_Array_Number>(Ark_Empty());
    modifier_->setSelectedIndex1(node_, &indexOpt);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTED_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_SELECTED_DEFAULT_VALUE);
}

/**
 * @tc.name: setSelectedIndex1Multi
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedIndex1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setSelectedIndex1Multi, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedIndex1, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTEDS_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_SELECTEDS_DEFAULT_VALUE);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTED_NAME_INDEX);
    EXPECT_EQ(checkVal, ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::vector<OHOS::Ace::NG::TextCascadePickerOptions> options;
    for (auto i = 0; i < 5; i++) {
        OHOS::Ace::NG::TextCascadePickerOptions opt;
        opt.rangeResult = { "first", "second", "third" };
        options.emplace_back(opt);
    }
    TextPickerModelNG::SetColumns(frameNode, options);

    for (const auto &[indexes, expected] : SELECTEDS_INDEX_TEST_PLAN) {
        auto indexesOpt = Converter::ArkValue<Opt_Union_Number_Array_Number>(indexes);
        modifier_->setSelectedIndex1(node_, &indexesOpt);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTEDS_NAME);
        EXPECT_EQ(checkVal, expected);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTED_NAME_INDEX);
        EXPECT_EQ(checkVal, expected);
    }

    auto indexesOpt = Converter::ArkValue<Opt_Union_Number_Array_Number>(Ark_Empty());
    modifier_->setSelectedIndex1(node_, &indexesOpt);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTEDS_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_SELECTEDS_DEFAULT_VALUE);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTED_NAME_INDEX);
    EXPECT_EQ(checkVal, ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE);
}

/**
 * @tc.name: setSelectedIndex1MultiCascade
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedIndex1Impl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest2, setSelectedIndex1MultiCascade, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedIndex1, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTEDS_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_SELECTEDS_DEFAULT_VALUE);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTED_NAME_INDEX);
    EXPECT_EQ(checkVal, ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE);

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::vector<OHOS::Ace::NG::TextCascadePickerOptions> children;
    for (auto i = 0; i < 3; i++) {
        OHOS::Ace::NG::TextCascadePickerOptions opt;
        opt.rangeResult = { "first", "second" };
        children.emplace_back(opt);
    }
    std::vector<OHOS::Ace::NG::TextCascadePickerOptions> options;
    for (auto i = 0; i < 5; i++) {
        OHOS::Ace::NG::TextCascadePickerOptions opt;
        opt.rangeResult = { "first", "second", "third" };
        opt.children = children;
        options.emplace_back(opt);
    }
    TextPickerModelNG::SetIsCascade(frameNode, true);
    TextPickerModelNG::SetColumns(frameNode, options);

    for (const auto &[indexes, expected] : SELECTEDS_INDEX_CASCADE_TEST_PLAN) {
        auto indexesOpt = Converter::ArkValue<Opt_Union_Number_Array_Number>(indexes);
        modifier_->setSelectedIndex1(node_, &indexesOpt);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTEDS_NAME);
        EXPECT_EQ(checkVal, expected);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTED_NAME_INDEX);
        EXPECT_EQ(checkVal, expected);
    }
}
}