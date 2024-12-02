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

#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const std::string COLOR_RED = "#FFFF0000";
const std::string COLOR_BLACK = "#FF000000";
const std::string COLOR_TRANSPARENT = "#00000000";
const auto COLOR_NAME = NamedResourceId("color_name", NodeModifier::ResourceType::COLOR);
const auto COLOR_ID = IntResourceId(1234, NodeModifier::ResourceType::COLOR);
const auto WRONG_COLOR_NAME = NamedResourceId("color_name", NodeModifier::ResourceType::STRING);
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
    { CreateResourceUnion<Ark_ResourceColor>(COLOR_NAME),
        COLOR_RED }, // Color::RED is result of mocked ThemeConstants::GetColorByName
    { CreateResourceUnion<Ark_ResourceColor>(COLOR_ID),
        COLOR_RED }, // Color::RED is result of mocked ThemeConstants::GetColor(int)
    { CreateResourceUnion<Ark_ResourceColor>(WRONG_COLOR_NAME),
        COLOR_BLACK } // Should be Color::RED, but converter from Resource works incorrect now.
                      // So modifier pass Color::BLACK to divider component in this case
};


typedef std::tuple<Ark_Boolean, bool> BoolTestStep;
const std::vector<BoolTestStep> BOOL_TEST_PLAN = {
    { false, false },
    { true, true },
    { 0, false },
    { -25, true },
    { 0, false },
    { 25, true },
    { false, false }};

const Ark_Int32 AINT32_POS(70);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Int32 FAKE_RES_ID(1234);
const Ark_Int32 INVALID_UNIT(10000);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);
const Ark_Float32 AFLT32_PERCENT_POS(70.0f);
const Ark_Float32 AFLT32_PERCENT_NEG(-70.0f);

typedef std::tuple<Ark_Length, std::string> ArkLengthTestStep;
const std::vector<ArkLengthTestStep> ARK_LENGTH_TEST_PLAN = {
    { { .type = ARK_TAG_INT32, .value = AINT32_POS, .unit = static_cast<int32_t>(DimensionUnit::PX) }, "70.00px" },
    { { .type = ARK_TAG_INT32, .value = AINT32_NEG, .unit = static_cast<int32_t>(DimensionUnit::PX) },
        "-2147483648.00px" },
    { { .type = ARK_TAG_INT32, .value = AFLT32_POS, .unit = static_cast<int32_t>(DimensionUnit::PX) }, "1.23px" },
    { { .type = ARK_TAG_INT32, .value = AFLT32_NEG, .unit = static_cast<int32_t>(DimensionUnit::PX) }, "-5.68px" },
    { { .type = ARK_TAG_FLOAT32, .value = AINT32_POS, .unit = static_cast<int32_t>(DimensionUnit::VP) }, "70.00vp" },
    { { .type = ARK_TAG_FLOAT32, .value = AINT32_NEG, .unit = static_cast<int32_t>(DimensionUnit::VP) },
        "-2147483648.00vp" },
    { { .type = ARK_TAG_FLOAT32, .value = AFLT32_POS, .unit = static_cast<int32_t>(DimensionUnit::VP) }, "1.23vp" },
    { { .type = ARK_TAG_FLOAT32, .value = AFLT32_NEG, .unit = static_cast<int32_t>(DimensionUnit::VP) }, "-5.68vp" },
    { { .type = ARK_TAG_FLOAT32, .value = AFLT32_POS, .unit = INVALID_UNIT }, "1.23px" },
    { { .type = ARK_TAG_FLOAT32, .value = AFLT32_PERCENT_POS, .unit = static_cast<int32_t>(DimensionUnit::PERCENT) },
        "70.00%" }, // Dimension::ToString do multiply value on 100
    { { .type = ARK_TAG_FLOAT32, .value = AFLT32_PERCENT_NEG, .unit = static_cast<int32_t>(DimensionUnit::PERCENT) },
        "-70.00%" } // Dimension::ToString do multiply value on 100
};
const std::vector<ArkLengthTestStep> ARK_LENGTH_TEST_PLAN_RES = {
    { { .type = ARK_TAG_RESOURCE, .value = AINT32_POS, .unit = static_cast<int32_t>(DimensionUnit::PX),
        .resource = FAKE_RES_ID },
        "0.00px" } // Work with resource dos not have final solution. Test step can be changed.
};

typedef std::pair<Ark_Union_Number_String_Resource, std::string> UnionNumStrResTestStep;
const Ark_String STR_NAME = Converter::ArkValue<Ark_String>("min_font_size");
const std::vector<UnionNumStrResTestStep> UNION_NUM_STR_RES_TEST_PLAN = {
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(123), "123.00vp" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(-123), "0.00px" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("5.6vp"), "5.60vp" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("-5.6vp"), "0.00px" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("45px"), "45.00px" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("-45px"), "0.00px" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(1.23f), "1.23vp" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(-1.23f), "0.00px" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("45fp"), "45.00fp" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("10%"), "0.00px" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("45dp"), "45.00fp" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("-10%"), "0.00px" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("undefVal"), "0.00fp" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("45.3fp"), "45.30fp" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(""), "0.00fp"},
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("qw111vp"), "0.00vp" },
    { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("qw111"), "0.00fp" }
};
const std::vector<UnionNumStrResTestStep> UNION_NUM_STR_RES_TEST_PLAN_RES = {
    { CreateResourceUnion<Ark_Union_Number_String_Resource>(IntResourceId(1234, NodeModifier::ResourceType::STRING)),
        "0.00px" }
};

typedef std::pair<Ark_Int32, Ark_Int32> ArkNumberIntTestStep;
const std::vector<ArkNumberIntTestStep> INT_NUMBER_TEST_PLAN = {
    { AINT32_POS, AINT32_POS },
    { AINT32_NEG, AINT32_NEG },
};

const std::vector<TextDeleteDirection> DELETE_DIRECTION_TEST_PLAN = {
    TextDeleteDirection::FORWARD,
    TextDeleteDirection::BACKWARD,
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
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_Number>(Converter::ArkValue<Ark_Number>(1000)),
        "FontWeight.Normal" },
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
        "FontWeight.Bolder" },
    { Converter::ArkUnion<Opt_Union_FontWeight_Number_String, Ark_String>(Converter::ArkValue<Ark_String>("1000")),
        "FontWeight.Normal" }
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

const auto RES_CONTENT = Converter::ArkValue<Ark_String>("aa.bb.cc");
const auto RES_NAME = NamedResourceId{"res_name", NodeModifier::ResourceType::STRING};
const Opt_Union_String_Resource OPT_UNION_RESOURCE_RESOURCE = CreateResourceUnion<Opt_Union_String_Resource>(RES_NAME);
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

typedef std::pair<Ark_TextDecorationType, std::string> DecorationTypeTestStep;
std::vector<DecorationTypeTestStep> TEXT_DECORATION_TYPE_TEST_PLAN = {
    { ARK_TEXT_DECORATION_TYPE_NONE, "TextDecorationType.None" },
    { ARK_TEXT_DECORATION_TYPE_UNDERLINE, "TextDecorationType.Underline" },
    { ARK_TEXT_DECORATION_TYPE_OVERLINE, "TextDecorationType.Overline" },
    { ARK_TEXT_DECORATION_TYPE_LINE_THROUGH, "TextDecorationType.LineThrough" },
    { static_cast<Ark_TextDecorationType>(-100), "TextDecorationType.None" },
    { static_cast<Ark_TextDecorationType>(3), "TextDecorationType.LineThrough" },
    { static_cast<Ark_TextDecorationType>(100), "TextDecorationType.None" },
    // only in the native part
    { static_cast<Ark_TextDecorationType>(TextDecoration::INHERIT), "TextDecorationType.None" },
};

typedef std::pair<Ark_TextDecorationStyle, std::string> DecorationStyleTestStep;
std::vector<DecorationStyleTestStep> TEXT_DECORATION_STYLE_TEST_PLAN = {
    { ARK_TEXT_DECORATION_STYLE_SOLID, "TextDecorationStyle.SOLID" },
    { ARK_TEXT_DECORATION_STYLE_DOUBLE, "TextDecorationStyle.DOUBLE" },
    { ARK_TEXT_DECORATION_STYLE_DOTTED, "TextDecorationStyle.DOTTED" },
    { ARK_TEXT_DECORATION_STYLE_DASHED, "TextDecorationStyle.DASHED" },
    { ARK_TEXT_DECORATION_STYLE_WAVY, "TextDecorationStyle.WAVY" },
    { static_cast<Ark_TextDecorationStyle>(-100), "TextDecorationStyle.SOLID" },
    { static_cast<Ark_TextDecorationStyle>(3), "TextDecorationStyle.DASHED" },
    { static_cast<Ark_TextDecorationStyle>(100), "TextDecorationStyle.SOLID" },
};

// events
const auto CHECK_TEXT("test_text");
const auto ERROR_TEXT("test_error_text");
PreviewText PREVIEW_TEXT = { .offset = 1234, .value = "test_offset" };
const auto EMPTY_TEXT("");

bool g_isEditChangeTest(true);
std::string g_EventTestString("");
std::string g_EventErrorTestString("");
int32_t g_EventTestOffset(0);
int32_t g_startValue(0);
int32_t g_endValue(0);
float g_scrollX(0);
float g_scrollY(0);
TextDeleteDirection g_deleteDirection(TextDeleteDirection::FORWARD);

GENERATED_ArkUITextAreaEventsReceiver recv {
    .onEditChange =
        [](Ark_Int32 nodeId, const Ark_Boolean isEditChange) {
            g_isEditChangeTest = isEditChange;
        },
    .onSubmit0 =
        [](Ark_Int32 nodeId, const Ark_EnterKeyType enterKey) {
            g_EventTestString = std::to_string(enterKey);
        },
    .onChange =
        [](Ark_Int32 nodeId, const Ark_String value, const Opt_PreviewText previewText) {
            g_EventTestOffset = PREVIEW_TEXT.offset;
            g_EventTestString.append(CHECK_TEXT).append(PREVIEW_TEXT.value);
        },
    .onTextSelectionChange =
        [](Ark_Int32 nodeId, Ark_Number selectionStart, Ark_Number selectionEnd) {
            g_startValue = Converter::Convert<int32_t>(selectionStart);
            g_endValue = Converter::Convert<int32_t>(selectionEnd);
        },
    .onContentScroll =
        [](Ark_Int32 nodeId, Ark_Number totalOffsetX, Ark_Number totalOffsetY) {
            g_scrollX = Converter::Convert<float>(totalOffsetX);
            g_scrollY = Converter::Convert<float>(totalOffsetY);
        },
    .onCopy =
        [](Ark_Int32 nodeId, Ark_String value) {
            auto textString = Converter::Convert<std::string>(value);
            g_EventTestString = textString;
        },
    .onCut =
        [](Ark_Int32 nodeId, Ark_String value) {
            g_EventTestString = Converter::Convert<std::string>(value);
        },
    .onWillInsert =
        [](Ark_Int32 nodeId, const Ark_InsertValue data) {
            g_EventTestString = Converter::Convert<std::string>(data.insertValue);
            g_EventTestOffset = Converter::Convert<int32_t>(data.insertOffset);
        },
    .onDidInsert =
        [](Ark_Int32 nodeId, const Ark_InsertValue data) {
            g_EventTestString = Converter::Convert<std::string>(data.insertValue);
            g_EventTestOffset = Converter::Convert<int32_t>(data.insertOffset);
        },
    .onWillDelete =
        [](Ark_Int32 nodeId, const Ark_DeleteValue data) {
            g_EventTestString = Converter::Convert<std::string>(data.deleteValue);
            g_EventTestOffset = Converter::Convert<int32_t>(data.deleteOffset);
            auto willDeleteDirection = Converter::OptConvert<TextDeleteDirection>(data.direction);
            if (willDeleteDirection) {
                g_deleteDirection = willDeleteDirection.value();
            }
        },
    .onDidDelete =
        [](Ark_Int32 nodeId, const Ark_DeleteValue data) {
            g_EventTestString = Converter::Convert<std::string>(data.deleteValue);
            g_EventTestOffset = Converter::Convert<int32_t>(data.deleteOffset);
            auto didDeleteDirection = Converter::OptConvert<TextDeleteDirection>(data.direction);
            if (didDeleteDirection) {
                g_deleteDirection = didDeleteDirection.value();
            }
        },
#ifdef WRONG_CALLBACK
    .inputFilter =
        [](Ark_Int32 nodeId, const Ark_String data) {
            g_EventErrorTestString = Converter::Convert<std::string>(data);
            g_EventTestString = g_EventErrorTestString;
        }
#endif
};

const GENERATED_ArkUITextAreaEventsReceiver* getTextAreaEventsReceiverTest()
{
    return &recv;
};

static const GENERATED_ArkUIEventsAPI* GetArkUiEventsAPITest()
{
    static const GENERATED_ArkUIEventsAPI eventsImpl = { .getTextAreaEventsReceiver = getTextAreaEventsReceiverTest };
    return &eventsImpl;
};
} // namespace

class TextAreaModifierTest : public ModifierTestBase<GENERATED_ArkUITextAreaModifier,
                                 &GENERATED_ArkUINodeModifiers::getTextAreaModifier, GENERATED_ARKUI_TEXT_AREA> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TextFieldTheme>();

        fullAPI_->setArkUIEventsAPI(GetArkUiEventsAPITest());
    }
};

/**
 * placeholderColorTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setPlaceholderColor
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setPlaceholderColorTest, TestSize.Level1)
{
    static const std::string PROP_NAME("placeholderColor");
    ASSERT_NE(modifier_->setPlaceholderColor, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, COLOR_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setPlaceholderColor(node_, &value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setPlaceholderColorTestRes
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setPlaceholderColor
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setPlaceholderColorTestRes, TestSize.Level1)
{
    static const std::string PROP_NAME("placeholderColor");
    ASSERT_NE(modifier_->setPlaceholderColor, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, COLOR_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN_RES) {
        modifier_->setPlaceholderColor(node_, &value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setCaretColorTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setCaretColor
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCaretColorTest, TestSize.Level1)
{
    static const std::string PROP_NAME("caretColor");
    ASSERT_NE(modifier_->setCaretColor, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, COLOR_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setCaretColor(node_, &value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
    }
}

/**
 * @tc.name: setFontColorTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontColorTest, TestSize.Level1)
{
    static const std::string PROP_NAME("fontColor");
    ASSERT_NE(modifier_->setFontColor, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, COLOR_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setFontColor(node_, &value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectedBackgroundColorTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setSelectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setSelectedBackgroundColorTest, TestSize.Level1)
{
    static const std::string PROP_NAME("selectedBackgroundColor");
    ASSERT_NE(modifier_->setSelectedBackgroundColor, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, COLOR_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setSelectedBackgroundColor(node_, &value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setEnablePreviewTextTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setEnablePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnablePreviewTextTest, TestSize.Level1)
{
    static const std::string PROP_NAME("enablePreviewText");
    ASSERT_NE(modifier_->setEnablePreviewText, nullptr);

    auto checkVal = GetAttrValue<bool>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, true);

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        modifier_->setEnablePreviewText(node_, value);
        checkVal = GetAttrValue<bool>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setEnableAutoFillTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setEnableAutoFill
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnableAutoFillTest, TestSize.Level1)
{
    static const std::string PROP_NAME("enableAutoFill");
    ASSERT_NE(modifier_->setEnableAutoFill, nullptr);

    auto checkVal = GetAttrValue<bool>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, true);

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        modifier_->setEnableAutoFill(node_, value);
        checkVal = GetAttrValue<bool>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setSelectionMenuHiddenTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setSelectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setSelectionMenuHiddenTest, TestSize.Level1)
{
    static const std::string PROP_NAME("selectionMenuHidden");
    ASSERT_NE(modifier_->setSelectionMenuHidden, nullptr);

    auto checkVal = GetAttrValue<bool>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, false);

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        modifier_->setSelectionMenuHidden(node_, value);
        checkVal = GetAttrValue<bool>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setEnableKeyboardOnFocusTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setEnableKeyboardOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnableKeyboardOnFocusTest, TestSize.Level1)
{
    static const std::string PROP_NAME("enableKeyboardOnFocus");
    ASSERT_NE(modifier_->setEnableKeyboardOnFocus, nullptr);

    auto checkVal = GetAttrValue<bool>(GetJsonValue(node_), PROP_NAME);
    EXPECT_EQ(checkVal, true);

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        modifier_->setEnableKeyboardOnFocus(node_, value);
        checkVal = GetAttrValue<bool>(GetJsonValue(node_), PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setTextIndentTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setTextIndent
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTextIndentTest, TestSize.Level1)
{
    static const std::string DEFAULT_TEXT_INDENT("0.00vp");
    static const std::string PROP_NAME("textIndent");
    ASSERT_NE(modifier_->setTextIndent, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, DEFAULT_TEXT_INDENT);

    for (const auto& [value, expectVal] : ARK_LENGTH_TEST_PLAN) {
        modifier_->setTextIndent(node_, &value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setCaretStyleTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setCaretStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCaretStyleTest, TestSize.Level1)
{
    static const std::string DEFAULT_CARET_COLOR("#FF000000");
    static const std::string DEFAULT_CARET_WIDTH("0.00px");
    static const std::string PROP_NAME("caretStyle");
    static const std::string PROP_COLOR("color");
    static const std::string PROP_WIDTH("width");
    ASSERT_NE(modifier_->setCaretStyle, nullptr);

    auto value = GetStringAttribute(node_, PROP_NAME);
    auto caretStyleObj = JsonUtil::ParseJsonString(value);
    auto defaultCaretColor = caretStyleObj->GetString(PROP_COLOR);
    auto defaultCaretWidth = caretStyleObj->GetString(PROP_WIDTH);
    EXPECT_EQ(defaultCaretColor, DEFAULT_CARET_COLOR);
    EXPECT_EQ(defaultCaretWidth, DEFAULT_CARET_WIDTH);

    typedef std::pair<std::string, std::string> CheckCaretValue;
    typedef std::pair<Ark_CaretStyle, CheckCaretValue> TestCaretStyle;

    std::vector<TestCaretStyle> testPlanCaretStyle;
    for (auto testLength : ARK_LENGTH_TEST_PLAN) {
        for (auto testColor : COLOR_TEST_PLAN) {
            Ark_CaretStyle arkCaretStyle = { .color = { .tag = ARK_TAG_OBJECT, .value = std::get<0>(testColor) },
                .width = { .tag = ARK_TAG_OBJECT, .value = std::get<0>(testLength) } };
            CheckCaretValue caretValue = { std::get<1>(testColor), std::get<1>(testLength) };
            auto type = std::get<0>(testLength).type;
            auto length = std::get<0>(testLength).value;
            auto unit = std::get<0>(testLength).unit;
            if (type != ARK_TAG_RESOURCE &&
                (LessNotEqual(length, 0.0f) || (unit == static_cast<int32_t>(DimensionUnit::PERCENT)))) {
                caretValue = { std::get<1>(testColor), DEFAULT_CARET_WIDTH };
            }
            TestCaretStyle testCaretStyle = { arkCaretStyle, caretValue };
            testPlanCaretStyle.push_back(testCaretStyle);
        }
    }

    for (auto caretStyle : testPlanCaretStyle) {
        modifier_->setCaretStyle(node_, &caretStyle.first);
        value = GetStringAttribute(node_, PROP_NAME);
        caretStyleObj = JsonUtil::ParseJsonString(value);
        auto caretColor = caretStyleObj->GetString(PROP_COLOR);
        auto caretWidth = caretStyleObj->GetString(PROP_WIDTH);
        EXPECT_EQ(caretColor, caretStyle.second.first);
        EXPECT_EQ(caretWidth, caretStyle.second.second);
    }
}

/**
 * @tc.name: setOnEditChangeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnEditChange
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnEditChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_Boolean_Void func{};
    modifier_->setOnEditChange(node_, &func);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    EXPECT_EQ(g_isEditChangeTest, true);
    ASSERT_NE(textFieldEventHub, nullptr);
    textFieldEventHub->FireOnEditChanged(false);
    EXPECT_EQ(g_isEditChangeTest, false);
    textFieldEventHub->FireOnEditChanged(true);
    EXPECT_EQ(g_isEditChangeTest, true);
}

/**
 * @tc.name: setOnSubmitTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnSubmit.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnSubmitTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_EnterKeyType_Void func{};
    modifier_->setOnSubmit0(node_, &func);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    ASSERT_NE(eventHub, nullptr);
    TextFieldCommonEvent event;
    eventHub->FireOnSubmit(111, event);
    EXPECT_EQ(g_EventTestString, "-1");
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEXT, event);
    EXPECT_EQ(g_EventTestString, "5");
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_GO, event);
    EXPECT_EQ(g_EventTestString, "2");
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_SEARCH, event);
    EXPECT_EQ(g_EventTestString, "3");
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_SEND, event);
    EXPECT_EQ(g_EventTestString, "4");
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEXT, event);
    EXPECT_EQ(g_EventTestString, "5");
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_DONE, event);
    EXPECT_EQ(g_EventTestString, "6");
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_PREVIOUS, event);
    EXPECT_EQ(g_EventTestString, "7");
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEW_LINE, event);
    EXPECT_EQ(g_EventTestString, "8");
}

/**
 * @tc.name: setOnChangeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnChangeTest, TestSize.Level1)
{
    g_EventTestString = "";
    g_EventTestOffset = 0;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    EditableTextOnChangeCallback func{};
    modifier_->setOnChange(node_, &func);
    textFieldEventHub->FireOnChange(CHECK_TEXT, PREVIEW_TEXT);
    std::string checkString = CHECK_TEXT;
    checkString.append(PREVIEW_TEXT.value);
    EXPECT_EQ(g_EventTestString, checkString);
    EXPECT_EQ(g_EventTestOffset, PREVIEW_TEXT.offset);
}

/**
 * @tc.name: setMaxLengthTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setMaxLength.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setMaxLengthTest, TestSize.Level1)
{
    static const std::string PROP_NAME("maxLength");
    ASSERT_NE(modifier_->setMaxLength, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "INF");

    typedef std::pair<Ark_Number, std::string> ArkNumberTestStep;
    static const std::vector<ArkNumberTestStep> arkNumberTestPlan = {
        { Converter::ArkValue<Ark_Number>(20), "20" },
        { Converter::ArkValue<Ark_Number>(0), "0" },
        { Converter::ArkValue<Ark_Number>(22.5f), "22" },
        { Converter::ArkValue<Ark_Number>(-20), "INF" },
        { Converter::ArkValue<Ark_Number>(0.0f), "0" },
        { Converter::ArkValue<Ark_Number>(-22.5f), "INF" } };

    for (const auto& [value, expectVal] : arkNumberTestPlan) {
        modifier_->setMaxLength(node_, &value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setMinFontSizeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setMinFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setMinFontSizeTest, TestSize.Level1)
{
    static const std::string PROP_NAME("minFontSize");
    ASSERT_NE(modifier_->setMinFontSize, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "0.00px");

    for (const auto& [value, expectVal] : UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setMinFontSize(node_, &value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setMaxFontSizeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setMaxFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setMaxFontSizeTest, TestSize.Level1)
{
    static const std::string PROP_NAME("maxFontSize");
    ASSERT_NE(modifier_->setMaxFontSize, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "0.00px");

    for (const auto& [value, expectVal] : UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setMaxFontSize(node_, &value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setLineHeightTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setLineHeightTest, TestSize.Level1)
{
    static const std::string PROP_NAME("lineHeight");
    ASSERT_NE(modifier_->setLineHeight, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "0.00vp");

    const std::vector<UnionNumStrResTestStep> testPlan = {
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(123), "123.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(-123), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("5.6vp"), "5.60vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("-5.6vp"), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("45px"), "45.00px" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("-45px"), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(1.23f), "1.23vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(-1.23f), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("45fp"), "45.00fp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("10%"), "10.00%" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("45dp"), "45.00fp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("-10%"), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("undefVal"), "0.00fp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("45.3fp"), "45.30fp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(""), "0.00fp"},
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("qw111vp"), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String_Resource, Ark_String>("qw111"), "0.00fp" },
    };

    for (const auto& [value, expectVal] : testPlan) {
        modifier_->setLineHeight(node_, &value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setLineHeightTestRes
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setLineHeightTest, TestSize.Level1)
{
    static const std::string PROP_NAME("lineHeight");
    ASSERT_NE(modifier_->setLineHeight, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "0.00vp");

    for (const auto& [value, expectVal] : UNION_NUM_STR_RES_TEST_PLAN_RES) {
        modifier_->setLineHeight(node_, &value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setTextAlignTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setTextAlign
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTextAlignTest, TestSize.Level1)
{
    static const std::string PROP_NAME("textAlign");
    ASSERT_NE(modifier_->setTextAlign, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "TextAlign.Start");

    typedef std::pair<Ark_TextAlign, std::string> TextAlignTestStep;
    const std::vector<TextAlignTestStep> testPlan = {
        { ARK_TEXT_ALIGN_CENTER, "TextAlign.Center" },
        { ARK_TEXT_ALIGN_START, "TextAlign.Start" },
        { ARK_TEXT_ALIGN_END, "TextAlign.End" },
        { ARK_TEXT_ALIGN_JUSTIFY, "TextAlign.Justify" },
        { static_cast<Ark_TextAlign>(-100), "TextAlign.Start" },
        { static_cast<Ark_TextAlign>(3), "TextAlign.Justify" },
        { static_cast<Ark_TextAlign>(100), "TextAlign.Start" }
    };

    for (const auto& [value, expectVal] : testPlan) {
        modifier_->setTextAlign(node_, value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setEnterKeyTypeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnterKeyTypeTest, TestSize.Level1)
{
    static const std::string PROP_NAME("enterKeyType");
    ASSERT_NE(modifier_->setEnterKeyType, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "EnterKeyType.NEW_LINE");

    typedef std::pair<Ark_EnterKeyType, std::string> EnterKeyTypeTestStep;
    const std::vector<EnterKeyTypeTestStep> testPlan = {
        { ARK_ENTER_KEY_TYPE_NEXT, "EnterKeyType.Next" },
        { ARK_ENTER_KEY_TYPE_DONE, "EnterKeyType.Done" },
        { ARK_ENTER_KEY_TYPE_PREVIOUS, "EnterKeyType.PREVIOUS" },
        { ARK_ENTER_KEY_TYPE_NEW_LINE, "EnterKeyType.NEW_LINE" },
        { ARK_ENTER_KEY_TYPE_SEND, "EnterKeyType.Send" },
        { static_cast<Ark_EnterKeyType>(0), "EnterKeyType.NEW_LINE" },
        { ARK_ENTER_KEY_TYPE_GO, "EnterKeyType.Go" },
        { static_cast<Ark_EnterKeyType>(1), "EnterKeyType.NEW_LINE" },
        { ARK_ENTER_KEY_TYPE_SEARCH, "EnterKeyType.Search" },
        { static_cast<Ark_EnterKeyType>(9), "EnterKeyType.NEW_LINE" },
    };

    for (const auto& [value, expectVal] : testPlan) {
        modifier_->setEnterKeyType(node_, value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setEnterKeyTypeTest2
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEnterKeyTypeTest2, TestSize.Level1)
{
    static const std::string PROP_NAME("enterKeyType");
    ASSERT_NE(modifier_->setEnterKeyType, nullptr);
    ASSERT_NE(modifier_->setMaxLines, nullptr);
    auto maxLines = Converter::ArkValue<Ark_Number>(1);
    modifier_->setMaxLines(node_, const_cast<Ark_Number*>(&maxLines));

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "EnterKeyType.NEW_LINE");

    // Additional conditions
    TextFieldModelNG::SetMaxLines(reinterpret_cast<FrameNode*>(node_), 1);
    checkVal = GetStringAttribute(node_, "maxLines");
    EXPECT_EQ(checkVal, "1");

    checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "EnterKeyType.Done");

    typedef std::pair<Ark_EnterKeyType, std::string> EnterKeyTypeTestStep;
    const std::vector<EnterKeyTypeTestStep> testPlan = {
        { ARK_ENTER_KEY_TYPE_NEXT, "EnterKeyType.Next" },
        { ARK_ENTER_KEY_TYPE_DONE, "EnterKeyType.Done" },
        { ARK_ENTER_KEY_TYPE_PREVIOUS, "EnterKeyType.PREVIOUS" },
        { ARK_ENTER_KEY_TYPE_NEW_LINE, "EnterKeyType.NEW_LINE" },
        { ARK_ENTER_KEY_TYPE_SEND, "EnterKeyType.Send" },
        { static_cast<Ark_EnterKeyType>(0), "EnterKeyType.Done" },
        { ARK_ENTER_KEY_TYPE_GO, "EnterKeyType.Go" },
        { static_cast<Ark_EnterKeyType>(1), "EnterKeyType.Done" },
        { ARK_ENTER_KEY_TYPE_SEARCH, "EnterKeyType.Search" },
        { static_cast<Ark_EnterKeyType>(9), "EnterKeyType.Done" },
    };

    for (const auto& [value, expectVal] : testPlan) {
        modifier_->setEnterKeyType(node_, value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setMaxLinesTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setMaxLinesTest, TestSize.Level1)
{
    static const std::string PROP_NAME("maxLines");
    static const std::string DEFAULT_MAX_VIEW_LINES("3");
    ASSERT_NE(modifier_->setMaxLines, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "INF");

    TextFieldModelNG::SetInputStyle(reinterpret_cast<FrameNode*>(node_), InputStyle::INLINE);
    checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, DEFAULT_MAX_VIEW_LINES);

    typedef std::pair<Ark_Number, std::string> ArkNumberTestStep;
    static const std::vector<ArkNumberTestStep> testPlan = {
        { Converter::ArkValue<Ark_Number>(20), "20" },
        { Converter::ArkValue<Ark_Number>(0), "0" },
        { Converter::ArkValue<Ark_Number>(22.5f), "22" },
        { Converter::ArkValue<Ark_Number>(-20), DEFAULT_MAX_VIEW_LINES },
        { Converter::ArkValue<Ark_Number>(0.0f), "0" },
        { Converter::ArkValue<Ark_Number>(-22.5f), DEFAULT_MAX_VIEW_LINES } };

    for (const auto& [value, expectVal] : testPlan) {
        modifier_->setMaxLines(node_, const_cast<Ark_Number*>(&value));
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setTypeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setType
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTypeTest, TestSize.Level1)
{
    static const std::string PROP_NAME("type");
    ASSERT_NE(modifier_->setType, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "TextAreaType.NORMAL");
    typedef std::pair<Ark_TextAreaType, std::string> typeTestStep;
    const std::vector<typeTestStep> testPlan = {
        { static_cast<Ark_TextAreaType>(TextInputType::EMAIL_ADDRESS), "TextAreaType.EMAIL" },
        { static_cast<Ark_TextAreaType>(TextInputType::BEGIN), "TextAreaType.NORMAL" },
        { ARK_TEXT_AREA_TYPE_EMAIL, "TextAreaType.EMAIL" },
        { static_cast<Ark_TextAreaType>(TextInputType::UNSPECIFIED), "TextAreaType.NORMAL" },
        { ARK_TEXT_AREA_TYPE_EMAIL, "TextAreaType.EMAIL" },
        { ARK_TEXT_AREA_TYPE_NORMAL, "TextAreaType.NORMAL" },
        { ARK_TEXT_AREA_TYPE_EMAIL, "TextAreaType.EMAIL" },
        { static_cast<Ark_TextAreaType>(TextInputType::MULTILINE), "TextAreaType.NORMAL" },
        { ARK_TEXT_AREA_TYPE_NUMBER, "TextAreaType.NUMBER" },
        { ARK_TEXT_AREA_TYPE_PHONE_NUMBER, "TextAreaType.PHONE_NUMBER" },
        { static_cast<Ark_TextAreaType>(TextInputType::DATETIME), "TextAreaType.NORMAL" },
        { ARK_TEXT_AREA_TYPE_EMAIL, "TextAreaType.EMAIL" },
        { static_cast<Ark_TextAreaType>(TextInputType::URL), "TextAreaType.NORMAL" },
        { ARK_TEXT_AREA_TYPE_EMAIL, "TextAreaType.EMAIL" },
        { static_cast<Ark_TextAreaType>(TextInputType::VISIBLE_PASSWORD), "TextAreaType.NORMAL" },
        { ARK_TEXT_AREA_TYPE_EMAIL, "TextAreaType.EMAIL" },
        { static_cast<Ark_TextAreaType>(TextInputType::NUMBER_PASSWORD), "TextAreaType.NORMAL" },
        { ARK_TEXT_AREA_TYPE_EMAIL, "TextAreaType.EMAIL" },
        { static_cast<Ark_TextAreaType>(TextInputType::SCREEN_LOCK_PASSWORD), "TextAreaType.NORMAL" },
        { ARK_TEXT_AREA_TYPE_EMAIL, "TextAreaType.EMAIL" },
        { static_cast<Ark_TextAreaType>(TextInputType::USER_NAME), "TextAreaType.NORMAL" },
        { ARK_TEXT_AREA_TYPE_EMAIL, "TextAreaType.EMAIL" },
        { static_cast<Ark_TextAreaType>(TextInputType::NEW_PASSWORD), "TextAreaType.NORMAL" },
        { ARK_TEXT_AREA_TYPE_EMAIL, "TextAreaType.EMAIL" },
        { ARK_TEXT_AREA_TYPE_NUMBER_DECIMAL, "TextAreaType.NUMBER_DECIMAL" },
        { ARK_TEXT_AREA_TYPE_URL, "TextAreaType.URL" },
        { ARK_TEXT_AREA_TYPE_EMAIL, "TextAreaType.EMAIL" },
        { static_cast<Ark_TextAreaType>(TextInputType::END), "TextAreaType.URL" },
    };
    for (const auto& [value, expectVal] : testPlan) {
        modifier_->setType(node_, value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setFontFeatureTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setFontFeature
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontFeatureTest, TestSize.Level1)
{
    static const std::string PROP_NAME("fontFeature");
    ASSERT_NE(modifier_->setFontFeature, nullptr);
    std::string checkVal = "";
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> array = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PROP_NAME);
    auto jsonArray = array.get();
    ASSERT_NE(jsonArray, nullptr);
    checkVal = jsonArray->ToString();
    EXPECT_EQ(checkVal, "");
    typedef std::pair<Ark_String, std::string> FontFeatureTestStep;
    const std::vector<FontFeatureTestStep> testPlan = {
        { Converter::ArkValue<Ark_String>("\"ss01\" on"), "\"ss01\" 1" },
        { Converter::ArkValue<Ark_String>("\"ss01\" off"), "\"ss01\" 0" },
        { Converter::ArkValue<Ark_String>("\"ss01\" 1"), "\"ss01\" 1" },
        { Converter::ArkValue<Ark_String>("\"ss01\" 0"), "\"ss01\" 0" },
        { Converter::ArkValue<Ark_String>("ss01 1"), "" },
        { Converter::ArkValue<Ark_String>("\"ss01\" on, \"ss02\" on"), "\"ss01\" 1,\"ss02\" 1" },
        { Converter::ArkValue<Ark_String>("\"ss01\" on, \"ss02\" off"), "\"ss01\" 1,\"ss02\" 0" },
        { Converter::ArkValue<Ark_String>("\"ss01\" on, ss02 off"),  "\"ss01\" 1" },
        { Converter::ArkValue<Ark_String>("ss01 on, ss02 off"), "" },
        { Converter::ArkValue<Ark_String>("\"ss01\" on"),  "\"ss01\" 1" },
        { Converter::ArkValue<Ark_String>("\"incorrect\" on"), "" },
        { Converter::ArkValue<Ark_String>("\"ss01\" on"),  "\"ss01\" 1" },
        { Converter::ArkValue<Ark_String>("invalid"), "" },
    };

    for (const auto& [value, expectVal] : testPlan) {
        modifier_->setFontFeature(node_, &value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setOnWillInsertTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnWillInsert.
 * @tc.desc: Test Seacrh setOnWillInsert event.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnWillInsertTest, TestSize.Level1)
{
    g_EventTestString = "";
    g_EventTestOffset = 0;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    InsertValueInfo checkValueDefault;
    textFieldEventHub->FireOnWillInsertValueEvent(checkValueDefault);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    Callback_InsertValue_Boolean func{};
    modifier_->setOnWillInsert(node_, &func);
    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        InsertValueInfo checkValue = { .insertOffset = value, .insertValue = CHECK_TEXT };
        textFieldEventHub->FireOnWillInsertValueEvent(checkValue);
        EXPECT_EQ(g_EventTestString, CHECK_TEXT);
        EXPECT_EQ(g_EventTestOffset, expectVal);
    }
}

/**
 * @tc.name: setOnDidInsertTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnDidInsert.
 * @tc.desc: Test Seacrh setOnDidInsert event.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnDidInsertTest, TestSize.Level1)
{
    g_EventTestString = "";
    g_EventTestOffset = 0;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    InsertValueInfo checkValueDefault;
    textFieldEventHub->FireOnDidInsertValueEvent(checkValueDefault);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    Callback_InsertValue_Void func{};
    modifier_->setOnDidInsert(node_, &func);
    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        InsertValueInfo checkValue = { .insertOffset = value, .insertValue = CHECK_TEXT };
        textFieldEventHub->FireOnDidInsertValueEvent(checkValue);
        EXPECT_EQ(g_EventTestString, CHECK_TEXT);
        EXPECT_EQ(g_EventTestOffset, expectVal);
    }
}

/**
 * @tc.name: setOnWillDeleteTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnWillDelete.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnWillDeleteTest, TestSize.Level1)
{
    g_EventTestString = "";
    g_EventTestOffset = 0;
    g_deleteDirection = TextDeleteDirection::FORWARD;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    DeleteValueInfo checkValueDefault;
    textFieldEventHub->FireOnWillDeleteEvent(checkValueDefault);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    EXPECT_EQ(g_deleteDirection, TextDeleteDirection::FORWARD);
    Callback_DeleteValue_Boolean func{};
    modifier_->setOnWillDelete(node_, &func);
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
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnDidlDelete.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnDidDeleteTest, TestSize.Level1)
{
    g_EventTestString = "";
    g_EventTestOffset = 0;
    g_deleteDirection = TextDeleteDirection::FORWARD;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    DeleteValueInfo checkValueDefault;
    textFieldEventHub->FireOnDidDeleteValueEvent(checkValueDefault);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    EXPECT_EQ(g_deleteDirection, TextDeleteDirection::FORWARD);
    Callback_DeleteValue_Void func{};
    modifier_->setOnDidDelete(node_, &func);
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
 * @tc.name: setOnTextSelectionChangeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnTextSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnTextSelectionChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnTextSelectionChange, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_Number_Number_Void func{};
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();

    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        modifier_->setOnTextSelectionChange(node_, &func);
        textFieldEventHub->FireOnSelectionChange(value, value);
        EXPECT_EQ(g_startValue, expectVal);
        EXPECT_EQ(g_endValue, expectVal);
    }
}

/**
 * @tc.name: setOnCopyTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnCopy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnCopyTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnCopy, nullptr);
    g_EventTestString = EMPTY_TEXT;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    textFieldEventHub->FireOnCopy(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    Callback_String_Void func{};
    modifier_->setOnCopy(node_, &func);
    textFieldEventHub->FireOnCopy(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, CHECK_TEXT);
}

/**
 * @tc.name: setOnCutTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnCut
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnCutTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnCut, nullptr);
    g_EventTestString = EMPTY_TEXT;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    textFieldEventHub->FireOnCut(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    Callback_String_Void func{};
    modifier_->setOnCut(node_, &func);
    textFieldEventHub->FireOnCut(CHECK_TEXT);
    EXPECT_EQ(g_EventTestString, CHECK_TEXT);
}

/**
 * @tc.name: setOnContentScrollTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnContentScroll
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnContentScrollTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnContentScroll, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_Number_Number_Void func{};
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();

    typedef std::pair<float, float> ArkNumberFloatTestStep;
    const std::vector<ArkNumberFloatTestStep> floatNumberTestPlan = {
        { AFLT32_POS, AFLT32_POS },
        { AFLT32_NEG, AFLT32_NEG },
    };

    for (const auto& [value, expectVal] : floatNumberTestPlan) {
        modifier_->setOnContentScroll(node_, &func);
        textFieldEventHub->FireOnScrollChangeEvent(value, value);
        EXPECT_EQ(g_scrollX, expectVal);
        EXPECT_EQ(g_scrollY, expectVal);
    }
}

/**
 * @tc.name: setCopyOptionTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setCopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setCopyOptionTest, TestSize.Level1)
{
    static const std::string PROP_NAME("copyOption");
    ASSERT_NE(modifier_->setCopyOption, nullptr);

    typedef std::pair<Ark_CopyOptions, std::string> CopyOptionTestStep;
    const std::vector<CopyOptionTestStep> copyOptionTestPlan = {
        { ARK_COPY_OPTIONS_NONE, "CopyOptions.None" },
        { ARK_COPY_OPTIONS_IN_APP, "CopyOptions.InApp" },
        { static_cast<Ark_CopyOptions>(4), "CopyOptions.Local" },
        { ARK_COPY_OPTIONS_CROSS_DEVICE, "CopyOptions.Distributed" },
        { ARK_COPY_OPTIONS_LOCAL_DEVICE, "CopyOptions.Local" }
    };

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "CopyOptions.Local"); // Now default value is CopyOptions.Distributed. It is wrong.
    for (const auto& [value, expectVal] : copyOptionTestPlan) {
        modifier_->setCopyOption(node_, value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setInputFilterTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setInputFilter
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setInputFilterTest, TestSize.Level1)
{
    static const std::string PROP_NAME("inputFilter");
    g_EventTestString = "";
    g_EventErrorTestString = "";
    ASSERT_NE(modifier_->setInputFilter, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Opt_Callback_String_Void func{};
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();

    auto sendString = Converter::ArkValue<Ark_String>(ERROR_TEXT);
    auto sendResource = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(sendString);
    modifier_->setInputFilter(node_, &sendResource, &func);
    textFieldEventHub->FireOnInputFilterError(ERROR_TEXT);
    auto filterValue = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(filterValue, ERROR_TEXT);
    EXPECT_EQ(g_EventTestString, ERROR_TEXT);
    EXPECT_EQ(g_EventErrorTestString, ERROR_TEXT);
}

/**
 * @tc.name: setPlaceholderFontTest1
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setPlaceholderFont.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setPlaceholderFontTest1, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPlaceholderFont, nullptr);

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
        modifier_->setPlaceholderFont(node_, &font);
        auto placeholderFontJSON = GetStringAttribute(node_, "placeholderFont");
        auto placeholderFont = JsonUtil::ParseJsonString(placeholderFontJSON);
        auto checkSize = placeholderFont->GetString("size");
        auto checkFamily = placeholderFont->GetString("fontFamily");
        auto checkWeight = placeholderFont->GetString("fontWeight");
        auto checkStyle = placeholderFont->GetString("style");
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, style.second);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setPlaceholderFontTest2
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setPlaceholderFont.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setPlaceholderFontTest2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPlaceholderFont, nullptr);

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
        modifier_->setPlaceholderFont(node_, &font);
        auto placeholderFontJSON = GetStringAttribute(node_, "placeholderFont");
        auto placeholderFont = JsonUtil::ParseJsonString(placeholderFontJSON);
        auto checkSize = placeholderFont->GetString("size");
        auto checkFamily = placeholderFont->GetString("fontFamily");
        auto checkWeight = placeholderFont->GetString("fontWeight");
        auto checkStyle = placeholderFont->GetString("style");
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setPlaceholderFontTest3
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setPlaceholderFont.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setPlaceholderFontTest3, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPlaceholderFont, nullptr);

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
        modifier_->setPlaceholderFont(node_, &font);
        auto placeholderFontJSON = GetStringAttribute(node_, "placeholderFont");
        auto placeholderFont = JsonUtil::ParseJsonString(placeholderFontJSON);
        auto checkSize = placeholderFont->GetString("size");
        auto checkFamily = placeholderFont->GetString("fontFamily");
        auto checkWeight = placeholderFont->GetString("weight");
        auto checkStyle = placeholderFont->GetString("style");
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily, familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weight.second);
    }
}

/**
 * @tc.name: setPlaceholderFontTestRes
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setPlaceholderFont.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setPlaceholderFontTestRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPlaceholderFont, nullptr);

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
        modifier_->setPlaceholderFont(node_, &font);
        auto placeholderFontJSON = GetStringAttribute(node_, "placeholderFont");
        auto placeholderFont = JsonUtil::ParseJsonString(placeholderFontJSON);
        auto checkSize = placeholderFont->GetString("size");
        auto checkFamily = placeholderFont->GetString("fontFamily");
        auto checkWeight = placeholderFont->GetString("fontWeight");
        auto checkStyle = placeholderFont->GetString("style");
        EXPECT_EQ(checkSize, sizeStr);
        EXPECT_EQ(checkFamily,  family.second);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setPlaceholderFontTest5
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setPlaceholderFont.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setPlaceholderFontTest5, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPlaceholderFont, nullptr);

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
        modifier_->setPlaceholderFont(node_, &font);
        auto placeholderFontJSON = GetStringAttribute(node_, "placeholderFont");
        auto placeholderFont = JsonUtil::ParseJsonString(placeholderFontJSON);
        auto checkSize = placeholderFont->GetString("size");
        auto checkFamily = placeholderFont->GetString("fontFamily");
        auto checkWeight = placeholderFont->GetString("fontWeight");
        auto checkStyle = placeholderFont->GetString("style");
        EXPECT_EQ(checkSize, size.second);
        EXPECT_EQ(checkFamily,  familyStr);
        EXPECT_EQ(checkStyle, styleStr);
        EXPECT_EQ(checkWeight, weightStr);
    }
}

/**
 * @tc.name: setDecorationTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setDecoration
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setDecorationTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDecoration, nullptr);
    const auto decorationsAttrs("decoration");
    const auto decorationTypeAttr("type");
    const auto decorationStyleAttr("style");
    const auto decorationColorAttr("color");
    auto defaultDecorationJSON = GetStringAttribute(node_, decorationsAttrs);
    auto defaultDecoration = JsonUtil::ParseJsonString(defaultDecorationJSON);
    auto defaultType = defaultDecoration->GetString(decorationTypeAttr);
    auto defaultStyle = defaultDecoration->GetString(decorationStyleAttr);
    auto defaultColor = defaultDecoration->GetString(decorationColorAttr);
    EXPECT_EQ(defaultType, "TextDecorationType.None");
    EXPECT_EQ(defaultStyle, "TextDecorationStyle.SOLID");
    EXPECT_EQ(defaultColor, COLOR_BLACK);

    for (const auto& [decorationType, expectDecorationType] : TEXT_DECORATION_TYPE_TEST_PLAN) {
        for (const auto& [decorationStyle, expectDecorationStyle] : TEXT_DECORATION_STYLE_TEST_PLAN) {
            for (const auto& [decorationColor, expectColor] : COLOR_TEST_PLAN) {
                Ark_TextDecorationOptions options = { .color = { .tag = ARK_TAG_OBJECT, .value = decorationColor },
                    .type = decorationType,
                    .style = Converter::ArkValue<Opt_TextDecorationStyle>(decorationStyle) };
                modifier_->setDecoration(node_, &options);
                auto decorationJSON = GetStringAttribute(node_, decorationsAttrs);
                auto decoration = JsonUtil::ParseJsonString(decorationJSON);
                auto type = decoration->GetString(decorationTypeAttr);
                auto style = decoration->GetString(decorationStyleAttr);
                auto color = decoration->GetString(decorationColorAttr);
                EXPECT_EQ(type, expectDecorationType);
                EXPECT_EQ(style, expectDecorationStyle);
                EXPECT_EQ(color, expectColor);
            }
        }
    }
}

/**
 * @tc.name: setLetterSpacingTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setLetterSpacing
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setLetterSpacingTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLetterSpacing, nullptr);
    const auto letterSpacingAttr("letterSpacing");

    auto checkVal = GetStringAttribute(node_, letterSpacingAttr);
    EXPECT_EQ(checkVal, "0.00px");

    for (const auto &[value, expectVal]: UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setLetterSpacing(node_, &value);
        checkVal = GetStringAttribute(node_, letterSpacingAttr);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setLetterSpacingTestRes
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setLetterSpacing
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setLetterSpacingTestRes, TestSize.Level1)
{
    ASSERT_NE(modifier_->setLetterSpacing, nullptr);
    const auto letterSpacingAttr("letterSpacing");

    auto checkVal = GetStringAttribute(node_, letterSpacingAttr);
    EXPECT_EQ(checkVal, "0.00px");

    for (const auto &[value, expectVal]: UNION_NUM_STR_RES_TEST_PLAN_RES) {
        modifier_->setLetterSpacing(node_, &value);
        checkVal = GetStringAttribute(node_, letterSpacingAttr);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setContentTypeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setContentType
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setContentTypeTest, TestSize.Level1)
{
    const std::string PROP_NAME("contentType");
    ASSERT_NE(modifier_->setContentType, nullptr);
    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "TextContentType.UNSPECIFIED");
    typedef std::pair<Ark_ContentType, std::string> TypeTestStep;
    const std::vector<TypeTestStep> testPlan = {
        { ARK_CONTENT_TYPE_USER_NAME, "TextContentType.USER_NAME" },
        { ARK_CONTENT_TYPE_PASSWORD, "TextContentType.VISIBLE_PASSWORD" },
        { ARK_CONTENT_TYPE_NEW_PASSWORD, "TextContentType.NEW_PASSWORD" },
        { ARK_CONTENT_TYPE_FULL_STREET_ADDRESS, "TextContentType.FULL_STREET_ADDRESS" },
        { ARK_CONTENT_TYPE_HOUSE_NUMBER, "TextContentType.HOUSE_NUMBER" },
        { ARK_CONTENT_TYPE_DISTRICT_ADDRESS, "TextContentType.DISTRICT_ADDRESS" },
        { ARK_CONTENT_TYPE_CITY_ADDRESS, "TextContentType.CITY_ADDRESS" },
        { ARK_CONTENT_TYPE_PROVINCE_ADDRESS, "TextContentType.PROVINCE_ADDRESS" },
        { ARK_CONTENT_TYPE_COUNTRY_ADDRESS, "TextContentType.COUNTRY_ADDRESS" },
        { ARK_CONTENT_TYPE_PERSON_FULL_NAME, "TextContentType.PERSON_FULL_NAME" },
        { ARK_CONTENT_TYPE_PERSON_LAST_NAME, "TextContentType.PERSON_LAST_NAME" },
        { ARK_CONTENT_TYPE_PERSON_FIRST_NAME, "TextContentType.PERSON_FIRST_NAME" },
        { ARK_CONTENT_TYPE_PHONE_NUMBER, "TextContentType.PHONE_NUMBER" },
        { ARK_CONTENT_TYPE_FULL_PHONE_NUMBER, "TextContentType.FULL_PHONE_NUMBER" },
        { ARK_CONTENT_TYPE_EMAIL_ADDRESS, "TextContentType.EMAIL_ADDRESS" },
        { ARK_CONTENT_TYPE_BANK_CARD_NUMBER, "TextContentType.BANK_CARD_NUMBER" },
        { ARK_CONTENT_TYPE_ID_CARD_NUMBER, "TextContentType.ID_CARD_NUMBER" },
        { ARK_CONTENT_TYPE_NICKNAME, "TextContentType.NICKNAME" },
        { ARK_CONTENT_TYPE_DETAIL_INFO_WITHOUT_STREET, "TextContentType.DETAIL_INFO_WITHOUT_STREET" },
        { ARK_CONTENT_TYPE_FORMAT_ADDRESS, "TextContentType.FORMAT_ADDRESS" },
        { static_cast<Ark_ContentType>(10000), "TextContentType.UNSPECIFIED" }
    };
    for (const auto& [value, expectVal] : testPlan) {
        modifier_->setContentType(node_, value);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}
} // namespace OHOS::Ace::NG
