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

#undef UNITEST_FRIEND_CLASS
#define UNITEST_FRIEND_CLASS friend class IndicatorComponentModifierTests

#include <limits>

#include "swiper_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/implementation/indicator_component_controller_peer.h"

#include "core/components/common/layout/constants.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_ng.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
static const Dimension THEME_SWIPER_INDICATOR_SIZE(9876, DimensionUnit::VP);
static const Dimension THEME_SWIPER_FONT_SIZE(321, DimensionUnit::PX);
static const Color THEME_SWIPER_INDICATOR_COLOR(Color::BLUE);
static const Color THEME_SWIPER_ARROW_COLOR(Color::GREEN);

static const std::vector<std::pair<Opt_Int32, std::string>> TEST_POSITIVE_INTEGER_PLAN {
    {ArkValue<Opt_Int32>(1234), "1234"},
    {ArkValue<Opt_Int32>(5), "5"},
    {ArkValue<Opt_Int32>(INT32_MIN), "0"},
    {ArkValue<Opt_Int32>(-123434), "0"},
};
} // namespace

class IndicatorComponentModifierTests : public ModifierTestBase<GENERATED_ArkUIIndicatorComponentModifier,
    &GENERATED_ArkUINodeModifiers::getIndicatorComponentModifier, GENERATED_ARKUI_INDICATOR_COMPONENT> {
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

    void OnModifyDone()
    {
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto pattern = frameNode->GetPattern<IndicatorPattern>();
        ASSERT_NE(pattern, nullptr);
        pattern->OnModifyDone();
    }

    void SetInternalController(const RefPtr<IndicatorController>& controller)
    {
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto pattern = frameNode->GetPattern<IndicatorPattern>();
        ASSERT_NE(pattern, nullptr);
        pattern->indicatorController_ = controller;
    }
};

/**
 * @tc.name: setInitialIndexTest
 * @tc.desc: Check the functionality of IndicatorComponentModifier.InitialIndexImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setInitialIndexTest, TestSize.Level1)
{
    static const std::string propName("initialIndex");
    static const std::string defaultValue("0");
    ASSERT_NE(modifier_->setInitialIndex, nullptr);

    auto checkDefVal = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkDefVal, defaultValue);

    for (auto [input, expected]: TEST_POSITIVE_INTEGER_PLAN) {
        modifier_->setInitialIndex(node_, &input);
        auto checkVal = GetAttrValue<std::string>(node_, propName);
        EXPECT_EQ(checkVal, expected);
    }
}

/**
 * @tc.name: setCountTest
 * @tc.desc: Check the functionality of IndicatorComponentModifier.CountImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setCountTest, TestSize.Level1)
{
    static const std::string propName("count");
    static const std::string defaultValue("0");
    ASSERT_NE(modifier_->setCount, nullptr);

    auto checkDefVal = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkDefVal, defaultValue);

    for (auto [input, expected]: TEST_POSITIVE_INTEGER_PLAN) {
        modifier_->setCount(node_, &input);
        auto checkVal = GetAttrValue<std::string>(node_, propName);
        EXPECT_EQ(checkVal, expected);
    }
}

/**
 * @tc.name: setLoopTest
 * @tc.desc: Check the functionality of IndicatorComponentModifier.LoopImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setLoopTest, TestSize.Level1)
{
    static const std::string propName("loop");
    static const std::string defaultValue("true");
    ASSERT_NE(modifier_->setLoop, nullptr);

    auto checkDefVal = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkDefVal, defaultValue);
    auto optTrue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setLoop(node_, &optTrue);
    auto checkValT = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkValT, "true");
    auto optFalse = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setLoop(node_, &optFalse);
    auto checkValF = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkValF, "false");
}

/**
 * @tc.name: setVerticalTest
 * @tc.desc: Check the functionality of IndicatorComponentModifier.VerticalImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setVerticalTest, TestSize.Level1)
{
    static const std::string propName("vertical");
    static const std::string defaultValue("false");
    ASSERT_NE(modifier_->setVertical, nullptr);

    auto checkDefVal = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkDefVal, defaultValue);
    auto optTrue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setVertical(node_, &optTrue);
    auto checkValT = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkValT, "true");
    auto optFalse = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setVertical(node_, &optFalse);
    auto checkValF = GetAttrValue<std::string>(node_, propName);
    EXPECT_EQ(checkValF, "false");
}

/**
 * @tc.name: setStyleTestDotValid
 * @tc.desc: Check the functionality of IndicatorComponentModifier.StyleImpl, Dot indicator, layout props
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setStyleTestDotLayoutValid, TestSize.Level1)
{
    Ark_DotIndicator arkDotIndicator {
        ._left = ArkValue<Opt_Length>(123.4f),
        ._top = ArkValue<Opt_Length>(23.45f),
        ._right = ArkValue<Opt_Length>(34.56f),
        ._bottom = ArkValue<Opt_Length>(45.67f),
        ._start = ArkValue<Opt_LengthMetrics>(),
        ._end = ArkValue<Opt_LengthMetrics>(),
        ._space = ArkValue<Opt_LengthMetrics>(),
    };

    ASSERT_NE(modifier_->setStyle, nullptr);
    auto arkParam = ArkUnion<Opt_Union_DotIndicator_DigitIndicator, Ark_DotIndicator>(arkDotIndicator);
    modifier_->setStyle(node_, &arkParam);
    OnModifyDone();

    auto indicatorNode = AceType::Claim<NG::FrameNode>(reinterpret_cast<FrameNode*>(node_));
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    ASSERT_TRUE(layoutProperty->GetIndicatorType());
    EXPECT_EQ(layoutProperty->GetIndicatorType().value(), SwiperIndicatorType::DOT);

    ASSERT_TRUE(layoutProperty->GetLeft().has_value());
    EXPECT_EQ(layoutProperty->GetLeft().value(), 123.4_vp);

    ASSERT_TRUE(layoutProperty->GetTop().has_value());
    EXPECT_EQ(layoutProperty->GetTop().value(), 23.45_vp);

    ASSERT_TRUE(layoutProperty->GetRight().has_value());
    EXPECT_EQ(layoutProperty->GetRight().value(), 34.56_vp);

    ASSERT_TRUE(layoutProperty->GetBottom().has_value());
    EXPECT_EQ(layoutProperty->GetBottom().value(), 45.67_vp);
}

/**
 * @tc.name: setStyleTestDotLayoutInvalid
 * @tc.desc: Check the functionality of IndicatorComponentModifier.StyleImpl, Dot indicator, layout props
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setStyleTestDotLayoutInvalid, TestSize.Level1)
{
    Ark_DotIndicator arkDotIndicator {
        ._left = ArkValue<Opt_Length>(-123.4f),
        ._top = ArkValue<Opt_Length>(std::numeric_limits<float>::lowest()),
        ._right = ArkValue<Opt_Length>(),
        ._bottom = ArkValue<Opt_Length>(),
        ._start = ArkValue<Opt_LengthMetrics>(),
        ._end = ArkValue<Opt_LengthMetrics>(),
    };

    ASSERT_NE(modifier_->setStyle, nullptr);
    auto arkParam = ArkUnion<Opt_Union_DotIndicator_DigitIndicator, Ark_DotIndicator>(arkDotIndicator);
    modifier_->setStyle(node_, &arkParam);
    OnModifyDone();

    auto indicatorNode = AceType::Claim<NG::FrameNode>(reinterpret_cast<FrameNode*>(node_));
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    ASSERT_TRUE(layoutProperty->GetIndicatorType());
    EXPECT_EQ(layoutProperty->GetIndicatorType().value(), SwiperIndicatorType::DOT);

    EXPECT_FALSE(layoutProperty->GetLeft().has_value());
    EXPECT_FALSE(layoutProperty->GetTop().has_value());
    EXPECT_FALSE(layoutProperty->GetRight().has_value());
    EXPECT_FALSE(layoutProperty->GetBottom().has_value());
}

/**
 * @tc.name: setStyleTestDotPaintValid
 * @tc.desc: Check the functionality of IndicatorComponentModifier.StyleImpl, Dot indicator, paint props
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setStyleTestDotPaintValid, TestSize.Level1)
{
    Ark_DotIndicator arkDotIndicator {
        ._itemWidth = ArkValue<Opt_Length>(123.4f),
        ._itemHeight = ArkValue<Opt_Length>(123.4f),
        ._selectedItemWidth = ArkValue<Opt_Length>(123.4f),
        ._selectedItemHeight = ArkValue<Opt_Length>(123.4f),
        ._mask = ArkValue<Opt_Boolean>(true),
        ._color = ArkValue<Opt_ResourceColor>(ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456)),
        ._selectedColor = ArkValue<Opt_ResourceColor>(ArkUnion<Ark_ResourceColor, Ark_String>("#11223344")),
    };

    ASSERT_NE(modifier_->setStyle, nullptr);
    auto arkParam = ArkUnion<Opt_Union_DotIndicator_DigitIndicator, Ark_DotIndicator>(arkDotIndicator);
    modifier_->setStyle(node_, &arkParam);
    OnModifyDone();

    auto indicatorNode = AceType::Claim<NG::FrameNode>(reinterpret_cast<FrameNode*>(node_));
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();

    ASSERT_NE(paintProperty, nullptr);

    ASSERT_TRUE(paintProperty->GetItemWidth().has_value());
    EXPECT_EQ(paintProperty->GetItemWidth().value(), 123.4_vp);

    ASSERT_TRUE(paintProperty->GetItemHeight().has_value());
    EXPECT_EQ(paintProperty->GetItemHeight().value(), 123.4_vp);

    ASSERT_TRUE(paintProperty->GetSelectedItemWidth().has_value());
    EXPECT_EQ(paintProperty->GetItemWidth().value(), 123.4_vp);

    ASSERT_TRUE(paintProperty->GetSelectedItemHeight().has_value());
    EXPECT_EQ(paintProperty->GetSelectedItemHeight().value(), 123.4_vp);

    ASSERT_TRUE(paintProperty->GetIndicatorMask().has_value());
    EXPECT_TRUE(paintProperty->GetIndicatorMask().value());

    ASSERT_TRUE(paintProperty->GetColor().has_value());
    EXPECT_EQ(paintProperty->GetColor().value(), Color(0xFF123456));

    ASSERT_TRUE(paintProperty->GetSelectedColor().has_value());
    EXPECT_EQ(paintProperty->GetSelectedColor().value(), Color(0x11223344));
}

/**
 * @tc.name: setStyleTestDotPaintInvalid
 * @tc.desc: Check the functionality of IndicatorComponentModifier.StyleImpl, Dot indicator, paint props
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, DISABLED_setStyleTestDotPaintInvalid, TestSize.Level1)
{
    Ark_DotIndicator arkDotIndicator {
        ._itemWidth = ArkValue<Opt_Length>(-123.4f),
        ._itemHeight = ArkValue<Opt_Length>(std::numeric_limits<float>::lowest()),
        ._selectedItemWidth = ArkValue<Opt_Length>(-123.4f),
        ._selectedItemHeight = ArkValue<Opt_Length>(std::numeric_limits<float>::lowest()),
        ._mask = ArkValue<Opt_Boolean>(),
        ._color = ArkValue<Opt_ResourceColor>(),
        ._selectedColor = ArkValue<Opt_ResourceColor>(),
    };

    ASSERT_NE(modifier_->setStyle, nullptr);
    auto arkParam = ArkUnion<Opt_Union_DotIndicator_DigitIndicator, Ark_DotIndicator>(arkDotIndicator);
    modifier_->setStyle(node_, &arkParam);
    OnModifyDone();

    auto indicatorNode = AceType::Claim<NG::FrameNode>(reinterpret_cast<FrameNode*>(node_));
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();

    ASSERT_NE(paintProperty, nullptr);

    ASSERT_TRUE(paintProperty->GetItemWidth().has_value());
    EXPECT_EQ(paintProperty->GetItemWidth().value(), THEME_SWIPER_INDICATOR_SIZE);

    ASSERT_TRUE(paintProperty->GetItemHeight().has_value());
    EXPECT_EQ(paintProperty->GetItemHeight().value(), THEME_SWIPER_INDICATOR_SIZE);

    ASSERT_TRUE(paintProperty->GetSelectedItemWidth().has_value());
    EXPECT_EQ(paintProperty->GetSelectedItemWidth().value(), THEME_SWIPER_INDICATOR_SIZE);

    ASSERT_TRUE(paintProperty->GetSelectedItemHeight().has_value());
    EXPECT_EQ(paintProperty->GetSelectedItemHeight().value(), THEME_SWIPER_INDICATOR_SIZE);

    ASSERT_TRUE(paintProperty->GetIndicatorMask().has_value());
    EXPECT_FALSE(paintProperty->GetIndicatorMask().value());

    ASSERT_TRUE(paintProperty->GetColor().has_value());
    EXPECT_EQ(paintProperty->GetColor().value(), THEME_SWIPER_INDICATOR_COLOR);

    ASSERT_TRUE(paintProperty->GetSelectedColor().has_value());
    EXPECT_EQ(paintProperty->GetSelectedColor().value(), THEME_SWIPER_INDICATOR_COLOR);
}

/**
 * @tc.name: setStyleTestDigitLayoutValid
 * @tc.desc: Check the functionality of IndicatorComponentModifier.StyleImpl, Digit indicator, layout props
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setStyleTestDigitLayoutValid, TestSize.Level1)
{
    Ark_DigitIndicator arkDigitIndicator {
        ._left = ArkValue<Opt_Length>(123.4f),
        ._top = ArkValue<Opt_Length>(23.45f),
        ._right = ArkValue<Opt_Length>(34.56f),
        ._bottom = ArkValue<Opt_Length>(45.67f),
        ._start = ArkValue<Opt_LengthMetrics>(),
        ._end = ArkValue<Opt_LengthMetrics>(),
    };

    ASSERT_NE(modifier_->setStyle, nullptr);
    auto arkParam = ArkUnion<Opt_Union_DotIndicator_DigitIndicator, Ark_DigitIndicator>(arkDigitIndicator);
    modifier_->setStyle(node_, &arkParam);
    OnModifyDone();

    auto indicatorNode = AceType::Claim<NG::FrameNode>(reinterpret_cast<FrameNode*>(node_));
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    ASSERT_TRUE(layoutProperty->GetIndicatorType());
    EXPECT_EQ(layoutProperty->GetIndicatorType().value(), SwiperIndicatorType::DIGIT);

    ASSERT_TRUE(layoutProperty->GetLeft().has_value());
    EXPECT_EQ(layoutProperty->GetLeft().value(), 123.4_vp);

    ASSERT_TRUE(layoutProperty->GetTop().has_value());
    EXPECT_EQ(layoutProperty->GetTop().value(), 23.45_vp);

    ASSERT_TRUE(layoutProperty->GetRight().has_value());
    EXPECT_EQ(layoutProperty->GetRight().value(), 34.56_vp);

    ASSERT_TRUE(layoutProperty->GetBottom().has_value());
    EXPECT_EQ(layoutProperty->GetBottom().value(), 45.67_vp);
}

/**
 * @tc.name: setStyleTestDigitValid
 * @tc.desc: Check the functionality of IndicatorComponentModifier.StyleImpl, Digit indicator, layout props
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setStyleTestDigitLayoutInvalid, TestSize.Level1)
{
    Ark_DigitIndicator arkDigitIndicator {
        ._left = ArkValue<Opt_Length>(-123.4f),
        ._top = ArkValue<Opt_Length>(std::numeric_limits<float>::lowest()),
        ._right = ArkValue<Opt_Length>(),
        ._bottom = ArkValue<Opt_Length>(),
        ._start = ArkValue<Opt_LengthMetrics>(),
        ._end = ArkValue<Opt_LengthMetrics>(),
    };

    ASSERT_NE(modifier_->setStyle, nullptr);
    auto arkParam = ArkUnion<Opt_Union_DotIndicator_DigitIndicator, Ark_DigitIndicator>(arkDigitIndicator);
    modifier_->setStyle(node_, &arkParam);
    OnModifyDone();

    auto indicatorNode = AceType::Claim<NG::FrameNode>(reinterpret_cast<FrameNode*>(node_));
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    ASSERT_TRUE(layoutProperty->GetIndicatorType());
    EXPECT_EQ(layoutProperty->GetIndicatorType().value(), SwiperIndicatorType::DIGIT);

    EXPECT_FALSE(layoutProperty->GetLeft().has_value());
    EXPECT_FALSE(layoutProperty->GetTop().has_value());
    EXPECT_FALSE(layoutProperty->GetRight().has_value());
    EXPECT_FALSE(layoutProperty->GetBottom().has_value());
}

/**
 * @tc.name: setStyleTestDigitPaintValid
 * @tc.desc: Check the functionality of IndicatorComponentModifier.StyleImpl, Digit indicator, paint props
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setStyleTestDigitPaintValid, TestSize.Level1)
{
    Ark_DigitIndicator arkDigitIndicator {
        ._fontColor = ArkValue<Opt_ResourceColor>(ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456)),
        ._selectedFontColor = ArkValue<Opt_ResourceColor>(ArkUnion<Ark_ResourceColor, Ark_String>("#11223344")),
        ._digitFont = ArkValue<Opt_Font>(Ark_Font {
            .size = ArkValue<Opt_Length>(123.4f),
            .weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_REGULAR)}),
        ._selectedDigitFont = ArkValue<Opt_Font>(Ark_Font {
            .size = ArkValue<Opt_Length>(43.21f),
            .weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("bold")})
    };

    ASSERT_NE(modifier_->setStyle, nullptr);
    auto arkParam = ArkUnion<Opt_Union_DotIndicator_DigitIndicator, Ark_DigitIndicator>(arkDigitIndicator);
    modifier_->setStyle(node_, &arkParam);
    OnModifyDone();

    auto indicatorNode = AceType::Claim<NG::FrameNode>(reinterpret_cast<FrameNode*>(node_));
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();

    ASSERT_NE(layoutProperty, nullptr);

    ASSERT_TRUE(layoutProperty->GetFontColor().has_value());
    EXPECT_EQ(layoutProperty->GetFontColor().value(), Color(0xFF123456));

    ASSERT_TRUE(layoutProperty->GetSelectedFontColor().has_value());
    EXPECT_EQ(layoutProperty->GetSelectedFontColor().value(), Color(0x11223344));

    ASSERT_TRUE(layoutProperty->GetFontSize().has_value());
    EXPECT_EQ(layoutProperty->GetFontSize().value(), 123.4_fp);

    ASSERT_TRUE(layoutProperty->GetFontWeight().has_value());
    EXPECT_EQ(layoutProperty->GetFontWeight().value(), FontWeight::REGULAR);

    ASSERT_TRUE(layoutProperty->GetSelectedFontSize().has_value());
    EXPECT_EQ(layoutProperty->GetSelectedFontSize().value(), 43.21_fp);

    ASSERT_TRUE(layoutProperty->GetSelectedFontWeight().has_value());
    EXPECT_EQ(layoutProperty->GetSelectedFontWeight().value(), FontWeight::BOLD);
}

/**
 * @tc.name: setStyleTestDigitPaintInvalid
 * @tc.desc: Check the functionality of IndicatorComponentModifier.StyleImpl, Digit indicator, paint props
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, DISABLED_setStyleTestDigitPaintInvalid, TestSize.Level1)
{
    Ark_DigitIndicator arkDigitIndicator {
        ._fontColor = ArkValue<Opt_ResourceColor>(Ark_Empty()),
        ._selectedFontColor = ArkValue<Opt_ResourceColor>(ArkUnion<Ark_ResourceColor, Ark_String>("WrongColor")),
        ._digitFont = ArkValue<Opt_Font>(Ark_Font {
            .size = ArkValue<Opt_Length>(Ark_Empty()),
            .weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(-111)}),
        ._selectedDigitFont = ArkValue<Opt_Font>(Ark_Font {
            .size = ArkValue<Opt_Length>(-111.11f),
            .weight = ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("InvalidData!")})
    };

    ASSERT_NE(modifier_->setStyle, nullptr);
    auto arkParam = ArkUnion<Opt_Union_DotIndicator_DigitIndicator, Ark_DigitIndicator>(arkDigitIndicator);
    modifier_->setStyle(node_, &arkParam);
    OnModifyDone();

    auto indicatorNode = AceType::Claim<NG::FrameNode>(reinterpret_cast<FrameNode*>(node_));
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();

    ASSERT_NE(layoutProperty, nullptr);

    ASSERT_TRUE(layoutProperty->GetFontColor().has_value());
    EXPECT_EQ(layoutProperty->GetFontColor().value(), Color::TRANSPARENT);

    ASSERT_TRUE(layoutProperty->GetSelectedFontColor().has_value());
    EXPECT_EQ(layoutProperty->GetSelectedFontColor().value(), Color::TRANSPARENT);

    ASSERT_TRUE(layoutProperty->GetFontSize().has_value());
    EXPECT_EQ(layoutProperty->GetFontSize().value(), THEME_SWIPER_FONT_SIZE);

    ASSERT_TRUE(layoutProperty->GetFontWeight().has_value());
    EXPECT_EQ(layoutProperty->GetFontWeight().value(), FontWeight::NORMAL);

    ASSERT_TRUE(layoutProperty->GetSelectedFontSize().has_value());
    EXPECT_EQ(layoutProperty->GetSelectedFontSize().value(), THEME_SWIPER_FONT_SIZE);

    ASSERT_TRUE(layoutProperty->GetSelectedFontWeight().has_value());
    EXPECT_EQ(layoutProperty->GetSelectedFontWeight().value(), FontWeight::NORMAL);
}

/**
 * @tc.name: setIndicatorComponentOptionsTest
 * @tc.desc: Check the functionality of IndicatorComponentModifier.SetIndicatorComponentOptionsImpl
 * @tc.type: FUNC
 */
HWTEST_F(IndicatorComponentModifierTests, setIndicatorComponentOptionsTest, TestSize.Level1)
{
    class MockIndicatorController : public IndicatorController {
    public:
        MOCK_METHOD(void, ShowNext, (), (const));
    };
    auto mockIndicatorController = AceType::MakeRefPtr<MockIndicatorController>();
    SetInternalController(mockIndicatorController);

    ASSERT_NE(modifier_->setIndicatorComponentOptions, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setIndicatorComponentOptions(node_, nullptr);
    auto controllerUndef = Converter::ArkValue<Opt_IndicatorComponentController>();
    modifier_->setIndicatorComponentOptions(node_, &controllerUndef);

    // create the external IndicatorComponentController peer and attach the modifier to it
    auto peer = PeerUtils::CreatePeer<IndicatorComponentControllerPeer>();
    ASSERT_NE(peer, nullptr);
    auto controller = Converter::ArkValue<Opt_IndicatorComponentController>(peer);
    modifier_->setIndicatorComponentOptions(node_, &controller);

    // assume the internal controller will be affected
    EXPECT_CALL(*mockIndicatorController, ShowNext()).Times(1);

    // during simulating of the action from the external peer
    peer->ShowNext();
}
} // namespace OHOS::Ace::NG