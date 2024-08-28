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
#include "node_api.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "frameworks/core/components/declaration/swiper/swiper_declaration.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components/swiper/swiper_indicator_theme.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
static const Ark_Boolean ABOOL_TRUE(true);
static const Ark_Boolean ABOOL_FALSE(false);
static const Ark_Int32 AINT32_POS(1234);
static const Ark_Int32 AINT32_NEG(INT_MIN);
static const Ark_Float32 AFLT32_POS(1.234f);
static const Ark_Float32 AFLT32_NEG(-5.6789f);

static const Ark_Number ANUM_INT_POS = {.tag = ARK_TAG_INT32, .i32 = AINT32_POS};
static const Ark_Number ANUM_INT_NEG = {.tag = ARK_TAG_INT32, .i32 = AINT32_NEG};
static const Ark_Number ANUM_FLT_POS = {.tag = ARK_TAG_FLOAT32, .f32 = AFLT32_POS};
static const Ark_Number ANUM_FLT_NEG = {.tag = ARK_TAG_FLOAT32, .f32 = AFLT32_NEG};
static const Ark_String ASTR_DIM_PX_POS = {.chars = "7.89px"};
static const Ark_String ASTR_DIM_PX_NEG = {.chars = "-4.5px"};
static const Ark_String ASTR_DIM_VP_POS = {.chars = "1.23vp"};
static const Ark_String ASTR_DIM_VP_NEG = {.chars = "-56vp"};

static const Ark_Length ALEN_PX_POS = {.type = ARK_TAG_INT32, .value = AINT32_POS, .unit = static_cast<int32_t>(DimensionUnit::PX)};
static const Ark_Length ALEN_PX_NEG = {.type = ARK_TAG_INT32, .value = AINT32_NEG, .unit = static_cast<int32_t>(DimensionUnit::PX)};
static const Ark_Length ALEN_VP_POS = {.type = ARK_TAG_FLOAT32, .value = AFLT32_POS, .unit = static_cast<int32_t>(DimensionUnit::VP)};
static const Ark_Length ALEN_VP_NEG = {.type = ARK_TAG_FLOAT32, .value = AFLT32_NEG, .unit = static_cast<int32_t>(DimensionUnit::VP)};

static const Opt_Length OPT_LEN_PX_POS = { .tag = ARK_TAG_OBJECT, .value = ALEN_PX_POS };
static const Opt_Length OPT_LEN_PX_NEG = { .tag = ARK_TAG_OBJECT, .value = ALEN_PX_NEG };
static const Opt_Length OPT_LEN_VP_POS = { .tag = ARK_TAG_OBJECT, .value = ALEN_VP_POS };
static const Opt_Length OPT_LEN_VP_NEG = { .tag = ARK_TAG_OBJECT, .value = ALEN_VP_NEG };

inline Ark_Number ArkNum(int src)
{
    return {.tag= ARK_TAG_INT32, .i32 = static_cast<Ark_Int32>(src)
    };
}

inline Ark_Number ArkNum(float src)
{
    return {.tag= ARK_TAG_FLOAT32, .f32 = static_cast<Ark_Float32>(src)
    };
}

inline Ark_String ArkStr(const char *s)
{
    return {.chars = s, .length = strlen(s)
    };
}

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

static inline Dimension g_swiperDefaultSize(9876, DimensionUnit::VP);
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
        themeStyle->SetAttr("swiper_indicator_size", { .value = g_swiperDefaultSize });
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
 * @tc.name: SwiperModifierTest2
 * @tc.desc: Check the functionality of SwiperModifier.IndexImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest2, TestSize.Level1)
{
    static const std::string PROP_NAME("index");
    static const std::string DEFAULT_VALUE("0");
    ASSERT_NE(modifier_->setIndex, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    auto numberInt = ArkNum(123456);
    modifier_->setIndex(node_, &numberInt);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123456");

    auto numberFlt = ArkNum(1.23456f);
    modifier_->setIndex(node_, &numberFlt);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1");

    auto numberIntNeg = ArkNum(-1);
    modifier_->setIndex(node_, &numberIntNeg);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);

    auto numberFltNeg = ArkNum(-1.111f);
    modifier_->setIndex(node_, &numberFltNeg);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, DEFAULT_VALUE);
}
/**
 * @tc.name: SwiperModifierTest3
 * @tc.desc: Check the functionality of SwiperModifier.AutoPlayImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest3, TestSize.Level1)
{
    static const std::string PROP_NAME("autoPlay");
    static const std::string DEFAULT_VALUE("false");
    ASSERT_NE(modifier_->setAutoPlay, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    auto arkBoolTrue = ABOOL_TRUE;
    modifier_->setAutoPlay(node_, arkBoolTrue);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "true");

    auto arkBoolFalse = ABOOL_FALSE;
    modifier_->setAutoPlay(node_, arkBoolFalse);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "false");
}
/**
 * @tc.name: SwiperModifierTest4
 * @tc.desc: Check the functionality of SwiperModifier.IntervalImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest4, TestSize.Level1)
{
    static const std::string PROP_NAME("interval");
    static const std::string DEFAULT_VALUE("3000"); // corrrsponds to
    // DEFAULT_SWIPER_AUTOPLAY_INTERVAL in frameworks/core/components/declaration/swiper/swiper_declaration.h
    ASSERT_NE(modifier_->setInterval, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    auto numberInt = ArkNum(123456);
    modifier_->setInterval(node_, &numberInt);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123456");

    auto numberFlt = ArkNum(1.23456f);
    modifier_->setInterval(node_, &numberFlt);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1");

    auto numberIntNeg = ArkNum(-1);
    modifier_->setInterval(node_, &numberIntNeg);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);

    auto numberFltNeg = ArkNum(-1.111f);
    modifier_->setInterval(node_, &numberFltNeg);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, DEFAULT_VALUE);
}

/**
 * @tc.name: SwiperModifierTest5_dot_padding
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Dot type, the padding's subattr
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest5_dot_padding, TestSize.Level1)
{
    typedef std::tuple<Ark_DotIndicator, std::string> OneTestStep;
    static const std::string PROP_NAME("indicator");
    static const std::string DEFAULT_PADDING("0.00vp");
    static const std::vector<OneTestStep> testPlan = {
    { { ._left = OPT_LEN_VP_POS, ._top = OPT_LEN_VP_POS, ._right = OPT_LEN_VP_POS, ._bottom = OPT_LEN_VP_POS,
        ._start = {.tag = ARK_TAG_OBJECT, .value = { .id = ARK_TAG_FLOAT32, .floats = {AFLT32_POS} } },
        ._end = {.tag = ARK_TAG_OBJECT, .value = { .id = ARK_TAG_FLOAT32, .floats = {AFLT32_POS} } },
        }, "1.23vp" },
    { { ._left = OPT_LEN_PX_POS, ._top = OPT_LEN_PX_POS, ._right = OPT_LEN_PX_POS, ._bottom = OPT_LEN_PX_POS,
        ._start = {.tag = ARK_TAG_OBJECT, .value = { .id = ARK_TAG_INT32, .floats = {AINT32_POS} } },
        ._end = {.tag = ARK_TAG_OBJECT, .value = { .id = ARK_TAG_INT32, .floats = {AINT32_POS} } },
        }, "1234.00px" },
    { { ._left = OPT_LEN_VP_NEG, ._top = OPT_LEN_VP_NEG, ._right = OPT_LEN_VP_NEG, ._bottom = OPT_LEN_VP_NEG,
        ._start = {.tag = ARK_TAG_OBJECT, .value = { .id = ARK_TAG_FLOAT32, .floats = {AFLT32_NEG} } },
        ._end = {.tag = ARK_TAG_OBJECT, .value = { .id = ARK_TAG_FLOAT32, .floats = {AFLT32_NEG} } },
        }, DEFAULT_PADDING },
    { { ._left = OPT_LEN_PX_NEG, ._top = OPT_LEN_PX_NEG, ._right = OPT_LEN_PX_NEG, ._bottom = OPT_LEN_PX_NEG,
        ._start = {.tag = ARK_TAG_OBJECT, .value = { .id = ARK_TAG_INT32, .floats = {AINT32_NEG} } },
        ._end = {.tag = ARK_TAG_OBJECT, .value = { .id = ARK_TAG_INT32, .floats = {AINT32_NEG} } },
        }, DEFAULT_PADDING },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkVal1 = GetStringAttribute(node_, "indicator");
    EXPECT_EQ(checkVal1, "true");

    static const std::vector<std::string> keys = { "left", "right", "top", "bottom",
        // "start", "end" - these fields are not supported in SwiperPattern::GetDotIndicatorStyle()
    };
    for (const auto &[dot, expect]: testPlan) {
        Type_SwiperAttribute_indicator_Arg0 arkParam = { .selector = 0, .value0 = dot };
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        for (const auto &nameKey: keys) {
            auto checkVal2 = GetStringAttribute(strWithObj, nameKey);
            EXPECT_EQ(checkVal2, expect);
        }
    }
}

/**
 * @tc.name: SwiperModifierTest5_dot_size
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Dot type, the size's subattr
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest5_dot_size, TestSize.Level1)
{
    typedef std::tuple<Ark_DotIndicator, std::string> OneTestStep;
    static const std::string PROP_NAME("indicator");
    static const std::string DEFAULT_SIZE = g_swiperDefaultSize.ToString();
    static const std::vector<OneTestStep> testPlan = {
    { { ._itemWidth = OPT_LEN_VP_POS, ._itemHeight = OPT_LEN_VP_POS,
        ._selectedItemWidth = OPT_LEN_VP_POS, ._selectedItemHeight = OPT_LEN_VP_POS,
        }, "1.23vp" },
    { { ._itemWidth = OPT_LEN_PX_POS, ._itemHeight = OPT_LEN_PX_POS,
        ._selectedItemWidth = OPT_LEN_PX_POS, ._selectedItemHeight = OPT_LEN_PX_POS,
        }, "1234.00px" },
    { { ._itemWidth = OPT_LEN_VP_NEG, ._itemHeight = OPT_LEN_VP_NEG,
        ._selectedItemWidth = OPT_LEN_VP_NEG, ._selectedItemHeight = OPT_LEN_VP_NEG,
        }, DEFAULT_SIZE },
    { { ._itemWidth = OPT_LEN_PX_NEG, ._itemHeight = OPT_LEN_PX_NEG,
        ._selectedItemWidth = OPT_LEN_PX_NEG, ._selectedItemHeight = OPT_LEN_PX_NEG,
        }, DEFAULT_SIZE },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkVal1 = GetStringAttribute(node_, "indicator");
    EXPECT_EQ(checkVal1, "true");

    static const std::vector<std::string> keys = {
        "itemWidth", "itemHeight", "selectedItemWidth", "selectedItemHeight"
    };
    for (const auto &[dot, expect]: testPlan) {
        Type_SwiperAttribute_indicator_Arg0 arkParam = { .selector = 0, .value0 = dot };
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        for (const auto &nameKey: keys) {
            auto checkVal2 = GetStringAttribute(strWithObj, nameKey);
            EXPECT_EQ(checkVal2, expect);
        }
    }
}

/**
 * @tc.name: SwiperModifierTest5_dot_color
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Dot type, the Color type subattr
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest5_dot_color, TestSize.Level1)
{
    typedef std::pair<Ark_ResourceColor, std::string> OneTestStep;
    static const std::string PROP_NAME("indicator");
    static Ark_String resName = {.chars = "aa.bb.cc"};
    static const std::vector<OneTestStep> testPlan = {
        { { .selector = 0, .value0 = 0x12345678 }, "#12345678" },
        { { .selector = 1, .value1 = {.tag = ARK_TAG_INT32, .i32 = 0x123456} }, "#FF123456" },
        { { .selector = 1, .value1 = {.tag = ARK_TAG_FLOAT32, .f32 = 0.5f} }, "#00000000" },
        { { .selector = 2, .value2 = {.chars = "#11223344"} }, "#11223344" },
        { { .selector = 2, .value2 = {.chars = "65535"} }, "#FF00FFFF" },
        { { .selector = 3, .value3 = ArkRes(&resName) }, Color::RED.ToString() },// Color::RED is result
            // of mocked ThemeConstants::GetColorByName
        { { .selector = 3, .value3 = ArkRes(nullptr, 1234) }, Color::RED.ToString() },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, "true");

    {
        Ark_DotIndicator dot = {
            ._color = {.tag = ARK_TAG_UNDEFINED},
            ._selectedColor = {.tag = ARK_TAG_UNDEFINED}
        };
        Type_SwiperAttribute_indicator_Arg0 arkParam = { .selector = 0, .value0 = dot };
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        auto checkVal2 = GetStringAttribute(strWithObj, "color");
        EXPECT_EQ(checkVal2, "#19182431");
        auto checkVal3 = GetStringAttribute(strWithObj, "selectedColor");
        EXPECT_EQ(checkVal3, "#FF007DFF");
    }

    for (const auto &[arcResColor, expected]: testPlan) {
        Ark_DotIndicator dot = {
            ._color = {.tag = ARK_TAG_OBJECT, .value = { arcResColor} },
            ._selectedColor = { .tag = ARK_TAG_OBJECT, .value = { arcResColor} }
        };
        Type_SwiperAttribute_indicator_Arg0 arkParam = { .selector = 0, .value0 = dot };
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        auto checkVal2 = GetStringAttribute(strWithObj, "color");
        EXPECT_EQ(checkVal2, expected);
        auto checkVal3 = GetStringAttribute(strWithObj, "selectedColor");
        EXPECT_EQ(checkVal3, expected);
    }
}

/**
 * @tc.name: SwiperModifierTest5_dot_other
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Dot type, the other subattr
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest5_dot_other, TestSize.Level1)
{
    typedef std::tuple<Ark_DotIndicator, std::string, std::string> OneTestStep;
    static const std::string PROP_NAME("indicator");
    static const std::vector<OneTestStep> testPlan = {
        { { ._mask = {.tag = ARK_TAG_UNDEFINED},
            ._maxDisplayCount = {.tag = ARK_TAG_UNDEFINED} }, "false", "0"},
        { { ._mask = {.tag = ARK_TAG_OBJECT, .value = ABOOL_TRUE},
            ._maxDisplayCount = {.tag = ARK_TAG_OBJECT, .value = ANUM_INT_POS} }, "true", "1234" },
        { { ._mask = {.tag = ARK_TAG_OBJECT, .value = ABOOL_FALSE},
            ._maxDisplayCount = {.tag = ARK_TAG_OBJECT, .value = ANUM_INT_NEG} }, "false", "0" },
    };

    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, "true");

    for (const auto &[dot, expectMask, expectCount]: testPlan) {
        Type_SwiperAttribute_indicator_Arg0 arkParam = { .selector = 0, .value0 = dot };
        modifier_->setIndicator(node_, &arkParam);
        auto strWithObj = GetStringAttribute(node_, PROP_NAME);
        auto checkVal2 = GetStringAttribute(strWithObj, "mask");
        EXPECT_EQ(checkVal2, expectMask);
        auto checkVal3 = GetStringAttribute(strWithObj, "maxDisplayCount");
        EXPECT_EQ(checkVal3, expectCount);
    }
}
/**
 * @tc.name: SwiperModifierTest5_digit
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Digit type
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest5_digit, TestSize.Level1)
{
    static const std::string PROP_NAME("indicator");
    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, "true");
}
/**
 * @tc.name: SwiperModifierTest5_bool
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorImpl with Boolean type
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest5_bool, TestSize.Level1)
{
    static const std::string PROP_NAME("indicator");
    ASSERT_NE(modifier_->setIndicator, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, "true");

    Type_SwiperAttribute_indicator_Arg0 boolIndFalse = {.selector = 2, .value2 = ABOOL_FALSE};
    modifier_->setIndicator(node_, &boolIndFalse);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "false");

    Type_SwiperAttribute_indicator_Arg0 boolIndTrue = {.selector = 2, .value2 = ABOOL_TRUE};
    modifier_->setIndicator(node_, &boolIndTrue);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "true");
}
/**
 * @tc.name: SwiperModifierTest6
 * @tc.desc: Check the functionality of SwiperModifier.DisplayArrowImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest6, TestSize.Level1)
{
}
/**
 * @tc.name: SwiperModifierTest7
 * @tc.desc: Check the functionality of SwiperModifier.LoopImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest7, TestSize.Level1)
{
    static const std::string PROP_NAME("loop");
    static const std::string DEFAULT_VALUE("true");
    ASSERT_NE(modifier_->setLoop, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    auto arkBoolTrue = ABOOL_TRUE;
    modifier_->setLoop(node_, arkBoolTrue);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "true");

    auto arkBoolFalse = ABOOL_FALSE;
    modifier_->setLoop(node_, arkBoolFalse);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "false");
}
/**
 * @tc.name: SwiperModifierTest8
 * @tc.desc: Check the functionality of SwiperModifier.DurationImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest8, TestSize.Level1)
{
    static const std::string PROP_NAME("duration");
    static const std::string DEFAULT_VALUE("400"); // corrrsponds to
    // DEFAULT_SWIPER_ANIMATION_DURATION in frameworks/core/components/declaration/swiper/swiper_declaration.h
    ASSERT_NE(modifier_->setDuration, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    auto numberInt = ArkNum(123456);
    modifier_->setDuration(node_, &numberInt);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123456");

    auto numberFlt = ArkNum(1.23456f);
    modifier_->setDuration(node_, &numberFlt);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1");

    auto numberIntNeg = ArkNum(-1);
    modifier_->setDuration(node_, &numberIntNeg);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);

    auto numberFltNeg = ArkNum(-1.111f);
    modifier_->setDuration(node_, &numberFltNeg);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, DEFAULT_VALUE);
}
/**
 * @tc.name: SwiperModifierTest9
 * @tc.desc: Check the functionality of SwiperModifier.VerticalImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest9, TestSize.Level1)
{
    static const std::string PROP_NAME("vertical");
    static const std::string DEFAULT_VALUE("false");
    ASSERT_NE(modifier_->setVertical, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    auto arkBoolTrue = ABOOL_TRUE;
    modifier_->setVertical(node_, arkBoolTrue);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "true");

    auto arkBoolFalse = ABOOL_FALSE;
    modifier_->setVertical(node_, arkBoolFalse);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "false");
}
/**
 * @tc.name: SwiperModifierTest10
 * @tc.desc: Check the functionality of SwiperModifier.ItemSpaceImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest10, TestSize.Level1)
{
    static const std::string PROP_NAME("itemSpace");
    static const std::string DEFAULT_VALUE("0.00vp");
    static const std::vector<std::pair<Type_SwiperAttribute_itemSpace_Arg0, std::string>> testPlan = {
        { { .selector = 0, .value0 = ANUM_INT_POS }, "1234.00vp" },
        { { .selector = 0, .value0 = ANUM_FLT_POS }, "1.23vp" },
        { { .selector = 1, .value1 = ASTR_DIM_PX_POS }, "7.89px" },
        { { .selector = 1, .value1 = ASTR_DIM_VP_POS }, "1.23vp" },
        { { .selector = 0, .value0 = ANUM_INT_NEG }, DEFAULT_VALUE },
        { { .selector = 0, .value0 = ANUM_FLT_NEG }, DEFAULT_VALUE },
        { { .selector = 1, .value1 = ASTR_DIM_PX_NEG }, DEFAULT_VALUE },
        { { .selector = 1, .value1 = ASTR_DIM_VP_NEG }, DEFAULT_VALUE },
    };

    ASSERT_NE(modifier_->setItemSpace, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    for (const auto &item: testPlan) {
        modifier_->setItemSpace(node_, &(item.first));
        auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal3, item.second);
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

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

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
 * @tc.name: SwiperModifierTest12
 * @tc.desc: Check the functionality of SwiperModifier.CachedCountImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest12, TestSize.Level1)
{
    static const std::string PROP_NAME("cachedCount");
    static const std::string DEFAULT_VALUE("1"); // corrrsponds to
    // DEFAULT_SWIPER_CACHED_SIZE in frameworks/core/components/declaration/swiper/swiper_declaration.h
    ASSERT_NE(modifier_->setCachedCount, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    Ark_Number numberInt = ArkNum(123456);
    modifier_->setCachedCount(node_, &numberInt);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123456");

    Ark_Number numberFlt = ArkNum(1.23456f);
    modifier_->setCachedCount(node_, &numberFlt);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1");

    Ark_Number numberIntNeg = ArkNum(-111);
    modifier_->setCachedCount(node_, &numberIntNeg);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);

    Ark_Number numberFltNeg = ArkNum(-1.111f);
    modifier_->setCachedCount(node_, &numberFltNeg);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, DEFAULT_VALUE);
}
/**
 * @tc.name: SwiperModifierTest13_Num
 * @tc.desc: Check the functionality of SwiperModifier.DisplayCountImpl with Ark_Number arg
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest13_Num, TestSize.Level1)
{
    static const std::string PROP_NAME("displayCount");
    static const std::string DEFAULT_VALUE("1"); // corrrsponds to
    // DEFAULT_SWIPER_DISPLAY_COUNT in frameworks/core/components/declaration/swiper/swiper_declaration.h
    ASSERT_NE(modifier_->setDisplayCount, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    Type_SwiperAttribute_displayCount_Arg0 numberInt = {.selector = 0, .value0 = ArkNum(123456)};
    modifier_->setDisplayCount(node_, &numberInt, nullptr);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123456");

    Type_SwiperAttribute_displayCount_Arg0 numberFlt = {.selector = 0, .value0 = ArkNum(1.23456f)};
    modifier_->setDisplayCount(node_, &numberFlt, nullptr);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1");

    Type_SwiperAttribute_displayCount_Arg0 numberIntNeg = {.selector = 0, .value0 = ArkNum(-111)};
    modifier_->setDisplayCount(node_, &numberIntNeg, nullptr);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);

    Type_SwiperAttribute_displayCount_Arg0 numberFltNeg = {.selector = 0, .value0 = ArkNum(-1.111f)};
    modifier_->setDisplayCount(node_, &numberFltNeg, nullptr);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, DEFAULT_VALUE);
}
/**
 * @tc.name: SwiperModifierTest13_Str
 * @tc.desc: Check the functionality of SwiperModifier.DisplayCountImpl with Ark_String arg
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest13_Str, TestSize.Level1)
{
    static const std::string PROP_NAME("displayCount");
    static const std::string DEFAULT_VALUE("1"); // corrrsponds to
    // DEFAULT_SWIPER_DISPLAY_COUNT in frameworks/core/components/declaration/swiper/swiper_declaration.h
    ASSERT_NE(modifier_->setDisplayCount, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    Type_SwiperAttribute_displayCount_Arg0 regularVal = {.selector = 1, .value1 = ArkStr("1234")};
    modifier_->setDisplayCount(node_, &regularVal, nullptr);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "1234");

    auto arkValue0 = static_cast<Ark_Int32>(OHOS::Ace::SwiperDisplayMode::STRETCH);
    modifier_->setDisplayMode(node_, arkValue0);
    Type_SwiperAttribute_displayCount_Arg0 autoVal = {.selector = 1, .value1 = ArkStr("auto")};
    modifier_->setDisplayCount(node_, &autoVal, nullptr);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, DEFAULT_VALUE);
    auto checkValDispMode= GetStringAttribute(node_, "displayMode");
    EXPECT_EQ(checkValDispMode, "SwiperDisplayMode.AutoLinear");

    Type_SwiperAttribute_displayCount_Arg0 negVal = {.selector = 1, .value1 = ArkStr("-1234")};
    modifier_->setDisplayCount(node_, &negVal, nullptr);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, DEFAULT_VALUE);
}

static Type_SwiperAttribute_displayCount_Arg0 ArkSwiperAutoFill(Ark_VP val) {
    return {.selector = 2, .value2 = { .minSize = {val}}};
}

/**
 * @tc.name: SwiperModifierTest13_Obj
 * @tc.desc: Check the functionality of SwiperModifier.DisplayCountImpl with Ark_VP arg
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest13_Obj, TestSize.Level1)
{
    static const std::string PROP_NAME("minSize");
    static const std::string DEFAULT_VALUE("0.00vp");
    ASSERT_NE(modifier_->setDisplayCount, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    auto intVal = ArkSwiperAutoFill( { .selector = 1, .value1 = ArkNum(123) } );
    modifier_->setDisplayCount(node_, &intVal, nullptr);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "123.00vp");

    auto floatVal = ArkSwiperAutoFill( { .selector = 1, .value1 = ArkNum(1.23f) });
    modifier_->setDisplayCount(node_, &floatVal, nullptr);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "1.23vp");

    auto pxVal = ArkSwiperAutoFill({ .selector = 0, .value0 = ArkStr("45px") });
    modifier_->setDisplayCount(node_, &pxVal, nullptr);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "45.00px");

    auto vpVal = ArkSwiperAutoFill({ .selector = 0, .value0 = ArkStr("5.6vp") });
    modifier_->setDisplayCount(node_, &vpVal, nullptr);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, "5.60vp");

    auto intNegVal = ArkSwiperAutoFill({ .selector = 1, .value1 = ArkNum(-123) });
    modifier_->setDisplayCount(node_, &intNegVal, nullptr);
    auto checkVal7 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal7, DEFAULT_VALUE);

    auto floatNegVal = ArkSwiperAutoFill({ .selector = 1, .value1 = ArkNum(-1.23f) });
    modifier_->setDisplayCount(node_, &floatNegVal, nullptr);
    auto checkVal8 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal8, DEFAULT_VALUE);

    auto pxNegVal = ArkSwiperAutoFill({ .selector = 0, .value0 = ArkStr("-4.5px") });
    modifier_->setDisplayCount(node_, &pxNegVal, nullptr);
    auto checkVal9 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal9, DEFAULT_VALUE);

    auto vpNegVal = ArkSwiperAutoFill({ .selector = 0, .value0 = ArkStr("-56vp") });
    modifier_->setDisplayCount(node_, &vpNegVal, nullptr);
    auto checkVal10 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal10, DEFAULT_VALUE);
}

/**
 * @tc.name: SwiperModifierTest13_ByGroup
 * @tc.desc: Check the functionality of SwiperModifier.DisplayCountImpl with ByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest13_ByGroup, TestSize.Level1)
{
    static const std::string PROP_NAME("swipeByGroup");
    static const std::string DEFAULT_VALUE("false");
    ASSERT_NE(modifier_->setDisplayCount, nullptr);

    Type_SwiperAttribute_displayCount_Arg0 aceFakeArg0;

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    Opt_Boolean optBoolTrue = {.tag = ARK_TAG_OBJECT, .value = ABOOL_TRUE};
    modifier_->setDisplayCount(node_, &aceFakeArg0, &optBoolTrue);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "true");

    modifier_->setDisplayCount(node_, &aceFakeArg0, nullptr);
    auto checkVal2opt = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2opt, "true"); // nothing change if no optional arg

    Opt_Boolean optBoolFalse = {.tag = ARK_TAG_OBJECT, .value = ABOOL_FALSE};
    modifier_->setDisplayCount(node_, &aceFakeArg0, &optBoolFalse);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "false");

    modifier_->setDisplayCount(node_, &aceFakeArg0, nullptr);
    auto checkVal3opt = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3opt, "false"); // nothing change if no optional arg
}

/**
 * @tc.name: SwiperModifierTest14
 * @tc.desc: Check the functionality of SwiperModifier.EffectModeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest14, TestSize.Level1)
{
    static const std::string PROP_NAME("effectMode");
    static const std::string DEFAULT_VALUE("EdgeEffect.Spring");
    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

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
 * @tc.name: SwiperModifierTest15
 * @tc.desc: Check the functionality of SwiperModifier.DisableSwipeImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest15, TestSize.Level1)
{
    static const std::string PROP_NAME("disableSwipe");
    static const std::string DEFAULT_VALUE("false");
    ASSERT_NE(modifier_->setDisableSwipe, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    auto arkBoolTrue = ABOOL_TRUE;
    modifier_->setDisableSwipe(node_, arkBoolTrue);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "true");

    auto arkBoolFalse = ABOOL_FALSE;
    modifier_->setDisableSwipe(node_, arkBoolFalse);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "false");
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
 * @tc.name: SwiperModifierTest18
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorStyleImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest18, TestSize.Level1)
{
}
/**
 * @tc.name: SwiperModifierTest19
 * @tc.desc: Check the functionality of SwiperModifier.PrevMarginImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest19, TestSize.Level1)
{
}
/**
 * @tc.name: SwiperModifierTest20
 * @tc.desc: Check the functionality of SwiperModifier.NextMarginImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest20, TestSize.Level1)
{
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
 * @tc.name: SwiperModifierTest27
 * @tc.desc: Check the functionality of SwiperModifier.IndicatorInteractiveImpl
 * @tc.type: FUNC
 */
HWTEST_F(SwiperModifierTest, SwiperModifierTest27, TestSize.Level1)
{
    static const std::string PROP_NAME("indicatorInteractive");
    static const std::string DEFAULT_VALUE("true");
    ASSERT_NE(modifier_->setIndicatorInteractive, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_VALUE);

    auto arkBoolFalse = ABOOL_FALSE;
    modifier_->setIndicatorInteractive(node_, arkBoolFalse);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "false");

    auto arkBoolTrue = ABOOL_TRUE;
    modifier_->setIndicatorInteractive(node_, arkBoolTrue);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "true");
}
} // namespace OHOS::Ace::NG
