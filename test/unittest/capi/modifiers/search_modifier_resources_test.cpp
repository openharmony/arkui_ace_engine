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
// attrs
// const auto BUTTON_OPTIONS_ATTR("searchButtonOption");
// const auto BUTTON_OPTIONS_COLOR_ATTR("fontColor");
// const auto BUTTON_OPTIONS_SIZE_ATTR("fontSize");
const auto CANCEL_BUTTON_ATTR("cancelButton");
const auto CANCEL_BUTTON_ICON_ATTR("icon");
const auto CANCEL_BUTTON_ICON_COLOR_ATTR("color");
const auto CANCEL_BUTTON_ICON_SRC_ATTR("src");
// const auto DECORATION_ATTRS("decoration");
// const auto DECORATION_TYPE_ATTR("type");
// const auto DECORATION_STYLE_ATTR("style");
// const auto DECORATION_COLOR_ATTR("color");
const auto FONT_COLOR_ATTR("fontColor");
const auto LETTER_SPACING_ATTR("letterSpacing");
// const auto LINE_HEIGHT_ATTR("lineHeight");
const auto MAX_FONT_SIZE_ATTR("maxFontSize");
const auto MIN_FONT_SIZE_ATTR("minFontSize");
// const auto PLACEHOLDER_FONT_ATTRS("placeholderFont");
// const auto PLACEHOLDER_FONT_SIZE("size");
// const auto PLACEHOLDER_FONT_FAMILY("fontFamily");
// const auto PLACEHOLDER_FONT_WEIGHT_ENUM("fontWeight");
// const auto PLACEHOLDER_FONT_WEIGHT("weight");
// const auto PLACEHOLDER_FONT_STYLE("style");
const auto PLACEHOLDER_COLOR_ATTR("placeholderColor");
// const auto SEARCH_ICON_ATTR("searchIcon");
// const auto SEARCH_ICON_SRC_ATTR("src");
// const auto SEARCH_ICON_COLOR_ATTR("color");
// const auto SEARCH_ICON_SIZE_ATTR("size");
const auto SELECTED_BACKGROUND_COLOR_ATTR("selectedBackgroundColor");
// const auto TEXT_FONT_ATTRS("textFont");
// const auto TEXT_FONT_SIZE_ATTR("fontSize");
// const auto TEXT_FONT_FAMILY_ATTR("fontFamily");
// const auto TEXT_FONT_WEIGHT_ATTR("fontWeight");
// const auto TEXT_FONT_STYLE_ATTR("fontStyle");

// length values
// const Ark_Int32 AINT32_POS(1234);
// const Ark_Int32 AINT32_NEG(INT_MIN);
// const Ark_Float32 AFLT32_POS(1.234f);
// const Ark_Float32 AFLT32_NEG(-5.6789f);
// const auto ALEN_PX_POS = ArkValue<Ark_Length>(AINT32_POS);
// const auto ALEN_PX_NEG = ArkValue<Ark_Length>(AINT32_NEG);
// const auto ALEN_VP_POS = ArkValue<Ark_Length>(AFLT32_POS);
// const auto ALEN_VP_NEG = ArkValue<Ark_Length>(AFLT32_NEG);
// const auto OPT_LEN_PX_POS = ArkValue<Opt_Length>(AINT32_POS);
// const auto OPT_LEN_PX_NEG = ArkValue<Opt_Length>(AINT32_NEG);
// const auto OPT_LEN_VP_POS = ArkValue<Opt_Length>(AFLT32_POS);
// const auto OPT_LEN_VP_NEG = ArkValue<Opt_Length>(AFLT32_NEG);

// default length
// const std::string CHECK_DEFAULT_PX("0.00px");
// const std::string CHECK_DEFAULT_VP("0.00vp");

// check length
// const std::string CHECK_POSITIVE_VALUE_INT("1234.00px");
// const std::string CHECK_NEGATIVE_VALUE_INT("-2147483648.00px");
// const std::string CHECK_POSITIVE_VALUE_FLOAT("1.23vp");
// const std::string CHECK_POSITIVE_VALUE_FLOAT_PX("1.23px");
// const std::string CHECK_NEGATIVE_VALUE_FLOAT("-5.68vp");

// check text
// const auto CHECK_TEXT("test_text");
// PreviewText PREVIEW_TEXT = { .offset = 1234, .value = "test_offset" };
// const auto EMPTY_TEXT("");

// // check resource
// const Ark_String STR_NAME = ArkValue<Ark_String>("min_font_size");
// const std::string CHECK_RESOURCE_STR("aa.bb.cc");

// test types
// typedef std::pair<Ark_Length, std::string> LengthTest;
// typedef std::pair<Opt_Length, std::string> OptLengthTest;
// typedef std::pair<Opt_ResourceColor, std::string> ColorTest;
// typedef std::pair<std::string, std::string> CheckSearchButtonOptions;
// typedef std::pair<Opt_SearchButtonOptions, CheckSearchButtonOptions> TestSearchButtonOption;
// typedef std::tuple<std::string, std::string, std::string> TripleCheckValues;
// typedef std::pair<Opt_ResourceStr, std::string> ResourceSRC;
// typedef std::pair<Opt_Union_String_Resource, std::string> UnionResourceString;
// typedef std::pair<Opt_FontStyle, std::string> ArkFontStyleTest;
// typedef std::pair<Opt_Union_FontWeight_Number_String, std::string> ArkFontWeightTest;
// typedef std::pair<Type_SearchAttribute_searchIcon_Arg0, TripleCheckValues> SearchIconTest;
// typedef std::pair<Opt_Type_SearchInterface_setSearchOptions_Arg0, TripleCheckValues> OptionsTest;
using OneUnionNumStrResStep = std::pair<Union_Number_String_Resource, std::string>;
using StringResourceTest = std::tuple<ResourceStr, std::string>;
// typedef std::pair<Ark_TextDecorationType, std::string> DecorationTypeTest;
// typedef std::pair<Ark_TextDecorationStyle, std::string> DecorationStyleTest;

// // common testPlans
// const std::vector<OptLengthTest> OPT_LENGTH_TEST_PLAN = {
//     { OPT_LEN_PX_POS, CHECK_POSITIVE_VALUE_INT },
//     { OPT_LEN_PX_NEG, CHECK_DEFAULT_PX },
//     { OPT_LEN_VP_NEG, CHECK_DEFAULT_PX },
//     { OPT_LEN_VP_POS, CHECK_POSITIVE_VALUE_FLOAT }
// };
// const std::vector<OptLengthTest> TEST_PLAN_OPT_LENGTH_PX = {
//     { OPT_LEN_PX_POS, CHECK_POSITIVE_VALUE_INT },
//     { OPT_LEN_PX_NEG, CHECK_DEFAULT_PX },
//     { OPT_LEN_VP_NEG, CHECK_DEFAULT_PX },
//     { OPT_LEN_VP_POS, CHECK_POSITIVE_VALUE_FLOAT_PX }
// };
// const std::vector<LengthTest> INDENT_LENGTH_TEST_PLAN = {
//     { ALEN_PX_POS, CHECK_POSITIVE_VALUE_INT },
//     { ALEN_PX_NEG, CHECK_NEGATIVE_VALUE_INT },
//     { ALEN_VP_NEG, CHECK_NEGATIVE_VALUE_FLOAT },
//     { ALEN_VP_POS, CHECK_POSITIVE_VALUE_FLOAT }
// };
// const std::vector<ColorTest> COLOR_TEST_PLAN = {
//     { OPT_COLOR_COLOR, CHECK_COLOR_COLOR },
//     { OPT_COLOR_INT, CUSTOM_COLOR_STRING },
//     { OPT_COLOR_FLOAT, CHECK_FLOAT_COLOR },
//     { OPT_COLOR_STRING, CUSTOM_COLOR_STRING },
// };

// resource names and id
const auto RES_STRING_NAME = NamedResourceId{"aa.bb.cc", NodeModifier::ResourceType::STRING};
const auto RES_STRING_ID = IntResourceId{01234, NodeModifier::ResourceType::STRING};
const auto INVALID_STRING_ID = IntResourceId{-1, NodeModifier::ResourceType::STRING};

const auto RES_COLOR_NAME = NamedResourceId{"color_resource", NodeModifier::ResourceType::COLOR};
const auto RES_COLOR_ID = IntResourceId{11111, NodeModifier::ResourceType::COLOR};
const auto INVALID_COLOR_ID = IntResourceId{-1, NodeModifier::ResourceType::COLOR};
// resource values
const auto RESOURCE_BY_STRING = "ResourceByString";
const auto RESOURCE_BY_NUMBER = "ResourceByNumber";
const auto COLOR_BY_STRING = Color(0xFF123456);
const auto COLOR_BY_NUMBER = Color(0xFF654321);
const auto RESOURCE_DEFAULT_COLOR_DEFAULT = "#FFFF0000";

const auto RES_DIMENSION_ID = 22222; // Ark_Length.Resource
const auto RES_NUMBER_ID = IntResourceId{RES_DIMENSION_ID, NodeModifier::ResourceType::FLOAT};
const auto RES_NUMBER_NAME = NamedResourceId{"number_resource", NodeModifier::ResourceType::FLOAT};
const auto RES_NUMBER_INVALID = IntResourceId{-1, NodeModifier::ResourceType::FLOAT};

const auto DIMENSION_BY_ID = Dimension(5, DimensionUnit::VP);
const auto DIMENSION_BY_NAME = Dimension(4, DimensionUnit::VP);
const auto DIMENSION_BY_INVALID = Dimension(10, DimensionUnit::PX);

const std::vector<StringResourceTest> SRC_RESOURCES_TEST_PLAN = {
    { CreateResourceUnion<ResourceStr>(RES_STRING_NAME), RESOURCE_BY_STRING },
    { CreateResourceUnion<ResourceStr>(RES_STRING_ID), RESOURCE_BY_NUMBER },
    { CreateResourceUnion<ResourceStr>(INVALID_STRING_ID), "" },
};

using ResourceColorTestPlan = std::pair<ResourceColor, std::string>;
static const std::vector<ResourceColorTestPlan> COLOR_RESOURCE_TEST_PLAN = {
    { Converter::ArkUnion<ResourceColor, Ark_Resource>(CreateResourceUnion(RES_COLOR_NAME)),
        COLOR_BY_STRING.ColorToString() },
    { Converter::ArkUnion<ResourceColor, Ark_Resource>(CreateResourceUnion(RES_COLOR_ID)),
        COLOR_BY_NUMBER.ColorToString() },
    { Converter::ArkUnion<ResourceColor, Ark_Resource>(CreateResourceUnion(INVALID_COLOR_ID)),
        RESOURCE_DEFAULT_COLOR_DEFAULT },
};


// const std::vector<ArkFontStyleTest> FONT_STYLE_TEST_PLAN = {
//     { ArkValue<Opt_FontStyle>(Ark_FontStyle::ARK_FONT_STYLE_NORMAL), "FontStyle.Normal" },
// };

// // Font.fontWeight apply only FontWeight enum values
// const std::vector<ArkFontWeightTest> FONT_WEIGHT_TEST_PLAN = {
//     { ArkUnion<Opt_Union_FontWeight_Number_String, Ark_FontWeight>(Ark_FontWeight::ARK_FONT_WEIGHT_LIGHTER),
//         "FontWeight.Lighter" },
// };

const std::vector<OneUnionNumStrResStep> UNION_NUM_STR_RES_TEST_PLAN_RESOURCES = {
    { ArkUnion<Union_Number_String_Resource, Ark_Resource>(CreateResourceUnion(RES_NUMBER_ID)),
      DIMENSION_BY_ID.ToString()
    },
    { ArkUnion<Union_Number_String_Resource, Ark_Resource>(CreateResourceUnion(RES_NUMBER_NAME)),
      DIMENSION_BY_NAME.ToString()
    },
    { ArkUnion<Union_Number_String_Resource, Ark_Resource>(CreateResourceUnion(RES_NUMBER_INVALID)),
      DIMENSION_BY_INVALID.ToString()
    }
};

// const std::vector<DecorationTypeTest> TEXT_DECORATION_TYPE_TEST_PLAN = {
//     { Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE, "TextDecorationType.None" },
// };

// const std::vector<DecorationStyleTest> TEXT_DECORATION_STYLE_TEST_PLAN = {
//     { Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_SOLID, "TextDecorationStyle.SOLID" },
// };
} // namespace

class SearchModifierResourcesTest : public ModifierTestBase<GENERATED_ArkUISearchModifier,
                               &GENERATED_ArkUINodeModifiers::getSearchModifier, GENERATED_ARKUI_SEARCH> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<SearchTheme>();
        SetupTheme<TextFieldTheme>();
        SetupTheme<IconTheme>();

        AddResource(RES_COLOR_NAME, COLOR_BY_STRING);
        AddResource(RES_COLOR_ID, COLOR_BY_NUMBER);

        AddResource(RES_NUMBER_ID, DIMENSION_BY_ID);
        AddResource(RES_NUMBER_NAME, DIMENSION_BY_NAME);

        AddResource(RES_STRING_NAME, RESOURCE_BY_STRING);
        AddResource(RES_STRING_ID, RESOURCE_BY_NUMBER);
    }
};

/**
 * @tc.name: setCancelButtonTestIconColorResource
 * @tc.desc: Check set color functionality of setCancelButton
 * Disabled: Only Icon.size and style options available for test
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setCancelButtonTestIconColorResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Type_SearchAttribute_cancelButton_Arg0 attrs;
    attrs.selector = 0;
    for (const auto &[color, expected] : COLOR_RESOURCE_TEST_PLAN) {
        attrs.value0.icon.value.color = ArkValue<Opt_ResourceColor>(color);
        modifier_->setCancelButton(node_, &attrs);
        jsonValue = GetJsonValue(node_);
        auto customCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, CANCEL_BUTTON_ATTR);
        auto customCancelButtonIconAttrs = customCancelButtonAttrs->GetValue(CANCEL_BUTTON_ICON_ATTR);
        auto resultStr = customCancelButtonIconAttrs->GetString(CANCEL_BUTTON_ICON_COLOR_ATTR);
        EXPECT_EQ(resultStr, expected);
    }
}

/**
 * @tc.name: setCancelButtonTestIconSrc
 * @tc.desc: Check set src functionality of setCancelButton
 * Disabled: Only Icon.size and style options available for test
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setCancelButtonTestIconSrc, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Type_SearchAttribute_cancelButton_Arg0 attrs;
    attrs.selector = 0;
    for (const auto &[src, expected] : SRC_RESOURCES_TEST_PLAN) {
        attrs.value0.icon.value.src = ArkValue<Opt_ResourceStr>(src);
        modifier_->setCancelButton(node_, &attrs);
        auto jsonValue = GetJsonValue(node_);
        auto customCancelButtonAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, CANCEL_BUTTON_ATTR);
        auto customCancelButtonIconAttrs = customCancelButtonAttrs->GetValue(CANCEL_BUTTON_ICON_ATTR);
        auto resultStr = customCancelButtonIconAttrs->GetString(CANCEL_BUTTON_ICON_SRC_ATTR);
        EXPECT_EQ(resultStr, expected);
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
HWTEST_F(SearchModifierResourcesTest, DISABLED_setSearchIconTestResources, TestSize.Level1)
{
    // ASSERT_NE(modifier_->setSearchIcon, nullptr);
    // // default
    // auto fullJson = GetJsonValue(node_);
    // auto defaultSearchIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, SEARCH_ICON_ATTR);
    // auto defaultSearchIconSrc = defaultSearchIconAttrs->GetString(SEARCH_ICON_SRC_ATTR);
    // auto defaultSearchIconColor = defaultSearchIconAttrs->GetString(SEARCH_ICON_COLOR_ATTR);
    // auto defaultSearchIconSize = defaultSearchIconAttrs->GetString(SEARCH_ICON_SIZE_ATTR);
    // EXPECT_EQ(defaultSearchIconSrc, EMPTY_TEXT);
    // EXPECT_EQ(defaultSearchIconColor, CHECK_DEFAULT_BLACK_COLOR);
    // EXPECT_EQ(defaultSearchIconSize, CHECK_DEFAULT_PX);
    // // custom
    // std::vector<SearchIconTest> testSearchIcon;
    // for (auto testLength : TEST_PLAN_OPT_LENGTH_PX) {
    //     for (auto ColorTest : COLOR_RESOURCE_TEST_PLAN) {
    //         for (auto testSrc : SRC_RESOURCES_TEST_PLAN) {
    //             Type_SearchAttribute_searchIcon_Arg0 attrs = {
    //                 .selector = 0,
    //                 .value0 = {
    //                     .color = ColorTest.first,
    //                     .size = testLength.first,
    //                     .src = testSrc.first
    //                 }
    //             };
    //             TripleCheckValues checkIconValues = {
    //                 testSrc.second,
    //                 ColorTest.second,
    //                 testLength.second
    //             };
    //             SearchIconTest searchIconTest = {
    //                 attrs, checkIconValues
    //             };
    //             testSearchIcon.push_back(searchIconTest);
    //         }
    //     }
    // }

    // for (auto iconAttrs : testSearchIcon) {
    //     modifier_->setSearchIcon(node_, &iconAttrs.first);
    //     fullJson = GetJsonValue(node_);
    //     auto customSearchIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, SEARCH_ICON_ATTR);
    //     auto customSearchIconSrc = customSearchIconAttrs->GetString(SEARCH_ICON_SRC_ATTR);
    //     auto customSearchIconColor = customSearchIconAttrs->GetString(SEARCH_ICON_COLOR_ATTR);
    //     auto customSearchIconSize = customSearchIconAttrs->GetString(SEARCH_ICON_SIZE_ATTR);
    //     std::string checkSrc;
    //     std::string checkColor;
    //     std::string checkSize;
    //     std::tie(checkSrc, checkColor, checkSize) = iconAttrs.second;
    //     EXPECT_EQ(customSearchIconSrc, checkSrc);
    //     EXPECT_EQ(customSearchIconColor, checkColor);
    //     EXPECT_EQ(customSearchIconSize, checkSize);
    // }
}

/**
 * @tc.name: setFontColorTestResources
 * @tc.desc: Check the functionality of setFontColor with Resources
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setFontColorTestResources, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::unique_ptr<JsonValue> radioStyle;
    for (const auto &[arkResColor, expected]: COLOR_RESOURCE_TEST_PLAN) {
        modifier_->setFontColor(node_, &arkResColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, FONT_COLOR_ATTR);
        EXPECT_EQ(resultStr, expected);
    }   
}

/**
 * @tc.name: setSearchButtonTest
 * @tc.desc: Check the functionality of setSearchButton with Resources
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_setSearchButtonTestResources, TestSize.Level1)
{
    // ASSERT_NE(modifier_->setSearchButton, nullptr);
    // // default
    // auto fullJson = GetJsonValue(node_);
    // auto defaultCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUTTON_OPTIONS_ATTR);
    // auto defaultCaretColor = defaultCaretStyle->GetString(BUTTON_OPTIONS_COLOR_ATTR);
    // auto defaultCaretWidth = defaultCaretStyle->GetString(BUTTON_OPTIONS_SIZE_ATTR);
    // EXPECT_EQ(defaultCaretColor, CHECK_DEFAULT_BLACK_COLOR);
    // EXPECT_EQ(defaultCaretWidth, CHECK_DEFAULT_VP);
    // // custom
    // std::vector<TestSearchButtonOption> testSearchButton;
    // for (auto testLength : OPT_LENGTH_TEST_PLAN) {
    //     for (auto ColorTest : COLOR_RESOURCE_TEST_PLAN) {
    //         Ark_SearchButtonOptions buttonOptions = { .fontColor = ColorTest.first, .fontSize = testLength.first };
    //         Opt_SearchButtonOptions options = { .tag = ARK_TAG_OBJECT, .value = buttonOptions };
    //         CheckSearchButtonOptions checkSearchButtonOptions = { ColorTest.second, testLength.second };
    //         TestSearchButtonOption testSearchButtonOption = { options, checkSearchButtonOptions };
    //         testSearchButton.push_back(testSearchButtonOption);
    //     }
    // }
    // auto checkText = ArkValue<Ark_String>(CHECK_TEXT);
    // for (auto buttonOptions : testSearchButton) {
    //     modifier_->setSearchButton(node_, &checkText, &buttonOptions.first);
    //     auto fullJson = GetJsonValue(node_);
    //     auto customButtonOptions = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUTTON_OPTIONS_ATTR);
    //     auto searchButtonColor = customButtonOptions->GetString(BUTTON_OPTIONS_COLOR_ATTR);
    //     auto searchButtonSize = customButtonOptions->GetString(BUTTON_OPTIONS_SIZE_ATTR);
    //     EXPECT_EQ(searchButtonColor, buttonOptions.second.first);
    //     EXPECT_EQ(searchButtonSize, buttonOptions.second.second);
    // }
}

/**
 * @tc.name: setTextIndentTestResources
 * @tc.desc: Check the functionality of setTextIndent
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_setTextIndentTestResources, TestSize.Level1)
{

}

/**
 * @tc.name: setPlaceholderColorTestResource
 * @tc.desc: Check the functionality of setPlaceholderColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setPlaceholderColorTestResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::unique_ptr<JsonValue> radioStyle;
    for (const auto &[arkResColor, expected]: COLOR_RESOURCE_TEST_PLAN) {
        modifier_->setPlaceholderColor(node_, &arkResColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, PLACEHOLDER_COLOR_ATTR);
        EXPECT_EQ(resultStr, expected);
    }
}

/**
 * @tc.name: setCaretStyleTestResources
 * @tc.desc: Check the functionality of setCaretStyle
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_setCaretStyleTestResources, TestSize.Level1)
{
    // implement test resources
}

/**
 * @tc.name: selectedBackgroundColorTest
 * @tc.desc: Check the functionality of selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, selectedBackgroundColorTestResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::unique_ptr<JsonValue> radioStyle;
    for (const auto &[arkResColor, expected]: COLOR_RESOURCE_TEST_PLAN) {
        modifier_->setSelectedBackgroundColor(node_, &arkResColor);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, SELECTED_BACKGROUND_COLOR_ATTR);
        EXPECT_EQ(resultStr, expected);
    }
}

/**
 * @tc.name: setMaxFontSizeTest
 * @tc.desc: Check the functionality of setMaxFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setMaxFontSizeTestResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;
    for (const auto &[arkLength, expected]: UNION_NUM_STR_RES_TEST_PLAN_RESOURCES) {
        modifier_->setMaxFontSize(node_, &arkLength);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, MAX_FONT_SIZE_ATTR);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: setMinFontSizeTest
 * @tc.desc: Check the functionality of setMinFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setMinFontSizeTestResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;
    for (const auto &[arkLength, expected]: UNION_NUM_STR_RES_TEST_PLAN_RESOURCES) {
        modifier_->setMinFontSize(node_, &arkLength);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, MIN_FONT_SIZE_ATTR);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: setLetterSpacingTestResource
 * @tc.desc: Check the functionality of setLetterSpacing
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setLetterSpacingTestResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;
    for (const auto &[arkLength, expected]: UNION_NUM_STR_RES_TEST_PLAN_RESOURCES) {
        modifier_->setLetterSpacing(node_, &arkLength);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, LETTER_SPACING_ATTR);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: setPlaceholderFontTestFamily
 * @tc.desc: Check the functionality of setPlaceholderFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_setPlaceholderFontTestFamily, TestSize.Level1)
{
    // ASSERT_NE(modifier_->setPlaceholderFont, nullptr);

    // Ark_Font font = {
    //     .family = UNION_RESOURCE_STRING_PLAN[0].first,
    //     .size = OPT_LENGTH_TEST_PLAN[0].first,
    //     .style = FONT_STYLE_TEST_PLAN[0].first,
    //     .weight = FONT_WEIGHT_TEST_PLAN[0].first
    // };
    // auto fontOpt = ArkValue<Opt_Font>(font);
    // auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
    // auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    // auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    // for (auto family : UNION_RESOURCE_STRING_PLAN) {
    //     font.family = family.first;
    //     fontOpt = ArkValue<Opt_Font>(font);
    //     modifier_->setPlaceholderFont(node_, &fontOpt);
    //     auto placeholderFontJSON = GetStringAttribute(node_, PLACEHOLDER_FONT_ATTRS);
    //     auto placeholderFont = JsonUtil::ParseJsonString(placeholderFontJSON);
    //     auto checkSize = placeholderFont->GetString(PLACEHOLDER_FONT_SIZE);
    //     auto checkFamily = placeholderFont->GetString(PLACEHOLDER_FONT_FAMILY);
    //     auto checkWeight = placeholderFont->GetString(PLACEHOLDER_FONT_WEIGHT);
    //     if (checkWeight.empty()) {
    //         checkWeight = placeholderFont->GetString(PLACEHOLDER_FONT_WEIGHT_ENUM);
    //     }
    //     auto checkStyle = placeholderFont->GetString(PLACEHOLDER_FONT_STYLE);
    //     EXPECT_EQ(checkSize, sizeStr);
    //     EXPECT_EQ(checkFamily, family.second);
    //     EXPECT_EQ(checkStyle, styleStr);
    //     EXPECT_EQ(checkWeight, weightStr);
    // }
}

/**
 * @tc.name: setTextFontTestFontFamily
 * @tc.desc: Check the functionality of setTextFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_setTextFontTestFontFamily, TestSize.Level1)
{
    // ASSERT_NE(modifier_->setTextFont, nullptr);

    // Ark_Font font = {
    //     .family = UNION_RESOURCE_STRING_PLAN[0].first,
    //     .size = OPT_LENGTH_TEST_PLAN[0].first,
    //     .style = FONT_STYLE_TEST_PLAN[0].first,
    //     .weight = FONT_WEIGHT_TEST_PLAN[0].first
    // };
    // auto fontOpt = ArkValue<Opt_Font>(font);
    // auto sizeStr = OPT_LENGTH_TEST_PLAN[0].second;
    // auto styleStr = FONT_STYLE_TEST_PLAN[0].second;
    // auto weightStr = FONT_WEIGHT_TEST_PLAN[0].second;

    // for (auto family : UNION_RESOURCE_STRING_PLAN) {
    //     font.family = family.first;
    //     fontOpt = ArkValue<Opt_Font>(font);
    //     modifier_->setTextFont(node_, &fontOpt);
    //     auto textFontJSON = GetStringAttribute(node_, TEXT_FONT_ATTRS);
    //     auto textFont = JsonUtil::ParseJsonString(textFontJSON);
    //     auto checkSize = textFont->GetString(TEXT_FONT_SIZE_ATTR);
    //     auto checkFamily = textFont->GetString(TEXT_FONT_FAMILY_ATTR);
    //     auto checkWeight = textFont->GetString(TEXT_FONT_WEIGHT_ATTR);
    //     auto checkStyle = textFont->GetString(TEXT_FONT_STYLE_ATTR);
    //     EXPECT_EQ(checkSize, sizeStr);
    //     EXPECT_EQ(checkFamily, family.second);
    //     EXPECT_EQ(checkStyle, styleStr);
    //     EXPECT_EQ(checkWeight, weightStr);
    // }
}

/**
 * @tc.name: setTextFontTestFontSize
 * @tc.desc: Check the functionality of setTextFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_setTextFontTestFontSizeResource, TestSize.Level1)
{
    // implement check resources
}

/**
 * @tc.name: setLineHeightTestResource
 * @tc.desc: Check the functionality of setLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_setLineHeightTestResource, TestSize.Level1)
{
    // ASSERT_NE(modifier_->setLineHeight, nullptr);

    // auto checkVal = GetStringAttribute(node_, LINE_HEIGHT_ATTR);
    // EXPECT_EQ(checkVal, "0.00vp");

    // for (const auto &[value, expectVal]: UNION_NUM_STR_RES_TEST_PLAN_WITH_PERCENT_RESOURCES) {
    //     modifier_->setLineHeight(node_, &value);
    //     checkVal = GetStringAttribute(node_, LINE_HEIGHT_ATTR);
    //     EXPECT_EQ(checkVal, expectVal);
    // }
}

/**
 * @tc.name: setDecorationTestResource
 * @tc.desc: Check the functionality of setDecoration
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_setDecorationTestResource, TestSize.Level1)
{
    // ASSERT_NE(modifier_->setDecoration, nullptr);
    // auto defaultDecorationJSON = GetStringAttribute(node_, DECORATION_ATTRS);
    // auto defaultDecoration = JsonUtil::ParseJsonString(defaultDecorationJSON);
    // auto defaultType = defaultDecoration->GetString(DECORATION_TYPE_ATTR);
    // auto defaultStyle = defaultDecoration->GetString(DECORATION_STYLE_ATTR);
    // auto defaultColor = defaultDecoration->GetString(DECORATION_COLOR_ATTR);
    // EXPECT_EQ(defaultType, "TextDecorationType.None");
    // EXPECT_EQ(defaultStyle, "TextDecorationStyle.SOLID");
    // EXPECT_EQ(defaultColor, CHECK_DEFAULT_BLACK_COLOR);

    // for (const auto &[decorationType, expectDecorationType]: TEXT_DECORATION_TYPE_TEST_PLAN) {
    //     for (const auto &[decorationStyle, expectDecorationStyle]: TEXT_DECORATION_STYLE_TEST_PLAN) {
    //         for (const auto &[decorationColor, expectColor] : COLOR_RESOURCE_TEST_PLAN) {
    //             Ark_TextDecorationOptions options = {
    //                 .color = decorationColor,
    //                 .type = decorationType,
    //                 .style = ArkValue<Opt_TextDecorationStyle>(decorationStyle)
    //             };
    //             modifier_->setDecoration(node_, &options);
    //             auto decorationJSON = GetStringAttribute(node_, DECORATION_ATTRS);
    //             auto decoration = JsonUtil::ParseJsonString(decorationJSON);
    //             auto type = decoration->GetString(DECORATION_TYPE_ATTR);
    //             auto style = decoration->GetString(DECORATION_STYLE_ATTR);
    //             auto color = decoration->GetString(DECORATION_COLOR_ATTR);
    //             EXPECT_EQ(type, expectDecorationType);
    //             EXPECT_EQ(style, expectDecorationStyle);
    //             EXPECT_EQ(color, expectColor);
    //         }
    //     }
    // }
}
} // namespace OHOS::Ace::NG
