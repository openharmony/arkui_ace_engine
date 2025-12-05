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

// Prop names
const auto ATTRIBUTE_RANGE_NAME = "range";
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_VALUES_NAME = "values";
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
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME = "enableHapticFeedback";
const auto ATTRIBUTE_DISABLE_TEXT_STYLE_ANIMATION_NAME = "disableTextStyleAnimation";
const auto ATTRIBUTE_DEFAULT_TEXT_STYLE_NAME = "defaultTextStyle";
const auto ATTRIBUTE_DEFAULT_TEXT_STYLE_MIN_FONT_SIZE_NAME = "minFontSize";
const auto ATTRIBUTE_DEFAULT_TEXT_STYLE_MAX_FONT_SIZE_NAME = "maxFontSize";
const auto ATTRIBUTE_DEFAULT_TEXT_STYLE_TEXT_OVERFLOW_NAME = "overflow";

const auto RES_STR_1_ID = IntResourceId { 111, ResourceType::STRING };
const auto RES_STR_2_ID = IntResourceId { 222, ResourceType::STRING };
const auto RES_STR_3_ID = IntResourceId { 333, ResourceType::STRING };
const auto RES_PIC_1_ID = IntResourceId { 444, ResourceType::STRING };
const auto RES_PIC_2_ID = IntResourceId { 555, ResourceType::STRING };
const auto RES_PIC_3_ID = IntResourceId { 666, ResourceType::STRING };
const auto RES_INT_1_ID = IntResourceId { 777, ResourceType::INTEGER };
const auto RES_INT_VALUE = 28;
const auto TEST_COMMENT_ID = 0;
const auto RANGE_ID = 1;
const auto VALUES_ID = 2;
const auto SELECTEDS_ID = 3;
const auto HAS_VALUES_ID = 4;
const auto HAS_SELECTEDS_ID = 5;
const auto RANGE_RES_ID = 6;
const auto VALUES_RES_ID = 7;
const auto SELECTEDS_RES_ID = 8;
const auto NAME_SUBCATEGORY_1 = "Subcategory 1";
const auto NAME_SUBCATEGORY_2 = "Subcategory 2";
const auto NAME_SUBCATEGORY_3 = "Subcategory 3";
const auto NAME_ITEM_1 = "item1";
const auto NAME_ITEM_2 = "item2";
const auto NAME_ITEM_3 = "item3";
const auto NAME_CATEGORY_1 = "Category 1";
const auto NAME_CATEGORY_2 = "Category 2";

// Expected values
static const std::string EXPECTED_TRUE("true");
static const std::string EXPECTED_FALSE("false");
const std::string COLOR_WHITE = "#FFFFFFFF";
const std::string COLOR_BLACK = "#FF000000";
const std::string COLOR_TRANSPARENT = "#00000000";

const auto OPT_TRUE = Converter::ArkValue<Opt_Boolean>(true);
const auto OPT_FALSE = Converter::ArkValue<Opt_Boolean>(false);

// Default values
const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_VALUES_DEFAULT_COUNT = 0;
const auto ATTRIBUTE_SELECTEDS_DEFAULT_COUNT = 0;
const auto ATTRIBUTE_DEFAULT_PICKER_ITEM_HEIGHT_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_CAN_LOOP_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "14.00px";
const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = COLOR_BLACK;
const auto ATTRIBUTE_SELECTED_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_SELECTEDS_DEFAULT_VALUE = "[]";
const auto ATTRIBUTE_SELECTED_INDEX_DEFAULT_VALUE = "[]";
const auto ATTRIBUTE_DIVIDER_STROKE_WIDTH_INITIAL_VALUE = "0.00vp";
const auto ATTRIBUTE_DIVIDER_COLOR_INITIAL_VALUE = COLOR_WHITE;
const auto ATTRIBUTE_DIVIDER_MARGIN_INITIAL_VALUE = "0.00vp";
const auto ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE = "1.00px";
const auto ATTRIBUTE_DIVIDER_COLOR_DEFAULT_VALUE = COLOR_BLACK;
const auto ATTRIBUTE_DIVIDER_MARGIN_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_GRADIENT_HEIGHT_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_DISABLE_TEXT_STYLE_ANIMATION_DEFAULT_VALUE = "false";

// Test plans
typedef std::pair<Opt_Union_F64_String, std::string> PickerItemHeightTestStep;
const std::vector<PickerItemHeightTestStep> PICKER_ITEM_HEIGHT_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(1.), "1.00vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(3.3), "3.30vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(-3.3), "-3.30vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("3.3px"), "3.30px" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("3.3vp"), "3.30vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("345vp"), "345.00vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("25%"), "25.00%" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("-10px"), "-10.00px" }
};

const auto RES_CONTENT_STR = "aa.bb.cc";
const auto RES_CONTENT = Converter::ArkValue<Ark_String>(RES_CONTENT_STR);
const auto RES_NAME = NamedResourceId{"res_name", ResourceType::STRING};
const Opt_Union_String_Resource OPT_UNION_RESOURCE_RESOURCE = CreateResourceUnion<Opt_Union_String_Resource>(RES_NAME);
const std::string CHECK_RESOURCE_STR(RES_CONTENT_STR);

typedef std::pair<Opt_Union_String_Resource, std::string> UnionStringResourceTestStep;
const std::vector<UnionStringResourceTestStep> UNION_RESOURCE_STRING_PLAN = {
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(RES_CONTENT), CHECK_RESOURCE_STR },
    { OPT_UNION_RESOURCE_RESOURCE, CHECK_RESOURCE_STR }
};

typedef std::pair<Opt_Length, std::string> OptLengthTestStep;
const std::vector<OptLengthTestStep> FONT_SIZE_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(1.234), "1.23fp" },
    { Converter::ArkValue<Opt_Length>(-5.6789), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
};

const std::vector<std::pair<Opt_Union_F64_String_Resource, std::string>> MIN_MAX_FONT_SIZE_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(28.), "28.00fp" },
    { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("28px"), "28.00px" },
    { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("28"), "28.00fp" },
    { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("28%"), "28.00%" },
    { Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Resource>(CreateResource(RES_INT_1_ID)), "28.00vp" },
};

typedef std::pair<Opt_TextOverflow, std::string> TextOverflowTestStep;
std::vector<TextOverflowTestStep> TEXT_OVERFLOW_TEST_PLAN = {
    { Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_NONE), "TextOverflow.None" },
    { Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_CLIP), "TextOverflow.Clip" },
    { Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_ELLIPSIS), "TextOverflow.Ellipsis" },
    { Converter::ArkValue<Opt_TextOverflow>(ARK_TEXT_OVERFLOW_MARQUEE), "TextOverflow.Marquee" },
};

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

typedef std::tuple<Ark_ResourceColor, std::string> ColorTestStep;
const std::vector<ColorTestStep> COLOR_BLACK_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), COLOR_BLACK },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), COLOR_BLACK }
};
const std::vector<ColorTestStep> COLOR_TRANSPARENT_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("incorrect_color"), COLOR_TRANSPARENT },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(""), COLOR_TRANSPARENT }
};

Converter::ConvContext ctx;
auto array1 = std::array {1, 2, 3};
auto arrayNumber1 = ArkValue<Array_I32>(array1, &ctx);

auto array2 = std::array {9, 1};
auto arrayNumber2 = ArkValue<Array_I32>(array2, &ctx);

auto array3 = std::array {2, -2, 2, 1, 2};
auto arrayNumber3 = ArkValue<Array_I32>(array3, &ctx);

auto array4 = std::array {6, 5, 4, 3, 2, 1};
auto arrayNumber4 = ArkValue<Array_I32>(array4, &ctx);

auto array5 = std::array<int32_t, 0> {};
auto arrayNumber5 = ArkValue<Array_I32>(array5, &ctx);

typedef std::tuple<Opt_Union_I32_Array_I32, std::string> SelectedIndexTestStep;
const std::vector<SelectedIndexTestStep> SELECTED_INDEX_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Ark_Int32>(1), "1" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Ark_Int32>(-33), "0" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Ark_Int32>(2), "2" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Ark_Int32>(33), "0" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber1), "1" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber2), "0" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber3), "2" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber4), "0" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber5), "0" }
};

const std::vector<SelectedIndexTestStep> SELECTEDS_INDEX_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Ark_Int32>(1), "[\"1\",\"0\",\"0\",\"0\",\"0\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Ark_Int32>(-33), "[\"0\",\"0\",\"0\",\"0\",\"0\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Ark_Int32>(2), "[\"2\",\"0\",\"0\",\"0\",\"0\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Ark_Int32>(33), "[\"0\",\"0\",\"0\",\"0\",\"0\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber1),
        "[\"1\",\"2\",\"0\",\"0\",\"0\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber2),
        "[\"0\",\"1\",\"0\",\"0\",\"0\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber3),
        "[\"2\",\"0\",\"2\",\"1\",\"2\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber4),
        "[\"0\",\"0\",\"0\",\"0\",\"2\",\"1\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber5),
        "[\"0\",\"0\",\"0\",\"0\",\"0\"]" }
};

const std::vector<SelectedIndexTestStep> SELECTEDS_INDEX_CASCADE_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Ark_Int32>(1), "[\"1\",\"0\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Ark_Int32>(-33), "[\"0\",\"0\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Ark_Int32>(2), "[\"2\",\"0\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Ark_Int32>(33), "[\"0\",\"0\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber1), "[\"1\",\"2\",\"3\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber2), "[\"0\",\"1\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber3),
        "[\"2\",\"0\",\"2\",\"1\",\"2\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber4),
        "[\"0\",\"0\",\"4\",\"3\",\"2\",\"1\"]" },
    { Converter::ArkUnion<Opt_Union_I32_Array_I32, Array_I32>(arrayNumber5), "[\"0\",\"0\"]" }
};

typedef std::pair<Opt_Dimension, std::string> OptDimensionTestStep;
const std::vector<OptDimensionTestStep> DIVIDER_STROKE_WIDTH_TEST_PLAN = {
    { Converter::ArkValue<Opt_Dimension>("10px"), "10.00px" },
    { Converter::ArkValue<Opt_Dimension>("-55.00%"), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Dimension>("0px"), "0.00px" },
    { Converter::ArkValue<Opt_Dimension>("-20px"), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Dimension>(15.4f), "15.40vp" },
    { Converter::ArkValue<Opt_Dimension>("55.00%"), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Dimension>("22.11px"), "22.11px" },
    { Converter::ArkValue<Opt_Dimension>("99.00%"), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Dimension>("13.0vp"), "13.00vp" },
    { Converter::ArkValue<Opt_Dimension>("-3.12px"), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE }
};
const std::vector<OptDimensionTestStep> DIVIDER_MARGIN_TEST_PLAN = {
    { Converter::ArkValue<Opt_Dimension>("10px"), "10.00px" },
    { Converter::ArkValue<Opt_Dimension>("-55.00%"), "0.00vp" },
    { Converter::ArkValue<Opt_Dimension>("0px"), "0.00px" },
    { Converter::ArkValue<Opt_Dimension>("-20px"), "0.00vp" },
    { Converter::ArkValue<Opt_Dimension>(15.4f), "15.40vp" },
    { Converter::ArkValue<Opt_Dimension>("55.00%"), "0.00vp" },
    { Converter::ArkValue<Opt_Dimension>("22.11px"), "22.11px" },
    { Converter::ArkValue<Opt_Dimension>("99.00%"), "0.00vp" },
    { Converter::ArkValue<Opt_Dimension>("13.0vp"), "13.00vp" },
    { Converter::ArkValue<Opt_Dimension>("-3.12px"), "0.00vp" }
};

const std::vector<OptDimensionTestStep> GRADIENT_HEIGHT_TEST_PLAN = {
    { Converter::ArkValue<Opt_Dimension>("1.0px"), "1.00px" },
    { Converter::ArkValue<Opt_Dimension>(0.5f), "0.50vp" },
    { Converter::ArkValue<Opt_Dimension>(-20.0f), "0.00px" },
    { Converter::ArkValue<Opt_Dimension>("99.00%"), "99.00%" },
    { Converter::ArkValue<Opt_Dimension>("0.7vp"), "0.70vp" },
    { Converter::ArkValue<Opt_Dimension>("-0.7vp"), "0.00px" },
    { Converter::ArkValue<Opt_Dimension>("30.00%"), "30.00%" },
};
} // namespace

class TextPickerModifierTest : public ModifierTestBase<GENERATED_ArkUITextPickerModifier,
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
        AddResource(RES_INT_1_ID, RES_INT_VALUE);
    }
};

/*
 * @tc.name: setTextPickerOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextPickerOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);

    EXPECT_EQ(false, jsonValue->Contains(ATTRIBUTE_RANGE_NAME));

    std::string resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE);

    auto resultJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUES_NAME);
    ASSERT_NE(resultJson.get(), nullptr);
    EXPECT_EQ(true, resultJson.get()->IsArray());
    EXPECT_EQ(ATTRIBUTE_VALUES_DEFAULT_COUNT, resultJson.get()->GetArraySize());

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SELECTED_DEFAULT_VALUE);

    resultJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTEDS_NAME);
    ASSERT_NE(resultJson.get(), nullptr);
    EXPECT_EQ(true, resultJson.get()->IsArray());
    EXPECT_EQ(ATTRIBUTE_SELECTEDS_DEFAULT_COUNT, resultJson.get()->GetArraySize());
}

using TextPickerOptionsTestTuple = std::tuple<std::string, std::vector<std::string>, std::string, int32_t,
    bool, bool, std::string, std::string, std::string>;
static std::vector<TextPickerOptionsTestTuple> textPickerOptionsAsStringArray = {
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

/*
 * @tc.name: setTextPickerOptionsAsStringArray
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextPickerOptionsAsStringArray, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    auto valueCheck = [&resultStr, &jsonValue](const std::string& attrName,
        const TextPickerOptionsTestTuple& value, const std::string& expectedStr) {
        resultStr = GetAttrValue<std::string>(jsonValue, attrName);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    };

    for (auto&& value: textPickerOptionsAsStringArray) {
        Ark_TextPickerOptions arkTextPickerOptions;
        Converter::ArkArrayHolder<Array_String> stringHolder(std::get<RANGE_ID>(value));
        Array_String stringHolderValue = stringHolder.ArkValue();
        arkTextPickerOptions.range = Converter::ArkUnion<
            Ark_Union_Array_String_Array_Array_String_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent,
            Array_String>(stringHolderValue);

        if (std::get<HAS_VALUES_ID>(value)) {
            auto arkValue = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(std::get<VALUES_ID>(value));
            arkTextPickerOptions.value = Converter::ArkUnion<Opt_Union_BindableResourceStr_BindableResourceStrArray,
                Ark_BindableResourceStr>(Converter::ArkUnion<Ark_BindableResourceStr, Ark_ResourceStr>(arkValue));
        } else {
            arkTextPickerOptions.value =
                Converter::ArkUnion<Opt_Union_BindableResourceStr_BindableResourceStrArray>(Ark_Empty());
        }

        if (std::get<HAS_SELECTEDS_ID>(value)) {
            auto arkSelected = std::get<SELECTEDS_ID>(value);
            arkTextPickerOptions.selected =
                Converter::ArkUnion<Opt_Union_I32_Array_I32_Bindable_I32_Bindable_Array_I32, Ark_Int32>(arkSelected);
        } else {
            arkTextPickerOptions.selected =
                Converter::ArkUnion<Opt_Union_I32_Array_I32_Bindable_I32_Bindable_Array_I32>(Ark_Empty());
        }
        Opt_TextPickerOptions inputValueOptions = Converter::ArkValue<Opt_TextPickerOptions>(arkTextPickerOptions);

        modifier_->setTextPickerOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);

        valueCheck(ATTRIBUTE_RANGE_NAME, value, std::get<RANGE_RES_ID>(value));
        valueCheck(ATTRIBUTE_VALUE_NAME, value, std::get<VALUES_RES_ID>(value));
        valueCheck(ATTRIBUTE_SELECTED_NAME, value, std::get<SELECTEDS_RES_ID>(value));

        //check "values"
        auto resultJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUES_NAME);
        ASSERT_NE(resultJson.get(), nullptr);
        EXPECT_EQ(true, resultJson.get()->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
        EXPECT_EQ(ATTRIBUTE_VALUES_DEFAULT_COUNT, resultJson.get()->GetArraySize())
            << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

        //check "selecteds"
        resultJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTEDS_NAME);
        ASSERT_NE(resultJson.get(), nullptr);
        EXPECT_EQ(true, resultJson.get()->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
        EXPECT_EQ(ATTRIBUTE_SELECTEDS_DEFAULT_COUNT, resultJson.get()->GetArraySize())
            << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    }
}

std::vector<Ark_TextPickerRangeContent> rangeContents {
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("ic1")),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("aa")) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("ic2")),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("bb")) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("ic3")),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("cc")) }
};

std::vector<Ark_TextPickerRangeContent> rangeContentsRes {
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_Resource>(CreateResource(RES_PIC_1_ID)),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_STR_1_ID)) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_Resource>(CreateResource(RES_PIC_2_ID)),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_STR_2_ID)) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_Resource>(CreateResource(RES_PIC_3_ID)),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_STR_3_ID)) }
};

std::vector<Ark_TextPickerRangeContent> rangeContentsMix {
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("icon0")),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("txt0")) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_Resource>(CreateResource(RES_PIC_1_ID)),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("txt1")) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(Converter::ArkValue<Ark_String>("icon2")),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_STR_2_ID)) },
    { Converter::ArkUnion<Ark_Union_String_Resource, Ark_Resource>(CreateResource(RES_PIC_3_ID)),
        Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(CreateResource(RES_STR_3_ID)) }
};

using TextPickerOptionsAsRangeArrayTestTuple = std::tuple<std::string, std::vector<Ark_TextPickerRangeContent>,
    std::string, int32_t, bool, bool, std::string, std::string, std::string>;
static std::vector<TextPickerOptionsAsRangeArrayTestTuple> textPickerOptionsAsRangeArray = {
    {"range-picker#0", rangeContents, "bb", -1, true, true,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "0"},
    {"range-picker#1", rangeContents, "bb", 1, true, true,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "1"},
    {"range-picker#2", rangeContents, "aa", 2, true, true,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "2"},
    {"range-picker#3", rangeContents, "cc", 1, true, true,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "1"},
    {"range-picker#4", rangeContents, "bb", 1, false, false,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "0"},
    {"range-picker#5", rangeContents, "cc", 0, true, false,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "0"},
    {"range-picker#6", rangeContents, "dd", 1, true, false,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "0"},
    {"range-picker#7", rangeContents, "", 2, false, true,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "2"},
    {"range-picker#8", rangeContents, "dd", 3, true, true,
        "[\"icon:ic1,text:aa\",\"icon:ic2,text:bb\",\"icon:ic3,text:cc\"]", "", "0"},
    {"range-picker#9", rangeContentsRes, "", 0, false, false,
        "[\"icon:pic1,text:str1\",\"icon:pic2,text:str2\",\"icon:pic3,text:str3\"]", "", "0"},
    {"range-picker#10", rangeContentsMix, "", 0, false, false,
        "[\"icon:icon0,text:txt0\",\"icon:pic1,text:txt1\",\"icon:icon2,text:str2\",\"icon:pic3,text:str3\"]",
        "", "0"}
};

/*
 * @tc.name: setTextPickerOptionsAsRangeArray
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextPickerOptionsAsRangeArray, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    auto valueCheck = [&resultStr, &jsonValue](const std::string& attrName,
        const TextPickerOptionsAsRangeArrayTestTuple& value, const std::string& expectedStr) {
        resultStr = GetAttrValue<std::string>(jsonValue, attrName);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    };

    for (auto&& value: textPickerOptionsAsRangeArray) {
        Ark_TextPickerOptions arkTextPickerOptions;
        Converter::ArkArrayHolder<Array_TextPickerRangeContent> holder(std::get<RANGE_ID>(value));
        Array_TextPickerRangeContent holderValue = holder.ArkValue();
        arkTextPickerOptions.range = Converter::ArkUnion<
            Ark_Union_Array_String_Array_Array_String_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent,
            Array_TextPickerRangeContent>(holderValue);

        if (std::get<HAS_VALUES_ID>(value)) {
            auto arkValue = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(std::get<VALUES_ID>(value));
            arkTextPickerOptions.value = Converter::ArkUnion<Opt_Union_BindableResourceStr_BindableResourceStrArray,
                Ark_BindableResourceStr>(Converter::ArkUnion<Ark_BindableResourceStr, Ark_ResourceStr>(arkValue));
        } else {
            arkTextPickerOptions.value =
                Converter::ArkUnion<Opt_Union_BindableResourceStr_BindableResourceStrArray>(Ark_Empty());
        }

        if (std::get<HAS_SELECTEDS_ID>(value)) {
            arkTextPickerOptions.selected = Converter::ArkUnion<Opt_Union_I32_Array_I32_Bindable_I32_Bindable_Array_I32,
                Ark_Int32>(std::get<SELECTEDS_ID>(value));
        } else {
            arkTextPickerOptions.selected =
                Converter::ArkUnion<Opt_Union_I32_Array_I32_Bindable_I32_Bindable_Array_I32>(Ark_Empty());
        }
        Opt_TextPickerOptions inputValueOptions = Converter::ArkValue<Opt_TextPickerOptions>(arkTextPickerOptions);

        modifier_->setTextPickerOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);

        valueCheck(ATTRIBUTE_RANGE_NAME, value, std::get<RANGE_RES_ID>(value));
        valueCheck(ATTRIBUTE_VALUE_NAME, value, std::get<VALUES_RES_ID>(value));
        valueCheck(ATTRIBUTE_SELECTED_NAME, value, std::get<SELECTEDS_RES_ID>(value));

        //check "values"
        auto resultJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUES_NAME);
        ASSERT_NE(resultJson.get(), nullptr);
        EXPECT_EQ(true, resultJson.get()->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
        EXPECT_EQ(ATTRIBUTE_VALUES_DEFAULT_COUNT, resultJson.get()->GetArraySize())
            << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);

        //check "selecteds"
        resultJson = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTEDS_NAME);
        ASSERT_NE(resultJson.get(), nullptr);
        EXPECT_EQ(true, resultJson.get()->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
        EXPECT_EQ(ATTRIBUTE_SELECTEDS_DEFAULT_COUNT, resultJson.get()->GetArraySize())
            << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    }
}

namespace {
struct MultiArrayTestData {
    std::string input;
    std::vector<std::vector<std::string>> range;
    std::vector<std::string> values;
    std::vector<int32_t> selecteds;
    bool hasValues;
    bool hasSelecteds;
    std::string rangeRes;
    std::vector<std::string> valuesRes;
    std::vector<std::string> selectedsRes;
};

static std::vector<MultiArrayTestData> textPickerOptionsAsStringMultiArray = {
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

void MultiArrayPickerTestProcedure (std::unique_ptr<JsonValue>& jsonValue, MultiArrayTestData value)
{
    std::string resultStr;
    std::string expectedStr;

    //check "range"
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RANGE_NAME);
    expectedStr = value.rangeRes;
    EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << value.input;

    //check "value"
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    expectedStr = ATTRIBUTE_VALUE_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << value.input;

    //check "values"
    auto attrValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUES_NAME);
    auto resultJson = attrValue.get();
    ASSERT_NE(resultJson, nullptr);
    EXPECT_EQ(true, resultJson->IsArray()) << "Passed value is: " << value.input;
    auto requiredValuesCount = value.range.size();
    ASSERT_EQ(requiredValuesCount, resultJson->GetArraySize())
        << "Passed value is: " << value.input;
    ASSERT_EQ(requiredValuesCount, value.valuesRes.size())
        << "Passed value is: " << value.input;
    for (int i = 0; i < requiredValuesCount; i++) {
        resultStr = resultJson->GetArrayItem(i)->ToString();
        expectedStr = value.valuesRes[i];
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << value.input;
    }

    //check "selected"
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_NAME);
    expectedStr = ATTRIBUTE_SELECTED_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr)  << "Passed value is: " << value.input;

    if (!value.hasSelecteds) {
        return;
    }
    //check "selecteds"
    attrValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTEDS_NAME);
    resultJson = attrValue.get();
    ASSERT_NE(resultJson, nullptr);
    EXPECT_EQ(true, resultJson->IsArray()) << "Passed value is: " << value.input;
    auto requiredSelectedsCount = value.range.size();
    ASSERT_LE(requiredSelectedsCount, resultJson->GetArraySize())
        << "Passed value is: " << value.input;
    ASSERT_EQ(requiredSelectedsCount, value.selectedsRes.size())
        << "Passed value is: " << value.input;
    for (int i = 0; i < requiredSelectedsCount; i++) {
        resultStr = resultJson->GetArrayItem(i)->ToString();
        expectedStr = value.selectedsRes[i];
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << value.input;
    }
}
} // namespace

/*
 * @tc.name: setTextPickerOptionsAsStringMultiArray
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextPickerOptionsAsStringMultiArray, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;

    for (auto&& value: textPickerOptionsAsStringMultiArray) {
        Ark_TextPickerOptions arkTextPickerOptions;
        Converter::ConvContext ctx;

        arkTextPickerOptions.range = Converter::ArkUnion<
            Ark_Union_Array_String_Array_Array_String_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent,
            Array_Array_String>(value.range, &ctx);

        if (value.hasValues) {
            arkTextPickerOptions.value = Converter::ArkUnion<Opt_Union_BindableResourceStr_BindableResourceStrArray,
                Ark_BindableResourceStrArray>(
                    Converter::ArkUnion<Ark_BindableResourceStrArray, Array_ResourceStr>(value.values, &ctx));
        } else {
            arkTextPickerOptions.value =
                Converter::ArkUnion<Opt_Union_BindableResourceStr_BindableResourceStrArray>(Ark_Empty());
        }

        if (value.hasSelecteds) {
            arkTextPickerOptions.selected = Converter::ArkUnion<Opt_Union_I32_Array_I32_Bindable_I32_Bindable_Array_I32,
                Array_I32>(value.selecteds, &ctx);
        } else {
            arkTextPickerOptions.selected =
                Converter::ArkUnion<Opt_Union_I32_Array_I32_Bindable_I32_Bindable_Array_I32>(Ark_Empty());
        }
        Opt_TextPickerOptions inputValueOptions = Converter::ArkValue<Opt_TextPickerOptions>(arkTextPickerOptions);

        modifier_->setTextPickerOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);

        MultiArrayPickerTestProcedure(jsonValue, value);
    }
}

namespace {
constexpr auto CASCADE_DATA =
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

const std::vector<cascade_test_data> textPickerOptionsAsCascadeArray = {
    {"cascade-picker#1", "", {}, {}, false, false, CASCADE_DATA,
        {"\"Category 1\"", "\"Subcategory 1\"", "\"Subcategory 2\""}, {"\"0\"", "\"0\"", "\"0\""}}
};
} // namespace

Ark_TextCascadePickerRangeContent createCascadeLevel1(std::string str)
{
    Ark_String itemText = Converter::ArkValue<Ark_String>(str);
    Ark_TextCascadePickerRangeContent item;
    item.text = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(itemText);
    item.children = Converter::ArkValue<Opt_Array_TextCascadePickerRangeContent>(Ark_Empty());
    return item;
}

void InitChild(Ark_TextCascadePickerRangeContent& child, std::string name)
{
    Ark_String arkName = Converter::ArkValue<Ark_String>(name);
    child.text = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(arkName);
}

void CreateOptions(Array_TextCascadePickerRangeContent& arrayRoot,
    cascade_test_data value,
    Ark_TextPickerOptions& arkTextPickerOptions,
    Converter::ConvContext *ctx)
{
    arkTextPickerOptions.range = Converter::ArkUnion<
        Ark_Union_Array_String_Array_Array_String_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent,
        Array_TextCascadePickerRangeContent>(arrayRoot);
    if (std::get<HAS_VALUES_ID>(value)) {
        auto arkValue = Converter::ArkValue<Array_ResourceStr>(std::get<VALUES_ID>(value), Converter::FC);
        arkTextPickerOptions.value = Converter::ArkUnion<Opt_Union_BindableResourceStr_BindableResourceStrArray,
                Ark_BindableResourceStrArray>(
                    Converter::ArkUnion<Ark_BindableResourceStrArray, Array_ResourceStr>(arkValue));
    } else {
        arkTextPickerOptions.value =
            Converter::ArkUnion<Opt_Union_BindableResourceStr_BindableResourceStrArray>(Ark_Empty());
    }
    if (std::get<HAS_SELECTEDS_ID>(value)) {
        arkTextPickerOptions.selected =
            Converter::ArkUnion<Opt_Union_I32_Array_I32_Bindable_I32_Bindable_Array_I32, Array_I32>(
                std::get<SELECTEDS_ID>(value), ctx);
    } else {
        arkTextPickerOptions.selected =
            Converter::ArkUnion<Opt_Union_I32_Array_I32_Bindable_I32_Bindable_Array_I32>(Ark_Empty());
    }
}

void CascadePickerTestProcedure (std::unique_ptr<JsonValue>& jsonValue, cascade_test_data value)
{
    std::string resultStr;
    std::string expectedStr;

    //check "range"
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RANGE_NAME);
    expectedStr = std::get<RANGE_RES_ID>(value);
    EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    //check "value"
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    expectedStr = ATTRIBUTE_VALUE_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    //check "values"
    auto attrValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUES_NAME);
    auto resultJson = attrValue.get();
    ASSERT_NE(resultJson, nullptr);
    EXPECT_EQ(true, resultJson->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    ASSERT_EQ(resultJson->GetArraySize(), std::get<VALUES_RES_ID>(value).size())
        << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    for (int i = 0; i < resultJson->GetArraySize(); i++) {
        resultStr = resultJson->GetArrayItem(i)->ToString();
        expectedStr = std::get<VALUES_RES_ID>(value)[i];
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    }
    //check "select"
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SELECTED_NAME);
    expectedStr = ATTRIBUTE_SELECTED_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr)  << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    //check "selecteds"
    attrValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SELECTEDS_NAME);
    resultJson = attrValue.get();
    ASSERT_NE(resultJson, nullptr);
    EXPECT_EQ(true, resultJson->IsArray()) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    ASSERT_EQ(resultJson->GetArraySize(), std::get<SELECTEDS_RES_ID>(value).size())
        << "Passed value is: "<< std::get<TEST_COMMENT_ID>(value);
    for (int i = 0; i < resultJson->GetArraySize(); i++) {
        resultStr = resultJson->GetArrayItem(i)->ToString();
        expectedStr = std::get<SELECTEDS_RES_ID>(value)[i];
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<TEST_COMMENT_ID>(value);
    }
}
/*
 * @tc.name: setTextPickerOptionsAsCascadeArray
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextPickerOptionsAsCascadeArray, TestSize.Level1)
{
    std::vector<Ark_TextCascadePickerRangeContent> subcategoryVector;
    subcategoryVector.push_back(createCascadeLevel1(NAME_SUBCATEGORY_2));
    subcategoryVector.push_back(createCascadeLevel1(NAME_SUBCATEGORY_3));
    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> holderSubcategoryVector(subcategoryVector);
    Opt_Array_TextCascadePickerRangeContent optArraySubcategory =
        holderSubcategoryVector.OptValue<Opt_Array_TextCascadePickerRangeContent>();
    Ark_TextCascadePickerRangeContent child1;
    InitChild(child1, NAME_SUBCATEGORY_1);
    child1.children = optArraySubcategory;

    std::vector<Ark_TextCascadePickerRangeContent> itemVector;
    itemVector.push_back(createCascadeLevel1(NAME_ITEM_2));
    itemVector.push_back(createCascadeLevel1(NAME_ITEM_3));
    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> holderItemVector(itemVector);
    Opt_Array_TextCascadePickerRangeContent optArrayItem =
        holderItemVector.OptValue<Opt_Array_TextCascadePickerRangeContent>();
    Ark_TextCascadePickerRangeContent child2;
    InitChild(child2, NAME_ITEM_1);
    child2.children = optArrayItem;

    std::vector<Ark_TextCascadePickerRangeContent> childrenVector;
    childrenVector.push_back(child1);
    childrenVector.push_back(child2);
    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> holderChildrenVector(childrenVector);
    Opt_Array_TextCascadePickerRangeContent optArrayChildren =
        holderChildrenVector.OptValue<Opt_Array_TextCascadePickerRangeContent>();
    Ark_TextCascadePickerRangeContent main1;
    InitChild(main1, NAME_CATEGORY_1);
    main1.children = optArrayChildren;
    Ark_TextCascadePickerRangeContent main2;
    InitChild(main2, NAME_CATEGORY_2);
    main2.children = optArrayChildren;

    std::vector<Ark_TextCascadePickerRangeContent> rootVector;
    rootVector.push_back(main1);
    rootVector.push_back(main2);
    Converter::ArkArrayHolder<Array_TextCascadePickerRangeContent> holderRootVector(rootVector);
    Array_TextCascadePickerRangeContent arrayRoot = holderRootVector.ArkValue();

    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    for (auto&& value: textPickerOptionsAsCascadeArray) {
        Ark_TextPickerOptions arkTextPickerOptions;
        Converter::ConvContext ctx;
        CreateOptions(arrayRoot, value, arkTextPickerOptions, &ctx);
        Opt_TextPickerOptions inputValueOptions = Converter::ArkValue<Opt_TextPickerOptions>(arkTextPickerOptions);

        modifier_->setTextPickerOptions(node_, &inputValueOptions);
        jsonValue = GetJsonValue(node_);
        CascadePickerTestProcedure(jsonValue, value);
    }
}

template<typename T>
void checkVectors(std::vector<T> actual, std::vector<T> expected)
{
    ASSERT_EQ(actual.size(), expected.size());
    for (int i = 0; i < actual.size(); i++) {
        EXPECT_EQ(actual.at(i), expected.at(i));
    }
}

/*
 * @tc.name: setOnChangeTest
 * @tc.desc: Check the functionality of TextPickerModifier.setOnChange
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setOnChangeTest, TestSize.Level1)
{
    const std::vector<std::string> values = {"aa", "bb"};
    const std::vector<double> indexes = {0.0, 1.0};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textPickerEventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(textPickerEventHub, nullptr);
    static std::optional<std::tuple<int32_t, std::vector<std::string>,  std::vector<double>>> checkInvoke;
    auto developerCallback = [](const Ark_Int32 resourceId, const Ark_Union_String_Array_String values,
        const Ark_Union_I32_Array_I32 selecteds) {
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
    auto func = ArkCallback<Opt_OnTextPickerChangeCallback>(developerCallback, CONTEXT_ID);
    textPickerEventHub->FireChangeEvent(values, indexes);
    ASSERT_FALSE(checkInvoke.has_value());
    modifier_->setOnChange(node_, &func);
    textPickerEventHub->FireChangeEvent(values, indexes);
    ASSERT_TRUE(checkInvoke.has_value());
    EXPECT_EQ(std::get<INVOKE_POS_0>(checkInvoke.value()), CONTEXT_ID);
    checkVectors(std::get<INVOKE_POS_1>(checkInvoke.value()), values);
    checkVectors(std::get<INVOKE_POS_2>(checkInvoke.value()), indexes);
}

/**
 * @tc.name: setDefaultItemHeight
 * @tc.desc: Check the functionality of TextPickerModifier.DefaultPickerItemHeightImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setDefaultItemHeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDefaultPickerItemHeight, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_DEFAULT_PICKER_ITEM_HEIGHT_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_DEFAULT_PICKER_ITEM_HEIGHT_DEFAULT_VALUE);

    for (const auto &[height, expected] : PICKER_ITEM_HEIGHT_TEST_PLAN) {
        modifier_->setDefaultPickerItemHeight(node_, &height);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_DEFAULT_PICKER_ITEM_HEIGHT_NAME);
        EXPECT_EQ(checkVal, expected);
    }
}

/**
 * @tc.name: setCanLoop
 * @tc.desc: Check the functionality of TextPickerModifier.CanLoopImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setCanLoop, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCanLoop, nullptr);

    auto checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_CAN_LOOP_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_CAN_LOOP_DEFAULT_VALUE);

    modifier_->setCanLoop(node_, &OPT_TRUE);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_CAN_LOOP_NAME);
    EXPECT_EQ(checkVal, EXPECTED_TRUE);

    modifier_->setCanLoop(node_, &OPT_FALSE);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_CAN_LOOP_NAME);
    EXPECT_EQ(checkVal, EXPECTED_FALSE);
}

/**
 * @tc.name: setDisappearTextStyle
 * @tc.desc: Check the functionality of TextPickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setDisappearTextStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto optStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optStyle);
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
 * @tc.name: setDisappearTextWeight
 * @tc.desc: Check the functionality of TextPickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setDisappearTextWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto optStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optStyle);
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
        auto optStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optStyle);
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
 * @tc.name: setDisappearTextFamily
 * @tc.desc: Check the functionality of TextPickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, DISABLED_setDisappearTextFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto optStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optStyle);
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
 * @tc.name: setDisappearTextSize
 * @tc.desc: Check the functionality of TextPickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setDisappearTextSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto optStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &optStyle);
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
 * @tc.name: setDisappearTextColor
 * @tc.desc: Check the functionality of TextPickerModifier.DisappearTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, DISABLED_setDisappearTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_BLACK_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        auto style = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setDisappearTextStyle(node_, &style);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DISAPPEAR_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setTextStyle
 * @tc.desc: Check the functionality of TextPickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto optStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &optStyle);
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
 * @tc.name: setTextWeight
 * @tc.desc: Check the functionality of TextPickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto style = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &style);
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
        auto style = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &style);
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
 * @tc.name: setTextFamily
 * @tc.desc: Check the functionality of TextPickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, DISABLED_setTextFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto style = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &style);
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
 * @tc.name: setTextSize
 * @tc.desc: Check the functionality of TextPickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setTextSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto style = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &style);
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
 * @tc.name: setTextColor
 * @tc.desc: Check the functionality of TextPickerModifier.TextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, DISABLED_setTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_BLACK_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        auto style = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setTextStyle(node_, &style);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectedTextStyle
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setSelectedTextStyle, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto optStyle = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &optStyle);
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
 * @tc.name: setSelectedTextWeight
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setSelectedTextWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto style = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &style);
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
        auto style = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &style);
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
 * @tc.name: setSelectedTextFamily
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, DISABLED_setSelectedTextFamily, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto style = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &style);
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
 * @tc.name: setSelectedTextSize
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setSelectedTextSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
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
        auto style = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &style);
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
 * @tc.name: setSelectedTextColor
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedTextStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, DISABLED_setSelectedTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_BLACK_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        auto style = Converter::ArkValue<Opt_PickerTextStyle>(pickerStyle);
        modifier_->setSelectedTextStyle(node_, &style);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_SELECTED_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectedIndex
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedIndexImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setSelectedIndex, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedIndex, nullptr);
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
        modifier_->setSelectedIndex(node_, &index);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTED_NAME);
        EXPECT_EQ(checkVal, expected);
    }
}

/**
 * @tc.name: setSelectedIndexMulti
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedIndexImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setSelectedIndexMulti, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedIndex, nullptr);
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
        modifier_->setSelectedIndex(node_, &indexes);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTEDS_NAME);
        EXPECT_EQ(checkVal, expected);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTED_NAME_INDEX);
        EXPECT_EQ(checkVal, expected);
    }
}

/**
 * @tc.name: setSelectedIndexMultiCascade
 * @tc.desc: Check the functionality of TextPickerModifier.SelectedIndexImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setSelectedIndexMultiCascade, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedIndex, nullptr);
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
        modifier_->setSelectedIndex(node_, &indexes);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTEDS_NAME);
        EXPECT_EQ(checkVal, expected);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_SELECTED_NAME_INDEX);
        EXPECT_EQ(checkVal, expected);
    }
}

/**
 * @tc.name: setDividerStrokeWidth
 * @tc.desc: Check the functionality of TextPickerModifier.DividerImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setDividerStrokeWidth, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDivider, nullptr);
    Ark_DividerOptions options;

    for (const auto &[length, expected] : DIVIDER_STROKE_WIDTH_TEST_PLAN) {
        options.strokeWidth = length;
        auto unionOptions = Converter::ArkValue<Opt_DividerOptions>(options);
        modifier_->setDivider(node_, &unionOptions);
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
 * @tc.name: setDividerColor
 * @tc.desc: Check the functionality of TextPickerModifier.DividerImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, DISABLED_setDividerColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDivider, nullptr);
    Ark_DividerOptions options;
    Opt_ResourceColor resColor;

    for (const auto &[color, expected] : COLOR_TRANSPARENT_TEST_PLAN) {
        resColor.value = color;
        options.color = resColor;
        auto unionOptions = Converter::ArkValue<Opt_DividerOptions>(options);
        modifier_->setDivider(node_, &unionOptions);
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
 * @tc.name: setDividerStartMargin
 * @tc.desc: Check the functionality of TextPickerModifier.DividerImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setDividerStartMargin, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDivider, nullptr);
    Ark_DividerOptions options;

    for (const auto &[length, expected] : DIVIDER_MARGIN_TEST_PLAN) {
        options.startMargin = length;
        auto unionOptions = Converter::ArkValue<Opt_DividerOptions>(options);
        modifier_->setDivider(node_, &unionOptions);
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
 * @tc.name: setDividerEndMargin
 * @tc.desc: Check the functionality of TextPickerModifier.DividerImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setDividerEndMargin, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDivider, nullptr);
    Ark_DividerOptions options;

    for (const auto &[length, expected] : DIVIDER_MARGIN_TEST_PLAN) {
        options.endMargin = length;
        auto unionOptions = Converter::ArkValue<Opt_DividerOptions>(options);
        modifier_->setDivider(node_, &unionOptions);
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
 * @tc.name: setDividerEndMargin
 * @tc.desc: Check the functionality of TextPickerModifier.DividerImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setDividerUndefined, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDivider, nullptr);
    auto unionOptions = Converter::ArkValue<Opt_DividerOptions>();
    modifier_->setDivider(node_, &unionOptions);
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
 * @tc.name: setGradientHeight
 * @tc.desc: Check the functionality of TextPickerModifier.GradientHeightImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, DISABLED_setGradientHeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setGradientHeight, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_GRADIENT_HEIGHT_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_GRADIENT_HEIGHT_DEFAULT_VALUE);

    for (const auto &[height, expected] : GRADIENT_HEIGHT_TEST_PLAN) {
        modifier_->setGradientHeight(node_, &height);
        checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_GRADIENT_HEIGHT_NAME);
        EXPECT_EQ(checkVal, expected);
    }
}

#ifdef WRONG_OLD_GEN
/*
 * @tc.name: setOnChangeEventSelected1Impl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setOnChangeEventSelected1Impl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<float> value;
        std::optional<std::vector<float>> valueVct;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Union_Number_Array_Number parameter) {
        checkEvent = {
            .nodeId = resourceId
        };
        Converter::VisitUnion(parameter,
            [](const Ark_Number& value) {
                checkEvent->value = Converter::OptConvert<float>(value);
            },
            [](const Array_Number& value) {
                checkEvent->valueVct = Converter::OptConvert<std::vector<float>>(value);
            },
            []() {});
    };

    Callback_Union_Number_Array_Number_Void arkCallback =
        Converter::ArkValue<Callback_Union_Number_Array_Number_Void>(checkCallback, contextId);

    modifier_->set_onChangeEvent_selected(node_, &arkCallback);

    std::vector<std::string> value;
    std::vector<double> index;

    value.emplace_back("value");
    index.emplace_back(56.33);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent(value, index);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    ASSERT_EQ(checkEvent->value.has_value(), true);
    ASSERT_EQ(checkEvent->valueVct.has_value(), false);
    EXPECT_NEAR(checkEvent->value.value(), 56.33f, FLT_EPSILON);
}

/*
 * @tc.name: setOnChangeEventSelected2Impl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setOnChangeEventSelected2Impl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<float> value;
        std::optional<std::vector<float>> valueVct;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Union_Number_Array_Number parameter) {
        checkEvent = {
            .nodeId = resourceId
        };
        Converter::VisitUnion(parameter,
            [](const Ark_Number& value) {
                checkEvent->value = Converter::OptConvert<float>(value);
            },
            [](const Array_Number& value) {
                checkEvent->valueVct = Converter::OptConvert<std::vector<float>>(value);
            },
            []() {});
    };

    Callback_Union_Number_Array_Number_Void arkCallback =
        Converter::ArkValue<Callback_Union_Number_Array_Number_Void>(checkCallback, contextId);

    modifier_->set_onChangeEvent_selected(node_, &arkCallback);

    std::vector<std::string> value;
    std::vector<double> index;

    value.emplace_back("value_1");
    value.emplace_back("value_2");
    index.emplace_back(56.33);
    index.emplace_back(89.435);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent(value, index);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    ASSERT_EQ(checkEvent->value.has_value(), false);
    ASSERT_EQ(checkEvent->valueVct.has_value(), true);
    EXPECT_EQ(checkEvent->valueVct.value().size(), 2);
    EXPECT_NEAR(checkEvent->valueVct.value()[0], 56.33f, FLT_EPSILON);
    EXPECT_NEAR(checkEvent->valueVct.value()[1], 89.435f, FLT_EPSILON);
}

/*
 * @tc.name: setOnChangeEventValue1Impl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setOnChangeEventValue1Impl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<std::string> value;
        std::optional<std::vector<std::string>> valueVct;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Union_String_Array_String parameter) {
        checkEvent = {
            .nodeId = resourceId
        };
        Converter::VisitUnion(parameter,
            [](const Ark_String& value) {
                checkEvent->value = Converter::OptConvert<std::string>(value);
            },
            [](const Array_String& value) {
                checkEvent->valueVct = Converter::OptConvert<std::vector<std::string>>(value);
            },
            []() {});
    };

    Callback_Union_String_Array_String_Void arkCallback =
        Converter::ArkValue<Callback_Union_String_Array_String_Void>(checkCallback, contextId);

    modifier_->set_onChangeEvent_value(node_, &arkCallback);

    std::vector<std::string> value;
    std::vector<double> index;

    value.emplace_back("value");
    index.emplace_back(56.33);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent(value, index);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    ASSERT_EQ(checkEvent->value.has_value(), true);
    ASSERT_EQ(checkEvent->valueVct.has_value(), false);
    EXPECT_EQ(checkEvent->value.value(), "value");
}

/*
 * @tc.name: setOnChangeEventValue2Impl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setOnChangeEventValue2Impl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<std::string> value;
        std::optional<std::vector<std::string>> valueVct;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Union_String_Array_String parameter) {
        checkEvent = {
            .nodeId = resourceId
        };
        Converter::VisitUnion(parameter,
            [](const Ark_String& value) {
                checkEvent->value = Converter::OptConvert<std::string>(value);
            },
            [](const Array_String& value) {
                checkEvent->valueVct = Converter::OptConvert<std::vector<std::string>>(value);
            },
            []() {});
    };

    Callback_Union_String_Array_String_Void arkCallback =
        Converter::ArkValue<Callback_Union_String_Array_String_Void>(checkCallback, contextId);

    modifier_->set_onChangeEvent_value(node_, &arkCallback);

    std::vector<std::string> value;
    std::vector<double> index;

    value.emplace_back("value_1");
    value.emplace_back("value_2");
    index.emplace_back(56.33);
    index.emplace_back(89.435);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent(value, index);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    ASSERT_EQ(checkEvent->value.has_value(), false);
    ASSERT_EQ(checkEvent->valueVct.has_value(), true);
    EXPECT_EQ(checkEvent->valueVct.value().size(), 2);
    EXPECT_EQ(checkEvent->valueVct.value()[0], "value_1");
    EXPECT_EQ(checkEvent->valueVct.value()[1], "value_2");
}
#endif

/**
 * @tc.name: setEnableHapticFeedback
 * @tc.desc: Check the functionality of TextPickerModifierTest.EnableHapticFeedbackImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setEnableHapticFeedback, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEnableHapticFeedback, nullptr);
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_DEFAULT_VALUE);
    modifier_->setEnableHapticFeedback(node_, &OPT_FALSE);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(checkVal, EXPECTED_FALSE);
    modifier_->setEnableHapticFeedback(node_, &OPT_TRUE);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_ENABLE_HAPTIC_FEEDBACK_NAME);
    EXPECT_EQ(checkVal, EXPECTED_TRUE);
}

/**
 * @tc.name: disableTextStyleAnimation
 * @tc.desc: Check the functionality of TextPickerModifierTest.disableTextStyleAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, disableTextStyleAnimation, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisableTextStyleAnimation, nullptr);
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_DISABLE_TEXT_STYLE_ANIMATION_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_DISABLE_TEXT_STYLE_ANIMATION_DEFAULT_VALUE);
    modifier_->setDisableTextStyleAnimation(node_, &OPT_FALSE);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_DISABLE_TEXT_STYLE_ANIMATION_NAME);
    EXPECT_EQ(checkVal, EXPECTED_FALSE);
    modifier_->setDisableTextStyleAnimation(node_, &OPT_TRUE);
    checkVal = GetAttrValue<std::string>(node_, ATTRIBUTE_DISABLE_TEXT_STYLE_ANIMATION_NAME);
    EXPECT_EQ(checkVal, EXPECTED_TRUE);
}

/**
 * @tc.name: defaultTextWeight
 * @tc.desc: Check the functionality of TextPickerModifier.defaultTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, defaultTextWeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDefaultTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_TextPickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto sizeStr = FONT_SIZE_TEST_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto weight : FONT_WEIGHT_TEST_PLAN) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto style = Converter::ArkValue<Opt_TextPickerTextStyle>(pickerStyle);
        modifier_->setDefaultTextStyle(node_, &style);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DEFAULT_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        auto style = Converter::ArkValue<Opt_TextPickerTextStyle>(pickerStyle);
        modifier_->setDefaultTextStyle(node_, &style);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DEFAULT_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkWeight = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_WEIGHT_NAME);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: defaultTextSize
 * @tc.desc: Check the functionality of TextPickerModifier.defaultTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, defaultTextSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDefaultTextStyle, nullptr);
    Ark_arkui_component_units_Font font = {
        .family = UNION_RESOURCE_STRING_PLAN[0].first,
        .size = FONT_SIZE_TEST_PLAN[0].first,
        .style = FONT_STYLE_TEST_PLAN[0].first,
        .weight = FONT_WEIGHT_TEST_PLAN[0].first
    };
    Ark_TextPickerTextStyle pickerStyle;
    auto familyStr = UNION_RESOURCE_STRING_PLAN[0].second;
    auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : FONT_SIZE_TEST_PLAN) {
        font.size = size.first;
        pickerStyle.font.value = font;
        auto style = Converter::ArkValue<Opt_TextPickerTextStyle>(pickerStyle);
        modifier_->setDefaultTextStyle(node_, &style);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DEFAULT_TEXT_STYLE_NAME);
        auto fontObject = GetAttrValue<std::unique_ptr<JsonValue>>(styleObject, ATTRIBUTE_FONT_NAME);
        auto checkSize = GetAttrValue<std::string>(fontObject, ATTRIBUTE_FONT_SIZE_NAME);
        EXPECT_EQ(checkSize, size.second);
    }
}

/**
 * @tc.name: defaultTextColor
 * @tc.desc: Check the functionality of TextPickerModifier.defaultTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, DISABLED_defaultTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDefaultTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DEFAULT_TEXT_STYLE_NAME);
    auto checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_TextPickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_BLACK_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        auto style = Converter::ArkValue<Opt_TextPickerTextStyle>(pickerStyle);
        modifier_->setDefaultTextStyle(node_, &style);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DEFAULT_TEXT_STYLE_NAME);
        checkVal = GetAttrValue<std::string>(styleObject, ATTRIBUTE_COLOR_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: defaultTextStyleMinMaxFontSize
 * @tc.desc: Check the functionality of TextPickerModifier.defaultTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, defaultTextStyleMinMaxFontSize, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDefaultTextStyle, nullptr);
    Ark_TextPickerTextStyle pickerStyle;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto size : MIN_MAX_FONT_SIZE_TEST_PLAN) {
        pickerStyle.minFontSize = size.first;
        pickerStyle.maxFontSize = size.first;
        auto style = Converter::ArkValue<Opt_TextPickerTextStyle>(pickerStyle);
        modifier_->setDefaultTextStyle(node_, &style);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DEFAULT_TEXT_STYLE_NAME);
        auto minSize = GetAttrValue<std::string>(styleObject, ATTRIBUTE_DEFAULT_TEXT_STYLE_MIN_FONT_SIZE_NAME);
        auto maxSize = GetAttrValue<std::string>(styleObject, ATTRIBUTE_DEFAULT_TEXT_STYLE_MAX_FONT_SIZE_NAME);
        EXPECT_EQ(minSize, size.second);
        EXPECT_EQ(maxSize, size.second);
    }
}

/**
 * @tc.name: defaultTextStyleTextOverflow
 * @tc.desc: Check the functionality of TextPickerModifier.defaultTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, defaultTextStyleTextOverflow, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDefaultTextStyle, nullptr);
    Ark_TextPickerTextStyle pickerStyle;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    for (auto overflow : TEXT_OVERFLOW_TEST_PLAN) {
        pickerStyle.overflow = overflow.first;
        auto style = Converter::ArkValue<Opt_TextPickerTextStyle>(pickerStyle);
        modifier_->setDefaultTextStyle(node_, &style);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_DEFAULT_TEXT_STYLE_NAME);
        auto strRes = GetAttrValue<std::string>(styleObject, ATTRIBUTE_DEFAULT_TEXT_STYLE_TEXT_OVERFLOW_NAME);
        EXPECT_EQ(strRes, overflow.second);
    }
}

/*
 * @tc.name: setOnScrollStop
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setOnScrollStop, TestSize.Level1)
{
    const std::vector<std::string> values = {"ab", "cd"};
    const std::vector<double> indexes = {0.0, 1.0};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textPickerEventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(textPickerEventHub, nullptr);
    static std::optional<std::tuple<int32_t, std::vector<std::string>,  std::vector<double>>> checkInvoke;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Union_String_Array_String values,
        const Ark_Union_I32_Array_I32 selecteds) {
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
    auto arkCallback = ArkCallback<Opt_TextPickerScrollStopCallback>(checkCallback, CONTEXT_ID);
    textPickerEventHub->FireScrollStopEvent(values, indexes);
    ASSERT_FALSE(checkInvoke.has_value());
    modifier_->setOnScrollStop(node_, &arkCallback);
    textPickerEventHub->FireScrollStopEvent(values, indexes);
    ASSERT_TRUE(checkInvoke.has_value());
    EXPECT_EQ(std::get<INVOKE_POS_0>(checkInvoke.value()), CONTEXT_ID);
    checkVectors(std::get<INVOKE_POS_1>(checkInvoke.value()), values);
    checkVectors(std::get<INVOKE_POS_2>(checkInvoke.value()), indexes);
}

/*
 * @tc.name: setOnEnterSelectedArea
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setOnEnterSelectedArea, TestSize.Level1)
{
    const std::vector<std::string> values = {"ab", "cd"};
    const std::vector<double> indexes = {2.0, 3.0};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textPickerEventHub = frameNode->GetEventHub<TextPickerEventHub>();
    ASSERT_NE(textPickerEventHub, nullptr);
    static std::optional<std::tuple<int32_t, std::vector<std::string>,  std::vector<double>>> checkInvoke;
    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Union_String_Array_String values,
        const Ark_Union_I32_Array_I32 selecteds) {
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
    auto arkCallback = ArkCallback<Opt_TextPickerEnterSelectedAreaCallback>(checkCallback, CONTEXT_ID);
    textPickerEventHub->FireEnterSelectedAreaEvent(values, indexes);
    ASSERT_FALSE(checkInvoke.has_value());
    modifier_->setOnEnterSelectedArea(node_, &arkCallback);
    textPickerEventHub->FireEnterSelectedAreaEvent(values, indexes);
    ASSERT_TRUE(checkInvoke.has_value());
    EXPECT_EQ(std::get<INVOKE_POS_0>(checkInvoke.value()), CONTEXT_ID);
    checkVectors(std::get<INVOKE_POS_1>(checkInvoke.value()), values);
    checkVectors(std::get<INVOKE_POS_2>(checkInvoke.value()), indexes);
}
}
