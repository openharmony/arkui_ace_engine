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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace {
static const float VALID_VAL = 123.4567f;
static const Opt_Length OPT_LEN_EMPTY = Converter::ArkValue<Opt_Length>(Ark_Empty());
static const Opt_Length OPT_LEN_VALID = Converter::ArkValue<Opt_Length>(VALID_VAL);

static const Ark_Rectangle ARK_RECT_EMPTY {
    OPT_LEN_EMPTY, OPT_LEN_EMPTY, OPT_LEN_EMPTY, OPT_LEN_EMPTY
};
static const Ark_Rectangle ARK_RECT_VALID {
    OPT_LEN_VALID, OPT_LEN_VALID, OPT_LEN_VALID, OPT_LEN_VALID
};

static const DimensionRect EXPECTED_DIM_RECT_DEFAULT;
static const DimensionRect EXPECTED_DIM_RECT_VALID {
    Dimension(VALID_VAL, DimensionUnit::VP), Dimension(VALID_VAL, DimensionUnit::VP),
    DimensionOffset(Dimension(VALID_VAL, DimensionUnit::VP), Dimension(VALID_VAL, DimensionUnit::VP))
};

bool operator==(const OHOS::Ace::DimensionRect& lhs, const OHOS::Ace::DimensionRect& rhs)
{
    return lhs.GetWidth() == rhs.GetWidth() &&
        lhs.GetHeight() == rhs.GetHeight() &&
        lhs.GetOffset() == rhs.GetOffset();
}

template<typename T>
inline T ArkTagUndefined()
{
    return {.tag = ARK_TAG_UNDEFINED};
}
} // namespace

namespace Converter {
    Ark_Tuple_Number_Number ArkValue(Ark_Number value0, Ark_Number value1)
    {
        return {.value0 = value0, .value1 = value1};
    }
    template<>
    Ark_BlurOptions ArkValue(const Ark_Tuple_Number_Number& value)
    {
        return {.grayscale = value};
    }
}

class CommonMethodModifierTest2 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    RefPtr<GestureEventHub> GetGestureEventHub()
    {
        if (auto fnode = reinterpret_cast<FrameNode *>(node_); fnode) {
            if (auto eventHub = fnode->GetEventHub<NG::EventHub>(); eventHub) {
                return eventHub->GetOrCreateGestureEventHub();
            }
        }
        return nullptr;
    }

    RefPtr<MockRenderContext> GetMockRenderContext()
    {
        if (auto fnode = reinterpret_cast<FrameNode *>(node_); fnode) {
            return AceType::DynamicCast<MockRenderContext>(fnode->GetRenderContext());
        }
        return nullptr;
    }
};

/*
 * @tc.name: setResponseRegionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setResponseRegionTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setResponseRegion, nullptr);

    // init state - the nothing region is expected
    auto gestureEventHub = GetGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    EXPECT_TRUE(gestureEventHub->GetResponseRegion().empty());

    // set the empty region, the default value of region is expected
    auto inputValueEmpty = Converter::ArkUnion<Ark_Union_Array_Rectangle_Rectangle, Ark_Rectangle>(ARK_RECT_EMPTY);
    modifier_->setResponseRegion(node_, &inputValueEmpty);
    ASSERT_FALSE(gestureEventHub->GetResponseRegion().empty());
    EXPECT_TRUE(gestureEventHub->GetResponseRegion().front() == EXPECTED_DIM_RECT_DEFAULT);

    // set the valid region, the matched region is expected
    auto inputValueValid = Converter::ArkUnion<Ark_Union_Array_Rectangle_Rectangle, Ark_Rectangle>(ARK_RECT_VALID);
    modifier_->setResponseRegion(node_, &inputValueValid);
    ASSERT_FALSE(gestureEventHub->GetResponseRegion().empty());
    EXPECT_TRUE(gestureEventHub->GetResponseRegion().front() == EXPECTED_DIM_RECT_VALID);

    // set the array of valid regions, the matched regions are expected
    Converter::ArkArrayHolder<Array_Rectangle> arrayHolder {
        ARK_RECT_VALID, ARK_RECT_EMPTY,
    };
    auto inputValueArray =
        Converter::ArkUnion<Ark_Union_Array_Rectangle_Rectangle, Array_Rectangle>(arrayHolder.ArkValue());
    modifier_->setResponseRegion(node_, &inputValueArray);
    ASSERT_FALSE(gestureEventHub->GetResponseRegion().empty());
    EXPECT_TRUE(gestureEventHub->GetResponseRegion().front() == EXPECTED_DIM_RECT_VALID);
    EXPECT_TRUE(gestureEventHub->GetResponseRegion().back() == EXPECTED_DIM_RECT_DEFAULT);
}

/*
 * @tc.name: setMouseResponseRegionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setMouseResponseRegionTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMouseResponseRegion, nullptr);

    // init state - the nothing region is expected
    auto gestureEventHub = GetGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    EXPECT_TRUE(gestureEventHub->GetMouseResponseRegion().empty());

    // set the empty region, the default value of region is expected
    auto inputValueEmpty = Converter::ArkUnion<Ark_Union_Array_Rectangle_Rectangle, Ark_Rectangle>(ARK_RECT_EMPTY);
    modifier_->setMouseResponseRegion(node_, &inputValueEmpty);
    ASSERT_FALSE(gestureEventHub->GetMouseResponseRegion().empty());
    EXPECT_TRUE(gestureEventHub->GetMouseResponseRegion().front() == EXPECTED_DIM_RECT_DEFAULT);

    // set the valid region, the matched region is expected
    auto inputValueValid = Converter::ArkUnion<Ark_Union_Array_Rectangle_Rectangle, Ark_Rectangle>(ARK_RECT_VALID);
    modifier_->setMouseResponseRegion(node_, &inputValueValid);
    ASSERT_FALSE(gestureEventHub->GetMouseResponseRegion().empty());
    EXPECT_TRUE(gestureEventHub->GetMouseResponseRegion().front() == EXPECTED_DIM_RECT_VALID);

    // set the array of valid regions, the matched regions are expected
    Converter::ArkArrayHolder<Array_Rectangle> arrayHolder {
        ARK_RECT_VALID, ARK_RECT_EMPTY,
    };
    auto inputValueArray =
        Converter::ArkUnion<Ark_Union_Array_Rectangle_Rectangle, Array_Rectangle>(arrayHolder.ArkValue());
    modifier_->setMouseResponseRegion(node_, &inputValueArray);
    ASSERT_FALSE(gestureEventHub->GetMouseResponseRegion().empty());
    EXPECT_TRUE(gestureEventHub->GetMouseResponseRegion().front() == EXPECTED_DIM_RECT_VALID);
    EXPECT_TRUE(gestureEventHub->GetMouseResponseRegion().back() == EXPECTED_DIM_RECT_DEFAULT);
}

/*
 * @tc.name: setPixelRoundTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setPixelRoundTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setPixelRound, nullptr);

    using OneTestStep = std::tuple<Ark_PixelRoundCalcPolicy, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Ark_PixelRoundCalcPolicy::ARK_PIXEL_ROUND_CALC_POLICY_NO_FORCE_ROUND, "PixelRoundCalcPolicy.NO_FORCE_ROUND"},
        {Ark_PixelRoundCalcPolicy::ARK_PIXEL_ROUND_CALC_POLICY_FORCE_CEIL, "PixelRoundCalcPolicy.FORCE_CEIL"},
        {Ark_PixelRoundCalcPolicy::ARK_PIXEL_ROUND_CALC_POLICY_FORCE_FLOOR, "PixelRoundCalcPolicy.FORCE_FLOOR"},
        {static_cast<Ark_PixelRoundCalcPolicy>(INT_MIN), "PixelRoundCalcPolicy.NO_FORCE_ROUND"},
    };

    auto checker = [](std::unique_ptr<JsonValue> fullJson, const std::string expected) {
        ASSERT_NE(fullJson, nullptr);
        auto pixelRoundJson = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "pixelRound");
        for (auto key: {"start", "end", "top", "bottom"}) {
            auto checkVal = GetAttrValue<std::string>(pixelRoundJson, key);
            EXPECT_EQ(checkVal, expected) << "Passed key = pixelRound." << key;
        }
    };

    for (auto [value, expected]: testPlan) {
        auto valueOpt = Converter::ArkValue<Opt_PixelRoundCalcPolicy>(value);
        Ark_PixelRoundPolicy inputVal = { valueOpt, valueOpt, valueOpt, valueOpt };
        modifier_->setPixelRound(node_, &inputVal);
        checker(GetJsonValue(node_), expected);
    }
}

/*
 * @tc.name: setBackgroundEffectTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBackgroundEffectTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBackgroundEffect, nullptr);

    EffectOption expectedBgEffect {
        .radius = 123.45_vp,
        .saturation = 0.123f,
        .brightness = 100,
        .color = Color(0xFF123123),
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .blurOption = {.grayscale = {123, -9.87f}},
        .policy = BlurStyleActivePolicy::ALWAYS_ACTIVE,
        .inactiveColor = Color(0xFF00FFFF),
        .blurType = BlurType::WITHIN_WINDOW
    };

    auto renderMock = GetMockRenderContext();
    ASSERT_NE(renderMock, nullptr);
    EXPECT_CALL(*renderMock, UpdateBackgroundEffect(std::optional<EffectOption>(expectedBgEffect))).Times(1);

    Ark_BackgroundEffectOptions inputValValid = {
        .radius = ArkValue<Ark_Number>(123.45f),
        .saturation = ArkValue<Opt_Number>(0.123f),
        .brightness = ArkValue<Opt_Number>(100),
        .color = ArkUnion<Opt_ResourceColor, Ark_Number>(0x123123),
        .adaptiveColor = ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
        .blurOptions = ArkValue<Opt_BlurOptions>(Ark_BlurOptions{
            .grayscale = {ArkValue<Ark_Number>(123), ArkValue<Ark_Number>(-9.87f)}
        }),
        .policy = ArkValue<Opt_BlurStyleActivePolicy>(ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE),
        .inactiveColor = ArkUnion<Opt_ResourceColor, Ark_String>("65535"),
        .type = ArkValue<Opt_BlurType>(Ark_BlurType::ARK_BLUR_TYPE_WITHIN_WINDOW)
    };
    modifier_->setBackgroundEffect(node_, &inputValValid);
}

/*
 * @tc.name: DISABLED_setBackgroundEffectTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setBackgroundEffectTestInvalidValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: setForegroundEffectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setForegroundEffectTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setForegroundEffect, nullptr);
    auto renderMock = GetMockRenderContext();
    ASSERT_NE(renderMock, nullptr);

    Ark_ForegroundEffectOptions inputValValid = {
        .radius = ArkValue<Ark_Number>(VALID_VAL),
    };
    modifier_->setForegroundEffect(node_, &inputValValid);
    ASSERT_TRUE(renderMock->GetForegroundEffect().has_value());
    EXPECT_EQ(renderMock->GetForegroundEffect().value(), VALID_VAL);

    Ark_ForegroundEffectOptions inputValInvalid = {
        .radius = ArkValue<Ark_Number>(INT_MIN),
    };
    modifier_->setForegroundEffect(node_, &inputValInvalid);
    EXPECT_FALSE(renderMock->GetForegroundEffect().has_value());
}

/*
 * @tc.name: setBackgroundBlurStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBackgroundBlurStyleTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBackgroundBlurStyle, nullptr);

    const BlurStyleOption expected {
        .blurStyle = BlurStyle::BACKGROUND_REGULAR,
        .colorMode = ThemeColorMode::DARK,
        .scale = 0.123,
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .blurOption = {.grayscale = {123, -9.87f}},
        .policy = BlurStyleActivePolicy::ALWAYS_ACTIVE,
        .blurType = BlurType::WITHIN_WINDOW,
        .inactiveColor = Color(0xFF00FFFF),
    };

    Ark_BlurStyle inputStyleValid = ARK_BLUR_STYLE_BACKGROUND_REGULAR;
    auto inputOptionValid = ArkValue<Opt_BackgroundBlurStyleOptions>(
        Ark_BackgroundBlurStyleOptions {
            .colorMode  = ArkValue<Opt_ThemeColorMode>(ARK_THEME_COLOR_MODE_DARK),
            .adaptiveColor = ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
            .scale = ArkValue<Opt_Number>(0.123f),
            .blurOptions = ArkValue<Opt_BlurOptions>(Ark_BlurOptions{
                .grayscale = {ArkValue<Ark_Number>(123), ArkValue<Ark_Number>(-9.87f)}
            }),
            .policy = ArkValue<Opt_BlurStyleActivePolicy>(ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE),
            .inactiveColor = ArkUnion<Opt_ResourceColor, Ark_String>("65535"),
            .type = ArkValue<Opt_BlurType>(Ark_BlurType::ARK_BLUR_TYPE_WITHIN_WINDOW)
        }
    );
    modifier_->setBackgroundBlurStyle(node_, inputStyleValid, &inputOptionValid);

    auto renderMock = GetMockRenderContext();
    ASSERT_NE(renderMock, nullptr);
    ASSERT_TRUE(renderMock->GetBackBlurStyle().has_value());
    EXPECT_EQ(renderMock->GetBackBlurStyle().value(), expected);
}

/*
 * @tc.name: DISABLED_setBackgroundBlurStyleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setBackgroundBlurStyleTestInvalidValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_setBackgroundTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setBackgroundTest, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_setBackgroundImageResizableTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setBackgroundImageResizableTest, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_setBackgroundBrightnessTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setBackgroundBrightnessTest, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_OutlineTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_OutlineTestDefaultValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_OutlineTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_OutlineTestValidValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_OutlineStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_OutlineStyleTestDefaultValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_OutlineStyleTestOutlineStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_OutlineStyleTestValidValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_OutlineWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_OutlineWidthTestDefaultValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_OutlineWidthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_OutlineWidthTestValidValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_OutlineColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_OutlineColorTestDefaultValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_OutlineColorTestOutlineColorTopValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_OutlineColorTestValidValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_OutlineRadiusTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_OutlineRadiusTestDefaultValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: DISABLED_OutlineRadiusTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_OutlineRadiusTestValidValues, TestSize.Level1)
{
    EXPECT_TRUE(true); // not implemented
}

/*
 * @tc.name: backdropBlur_setValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur_setValues, TestSize.Level1)
{
    // see ./components_ng/render/adapter/rosen_render_context.cpp for details or possible operation
    double blurRadiusBefore = 3.1415;
    double grayCoeff1 = 2.1;
    double grayCoeff2 = 5.7;
    auto radius = Converter::ArkValue<Ark_Number>(blurRadiusBefore);
    auto grayscale = Converter::ArkValue(
        Converter::ArkValue<Ark_Number>(grayCoeff1),
        Converter::ArkValue<Ark_Number>(grayCoeff2));
    auto options = Converter::ArkValue<Opt_BlurOptions>(Converter::ArkValue<Ark_BlurOptions>(grayscale));

    modifier_->setBackdropBlur(node_, &radius, &options);

    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);

    auto renderMock = GetMockRenderContext();
    ASSERT_EQ(renderMock->backdropBlurOption.grayscale.size(), 2);
    ASSERT_NEAR(renderMock->backdropBlurOption.grayscale[0], grayCoeff1, 0.0001);
    ASSERT_NEAR(renderMock->backdropBlurOption.grayscale[1], grayCoeff2, 0.0001);
}

/*
 * @tc.name: backdropBlur_setNullRadiusValue
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur_setNullRadiusValue, TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusBefore = GetAttrValue<double>(json, "backdropBlur");
    auto grayscale = Converter::ArkValue(Converter::ArkValue<Ark_Number>(2), Converter::ArkValue<Ark_Number>(3));
    auto options = Converter::ArkValue<Opt_BlurOptions>(Converter::ArkValue<Ark_BlurOptions>(grayscale));

    modifier_->setBackdropBlur(node_, nullptr, &options);

    json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);
}

/*
 * @tc.name: backdropBlur_setBadRadiusValue
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur_setBadRadiusValue, TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusBefore = GetAttrValue<double>(json, "backdropBlur");

    Ark_Number radius = ArkTagUndefined<Ark_Number>();
    auto grayscale = Converter::ArkValue(Converter::ArkValue<Ark_Number>(2), Converter::ArkValue<Ark_Number>(3));
    auto options = Converter::ArkValue<Opt_BlurOptions>(Converter::ArkValue<Ark_BlurOptions>(grayscale));

    modifier_->setBackdropBlur(node_, &radius, &options);

    json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);
}

/*
 * @tc.name: backdropBlur_setNullOption
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur_setNullOption, TestSize.Level1)
{
    auto renderMock = GetMockRenderContext();
    double blurRadiusBefore = 3.1415;
    auto radius = Converter::ArkValue<Ark_Number>(blurRadiusBefore);

    modifier_->setBackdropBlur(node_, &radius, nullptr);

    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);

    ASSERT_TRUE(renderMock->backdropBlurOption.grayscale.empty());
}

/*
 * @tc.name: backdropBlur_setValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur_setShortOption, TestSize.Level1)
{
    auto renderMock = GetMockRenderContext();
    double blurRadiusBefore = 3.1415;
    auto radius = Converter::ArkValue<Ark_Number>(blurRadiusBefore);
    float emptyNumberFloat = 0.0;
    float goodNumberFloat = 123.0;
    renderMock->backdropBlurOption.grayscale.clear();

    Ark_Number faultyNumber = ArkTagUndefined<Ark_Number>();
    auto grayscale = Converter::ArkValue(faultyNumber, faultyNumber);
    auto options = Converter::ArkValue<Opt_BlurOptions>(Converter::ArkValue<Ark_BlurOptions>(grayscale));
    modifier_->setBackdropBlur(node_, &radius, &options);

    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);

    ASSERT_FALSE(renderMock->backdropBlurOption.grayscale.empty());
    ASSERT_EQ(emptyNumberFloat, renderMock->backdropBlurOption.grayscale[0]);
    ASSERT_EQ(emptyNumberFloat, renderMock->backdropBlurOption.grayscale[1]);

    renderMock->backdropBlurOption.grayscale.clear();
    auto goodNumber = Converter::ArkValue<Ark_Number>(goodNumberFloat);
    grayscale = Converter::ArkValue(goodNumber, faultyNumber);
    options = Converter::ArkValue<Opt_BlurOptions>(Converter::ArkValue<Ark_BlurOptions>(grayscale));
    modifier_->setBackdropBlur(node_, &radius, &options);

    json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);

    ASSERT_FALSE(renderMock->backdropBlurOption.grayscale.empty());
    ASSERT_EQ(goodNumberFloat, renderMock->backdropBlurOption.grayscale[0]);
    ASSERT_EQ(emptyNumberFloat, renderMock->backdropBlurOption.grayscale[1]);

    renderMock->backdropBlurOption.grayscale.clear();
    grayscale = Converter::ArkValue(faultyNumber, goodNumber);
    options = Converter::ArkValue<Opt_BlurOptions>(Converter::ArkValue<Ark_BlurOptions>(grayscale));
    modifier_->setBackdropBlur(node_, &radius, &options);

    json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);

    ASSERT_FALSE(renderMock->backdropBlurOption.grayscale.empty());
    ASSERT_EQ(emptyNumberFloat, renderMock->backdropBlurOption.grayscale[0]);
    ASSERT_EQ(goodNumberFloat, renderMock->backdropBlurOption.grayscale[1]);
}

} // namespace OHOS::Ace::NG