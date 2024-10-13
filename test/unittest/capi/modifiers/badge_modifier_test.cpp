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

#include "badge_modifier_test.h"

#include <gtest/gtest.h>

#include "arkoala_api_generated.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/components/badge/badge_theme.h"
#include "core/interfaces/arkoala/utility/converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
Ark_Position ToArkPos(int32_t value);
Ark_Position ToArkPos(double v, DimensionUnit unit);
Ark_Length ToArkLength(int32_t value);
inline Ark_Resource ArkRes(Ark_String* name, int id = -1,
    NodeModifier::ResourceType type = NodeModifier::ResourceType::COLOR, const char* module = "",
    const char* bundle = "");

const auto ATTRIBUTE_POSITION_NAME = "position";
const auto ATTRIBUTE_POSITION_DEFAULT_VALUE = "BadgePosition.RightTop";
const auto ATTRIBUTE_SET_STYLE_NAME = "style";
const auto ATTRIBUTE_SET_STYLE_X_NAME = "x";
const auto ATTRIBUTE_SET_STYLE_X_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_SET_STYLE_Y_NAME = "y";
const auto ATTRIBUTE_SET_STYLE_Y_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_SET_STYLE_COLOR_NAME = "color";
const auto ATTRIBUTE_SET_STYLE_COLOR_DEFAULT_VALUE = "#FFFFFFFF";
const auto ATTRIBUTE_SET_STYLE_FONT_SIZE_NAME = "fontSize";
const auto ATTRIBUTE_SET_STYLE_FONT_SIZE_DEFAULT_VALUE = "10.00vp";
const auto ATTRIBUTE_SET_STYLE_BADGE_COLOR_NAME = "badgeColor";
const auto ATTRIBUTE_SET_STYLE_BADGE_COLOR_DEFAULT_VALUE = "#FFFF0000";
const auto ATTRIBUTE_SET_STYLE_BADGE_SIZE_NAME = "badgeSize";
const auto ATTRIBUTE_SET_STYLE_BADGE_SIZE_DEFAULT_VALUE = "16.00vp";
const auto ATTRIBUTE_SET_STYLE_BORDER_COLOR_NAME = "borderColor";
const auto ATTRIBUTE_SET_STYLE_BORDER_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_SET_STYLE_BORDER_WIDTH_NAME = "borderWidth";
const auto ATTRIBUTE_SET_STYLE_BORDER_WIDTH_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_SET_STYLE_FONT_WEIGHT_NAME = "fontWeight";
const auto ATTRIBUTE_SET_STYLE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
const auto ATTRIBUTE_COUNT_NAME = "count";
const auto ATTRIBUTE_COUNT_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_MAX_COUNT_NAME = "maxCount";
const auto ATTRIBUTE_MAX_COUNT_DEFAULT_VALUE = "99";
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "";

inline Ark_Resource ArkRes(Ark_String* name, int id, NodeModifier::ResourceType type, 
    const char* module, const char* bundle)
{
    return { .id = { .tag = ARK_TAG_INT32, .i32 = static_cast<Ark_Int32>(id) },
        .type = { .tag = ARK_TAG_INT32, .i32 = static_cast<Ark_Int32>(type) },
        .moduleName = { .chars = module },
        .bundleName = { .chars = bundle },
        .params = { .tag = ARK_TAG_OBJECT, .value = { .array = name, .length = name ? 1 : 0 } }
    };
}

template<typename T>
void FillEmptyOptions(T& options)
{
    options.position = Converter::ArkValue<Opt_Union_BadgePosition_Position>(Ark_Empty());
    options.style = {
        .color = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty()),
        .fontSize = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty()),
        .badgeSize = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty()),
        .badgeColor = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty()),
        .borderColor = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty()),
        .borderWidth = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .fontWeight = Converter::ArkValue<Opt_Union_Number_FontWeight_String>(Ark_Empty()),
    };
}

void InitStringOptions(Ark_BadgeParamWithString& options)
{
    FillEmptyOptions(options);
    options.value = Converter::ArkValue<Ark_String>("");
}

void InitNumberOptions(Ark_BadgeParamWithNumber& options)
{
    FillEmptyOptions(options);
    options.maxCount = Converter::ArkValue<Opt_Number>(Ark_Empty());
    options.count = Converter::ArkValue<Ark_Number>(0);
}

/**
 *  Converts int32_t into Ark_Length
 */
Ark_Length ToArkLength(int32_t value)
{
   return { 
        .type = ARK_TAG_RESOURCE, .resource = Ark_Int32(value) 
    };
}

/**
 *  Converts int32_t into Ark_Position, x = y = value
 */
Ark_Position ToArkPos(int32_t value)
{
    Ark_Length x = { .type = ARK_TAG_RESOURCE, .resource = Ark_Int32(value) };
    
    return { 
        .x = Converter::ArkValue<Opt_Length>(x), .y = Converter::ArkValue<Opt_Length>(x) 
    };
}

/**
 * Converts double and DimensionUnit into Ark_Position
 */
Ark_Position ToArkPos(double v, DimensionUnit unit)
{
   return {
        .x =Converter::ArkValue<Opt_Length>(Dimension(v, unit)),
        .y =Converter::ArkValue<Opt_Length>(Dimension(v, unit)),
   };
}

} // namespace

namespace Converter {

void AssignArkValue(Ark_FontWeight& dst, const FontWeight& src)
{
    switch (src) {
        case FontWeight::W100: dst = Ark_FontWeight::ARK_FONT_WEIGHT_LIGHTER; break;
        case FontWeight::W400: dst = Ark_FontWeight::ARK_FONT_WEIGHT_NORMAL; break;
        case FontWeight::W700: dst = Ark_FontWeight::ARK_FONT_WEIGHT_BOLD; break;
        case FontWeight::W900: dst = Ark_FontWeight::ARK_FONT_WEIGHT_BOLDER; break;
        case FontWeight::LIGHTER: dst = Ark_FontWeight::ARK_FONT_WEIGHT_LIGHTER; break;
        case FontWeight::NORMAL: dst = Ark_FontWeight::ARK_FONT_WEIGHT_NORMAL; break;
        case FontWeight::REGULAR: dst = Ark_FontWeight::ARK_FONT_WEIGHT_REGULAR; break;
        case FontWeight::MEDIUM: dst = Ark_FontWeight::ARK_FONT_WEIGHT_MEDIUM; break;
        case FontWeight::BOLD: dst = Ark_FontWeight::ARK_FONT_WEIGHT_BOLD; break;
        case FontWeight::BOLDER: dst = Ark_FontWeight::ARK_FONT_WEIGHT_BOLDER; break;
        default:
            dst = static_cast<Ark_FontWeight>(-1);
            LOGE("Unexpected enum value in Ark_FontWeight: %{public}d", src);
    }
}

} // namespace Converter

class BadgeModifierTest : public ModifierTestBase<GENERATED_ArkUIBadgeModifier,
                              &GENERATED_ArkUINodeModifiers::getBadgeModifier, GENERATED_ARKUI_BADGE> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<BadgeTheme>();
    }
};

/*
 * @tc.name: setBadgeOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BadgeModifierTest, setBadgeOptionsTestDefaultValues, TestSize.Level1)
{
    auto jsonValue = GetJsonValue(node_);
    jsonValue->Delete("position");

    auto badgePosition = jsonValue->GetString(ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(badgePosition, ATTRIBUTE_POSITION_DEFAULT_VALUE);

    auto badgeStyleAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SET_STYLE_NAME);

    auto badgeStyleX = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_X_NAME);
    EXPECT_EQ(badgeStyleX, ATTRIBUTE_SET_STYLE_X_DEFAULT_VALUE);

    auto badgeStyleY = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_Y_NAME);
    EXPECT_EQ(badgeStyleY, ATTRIBUTE_SET_STYLE_Y_DEFAULT_VALUE);

    auto badgeStyleColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_COLOR_NAME);
    EXPECT_EQ(badgeStyleColor, ATTRIBUTE_SET_STYLE_COLOR_DEFAULT_VALUE);

    auto badgeStyleFontSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_SIZE_NAME);
    EXPECT_EQ(badgeStyleFontSize, ATTRIBUTE_SET_STYLE_FONT_SIZE_DEFAULT_VALUE);

    auto badgeStyleBadgeColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_COLOR_NAME);
    EXPECT_EQ(badgeStyleBadgeColor, ATTRIBUTE_SET_STYLE_BADGE_COLOR_DEFAULT_VALUE);

    auto badgeStyleBadgeSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_SIZE_NAME);
    EXPECT_EQ(badgeStyleBadgeSize, ATTRIBUTE_SET_STYLE_BADGE_SIZE_DEFAULT_VALUE);

    auto badgeStyleBorderColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_COLOR_NAME);
    EXPECT_EQ(badgeStyleBorderColor, ATTRIBUTE_SET_STYLE_BORDER_COLOR_DEFAULT_VALUE);

    auto badgeStyleBorderWidth = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_WIDTH_NAME);
    EXPECT_EQ(badgeStyleBorderWidth, ATTRIBUTE_SET_STYLE_BORDER_WIDTH_DEFAULT_VALUE);

    auto badgeStyleFontWeight = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_WEIGHT_NAME);
    EXPECT_EQ(badgeStyleFontWeight, ATTRIBUTE_SET_STYLE_FONT_WEIGHT_DEFAULT_VALUE);

    auto badgeCount = jsonValue->GetString(ATTRIBUTE_COUNT_NAME);
    EXPECT_EQ(badgeCount, ATTRIBUTE_COUNT_DEFAULT_VALUE);

    auto badgeMaxCount = jsonValue->GetString(ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(badgeMaxCount, ATTRIBUTE_MAX_COUNT_DEFAULT_VALUE);

    auto badgeValue = jsonValue->GetString(ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(badgeValue, ATTRIBUTE_VALUE_DEFAULT_VALUE);
}

/*
 * @tc.name: setBadgeOptions0TestEmptyValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BadgeModifierTest, setBadgeOptions0TestEmptyValues, TestSize.Level1)
{
    Ark_BadgeParamWithNumber inputValueOptions;
    InitNumberOptions(inputValueOptions);

    modifier_->setBadgeOptions0(node_, &inputValueOptions);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    jsonValue->Delete("position");

    auto badgePosition = jsonValue->GetString(ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(badgePosition, "BadgePosition.RightTop");

    auto badgeStyleAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SET_STYLE_NAME);

    auto badgeStyleX = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_X_NAME);
    EXPECT_EQ(badgeStyleX, "0.00vp");

    auto badgeStyleY = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_Y_NAME);
    EXPECT_EQ(badgeStyleY, "0.00vp");

    auto badgeStyleColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_COLOR_NAME);
    EXPECT_EQ(badgeStyleColor, "#FF000000");

    auto badgeStyleFontSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_SIZE_NAME);
    EXPECT_EQ(badgeStyleFontSize, "10.00vp");

    auto badgeStyleBadgeColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_COLOR_NAME);
    EXPECT_EQ(badgeStyleBadgeColor, "#FF000000");

    auto badgeStyleBadgeSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_SIZE_NAME);
    EXPECT_EQ(badgeStyleBadgeSize, "16.00vp");

    auto badgeStyleBorderColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_COLOR_NAME);
    EXPECT_EQ(badgeStyleBorderColor, "#FF000000");

    auto badgeStyleBorderWidth = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_WIDTH_NAME);
    EXPECT_EQ(badgeStyleBorderWidth, "0.00px");

    auto badgeStyleFontWeight = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_WEIGHT_NAME);
    EXPECT_EQ(badgeStyleFontWeight, "FontWeight.Normal");

    auto badgeCount = jsonValue->GetString(ATTRIBUTE_COUNT_NAME);
    EXPECT_EQ(badgeCount, "0");

    auto badgeMaxCount = jsonValue->GetString(ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(badgeMaxCount, "99");
}

/*
 * @tc.name: setBadgeOptions0TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BadgeModifierTest, setBadgeOptions0TestValidValues, TestSize.Level1)
{
    Ark_BadgeParamWithNumber inputValueOptions;
    InitNumberOptions(inputValueOptions);
    inputValueOptions.position =
        Converter::ArkUnion<Opt_Union_BadgePosition_Position, Ark_Position>(ToArkPos(12.00, DimensionUnit::PX));
    inputValueOptions.style = {
        .color =
            Converter::ArkValue<Opt_ResourceColor>(Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_GRAY)),
        .fontSize = Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("8.00vp"),
        .badgeSize = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(32.00f),
        .badgeColor =
            Converter::ArkValue<Opt_ResourceColor>(Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#FF00FF00")),
        .borderColor =
            Converter::ArkValue<Opt_ResourceColor>(Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xFF0000FF)),
        .borderWidth = Converter::ArkValue<Opt_Length>(Dimension(2.45f, DimensionUnit::VP)),
        .fontWeight = Converter::ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(
            Converter::ArkValue<Ark_FontWeight>(FontWeight::MEDIUM)),
    };
    inputValueOptions.count = Converter::ArkValue<Ark_Number>(4);
    inputValueOptions.maxCount = Converter::ArkValue<Opt_Number>(20);

    modifier_->setBadgeOptions0(node_, &inputValueOptions);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    jsonValue->Delete("position");

    auto badgePosition = jsonValue->GetString(ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(badgePosition, "BadgePosition.RightTop");

    auto badgeStyleAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SET_STYLE_NAME);

    auto badgeStyleX = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_X_NAME);
    EXPECT_EQ(badgeStyleX, "12.00px");

    auto badgeStyleY = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_Y_NAME);
    EXPECT_EQ(badgeStyleY, "12.00px");

    auto badgeStyleColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_COLOR_NAME);
    EXPECT_EQ(badgeStyleColor, "#FF808080");

    auto badgeStyleFontSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_SIZE_NAME);
    EXPECT_EQ(badgeStyleFontSize, "8.00vp");

    auto badgeStyleBadgeColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_COLOR_NAME);
    EXPECT_EQ(badgeStyleBadgeColor, "#FF00FF00");

    auto badgeStyleBadgeSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_SIZE_NAME);
    EXPECT_EQ(badgeStyleBadgeSize, "32.00vp");

    auto badgeStyleBorderColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_COLOR_NAME);
    EXPECT_EQ(badgeStyleBorderColor, "#FF0000FF");

    auto badgeStyleBorderWidth = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_WIDTH_NAME);
    EXPECT_EQ(badgeStyleBorderWidth, "2.45vp");

    auto badgeStyleFontWeight = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_WEIGHT_NAME);
    EXPECT_EQ(badgeStyleFontWeight, "FontWeight.Medium");

    auto badgeCount = jsonValue->GetString(ATTRIBUTE_COUNT_NAME);
    EXPECT_EQ(badgeCount, "4");

    auto badgeMaxCount = jsonValue->GetString(ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(badgeMaxCount, "20");
}

/*
 * @tc.name: setBadgeOptions0TestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BadgeModifierTest, setBadgeOptions0TestInvalidValues, TestSize.Level1)
{
    Ark_BadgeParamWithNumber inputValueOptions;
    InitNumberOptions(inputValueOptions);

    inputValueOptions.position = Converter::ArkUnion<Opt_Union_BadgePosition_Position, Ark_Position>(ToArkPos(-12.00));
    inputValueOptions.style = {
        .color =
            Converter::ArkValue<Opt_ResourceColor>(Converter::ArkUnion<Ark_ResourceColor, Ark_String>("invalid color")),
        .fontSize = Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-8.00vp"),
        .badgeSize = Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-32.00vp"),
        .badgeColor =
            Converter::ArkValue<Opt_ResourceColor>(Converter::ArkUnion<Ark_ResourceColor, Ark_String>("-100 color")),
        .borderColor =
            Converter::ArkValue<Opt_ResourceColor>(Converter::ArkUnion<Ark_ResourceColor, Ark_String>("no color")),
        .borderWidth = Converter::ArkValue<Opt_Length>(Dimension(-2.45f, DimensionUnit::VP)),
        .fontWeight = Converter::ArkUnion<Opt_Union_Number_FontWeight_String, Ark_FontWeight>(
            Converter::ArkValue<Ark_FontWeight>(static_cast<FontWeight>(-100))),
    };
    inputValueOptions.count = Converter::ArkValue<Ark_Number>(-1);
    inputValueOptions.maxCount = Converter::ArkValue<Opt_Number>(-100);

    modifier_->setBadgeOptions0(node_, &inputValueOptions);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    jsonValue->Delete("position");

    auto badgePosition = jsonValue->GetString(ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(badgePosition, "BadgePosition.RightTop");

    auto badgeStyleAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SET_STYLE_NAME);

    auto badgeStyleX = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_X_NAME);
    EXPECT_EQ(badgeStyleX, "10.00px");

    auto badgeStyleY = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_Y_NAME);
    EXPECT_EQ(badgeStyleY, "10.00px");

    auto badgeStyleColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_COLOR_NAME);
    EXPECT_EQ(badgeStyleColor, "#FF000000");

    auto badgeStyleFontSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_SIZE_NAME);
    EXPECT_EQ(badgeStyleFontSize, "10.00vp");

    auto badgeStyleBadgeColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_COLOR_NAME);
    EXPECT_EQ(badgeStyleBadgeColor, "#FF000000");

    auto badgeStyleBadgeSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_SIZE_NAME);
    EXPECT_EQ(badgeStyleBadgeSize, "16.00vp");

    auto badgeStyleBorderColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_COLOR_NAME);
    EXPECT_EQ(badgeStyleBorderColor, "#FF000000");

    auto badgeStyleBorderWidth = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_WIDTH_NAME);
    EXPECT_EQ(badgeStyleBorderWidth, "0.00px");

    auto badgeStyleFontWeight = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_WEIGHT_NAME);
    EXPECT_EQ(badgeStyleFontWeight, "FontWeight.Normal");

    auto badgeCount = jsonValue->GetString(ATTRIBUTE_COUNT_NAME);
    EXPECT_EQ(badgeCount, "-1");

    auto badgeMaxCount = jsonValue->GetString(ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(badgeMaxCount, "-100");
}

/*
 * @tc.name: setBadgeOptions1TestEmptyValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BadgeModifierTest, setBadgeOptions1TestEmptyValues, TestSize.Level1)
{
    Ark_BadgeParamWithString inputValueOptions;
    InitStringOptions(inputValueOptions);

    modifier_->setBadgeOptions1(node_, &inputValueOptions);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    jsonValue->Delete("position");

    auto badgePosition = jsonValue->GetString(ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(badgePosition, "BadgePosition.RightTop");

    auto badgeStyleAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SET_STYLE_NAME);

    auto badgeStyleX = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_X_NAME);
    EXPECT_EQ(badgeStyleX, "0.00vp");

    auto badgeStyleY = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_Y_NAME);
    EXPECT_EQ(badgeStyleY, "0.00vp");

    auto badgeStyleColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_COLOR_NAME);
    EXPECT_EQ(badgeStyleColor, "#FF000000");

    auto badgeStyleFontSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_SIZE_NAME);
    EXPECT_EQ(badgeStyleFontSize, "10.00vp");

    auto badgeStyleBadgeColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_COLOR_NAME);
    EXPECT_EQ(badgeStyleBadgeColor, "#FF000000");

    auto badgeStyleBadgeSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_SIZE_NAME);
    EXPECT_EQ(badgeStyleBadgeSize, "16.00vp");

    auto badgeStyleBorderColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_COLOR_NAME);
    EXPECT_EQ(badgeStyleBorderColor, "#FF000000");

    auto badgeStyleBorderWidth = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_WIDTH_NAME);
    EXPECT_EQ(badgeStyleBorderWidth, "0.00px");

    auto badgeStyleFontWeight = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_WEIGHT_NAME);
    EXPECT_EQ(badgeStyleFontWeight, "FontWeight.Normal");

    auto badgeValue = jsonValue->GetString(ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(badgeValue, "");
}

/*
 * @tc.name: setBadgeOptions1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BadgeModifierTest, setBadgeOptions1TestValidValues, TestSize.Level1)
{
    Ark_BadgeParamWithString inputValueOptions;
    InitStringOptions(inputValueOptions);
    inputValueOptions.position =
        Converter::ArkUnion<Opt_Union_BadgePosition_Position, Ark_Position>(ToArkPos(16, DimensionUnit::VP));
    inputValueOptions.style = {
        .color = Converter::ArkValue<Opt_ResourceColor>(Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xFF00FFFF)),
        .fontSize = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(28.00f),
        .badgeSize = Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("32.00px"),
        .badgeColor =
            Converter::ArkValue<Opt_ResourceColor>(Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE)),
        .borderColor =
            Converter::ArkValue<Opt_ResourceColor>(Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#FF0000FF")),
        .borderWidth = Converter::ArkValue<Opt_Length>(ToArkLength(10)),
        .fontWeight = Converter::ArkUnion<Opt_Union_Number_FontWeight_String, Ark_String>("100"),
    };
    inputValueOptions.value = Converter::ArkValue<Ark_String>("badge_value");

    modifier_->setBadgeOptions1(node_, &inputValueOptions);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    jsonValue->Delete("position");

    auto badgePosition = jsonValue->GetString(ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(badgePosition, "BadgePosition.RightTop");

    auto badgeStyleAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SET_STYLE_NAME);

    auto badgeStyleX = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_X_NAME);
    EXPECT_EQ(badgeStyleX, "16.00vp");

    auto badgeStyleY = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_Y_NAME);
    EXPECT_EQ(badgeStyleY, "16.00vp");

    auto badgeStyleColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_COLOR_NAME);
    EXPECT_EQ(badgeStyleColor, "#FF00FFFF");

    auto badgeStyleFontSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_SIZE_NAME);
    EXPECT_EQ(badgeStyleFontSize, "28.00vp");

    auto badgeStyleBadgeColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_COLOR_NAME);
    EXPECT_EQ(badgeStyleBadgeColor, "#FF0000FF");

    auto badgeStyleBadgeSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_SIZE_NAME);
    EXPECT_EQ(badgeStyleBadgeSize, "32.00px");

    auto badgeStyleBorderColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_COLOR_NAME);
    EXPECT_EQ(badgeStyleBorderColor, "#FF0000FF");

    auto badgeStyleBorderWidth = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_WIDTH_NAME);
    EXPECT_EQ(badgeStyleBorderWidth, "10.00px");

    auto badgeStyleFontWeight = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_WEIGHT_NAME);
    EXPECT_EQ(badgeStyleFontWeight, "100");

    auto badgeValue = jsonValue->GetString(ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(badgeValue, "badge_value");
}

/*
 * @tc.name: setBadgeOptions1TestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BadgeModifierTest, setBadgeOptions1TestInvalidValues, TestSize.Level1)
{
    Ark_BadgeParamWithString inputValueOptions;
    InitStringOptions(inputValueOptions);

    inputValueOptions.position =
        Converter::ArkUnion<Opt_Union_BadgePosition_Position, Ark_Position>(ToArkPos(-12.00, DimensionUnit::PX));
    inputValueOptions.style = {
        .color =
            Converter::ArkValue<Opt_ResourceColor>(Converter::ArkUnion<Ark_ResourceColor, Ark_String>("invalid color")),
        .fontSize = Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("50%"),
        .badgeSize = Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("10%"),
        .badgeColor =
            Converter::ArkValue<Opt_ResourceColor>(Converter::ArkUnion<Ark_ResourceColor, Ark_String>("no color")),
        .borderColor = Converter::ArkValue<Opt_ResourceColor>(
            Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 150001))),
        .borderWidth = Converter::ArkValue<Opt_Length>(Dimension(0.55f, DimensionUnit::PERCENT)),
        .fontWeight = Converter::ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Number>(-100),
    };
    inputValueOptions.value = Converter::ArkValue<Ark_String>("");

    modifier_->setBadgeOptions1(node_, &inputValueOptions);

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    jsonValue->Delete("position");

    auto badgePosition = jsonValue->GetString(ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(badgePosition, "BadgePosition.RightTop");

    auto badgeStyleAttrs = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SET_STYLE_NAME);

    auto badgeStyleX = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_X_NAME);
    EXPECT_EQ(badgeStyleX, "0.00vp");

    auto badgeStyleY = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_Y_NAME);
    EXPECT_EQ(badgeStyleY, "0.00vp");

    auto badgeStyleColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_COLOR_NAME);
    EXPECT_EQ(badgeStyleColor, "#FF000000");

    auto badgeStyleFontSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_SIZE_NAME);
    EXPECT_EQ(badgeStyleFontSize, "10.00vp");

    auto badgeStyleBadgeColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_COLOR_NAME);
    EXPECT_EQ(badgeStyleBadgeColor, "#FF000000");

    auto badgeStyleBadgeSize = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BADGE_SIZE_NAME);
    EXPECT_EQ(badgeStyleBadgeSize, "16.00vp");

    auto badgeStyleBorderColor = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_COLOR_NAME);
    EXPECT_EQ(badgeStyleBorderColor, "#FFFF0000");

    auto badgeStyleBorderWidth = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_BORDER_WIDTH_NAME);
    EXPECT_EQ(badgeStyleBorderWidth, "0.00px");

    auto badgeStyleFontWeight = badgeStyleAttrs->GetString(ATTRIBUTE_SET_STYLE_FONT_WEIGHT_NAME);
    EXPECT_EQ(badgeStyleFontWeight, "FontWeight.Normal");

    auto badgeValue = jsonValue->GetString(ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(badgeValue, "");
}

} // namespace OHOS::Ace::NG
