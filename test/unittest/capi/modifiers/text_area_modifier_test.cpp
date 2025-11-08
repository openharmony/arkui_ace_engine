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

#include "test/unittest/capi/stubs/friend_class_accessor.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "generated/test_fixtures.h"

#include "base/utils/string_utils.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/interfaces/native/implementation/paste_event_peer.h"
#include "core/interfaces/native/implementation/text_area_controller_peer.h"
#include "core/interfaces/native/implementation/submit_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const auto ATTRIBUTE_PLACEHOLDER_NAME = "placeholder";
const auto ATTRIBUTE_TEXT_NAME = "text";
const auto ATTRIBUTE_PLACEHOLDER_VALUE = "xxx";
const auto ATTRIBUTE_TEXT_VALUE = "yyy";
const auto ATTRIBUTE_INPUT_FILTER_NAME("inputFilter");
const auto ATTRIBUTE_TEXT_OVERFLOW_NAME = "textOverflow";
const std::u16string ERROR_TEXT = u"error_text";
const std::u16string ERROR_TEXT2 = u"error_text2";
const std::string STR_TEST_TEXT("test_text");
const std::string STR_TEST_TEXT2("test_text2");
const std::string COLOR_RED = "#FFFF0000";
const std::string COLOR_BLACK = "#FF000000";
const std::string COLOR_TRANSPARENT = "#00000000";
const auto COLOR_NAME = NamedResourceId("color_name", ResourceType::COLOR);
const auto COLOR_ID = IntResourceId(1234, ResourceType::COLOR);
const auto WRONG_COLOR_NAME = NamedResourceId("color_name", ResourceType::STRING);
const auto ATTRIBUTE_CUSTOM_KEYBOARD_AVOIDANCE_DEFAULT_VALUE = false;
const std::string TEST_CONTENT_ONE = "ContentTestOne";
const std::string TEST_CONTENT_TWO = "ContentTestTwo";
typedef std::tuple<Ark_ResourceColor, std::string> ColorTestStep;
const std::vector<ColorTestStep> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, enum Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f), COLOR_TRANSPARENT },
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
const int64_t FAKE_RES_ID(1234);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);

typedef std::tuple<Ark_Length, std::string> ArkLengthTestStep;
const std::vector<ArkLengthTestStep> ARK_LENGTH_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>("70.00px"), "70.00px" },
    { Converter::ArkValue<Ark_Length>("-2147483648.00px"), "-2147483648.00px" },
    { Converter::ArkValue<Ark_Length>("1.23px"), "1.23px" },
    { Converter::ArkValue<Ark_Length>("-5.68px"), "-5.68px" },
    { Converter::ArkValue<Ark_Length>("70.00vp"), "70.00vp" },
    { Converter::ArkValue<Ark_Length>("-2147483648.00vp"), "-2147483648.00vp" },
    { Converter::ArkValue<Ark_Length>("1.23vp"), "1.23vp" },
    { Converter::ArkValue<Ark_Length>("-5.68vp"), "-5.68vp" },
    { Converter::ArkValue<Ark_Length>("1.23px"), "1.23px" },
    { Converter::ArkValue<Ark_Length>("70.00%"), "70.00%" },
    { Converter::ArkValue<Ark_Length>("-70.00%"), "-70.00%" },
};
const std::vector<ArkLengthTestStep> ARK_LENGTH_TEST_PLAN_RES = {
    { Converter::ArkValue<Ark_Length>(FAKE_RES_ID),
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
    { CreateResourceUnion<Ark_Union_Number_String_Resource>(IntResourceId(1234, ResourceType::STRING)),
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
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Number>(Converter::ArkValue<Ark_Number>(1000)),
        "FontWeight.Normal" },
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
        "FontWeight.Bolder" },
    { Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>(Converter::ArkValue<Ark_String>("1000")),
        "FontWeight.Normal" }
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

const auto RES_CONTENT = Converter::ArkValue<Ark_String>("aa.bb.cc");
const auto RES_NAME = NamedResourceId{"res_name", ResourceType::STRING};
const Opt_Union_String_Resource OPT_UNION_RESOURCE_RESOURCE = CreateResourceUnion<Opt_Union_String_Resource>(RES_NAME);
const std::string CHECK_RESOURCE_STR("aa.bb.cc");

typedef std::pair<Opt_Union_String_Resource, std::string> UnionStringResourceTestStep;
const std::vector<UnionStringResourceTestStep> UNION_RESOURCE_STRING_PLAN = {
    { Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>(RES_CONTENT), CHECK_RESOURCE_STR },
    { OPT_UNION_RESOURCE_RESOURCE, CHECK_RESOURCE_STR }
};

typedef std::pair<Opt_Length, std::string> OptLengthTestStep;
const std::vector<OptLengthTestStep> OPT_LENGTH_TEST_PLAN = {
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

typedef std::tuple<std::string, Ark_TextOverflow, std::string> TextOverflowTestStep;
std::vector<TextOverflowTestStep> TEXT_OVERFLOW_VALID_TEST_PLAN = {
    { "ARK_TEXT_OVERFLOW_NONE", ARK_TEXT_OVERFLOW_NONE, "TextOverflow.None" },
    { "ARK_TEXT_OVERFLOW_CLIP", ARK_TEXT_OVERFLOW_CLIP, "TextOverflow.Clip" },
    { "ARK_TEXT_OVERFLOW_ELLIPSIS", ARK_TEXT_OVERFLOW_ELLIPSIS, "TextOverflow.Ellipsis" },
    { "ARK_TEXT_OVERFLOW_MARQUEE", ARK_TEXT_OVERFLOW_MARQUEE, "TextOverflow.Marquee" },
};

// events
const auto CHECK_TEXT(u"test_text");
PreviewText PREVIEW_TEXT = { .offset = 1234, .value = u"test_offset" };
const auto EMPTY_TEXT(u"");

bool g_isEditChangeTest(true);
std::u16string g_EventTestString(u"");
std::u16string g_EventErrorTestString(u"");
Ark_EnterKeyType g_EventTestKey{};
int32_t g_EventTestOffset(0);
int32_t g_startValue(0);
int32_t g_endValue(0);
float g_scrollX(0);
float g_scrollY(0);
TextDeleteDirection g_deleteDirection(TextDeleteDirection::FORWARD);
const auto CONTEXT_ID = 123;
} // namespace

namespace GeneratedModifier {
    const GENERATED_ArkUISubmitEventAccessor* GetSubmitEventAccessor();
}

class TextAreaModifierTest : public ModifierTestBase<GENERATED_ArkUITextAreaModifier,
                                 &GENERATED_ArkUINodeModifiers::getTextAreaModifier, GENERATED_ARKUI_TEXT_AREA> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TextFieldTheme>();
        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }

    std::vector<MenuItemParam> GetMenuItemParams()
    {
        std::vector<MenuItemParam> params;
        MenuOptionsParam menuOptionItemOne;
        menuOptionItemOne.content = TEST_CONTENT_ONE;
        menuOptionItemOne.action = [](const std::string&) {};
        MenuOptionsParam menuOptionItemTwo;
        menuOptionItemTwo.content = TEST_CONTENT_TWO;
        menuOptionItemTwo.action = [](const std::string&) {};
        MenuItemParam param1;
        param1.menuOptionsParam = menuOptionItemOne;
        MenuItemParam param2;
        param2.menuOptionsParam = menuOptionItemTwo;
        params.push_back(param1);
        params.push_back(param2);
        return params;
    }
};

/**
 * placeholderColorTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setPlaceholderColor
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, DISABLED_setPlaceholderColorTest, TestSize.Level1)
{
    static const std::string propName("placeholderColor");
    ASSERT_NE(modifier_->setPlaceholderColor, nullptr);

    auto checkVal = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal, COLOR_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setPlaceholderColor(node_, &value);
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("caretColor");
    ASSERT_NE(modifier_->setCaretColor, nullptr);

    auto checkVal = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal, COLOR_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setCaretColor(node_, &value);
        checkVal = GetStringAttribute(node_, propName);
    }
}

/**
 * @tc.name: setFontColorTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setFontColor
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setFontColorTest, TestSize.Level1)
{
    static const std::string propName("fontColor");
    ASSERT_NE(modifier_->setFontColor, nullptr);

    auto checkVal = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal, COLOR_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setFontColor(node_, &value);
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("selectedBackgroundColor");
    ASSERT_NE(modifier_->setSelectedBackgroundColor, nullptr);

    auto checkVal = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal, COLOR_BLACK);

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        modifier_->setSelectedBackgroundColor(node_, &value);
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("enablePreviewText");
    ASSERT_NE(modifier_->setEnablePreviewText, nullptr);

    auto checkVal = GetAttrValue<bool>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, true);

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        modifier_->setEnablePreviewText(node_, value);
        checkVal = GetAttrValue<bool>(GetJsonValue(node_), propName);
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
    static const std::string propName("enableAutoFill");
    ASSERT_NE(modifier_->setEnableAutoFill, nullptr);

    auto checkVal = GetAttrValue<bool>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, true);

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        modifier_->setEnableAutoFill(node_, value);
        checkVal = GetAttrValue<bool>(GetJsonValue(node_), propName);
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
    static const std::string propName("selectionMenuHidden");
    ASSERT_NE(modifier_->setSelectionMenuHidden, nullptr);

    auto checkVal = GetAttrValue<bool>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, false);

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        modifier_->setSelectionMenuHidden(node_, value);
        checkVal = GetAttrValue<bool>(GetJsonValue(node_), propName);
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
    static const std::string propName("enableKeyboardOnFocus");
    ASSERT_NE(modifier_->setEnableKeyboardOnFocus, nullptr);

    auto checkVal = GetAttrValue<bool>(GetJsonValue(node_), propName);
    EXPECT_EQ(checkVal, true);

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        modifier_->setEnableKeyboardOnFocus(node_, value);
        checkVal = GetAttrValue<bool>(GetJsonValue(node_), propName);
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
    static const std::string propName("textIndent");
    ASSERT_NE(modifier_->setTextIndent, nullptr);

    auto checkVal = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal, DEFAULT_TEXT_INDENT);

    for (const auto& [value, expectVal] : ARK_LENGTH_TEST_PLAN) {
        modifier_->setTextIndent(node_, &value);
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("caretStyle");
    static const std::string PROP_COLOR("color");
    static const std::string PROP_WIDTH("width");
    ASSERT_NE(modifier_->setCaretStyle, nullptr);

    auto value = GetStringAttribute(node_, propName);
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
            Ark_CaretStyle arkCaretStyle = {
                .color = Converter::ArkValue<Opt_ResourceColor>(std::get<0>(testColor)),
                .width = Converter::ArkValue<Opt_Length>(std::get<0>(testLength)),
            };
            CheckCaretValue caretValue = { std::get<1>(testColor), std::get<1>(testLength) };
            auto length = std::get<0>(testLength).value;
            auto unit = std::get<0>(testLength).unit;
            if ((LessNotEqual(length, 0.0f) || (unit == static_cast<int32_t>(DimensionUnit::PERCENT)))) {
                caretValue = { std::get<1>(testColor), DEFAULT_CARET_WIDTH };
            }
            TestCaretStyle testCaretStyle = { arkCaretStyle, caretValue };
            testPlanCaretStyle.push_back(testCaretStyle);
        }
    }

    for (auto caretStyle : testPlanCaretStyle) {
        modifier_->setCaretStyle(node_, &caretStyle.first);
        value = GetStringAttribute(node_, propName);
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
    auto onEditChange =
        [](Ark_Int32 nodeId, const Ark_Boolean isEditChange) {
            g_isEditChangeTest = isEditChange;
        };
    auto func = Converter::ArkValue<Callback_Boolean_Void>(onEditChange, CONTEXT_ID);
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
 * @tc.name: setOnSubmit0Test
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnSubmit0.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnSubmit0Test, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto onSubmit0 =
        [](Ark_Int32 nodeId, const Ark_EnterKeyType enterKey) {
            g_EventTestKey = enterKey;
        };
    auto func = Converter::ArkValue<Callback_EnterKeyType_Void>(onSubmit0, CONTEXT_ID);
    modifier_->setOnSubmit0(node_, &func);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    ASSERT_NE(eventHub, nullptr);
    TextFieldCommonEvent event;
    eventHub->FireOnSubmit(111, event);
    EXPECT_EQ(g_EventTestKey, -1);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEXT, event);
    EXPECT_EQ(g_EventTestKey, 5);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_GO, event);
    EXPECT_EQ(g_EventTestKey, 2);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_SEARCH, event);
    EXPECT_EQ(g_EventTestKey, 3);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_SEND, event);
    EXPECT_EQ(g_EventTestKey, 4);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEXT, event);
    EXPECT_EQ(g_EventTestKey, 5);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_DONE, event);
    EXPECT_EQ(g_EventTestKey, 6);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_PREVIOUS, event);
    EXPECT_EQ(g_EventTestKey, 7);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEW_LINE, event);
    EXPECT_EQ(g_EventTestKey, 8);
}

/**
 * @tc.name: setOnSubmit1Test
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnSubmit1.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnSubmit1Test, TestSize.Level1)
{
    static const int expectedResId = 123;
    static const std::u16string testValue(u"string text");
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto onSubmitFunc = [](
        Ark_VMContext, Ark_Int32 resourceId, const Ark_EnterKeyType enterKeyType, const Opt_SubmitEvent event
    ) {
        auto eventValue = Converter::OptConvert<Ark_SubmitEvent>(event);
        ASSERT_TRUE(eventValue);
        auto peer = eventValue.value();
        ASSERT_NE(peer, nullptr);
        auto submitEventInfo = peer->GetEventInfo();
        ASSERT_NE(submitEventInfo, nullptr);
        EXPECT_EQ(submitEventInfo->GetText(), testValue);
        GeneratedModifier::GetSubmitEventAccessor()->destroyPeer(peer);
        EXPECT_EQ(resourceId, expectedResId);
        g_EventTestKey = enterKeyType;
    };

    auto func = Converter::ArkValue<TextAreaSubmitCallback>(onSubmitFunc, expectedResId);
    modifier_->setOnSubmit1(node_, &func);
    TextFieldCommonEvent event;
    event.SetText(testValue);
    eventHub->FireOnSubmit(111, event);
    EXPECT_EQ(g_EventTestKey, -1);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEXT, event);
    EXPECT_EQ(g_EventTestKey, 5);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_GO, event);
    EXPECT_EQ(g_EventTestKey, 2);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_SEARCH, event);
    EXPECT_EQ(g_EventTestKey, 3);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_SEND, event);
    EXPECT_EQ(g_EventTestKey, 4);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEXT, event);
    EXPECT_EQ(g_EventTestKey, 5);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_DONE, event);
    EXPECT_EQ(g_EventTestKey, 6);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_PREVIOUS, event);
    EXPECT_EQ(g_EventTestKey, 7);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEW_LINE, event);
    EXPECT_EQ(g_EventTestKey, 8);
}

/**
 * @tc.name: setOnChangeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnChangeTest, TestSize.Level1)
{
    g_EventTestString = u"";
    g_EventTestOffset = 0;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    auto onChange =
        [](Ark_Int32 nodeId, Ark_String value, Opt_PreviewText previewText, Opt_TextChangeOptions options) {
            g_EventTestOffset = PREVIEW_TEXT.offset;
            g_EventTestString.append(CHECK_TEXT).append(PREVIEW_TEXT.value);
        };
    auto func = Converter::ArkValue<EditableTextOnChangeCallback>(onChange, CONTEXT_ID);
    modifier_->setOnChange(node_, &func);
    textFieldEventHub->FireOnChange({CHECK_TEXT, PREVIEW_TEXT});
    std::u16string checkString = CHECK_TEXT;
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
    static const std::string propName("maxLength");
    ASSERT_NE(modifier_->setMaxLength, nullptr);
    auto checkVal = GetStringAttribute(node_, propName);
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
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("minFontSize");
    ASSERT_NE(modifier_->setMinFontSize, nullptr);

    auto checkVal = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal, "0.00px");

    for (const auto& [value, expectVal] : UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setMinFontSize(node_, &value);
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("maxFontSize");
    ASSERT_NE(modifier_->setMaxFontSize, nullptr);

    auto checkVal = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal, "0.00px");

    for (const auto& [value, expectVal] : UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setMaxFontSize(node_, &value);
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("lineHeight");
    ASSERT_NE(modifier_->setLineHeight, nullptr);

    auto checkVal = GetStringAttribute(node_, propName);
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
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("textAlign");
    ASSERT_NE(modifier_->setTextAlign, nullptr);

    auto checkVal = GetStringAttribute(node_, propName);
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
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("enterKeyType");
    ASSERT_NE(modifier_->setEnterKeyType, nullptr);

    auto checkVal = GetStringAttribute(node_, propName);
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
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("enterKeyType");
    ASSERT_NE(modifier_->setEnterKeyType, nullptr);
    ASSERT_NE(modifier_->setMaxLines, nullptr);
    auto maxLines = Converter::ArkValue<Ark_Number>(1);
    modifier_->setMaxLines(node_, const_cast<Ark_Number*>(&maxLines));

    auto checkVal = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal, "EnterKeyType.NEW_LINE");

    // Additional conditions
    TextFieldModelNG::SetMaxLines(reinterpret_cast<FrameNode*>(node_), 1);
    checkVal = GetStringAttribute(node_, "maxLines");
    EXPECT_EQ(checkVal, "1");

    checkVal = GetStringAttribute(node_, propName);
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
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("maxLines");
    static const std::string DEFAULT_MAX_VIEW_LINES("3");
    ASSERT_NE(modifier_->setMaxLines, nullptr);

    auto checkVal = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal, "INF");

    TextFieldModelNG::SetInputStyle(reinterpret_cast<FrameNode*>(node_), InputStyle::INLINE);
    checkVal = GetStringAttribute(node_, propName);
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
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("type");
    ASSERT_NE(modifier_->setType, nullptr);
    auto checkVal = GetStringAttribute(node_, propName);
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
        checkVal = GetStringAttribute(node_, propName);
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
    static const std::string propName("fontFeature");
    ASSERT_NE(modifier_->setFontFeature, nullptr);
    std::string checkVal = "";
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> array = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, propName);
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
        checkVal = GetStringAttribute(node_, propName);
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
    static const Ark_Int32 expectedResId = 123;
    auto onWillInsertHandler = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_InsertValue data,
        const Callback_Boolean_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Converter::Convert<std::u16string>(data.insertValue), CHECK_TEXT);
        auto result = Converter::Convert<int32_t>(data.insertOffset) > 0;
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_Boolean>(result));
    };
    auto arkFunc = Converter::ArkValue<Callback_InsertValue_Boolean>(nullptr, onWillInsertHandler, expectedResId);
    modifier_->setOnWillInsert(node_, &arkFunc);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);

    {
        InsertValueInfo checkValue = { .insertOffset = AINT32_POS, .insertValue = CHECK_TEXT };
        auto returnVal = textFieldEventHub->FireOnWillInsertValueEvent(checkValue);
        EXPECT_TRUE(returnVal);
    }
    {
        InsertValueInfo checkValue = { .insertOffset = AINT32_NEG, .insertValue = CHECK_TEXT };
        auto returnVal = textFieldEventHub->FireOnWillInsertValueEvent(checkValue);
        EXPECT_FALSE(returnVal);
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
    g_EventTestString = u"";
    g_EventTestOffset = 0;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    InsertValueInfo checkValueDefault;
    textFieldEventHub->FireOnDidInsertValueEvent(checkValueDefault);
    EXPECT_EQ(g_EventTestString, EMPTY_TEXT);
    EXPECT_EQ(g_EventTestOffset, 0);
    auto onDidInsert =
        [](Ark_Int32 nodeId, const Ark_InsertValue data) {
            g_EventTestString = Converter::Convert<std::u16string>(data.insertValue);
            g_EventTestOffset = Converter::Convert<int32_t>(data.insertOffset);
        };
    auto func = Converter::ArkValue<Callback_InsertValue_Void>(onDidInsert, CONTEXT_ID);
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
    static const Ark_Int32 expectedResId = 123;
    static const Ark_Int32 expectedOffset = AINT32_POS;

    ASSERT_NE(modifier_->setOnWillDelete, nullptr);
    auto onWillDeleteHandler = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_DeleteValue data, const Callback_Boolean_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Converter::Convert<std::u16string>(data.deleteValue), CHECK_TEXT);
        EXPECT_EQ(Converter::Convert<int32_t>(data.deleteOffset), expectedOffset);
        auto willDeleteDirection = Converter::OptConvert<TextDeleteDirection>(data.direction);
        auto result = willDeleteDirection == TextDeleteDirection::FORWARD;
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_Boolean>(result));
    };
    auto arkFunc = Converter::ArkValue<Callback_DeleteValue_Boolean>(nullptr, onWillDeleteHandler, expectedResId);
    modifier_->setOnWillDelete(node_, &arkFunc);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);
    DeleteValueInfo checkValueDefault;

    {
        DeleteValueInfo checkValue = {
            .deleteOffset = expectedOffset, .deleteValue = CHECK_TEXT, .direction = TextDeleteDirection::FORWARD
        };
        auto checkVal = textFieldEventHub->FireOnWillDeleteEvent(checkValue);
        EXPECT_TRUE(checkVal);
    }
    {
        DeleteValueInfo checkValue = {
            .deleteOffset = expectedOffset, .deleteValue = CHECK_TEXT, .direction = TextDeleteDirection::BACKWARD
        };
        auto checkVal = textFieldEventHub->FireOnWillDeleteEvent(checkValue);
        EXPECT_FALSE(checkVal);
    }
}

/**
 * @tc.name: setOnDidDeleteTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnDidlDelete.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnDidDeleteTest, TestSize.Level1)
{
    g_EventTestString = u"";
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
    auto onDidDelete =
        [](Ark_Int32 nodeId, const Ark_DeleteValue data) {
            g_EventTestString = Converter::Convert<std::u16string>(data.deleteValue);
            g_EventTestOffset = Converter::Convert<int32_t>(data.deleteOffset);
            auto didDeleteDirection = Converter::OptConvert<TextDeleteDirection>(data.direction);
            if (didDeleteDirection) {
                g_deleteDirection = didDeleteDirection.value();
            }
        };
    auto func = Converter::ArkValue<Callback_DeleteValue_Void>(onDidDelete, CONTEXT_ID);
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
    auto onTextSelectionChange =
        [](Ark_Int32 nodeId, Ark_Number selectionStart, Ark_Number selectionEnd) {
            g_startValue = Converter::Convert<int32_t>(selectionStart);
            g_endValue = Converter::Convert<int32_t>(selectionEnd);
        };
    auto func = Converter::ArkValue<Callback_Number_Number_Void>(onTextSelectionChange, CONTEXT_ID);
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
    auto onCopy =
        [](Ark_Int32 nodeId, Ark_String value) {
            auto textString = Converter::Convert<std::u16string>(value);
            g_EventTestString = textString;
        };
    auto func = Converter::ArkValue<Callback_String_Void>(onCopy, CONTEXT_ID);
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
    auto onCut =
        [](Ark_Int32 nodeId, Ark_String value) {
            g_EventTestString = Converter::Convert<std::u16string>(value);
        };
    auto func = Converter::ArkValue<Callback_String_Void>(onCut, CONTEXT_ID);
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
    auto onContentScroll =
        [](Ark_Int32 nodeId, Ark_Number totalOffsetX, Ark_Number totalOffsetY) {
            g_scrollX = Converter::Convert<float>(totalOffsetX);
            g_scrollY = Converter::Convert<float>(totalOffsetY);
        };
    auto func = Converter::ArkValue<Callback_Number_Number_Void>(onContentScroll, CONTEXT_ID);
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
HWTEST_F(TextAreaModifierTest, setCopyOptionTest, TestSize.Level1)
{
    static const std::string propName("copyOption");
    ASSERT_NE(modifier_->setCopyOption, nullptr);

    typedef std::pair<Ark_CopyOptions, std::string> CopyOptionTestStep;
    const std::vector<CopyOptionTestStep> copyOptionTestPlan = {
        { ARK_COPY_OPTIONS_NONE, "CopyOptions.None" },
        { ARK_COPY_OPTIONS_IN_APP, "CopyOptions.InApp" },
        { static_cast<Ark_CopyOptions>(4), "CopyOptions.Local" },
        { ARK_COPY_OPTIONS_CROSS_DEVICE, "CopyOptions.Distributed" },
        { ARK_COPY_OPTIONS_LOCAL_DEVICE, "CopyOptions.Local" }
    };

    auto checkVal = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal, "CopyOptions.Local");
    for (const auto& [value, expectVal] : copyOptionTestPlan) {
        modifier_->setCopyOption(node_, value);
        checkVal = GetStringAttribute(node_, propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setInputFilterTestValidValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setInputFilter
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setInputFilterTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setInputFilter, nullptr);
    struct CheckEvent {
        int32_t nodeId;
        std::u16string error;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onErrorChange = [](Ark_Int32 nodeId, const Ark_String error) {
        checkEvent = CheckEvent{
            .nodeId = nodeId,
            .error = Converter::Convert<std::u16string>(error)
        };
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    Callback_String_Void callBackValue = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onErrorChange
    };
    auto optCallbackValue = Converter::ArkValue<Opt_Callback_String_Void>(callBackValue);
    Converter::ConvContext ctx;
    auto sendString = Converter::ArkValue<Ark_String>(STR_TEST_TEXT, &ctx);
    auto sendResource = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(sendString);
    sendString = Converter::ArkValue<Ark_String>(STR_TEST_TEXT2, &ctx);
    auto sendResource2 = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(sendString);

    modifier_->setInputFilter(node_, &sendResource, &optCallbackValue);
    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnInputFilterError(ERROR_TEXT);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->error, ERROR_TEXT);
    auto attrValue = GetStringAttribute(node_, ATTRIBUTE_INPUT_FILTER_NAME);
    EXPECT_EQ(attrValue, STR_TEST_TEXT);

    checkEvent.reset();
    modifier_->setInputFilter(node_, &sendResource2, &optCallbackValue);
    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnInputFilterError(ERROR_TEXT2);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->error, ERROR_TEXT2);
    attrValue = GetStringAttribute(node_, ATTRIBUTE_INPUT_FILTER_NAME);
    EXPECT_EQ(attrValue, STR_TEST_TEXT2);
}

/**
 * @tc.name: setInputFilterTestInvalidValues
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setInputFilter
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setInputFilterTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setInputFilter, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    auto optCallbackValue = Converter::ArkValue<Opt_Callback_String_Void>();
    Converter::ConvContext ctx;
    auto sendString = Converter::ArkValue<Ark_String>(STR_TEST_TEXT, &ctx);
    auto sendResource = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(sendString);
    sendString = Converter::ArkValue<Ark_String>(STR_TEST_TEXT2, &ctx);
    auto sendResource2 = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(sendString);

    modifier_->setInputFilter(node_, &sendResource, &optCallbackValue);
    eventHub->FireOnInputFilterError(ERROR_TEXT);
    auto attrValue = GetStringAttribute(node_, ATTRIBUTE_INPUT_FILTER_NAME);
    EXPECT_EQ(attrValue, STR_TEST_TEXT);

    modifier_->setInputFilter(node_, &sendResource2, nullptr);
    eventHub->FireOnInputFilterError(ERROR_TEXT);
    attrValue = GetStringAttribute(node_, ATTRIBUTE_INPUT_FILTER_NAME);
    EXPECT_EQ(attrValue, STR_TEST_TEXT2);
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
 * @tc.name: setPlaceholderFontTest4
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setPlaceholderFont.
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setPlaceholderFontTest4, TestSize.Level1)
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
                Ark_TextDecorationOptions options = {
                    .color = Converter::ArkValue<Opt_ResourceColor>(decorationColor),
                    .type = decorationType,
                    .style = Converter::ArkValue<Opt_TextDecorationStyle>(decorationStyle),
                };
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
 * @tc.name: setContentTypeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setContentType
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setContentTypeTest, TestSize.Level1)
{
    const std::string propName("contentType");
    ASSERT_NE(modifier_->setContentType, nullptr);
    auto checkVal = GetStringAttribute(node_, propName);
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
        { ARK_CONTENT_TYPE_PASSPORT_NUMBER, "TextContentType.PASSPORT_NUMBER" },
        { ARK_CONTENT_TYPE_VALIDITY, "TextContentType.VALIDITY" },
        { ARK_CONTENT_TYPE_ISSUE_AT, "TextContentType.ISSUE_AT" },
        { ARK_CONTENT_TYPE_ORGANIZATION, "TextContentType.ORGANIZATION" },
        { ARK_CONTENT_TYPE_TAX_ID, "TextContentType.TAX_ID" },
        { ARK_CONTENT_TYPE_ADDRESS_CITY_AND_STATE, "TextContentType.ADDRESS_CITY_AND_STATE" },
        { ARK_CONTENT_TYPE_FLIGHT_NUMBER, "TextContentType.FLIGHT_NUMBER" },
        { ARK_CONTENT_TYPE_LICENSE_NUMBER, "TextContentType.LICENSE_NUMBER" },
        { ARK_CONTENT_TYPE_LICENSE_FILE_NUMBER, "TextContentType.LICENSE_FILE_NUMBER" },
        { ARK_CONTENT_TYPE_LICENSE_PLATE, "TextContentType.LICENSE_PLATE" },
        { ARK_CONTENT_TYPE_ENGINE_NUMBER, "TextContentType.ENGINE_NUMBER" },
        { ARK_CONTENT_TYPE_LICENSE_CHASSIS_NUMBER, "TextContentType.LICENSE_CHASSIS_NUMBER" },
        { static_cast<Ark_ContentType>(10000), "TextContentType.UNSPECIFIED" }
    };
    for (const auto& [value, expectVal] : testPlan) {
        modifier_->setContentType(node_, value);
        checkVal = GetStringAttribute(node_, propName);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setTextAreaOptionsTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setTextAreaOptions
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTextAreaOptionsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextAreaOptions, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setTextAreaOptions(node_, nullptr);
    auto optionsUndef = Converter::ArkValue<Opt_TextAreaOptions>();
    modifier_->setTextAreaOptions(node_, &optionsUndef);

    Ark_TextAreaOptions optionsInvalid;
    optionsInvalid.text = Converter::ArkValue<Opt_ResourceStr>();
    optionsInvalid.placeholder = Converter::ArkValue<Opt_ResourceStr>();
    optionsInvalid.controller = Converter::ArkValue<Opt_TextAreaController>();
    auto optionsInvalidDef = Converter::ArkValue<Opt_TextAreaOptions>();
    modifier_->setTextAreaOptions(node_, &optionsInvalidDef);

    // set the invoke checker to the internal controller
    bool checkInvoke = false;
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    std::optional<std::u16string> placeholder;
    std::optional<std::u16string> text;
    auto internalController = TextFieldModelNG::GetController(frameNode, placeholder, text);
    ASSERT_NE(internalController, nullptr);
    internalController->SetStopEditing([&checkInvoke]() {
        checkInvoke = true;
    });

    // create the external TextAreaController peer and attach modifier to it
    TextAreaControllerPeer peer;
    Ark_TextAreaOptions options;
    options.text = Converter::ArkUnion<Opt_ResourceStr, Ark_String>(ATTRIBUTE_TEXT_VALUE);
    options.placeholder = Converter::ArkUnion<Opt_ResourceStr, Ark_String>(ATTRIBUTE_PLACEHOLDER_VALUE);
    options.controller = Converter::ArkValue<Opt_TextAreaController>(&peer);
    auto optionsDef = Converter::ArkValue<Opt_TextAreaOptions>(options);
    modifier_->setTextAreaOptions(node_, &optionsDef);

    // check initial state of invoke checker
    EXPECT_FALSE(checkInvoke);

    // simulate the action from the external peer
    peer.GetController()->StopEditing();

    // check the expected state of invoke checker
    EXPECT_TRUE(checkInvoke);

    // check the expected "placeholder" and "text" attribute values
    auto checkVal = GetStringAttribute(node_, ATTRIBUTE_PLACEHOLDER_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_PLACEHOLDER_VALUE);
    checkVal = GetStringAttribute(node_, ATTRIBUTE_TEXT_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_TEXT_VALUE);
}

/**
 * @tc.name: setTextAreaOptionsTest2
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setTextAreaOptions
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTextAreaOptionsTest2, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextAreaOptions, nullptr);
    Opt_ResourceStr initValue =
        Converter::ArkUnion<Opt_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0]));
    auto checkValue = [this, &initValue](const std::string& input,
            const std::string& expectedStr, const Opt_ResourceStr& value) {
        Ark_TextAreaOptions options;
        TextAreaControllerPeer peer;
        Opt_ResourceStr inputValue = initValue;
        inputValue = value;
        options.text = inputValue;
        options.placeholder = inputValue;
        options.controller = Converter::ArkValue<Opt_TextAreaController>(&peer);
        auto optionsDef = Converter::ArkValue<Opt_TextAreaOptions>(options);
        modifier_->setTextAreaOptions(node_, &optionsDef);

        auto jsonValue = GetJsonValue(node_);
        ASSERT_NE(jsonValue, nullptr);
        auto checkVal = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
        EXPECT_EQ(checkVal, expectedStr)
            << "Input value is: " << input << ", method: setTextAreaOptions, attribute: "
            << ATTRIBUTE_PLACEHOLDER_NAME;
        checkVal = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_NAME);
        EXPECT_EQ(checkVal, expectedStr)
            << "Input value is: " << input << ", method: setTextAreaOptions, attribute: "
            << ATTRIBUTE_TEXT_NAME;
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, Converter::ArkUnion<Opt_ResourceStr, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, Converter::ArkUnion<Opt_ResourceStr, Ark_String>(value));
    }
}

/**
 * @tc.name: setOnPasteTestCallEvent
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnPaste
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnPasteTestCallEvent, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnPaste, nullptr);
    TextCommonEvent event;
    const std::u16string testString = u"testText";
    struct CheckEvent {
        int32_t resourceId;
        std::u16string content;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .content = Converter::Convert<std::u16string>(content)
        };
        if (event) {
            event->HandlePreventDefault();
        }
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    auto arkCallback = Converter::ArkValue<Callback_String_PasteEvent_Void>(testCallback, frameNode->GetId());
    ASSERT_NE(eventHub, nullptr);
    modifier_->setOnPaste(node_, &arkCallback);
    EXPECT_FALSE(checkEvent);
    EXPECT_FALSE(event.IsPreventDefault());
    eventHub->FireOnPasteWithEvent(testString, event);
    ASSERT_TRUE(checkEvent);
    EXPECT_TRUE(event.IsPreventDefault());
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
    EXPECT_EQ(checkEvent->content, testString);
}

/**
 * @tc.name: setOnPasteTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextAreaModifier.setOnPaste
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnPasteTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnPaste, nullptr);
    TextCommonEvent event;
    const std::u16string testString = u"testText";
    struct CheckEvent {
        int32_t resourceId;
        std::u16string content;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .content = Converter::Convert<std::u16string>(content)
        };
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    auto arkCallback = Converter::ArkValue<Callback_String_PasteEvent_Void>(testCallback, frameNode->GetId());
    ASSERT_NE(eventHub, nullptr);
    modifier_->setOnPaste(node_, &arkCallback);
    EXPECT_FALSE(checkEvent);
    EXPECT_FALSE(event.IsPreventDefault());
    eventHub->FireOnPasteWithEvent(testString, event);
    ASSERT_TRUE(checkEvent);
    EXPECT_FALSE(event.IsPreventDefault());
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
    EXPECT_EQ(checkEvent->content, testString);
}

/*
 * @tc.name: setTextOverflowTestTextOverflowValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setTextOverflowTestTextOverflowValidValues, TestSize.Level1)
{
    Ark_TextOverflow initValueTextOverflow;

    // Initial setup
    initValueTextOverflow = std::get<1>(TEXT_OVERFLOW_VALID_TEST_PLAN[0]);

    auto checkValue = [this, &initValueTextOverflow](
                          const std::string& input, const std::string& expectedStr, const Ark_TextOverflow& value) {
        Ark_TextOverflow inputValueTextOverflow = initValueTextOverflow;

        inputValueTextOverflow = value;
        modifier_->setTextOverflow(node_, inputValueTextOverflow);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setTextOverflow, attribute: textOverflow";
    };

    for (auto& [input, value, expected] : TEXT_OVERFLOW_VALID_TEST_PLAN) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setCustomKeyboardDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCustomKeyboardDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetCustomKeyboardOption(), ATTRIBUTE_CUSTOM_KEYBOARD_AVOIDANCE_DEFAULT_VALUE);
}

/*
 * @tc.name: setCustomKeyboardValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setCustomKeyboardValidValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    static auto expectedCustomNode = CreateNode();
    ASSERT_NE(expectedCustomNode, nullptr);
    static const FrameNode* expectedParentNode = frameNode;
    static FrameNode* actualParentNode = nullptr;
    static const CustomNodeBuilder customBuilder = {
        .call = [](const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            actualParentNode = reinterpret_cast<FrameNode*>(parentNode);
            CallbackHelper(continuation).Invoke(reinterpret_cast<Ark_NativePointer>(expectedCustomNode));
        }
    };
    KeyboardOptions keyboardOptions = { .supportAvoidance = true };
    auto optKeyboardOptions = Converter::ArkValue<Opt_KeyboardOptions>(keyboardOptions);

    modifier_->setCustomKeyboard(node_, &customBuilder, &optKeyboardOptions);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_EQ(actualParentNode, expectedParentNode);
    ASSERT_TRUE(pattern->GetCustomKeyboardOption());

    keyboardOptions = { .supportAvoidance = false };
    optKeyboardOptions = Converter::ArkValue<Opt_KeyboardOptions>(keyboardOptions);
    modifier_->setCustomKeyboard(node_, &customBuilder, &optKeyboardOptions);
    ASSERT_EQ(actualParentNode, expectedParentNode);
    ASSERT_FALSE(pattern->GetCustomKeyboardOption());
}

/*
 * @tc.name: setOnChangeEventTextImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setOnChangeEventTextImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<std::string> value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_ResourceStr parameter) {
        checkEvent = CheckEvent{
            .nodeId = resourceId,
            .value = Converter::OptConvert<std::string>(parameter)
        };
    };

    Callback_ResourceStr_Void arkCallback = Converter::ArkValue<Callback_ResourceStr_Void>(checkCallback, contextId);

    modifier_->set_onChangeEvent_text(node_, &arkCallback);

    PreviewText previewText {.offset = -1, .value = u""};
    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnChange({u"test", previewText});
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    ASSERT_EQ(checkEvent->value.has_value(), true);
    EXPECT_EQ(checkEvent->value.value(), "test");
    eventHub->FireOnChange({u"test_2", previewText});
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    ASSERT_EQ(checkEvent->value.has_value(), true);
    EXPECT_EQ(checkEvent->value.value(), "test_2");
}

/**
 * @tc.name: setEditMenuOptionsTest
 * @tc.desc: setEditMenuOptions test
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaModifierTest, setEditMenuOptionsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEditMenuOptions, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t testID = 323;
    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testOnCreateMenuCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Array_TextMenuItem menuItems, const Callback_Array_TextMenuItem_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        CallbackHelper(continuation).Invoke(menuItems);
    };
    auto arkCreateCallback = Converter::ArkValue<
        AsyncCallback_Array_TextMenuItem_Array_TextMenuItem>(testOnCreateMenuCallback, testID);

    auto testOnMenuItemClickCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_TextMenuItem menuItem, const Ark_TextRange range, const Callback_Boolean_Void continuation) {
        auto item = Converter::OptConvert<MenuOptionsParam>(menuItem);
        ASSERT_TRUE(item.has_value());
        ASSERT_TRUE(item->content.has_value());
        CallbackHelper(continuation).Invoke(Converter::ArkValue<Ark_Boolean>(*item->content == TEST_CONTENT_ONE));
    };
    auto arkClickCallback = Converter::ArkValue<
        AsyncCallback_TextMenuItem_TextRange_Boolean>(testOnMenuItemClickCallback, testID);

    Ark_EditMenuOptions options {
        .onCreateMenu = arkCreateCallback,
        .onMenuItemClick = arkClickCallback
    };

    SelectOverlayInfo selectOverlayInfo;
    auto params = GetMenuItemParams();
    FriendClassAccessor::OnUpdateOnCreateMenuCallback(selectOverlayInfo, pattern);
    EXPECT_TRUE(selectOverlayInfo.onCreateCallback.onCreateMenuCallback == nullptr);
    modifier_->setEditMenuOptions(node_, &options);
    FriendClassAccessor::OnUpdateOnCreateMenuCallback(selectOverlayInfo, pattern);
    ASSERT_NE(selectOverlayInfo.onCreateCallback.onCreateMenuCallback, nullptr);
    selectOverlayInfo.onCreateCallback.onCreateMenuCallback(params);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, testID);

    ASSERT_NE(selectOverlayInfo.onCreateCallback.onMenuItemClick, nullptr);
    EXPECT_TRUE(selectOverlayInfo.onCreateCallback.onMenuItemClick(params[0]));
    EXPECT_FALSE(selectOverlayInfo.onCreateCallback.onMenuItemClick(params[1]));
}
} // namespace OHOS::Ace::NG
