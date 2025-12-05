/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components/common/layout/constants.h"
#include "core/interfaces/native/implementation/decoration_style_peer.h"
#include "accessor_test_base.h"
#include "accessor_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr auto COLORS_RES_0_ID = 100001;
    constexpr auto COLORS_RES_0_STR = "COLORS_RES_0_STR";

    const std::vector<std::tuple<std::string, TextDecoration,
        Ark_TextDecorationType>> testFixtureTextDecorationValues = {
        { "TextDecoration::NONE", TextDecoration::NONE, Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE },
        { "TextDecoration::UNDERLINE", TextDecoration::UNDERLINE,
            Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_UNDERLINE },
        { "TextDecoration::OVERLINE", TextDecoration::OVERLINE,
            Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_OVERLINE },
        { "TextDecoration::LINE_THROUGH", TextDecoration::LINE_THROUGH,
            Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_LINE_THROUGH },
        { "TextDecoration::INHERIT", TextDecoration::INHERIT, Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE },
        { "-1", static_cast<TextDecoration>(-1), Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE },
    };

    const std::vector<std::tuple<std::string, TextDecorationStyle,
        std::optional<Ark_TextDecorationStyle>>> testFixtureTextDecorationStyleValues = {
        { "TextDecorationStyle::SOLID", TextDecorationStyle::SOLID,
            Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_SOLID },
        { "TextDecorationStyle::DOUBLE", TextDecorationStyle::DOUBLE,
            Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DOUBLE },
        { "TextDecorationStyle::DOTTED", TextDecorationStyle::DOTTED,
            Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DOTTED },
        { "TextDecorationStyle::DASHED", TextDecorationStyle::DASHED,
            Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_DASHED },
        { "TextDecorationStyle::WAVY", TextDecorationStyle::WAVY,
            Ark_TextDecorationStyle::ARK_TEXT_DECORATION_STYLE_WAVY },
        { "TextDecorationStyle::INITIAL", TextDecorationStyle::INITIAL, std::nullopt },
        { "TextDecorationStyle::INHERIT", TextDecorationStyle::INHERIT, std::nullopt },
        { "-1", static_cast<TextDecorationStyle>(-1), std::nullopt },
    };

    std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureColorsStrValidValues = {
        { "\"#123\"", Converter::ArkValue<Ark_String>("#123"), "#FF112233" },
        { "\"#11223344\"", Converter::ArkValue<Ark_String>("#11223344"), "#11223344" },
        { "\"#123456\"", Converter::ArkValue<Ark_String>("#123456"), "#FF123456" },
        { "\"65535\"", Converter::ArkValue<Ark_String>("65535"), "#FF00FFFF" },
        { "\"#abcdef\"", Converter::ArkValue<Ark_String>("#abcdef"), "#FFABCDEF" },
        { "\"#aBcdeF\"", Converter::ArkValue<Ark_String>("#aBcdeF"), "#FFABCDEF" },
        { "\"rgb(255, 100, 55)\"", Converter::ArkValue<Ark_String>("rgb(255, 100, 55)"), "#FFFF6437" },
        { "\"rgba(255, 100, 255, 0.5)\"", Converter::ArkValue<Ark_String>("rgba(255, 100, 255, 0.5)"), "#80FF64FF" },
    };

    std::vector<std::tuple<std::string, Ark_String>> testFixtureColorsStrInvalidValues = {
        { "\"invalid\"", Converter::ArkValue<Ark_String>("invalid") },
        { "\"\"", Converter::ArkValue<Ark_String>("") },
        { "\"rgb(270, 0xf1, 755.5f)\"", Converter::ArkValue<Ark_String>("rgb(270, 0xf1, 755.5f)") },
        { "\"RgbA(255, 100, 255, 0.5)\"", Converter::ArkValue<Ark_String>("RgbA(255, 100, 255, 0.5)") },
    };

    const auto TEST_COLOR_BLUE = Color::BLUE;
    const auto TEST_COLOR_RED = Color::RED;
    std::vector<std::tuple<std::string, Ark_Resource, std::string>> testFixtureColorsResValidValues = {
        { "ResId:COLORS_RES_0_ID", CreateResource(COLORS_RES_0_ID, ResourceType::COLOR), "#FF0000FF" },
        { "ResName:COLORS_RES_0_STR", CreateResource(COLORS_RES_0_STR, ResourceType::COLOR), "#FFFF0000" },
    };

    std::vector<std::tuple<std::string, Ark_arkui_component_enums_Color, std::string>> testFixtureColorsEnumValidValues = {
        { "ARK_COLOR_WHITE", ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE, "#FFFFFFFF" },
        { "ARK_COLOR_BLACK", ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLACK, "#FF000000" },
        { "ARK_COLOR_BLUE", ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE, "#FF0000FF" },
        { "ARK_COLOR_BROWN", ARK_ARKUI_COMPONENT_ENUMS_COLOR_BROWN, "#FFA52A2A" },
        { "ARK_COLOR_GRAY", ARK_ARKUI_COMPONENT_ENUMS_COLOR_GRAY, "#FF808080" },
        { "ARK_COLOR_GREEN", ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREEN, "#FF008000" },
        { "ARK_COLOR_GREY", ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREY, "#FF808080" },
        { "ARK_COLOR_ORANGE", ARK_ARKUI_COMPONENT_ENUMS_COLOR_ORANGE, "#FFFFA500" },
        { "ARK_COLOR_PINK", ARK_ARKUI_COMPONENT_ENUMS_COLOR_PINK, "#FFFFC0CB" },
        { "ARK_COLOR_RED", ARK_ARKUI_COMPONENT_ENUMS_COLOR_RED, "#FFFF0000" },
        { "ARK_COLOR_YELLOW", ARK_ARKUI_COMPONENT_ENUMS_COLOR_YELLOW, "#FFFFFF00" },
        { "ARK_COLOR_TRANSPARENT", ARK_ARKUI_COMPONENT_ENUMS_COLOR_TRANSPARENT, "#00000000" },
    };

    std::vector<std::tuple<std::string, Ark_arkui_component_enums_Color>> testFixtureColorsEnumInvalidValues = {
        { "-1", static_cast<Ark_arkui_component_enums_Color>(-1) },
        { "INT_MAX", static_cast<Ark_arkui_component_enums_Color>(INT_MAX) },
    };

}

using namespace testing;
using namespace testing::ext;

class DecorationStyleAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIDecorationStyleAccessor,
        &GENERATED_ArkUIAccessors::getDecorationStyleAccessor, DecorationStylePeer> {
public:
    static void SetUpTestCase()
    {
        AccessorTestBaseParent::SetUpTestCase();
        AddResource(COLORS_RES_0_ID, TEST_COLOR_BLUE);
        AddResource(COLORS_RES_0_STR, TEST_COLOR_RED);
    }
    void* CreatePeerInstance() override
    {
        return accessor_->construct(nullptr);
    }
    void DestroyPeer(DecorationStylePeer* peer)
    {
        finalyzer_(peer);
        peer = nullptr;
    }
};

/**
 * @tc.name: getTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DecorationStyleAccessorTest, getTypeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getType, nullptr);
    Ark_DecorationStyleInterface* stylePtr = new Ark_DecorationStyleInterface();
    for (auto& [input, value, expected] : testFixtureTextDecorationValues) {
        DestroyPeer(peer_);
        stylePtr->type = Converter::ArkValue<Opt_TextDecorationType>(value);
        peer_ = accessor_->construct(stylePtr);
        auto type = accessor_->getType(peer_);
        EXPECT_EQ(expected, type) <<
            "Input value is: " << input << ", method: getType";
    }
}

/**
 * @tc.name: getStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DecorationStyleAccessorTest, getStyleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getStyle, nullptr);
    Ark_DecorationStyleInterface stylePtr;
    stylePtr.type = Converter::ArkValue<Opt_TextDecorationType>(Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE);
    for (auto& [input, value, expected] : testFixtureTextDecorationStyleValues) {
        DestroyPeer(peer_);
        stylePtr.style = Converter::ArkValue<Opt_TextDecorationStyle>(value);
        peer_ = accessor_->construct(&stylePtr);
        auto style = accessor_->getStyle(peer_);
        EXPECT_EQ(expected, Converter::GetOpt(style)) <<
            "Input value is: " << input << ", method: getStyle";
    }
}

/**
 * @tc.name: getColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DecorationStyleAccessorTest, getColorTestValidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getColor, nullptr);
    Ark_DecorationStyleInterface* stylePtr = new Ark_DecorationStyleInterface();
    auto textDecorationType = Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE;
    stylePtr->type = Converter::ArkValue<Opt_TextDecorationType>(textDecorationType);
    auto checkValue =
        [this, stylePtr](const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        DestroyPeer(peer_);
        stylePtr->color = value;
        peer_ = accessor_->construct(stylePtr);
        auto arkResColor = accessor_->getColor(peer_);
        auto colorOpt = Converter::OptConvert<Color>(arkResColor);
        ASSERT_TRUE(colorOpt.has_value());
        EXPECT_EQ(expectedStr, colorOpt.value().ToString()) <<
            "Input value is: " << input << ", method: getColor";
    };

    Converter::ConvContext ctx;
    for (auto& [input, value, expected] : testFixtureColorsStrValidValues) {
        checkValue(input, Converter::ArkUnion<Opt_ResourceColor, Ark_String>(value, &ctx), expected);
    }

    for (auto& [input, value, expected] : testFixtureColorsResValidValues) {
        checkValue(input, Converter::ArkUnion<Opt_ResourceColor, Ark_Resource>(value), expected);
    }

    for (auto& [input, value, expected] : testFixtureColorsEnumValidValues) {
        checkValue(input, Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value), expected);
    }
}

HWTEST_F(DecorationStyleAccessorTest, getColorTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(accessor_->getColor, nullptr);
    Ark_DecorationStyleInterface* stylePtr = new Ark_DecorationStyleInterface();
    auto textDecorationType = Ark_TextDecorationType::ARK_TEXT_DECORATION_TYPE_NONE;
    stylePtr->type = Converter::ArkValue<Opt_TextDecorationType>(textDecorationType);
    auto checkValue =
        [this, stylePtr](const std::string& input, const Opt_ResourceColor& value) {
        DestroyPeer(peer_);
        stylePtr->color = value;
        peer_ = accessor_->construct(stylePtr);
        auto arkResColor = accessor_->getColor(peer_);
        auto colorOpt = Converter::OptConvert<Color>(arkResColor);
        EXPECT_EQ(colorOpt, std::nullopt) <<
            "Input value is: " << input << ", method: getColor";
    };

    for (auto& [input, value] : testFixtureColorsStrInvalidValues) {
        checkValue(input, Converter::ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }

    for (auto& [input, value] : testFixtureColorsEnumInvalidValues) {
        checkValue(input, Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
}

} // namespace OHOS::Ace::NG
