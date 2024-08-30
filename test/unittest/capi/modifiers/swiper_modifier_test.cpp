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
#include "node_api.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

#include "core/components/common/layout/constants.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
template<typename To, typename From, typename = std::void_t<decltype(To().tag), decltype(To().value)>>
To OptValue(From&& src)
{
    To dst;
    dst.tag = ARK_TAG_OBJECT;
    Converter::AssignArkValue(dst.value, std::forward<From>(src));
    return dst;
}

template<typename To, typename = std::void_t<decltype(To().tag), decltype(To().value)>>
To OptValue()
{
    return {
        .tag = ARK_TAG_UNDEFINED
    };
}

static const Ark_Boolean ABOOL_TRUE(true);
static const Ark_Boolean ABOOL_FALSE(false);
static const Ark_Int32 AINT32_POS(1234);
static const Ark_Int32 AINT32_NEG(INT_MIN);
static const Ark_Float32 AFLT32_POS(1.234f);
static const Ark_Float32 AFLT32_NEG(-5.6789f);

static const auto ANUM_INT_POS = ArkValue<Ark_Number>(AINT32_POS);
static const auto ANUM_INT_NEG = ArkValue<Ark_Number>(AINT32_NEG);
static const auto ASTR_INVALID = ArkValue<Ark_String>("(*%^&#@");

static const auto ALEN_PX_POS = ArkValue<Ark_Length>(AINT32_POS);
static const auto ALEN_PX_NEG = ArkValue<Ark_Length>(AINT32_NEG);
static const auto ALEN_VP_POS = ArkValue<Ark_Length>(AFLT32_POS);
static const auto ALEN_VP_NEG = ArkValue<Ark_Length>(AFLT32_NEG);

static const auto OPT_LEN_PX_POS = OptValue<Opt_Length>(AINT32_POS);
static const auto OPT_LEN_PX_NEG = OptValue<Opt_Length>(AINT32_NEG);
static const auto OPT_LEN_VP_POS = OptValue<Opt_Length>(AFLT32_POS);
static const auto OPT_LEN_VP_NEG = OptValue<Opt_Length>(AFLT32_NEG);

static const auto OPT_BOOL_UNDEF = OptValue<Opt_Boolean>();
static const auto OPT_BOOL_TRUE = OptValue<Opt_Boolean>(true);
static const auto OPT_BOOL_FALSE = OptValue<Opt_Boolean>(false);

static const std::string EXPECTED_TRUE("true");
static const std::string EXPECTED_FALSE("false");
static const std::string EXPECTED_VP_ZERO(Dimension(0, DimensionUnit::VP).ToString());
static const std::string EXPECTED_PX_POS(Dimension(AINT32_POS, DimensionUnit::PX).ToString());
static const std::string EXPECTED_VP_POS(Dimension(AFLT32_POS, DimensionUnit::VP).ToString());

static const Dimension THEME_SWIPER_INDICATOR_SIZE(9876, DimensionUnit::VP);
static const Dimension THEME_SWIPER_FONT_SIZE(321, DimensionUnit::PX);
static const Color THEME_SWIPER_INDICATOR_COLOR(Color::BLUE);
static const Color THEME_SWIPER_ARROW_COLOR(Color::GREEN);

inline Ark_Resource ArkRes(Ark_String *name, int id = -1,
    NodeModifier::ResourceType type = NodeModifier::ResourceType::COLOR,
    const char *module = "", const char *bundle = "")
{
    return {
        .id = {.tag= ARK_TAG_INT32, .i32 = static_cast<Ark_Int32>(id) },
        .type = {.tag= ARK_TAG_INT32, .i32 = static_cast<Ark_Int32>(type)},
        .moduleName = {.chars = module},
        .bundleName = {.chars = bundle},
        .params = { .tag = ARK_TAG_OBJECT, .value = {.array = name, .length = name ? 1 : 0} }
    };
}

std::string GetStringAttribute(const std::string &strWithJson, const std::string &name)
{
    auto jsonVal = JsonUtil::ParseJsonData(strWithJson.c_str());
    return GetStringAttribute(jsonVal, name);
}

} // namespace

class SwiperModifierTest : public ModifierTestBase<GENERATED_ArkUISwiperModifier,
    &GENERATED_ArkUINodeModifiers::getSwiperModifier, GENERATED_ARKUI_SWIPER>
{
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();

        // assume using of test/mock/core/common/mock_theme_constants.cpp in build
        auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
        themeStyle->SetAttr("swiper_indicator_size", { .value = THEME_SWIPER_INDICATOR_SIZE });
        themeStyle->SetAttr("indicator_color", { .value = THEME_SWIPER_INDICATOR_COLOR });
        themeStyle->SetAttr("indicator_color_selected", { .value = THEME_SWIPER_INDICATOR_COLOR });
        themeStyle->SetAttr("indicator_text_font_size", { .value = THEME_SWIPER_FONT_SIZE });
        themeStyle->SetAttr(ARROW_COLOR_PRIMARY, { .value = THEME_SWIPER_ARROW_COLOR });
        themeStyle->SetAttr(ARROW_COLOR_COMPONENT_NORMAL, { .value = THEME_SWIPER_ARROW_COLOR });
        MockThemeStyle::GetInstance()->SetAttr("swiper_pattern", { .value = themeStyle });
        themeConstants->LoadTheme(0);

        // build default SwiperTheme
        SwiperIndicatorTheme::Builder builder;
        auto swiperTheme = builder.Build(themeConstants);

        // create Theme Manager and provide return of SwiperTheme
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetThemeConstants(testing::_, testing::_))
            .WillRepeatedly(Return(themeConstants));
        EXPECT_CALL(*themeManager, GetTheme(testing::_))
            .WillRepeatedly(Return(swiperTheme));

        // setup Context with Theme Manager and Container
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::SetUp(MockPipelineContext::GetCurrent());
        MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: SwiperModifierTest1
 * @tc.desc: Check the functionality of SwiperModifier.SetSwiperOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest1, TestSize.Level1)
{
}
/**
 * @tc.name: setIndexTest
 * @tc.desc: Check the functionality of SwiperModifier.IndexImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndexTest, TestSize.Level1)
{
    static const std::string PROP_NAME("index");
    static const std::string DEFAULT_VALUE("0");
    ASSERT_NE(modifier_->setIndex, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    auto numberInt = ArkValue<Ark_Number>(123456);
    modifier_->setIndex(node_, &numberInt);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123456");

    auto numberFlt = ArkValue<Ark_Number>(1.23456f);
    modifier_->setIndex(node_, &numberFlt);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1");

    auto numberIntNeg = ArkValue<Ark_Number>(-1);
    modifier_->setIndex(node_, &numberIntNeg);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);

    auto numberFltNeg = ArkValue<Ark_Number>(-1.111f);
    modifier_->setIndex(node_, &numberFltNeg);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, DEFAULT_VALUE);
}
/**
 * @tc.name: setAutoPlayTest
 * @tc.desc: Check the functionality of SwiperModifier.AutoPlayImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setAutoPlayTest, TestSize.Level1)
{
    static const std::string PROP_NAME("autoPlay");
    static const std::string &DEFAULT_VALUE(EXPECTED_FALSE);
    ASSERT_NE(modifier_->setAutoPlay, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    modifier_->setAutoPlay(node_, ABOOL_TRUE);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setAutoPlay(node_, ABOOL_FALSE);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);
}
/**
 * @tc.name: setIntervalTest
 * @tc.desc: Check the functionality of SwiperModifier.IntervalImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIntervalTest, TestSize.Level1)
{
    static const std::string PROP_NAME("interval");
    static const std::string DEFAULT_VALUE("3000"); // corrrsponds to
    // DEFAULT_SWIPER_AUTOPLAY_INTERVAL in frameworks/core/components/declaration/swiper/swiper_declaration.h
    ASSERT_NE(modifier_->setInterval, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    auto numberInt = ArkValue<Ark_Number>(123456);
    modifier_->setInterval(node_, &numberInt);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123456");

    auto numberFlt = ArkValue<Ark_Number>(1.23456f);
    modifier_->setInterval(node_, &numberFlt);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1");

    auto numberIntNeg = ArkValue<Ark_Number>(-1);
    modifier_->setInterval(node_, &numberIntNeg);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);

    auto numberFltNeg = ArkValue<Ark_Number>(-1.111f);
    modifier_->setInterval(node_, &numberFltNeg);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, DEFAULT_VALUE);
}

/**
 * @tc.name: setIndicatorTestDotPadding
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Dot type, the padding's subattr
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorTestDotPadding, TestSize.Level1)
{
    typedef std::tuple<Ark_DotIndicator, std::string> OneTestStep;
    static const std::string PROP_NAME("indicator");
    static const std::string &DEFAULT_VALUE(EXPECTED_VP_ZERO);
    static const std::vector<OneTestStep> testPlan = {
    { { ._left = OPT_LEN_VP_POS, ._top = OPT_LEN_VP_POS, ._right = OPT_LEN_VP_POS, ._bottom = OPT_LEN_VP_POS,
        ._start = OptValue<Opt_CustomObject>(AFLT32_POS), ._end = OptValue<Opt_CustomObject>(AFLT32_POS),
        }, EXPECTED_VP_POS },
    { { ._left = OPT_LEN_PX_POS, ._top = OPT_LEN_PX_POS, ._right = OPT_LEN_PX_POS, ._bottom = OPT_LEN_PX_POS,
        ._start = OptValue<Opt_CustomObject>(AINT32_POS), ._end = OptValue<Opt_CustomObject>(AINT32_POS),
        }, EXPECTED_PX_POS },
    { { ._left = OPT_LEN_VP_NEG, ._top = OPT_LEN_VP_NEG, ._right = OPT_LEN_VP_NEG, ._bottom = OPT_LEN_VP_NEG,
        ._start = OptValue<Opt_CustomObject>(AFLT32_NEG), ._end = OptValue<Opt_CustomObject>(AFLT32_NEG),
        }, DEFAULT_VALUE },
    { { ._left = OPT_LEN_PX_NEG, ._top = OPT_LEN_PX_NEG, ._right = OPT_LEN_PX_NEG, ._bottom = OPT_LEN_PX_NEG,
        ._start = OptValue<Opt_CustomObject>(AINT32_NEG), ._end = OptValue<Opt_CustomObject>(AINT32_NEG),
        }, DEFAULT_VALUE },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    static const std::vector<std::string> keys = { "left", "right", "top", "bottom",
        // "start", "end" - these fields are not supported in SwiperPattern::GetDotIndicatorStyle()
    };
    for (const auto &[indicator, expect]: testPlan) {
        auto arkParam = ArkUnion<Type_SwiperAttribute_indicator_Arg0, Ark_DotIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        for (const auto &nameKey: keys) {
            auto checkPadding = GetStringAttribute(strWithObj, nameKey);
            EXPECT_EQ(checkPadding, expect);
        }
    }
}

/**
 * @tc.name: setIndicatorTestDotSize
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Dot type, the size's subattr
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorTestDotSize, TestSize.Level1)
{
    typedef std::tuple<Ark_DotIndicator, std::string> OneTestStep;
    static const std::string PROP_NAME("indicator");
    static const std::string DEFAULT_SIZE = THEME_SWIPER_INDICATOR_SIZE.ToString();
    static const std::vector<OneTestStep> testPlan = {
    { { ._itemWidth = OPT_LEN_VP_POS, ._itemHeight = OPT_LEN_VP_POS,
        ._selectedItemWidth = OPT_LEN_VP_POS, ._selectedItemHeight = OPT_LEN_VP_POS,
        }, EXPECTED_VP_POS },
    { { ._itemWidth = OPT_LEN_PX_POS, ._itemHeight = OPT_LEN_PX_POS,
        ._selectedItemWidth = OPT_LEN_PX_POS, ._selectedItemHeight = OPT_LEN_PX_POS,
        }, EXPECTED_PX_POS },
    { { ._itemWidth = OPT_LEN_VP_NEG, ._itemHeight = OPT_LEN_VP_NEG,
        ._selectedItemWidth = OPT_LEN_VP_NEG, ._selectedItemHeight = OPT_LEN_VP_NEG,
        }, DEFAULT_SIZE },
    { { ._itemWidth = OPT_LEN_PX_NEG, ._itemHeight = OPT_LEN_PX_NEG,
        ._selectedItemWidth = OPT_LEN_PX_NEG, ._selectedItemHeight = OPT_LEN_PX_NEG,
        }, DEFAULT_SIZE },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    static const std::vector<std::string> keys = {
        "itemWidth", "itemHeight", "selectedItemWidth", "selectedItemHeight"
    };
    for (const auto &[indicator, expect]: testPlan) {
        auto arkParam = ArkUnion<Type_SwiperAttribute_indicator_Arg0, Ark_DotIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        for (const auto &nameKey: keys) {
            auto checkVal = GetStringAttribute(strWithObj, nameKey);
            EXPECT_EQ(checkVal, expect);
        }
    }
}

/**
 * @tc.name: setIndicatorTestDotColor
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Dot type, the Color type subattr
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorTestDotColor, TestSize.Level1)
{
    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static const std::string PROP_NAME("indicator");
    static const std::string DEFAULT_VALUE(THEME_SWIPER_INDICATOR_COLOR.ToString());
    static Ark_String resName = ArkValue<Ark_String>("aa.bb.cc");
    static const std::string EXPECTED_RESOURCE_COLOR =
        Color::RED.ToString(); // Color::RED is result of stubs for ThemeConstants::GetColorByName
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Ark_ResourceColor, Ark_Int32>(0x12345678), "#12345678" },
        { ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
        { ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), "#00000000" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
        { ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&resName)), EXPECTED_RESOURCE_COLOR },
        { ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 1234)), EXPECTED_RESOURCE_COLOR },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    Ark_DotIndicator indicator = {
        ._color = OptValue<Opt_ResourceColor>(),
        ._selectedColor = OptValue<Opt_ResourceColor>()
    };
    auto arkParam = ArkUnion<Type_SwiperAttribute_indicator_Arg0, Ark_DotIndicator>(indicator);
    modifier_->setIndicator(node_, &arkParam);
    auto strWithObj = GetStringAttribute(node_, PROP_NAME);
    auto checkColorDflt = GetStringAttribute(strWithObj, "color");
    EXPECT_EQ(checkColorDflt, DEFAULT_VALUE);
    auto checkSelColorDflt = GetStringAttribute(strWithObj, "selectedColor");
    EXPECT_EQ(checkSelColorDflt, DEFAULT_VALUE);

    for (const auto &[arkResColor, expected]: testPlan) {
        Ark_DotIndicator indicator = {
            ._color = OptValue<Opt_ResourceColor>(arkResColor),
            ._selectedColor = OptValue<Opt_ResourceColor>(arkResColor)
        };
        auto arkParam = ArkUnion<Type_SwiperAttribute_indicator_Arg0, Ark_DotIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        auto checkColor = GetStringAttribute(strWithObj, "color");
        EXPECT_EQ(checkColor, expected);
        auto checkSelColor = GetStringAttribute(strWithObj, "selectedColor");
        EXPECT_EQ(checkSelColor, expected);
    }
}

/**
 * @tc.name: setIndicatorTestDotOther
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Dot type, the other subattr
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorTestDotOther, TestSize.Level1)
{
    typedef std::tuple<Ark_DotIndicator, std::string, std::string> OneTestStep;
    static const std::string PROP_NAME("indicator");
    static const std::vector<OneTestStep> testPlan = {
        { { ._mask = OPT_BOOL_UNDEF, ._maxDisplayCount = OptValue<Opt_Number>() },
            EXPECTED_FALSE, "0"},
        { { ._mask = OPT_BOOL_TRUE, ._maxDisplayCount = OptValue<Opt_Number>(5325) },
            EXPECTED_TRUE, "5325" },
        { { ._mask = OPT_BOOL_FALSE, ._maxDisplayCount = OptValue<Opt_Number>(INT_MIN) },
            EXPECTED_FALSE, "0" },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    for (const auto &[indicator, expectMask, expectCount]: testPlan) {
        Type_SwiperAttribute_indicator_Arg0 arkParam = { .selector = 0, .value0 = indicator };
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        auto checkMask = GetStringAttribute(strWithObj, "mask");
        EXPECT_EQ(checkMask, expectMask);
        auto checkMaxDispCnt = GetStringAttribute(strWithObj, "maxDisplayCount");
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
    static const std::string PROP_NAME("indicator");
    static const std::string DEFAULT_VALUE("0.00vp");
    static const std::vector<OneTestStep> testPlan = {
    { { ._left = OPT_LEN_VP_POS, ._top = OPT_LEN_VP_POS, ._right = OPT_LEN_VP_POS, ._bottom = OPT_LEN_VP_POS,
        ._start = OptValue<Opt_CustomObject>(AFLT32_POS), ._end = OptValue<Opt_CustomObject>(AFLT32_POS),
        }, EXPECTED_VP_POS },
    { { ._left = OPT_LEN_PX_POS, ._top = OPT_LEN_PX_POS, ._right = OPT_LEN_PX_POS, ._bottom = OPT_LEN_PX_POS,
        ._start = OptValue<Opt_CustomObject>(AINT32_POS), ._end = OptValue<Opt_CustomObject>(AINT32_POS),
        }, EXPECTED_PX_POS },
    { { ._left = OPT_LEN_VP_NEG, ._top = OPT_LEN_VP_NEG, ._right = OPT_LEN_VP_NEG, ._bottom = OPT_LEN_VP_NEG,
        ._start = OptValue<Opt_CustomObject>(AFLT32_NEG), ._end = OptValue<Opt_CustomObject>(AFLT32_NEG),
        }, DEFAULT_VALUE },
    { { ._left = OPT_LEN_PX_NEG, ._top = OPT_LEN_PX_NEG, ._right = OPT_LEN_PX_NEG, ._bottom = OPT_LEN_PX_NEG,
        ._start = OptValue<Opt_CustomObject>(AINT32_NEG), ._end = OptValue<Opt_CustomObject>(AINT32_NEG),
        }, DEFAULT_VALUE },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    static const std::vector<std::string> keys = { "left", "right", "top", "bottom",
        // "start", "end" - these fields are not supported in SwiperPattern::GetDigitIndicatorStyle()
    };
    for (const auto &[indicator, expect]: testPlan) {
        Type_SwiperAttribute_indicator_Arg0 arkParam = { .selector = 1, .value1 = indicator };
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        for (const auto &nameKey: keys) {
            auto checkVal = GetStringAttribute(strWithObj, nameKey);
            EXPECT_EQ(checkVal, expect);
        }
    }
}

/**
 * @tc.name: setIndicatorTestDigitFontSize
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Digit indicator, font size attributes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorTestDigitFontSize, TestSize.Level1)
{
    typedef std::tuple<Ark_Font, std::string> OneTestStep;
    static const std::string PROP_NAME("indicator");
    static const std::string DEFAULT_VALUE(THEME_SWIPER_FONT_SIZE.ToString());
    static const std::vector<OneTestStep> testPlan = {
        {{ .size = OPT_LEN_VP_POS }, EXPECTED_VP_POS},
        {{ .size = OPT_LEN_PX_POS }, EXPECTED_PX_POS},
        {{ .size = OPT_LEN_VP_NEG }, DEFAULT_VALUE},
        {{ .size = OPT_LEN_PX_NEG }, DEFAULT_VALUE},
        {{ .size = OptValue<Opt_Dimension>() }, DEFAULT_VALUE},
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    for (const auto &[font, expect]: testPlan) {
        Ark_DigitIndicator indicator = {
            ._digitFont = OptValue<Opt_Font>(font),
            ._selectedDigitFont = OptValue<Opt_Font>(font)
        };
        auto arkParam = ArkUnion<Type_SwiperAttribute_indicator_Arg0, Ark_DigitIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        auto checkFontSz = GetStringAttribute(strWithObj, "fontSize");
        EXPECT_EQ(checkFontSz, expect);
        auto checkSelFontSz = GetStringAttribute(strWithObj, "selectedFontSize");
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
    typedef Opt_Union_FontWeight_Number_String FontWeightT;
    typedef std::tuple<Ark_Font, std::string> OneTestStep;
    static const std::string PROP_NAME("indicator");
    static const std::string DEFAULT_VALUE("FontWeight.Normal");
    static const std::vector<OneTestStep> testPlan = {
        { {.weight = ArkUnion<FontWeightT, Ark_FontWeight>(FontWeight::W500)}, "500" },
        { {.weight = ArkUnion<FontWeightT, Ark_FontWeight>(FontWeight::BOLD)}, "FontWeight.Bold" },
        { {.weight = ArkUnion<FontWeightT, Ark_FontWeight>(FontWeight::REGULAR)}, "FontWeight.Regular" },
        { {.weight = ArkUnion<FontWeightT, Ark_Number>(100)}, "100" },
        { {.weight = ArkUnion<FontWeightT, Ark_Number>(-111)}, DEFAULT_VALUE },
        { {.weight = ArkUnion<FontWeightT, Ark_Number>(300.00f)}, "300" },
        { {.weight = ArkUnion<FontWeightT, Ark_Number>(-123.456f)}, DEFAULT_VALUE },
        { {.weight = ArkUnion<FontWeightT, Ark_String>("700")}, "700" },
        { {.weight = ArkUnion<FontWeightT, Ark_String>("bold")}, "FontWeight.Bold" },
        { {.weight = ArkUnion<FontWeightT, Ark_String>("InvalidData!")}, DEFAULT_VALUE },
        { {.weight = OptValue<FontWeightT>()}, DEFAULT_VALUE },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    {
        Ark_DigitIndicator indicator = {
            ._digitFont = OptValue<Opt_Font>(),
            ._selectedDigitFont = OptValue<Opt_Font>(),
        };
        auto arkParam = ArkUnion<Type_SwiperAttribute_indicator_Arg0, Ark_DigitIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        auto checkFontWeightDftl = GetStringAttribute(strWithObj, "fontWeight");
        EXPECT_EQ(checkFontWeightDftl, DEFAULT_VALUE);
        auto checkSelFontWeightDftl = GetStringAttribute(strWithObj, "selectedFontWeight");
        EXPECT_EQ(checkSelFontWeightDftl, DEFAULT_VALUE);
    }
    for (const auto &[font, expect]: testPlan) {
        Ark_DigitIndicator indicator = {
            ._digitFont = OptValue<Opt_Font>(font),
            ._selectedDigitFont = OptValue<Opt_Font>(font),
        };
        auto arkParam = ArkUnion<Type_SwiperAttribute_indicator_Arg0, Ark_DigitIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        auto checkFontWeight = GetStringAttribute(strWithObj, "fontWeight");
        EXPECT_EQ(checkFontWeight, expect);
        auto checkSelFontWeight = GetStringAttribute(strWithObj, "selectedFontWeight");
        EXPECT_EQ(checkSelFontWeight, expect);
    }
}

/**
 * @tc.name: setIndicatorTestDigitFontColor
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Digit Indicator, the Color type subattributes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorTestDigitFontColor, TestSize.Level1)
{
    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static const std::string PROP_NAME("indicator");
    static const std::string DEFAULT_VALUE(Color::TRANSPARENT.ToString());// ??? THEME_SWIPER_INDICATOR_COLOR.ToString());
    static Ark_String resName = ArkValue<Ark_String>("aa.bb.cc");
    static const std::string EXPECTED_RESOURCE_COLOR =
        Color::RED.ToString(); // Color::RED is result of stubs for ThemeConstants::GetColorByName
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Ark_ResourceColor, Ark_Int32>(0x12345678), "#12345678" },
        { ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
        { ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), "#00000000" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
        { ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&resName)), EXPECTED_RESOURCE_COLOR },
        { ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 1234)), EXPECTED_RESOURCE_COLOR },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    Ark_DigitIndicator indicator = {
        ._fontColor = OptValue<Opt_ResourceColor>(),
        ._selectedFontColor = OptValue<Opt_ResourceColor>()
    };
    auto arkParam = ArkUnion<Type_SwiperAttribute_indicator_Arg0, Ark_DigitIndicator>(indicator);
    modifier_->setIndicator(node_, &arkParam);
    auto strWithObj = GetStringAttribute(node_, PROP_NAME);
    auto checkColorDflt = GetStringAttribute(strWithObj, "fontColor");
    EXPECT_EQ(checkColorDflt, DEFAULT_VALUE);
    auto checkSelColorDflt = GetStringAttribute(strWithObj, "selectedFontColor");
    EXPECT_EQ(checkSelColorDflt, DEFAULT_VALUE);

    for (const auto &[arkResColor, expected]: testPlan) {
        Ark_DigitIndicator indicator = {
            ._fontColor = OptValue<Opt_ResourceColor>(arkResColor),
            ._selectedFontColor = OptValue<Opt_ResourceColor>(arkResColor)
        };
        auto arkParam = ArkUnion<Type_SwiperAttribute_indicator_Arg0, Ark_DigitIndicator>(indicator);
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        auto checkColor = GetStringAttribute(strWithObj, "fontColor");
        EXPECT_EQ(checkColor, expected);
        auto checkSelColor = GetStringAttribute(strWithObj, "selectedFontColor");
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
    static const std::string PROP_NAME("indicator");
    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    auto boolIndFalse = ArkUnion<Type_SwiperAttribute_indicator_Arg0, Ark_Boolean>(ABOOL_FALSE);
    modifier_->setIndicator(node_, &boolIndFalse);
    auto checkFalse = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkFalse, EXPECTED_FALSE);

    auto boolIndTrue = ArkUnion<Type_SwiperAttribute_indicator_Arg0, Ark_Boolean>(ABOOL_TRUE);
    modifier_->setIndicator(node_, &boolIndTrue);
    auto checkTrue = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkTrue, EXPECTED_TRUE);
}

/**
 * @tc.name: setDisplayArrowTestStyleShowBg
 * @tc.desc: Check the functionality of SwiperModifier.setDisplayArrow with the Style size subattruibutes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayArrowTestStyleShowBg, TestSize.Level1)
{
    static const std::string PROP_NAME("showBackground");
    static const std::string DEFAULT_VALUE = EXPECTED_FALSE;

    ASSERT_NE(modifier_->setDisplayArrow, nullptr);

    auto checkValInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkValInitial, DEFAULT_VALUE);

    Type_SwiperAttribute_displayArrow_Arg0 arkParam1 = {.selector=0, .value0={.showBackground = OPT_BOOL_TRUE}};
    modifier_->setDisplayArrow(node_, &arkParam1, nullptr);
    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    Type_SwiperAttribute_displayArrow_Arg0 arkParam2 = {.selector=0, .value0={.showBackground = OPT_BOOL_FALSE}};
    modifier_->setDisplayArrow(node_, &arkParam2, nullptr);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, EXPECTED_FALSE);

    Type_SwiperAttribute_displayArrow_Arg0 arkParam3 = {.selector=0, .value0={.showBackground = OPT_BOOL_UNDEF}};
    modifier_->setDisplayArrow(node_, &arkParam3, nullptr);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, DEFAULT_VALUE);
}

/**
 * @tc.name: setDisplayArrowTestStyleSize
 * @tc.desc: Check the functionality of SwiperModifier.setDisplayArrow with the Style size subattruibutes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayArrowTestStyleSize, TestSize.Level1)
{
    typedef std::tuple<Ark_ArrowStyle, std::string> OneTestStep;
    static const std::string PROP_NAME("arrowSize");
    static const std::string DEFAULT_VALUE_S = SWIPER_ARROW_SMALL_ARROW_SIZE.ToString();
    static const std::string DEFAULT_VALUE_B = SWIPER_ARROW_BIG_ARROW_SIZE.ToString();
    static const std::vector<OneTestStep> testPlan = {
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .arrowSize = OPT_LEN_VP_POS}, "1.23vp" },
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .arrowSize = OPT_LEN_PX_POS}, "1234.00px" },
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .arrowSize = OPT_LEN_VP_NEG}, DEFAULT_VALUE_S },
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .arrowSize = OPT_LEN_PX_NEG}, DEFAULT_VALUE_S },
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .arrowSize = {.tag = ARK_TAG_UNDEFINED}}, DEFAULT_VALUE_S },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .arrowSize = OPT_LEN_VP_POS}, "1.23vp" },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .arrowSize = OPT_LEN_PX_POS}, "1234.00px" },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .arrowSize = OPT_LEN_VP_NEG}, DEFAULT_VALUE_B },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .arrowSize = OPT_LEN_PX_NEG}, DEFAULT_VALUE_B },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .arrowSize = {.tag = ARK_TAG_UNDEFINED}}, DEFAULT_VALUE_B },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .arrowSize = OPT_LEN_VP_POS}, "1.23vp" },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .arrowSize = OPT_LEN_PX_POS}, "1234.00px" },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .arrowSize = OPT_LEN_VP_NEG}, DEFAULT_VALUE_S },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .arrowSize = OPT_LEN_PX_NEG}, DEFAULT_VALUE_S },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .arrowSize = {.tag = ARK_TAG_UNDEFINED}}, DEFAULT_VALUE_S },
    };

    ASSERT_NE(modifier_->setDisplayArrow, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, "0.00vp");

    for (const auto &[style, expect]: testPlan) {
        Type_SwiperAttribute_displayArrow_Arg0 arkParam = {
            .selector = 0, .value0 = style
        };
        modifier_->setDisplayArrow(node_, &arkParam, nullptr);
        auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal2, expect);
        auto checkVal3 = GetStringAttribute(node_, "isSidebarMiddle");
        bool expect3 = (style.isSidebarMiddle.tag != ARK_TAG_UNDEFINED && style.isSidebarMiddle.value != 0);
        EXPECT_EQ(checkVal3, expect3 ? EXPECTED_TRUE : EXPECTED_FALSE);
    }
}

/**
 * @tc.name: setDisplayArrowTestStyleBgSize
 * @tc.desc: Check the functionality of SwiperModifier.setDisplayArrow with the Style, bg size subattruibutes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayArrowTestStyleBgSize, TestSize.Level1)
{
    typedef std::tuple<Ark_ArrowStyle, std::string> OneTestStep;
    static const std::string PROP_NAME("arrowBackgroundSize");
    static const std::string DEFAULT_VALUE_S = SWIPER_ARROW_SMALL_ARROW_BACKGROUND_SIZE.ToString();
    static const std::string DEFAULT_VALUE_B = SWIPER_ARROW_BIG_ARROW_BACKGROUND_SIZE.ToString();
    static const std::vector<OneTestStep> testPlan = {
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .backgroundSize = OPT_LEN_VP_POS}, "1.23vp" },
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .backgroundSize = OPT_LEN_PX_POS}, "1234.00px" },
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .backgroundSize = OPT_LEN_VP_NEG}, DEFAULT_VALUE_S },
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .backgroundSize = OPT_LEN_PX_NEG}, DEFAULT_VALUE_S },
        { {.isSidebarMiddle = OPT_BOOL_FALSE, .backgroundSize = {.tag = ARK_TAG_UNDEFINED}}, DEFAULT_VALUE_S },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .backgroundSize = OPT_LEN_VP_POS}, "1.23vp" },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .backgroundSize = OPT_LEN_PX_POS}, "1234.00px" },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .backgroundSize = OPT_LEN_VP_NEG}, DEFAULT_VALUE_B },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .backgroundSize = OPT_LEN_PX_NEG}, DEFAULT_VALUE_B },
        { {.isSidebarMiddle = OPT_BOOL_TRUE, .backgroundSize = {.tag = ARK_TAG_UNDEFINED}}, DEFAULT_VALUE_B },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .backgroundSize = OPT_LEN_VP_POS}, "1.23vp" },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .backgroundSize = OPT_LEN_PX_POS}, "1234.00px" },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .backgroundSize = OPT_LEN_VP_NEG}, DEFAULT_VALUE_S },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .backgroundSize = OPT_LEN_PX_NEG}, DEFAULT_VALUE_S },
        { {.isSidebarMiddle = OPT_BOOL_UNDEF, .backgroundSize = {.tag = ARK_TAG_UNDEFINED}}, DEFAULT_VALUE_S },
    };

    ASSERT_NE(modifier_->setDisplayArrow, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, "0.00vp");

    for (const auto &[style, expect]: testPlan) {
        Type_SwiperAttribute_displayArrow_Arg0 arkParam = {
            .selector = 0, .value0 = style
        };
        modifier_->setDisplayArrow(node_, &arkParam, nullptr);
        auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal2, expect);
    }
}

/**
 * @tc.name: setDisplayArrowTestStyleColorDefault
 * @tc.desc: Check the functionality of SwiperModifier.DisplayArrowImpl with Style, the Color's default and init
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayArrowTestStyleColorDefault, TestSize.Level1)
{
    static const std::string DEFAULT_VALUE = THEME_SWIPER_ARROW_COLOR.ToString();
    {
        auto initArrowColor = GetStringAttribute(node_, "arrowColor");
        EXPECT_EQ(initArrowColor, Color::TRANSPARENT.ToString());
        auto initArrowBgColor = GetStringAttribute(node_, "arrowBackgroundColor");
        EXPECT_EQ(initArrowBgColor, Color::TRANSPARENT.ToString());
    }
    {
        Type_SwiperAttribute_displayArrow_Arg0 arkParam = { .selector = 0, .value0 = {
            .isSidebarMiddle = OPT_BOOL_FALSE,
            .arrowColor = {.tag = ARK_TAG_UNDEFINED}, .backgroundColor = {.tag = ARK_TAG_UNDEFINED}
        } };
        modifier_->setDisplayArrow(node_, &arkParam, nullptr);
        auto defaultSmallArrowColor = GetStringAttribute(node_, "arrowColor");
        EXPECT_EQ(defaultSmallArrowColor, DEFAULT_VALUE);
        auto defaultSmallArrowBgColor = GetStringAttribute(node_, "arrowBackgroundColor");
        EXPECT_EQ(defaultSmallArrowBgColor, Color::TRANSPARENT.ToString());
    }
    {
        Type_SwiperAttribute_displayArrow_Arg0 arkParam = { .selector = 0, .value0 = {
            .isSidebarMiddle = OPT_BOOL_TRUE,
            .arrowColor = {.tag = ARK_TAG_UNDEFINED}, .backgroundColor = {.tag = ARK_TAG_UNDEFINED}
        } };
        modifier_->setDisplayArrow(node_, &arkParam, nullptr);
        auto defaultBigArrowColor = GetStringAttribute(node_, "arrowColor");
        EXPECT_EQ(defaultBigArrowColor, DEFAULT_VALUE);
        auto defaultBigArrowBgColor = GetStringAttribute(node_, "arrowBackgroundColor");
        EXPECT_EQ(defaultBigArrowBgColor, DEFAULT_VALUE);
    }
}

/**
 * @tc.name: setDisplayArrowTestStyleColor
 * @tc.desc: Check the functionality of SwiperModifier.DisplayArrowImpl with Style, the Color's subattributes
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayArrowTestStyleColor, TestSize.Level1)
{
    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static Ark_String resName = {.chars = "aa.bb.cc"};
    static const std::string EXPECTED_RESOURCE_COLOR =
        Color::RED.ToString(); // Color::RED is result of stubs for ThemeConstants::GetColorByName
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Ark_ResourceColor, Ark_Int32>(0x12345678), "#12345678" },
        { ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
        { ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), "#00000000" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
        { ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&resName)), EXPECTED_RESOURCE_COLOR },
        { ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 1234)), EXPECTED_RESOURCE_COLOR },
    };

    ASSERT_NE(modifier_->setDisplayArrow, nullptr);

    for (const auto &[arkResColor, expected]: testPlan) {
        Ark_ArrowStyle style = {
             .arrowColor = OptValue<Opt_ResourceColor>(arkResColor),
             .backgroundColor = OptValue<Opt_ResourceColor>(arkResColor)
        };
        auto arkParam = ArkUnion<Type_SwiperAttribute_displayArrow_Arg0, Ark_ArrowStyle>(style);
        modifier_->setDisplayArrow(node_, &arkParam, nullptr);
        auto checkColor = GetStringAttribute(node_, "arrowColor");
        EXPECT_EQ(checkColor, expected);
        auto checkBgColor = GetStringAttribute(node_, "arrowBackgroundColor");
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
    static const std::string PROP_NAME("displayArrow");
    static const std::string PROP_NAME_EXT("hoverShow");
    ASSERT_NE(modifier_->setDisplayArrow, nullptr);

    auto isDisplayArrowDefault = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(isDisplayArrowDefault, EXPECTED_FALSE);
    auto isHoverShowDefault = GetStringAttribute(node_, PROP_NAME_EXT);
    EXPECT_EQ(isHoverShowDefault, EXPECTED_FALSE);

    auto boolFalse = ArkUnion<Type_SwiperAttribute_displayArrow_Arg0, Ark_Boolean>(ABOOL_FALSE);
    modifier_->setDisplayArrow(node_, &boolFalse, nullptr);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, EXPECTED_FALSE);
    auto checkVal2x = GetStringAttribute(node_, PROP_NAME_EXT);
    EXPECT_EQ(checkVal2x, EXPECTED_FALSE);

    auto boolIndTrue = ArkUnion<Type_SwiperAttribute_displayArrow_Arg0, Ark_Boolean>(ABOOL_TRUE);
    modifier_->setDisplayArrow(node_, &boolIndTrue, nullptr);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, EXPECTED_TRUE);
    auto checkVal3x = GetStringAttribute(node_, PROP_NAME_EXT);
    EXPECT_EQ(checkVal3x, EXPECTED_FALSE);

    modifier_->setDisplayArrow(node_, &boolIndTrue, &OPT_BOOL_TRUE);
    auto checkVal4x = GetStringAttribute(node_, PROP_NAME_EXT);
    EXPECT_EQ(checkVal4x, EXPECTED_TRUE);

    modifier_->setDisplayArrow(node_, &boolIndTrue, &OPT_BOOL_UNDEF);
    auto checkVal5x = GetStringAttribute(node_, PROP_NAME_EXT);
    EXPECT_EQ(checkVal5x, EXPECTED_TRUE); // nothing change

    modifier_->setDisplayArrow(node_, &boolIndTrue, &OPT_BOOL_FALSE);
    auto checkVal6x = GetStringAttribute(node_, PROP_NAME_EXT);
    EXPECT_EQ(checkVal6x, EXPECTED_FALSE);

    modifier_->setDisplayArrow(node_, &boolIndTrue, &OPT_BOOL_UNDEF);
    auto checkVal7x = GetStringAttribute(node_, PROP_NAME_EXT);
    EXPECT_EQ(checkVal7x, EXPECTED_FALSE); // nothing change
}
/**
 * @tc.name: setLoopTest
 * @tc.desc: Check the functionality of SwiperModifier.LoopImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setLoopTest, TestSize.Level1)
{
    static const std::string PROP_NAME("loop");
    static const std::string &DEFAULT_VALUE(EXPECTED_TRUE);
    ASSERT_NE(modifier_->setLoop, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    modifier_->setLoop(node_, ABOOL_TRUE);
    auto checkTrue = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkTrue, EXPECTED_TRUE);

    modifier_->setLoop(node_, ABOOL_FALSE);
    auto checkFalse = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkFalse, EXPECTED_FALSE);
}
/**
 * @tc.name: setDurationTest
 * @tc.desc: Check the functionality of SwiperModifier.DurationImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDurationTest, TestSize.Level1)
{
    static const std::string PROP_NAME("duration");
    static const std::string DEFAULT_VALUE("400"); // corrrsponds to
    // DEFAULT_SWIPER_ANIMATION_DURATION in frameworks/core/components/declaration/swiper/swiper_declaration.h
    ASSERT_NE(modifier_->setDuration, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    auto numberInt = ArkValue<Ark_Number>(123456);
    modifier_->setDuration(node_, &numberInt);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123456");

    auto numberFlt = ArkValue<Ark_Number>(1.23456f);
    modifier_->setDuration(node_, &numberFlt);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1");

    auto numberIntNeg = ArkValue<Ark_Number>(-1);
    modifier_->setDuration(node_, &numberIntNeg);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);

    auto numberFltNeg = ArkValue<Ark_Number>(-1.111f);
    modifier_->setDuration(node_, &numberFltNeg);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, DEFAULT_VALUE);
}
/**
 * @tc.name: setVerticalTest
 * @tc.desc: Check the functionality of SwiperModifier.VerticalImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setVerticalTest, TestSize.Level1)
{
    static const std::string PROP_NAME("vertical");
    static const std::string DEFAULT_VALUE(EXPECTED_FALSE);
    ASSERT_NE(modifier_->setVertical, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    modifier_->setVertical(node_, ABOOL_TRUE);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setVertical(node_, ABOOL_FALSE);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);
}
/**
 * @tc.name: setItemSpaceTest
 * @tc.desc: Check the functionality of SwiperModifier.ItemSpaceImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setItemSpaceTest, TestSize.Level1)
{
    using namespace Converter;
    using TypeArg0 = Type_SwiperAttribute_itemSpace_Arg0;
    using OneTestStep = std::pair<TypeArg0, std::string>;
    static const std::string PROP_NAME("itemSpace");
    static const std::string &DEFAULT_VALUE(EXPECTED_VP_ZERO);
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<TypeArg0, Ark_Number>(AINT32_POS), Dimension(AINT32_POS, DimensionUnit::VP).ToString()},
        { ArkUnion<TypeArg0, Ark_Number>(AFLT32_POS), Dimension(AFLT32_POS, DimensionUnit::VP).ToString()},
        { ArkUnion<TypeArg0, Ark_String>("7.89px"), "7.89px"},
        { ArkUnion<TypeArg0, Ark_String>("1.2345vp"), "1.23vp"},
        { ArkUnion<TypeArg0, Ark_Number>(AINT32_NEG), DEFAULT_VALUE},
        { ArkUnion<TypeArg0, Ark_Number>(AFLT32_NEG), DEFAULT_VALUE},
        { ArkUnion<TypeArg0, Ark_String>("-4.5px"), DEFAULT_VALUE},
        { ArkUnion<TypeArg0, Ark_String>("-56vp"), DEFAULT_VALUE},
    };

    ASSERT_NE(modifier_->setItemSpace, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    for (const auto &[itemSpace, expected]: testPlan) {
        modifier_->setItemSpace(node_, &itemSpace);
        auto checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expected);
    }
}
/**
 * @tc.name: SwiperModifierTest11
 * @tc.desc: Check the functionality of SwiperModifier.DisplayModeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest11, TestSize.Level1)
{
    static const std::string PROP_NAME("displayMode");
    static const std::string DEFAULT_VALUE("SwiperDisplayMode.Stretch"); // corrrsponds to
    // SwiperDisplayMode::STRETCH in frameworks/core/components/declaration/swiper/swiper_declaration.h
    ASSERT_NE(modifier_->setDisplayMode, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    auto arkValue0 = static_cast<Ark_Int32>(OHOS::Ace::SwiperDisplayMode::STRETCH);
    modifier_->setDisplayMode(node_, arkValue0);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "SwiperDisplayMode.Stretch");

    auto arkValue1 = static_cast<Ark_Int32>(OHOS::Ace::SwiperDisplayMode::AUTO_LINEAR);
    modifier_->setDisplayMode(node_, arkValue1);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "SwiperDisplayMode.AutoLinear");

    auto arkValue2 = static_cast<Ark_Int32>(INT_MAX);
    modifier_->setDisplayMode(node_, arkValue2);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);

    auto arkValue3 = static_cast<Ark_Int32>(INT_MIN);
    modifier_->setDisplayMode(node_, arkValue3);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, DEFAULT_VALUE);
}
/**
 * @tc.name: setCachedCountTest
 * @tc.desc: Check the functionality of SwiperModifier.CachedCountImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setCachedCountTest, TestSize.Level1)
{
    static const std::string PROP_NAME("cachedCount");
    static const std::string DEFAULT_VALUE(std::to_string(DEFAULT_SWIPER_CACHED_SIZE));
    ASSERT_NE(modifier_->setCachedCount, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    Ark_Number numberInt = ArkValue<Ark_Number>(123456);
    modifier_->setCachedCount(node_, &numberInt);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123456");

    Ark_Number numberFlt = ArkValue<Ark_Number>(1.23456f);
    modifier_->setCachedCount(node_, &numberFlt);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1");

    Ark_Number numberIntNeg = ArkValue<Ark_Number>(-111);
    modifier_->setCachedCount(node_, &numberIntNeg);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);

    Ark_Number numberFltNeg = ArkValue<Ark_Number>(-1.111f);
    modifier_->setCachedCount(node_, &numberFltNeg);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, DEFAULT_VALUE);
}
/**
 * @tc.name: setDisplayCountTestNumber
 * @tc.desc: Check the functionality of SwiperModifier.DisplayCountImpl with Ark_Number arg
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayCountTestNumber, TestSize.Level1)
{
    static const std::string PROP_NAME("displayCount");
    static const std::string DEFAULT_VALUE("1"); // corrrsponds to
    // DEFAULT_SWIPER_DISPLAY_COUNT in frameworks/core/components/declaration/swiper/swiper_declaration.h
    ASSERT_NE(modifier_->setDisplayCount, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    // Type_SwiperAttribute_displayCount_Arg0 numberInt = {.selector = 0, .value0 = ArkNum(123456)};
    auto numberInt = ArkUnion<Type_SwiperAttribute_displayCount_Arg0, Ark_Number>(123456);
    modifier_->setDisplayCount(node_, &numberInt, nullptr);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123456");

    auto numberFlt = ArkUnion<Type_SwiperAttribute_displayCount_Arg0, Ark_Number>(1.23456f);
    modifier_->setDisplayCount(node_, &numberFlt, nullptr);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1");

    auto numberIntNeg = ArkUnion<Type_SwiperAttribute_displayCount_Arg0, Ark_Number>(-111);
    modifier_->setDisplayCount(node_, &numberIntNeg, nullptr);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);

    auto numberFltNeg = ArkUnion<Type_SwiperAttribute_displayCount_Arg0, Ark_Number>(-1.111f);
    modifier_->setDisplayCount(node_, &numberFltNeg, nullptr);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, DEFAULT_VALUE);
}
/**
 * @tc.name: setDisplayCountTestString
 * @tc.desc: Check the functionality of SwiperModifier.DisplayCountImpl with Ark_String arg
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayCountTestString, TestSize.Level1)
{
    static const std::string PROP_NAME("displayCount");
    static const std::string DEFAULT_VALUE(std::to_string(DEFAULT_SWIPER_DISPLAY_COUNT));
    ASSERT_NE(modifier_->setDisplayCount, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    auto regularVal = ArkUnion<Type_SwiperAttribute_displayCount_Arg0, Ark_String>("1234");
    modifier_->setDisplayCount(node_, &regularVal, nullptr);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "1234");

    auto arkValue0 = ArkValue<Ark_Int32>(OHOS::Ace::SwiperDisplayMode::STRETCH);
    modifier_->setDisplayMode(node_, arkValue0);
    auto autoVal = ArkUnion<Type_SwiperAttribute_displayCount_Arg0, Ark_String>("auto");
    modifier_->setDisplayCount(node_, &autoVal, nullptr);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, DEFAULT_VALUE);
    auto checkValDispMode= GetStringAttribute(node_, "displayMode");
    EXPECT_EQ(checkValDispMode, "SwiperDisplayMode.AutoLinear");

    auto negVal = ArkUnion<Type_SwiperAttribute_displayCount_Arg0, Ark_String>("-1234");
    modifier_->setDisplayCount(node_, &negVal, nullptr);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);
}

/**
 * @tc.name: setDisplayCountTestObj
 * @tc.desc: Check the functionality of SwiperModifier.DisplayCountImpl with Ark_VP object argument
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayCountTestObj, TestSize.Level1)
{
    typedef Type_SwiperAttribute_displayCount_Arg0 displayCountArgT;
    typedef Ark_SwiperAutoFill checkT;
    static const std::string PROP_NAME("minSize");
    static const std::string &DEFAULT_VALUE(EXPECTED_VP_ZERO);
    ASSERT_NE(modifier_->setDisplayCount, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    auto intVal = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_Number>(123)));
    modifier_->setDisplayCount(node_, &intVal, nullptr);
    auto checkInt = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInt, "123.00vp");

    auto floatVal = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_Number>(1.23f)));
    modifier_->setDisplayCount(node_, &floatVal, nullptr);
    auto checkFloat = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkFloat, "1.23vp");

    auto strPx = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_String>("45px")));
    modifier_->setDisplayCount(node_, &strPx, nullptr);
    auto checkStrPx = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkStrPx, "45.00px");

    auto strVp = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_String>("5.60vp")));
    modifier_->setDisplayCount(node_, &strVp, nullptr);
    auto checkStrVp = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkStrVp, "5.60vp");

    auto intNegVal = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_Number>(-123)));
    modifier_->setDisplayCount(node_, &intNegVal, nullptr);
    auto checkIntNeg = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkIntNeg, DEFAULT_VALUE);

    auto floatNegVal = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_Number>(-1.23f)));
    modifier_->setDisplayCount(node_, &floatNegVal, nullptr);
    auto checkFloatNeg = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkFloatNeg, DEFAULT_VALUE);

    auto strPxNeg = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_String>("-4.5px")));
    modifier_->setDisplayCount(node_, &strPxNeg, nullptr);
    auto checkStrPxNeg = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkStrPxNeg, DEFAULT_VALUE);

    auto strVpNeg = ArkUnion<displayCountArgT, checkT>(ArkValue<checkT>(ArkUnion<Ark_VP, Ark_String>("-56vp")));
    modifier_->setDisplayCount(node_, &strVpNeg, nullptr);
    auto checkStrVpNeg = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkStrVpNeg, DEFAULT_VALUE);
}

/**
 * @tc.name: setDisplayCountTestByGroup
 * @tc.desc: Check the functionality of SwiperModifier.DisplayCountImpl with ByGroup optional
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisplayCountTestByGroup, TestSize.Level1)
{
    static const std::string PROP_NAME("swipeByGroup");
    static const std::string DEFAULT_VALUE(EXPECTED_FALSE);
    ASSERT_NE(modifier_->setDisplayCount, nullptr);

    Type_SwiperAttribute_displayCount_Arg0 aceFakeArg0;

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    modifier_->setDisplayCount(node_, &aceFakeArg0, &OPT_BOOL_TRUE);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setDisplayCount(node_, &aceFakeArg0, nullptr);
    auto checkVal2opt = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2opt, EXPECTED_TRUE); // nothing change if no optional arg

    modifier_->setDisplayCount(node_, &aceFakeArg0, &OPT_BOOL_FALSE);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);

    modifier_->setDisplayCount(node_, &aceFakeArg0, nullptr);
    auto checkVal3opt = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3opt, EXPECTED_FALSE); // nothing change if no optional arg
}

/**
 * @tc.name: setEffectModeTest
 * @tc.desc: Check the functionality of SwiperModifier.EffectModeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setEffectModeTest, TestSize.Level1)
{
    static const std::string PROP_NAME("effectMode");
    static const std::string DEFAULT_VALUE("EdgeEffect.Spring");
    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    auto arkValue0 = static_cast<Ark_Int32>(OHOS::Ace::EdgeEffect::SPRING);
    modifier_->setEffectMode(node_, arkValue0);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "EdgeEffect.Spring");

    auto arkValue1 = static_cast<Ark_Int32>(OHOS::Ace::EdgeEffect::FADE);
    modifier_->setEffectMode(node_, arkValue1);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "EdgeEffect.Fade");

    auto arkValue2 = static_cast<Ark_Int32>(INT_MAX);
    modifier_->setEffectMode(node_, arkValue2);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);

    auto arkValue3 = static_cast<Ark_Int32>(INT_MIN);
    modifier_->setEffectMode(node_, arkValue3);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, DEFAULT_VALUE);
}
/**
 * @tc.name: setDisableSwipeTest
 * @tc.desc: Check the functionality of SwiperModifier.DisableSwipeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setDisableSwipeTest, TestSize.Level1)
{
    static const std::string PROP_NAME("disableSwipe");
    static const std::string DEFAULT_VALUE(EXPECTED_FALSE);
    ASSERT_NE(modifier_->setDisableSwipe, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    modifier_->setDisableSwipe(node_, ABOOL_TRUE);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, EXPECTED_TRUE);

    modifier_->setDisableSwipe(node_, ABOOL_FALSE);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, EXPECTED_FALSE);
}
/**
 * @tc.name: SwiperModifierTest16
 * @tc.desc: Check the functionality of SwiperModifier.CurveImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest16, TestSize.Level1)
{
}
/**
 * @tc.name: SwiperModifierTest17
 * @tc.desc: Check the functionality of SwiperModifier.OnChangeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest17, TestSize.Level1)
{
}
/**
 * @tc.name: setIndicatorStyleTest
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorStyleTest, TestSize.Level1)
{
    static const std::string PROP_NAME("indicator");
    ASSERT_NE(modifier_->setIndicatorStyle, nullptr);
    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkValInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkValInitial, EXPECTED_TRUE);

    Opt_IndicatorStyle style = {.tag = ARK_TAG_OBJECT, .value = {
        .left = OPT_LEN_PX_NEG,
        .top = OPT_LEN_VP_NEG,
        .right = OPT_LEN_PX_POS,
        .bottom = OPT_LEN_VP_POS,
        .size = OPT_LEN_PX_POS,
        .mask = OPT_BOOL_TRUE,
        .color = OptValue<Opt_ResourceColor>(ArkUnion<Ark_ResourceColor, Ark_Int32>(0x12345678)),
        .selectedColor = OptValue<Opt_ResourceColor>(ArkUnion<Ark_ResourceColor, Ark_String>("65535")),
    }};
    modifier_->setIndicatorStyle(node_, &style);
    auto strWithObj = GetStringAttribute(node_, PROP_NAME);
    ASSERT_NE(strWithObj, EXPECTED_TRUE);
    ASSERT_NE(strWithObj, EXPECTED_FALSE);

    auto checkL = GetStringAttribute(strWithObj, "left");
    EXPECT_EQ(checkL, "0.00vp");
    auto checkT = GetStringAttribute(strWithObj, "top");
    EXPECT_EQ(checkT, "0.00vp");
    auto checkR = GetStringAttribute(strWithObj, "right");
    EXPECT_EQ(checkR, "1234.00px");
    auto checkB = GetStringAttribute(strWithObj, "bottom");
    EXPECT_EQ(checkB, "1.23vp");

    auto checkW = GetStringAttribute(strWithObj, "itemWidth");
    EXPECT_EQ(checkW, "1234.00px");
    auto checkH = GetStringAttribute(strWithObj, "itemHeight");
    EXPECT_EQ(checkH, "1234.00px");
    auto checkSelW = GetStringAttribute(strWithObj, "selectedItemWidth");
    EXPECT_EQ(checkSelW, "1234.00px");
    auto checkSelH = GetStringAttribute(strWithObj, "selectedItemHeight");
    EXPECT_EQ(checkSelH, "1234.00px");

    auto checkMask = GetStringAttribute(strWithObj, "mask");
    EXPECT_EQ(checkMask, EXPECTED_TRUE);

    auto checkColor = GetStringAttribute(strWithObj, "color");
    EXPECT_EQ(checkColor, "#12345678");
    auto checkSelColor = GetStringAttribute(strWithObj, "selectedColor");
    EXPECT_EQ(checkSelColor, "#FF00FFFF");
}

/**
 * @tc.name: setIndicatorStyleTestInvalid
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorStyleImpl with undefined param
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorStyleTestInvalid, TestSize.Level1)
{
    static const std::string PROP_NAME("indicator");
    ASSERT_NE(modifier_->setIndicatorStyle, nullptr);
    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, EXPECTED_TRUE);

    Opt_IndicatorStyle styleInvalid = {.tag = ARK_TAG_UNDEFINED };
    modifier_->setIndicatorStyle(node_, &styleInvalid);
    auto strWithObj = GetStringAttribute(node_, PROP_NAME);
    ASSERT_NE(strWithObj, EXPECTED_TRUE);
    ASSERT_NE(strWithObj, EXPECTED_FALSE);

    auto checkL = GetStringAttribute(strWithObj, "left");
    EXPECT_EQ(checkL, "0.00vp");
    auto checkT = GetStringAttribute(strWithObj, "top");
    EXPECT_EQ(checkT, "0.00vp");
    auto checkR = GetStringAttribute(strWithObj, "right");
    EXPECT_EQ(checkR, "0.00vp");
    auto checkB = GetStringAttribute(strWithObj, "bottom");
    EXPECT_EQ(checkB, "0.00vp");

    auto checkW = GetStringAttribute(strWithObj, "itemWidth");
    EXPECT_EQ(checkW, "6.00vp");
    auto checkH = GetStringAttribute(strWithObj, "itemHeight");
    EXPECT_EQ(checkH, "6.00vp");
    auto checkSelW = GetStringAttribute(strWithObj, "selectedItemWidth");
    EXPECT_EQ(checkSelW, "6.00vp");
    auto checkSelH = GetStringAttribute(strWithObj, "selectedItemHeight");
    EXPECT_EQ(checkSelH, "6.00vp");

    auto checkMask = GetStringAttribute(strWithObj, "mask");
    EXPECT_EQ(checkMask, EXPECTED_FALSE);

    auto checkColor = GetStringAttribute(strWithObj, "color");
    EXPECT_EQ(checkColor, THEME_SWIPER_INDICATOR_COLOR.ToString());
    auto checkSelColor = GetStringAttribute(strWithObj, "selectedColor");
    EXPECT_EQ(checkSelColor, THEME_SWIPER_INDICATOR_COLOR.ToString());
}

/**
 * @tc.name: setPrevMarginTest
 * @tc.desc: Check the functionality of SwiperModifier.PrevMarginImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setPrevMarginTest, TestSize.Level1)
{
    static const std::string PROP_NAME("prevMargin");
    static const std::string PROP_NAME_OPT("prevMarginIgnoreBlank");
    static const std::string &DEFAULT_VALUE(EXPECTED_VP_ZERO);
    ASSERT_NE(modifier_->setPrevMargin, nullptr);

    // test init state
    auto checkInit = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInit, DEFAULT_VALUE);
    auto checkInitOpt = GetStringAttribute(node_, PROP_NAME_OPT);
    EXPECT_EQ(checkInitOpt, EXPECTED_FALSE);

    // test the main arg
    modifier_->setPrevMargin(node_, &ALEN_PX_POS, nullptr);
    auto checkPxPos = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkPxPos, EXPECTED_PX_POS);
    modifier_->setPrevMargin(node_, &ALEN_VP_NEG, nullptr);
    auto checkVpNeg = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVpNeg, DEFAULT_VALUE);

    // test the optional arg
    modifier_->setPrevMargin(node_, &ALEN_PX_POS, &OPT_BOOL_TRUE);
    auto checkOptTrue = GetStringAttribute(node_, PROP_NAME_OPT);
    EXPECT_EQ(checkOptTrue, EXPECTED_TRUE);
    modifier_->setPrevMargin(node_, &ALEN_PX_POS, &OPT_BOOL_UNDEF);
    auto checkOptUndef = GetStringAttribute(node_, PROP_NAME_OPT);
    EXPECT_EQ(checkOptUndef, EXPECTED_TRUE); // nothing change with the undefined optional param
    modifier_->setPrevMargin(node_, &ALEN_PX_POS, nullptr);
    auto checkOptNull = GetStringAttribute(node_, PROP_NAME_OPT);
    EXPECT_EQ(checkOptNull, EXPECTED_TRUE); // nothing change with no optional param
    modifier_->setPrevMargin(node_, &ALEN_PX_POS, &OPT_BOOL_FALSE);
    auto checkOptFalse = GetStringAttribute(node_, PROP_NAME_OPT);
    EXPECT_EQ(checkOptFalse, EXPECTED_FALSE);
}
/**
 * @tc.name: setNextMarginTest
 * @tc.desc: Check the functionality of SwiperModifier.NextMarginImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setNextMarginTest, TestSize.Level1)
{
    static const std::string PROP_NAME("nextMargin");
    static const std::string PROP_NAME_OPT("nextMarginIgnoreBlank");
    static const std::string &DEFAULT_VALUE(EXPECTED_VP_ZERO);
    ASSERT_NE(modifier_->setNextMargin, nullptr);

    // test init state
    auto checkInit = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInit, DEFAULT_VALUE);
    auto checkInitOpt = GetStringAttribute(node_, PROP_NAME_OPT);
    EXPECT_EQ(checkInitOpt, EXPECTED_FALSE);

    // test the main arg
    modifier_->setNextMargin(node_, &ALEN_PX_POS, nullptr);
    auto checkPxPos = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkPxPos, EXPECTED_PX_POS);
    modifier_->setNextMargin(node_, &ALEN_VP_NEG, nullptr);
    auto checkVpNeg = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVpNeg, DEFAULT_VALUE);

    // test the optional arg
    modifier_->setNextMargin(node_, &ALEN_PX_POS, &OPT_BOOL_TRUE);
    auto checkOptTrue = GetStringAttribute(node_, PROP_NAME_OPT);
    EXPECT_EQ(checkOptTrue, EXPECTED_TRUE);
    modifier_->setNextMargin(node_, &ALEN_PX_POS, &OPT_BOOL_UNDEF);
    auto checkOptUndef = GetStringAttribute(node_, PROP_NAME_OPT);
    EXPECT_EQ(checkOptUndef, EXPECTED_TRUE); // nothing change with the undefined optional param
    modifier_->setNextMargin(node_, &ALEN_PX_POS, nullptr);
    auto checkOptNull = GetStringAttribute(node_, PROP_NAME_OPT);
    EXPECT_EQ(checkOptNull, EXPECTED_TRUE); // nothing change with no optional param
    modifier_->setNextMargin(node_, &ALEN_PX_POS, &OPT_BOOL_FALSE);
    auto checkOptFalse = GetStringAttribute(node_, PROP_NAME_OPT);
    EXPECT_EQ(checkOptFalse, EXPECTED_FALSE);
}
/**
 * @tc.name: SwiperModifierTest21
 * @tc.desc: Check the functionality of SwiperModifier.OnAnimationStartImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest21, TestSize.Level1)
{
}
/**
 * @tc.name: SwiperModifierTest22
 * @tc.desc: Check the functionality of SwiperModifier.OnAnimationEndImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest22, TestSize.Level1)
{
}
/**
 * @tc.name: SwiperModifierTest23
 * @tc.desc: Check the functionality of SwiperModifier.OnGestureSwipeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest23, TestSize.Level1)
{
}
/**
 * @tc.name: SwiperModifierTest24
 * @tc.desc: Check the functionality of SwiperModifier.NestedScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest24, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEffectMode, nullptr);
    // this property JSON showing is not supported in ace_engine
}
/**
 * @tc.name: SwiperModifierTest25
 * @tc.desc: Check the functionality of SwiperModifier.CustomContentTransitionImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest25, TestSize.Level1)
{
}
/**
 * @tc.name: SwiperModifierTest26
 * @tc.desc: Check the functionality of SwiperModifier.OnContentDidScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest26, TestSize.Level1)
{
}
/**
 * @tc.name: setIndicatorInteractiveTest
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorInteractiveImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, setIndicatorInteractiveTest, TestSize.Level1)
{
    static const std::string PROP_NAME("indicatorInteractive");
    static const std::string &DEFAULT_VALUE(EXPECTED_TRUE);
    ASSERT_NE(modifier_->setIndicatorInteractive, nullptr);

    auto checkInitial = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, DEFAULT_VALUE);

    modifier_->setIndicatorInteractive(node_, ABOOL_FALSE);
    auto checkFalse = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkFalse, EXPECTED_FALSE);

    modifier_->setIndicatorInteractive(node_, ABOOL_TRUE);
    auto checkTrue = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkTrue, EXPECTED_TRUE);
}
} // namespace OHOS::Ace::NG
