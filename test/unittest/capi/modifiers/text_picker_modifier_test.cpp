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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/picker/picker_text_component.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "node_api.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;


namespace {
struct EventsTracker {
    static inline GENERATED_ArkUITextPickerEventsReceiver textPickerEventReceiver {};

    static inline const GENERATED_ArkUIEventsAPI eventsApiImpl {
        .getTextPickerEventsReceiver = []() -> const GENERATED_ArkUITextPickerEventsReceiver* {
            return &textPickerEventReceiver;
        }
    };
}; // EventsTracker

inline Ark_Resource ArkRes(Ark_String* name, int id = -1,
    NodeModifier::ResourceType type = NodeModifier::ResourceType::COLOR, const char* module = "",
    const char* bundle = "")
{
    return { .id = { .tag = ARK_TAG_INT32, .i32 = static_cast<Ark_Int32>(id) },
        .type = { .tag = ARK_TAG_INT32, .i32 = static_cast<Ark_Int32>(type) },
        .moduleName = { .chars = module },
        .bundleName = { .chars = bundle },
        .params = { .tag = ARK_TAG_OBJECT, .value = { .array = name, .length = name ? 1 : 0 } }
    };
}

// Prop names
const auto PROP_NAME_DEFAULT_PICKER_ITEM_HEIGHT = "defaultPickerItemHeight";
const auto PROP_NAME_CAN_LOOP = "canLoop";
const auto PROP_NAME_DISAPPEAR_TEXT_STYLE = "disappearTextStyle";
const auto PROP_NAME_TEXT_STYLE = "textStyle";
const auto PROP_NAME_SELECTED_TEXT_STYLE = "selectedTextStyle";
const auto PROP_NAME_FONT = "font";
const auto PROP_NAME_COLOR = "color";
const auto PROP_NAME_FONT_SIZE = "size";
const auto PROP_NAME_FONT_WEIGHT = "weight";
const auto PROP_NAME_FONT_STYLE = "style";
const auto PROP_NAME_FONT_FAMILY = "family";
const auto PROP_NAME_SELECTED = "selected";
const auto PROP_NAME_SELECTEDS = "selecteds";
const auto PROP_NAME_SELECTED_INDEX = "selectedIndex";
const auto PROP_NAME_DIVIDER = "divider";
const auto PROP_NAME_STROKE_WIDTH = "strokeWidth";
const auto PROP_NAME_START_MARGIN = "startMargin";
const auto PROP_NAME_END_MARGIN = "endMargin";
const auto PROP_NAME_GRADIENT_HEIGHT = "gradientHeight";

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

const Ark_Int32 AINT32_POS(70);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const auto CHECK_AINT32_POS = "70.00px";
const auto CHECK_AFLT32_POS = "1.23vp";

const auto RES_CONTENT_STR = "aa.bb.cc";
const auto RES_NAME_STR = "res_name";
const auto RES_CONTENT = Converter::ArkValue<Ark_String>(RES_CONTENT_STR);
const auto RES_NAME = Converter::ArkValue<Ark_String>(RES_NAME_STR);
const Opt_Union_String_Resource OPT_UNION_RESOURCE_RESOURCE =
    Converter::ArkUnion<Opt_Union_String_Resource, Ark_Resource>(
        ArkRes(const_cast<Ark_String*>(&RES_NAME), 1234, NodeModifier::ResourceType::STRING));
const std::string CHECK_RESOURCE_STR(RES_CONTENT_STR);

typedef std::pair<Opt_Union_String_Resource, std::string> UnionStringResourceTestStep;
const std::vector<UnionStringResourceTestStep> UNION_RESOURCE_STRING_PLAN = {
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(RES_CONTENT), CHECK_RESOURCE_STR },
    { OPT_UNION_RESOURCE_RESOURCE, CHECK_RESOURCE_STR }
};

typedef std::pair<Opt_Length, std::string> OptLengthTestStep;
const std::vector<OptLengthTestStep> FONT_SIZE_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(AINT32_POS), CHECK_AINT32_POS },
    { Converter::ArkValue<Opt_Length>(AINT32_NEG), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(AFLT32_NEG), ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(AFLT32_POS), CHECK_AFLT32_POS }
};

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
    { Converter::ArkValue<Opt_Length>(10), "10.00px" },
    { Converter::ArkValue<Opt_Length>(-55.0_pct), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(0), "0.00px" },
    { Converter::ArkValue<Opt_Length>(-20), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(15.4f), "15.40vp" },
    { Converter::ArkValue<Opt_Length>(55.0_pct), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(22.11_px), "22.11px" },
    { Converter::ArkValue<Opt_Length>(99.0_pct), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE },
    { Converter::ArkValue<Opt_Length>(13.0_vp), "13.00vp" },
    { Converter::ArkValue<Opt_Length>(-3.12_px), ATTRIBUTE_DIVIDER_STROKE_WIDTH_DEFAULT_VALUE }
};
const std::vector<OptLengthTestStep> DIVIDER_MARGIN_TEST_PLAN = {
    { Converter::ArkValue<Opt_Length>(10), "10.00px" },
    { Converter::ArkValue<Opt_Length>(-55.0_pct), "0.00vp" },
    { Converter::ArkValue<Opt_Length>(0), "0.00px" },
    { Converter::ArkValue<Opt_Length>(-20), "0.00vp" },
    { Converter::ArkValue<Opt_Length>(15.4f), "15.40vp" },
    { Converter::ArkValue<Opt_Length>(55.0_pct), "0.00vp" },
    { Converter::ArkValue<Opt_Length>(22.11_px), "22.11px" },
    { Converter::ArkValue<Opt_Length>(99.0_pct), "0.00vp" },
    { Converter::ArkValue<Opt_Length>(13.0_vp), "13.00vp" },
    { Converter::ArkValue<Opt_Length>(-3.12_px), "0.00vp" }
};

typedef std::pair<Ark_Length, std::string> ArkLengthTestStep;
const std::vector<ArkLengthTestStep> GRADIENT_HEIGHT_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(1.0_px), "1.00px" },
    { Converter::ArkValue<Ark_Length>(0.5f), "0.50vp" },
    { Converter::ArkValue<Ark_Length>(-20.0f), "0.00px" },
    { Converter::ArkValue<Ark_Length>(99.0_pct), "0.00px" },
    { Converter::ArkValue<Ark_Length>(0.7_vp), "0.70vp" },
    { Converter::ArkValue<Ark_Length>(-0.7_vp), "0.00px" },
    { Converter::ArkValue<Ark_Length>(0.3_pct), "0.00px" },
};
} // namespace

class TextPickerModifierTest
    : public ModifierTestBase<GENERATED_ArkUITextPickerModifier,
          &GENERATED_ArkUINodeModifiers::getTextPickerModifier, GENERATED_ARKUI_TEXT_PICKER> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<PickerTheme>();

        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/**
 * @tc.name: setDefaultItemHeight
 * @tc.desc: Check the functionality of TextPickerModifier.DefaultPickerItemHeightImpl
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerModifierTest, setDefaultItemHeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDefaultPickerItemHeight, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, PROP_NAME_DEFAULT_PICKER_ITEM_HEIGHT);
    EXPECT_EQ(checkVal, ATTRIBUTE_DEFAULT_PICKER_ITEM_HEIGHT_DEFAULT_VALUE);

    for (const auto &[height, expected] : PICKER_ITEM_HEIGHT_TEST_PLAN) {
        modifier_->setDefaultPickerItemHeight(node_, &height);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_DEFAULT_PICKER_ITEM_HEIGHT);
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

    auto checkVal = GetAttrValue<std::string>(node_, PROP_NAME_CAN_LOOP);
    EXPECT_EQ(checkVal, ATTRIBUTE_CAN_LOOP_DEFAULT_VALUE);

    modifier_->setCanLoop(node_, true);
    checkVal = GetAttrValue<std::string>(node_, PROP_NAME_CAN_LOOP);
    EXPECT_EQ(checkVal, EXPECTED_TRUE);

    modifier_->setCanLoop(node_, false);
    checkVal = GetAttrValue<std::string>(node_, PROP_NAME_CAN_LOOP);
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
        modifier_->setDisappearTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
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
        modifier_->setDisappearTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        modifier_->setDisappearTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
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
        modifier_->setDisappearTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
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
        modifier_->setDisappearTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
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
HWTEST_F(TextPickerModifierTest, setDisappearTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDisappearTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
    auto checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_BLACK_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        modifier_->setDisappearTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DISAPPEAR_TEXT_STYLE);
        checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
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
        modifier_->setTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
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
        modifier_->setTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        modifier_->setTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
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
        modifier_->setTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
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
        modifier_->setTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
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
HWTEST_F(TextPickerModifierTest, setTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
    auto checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_BLACK_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        modifier_->setTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_TEXT_STYLE);
        checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
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
        modifier_->setSelectedTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
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
        modifier_->setSelectedTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }

    for (auto weight : FONT_WEIGHT_TEST_PLAN2) {
        font.weight = weight.first;
        pickerStyle.font.value = font;
        modifier_->setSelectedTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
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
        modifier_->setSelectedTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
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
        modifier_->setSelectedTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        auto fontObject = GetAttrValue<std::string>(styleObject, PROP_NAME_FONT);
        auto checkSize = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_SIZE);
        auto checkWeight = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_WEIGHT);
        auto checkStyle =  GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_STYLE);
        auto checkFamily = GetAttrValue<std::string>(fontObject, PROP_NAME_FONT_FAMILY);
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
HWTEST_F(TextPickerModifierTest, setSelectedTextColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSelectedTextStyle, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
    auto checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkVal, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    Ark_PickerTextStyle pickerStyle;

    for (const auto& [value, expectVal] : COLOR_BLACK_TEST_PLAN) {
        pickerStyle.color = { .value = value };
        modifier_->setSelectedTextStyle(node_, &pickerStyle);
        auto fullJson = GetJsonValue(node_);
        auto styleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SELECTED_TEXT_STYLE);
        checkVal = GetAttrValue<std::string>(styleObject, PROP_NAME_COLOR);
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
    auto checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED);
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
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED);
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
    auto checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTEDS);
    EXPECT_EQ(checkVal, ATTRIBUTE_SELECTEDS_DEFAULT_VALUE);
    checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED_INDEX);
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
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTEDS);
        EXPECT_EQ(checkVal, expected);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED_INDEX);
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
    auto checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTEDS);
    EXPECT_EQ(checkVal, ATTRIBUTE_SELECTEDS_DEFAULT_VALUE);
    checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED_INDEX);
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
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTEDS);
        EXPECT_EQ(checkVal, expected);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_SELECTED_INDEX);
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
    Ark_Union_DividerOptions_Undefined unionOptions;
    Ark_DividerOptions options;

    for (const auto &[length, expected] : DIVIDER_STROKE_WIDTH_TEST_PLAN) {
        options.strokeWidth = length;
        unionOptions.value0 = options;
        modifier_->setDivider(node_, &unionOptions);
        auto fullJson = GetJsonValue(node_);
        auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DIVIDER);
        auto checkStrokeWidth = GetAttrValue<std::string>(dividerObject, PROP_NAME_STROKE_WIDTH);
        auto checkColor = GetAttrValue<std::string>(dividerObject, PROP_NAME_COLOR);
        auto checkStartMargin =  GetAttrValue<std::string>(dividerObject, PROP_NAME_START_MARGIN);
        auto checkEndMargin = GetAttrValue<std::string>(dividerObject, PROP_NAME_END_MARGIN);
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
HWTEST_F(TextPickerModifierTest, setDividerColor, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDivider, nullptr);
    Ark_Union_DividerOptions_Undefined unionOptions;
    Ark_DividerOptions options;
    Opt_ResourceColor resColor;

    for (const auto &[color, expected] : COLOR_TRANSPARENT_TEST_PLAN) {
        resColor.value = color;
        options.color = resColor;
        unionOptions.value0 = options;
        modifier_->setDivider(node_, &unionOptions);
        auto fullJson = GetJsonValue(node_);
        auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DIVIDER);
        auto checkStrokeWidth = GetAttrValue<std::string>(dividerObject, PROP_NAME_STROKE_WIDTH);
        auto checkColor = GetAttrValue<std::string>(dividerObject, PROP_NAME_COLOR);
        auto checkStartMargin =  GetAttrValue<std::string>(dividerObject, PROP_NAME_START_MARGIN);
        auto checkEndMargin = GetAttrValue<std::string>(dividerObject, PROP_NAME_END_MARGIN);
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
    Ark_Union_DividerOptions_Undefined unionOptions;
    Ark_DividerOptions options;

    for (const auto &[length, expected] : DIVIDER_MARGIN_TEST_PLAN) {
        options.startMargin = length;
        unionOptions.value0 = options;
        modifier_->setDivider(node_, &unionOptions);
        auto fullJson = GetJsonValue(node_);
        auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DIVIDER);
        auto checkStrokeWidth = GetAttrValue<std::string>(dividerObject, PROP_NAME_STROKE_WIDTH);
        auto checkColor = GetAttrValue<std::string>(dividerObject, PROP_NAME_COLOR);
        auto checkStartMargin =  GetAttrValue<std::string>(dividerObject, PROP_NAME_START_MARGIN);
        auto checkEndMargin = GetAttrValue<std::string>(dividerObject, PROP_NAME_END_MARGIN);
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
    Ark_Union_DividerOptions_Undefined unionOptions;
    Ark_DividerOptions options;

    for (const auto &[length, expected] : DIVIDER_MARGIN_TEST_PLAN) {
        options.endMargin = length;
        unionOptions.value0 = options;
        modifier_->setDivider(node_, &unionOptions);
        auto fullJson = GetJsonValue(node_);
        auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DIVIDER);
        auto checkStrokeWidth = GetAttrValue<std::string>(dividerObject, PROP_NAME_STROKE_WIDTH);
        auto checkColor = GetAttrValue<std::string>(dividerObject, PROP_NAME_COLOR);
        auto checkStartMargin =  GetAttrValue<std::string>(dividerObject, PROP_NAME_START_MARGIN);
        auto checkEndMargin = GetAttrValue<std::string>(dividerObject, PROP_NAME_END_MARGIN);
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
    Ark_Union_DividerOptions_Undefined unionOptions = {
        .selector = 1,
        .value1 = Ark_Undefined()
    };
    modifier_->setDivider(node_, &unionOptions);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_DIVIDER);
    auto checkStrokeWidth = GetAttrValue<std::string>(dividerObject, PROP_NAME_STROKE_WIDTH);
    auto checkColor = GetAttrValue<std::string>(dividerObject, PROP_NAME_COLOR);
    auto checkStartMargin = GetAttrValue<std::string>(dividerObject, PROP_NAME_START_MARGIN);
    auto checkEndMargin = GetAttrValue<std::string>(dividerObject, PROP_NAME_END_MARGIN);
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
HWTEST_F(TextPickerModifierTest, setGradientHeight, TestSize.Level1)
{
    ASSERT_NE(modifier_->setGradientHeight, nullptr);
    auto checkVal = GetAttrValue<std::string>(node_, PROP_NAME_GRADIENT_HEIGHT);
    EXPECT_EQ(checkVal, ATTRIBUTE_GRADIENT_HEIGHT_DEFAULT_VALUE);

    for (const auto &[height, expected] : GRADIENT_HEIGHT_TEST_PLAN) {
        modifier_->setGradientHeight(node_, &height);
        checkVal = GetAttrValue<std::string>(node_, PROP_NAME_GRADIENT_HEIGHT);
        EXPECT_EQ(checkVal, expected);
    }
}
} // namespace OHOS::Ace::NG
