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
#include "base/utils/string_utils.h"

#include "generated/type_helpers.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;

namespace {
// attrs
const auto BUTTON_OPTIONS_ATTR("searchButtonOption");
const auto BUTTON_OPTIONS_COLOR_ATTR("fontColor");
const auto BUTTON_OPTIONS_SIZE_ATTR("fontSize");
const auto CANCEL_BUTTON_ATTR("cancelButton");
const auto CANCEL_BUTTON_ICON_ATTR("icon");
const auto CANCEL_BUTTON_ICON_COLOR_ATTR("color");
const auto CANCEL_BUTTON_ICON_SRC_ATTR("src");
const auto CARET_STYLE_ATTR("caretStyle");
const auto CARET_STYLE_COLOR_ATTR("color");
const auto CARET_STYLE_WIDTH_ATTR("width");
const auto DECORATION_ATTRS("decoration");
const auto DECORATION_COLOR_ATTR("color");
const auto FONT_COLOR_ATTR("fontColor");
const auto INPUT_FILTER_ATTR("inputFilter");
const auto LETTER_SPACING_ATTR("letterSpacing");
const auto LINE_HEIGHT_ATTR("lineHeight");
const auto MAX_FONT_SIZE_ATTR("maxFontSize");
const auto MIN_FONT_SIZE_ATTR("minFontSize");
const auto PLACEHOLDER_FONT_ATTRS("placeholderFont");
const auto PLACEHOLDER_FONT_FAMILY("fontFamily");
const auto PLACEHOLDER_FONT_SIZE("size");
const auto PLACEHOLDER_COLOR_ATTR("placeholderColor");
const auto SEARCH_ICON_ATTR("searchIcon");
const auto SEARCH_ICON_SRC_ATTR("src");
const auto SEARCH_ICON_COLOR_ATTR("color");
const auto SEARCH_ICON_SIZE_ATTR("size");
const auto SEARCH_PLACEHOLDER_OPTION("placeholder");
const auto SELECTED_BACKGROUND_COLOR_ATTR("selectedBackgroundColor");
const auto TEXT_FONT_ATTRS("textFont");
const auto TEXT_FONT_SIZE_ATTR("fontSize");
const auto TEXT_FONT_FAMILY_ATTR("fontFamily");
const auto TEXT_INDENT_ATTR("textIndent");

// resource names and id
const auto RES_STRING_NAME = NamedResourceId{"aa.bb.cc", ResourceType::STRING};
const auto RES_STRING_ID = IntResourceId{01234, ResourceType::STRING};
const auto INVALID_STRING_ID = IntResourceId{-1, ResourceType::STRING};

const auto RES_COLOR_NAME = NamedResourceId{"color_resource", ResourceType::COLOR};
const auto RES_COLOR_ID = IntResourceId{11111, ResourceType::COLOR};
const auto INVALID_COLOR_ID = IntResourceId{-1, ResourceType::COLOR};

const auto RES_FAMILY_NAME = NamedResourceId{"family_resource", ResourceType::STRARRAY};
const auto RES_FAMILY_ID = IntResourceId{3333, ResourceType::STRARRAY};
// resource values
const auto RESOURCE_BY_STRING = "ResourceByString";
const auto RESOURCE_BY_NUMBER = "ResourceByNumber";
const auto COLOR_BY_STRING = Color(0xFF123456);
const auto COLOR_BY_NUMBER = Color(0xFF654321);
const auto RESOURCE_DEFAULT_COLOR_DEFAULT = "#FFFF0000";

const auto ICON_DEFAULT_SRC("resource:///ohos_test_image.svg");

const int64_t RES_DIMENSION_ID = 22222; // Ark_Length.Resource
const int64_t INVALID_RES_ID = -1;
const auto RES_NUMBER_ID = IntResourceId{RES_DIMENSION_ID, ResourceType::FLOAT};
const auto RES_NUMBER_NAME = NamedResourceId{"number_resource", ResourceType::FLOAT};
const auto RES_NUMBER_INVALID = IntResourceId{-1, ResourceType::FLOAT};

const auto DIMENSION_BY_ID = Dimension(5, DimensionUnit::VP);
const auto DIMENSION_BY_NAME = Dimension(4, DimensionUnit::VP);
const auto DIMENSION_BY_INVALID = Dimension(0, DimensionUnit::PX);

const auto FAMILY_BY_STRING = "first";
const auto FAMILY_BY_NUMBER = "second";

const std::vector<std::tuple<Ark_ResourceStr, std::string>> SRC_RESOURCES_TEST_PLAN = {
    { CreateResourceUnion<Ark_ResourceStr>(RES_STRING_NAME), RESOURCE_BY_STRING },
    { CreateResourceUnion<Ark_ResourceStr>(RES_STRING_ID), RESOURCE_BY_NUMBER },
    { CreateResourceUnion<Ark_ResourceStr>(INVALID_STRING_ID), ICON_DEFAULT_SRC },
};

const std::vector<std::tuple<Ark_ResourceStr, std::string>> ARK_RESOURCES_TEST_PLAN = {
    { CreateResourceUnion<Ark_ResourceStr>(RES_STRING_NAME), RESOURCE_BY_STRING },
    { CreateResourceUnion<Ark_ResourceStr>(RES_STRING_ID), RESOURCE_BY_NUMBER },
    { CreateResourceUnion<Ark_ResourceStr>(INVALID_STRING_ID), "" },
};

static const std::vector<std::pair<Ark_ResourceColor, std::string>> COLOR_RESOURCE_TEST_PLAN = {
    { CreateResourceUnion<Ark_ResourceColor>(RES_COLOR_NAME), COLOR_BY_STRING.ColorToString() },
    { CreateResourceUnion<Ark_ResourceColor>(RES_COLOR_ID), COLOR_BY_NUMBER.ColorToString() },
    { CreateResourceUnion<Ark_ResourceColor>(INVALID_COLOR_ID), RESOURCE_DEFAULT_COLOR_DEFAULT },
};

const std::vector<std::pair<Ark_Length, std::string>> ARK_LENGTH_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(RES_DIMENSION_ID), "5.00vp" },
    { Converter::ArkValue<Ark_Length>(INVALID_RES_ID), "0.00px" }
};

const std::vector<std::pair<Ark_Length, std::string>> ARK_SIZE_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(RES_DIMENSION_ID), "5.00px" },
    { Converter::ArkValue<Ark_Length>(INVALID_RES_ID), "0.00px" }
};

const std::vector<std::pair<Ark_Union_F64_String_Resource, std::string>> UNION_NUM_STR_RES_TEST_PLAN_RESOURCES = {
    { CreateResourceUnion<Ark_Union_F64_String_Resource>(RES_NUMBER_ID), DIMENSION_BY_ID.ToString() },
    { CreateResourceUnion<Ark_Union_F64_String_Resource>(RES_NUMBER_NAME), DIMENSION_BY_NAME.ToString() },
    { CreateResourceUnion<Ark_Union_F64_String_Resource>(RES_NUMBER_INVALID), DIMENSION_BY_INVALID.ToString() },
};

using ResourceTest = std::tuple<Opt_Union_String_Resource, std::string>;
const std::vector<ResourceTest> FONT_FAMILY_TEST_PLAN_RESOURCES = {
    { CreateResourceUnion<Opt_Union_String_Resource>(RES_FAMILY_NAME), FAMILY_BY_STRING },
    { CreateResourceUnion<Opt_Union_String_Resource>(RES_FAMILY_ID), FAMILY_BY_NUMBER },
};
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

        AddResource(RES_FAMILY_ID, FAMILY_BY_NUMBER);
        AddResource(RES_FAMILY_NAME, FAMILY_BY_STRING);
    }
};

/**
 * @tc.name: setSearchOptionsResources
 * @tc.desc: Check the default values of setSearchOptions
 *
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setSearchOptionsResources, TestSize.Level1)
{
    Ark_SearchOptions options = {};

    const std::vector<std::tuple<Ark_ResourceStr, std::string>> testPlan = {
        { CreateResourceUnion<Ark_ResourceStr>(RES_STRING_NAME), RESOURCE_BY_STRING },
        { CreateResourceUnion<Ark_ResourceStr>(RES_STRING_ID), RESOURCE_BY_NUMBER },
        { CreateResourceUnion<Ark_ResourceStr>(INVALID_STRING_ID), "" },
    };

    for (const auto &[src, expected] : testPlan) {
        options.placeholder = ArkValue<Opt_ResourceStr>(src);
        auto optOptions = ArkValue<Opt_SearchOptions>(options);
        modifier_->setSearchOptions(node_, &optOptions);
        // default
        auto jsonValue = GetJsonValue(node_);
        auto placeholder = GetAttrValue<std::string>(jsonValue, SEARCH_PLACEHOLDER_OPTION);
        EXPECT_EQ(placeholder, expected);
    }
}

/**
 * @tc.name: setCancelButtonTestIconColorResource
 * @tc.desc: Check set color functionality of setCancelButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setCancelButtonTestIconColorResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions attrs;
    auto& value = WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(attrs)).icon).color;
    for (const auto &[color, expected] : COLOR_RESOURCE_TEST_PLAN) {
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
 * @tc.name: setCancelButtonTestIconSrc
 * @tc.desc: Check set src functionality of setCancelButton
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_setCancelButtonTestIconSrc, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions attrs;
    auto& value = WriteTo(WriteToUnion<Ark_CancelButtonOptions>(WriteTo(attrs)).icon).src;
    for (const auto &[src, expected] : SRC_RESOURCES_TEST_PLAN) {
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
 * @tc.name: setSearchIconTest
 * @tc.desc: Check the functionality of setSearchIcon
 * This test disabled because set icon src and color always return default value
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setSearchIconTestResources, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSearchIcon, nullptr);
    // custom
    for (const auto &[testLength, resultLength] : ARK_SIZE_TEST_PLAN) {
        auto attrs = ArkUnion<Opt_Union_IconOptions_SymbolGlyphModifier, Ark_IconOptions>(
            Ark_IconOptions {
                .color = ArkValue<Opt_ResourceColor>(),
                .size = ArkValue<Opt_Length>(testLength),
                .src = ArkValue<Opt_ResourceStr>()
            });
        modifier_->setSearchIcon(node_, &attrs);
        auto fullJson = GetJsonValue(node_);
        auto customSearchIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, SEARCH_ICON_ATTR);
        auto customSearchIconSize = GetAttrValue<std::string>(customSearchIconAttrs, SEARCH_ICON_SIZE_ATTR);
        EXPECT_EQ(customSearchIconSize, resultLength);
    }
    for (const auto &[colorTest, resultColor] : COLOR_RESOURCE_TEST_PLAN) {
        auto attrs = ArkUnion<Opt_Union_IconOptions_SymbolGlyphModifier, Ark_IconOptions>(
            Ark_IconOptions {
                .color = ArkValue<Opt_ResourceColor>(colorTest),
                .size = ArkValue<Opt_Length>(),
                .src = ArkValue<Opt_ResourceStr>()
            });
        modifier_->setSearchIcon(node_, &attrs);
        auto fullJson = GetJsonValue(node_);
        auto customSearchIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, SEARCH_ICON_ATTR);
        auto customSearchIconColor = GetAttrValue<std::string>(customSearchIconAttrs, SEARCH_ICON_COLOR_ATTR);
        EXPECT_EQ(customSearchIconColor, resultColor);
    }
    for (const auto &[testSrc, resultSrc] : SRC_RESOURCES_TEST_PLAN) {
        auto attrs = ArkUnion<Opt_Union_IconOptions_SymbolGlyphModifier, Ark_IconOptions>(
            Ark_IconOptions {
                .color = ArkValue<Opt_ResourceColor>(),
                .size = ArkValue<Opt_Length>(),
                .src = ArkValue<Opt_ResourceStr>(testSrc)
            });
        modifier_->setSearchIcon(node_, &attrs);
        auto fullJson = GetJsonValue(node_);
        auto customSearchIconAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, SEARCH_ICON_ATTR);
        auto customSearchIconSrc = GetAttrValue<std::string>(customSearchIconAttrs, SEARCH_ICON_SRC_ATTR);
        EXPECT_EQ(customSearchIconSrc, resultSrc);
    }
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
        auto inputValue = ArkValue<Opt_ResourceColor>(arkResColor);
        modifier_->setFontColor(node_, &inputValue);
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
    auto checkText = ArkValue<Opt_String>(RESOURCE_BY_STRING);
    for (const auto &[testLength, expectLength] : ARK_LENGTH_TEST_PLAN) {
        for (const auto &[testColor, expectColor] : COLOR_RESOURCE_TEST_PLAN) {
            Ark_SearchButtonOptions buttonOptions = {
                .fontColor = ArkValue<Opt_ResourceColor>(testColor),
                .fontSize = ArkValue<Opt_Length>(testLength)
            };
            auto options = ArkValue<Opt_SearchButtonOptions>(buttonOptions);
            modifier_->setSearchButton(node_, &checkText, &options);
            auto fullJson = GetJsonValue(node_);
            auto customButtonOptions = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUTTON_OPTIONS_ATTR);
            auto searchButtonColor = GetAttrValue<std::string>(customButtonOptions, BUTTON_OPTIONS_COLOR_ATTR);
            auto searchButtonSize = GetAttrValue<std::string>(customButtonOptions, BUTTON_OPTIONS_SIZE_ATTR);
            EXPECT_EQ(searchButtonColor, expectColor);
            EXPECT_EQ(searchButtonSize, expectLength);
        }
    }
}

/**
 * @tc.name: setTextIndentTestResources
 * @tc.desc: Check the functionality of setTextIndent
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_setTextIndentTestResources, TestSize.Level1)
{
    const std::vector<std::pair<Opt_Dimension, std::string>> testPlan = {
        { Converter::ArkValue<Opt_Dimension>(RES_DIMENSION_ID), "5.00vp" },
        { Converter::ArkValue<Opt_Dimension>(INVALID_RES_ID), "0.00px" }
    };
    for (const auto &[value, expected]: testPlan) {
        modifier_->setTextIndent(node_, &value);
        auto jsonValue = GetJsonValue(node_);
        auto result = GetAttrValue<std::string>(jsonValue, TEXT_INDENT_ATTR);
        EXPECT_EQ(result, expected);
    }
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
        auto inputValue = ArkValue<Opt_ResourceColor>(arkResColor);
        modifier_->setPlaceholderColor(node_, &inputValue);
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
HWTEST_F(SearchModifierResourcesTest, setCaretStyleTestResources, TestSize.Level1)
{
    for (const auto &[testLength, resultLength] : ARK_LENGTH_TEST_PLAN) {
        for (const auto &[testColor, resultColor] : COLOR_RESOURCE_TEST_PLAN) {
            Ark_CaretStyle arkCaretStyle = {
                .color = ArkValue<Opt_ResourceColor>(testColor),
                .width = ArkValue<Opt_Length>(testLength)
            };
            auto inputValue = ArkValue<Opt_CaretStyle>(arkCaretStyle);
            modifier_->setCaretStyle(node_, &inputValue);
            auto value = GetStringAttribute(node_, CARET_STYLE_ATTR);
            auto fullJson = GetJsonValue(node_);
            auto customCaretStyle = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, CARET_STYLE_ATTR);
            auto caretColor = GetAttrValue<std::string>(customCaretStyle, CARET_STYLE_COLOR_ATTR);
            auto caretWidth = GetAttrValue<std::string>(customCaretStyle, CARET_STYLE_WIDTH_ATTR);
            EXPECT_EQ(caretColor, resultColor);
            EXPECT_EQ(caretWidth, resultLength);
        }
    }
}

/**
 * @tc.name: setInputFilterTestResources
 * @tc.desc: Check the functionality of setInputFilter
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_setInputFilterTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setInputFilter, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_TRUE(textFieldChild);
    auto textFieldEventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_TRUE(textFieldEventHub);
    struct CheckEvent {
        int32_t nodeId;
        std::string textBreakpoints;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto callback = [] (const Ark_Int32 resourceId, const Ark_String breakpoints) {
        checkEvent = {
            .nodeId = Convert<int32_t>(resourceId),
            .textBreakpoints = Convert<std::string>(breakpoints),
        };
    };
    auto arkCallback = ArkCallback<Opt_Callback_String_Void>(callback, textFieldChild->GetId());
    std::unique_ptr<JsonValue> jsonValue;
    for (const auto &[src, expected] : ARK_RESOURCES_TEST_PLAN) {
        auto sendResource = ArkValue<Opt_ResourceStr>(src);
        modifier_->setInputFilter(node_, &sendResource, &arkCallback);
        textFieldEventHub->FireOnInputFilterError(UtfUtils::Str8ToStr16(expected));
        ASSERT_TRUE(checkEvent);
        auto jsonValue = GetJsonValue(node_);
        auto filterValue = GetAttrValue<std::string>(jsonValue, INPUT_FILTER_ATTR);
        EXPECT_EQ(checkEvent->nodeId, textFieldChild->GetId());
        EXPECT_EQ(checkEvent->textBreakpoints, expected);
        EXPECT_EQ(filterValue, expected);
    }
}

/**
 * @tc.name: selectedBackgroundColorTest
 * @tc.desc: Check the functionality of selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_selectedBackgroundColorTestResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::unique_ptr<JsonValue> radioStyle;
    for (const auto &[arkResColor, expected]: COLOR_RESOURCE_TEST_PLAN) {
        auto inputValue = ArkValue<Opt_ResourceColor>(arkResColor);
        modifier_->setSelectedBackgroundColor(node_, &inputValue);
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
HWTEST_F(SearchModifierResourcesTest, DISABLED_setMaxFontSizeTestResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;
    for (const auto &[arkLength, expected]: UNION_NUM_STR_RES_TEST_PLAN_RESOURCES) {
        auto inputValue = ArkValue<Opt_Union_F64_String_Resource>(arkLength);
        modifier_->setMaxFontSize(node_, &inputValue);
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
HWTEST_F(SearchModifierResourcesTest, DISABLED_setMinFontSizeTestResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;
    for (const auto &[arkLength, expected]: UNION_NUM_STR_RES_TEST_PLAN_RESOURCES) {
        auto inputValue = ArkValue<Opt_Union_F64_String_Resource>(arkLength);
        modifier_->setMinFontSize(node_, &inputValue);
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
HWTEST_F(SearchModifierResourcesTest, DISABLED_setLetterSpacingTestResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;
    for (const auto &[arkLength, expected]: UNION_NUM_STR_RES_TEST_PLAN_RESOURCES) {
        auto inputValue = ArkValue<Opt_Union_F64_String_Resource>(arkLength);
        modifier_->setLetterSpacing(node_, &inputValue);
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
HWTEST_F(SearchModifierResourcesTest, setPlaceholderFontTestFamily, TestSize.Level1)
{
    Ark_Font font;
    std::unique_ptr<JsonValue> jsonValue;
    for (const auto &[family, expected] : FONT_FAMILY_TEST_PLAN_RESOURCES) {
        font.family = family;
        auto fontOpt = ArkValue<Opt_Font>(font);
        modifier_->setPlaceholderFont(node_, &fontOpt);
        jsonValue = GetJsonValue(node_);
        auto placeholderFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PLACEHOLDER_FONT_ATTRS);
        auto checkFamily = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_FAMILY);
        EXPECT_EQ(checkFamily, expected);
    }
}

/**
 * @tc.name: setPlaceholderFontTestSize
 * @tc.desc: Check the functionality of setPlaceholderFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setPlaceholderFontTestSize, TestSize.Level1)
{
    Ark_Font font;
    std::unique_ptr<JsonValue> jsonValue;
    for (const auto &[arkLength, expected]: ARK_LENGTH_TEST_PLAN) {
        font.size = ArkValue<Opt_Length>(arkLength);
        auto fontOpt = ArkValue<Opt_Font>(font);
        modifier_->setPlaceholderFont(node_, &fontOpt);
        jsonValue = GetJsonValue(node_);
        auto placeholderFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, PLACEHOLDER_FONT_ATTRS);
        auto result = GetAttrValue<std::string>(placeholderFont, PLACEHOLDER_FONT_SIZE);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: setTextFontTestFontFamily
 * @tc.desc: Check the functionality of setTextFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setTextFontTestFontFamily, TestSize.Level1)
{
    Ark_Font font;
    std::unique_ptr<JsonValue> jsonValue;
    for (const auto &[family, expected] : FONT_FAMILY_TEST_PLAN_RESOURCES) {
        font.family = family;
        auto fontOpt = ArkValue<Opt_Font>(font);
        modifier_->setTextFont(node_, &fontOpt);
        jsonValue = GetJsonValue(node_);
        auto placeholderFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, TEXT_FONT_ATTRS);
        auto result = GetAttrValue<std::string>(placeholderFont, TEXT_FONT_FAMILY_ATTR);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: setTextFontTestFontSize
 * @tc.desc: Check the functionality of setTextFont.
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setTextFontTestFontSizeResource, TestSize.Level1)
{
    Ark_Font font;
    std::unique_ptr<JsonValue> jsonValue;
    for (const auto &[arkLength, expected]: ARK_LENGTH_TEST_PLAN) {
        font.size = ArkValue<Opt_Length>(arkLength);
        auto fontOpt = ArkValue<Opt_Font>(font);
        modifier_->setTextFont(node_, &fontOpt);
        jsonValue = GetJsonValue(node_);
        auto placeholderFont = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, TEXT_FONT_ATTRS);
        auto result = GetAttrValue<std::string>(placeholderFont, TEXT_FONT_SIZE_ATTR);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: setLineHeightTestResource
 * @tc.desc: Check the functionality of setLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, DISABLED_setLineHeightTestResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;
    const std::vector<std::pair<Opt_Union_F64_String_Resource, std::string>> testPlan = {
        { CreateResourceUnion<Opt_Union_F64_String_Resource>(RES_NUMBER_ID), DIMENSION_BY_ID.ToString() },
        { CreateResourceUnion<Opt_Union_F64_String_Resource>(RES_NUMBER_NAME), DIMENSION_BY_NAME.ToString() },
        { CreateResourceUnion<Opt_Union_F64_String_Resource>(RES_NUMBER_INVALID), "0.00vp" },
    };
    for (const auto &[value, expected]: testPlan) {
        modifier_->setLineHeight(node_, &value);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<std::string>(jsonValue, LINE_HEIGHT_ATTR);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: setDecorationTestResource
 * @tc.desc: Check the functionality of setDecoration
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierResourcesTest, setDecorationTestResource, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string result;
    for (const auto &[decorationColor, expectColor] : COLOR_RESOURCE_TEST_PLAN) {
        Ark_TextDecorationOptions options = {
            .color = ArkValue<Opt_ResourceColor>(decorationColor),
        };
        auto inputValue = ArkValue<Opt_TextDecorationOptions>(options);
        modifier_->setDecoration(node_, &inputValue);
        auto decorationJSON = GetStringAttribute(node_, DECORATION_ATTRS);
        auto decoration = JsonUtil::ParseJsonString(decorationJSON);
        auto result = GetAttrValue<std::string>(decoration, DECORATION_COLOR_ATTR);
        EXPECT_EQ(result, expectColor);
    }
}
} // namespace OHOS::Ace::NG
