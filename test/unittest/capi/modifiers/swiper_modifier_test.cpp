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

#include "swiper_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/peer_utils.h"

#include "core/components/common/layout/constants.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
const Ark_Boolean ABOOL_TRUE(true);
const Ark_Boolean ABOOL_FALSE(false);
const Ark_Int32 AINT32_POS(1234);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);

const auto ANUM_INT_POS = ArkValue<Ark_Number>(AINT32_POS);
const auto ANUM_INT_NEG = ArkValue<Ark_Number>(AINT32_NEG);
const auto ASTR_INVALID = ArkValue<Ark_String>("(*%^&#@");

const auto ALEN_VP_POS = ArkValue<Ark_Length>(AFLT32_POS);
const auto ALEN_VP_NEG = ArkValue<Ark_Length>(AFLT32_NEG);

const auto OPT_LEN_VP_POS = ArkValue<Opt_Length>(AFLT32_POS);
const auto OPT_LEN_VP_NEG = ArkValue<Opt_Length>(AFLT32_NEG);
const auto OPT_LEN_UNDEF = ArkValue<Opt_Length>();

const auto OPT_BOOL_UNDEF = ArkValue<Opt_Boolean>(Ark_Empty());
const auto OPT_BOOL_TRUE = ArkValue<Opt_Boolean>(true);
const auto OPT_BOOL_FALSE = ArkValue<Opt_Boolean>(false);

const auto OPT_COLOR_UNDEF = ArkValue<Opt_ResourceColor>();

constexpr auto EXPECTED_TRUE = "true";
constexpr auto EXPECTED_FALSE = "false";
const std::string EXPECTED_VP_ZERO(Dimension(0, DimensionUnit::VP).ToString());
const std::string EXPECTED_PX_POS(Dimension(AINT32_POS, DimensionUnit::PX).ToString());
const std::string EXPECTED_VP_POS(Dimension(AFLT32_POS, DimensionUnit::VP).ToString());

const Dimension THEME_SWIPER_INDICATOR_SIZE(9876, DimensionUnit::VP);
const Dimension THEME_SWIPER_FONT_SIZE(321, DimensionUnit::PX);
const Color THEME_SWIPER_INDICATOR_COLOR(Color::BLUE);
const Color THEME_SWIPER_ARROW_COLOR(Color::GREEN);

const auto RES_NAME = NamedResourceId("aa.bb.cc", ResourceType::COLOR);
const auto RES_ID = IntResourceId(1234, ResourceType::COLOR);
const auto CONTEXT_ID = 123;
} // namespace

class SwiperModifierTest : public ModifierTestBase<GENERATED_ArkUISwiperModifier,
    &GENERATED_ArkUINodeModifiers::getSwiperModifier, GENERATED_ARKUI_SWIPER> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = SetupThemeStyle("swiper_pattern");
        themeStyle->SetAttr("swiper_indicator_size", { .value = THEME_SWIPER_INDICATOR_SIZE });
        themeStyle->SetAttr("indicator_color", { .value = THEME_SWIPER_INDICATOR_COLOR });
        themeStyle->SetAttr("indicator_color_selected", { .value = THEME_SWIPER_INDICATOR_COLOR });
        themeStyle->SetAttr("indicator_text_font_size", { .value = THEME_SWIPER_FONT_SIZE });
        themeStyle->SetAttr(ARROW_COLOR_PRIMARY, { .value = THEME_SWIPER_ARROW_COLOR });
        themeStyle->SetAttr(ARROW_COLOR_COMPONENT_NORMAL, { .value = THEME_SWIPER_ARROW_COLOR });

        SetupTheme<SwiperIndicatorTheme>();
    }
};

/**
 * @tc.name: setIndexTest
 * @tc.desc: Check the functionality of SwiperModifier.IndexImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndexTest, TestSize.Level1)
{
    constexpr auto propName = "index";
    constexpr auto defaultValue = "0";
    ASSERT_NE(modifier_->setIndex, nullptr);

    auto input = ArkUnion<Opt_Union_I32_Bindable, Ark_Int32>(123456);
    modifier_->setIndex(node_, &input);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, "123456");

    input = ArkUnion<Opt_Union_I32_Bindable, Ark_Int32>(0);
    modifier_->setIndex(node_, &input);
    auto checkVal3 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal3, "0");

    input = ArkUnion<Opt_Union_I32_Bindable, Ark_Int32>(1);
    modifier_->setIndex(node_, &input);
    auto checkVal4 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal4, "1");

    input = ArkUnion<Opt_Union_I32_Bindable, Ark_Int32>(-1);
    modifier_->setIndex(node_, &input);
    auto checkVal5 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal5, defaultValue);
}
/**
 * @tc.name: setAutoPlayTest
 * @tc.desc: Check the functionality of SwiperModifier.AutoPlayImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setAutoPlay0Test, TestSize.Level1)
{
    constexpr auto propName = "autoPlay";
    const std::string &defaultValue(EXPECTED_FALSE);
    ASSERT_NE(modifier_->setAutoPlay0, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    modifier_->setAutoPlay0(node_, &OPT_BOOL_TRUE);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setAutoPlay0(node_, &OPT_BOOL_FALSE);
    auto checkVal3 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);
}
/**
 * @tc.name: setAutoPlayTest
 * @tc.desc: Check the functionality of SwiperModifier.AutoPlay1Impl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setAutoPlay1Test2Arg, TestSize.Level1)
{
    const std::string propNameAutoPlay("autoPlay");
    const std::string &autoPlayDefault(EXPECTED_FALSE);
    const std::string propNameAutoPlayOptions("stopWhenTouched");
    const std::string &autoPlayOptionsDefault(EXPECTED_TRUE);

    ASSERT_NE(modifier_->setAutoPlay1, nullptr);

    auto checkAutoPlay = GetAttrValue<std::string>(node_, propNameAutoPlay);
    EXPECT_EQ(checkAutoPlay, autoPlayDefault);
    auto checkAutoPlayOptions = GetAttrValue<std::string>(node_, propNameAutoPlayOptions);
    EXPECT_EQ(checkAutoPlayOptions, autoPlayOptionsDefault);

    Ark_AutoPlayOptions options = { .stopWhenTouched = false };
    auto optionsOpt = Converter::ArkValue<Opt_AutoPlayOptions>(options);
    modifier_->setAutoPlay1(node_, &OPT_BOOL_TRUE, &optionsOpt);
    checkAutoPlay = GetAttrValue<std::string>(node_, propNameAutoPlay);
    EXPECT_EQ(checkAutoPlay, EXPECTED_TRUE);
    checkAutoPlayOptions = GetAttrValue<std::string>(node_, propNameAutoPlayOptions);
    EXPECT_EQ(checkAutoPlayOptions, EXPECTED_FALSE);

    options = { .stopWhenTouched = true };
    optionsOpt = Converter::ArkValue<Opt_AutoPlayOptions>(options);
    modifier_->setAutoPlay1(node_, &OPT_BOOL_FALSE, &optionsOpt);
    checkAutoPlay = GetAttrValue<std::string>(node_, propNameAutoPlay);
    EXPECT_EQ(checkAutoPlay, EXPECTED_FALSE);
    checkAutoPlayOptions = GetAttrValue<std::string>(node_, propNameAutoPlayOptions);
    EXPECT_EQ(checkAutoPlayOptions, EXPECTED_TRUE);
}
/**
 * @tc.name: setIntervalTest
 * @tc.desc: Check the functionality of SwiperModifier.IntervalImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setIntervalTest, TestSize.Level1)
{
    constexpr auto propName = "interval";
    const std::string defaultValue(std::to_string(static_cast<int>(DEFAULT_SWIPER_AUTOPLAY_INTERVAL)));
    ASSERT_NE(modifier_->setInterval, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    auto numberInt = ArkValue<Opt_Int32>(123456);
    modifier_->setInterval(node_, &numberInt);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, "123456");

    auto numberFlt = ArkValue<Opt_Int32>(0);
    modifier_->setInterval(node_, &numberFlt);
    auto checkVal3 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal3, "0");

    auto numberIntNeg = ArkValue<Opt_Int32>(-1);
    modifier_->setInterval(node_, &numberIntNeg);
    auto checkVal4 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal4, defaultValue);
}

/**
 * @tc.name: setIndicatorTestDotPadding
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Dot type, the padding's subattr
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorTestDotPadding, TestSize.Level1)
{
    typedef std::tuple<Ark_DotIndicator, std::string> OneTestStep;
    constexpr auto propName = "indicator";
    const std::string &defaultValue(EXPECTED_VP_ZERO);
    const std::vector<OneTestStep> testPlan = {
    { { ._left = OPT_LEN_VP_POS, ._top = OPT_LEN_VP_POS, ._right = OPT_LEN_VP_POS, ._bottom = OPT_LEN_VP_POS,
        ._start = ArkValue<Opt_LengthMetrics>(), ._end = ArkValue<Opt_LengthMetrics>(),
        }, EXPECTED_VP_POS },
    { { ._left = OPT_LEN_VP_NEG, ._top = OPT_LEN_VP_NEG, ._right = OPT_LEN_VP_NEG, ._bottom = OPT_LEN_VP_NEG,
        ._start = ArkValue<Opt_LengthMetrics>(), ._end = ArkValue<Opt_LengthMetrics>(),
        }, defaultValue },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    const std::vector<std::string> keys = { "left", "right", "top", "bottom",
        // "start", "end" - these fields are not supported in SwiperPattern::GetDotIndicatorStyle()
    };
    for (const auto &[indicator, expect]: testPlan) {
        auto arkParam = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
            Ark_DotIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetAttrValue<std::string>(node_, propName);
        for (const auto &nameKey: keys) {
            auto checkPadding = GetAttrValue<std::string>(strWithObj, nameKey);
            EXPECT_EQ(checkPadding, expect);
        }
    }
}

/**
 * @tc.name: setIndicatorTestDotSize
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Dot type, the size's subattr
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setIndicatorTestDotSize, TestSize.Level1)
{
    typedef std::tuple<Ark_DotIndicator, std::string> OneTestStep;
    constexpr auto propName = "indicator";
    const std::string defaultSize = THEME_SWIPER_INDICATOR_SIZE.ToString();
    const std::vector<OneTestStep> testPlan = {
    { { ._itemWidth = OPT_LEN_VP_POS, ._itemHeight = OPT_LEN_VP_POS,
        ._selectedItemWidth = OPT_LEN_VP_POS, ._selectedItemHeight = OPT_LEN_VP_POS,
        }, EXPECTED_VP_POS },
    { { ._itemWidth = OPT_LEN_VP_NEG, ._itemHeight = OPT_LEN_VP_NEG,
        ._selectedItemWidth = OPT_LEN_VP_NEG, ._selectedItemHeight = OPT_LEN_VP_NEG,
        }, defaultSize },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    const std::vector<std::string> keys = {
        "itemWidth", "itemHeight", "selectedItemWidth", "selectedItemHeight"
    };
    for (const auto &[indicator, expect]: testPlan) {
        auto arkParam = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
            Ark_DotIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetAttrValue<std::string>(node_, propName);
        for (const auto &nameKey: keys) {
            auto checkVal = GetAttrValue<std::string>(strWithObj, nameKey);
            EXPECT_EQ(checkVal, expect);
        }
    }
}

/**
 * @tc.name: setIndicatorTestDotColor
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Dot type, the Color type subattr
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setIndicatorTestDotColor, TestSize.Level1)
{
    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    constexpr auto propName = "indicator";
    const std::string defaultValue(THEME_SWIPER_INDICATOR_COLOR.ToString());
    const std::string expectedResourceColor = Color::RED.ToString();
    const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
        { ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f), "#00000000" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
        { CreateResourceUnion<Ark_ResourceColor>(RES_NAME), expectedResourceColor },
        { CreateResourceUnion<Ark_ResourceColor>(RES_ID), expectedResourceColor },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    Ark_DotIndicator indicator = {
        ._color = ArkValue<Opt_ResourceColor>(Ark_Empty()),
        ._selectedColor = ArkValue<Opt_ResourceColor>(Ark_Empty())
    };
    auto arkParam = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
        Ark_DotIndicator>(indicator);
    modifier_->setIndicator(node_, &arkParam);
    auto strWithObj = GetAttrValue<std::string>(node_, propName);
    auto checkColorDflt = GetAttrValue<std::string>(strWithObj, "color");
    EXPECT_EQ(checkColorDflt, defaultValue);
    auto checkSelColorDflt = GetAttrValue<std::string>(strWithObj, "selectedColor");
    EXPECT_EQ(checkSelColorDflt, defaultValue);

    for (const auto &[arkResColor, expected]: testPlan) {
        Ark_DotIndicator indicator = {
            ._color = ArkValue<Opt_ResourceColor>(arkResColor),
            ._selectedColor = ArkValue<Opt_ResourceColor>(arkResColor)
        };
        auto arkParam = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
            Ark_DotIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetAttrValue<std::string>(node_, propName);
        auto checkColor = GetAttrValue<std::string>(strWithObj, "color");
        EXPECT_EQ(checkColor, expected);
        auto checkSelColor = GetAttrValue<std::string>(strWithObj, "selectedColor");
        EXPECT_EQ(checkSelColor, expected);
    }
}

/**
 * @tc.name: setIndicatorTestDotOther
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Dot type, the other subattr
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setIndicatorTestDotOther, TestSize.Level1)
{
    typedef std::tuple<Ark_DotIndicator, std::string, int> OneTestStep;
    constexpr auto propName = "indicator";
    const std::vector<OneTestStep> testPlan = {
        { { ._mask = OPT_BOOL_UNDEF, ._maxDisplayCount = ArkValue<Opt_Int32>(Ark_Empty()) },
            EXPECTED_FALSE, 0},
        { { ._mask = OPT_BOOL_TRUE, ._maxDisplayCount = ArkValue<Opt_Int32>(5325) },
            EXPECTED_TRUE, 5325 },
        { { ._mask = OPT_BOOL_FALSE, ._maxDisplayCount = ArkValue<Opt_Int32>(INT_MIN) },
            EXPECTED_FALSE, 0 },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    for (const auto &[indicator, expectMask, expectCount]: testPlan) {
        auto optParam = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
            Ark_DotIndicator>(indicator);
        modifier_->setIndicator(node_, &optParam);
        auto strWithObj = GetAttrValue<std::string>(node_, propName);
        auto checkMask = GetAttrValue<std::string>(strWithObj, "mask");
        EXPECT_EQ(checkMask, expectMask);
        auto checkMaxDispCnt = GetAttrValue<int>(strWithObj, "maxDisplayCount");
        EXPECT_EQ(checkMaxDispCnt, expectCount);
    }
}
/**
 * @tc.name: setIndicatorTestDigitPadding
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Digit indicator, padding's attributes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorTestDigitPadding, TestSize.Level1)
{
    typedef std::tuple<Ark_DigitIndicator, std::string> OneTestStep;
    constexpr auto propName = "indicator";
    constexpr auto defaultValue = "0.00vp";
    const std::vector<OneTestStep> testPlan = {
    { { ._left = OPT_LEN_VP_POS, ._top = OPT_LEN_VP_POS, ._right = OPT_LEN_VP_POS, ._bottom = OPT_LEN_VP_POS,
        ._start = ArkValue<Opt_LengthMetrics>(), ._end = ArkValue<Opt_LengthMetrics>(),
        }, EXPECTED_VP_POS },
    { { ._left = OPT_LEN_VP_NEG, ._top = OPT_LEN_VP_NEG, ._right = OPT_LEN_VP_NEG, ._bottom = OPT_LEN_VP_NEG,
        ._start = ArkValue<Opt_LengthMetrics>(), ._end = ArkValue<Opt_LengthMetrics>(),
        }, defaultValue },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    const std::vector<std::string> keys = { "left", "right", "top", "bottom",
        // "start", "end" - these fields are not supported in SwiperPattern::GetDigitIndicatorStyle()
    };
    for (const auto &[indicator, expect]: testPlan) {
        auto optParam = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
            Ark_DigitIndicator>(indicator);
        modifier_->setIndicator(node_, &optParam);
        auto strWithObj = GetAttrValue<std::string>(node_, propName);
        for (const auto &nameKey: keys) {
            auto checkVal = GetAttrValue<std::string>(strWithObj, nameKey);
            EXPECT_EQ(checkVal, expect);
        }
    }
}

/**
 * @tc.name: setIndicatorTestDigitFontSize
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Digit indicator, font size attributes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setIndicatorTestDigitFontSize, TestSize.Level1)
{
    typedef std::tuple<Ark_Font, std::string> OneTestStep;
    constexpr auto propName = "indicator";
    const std::string defaultValue(THEME_SWIPER_FONT_SIZE.ToString());
    const std::vector<OneTestStep> testPlan = {
        {{ .size = OPT_LEN_VP_POS }, EXPECTED_VP_POS},
        {{ .size = OPT_LEN_VP_NEG }, defaultValue},
        {{ .size = ArkValue<Opt_Length>(Ark_Empty()) }, defaultValue},
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    for (const auto &[font, expect]: testPlan) {
        Ark_DigitIndicator indicator = {
            ._digitFont = ArkValue<Opt_Font>(font),
            ._selectedDigitFont = ArkValue<Opt_Font>(font)
        };
        auto arkParam = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
            Ark_DigitIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetAttrValue<std::string>(node_, propName);
        auto checkFontSz = GetAttrValue<std::string>(strWithObj, "fontSize");
        EXPECT_EQ(checkFontSz, expect);
        auto checkSelFontSz = GetAttrValue<std::string>(strWithObj, "selectedFontSize");
        EXPECT_EQ(checkSelFontSz, expect);
    }
}

/**
 * @tc.name: setIndicatorTestDigitFontWeight
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Digit indicator, font weight attributes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorTestDigitFontWeight, TestSize.Level1)
{
    typedef Opt_Union_FontWeight_I32_String FontWeightT;
    typedef std::tuple<Ark_Font, std::string> OneTestStep;
    constexpr auto propName = "indicator";
    constexpr auto defaultValue = "FontWeight.Normal";
    const std::vector<OneTestStep> testPlan = {
        { {.weight = ArkUnion<FontWeightT, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD)}, "FontWeight.Bold" },
        { {.weight = ArkUnion<FontWeightT, Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR)}, "FontWeight.Regular" },
        { {.weight = ArkUnion<FontWeightT, Ark_Int32>(100)}, "100" },
        { {.weight = ArkUnion<FontWeightT, Ark_Int32>(-111)}, defaultValue },
        { {.weight = ArkUnion<FontWeightT, Ark_Int32>(300)}, "300" },
        { {.weight = ArkUnion<FontWeightT, Ark_Int32>(-123)}, defaultValue },
        { {.weight = ArkUnion<FontWeightT, Ark_String>("700")}, "700" },
        { {.weight = ArkUnion<FontWeightT, Ark_String>("bold")}, "FontWeight.Bold" },
        { {.weight = ArkUnion<FontWeightT, Ark_String>("InvalidData!")}, defaultValue },
        { {.weight = ArkValue<FontWeightT>(Ark_Empty())}, defaultValue },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    {
        Ark_DigitIndicator indicator = {
            ._digitFont = ArkValue<Opt_Font>(Ark_Empty()),
            ._selectedDigitFont = ArkValue<Opt_Font>(Ark_Empty()),
        };
        auto arkParam = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
            Ark_DigitIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetAttrValue<std::string>(node_, propName);
        auto checkFontWeightDftl = GetAttrValue<std::string>(strWithObj, "fontWeight");
        EXPECT_EQ(checkFontWeightDftl, defaultValue);
        auto checkSelFontWeightDftl = GetAttrValue<std::string>(strWithObj, "selectedFontWeight");
        EXPECT_EQ(checkSelFontWeightDftl, defaultValue);
    }
    for (const auto &[font, expect]: testPlan) {
        Ark_DigitIndicator indicator = {
            ._digitFont = ArkValue<Opt_Font>(font),
            ._selectedDigitFont = ArkValue<Opt_Font>(font)
        };
        auto arkParam = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
            Ark_DigitIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetAttrValue<std::string>(node_, propName);
        auto checkFontWeight = GetAttrValue<std::string>(strWithObj, "fontWeight");
        EXPECT_EQ(checkFontWeight, expect);
        auto checkSelFontWeight = GetAttrValue<std::string>(strWithObj, "selectedFontWeight");
        EXPECT_EQ(checkSelFontWeight, expect);
    }
}

/**
 * @tc.name: setIndicatorTestDigitFontColor
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Digit Indicator, the Color type subattributes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setIndicatorTestDigitFontColor, TestSize.Level1)
{
    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    constexpr auto propName = "indicator";
    const std::string defaultValue(Color::TRANSPARENT.ToString());
    const std::string expectedResourceColor = Color::RED.ToString();
    const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
        { ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f), "#00000000" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
        { CreateResourceUnion<Ark_ResourceColor>(RES_NAME), expectedResourceColor },
        { CreateResourceUnion<Ark_ResourceColor>(RES_ID), expectedResourceColor },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    Ark_DigitIndicator indicator = {
        ._fontColor = ArkValue<Opt_ResourceColor>(Ark_Empty()),
        ._selectedFontColor = ArkValue<Opt_ResourceColor>(Ark_Empty())
    };
    auto arkParam = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
        Ark_DigitIndicator>(indicator);
    modifier_->setIndicator(node_, &arkParam);
    auto strWithObj = GetAttrValue<std::string>(node_, propName);
    auto checkColorDflt = GetAttrValue<std::string>(strWithObj, "fontColor");
    EXPECT_EQ(checkColorDflt, defaultValue);
    auto checkSelColorDflt = GetAttrValue<std::string>(strWithObj, "selectedFontColor");
    EXPECT_EQ(checkSelColorDflt, defaultValue);

    for (const auto &[arkResColor, expected]: testPlan) {
        Ark_DigitIndicator indicator = {
            ._fontColor = ArkValue<Opt_ResourceColor>(arkResColor),
            ._selectedFontColor = ArkValue<Opt_ResourceColor>(arkResColor)
        };
        auto arkParam = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
            Ark_DigitIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetAttrValue<std::string>(node_, propName);
        auto checkColor = GetAttrValue<std::string>(strWithObj, "fontColor");
        EXPECT_EQ(checkColor, expected);
        auto checkSelColor = GetAttrValue<std::string>(strWithObj, "selectedFontColor");
        EXPECT_EQ(checkSelColor, expected);
    }
}

/**
 * @tc.name: setIndicatorTestBoolean
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Boolean type
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorTestBoolean, TestSize.Level1)
{
    constexpr auto propName = "indicator";
    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    auto boolIndFalse = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
        Ark_Boolean>(ABOOL_FALSE);
    modifier_->setIndicator(node_, &boolIndFalse);
    auto checkFalse = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkFalse, EXPECTED_FALSE);

    auto boolIndTrue = ArkUnion<Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean,
        Ark_Boolean>(ABOOL_TRUE);
    modifier_->setIndicator(node_, &boolIndTrue);
    auto checkTrue = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkTrue, EXPECTED_TRUE);
}

/**
 * @tc.name: setDisplayArrowTestStyleShowBg
 * @tc.desc: Check the functionality of SwiperModifier.setDisplayArrow with the Style size subattruibutes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayArrowTestStyleShowBg, TestSize.Level1)
{
    constexpr auto propName = "showBackground";
    const std::string defaultValue = EXPECTED_FALSE;

    ASSERT_NE(modifier_->setDisplayArrow, nullptr);

    auto checkValInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkValInitial, defaultValue);

    Ark_Union_ArrowStyle_Boolean arkParam1 = {.selector=0, .value0={.showBackground = OPT_BOOL_TRUE}};
    auto optParam = Converter::ArkValue<Opt_Union_ArrowStyle_Boolean>(arkParam1);
    modifier_->setDisplayArrow(node_, &optParam, nullptr);
    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    Ark_Union_ArrowStyle_Boolean arkParam2 = {.selector=0, .value0={.showBackground = OPT_BOOL_FALSE}};
    optParam = Converter::ArkValue<Opt_Union_ArrowStyle_Boolean>(arkParam2);
    modifier_->setDisplayArrow(node_, &optParam, nullptr);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, EXPECTED_FALSE);

    Ark_Union_ArrowStyle_Boolean arkParam3 = {.selector=0, .value0={.showBackground = OPT_BOOL_UNDEF}};
    optParam = Converter::ArkValue<Opt_Union_ArrowStyle_Boolean>(arkParam3);
    modifier_->setDisplayArrow(node_, &optParam, nullptr);
    auto checkVal3 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal3, defaultValue);
}

/**
 * @tc.name: setDisplayArrowTestStyleSize
 * @tc.desc: Check the functionality of SwiperModifier.setDisplayArrow with the Style size subattruibutes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setDisplayArrowTestStyleSize, TestSize.Level1)
{
    typedef std::tuple<Ark_ArrowStyle, std::string> OneTestStep;
    constexpr auto propName = "arrowSize";
    const std::string &defaultValueS(EXPECTED_VP_ZERO);
    const std::string &defaultValueB(EXPECTED_VP_ZERO);
    const std::vector<OneTestStep> testPlan = {
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .arrowSize = OPT_LEN_VP_POS}, "1.23vp" },
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .arrowSize = OPT_LEN_VP_NEG}, defaultValueS },
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .arrowSize = OPT_LEN_UNDEF}, defaultValueS },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .arrowSize = OPT_LEN_VP_POS}, "1.23vp" },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .arrowSize = OPT_LEN_VP_NEG}, defaultValueB },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .arrowSize = OPT_LEN_UNDEF}, defaultValueB },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .arrowSize = OPT_LEN_VP_POS}, "1.23vp" },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .arrowSize = OPT_LEN_VP_NEG}, defaultValueS },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .arrowSize = OPT_LEN_UNDEF}, defaultValueS },
    };

    ASSERT_NE(modifier_->setDisplayArrow, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, "0.00vp");

    for (const auto &[style, expect]: testPlan) {
        Ark_Union_ArrowStyle_Boolean arkParam = {
            .selector = 0, .value0 = style
        };
        auto optParam = Converter::ArkValue<Opt_Union_ArrowStyle_Boolean>(arkParam);
        modifier_->setDisplayArrow(node_, &optParam, nullptr);
        auto checkVal2 = GetAttrValue<std::string>(node_, propName);
        EXPECT_EQ(checkVal2, expect);
        auto checkVal3 = GetAttrValue<std::string>(node_, "isSidebarMiddle");
        auto optExp3 = Converter::OptConvert<bool>(style.isSidebarMiddle);
        bool expect3 = optExp3 && *optExp3;
        EXPECT_EQ(checkVal3, expect3 ? EXPECTED_TRUE : EXPECTED_FALSE);
    }
}

/**
 * @tc.name: setDisplayArrowTestStyleBgSize
 * @tc.desc: Check the functionality of SwiperModifier.setDisplayArrow with the Style, bg size subattruibutes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setDisplayArrowTestStyleBgSize, TestSize.Level1)
{
    typedef std::tuple<Ark_ArrowStyle, std::string> OneTestStep;
    constexpr auto propName = "arrowBackgroundSize";
    const std::string &defaultValueS(EXPECTED_VP_ZERO);
    const std::string &defaultValueB(EXPECTED_VP_ZERO);
    const std::vector<OneTestStep> testPlan = {
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .backgroundSize = OPT_LEN_VP_POS}, "1.23vp" },
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .backgroundSize = OPT_LEN_VP_NEG}, defaultValueS },
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .backgroundSize = OPT_LEN_UNDEF}, defaultValueS },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .backgroundSize = OPT_LEN_VP_POS}, "1.23vp" },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .backgroundSize = OPT_LEN_VP_NEG}, defaultValueB },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .backgroundSize = OPT_LEN_UNDEF}, defaultValueB },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .backgroundSize = OPT_LEN_VP_POS}, "1.23vp" },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .backgroundSize = OPT_LEN_VP_NEG}, defaultValueS },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .backgroundSize = OPT_LEN_UNDEF}, defaultValueS },
    };

    ASSERT_NE(modifier_->setDisplayArrow, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, "0.00vp");

    for (const auto &[style, expect]: testPlan) {
        Ark_Union_ArrowStyle_Boolean arkParam = {
            .selector = 0, .value0 = style
        };
        auto optParam = Converter::ArkValue<Opt_Union_ArrowStyle_Boolean>(arkParam);
        modifier_->setDisplayArrow(node_, &optParam, nullptr);
        auto checkVal2 = GetAttrValue<std::string>(node_, propName);
        EXPECT_EQ(checkVal2, expect);
    }
}

/**
 * @tc.name: setDisplayArrowTestStyleColorDefault
 * @tc.desc: Check the functionality of SwiperModifier.DisplayArrowImpl with Style, the Color's default and init
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setDisplayArrowTestStyleColorDefault, TestSize.Level1)
{
    const std::string defaultValue = Color::TRANSPARENT.ToString();
    {
        auto initArrowColor = GetAttrValue<std::string>(node_, "arrowColor");
        EXPECT_EQ(initArrowColor, Color::TRANSPARENT.ToString());
        auto initArrowBgColor = GetAttrValue<std::string>(node_, "arrowBackgroundColor");
        EXPECT_EQ(initArrowBgColor, Color::TRANSPARENT.ToString());
    }
    {
        Ark_Union_ArrowStyle_Boolean arkParam = { .selector = 0, .value0 = {
            .isSidebarMiddle = OPT_BOOL_FALSE,
            .arrowColor = OPT_COLOR_UNDEF,
            .backgroundColor = OPT_COLOR_UNDEF,
        } };
        auto optParam = Converter::ArkValue<Opt_Union_ArrowStyle_Boolean>(arkParam);
        modifier_->setDisplayArrow(node_, &optParam, nullptr);
        auto defaultSmallArrowColor = GetAttrValue<std::string>(node_, "arrowColor");
        EXPECT_EQ(defaultSmallArrowColor, defaultValue);
        auto defaultSmallArrowBgColor = GetAttrValue<std::string>(node_, "arrowBackgroundColor");
        EXPECT_EQ(defaultSmallArrowBgColor, Color::TRANSPARENT.ToString());
    }
    {
        Ark_Union_ArrowStyle_Boolean arkParam = { .selector = 0, .value0 = {
            .isSidebarMiddle = OPT_BOOL_TRUE,
            .arrowColor = OPT_COLOR_UNDEF,
            .backgroundColor = OPT_COLOR_UNDEF,
        } };
        auto optParam = Converter::ArkValue<Opt_Union_ArrowStyle_Boolean>(arkParam);
        modifier_->setDisplayArrow(node_, &optParam, nullptr);
        auto defaultBigArrowColor = GetAttrValue<std::string>(node_, "arrowColor");
        EXPECT_EQ(defaultBigArrowColor, defaultValue);
        auto defaultBigArrowBgColor = GetAttrValue<std::string>(node_, "arrowBackgroundColor");
        EXPECT_EQ(defaultBigArrowBgColor, defaultValue);
    }
}

/**
 * @tc.name: setDisplayArrowTestStyleColor
 * @tc.desc: Check the functionality of SwiperModifier.DisplayArrowImpl with Style, the Color's subattributes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setDisplayArrowTestStyleColor, TestSize.Level1)
{
    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    const std::string expectedResourceColor = Color::RED.ToString();
    const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
        { ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f), "#00000000" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
        { CreateResourceUnion<Ark_ResourceColor>(RES_NAME), expectedResourceColor },
        { CreateResourceUnion<Ark_ResourceColor>(RES_ID), expectedResourceColor },
    };

    ASSERT_NE(modifier_->setDisplayArrow, nullptr);

    for (const auto &[arkResColor, expected]: testPlan) {
        Ark_ArrowStyle style = {
             .arrowColor = ArkValue<Opt_ResourceColor>(arkResColor),
             .backgroundColor = ArkValue<Opt_ResourceColor>(arkResColor)
        };
        auto arkParam = ArkUnion<Opt_Union_ArrowStyle_Boolean, Ark_ArrowStyle>(style);
        modifier_->setDisplayArrow(node_, &arkParam, nullptr);
        auto checkColor = GetAttrValue<std::string>(node_, "arrowColor");
        EXPECT_EQ(checkColor, expected);
        auto checkBgColor = GetAttrValue<std::string>(node_, "arrowBackgroundColor");
        EXPECT_EQ(checkBgColor, expected);
    }
}

/**
 * @tc.name: setDisplayArrowTestBoolean
 * @tc.desc: Check the functionality of SwiperModifier.setDisplayArrow with Boolean type
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayArrowTestBoolean, TestSize.Level1)
{
    constexpr auto propName = "displayArrow";
    constexpr auto propNameExt = "hoverShow";
    ASSERT_NE(modifier_->setDisplayArrow, nullptr);

    auto isDisplayArrowDefault = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(isDisplayArrowDefault, EXPECTED_FALSE);
    auto isHoverShowDefault = GetAttrValue<std::string>(node_, propNameExt);
    EXPECT_EQ(isHoverShowDefault, EXPECTED_FALSE);

    auto boolFalse = ArkUnion<Opt_Union_ArrowStyle_Boolean, Ark_Boolean>(ABOOL_FALSE);
    modifier_->setDisplayArrow(node_, &boolFalse, nullptr);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, EXPECTED_FALSE);
    auto checkVal2x = GetAttrValue<std::string>(node_, propNameExt);
    EXPECT_EQ(checkVal2x, EXPECTED_FALSE);

    auto boolIndTrue = ArkUnion<Opt_Union_ArrowStyle_Boolean, Ark_Boolean>(ABOOL_TRUE);
    modifier_->setDisplayArrow(node_, &boolIndTrue, nullptr);
    auto checkVal3 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal3, EXPECTED_TRUE);
    auto checkVal3x = GetAttrValue<std::string>(node_, propNameExt);
    EXPECT_EQ(checkVal3x, EXPECTED_FALSE);

    modifier_->setDisplayArrow(node_, &boolIndTrue, &OPT_BOOL_TRUE);
    auto checkVal4x = GetAttrValue<std::string>(node_, propNameExt);
    EXPECT_EQ(checkVal4x, EXPECTED_TRUE);

    modifier_->setDisplayArrow(node_, &boolIndTrue, &OPT_BOOL_UNDEF);
    auto checkVal5x = GetAttrValue<std::string>(node_, propNameExt);
    EXPECT_EQ(checkVal5x, EXPECTED_TRUE); // nothing change

    modifier_->setDisplayArrow(node_, &boolIndTrue, &OPT_BOOL_FALSE);
    auto checkVal6x = GetAttrValue<std::string>(node_, propNameExt);
    EXPECT_EQ(checkVal6x, EXPECTED_FALSE);

    modifier_->setDisplayArrow(node_, &boolIndTrue, &OPT_BOOL_UNDEF);
    auto checkVal7x = GetAttrValue<std::string>(node_, propNameExt);
    EXPECT_EQ(checkVal7x, EXPECTED_FALSE); // nothing change
}
/**
 * @tc.name: setLoopTest
 * @tc.desc: Check the functionality of SwiperModifier.LoopImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setLoopTest, TestSize.Level1)
{
    constexpr auto propName = "loop";
    const std::string &defaultValue(EXPECTED_TRUE);
    ASSERT_NE(modifier_->setLoop, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    modifier_->setLoop(node_, &OPT_BOOL_TRUE);
    auto checkTrue = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkTrue, EXPECTED_TRUE);

    modifier_->setLoop(node_, &OPT_BOOL_FALSE);
    auto checkFalse = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkFalse, EXPECTED_FALSE);
}
/**
 * @tc.name: setDurationTest
 * @tc.desc: Check the functionality of SwiperModifier.DurationImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setDurationTest, TestSize.Level1)
{
    constexpr auto propName = "duration";
    const std::string defaultValue(std::to_string(static_cast<int32_t>(DEFAULT_SWIPER_ANIMATION_DURATION)));
    ASSERT_NE(modifier_->setDuration, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    auto numberInt = ArkValue<Opt_Int32>(123456);
    modifier_->setDuration(node_, &numberInt);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, "123456");

    auto numberFlt = ArkValue<Opt_Int32>(1);
    modifier_->setDuration(node_, &numberFlt);
    auto checkVal3 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal3, "1");

    auto numberIntNeg = ArkValue<Opt_Int32>(-1);
    modifier_->setDuration(node_, &numberIntNeg);
    auto checkVal4 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal4, defaultValue);
}
/**
 * @tc.name: setVerticalTest
 * @tc.desc: Check the functionality of SwiperModifier.VerticalImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setVerticalTest, TestSize.Level1)
{
    constexpr auto propName = "vertical";
    const std::string defaultValue(EXPECTED_FALSE);
    ASSERT_NE(modifier_->setVertical, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    modifier_->setVertical(node_, &OPT_BOOL_TRUE);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setVertical(node_, &OPT_BOOL_FALSE);
    auto checkVal3 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);
}
/**
 * @tc.name: setItemSpaceTest
 * @tc.desc: Check the functionality of SwiperModifier.ItemSpaceImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setItemSpaceTest, TestSize.Level1)
{
    using namespace Converter;
    using TypeArg0 = Opt_Union_F64_String;
    using OneTestStep = std::pair<TypeArg0, std::string>;
    constexpr auto propName = "itemSpace";
    const std::string &defaultValue(EXPECTED_VP_ZERO);
    const std::vector<OneTestStep> testPlan = {
        { ArkUnion<TypeArg0, Ark_Float64>(1234), "1234.00vp"},
        { ArkUnion<TypeArg0, Ark_Float64>(AINT32_NEG), defaultValue},
        { ArkUnion<TypeArg0, Ark_Float64>(1.234), "1.23vp"},
        { ArkUnion<TypeArg0, Ark_Float64>(AFLT32_NEG), defaultValue},
        { ArkUnion<TypeArg0, Ark_String>("7.89px"), "7.89px"},
        { ArkUnion<TypeArg0, Ark_String>("-4.5px"), defaultValue},
        { ArkUnion<TypeArg0, Ark_String>("1.2345vp"), "1.23vp"},
        { ArkUnion<TypeArg0, Ark_String>("-56vp"), defaultValue},
    };

    ASSERT_NE(modifier_->setItemSpace, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    for (const auto &[itemSpace, expected]: testPlan) {
        modifier_->setItemSpace(node_, &itemSpace);
        auto checkVal = GetAttrValue<std::string>(node_, propName);
        EXPECT_EQ(checkVal, expected);
    }
}
/**
 * @tc.name: setDisplayModeTest
 * @tc.desc: Check the functionality of SwiperModifier.DisplayModeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setDisplayModeTest, TestSize.Level1)
{
    constexpr auto propName = "displayMode";
    constexpr auto defaultValue = "SwiperDisplayMode.Stretch"; // corrrsponds to
    // SwiperDisplayMode::STRETCH in frameworks/core/components/declaration/swiper/swiper_declaration.h
    ASSERT_NE(modifier_->setDisplayMode, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    auto mode = Converter::ArkValue<Opt_SwiperDisplayMode>(ARK_SWIPER_DISPLAY_MODE_STRETCH);
    modifier_->setDisplayMode(node_, &mode);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, "SwiperDisplayMode.Stretch");

    auto arkValue2 = static_cast<Ark_SwiperDisplayMode>(INT_MAX);
    mode = Converter::ArkValue<Opt_SwiperDisplayMode>(arkValue2);
    modifier_->setDisplayMode(node_, &mode);
    auto checkVal4 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, "SwiperDisplayMode.Stretch");

    auto arkValue3 = static_cast<Ark_SwiperDisplayMode>(INT_MIN);
    mode = Converter::ArkValue<Opt_SwiperDisplayMode>(arkValue3);
    modifier_->setDisplayMode(node_, &mode);
    auto checkVal5 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, "SwiperDisplayMode.Stretch");
}
/**
 * @tc.name: setCachedCountTest
 * @tc.desc: Check the functionality of SwiperModifier.CachedCountImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setCachedCountTest, TestSize.Level1)
{
    constexpr auto propName = "cachedCount";
    const int defaultValue(DEFAULT_SWIPER_CACHED_SIZE);
    ASSERT_NE(modifier_->setCachedCount0, nullptr);

    auto checkInitial = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    auto numberInt = ArkValue<Opt_Int32>(123456);
    modifier_->setCachedCount0(node_, &numberInt);
    auto checkVal2 = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkVal2, 123456);

    auto numberFlt = ArkValue<Opt_Int32>(1);
    modifier_->setCachedCount0(node_, &numberFlt);
    auto checkVal3 = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkVal3, 1);

    auto numberIntNeg = ArkValue<Opt_Int32>(-111);
    modifier_->setCachedCount0(node_, &numberIntNeg);
    auto checkVal4 = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkVal4, defaultValue);
}

/**
 * @tc.name: setCachedCount1Test
 * @tc.desc: Check the functionality of SwiperModifier.CachedCount1Impl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setCachedCount1Test, TestSize.Level1)
{
    const std::string propNameCount("cachedCount");
    const int defaultValueCount(DEFAULT_SWIPER_CACHED_SIZE);
    const std::string propNameShown("cachedIsShown");
    const std::string &defaultValueShown(EXPECTED_FALSE);
    ASSERT_NE(modifier_->setCachedCount1, nullptr);

    auto checkCount = GetAttrValue<int>(node_, propNameCount);
    EXPECT_EQ(checkCount, defaultValueCount);
    auto checkShown = GetAttrValue<std::string>(node_, propNameShown);
    EXPECT_EQ(checkShown, defaultValueShown);

    auto numberInt = ArkValue<Opt_Int32>(123456);
    auto isShown = ArkValue<Opt_Boolean>(true);
    modifier_->setCachedCount1(node_, &numberInt, &isShown);
    checkCount = GetAttrValue<int>(node_, propNameCount);
    EXPECT_EQ(checkCount, 123456);
    checkShown = GetAttrValue<std::string>(node_, propNameShown);
    EXPECT_EQ(checkShown, EXPECTED_TRUE);

    auto numberFlt = ArkValue<Opt_Int32>(1);
    isShown = ArkValue<Opt_Boolean>(false);
    modifier_->setCachedCount1(node_, &numberFlt, &isShown);
    checkCount = GetAttrValue<int>(node_, propNameCount);
    EXPECT_EQ(checkCount, 1);
    checkShown = GetAttrValue<std::string>(node_, propNameShown);
    EXPECT_EQ(checkShown, EXPECTED_FALSE);

    auto numberIntNeg = ArkValue<Opt_Int32>(-111);
    isShown = ArkValue<Opt_Boolean>(true);
    modifier_->setCachedCount1(node_, &numberIntNeg, &isShown);
    checkCount = GetAttrValue<int>(node_, propNameCount);
    EXPECT_EQ(checkCount, defaultValueCount);
    checkShown = GetAttrValue<std::string>(node_, propNameShown);
    EXPECT_EQ(checkShown, EXPECTED_TRUE);

    auto numberFltNeg = ArkValue<Opt_Int32>(-1);
    isShown = ArkValue<Opt_Boolean>(false);
    modifier_->setCachedCount1(node_, &numberFltNeg, &isShown);
    checkCount = GetAttrValue<int>(node_, propNameCount);
    EXPECT_EQ(checkCount, defaultValueCount);
    checkShown = GetAttrValue<std::string>(node_, propNameShown);
    EXPECT_EQ(checkShown, EXPECTED_FALSE);
}
/**
 * @tc.name: setDisplayCountTestNumber
 * @tc.desc: Check the functionality of SwiperModifier.DisplayCountImpl with Ark_Number arg
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayCountTestNumber, TestSize.Level1)
{
    constexpr auto propName = "displayCount";
    const int defaultValue(DEFAULT_SWIPER_DISPLAY_COUNT);
    ASSERT_NE(modifier_->setDisplayCount, nullptr);

    auto checkInitial = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    auto numberInt = ArkUnion<Opt_Union_I32_String_SwiperAutoFill, Ark_Int32>(123456);
    modifier_->setDisplayCount(node_, &numberInt, nullptr);
    auto checkVal2 = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkVal2, 123456);

    auto numberFlt = ArkUnion<Opt_Union_I32_String_SwiperAutoFill, Ark_Int32>(1);
    modifier_->setDisplayCount(node_, &numberFlt, nullptr);
    auto checkVal3 = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkVal3, 1);

    auto numberIntNeg = ArkUnion<Opt_Union_I32_String_SwiperAutoFill, Ark_Int32>(-111);
    modifier_->setDisplayCount(node_, &numberIntNeg, nullptr);
    auto checkVal4 = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkVal4, defaultValue);

    auto numberFltNeg = ArkUnion<Opt_Union_I32_String_SwiperAutoFill, Ark_Int32>(-1);
    modifier_->setDisplayCount(node_, &numberFltNeg, nullptr);

    auto checkVal5 = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkVal5, defaultValue);
}
/**
 * @tc.name: setDisplayCountTestString
 * @tc.desc: Check the functionality of SwiperModifier.DisplayCountImpl with Ark_String arg
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayCountTestString, TestSize.Level1)
{
    constexpr auto propName = "displayCount";
    const int defaultValue(DEFAULT_SWIPER_DISPLAY_COUNT);
    ASSERT_NE(modifier_->setDisplayCount, nullptr);

    auto checkInitial = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    auto regularVal = ArkUnion<Opt_Union_I32_String_SwiperAutoFill, Ark_String>("1234");
    modifier_->setDisplayCount(node_, &regularVal, nullptr);
    auto checkVal2 = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkVal2, 1234);

    auto arkValue0 = ArkValue<Opt_SwiperDisplayMode>(ARK_SWIPER_DISPLAY_MODE_STRETCH);
    modifier_->setDisplayMode(node_, &arkValue0);
    auto autoVal = ArkUnion<Opt_Union_I32_String_SwiperAutoFill, Ark_String>("auto");
    modifier_->setDisplayCount(node_, &autoVal, nullptr);
    auto checkVal3 = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkVal3, defaultValue);
    auto checkValDispMode= GetAttrValue<std::string>(node_, "displayMode");
    EXPECT_EQ(checkValDispMode, "SwiperDisplayMode.AutoLinear");

    auto negVal = ArkUnion<Opt_Union_I32_String_SwiperAutoFill, Ark_String>("-1234");
    modifier_->setDisplayCount(node_, &negVal, nullptr);
    auto checkVal4 = GetAttrValue<int>(node_, propName);
    EXPECT_EQ(checkVal4, defaultValue);
}

/**
 * @tc.name: setDisplayCountTestObj
 * @tc.desc: Check the functionality of SwiperModifier.DisplayCountImpl with Ark_VP object argument
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setDisplayCountTestObj, TestSize.Level1)
{
    typedef Opt_Union_I32_String_SwiperAutoFill displayCountArgT;
    typedef Ark_SwiperAutoFill checkT;
    constexpr auto propName = "minSize";
    const std::string &defaultValue(EXPECTED_VP_ZERO);
    ASSERT_NE(modifier_->setDisplayCount, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    auto intVal = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_Float64>(123)));
    modifier_->setDisplayCount(node_, &intVal, nullptr);
    auto checkInt = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInt, "123.00vp");

    auto floatVal = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_Float64>(1.23f)));
    modifier_->setDisplayCount(node_, &floatVal, nullptr);
    auto checkFloat = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkFloat, "1.23vp");

    auto strPx = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_String>("45px")));
    modifier_->setDisplayCount(node_, &strPx, nullptr);
    auto checkStrPx = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkStrPx, "45.00px");

    auto strVp = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_String>("5.60vp")));
    modifier_->setDisplayCount(node_, &strVp, nullptr);
    auto checkStrVp = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkStrVp, "5.60vp");

    auto intNegVal = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_Float64>(-123)));
    modifier_->setDisplayCount(node_, &intNegVal, nullptr);
    auto checkIntNeg = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkIntNeg, defaultValue);

    auto floatNegVal = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_Float64>(-1.23f)));
    modifier_->setDisplayCount(node_, &floatNegVal, nullptr);
    auto checkFloatNeg = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkFloatNeg, defaultValue);

    auto strPxNeg = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_String>("-4.5px")));
    modifier_->setDisplayCount(node_, &strPxNeg, nullptr);
    auto checkStrPxNeg = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkStrPxNeg, defaultValue);

    auto strVpNeg = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_String>("-56vp")));
    modifier_->setDisplayCount(node_, &strVpNeg, nullptr);
    auto checkStrVpNeg = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkStrVpNeg, defaultValue);
}

/**
 * @tc.name: setDisplayCountTestByGroup
 * @tc.desc: Check the functionality of SwiperModifier.DisplayCountImpl with ByGroup optional
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayCountTestByGroup, TestSize.Level1)
{
    constexpr auto propName = "swipeByGroup";
    const std::string defaultValue(EXPECTED_FALSE);
    ASSERT_NE(modifier_->setDisplayCount, nullptr);

    Opt_Union_I32_String_SwiperAutoFill aceFakeArg0;

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    modifier_->setDisplayCount(node_, &aceFakeArg0, &OPT_BOOL_TRUE);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setDisplayCount(node_, &aceFakeArg0, nullptr);
    auto checkVal2opt = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2opt, EXPECTED_TRUE); // nothing change if no optional arg

    modifier_->setDisplayCount(node_, &aceFakeArg0, &OPT_BOOL_FALSE);
    auto checkVal3 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);

    modifier_->setDisplayCount(node_, &aceFakeArg0, nullptr);
    auto checkVal3opt = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal3opt, EXPECTED_FALSE); // nothing change if no optional arg
}

/**
 * @tc.name: setEffectModeTest
 * @tc.desc: Check the functionality of SwiperModifier.EffectModeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setEffectModeTest, TestSize.Level1)
{
    constexpr auto propName = "effectMode";
    constexpr auto defaultValue = "EdgeEffect.Spring";
    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    auto effect = Converter::ArkValue<Opt_EdgeEffect>(ARK_EDGE_EFFECT_SPRING);
    modifier_->setEffectMode(node_, &effect);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, "EdgeEffect.Spring");

    effect = Converter::ArkValue<Opt_EdgeEffect>(ARK_EDGE_EFFECT_FADE);
    modifier_->setEffectMode(node_, &effect);
    auto checkVal3 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal3, "EdgeEffect.Fade");
    auto arkValue2 = static_cast<Ark_EdgeEffect>(INT_MAX);
    effect = Converter::ArkValue<Opt_EdgeEffect>(arkValue2);
    modifier_->setEffectMode(node_, &effect);
    auto checkVal4 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal4, defaultValue);
    auto arkValue3 = static_cast<Ark_EdgeEffect>(INT_MIN);
    effect = Converter::ArkValue<Opt_EdgeEffect>(arkValue3);
    modifier_->setEffectMode(node_, &effect);
    auto checkVal5 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal5, defaultValue);
}
/**
 * @tc.name: setDisableSwipeTest
 * @tc.desc: Check the functionality of SwiperModifier.DisableSwipeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisableSwipeTest, TestSize.Level1)
{
    constexpr auto propName = "disableSwipe";
    const std::string defaultValue(EXPECTED_FALSE);
    ASSERT_NE(modifier_->setDisableSwipe, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    modifier_->setDisableSwipe(node_, &OPT_BOOL_TRUE);
    auto checkVal2 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setDisableSwipe(node_, &OPT_BOOL_FALSE);
    auto checkVal3 = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);
}
/**
 * @tc.name: setCurveTestBuiltIn
 * @tc.desc: Check the functionality of SwiperModifier.CurveImpl for built-in curves
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setCurveTestBuiltIn, TestSize.Level1)
{
    constexpr auto propName = "curve";
    const std::string defaultValue(Curves::ToString(Curves::EASE_IN_OUT));
    ASSERT_NE(modifier_->setCurve, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, Curves::DEFAULT_CURVE_NAME);

    auto arkCurveEasyIn =
        ArkUnion<Opt_Union_Curve_String_ICurve, Ark_curves_Curve>(ARK_CURVES_CURVE_EASE_IN);
    modifier_->setCurve(node_, &arkCurveEasyIn);
    auto checkEasyIO = GetAttrValue<std::string>(node_, propName);
    auto expectedCurveEasyIn =
        Framework::CreateCurve(Framework::CurveIntToString(ArkUI_AnimationCurve::ARKUI_CURVE_EASE_IN));
    EXPECT_EQ(checkEasyIO, Curves::ToString(expectedCurveEasyIn));

    modifier_->setCurve(node_, nullptr);
    auto checkNull = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkNull, Curves::ToString(expectedCurveEasyIn));

    auto arkCurveLinear =
        ArkUnion<Opt_Union_Curve_String_ICurve, Ark_curves_Curve>(ARK_CURVES_CURVE_LINEAR);
    modifier_->setCurve(node_, &arkCurveLinear);
    auto checkLinear = GetAttrValue<std::string>(node_, propName);
    auto expectedCurveLinear =
        Framework::CreateCurve(Framework::CurveIntToString(ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR));
    EXPECT_EQ(checkLinear, Curves::ToString(expectedCurveLinear));

    auto arkCurveInv = ArkUnion<Opt_Union_Curve_String_ICurve, Ark_curves_Curve>(INVALID_ENUM_VAL<Ark_curves_Curve>);
    modifier_->setCurve(node_, &arkCurveInv);
    auto checkInv = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInv, defaultValue);
}
/**
 * @tc.name: setCurveTestCustom
 * @tc.desc: Check the functionality of SwiperModifier.CurveImpl for Custom curves
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setCurveTestCustom, TestSize.Level1)
{
    constexpr auto propName = "curve";
    const std::string defaultValue(Curves::ToString(Curves::EASE_IN_OUT));
    ASSERT_NE(modifier_->setCurve, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, Curves::DEFAULT_CURVE_NAME);

    auto arkCurveCustom = ArkUnion<Opt_Union_Curve_String_ICurve, Ark_String>("interpolating-spring(1, 1, 28, 34)");
    modifier_->setCurve(node_, &arkCurveCustom);
    auto checkCustStr = GetAttrValue<std::string>(node_, propName);
    // this can't be exactly check due to SwiperPaintProperty::ToJsonValue supports the built-in Curves only
    EXPECT_NE(checkCustStr, defaultValue);

    auto arkCurveInv = ArkUnion<Opt_Union_Curve_String_ICurve, Ark_String>("invalidCurveDefinition");
    modifier_->setCurve(node_, &arkCurveInv);
    auto checkInv = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInv, defaultValue);
}

/**
 * @tc.name: setOnChangeTest
 * @tc.desc: Check the functionality of SwiperModifier.OnChangeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setOnChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int32_t index;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto checkCallback =
        [](const Ark_Int32 resourceId, const Ark_Int32 index) {
            checkEvent = {
                .nodeId = resourceId,
                .index = Converter::Convert<Ark_Int32>(index)
            };
        };
    auto func = Converter::ArkValue<Callback_I32_Void>(checkCallback, CONTEXT_ID);
    auto optCallback = Converter::ArkValue<Opt_Callback_I32_Void>(func);

    ASSERT_NE(modifier_->setOnChange, nullptr);

    modifier_->setOnChange(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent(0, 321, false);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, CONTEXT_ID);
    EXPECT_EQ(checkEvent->index, 321);
}

/**
 * @tc.name: setPrevMarginTest
 * @tc.desc: Check the functionality of SwiperModifier.PrevMarginImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setPrevMarginTest, TestSize.Level1)
{
    constexpr auto propName = "prevMargin";
    constexpr auto propNameOpt = "prevMarginIgnoreBlank";
    const std::string &defaultValue(EXPECTED_VP_ZERO);
    ASSERT_NE(modifier_->setPrevMargin, nullptr);

    // test init state
    auto checkInit = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInit, defaultValue);
    auto checkInitOpt = GetAttrValue<std::string>(node_, propNameOpt);
    EXPECT_EQ(checkInitOpt, EXPECTED_FALSE);

    // test the main arg
    modifier_->setPrevMargin(node_, &OPT_LEN_VP_POS, nullptr);
    auto checkPxPos = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkPxPos, EXPECTED_VP_POS);
    modifier_->setPrevMargin(node_, &OPT_LEN_VP_NEG, nullptr);
    auto checkVpNeg = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVpNeg, defaultValue);

    // test the optional arg
    modifier_->setPrevMargin(node_, &OPT_LEN_VP_POS, &OPT_BOOL_TRUE);
    auto checkOptTrue = GetAttrValue<std::string>(node_, propNameOpt);
    EXPECT_EQ(checkOptTrue, EXPECTED_TRUE);
    modifier_->setPrevMargin(node_, &OPT_LEN_VP_POS, &OPT_BOOL_UNDEF);
    auto checkOptUndef = GetAttrValue<std::string>(node_, propNameOpt);
    EXPECT_EQ(checkOptUndef, EXPECTED_TRUE); // nothing change with the undefined optional param
    modifier_->setPrevMargin(node_, &OPT_LEN_VP_POS, nullptr);
    auto checkOptNull = GetAttrValue<std::string>(node_, propNameOpt);
    EXPECT_EQ(checkOptNull, EXPECTED_TRUE); // nothing change with no optional param
    modifier_->setPrevMargin(node_, &OPT_LEN_VP_POS, &OPT_BOOL_FALSE);
    auto checkOptFalse = GetAttrValue<std::string>(node_, propNameOpt);
    EXPECT_EQ(checkOptFalse, EXPECTED_FALSE);
}
/**
 * @tc.name: setNextMarginTest
 * @tc.desc: Check the functionality of SwiperModifier.NextMarginImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setNextMarginTest, TestSize.Level1)
{
    constexpr auto propName = "nextMargin";
    constexpr auto propNameOpt = "nextMarginIgnoreBlank";
    const std::string &defaultValue(EXPECTED_VP_ZERO);
    ASSERT_NE(modifier_->setNextMargin, nullptr);

    // test init state
    auto checkInit = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInit, defaultValue);
    auto checkInitOpt = GetAttrValue<std::string>(node_, propNameOpt);
    EXPECT_EQ(checkInitOpt, EXPECTED_FALSE);

    // test the main arg
    modifier_->setNextMargin(node_, &OPT_LEN_VP_POS, nullptr);
    auto checkPxPos = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkPxPos, EXPECTED_VP_POS);
    modifier_->setNextMargin(node_, &OPT_LEN_VP_NEG, nullptr);
    auto checkVpNeg = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkVpNeg, defaultValue);

    // test the optional arg
    modifier_->setNextMargin(node_, &OPT_LEN_VP_POS, &OPT_BOOL_TRUE);
    auto checkOptTrue = GetAttrValue<std::string>(node_, propNameOpt);
    EXPECT_EQ(checkOptTrue, EXPECTED_TRUE);
    modifier_->setNextMargin(node_, &OPT_LEN_VP_POS, &OPT_BOOL_UNDEF);
    auto checkOptUndef = GetAttrValue<std::string>(node_, propNameOpt);
    EXPECT_EQ(checkOptUndef, EXPECTED_TRUE); // nothing change with the undefined optional param
    modifier_->setNextMargin(node_, &OPT_LEN_VP_POS, nullptr);
    auto checkOptNull = GetAttrValue<std::string>(node_, propNameOpt);
    EXPECT_EQ(checkOptNull, EXPECTED_TRUE); // nothing change with no optional param
    modifier_->setNextMargin(node_, &OPT_LEN_VP_POS, &OPT_BOOL_FALSE);
    auto checkOptFalse = GetAttrValue<std::string>(node_, propNameOpt);
    EXPECT_EQ(checkOptFalse, EXPECTED_FALSE);
}
/**
 * @tc.name: setOnAnimationStartTest
 * @tc.desc: Check the functionality of SwiperModifier.OnAnimationStartImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setOnAnimationStartTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int32_t index;
        int32_t targetIndex;
        AnimationCallbackInfo info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto checkCallback =
        [](const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_Int32 targetIndex,
        const Ark_SwiperAnimationEvent extraInfo) {
            checkEvent = {
                .nodeId = resourceId,
                .index = Converter::Convert<Ark_Int32>(index),
                .targetIndex = Converter::Convert<Ark_Int32>(targetIndex),
                .info = {
                    .currentOffset = Converter::Convert<Ark_Float32>(extraInfo.currentOffset),
                    .targetOffset = Converter::Convert<Ark_Float32>(extraInfo.targetOffset),
                    .velocity = Converter::Convert<Ark_Float32>(extraInfo.velocity),
                }
            };
        };
    auto func = Converter::ArkValue<OnSwiperAnimationStartCallback>(checkCallback, CONTEXT_ID);
    auto optCallback = Converter::ArkValue<Opt_OnSwiperAnimationStartCallback>(func);

    ASSERT_NE(modifier_->setOnAnimationStart, nullptr);

    modifier_->setOnAnimationStart(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireAnimationStartEvent(123, 456, {
        .currentOffset = 1.23f,
        .targetOffset = -4.56f,
        .velocity = 78.9f,
    });
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, CONTEXT_ID);
    EXPECT_EQ(checkEvent->index, 123);
    EXPECT_EQ(checkEvent->targetIndex, 456);
    EXPECT_EQ(checkEvent->info.currentOffset, 1.23f);
    EXPECT_EQ(checkEvent->info.targetOffset, -4.56f);
    EXPECT_EQ(checkEvent->info.velocity, 78.9f);
}
/**
 * @tc.name: setOnAnimationEndTest
 * @tc.desc: Check the functionality of SwiperModifier.OnAnimationEndImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setOnAnimationEndTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int32_t index;
        AnimationCallbackInfo info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto checkCallback =
        [](const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_SwiperAnimationEvent extraInfo) {
            checkEvent = {
            .nodeId = resourceId,
            .index = Converter::Convert<Ark_Int32>(index),
            .info = {
                .currentOffset = Converter::Convert<Ark_Float32>(extraInfo.currentOffset),
                .targetOffset = Converter::Convert<Ark_Float32>(extraInfo.targetOffset),
                .velocity = Converter::Convert<Ark_Float32>(extraInfo.velocity),
            }
        };
        };
    auto func = Converter::ArkValue<OnSwiperAnimationEndCallback>(checkCallback, CONTEXT_ID);
    auto optCallback = Converter::ArkValue<Opt_OnSwiperAnimationEndCallback>(func);

    // the start animation before is required for the end of animation testing
    eventHub->FireAnimationStartEvent(0, 0, {});

    ASSERT_NE(modifier_->setOnAnimationEnd, nullptr);

    modifier_->setOnAnimationEnd(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireAnimationEndEvent(321, {
        .currentOffset = 1.23f,
        .targetOffset = -4.56f,
        .velocity = 78.9f,
    });
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, CONTEXT_ID);
    EXPECT_EQ(checkEvent->index, 321);
    EXPECT_EQ(checkEvent->info.currentOffset, 1.23f);
    EXPECT_EQ(checkEvent->info.targetOffset, -4.56f);
    EXPECT_EQ(checkEvent->info.velocity, 78.9f);
}
/**
 * @tc.name: setOnGestureSwipeTest
 * @tc.desc: Check the functionality of SwiperModifier.OnGestureSwipeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setOnGestureSwipeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int32_t index;
        AnimationCallbackInfo info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto checkCallback =
        [](const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_SwiperAnimationEvent extraInfo) {
            checkEvent = {
                .nodeId = resourceId,
                .index = Converter::Convert<Ark_Int32>(index),
                .info = {
                    .currentOffset = Converter::Convert<Ark_Float32>(extraInfo.currentOffset),
                    .targetOffset = Converter::Convert<Ark_Float32>(extraInfo.targetOffset),
                    .velocity = Converter::Convert<Ark_Float32>(extraInfo.velocity),
                }
            };
        };
    auto func = Converter::ArkValue<OnSwiperGestureSwipeCallback>(checkCallback, CONTEXT_ID);
    auto optCallback = Converter::ArkValue<Opt_OnSwiperGestureSwipeCallback>(func);

    ASSERT_NE(modifier_->setOnGestureSwipe, nullptr);

    modifier_->setOnGestureSwipe(node_, &optCallback);

    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireGestureSwipeEvent(321, {
        .currentOffset = 1.23f,
        .targetOffset = -4.56f,
        .velocity = 78.9f,
    });
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, CONTEXT_ID);
    EXPECT_EQ(checkEvent->index, 321);
    EXPECT_EQ(checkEvent->info.currentOffset, 1.23f);
    EXPECT_EQ(checkEvent->info.targetOffset, -4.56f);
    EXPECT_EQ(checkEvent->info.velocity, 78.9f);
}
/**
 * @tc.name: setNestedScrollTest
 * @tc.desc: Check the functionality of SwiperModifier.NestedScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, DISABLED_setNestedScrollTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setNestedScroll, nullptr);
    // the result can't be checked due to nothing corresponded attributes in JSON object,
    // that is provided by the SwiperPattern::ToJsonValue and SwiperLayoutProperty::ToJsonValue
}
/**
 * @tc.name: setCustomContentTransition
 * @tc.desc: Check the functionality of SwiperModifier.CustomContentTransitionImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setCustomContentTransition, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCustomContentTransition, nullptr);

    const int32_t timeOut = 1000;
    const int32_t contextId = 123;
    const int32_t expectedIndexValue = 2342;

    ASSERT_NE(fullAPI_->getAccessors(), nullptr);
    static const auto *accessor = fullAPI_->getAccessors()->getSwiperContentTransitionProxyAccessor();
    ASSERT_NE(accessor, nullptr);
    ASSERT_NE(accessor->getFinalizer, nullptr);
    ASSERT_NE(accessor->getIndex, nullptr);

    static std::optional<std::pair<int32_t, int32_t>> checkInvoke;
    void (*fakeDeveloperCallbackFunc)(const Ark_Int32 resourceId, const Ark_SwiperContentTransitionProxy parameter) =
        [](const Ark_Int32 resourceId, const Ark_SwiperContentTransitionProxy peer) {
            // get to further test: incoming resource, data from incoming peer via accessor
            checkInvoke = {
                resourceId,
                Converter::Convert<int32_t>(accessor->getIndex(peer))
            };

            auto destroy = reinterpret_cast<void (*)(SwiperContentTransitionProxyPeer *)>(accessor->getFinalizer());
            if (destroy) {
                (*destroy)(peer);
            }
        };
    ASSERT_FALSE(checkInvoke.has_value());

    // setup the callback object via C-API
    Ark_SwiperContentAnimatedTransition transition {
        .timeout = ArkValue<Opt_Int32>(timeOut),
        .transition = ArkValue<Callback_SwiperContentTransitionProxy_Void>(fakeDeveloperCallbackFunc, CONTEXT_ID)
    };
    auto transitionOpt = Converter::ArkValue<Opt_SwiperContentAnimatedTransition>(transition);
    modifier_->setCustomContentTransition(node_, &transitionOpt);

    // check the callback object that was setup
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    auto swiperContentAnimatedTransition = pattern->GetSwiperCustomContentTransition();
    ASSERT_NE(swiperContentAnimatedTransition, nullptr);
    EXPECT_EQ(swiperContentAnimatedTransition->timeout, timeOut);
    ASSERT_NE(swiperContentAnimatedTransition->transition, nullptr);

    // simulate of the callback function invoking from ace_engine part
    auto swiperContentTransitionProxy = AceType::MakeRefPtr<SwiperContentTransitionProxy>();
    swiperContentTransitionProxy->SetIndex(expectedIndexValue);
    swiperContentAnimatedTransition->transition(swiperContentTransitionProxy);

    // check the invoking result
    ASSERT_TRUE(checkInvoke.has_value());
    EXPECT_EQ(checkInvoke.value().first, contextId);
    EXPECT_EQ(checkInvoke.value().second, expectedIndexValue);
}
/**
 * @tc.name: setOnContentDidScrollTest
 * @tc.desc: Check the functionality of SwiperModifier.OnContentDidScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setOnContentDidScrollTest, TestSize.Level1)
{
    struct OnDidScrollParams {
        int32_t nodeId;
        int32_t selectedIndex;
        int32_t index;
        float position;
        float mainAxisLength;
    };

    struct OnDidScrollParams expected {
        reinterpret_cast<UINode *>(node_)->GetId(),
        1122,
        3344,
        55.66f,
        77.88f,
    };

    static std::optional<OnDidScrollParams> checkEvent = std::nullopt;
    auto checkCallback =
        [](const Ark_Int32 resourceId, Ark_Int32 selectedIndex,
            Ark_Int32 index, Ark_Float64 position, Ark_Float64 mainAxisLength) {
            checkEvent = {
                .nodeId = resourceId,
                .selectedIndex = Converter::Convert<int32_t>(selectedIndex),
                .index = Converter::Convert<int32_t>(index),
                .position = Converter::Convert<float>(position),
                .mainAxisLength = Converter::Convert<float>(mainAxisLength),
            };
        };
    auto func = Converter::ArkValue<ContentDidScrollCallback>(checkCallback, CONTEXT_ID);
    auto optCallback = Converter::ArkValue<Opt_ContentDidScrollCallback>(func);

    EXPECT_NE(modifier_->setOnContentDidScroll, nullptr);
    EXPECT_FALSE(checkEvent);

    modifier_->setOnContentDidScroll(node_, &optCallback);

    // check the callback func that was setup
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    auto onContentDidScroll = pattern->GetOnContentDidScroll();
    ASSERT_NE(onContentDidScroll, nullptr);

    // simulate the callback invoking from ace_engine
    (*onContentDidScroll.get())(expected.selectedIndex, expected.index, expected.position, expected.mainAxisLength);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->nodeId, CONTEXT_ID);
    EXPECT_EQ(checkEvent->selectedIndex, expected.selectedIndex);
    EXPECT_EQ(checkEvent->index, expected.index);
    EXPECT_EQ(checkEvent->position, expected.position);
    EXPECT_EQ(checkEvent->mainAxisLength, expected.mainAxisLength);
}
/**
 * @tc.name: setIndicatorInteractiveTest
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorInteractiveImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorInteractiveTest, TestSize.Level1)
{
    constexpr auto propName = "indicatorInteractive";
    const std::string &defaultValue(EXPECTED_TRUE);
    ASSERT_NE(modifier_->setIndicatorInteractive, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkInitial, defaultValue);

    modifier_->setIndicatorInteractive(node_, &OPT_BOOL_FALSE);
    auto checkFalse = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkFalse, EXPECTED_FALSE);

    modifier_->setIndicatorInteractive(node_, &OPT_BOOL_TRUE);
    auto checkTrue = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkTrue, EXPECTED_TRUE);
}

#ifdef WRONG_OLD_GEN
/*
 * @tc.name: setOnChangeEventIndexImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setOnChangeEventIndexImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<int32_t> value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Opt_Number parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::OptConvert<int32_t>(parameter)
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_Opt_Number_Void>(checkCallback, contextId);
    modifier_->set_onChangeEvent_index(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireChangeEvent(0, 1, false);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, 1);
    eventHub->FireChangeEvent(1, 2, false);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, 2);
}
#endif
} // namespace OHOS::Ace::NG
