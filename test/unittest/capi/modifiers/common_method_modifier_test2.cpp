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
const auto ATTRIBUTE_RESPONSE_REGION_NAME = "responseRegion";
const auto ATTRIBUTE_CONSTRAINT_SIZE_NAME = "constraintSize";
const auto ATTRIBUTE_TOUCHABLE_NAME = "touchable";
const auto ATTRIBUTE_LAYOUT_WEIGHT_NAME = "layoutWeight";
const auto ATTRIBUTE_HIT_TEST_MODE_NAME = "hitTestBehavior";
const auto ATTRIBUTE_OPACITY_NAME = "opacity";
const auto ATTRIBUTE_HOVER_EFFECT_NAME = "hoverEffect";
const auto ATTRIBUTE_VISIBILITY_NAME = "visibility";
const auto ATTRIBUTE_FOCUSABLE_NAME = "focusable";
const auto ATTRIBUTE_ALIGN_SELF_NAME = "alignSelf";
const auto ATTRIBUTE_DISPLAY_PRIORITY_NAME = "displayPriority";
const auto ATTRIBUTE_Z_INDEX_NAME = "zIndex";
const auto ATTRIBUTE_DIRECTION_NAME = "direction";
const auto ATTRIBUTE_ALIGN_NAME = "align";
const auto ATTRIBUTE_POSITION_NAME = "position";
const auto ATTRIBUTE_ENABLED_NAME = "enabled";
const auto ATTRIBUTE_ASPECT_RATIO_NAME = "aspectRatio";
const auto ATTRIBUTE_SHADOW_NAME = "shadow";
const auto ATTRIBUTE_BACKGROUND_BLUR_STYLE_NAME = "backgroundBlurStyle";
const auto ATTRIBUTE_FOREGROUND_BLUR_STYLE_NAME = "foregroundBlurStyle";
const auto ATTRIBUTE_BLUR_NAME = "blur";
const auto ATTRIBUTE_OVERLAY_NAME = "overlay";
const auto ATTRIBUTE_BORDER_NAME = "border";
const auto ATTRIBUTE_BORDER_STYLE_NAME = "borderStyle";
const auto ATTRIBUTE_BORDER_COLOR_NAME = "borderColor";
const auto ATTRIBUTE_BORDER_WIDTH_NAME = "borderWidth";
const auto ATTRIBUTE_BORDER_RADIUS_NAME = "borderRadius";
const auto ATTRIBUTE_BORDER_IMAGE_NAME = "borderImage";
const auto ATTRIBUTE_LINEAR_GRADIENT_NAME = "linearGradient";
const auto ATTRIBUTE_SWEEP_GRADIENT_NAME = "sweepGradient";

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
} // namespace

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
 * @tc.name: setResponseRegion
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setResponseRegion, TestSize.Level1)
{
    Ark_Union_Array_Rectangle_Rectangle inputValue;
    inputValue.selector = 1;
    inputValue.value1.x = Converter::ArkValue<Opt_Length>(0.0_vp);
    inputValue.value1.y = Converter::ArkValue<Opt_Length>(0.0_vp);
    inputValue.value1.width = Converter::ArkValue<Opt_Length>(20.0_vp);
    inputValue.value1.height = Converter::ArkValue<Opt_Length>(20.0_vp);
    modifier_->setResponseRegion(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_RESPONSE_REGION_NAME);
    EXPECT_EQ(strResult, "[\"{\\\"x\\\":\\\"0.00vp\\\",\\\"y\\\":\\\"0.00vp\\\","
                         "\\\"width\\\":\\\"20.00vp\\\",\\\"height\\\":\\\"20.00vp\\\"}\"]");

    inputValue.selector = 0;
    inputValue.value0.length = 2;
    inputValue.value0.array = new Ark_Rectangle[] {
        {
            Converter::ArkValue<Opt_Length>(),
            Converter::ArkValue<Opt_Length>(20.0_vp),
            Converter::ArkValue<Opt_Length>(50.0_vp),
            Converter::ArkValue<Opt_Length>(),
        },
        {
            Converter::ArkValue<Opt_Length>(-100.0_vp),
            Converter::ArkValue<Opt_Length>(-100.0_vp),
            Converter::ArkValue<Opt_Length>(200.0_vp),
            Converter::ArkValue<Opt_Length>(200.0_vp),
        }
    };
    modifier_->setResponseRegion(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_RESPONSE_REGION_NAME);
    EXPECT_EQ(strResult, "[\"{\\\"x\\\":\\\"0.00vp\\\",\\\"y\\\":\\\"20.00vp\\\","
                         "\\\"width\\\":\\\"50.00vp\\\",\\\"height\\\":\\\"100.00%\\\"}\","
                         "\"{\\\"x\\\":\\\"-100.00vp\\\",\\\"y\\\":\\\"-100.00vp\\\","
                         "\\\"width\\\":\\\"200.00vp\\\",\\\"height\\\":\\\"200.00vp\\\"}\"]");
}

/*
 * @tc.name: setConstraintSize
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setConstraintSize, TestSize.Level1)
{
    Ark_ConstraintSizeOptions inputValue;
    inputValue.minWidth = Converter::ArkValue<Opt_Length>(10.0_vp);
    inputValue.maxWidth = Converter::ArkValue<Opt_Length>(370.0_vp);
    inputValue.minHeight = Converter::ArkValue<Opt_Length>(10.0_vp);
    inputValue.maxHeight = Converter::ArkValue<Opt_Length>(55.0_vp);
    modifier_->setConstraintSize(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
    EXPECT_EQ(strResult, "{\"minWidth\":\"10.00vp\",\"minHeight\":\"10.00vp\","
                         "\"maxWidth\":\"370.00vp\",\"maxHeight\":\"55.00vp\"}");
}

/*
 * @tc.name: setTouchable
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setTouchable, TestSize.Level1)
{
    modifier_->setTouchable(node_, 1); // true
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_TOUCHABLE_NAME);
    EXPECT_EQ(strResult, "true");

    modifier_->setTouchable(node_, 0); // false
    strResult = GetStringAttribute(node_, ATTRIBUTE_TOUCHABLE_NAME);
    EXPECT_EQ(strResult, "false");
}

/*
 * @tc.name: setLayoutWeight
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setLayoutWeight, TestSize.Level1)
{
    Ark_Union_Number_String inputValue;
    inputValue.selector = 0;
    inputValue.value0 = Converter::ArkValue<Ark_Number>(1.1001f);
    modifier_->setLayoutWeight(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_WEIGHT_NAME);
    EXPECT_EQ(strResult.substr(0, 3), "1.1");

    inputValue.selector = 1;
    inputValue.value1 = Converter::ArkValue<Ark_String>("17");
    modifier_->setLayoutWeight(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_WEIGHT_NAME);
    EXPECT_EQ(strResult, "17");
}

/*
 * @tc.name: setHitTestBehavior
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setHitTestBehavior, TestSize.Level1)
{
    modifier_->setHitTestBehavior(node_, ARK_HIT_TEST_MODE_DEFAULT);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_HIT_TEST_MODE_NAME);
    EXPECT_EQ(strResult, "HitTestMode.Default");
    modifier_->setHitTestBehavior(node_, ARK_HIT_TEST_MODE_BLOCK);
    strResult = GetStringAttribute(node_, ATTRIBUTE_HIT_TEST_MODE_NAME);
    EXPECT_EQ(strResult, "HitTestMode.Block");
    modifier_->setHitTestBehavior(node_, ARK_HIT_TEST_MODE_TRANSPARENT);
    strResult = GetStringAttribute(node_, ATTRIBUTE_HIT_TEST_MODE_NAME);
    EXPECT_EQ(strResult, "HitTestMode.Transparent");
    modifier_->setHitTestBehavior(node_, ARK_HIT_TEST_MODE_NONE);
    strResult = GetStringAttribute(node_, ATTRIBUTE_HIT_TEST_MODE_NAME);
    EXPECT_EQ(strResult, "HitTestMode.None");
}

/*
 * @tc.name: setOpacity
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setOpacity, TestSize.Level1)
{
    Ark_Union_Number_Resource inputValue;
    inputValue.selector = 0;
    inputValue.value0 = Converter::ArkValue<Ark_Number>(0.7001);
    modifier_->setOpacity(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_OPACITY_NAME);
    EXPECT_EQ(strResult.substr(0, 3), "0.7");
}

/**
 * @tc.name: setForegroundColorTest
 * @tc.desc: Check the functionality of CommonMethodModifierTest2.setForegroundColor
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setForegroundColor, TestSize.Level1)
{
    using OneTestStep = std::pair<Ark_ResourceColor, std::string>;
    static const std::string PROP_NAME("foregroundColor");
    static Ark_String resName = ArkValue<Ark_String>("aa.bb.cc");
    static const std::string EXPECTED_RESOURCE_COLOR =
        Color::RED.ToString(); // Color::RED is result of ThemeConstants::GetColorXxxx stubs
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
        { ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), "#00000000" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
        { ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
        { ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&resName)), EXPECTED_RESOURCE_COLOR },
        { ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 1234)), EXPECTED_RESOURCE_COLOR },
    };

    ASSERT_NE(modifier_->setForegroundColor, nullptr);

    for (const auto &[arkResColor, expected]: testPlan) {
        Ark_Union_ResourceColor_ColoringStrategy value = {
            .selector = 0,
            .value0 = arkResColor
        };
        modifier_->setForegroundColor(node_, &value);
        auto checkColor = GetAttrValue<std::string>(node_, PROP_NAME);
        EXPECT_EQ(checkColor, expected);
    }
}

/*
 * @tc.name: setHoverEffect
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setHoverEffect, TestSize.Level1)
{
    modifier_->setHoverEffect(node_, ARK_HOVER_EFFECT_NONE);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_HOVER_EFFECT_NAME);
    EXPECT_EQ(strResult, "HoverEffect.None");

    modifier_->setHoverEffect(node_, ARK_HOVER_EFFECT_AUTO);
    strResult = GetStringAttribute(node_, ATTRIBUTE_HOVER_EFFECT_NAME);
    EXPECT_EQ(strResult, "HoverEffect.Auto");

    modifier_->setHoverEffect(node_, ARK_HOVER_EFFECT_SCALE);
    strResult = GetStringAttribute(node_, ATTRIBUTE_HOVER_EFFECT_NAME);
    EXPECT_EQ(strResult, "HoverEffect.Scale");

    modifier_->setHoverEffect(node_, ARK_HOVER_EFFECT_HIGHLIGHT);
    strResult = GetStringAttribute(node_, ATTRIBUTE_HOVER_EFFECT_NAME);
    EXPECT_EQ(strResult, "HoverEffect.Highlight");
}

/*
 * @tc.name: setVisibility
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setVisibility, TestSize.Level1)
{
    modifier_->setVisibility(node_, ARK_VISIBILITY_VISIBLE);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_VISIBILITY_NAME);
    EXPECT_EQ(strResult, "Visibility.Visible");

    modifier_->setVisibility(node_, ARK_VISIBILITY_HIDDEN);
    strResult = GetStringAttribute(node_, ATTRIBUTE_VISIBILITY_NAME);
    EXPECT_EQ(strResult, "Visibility.Hidden");

    modifier_->setVisibility(node_, ARK_VISIBILITY_NONE);
    strResult = GetStringAttribute(node_, ATTRIBUTE_VISIBILITY_NAME);
    EXPECT_EQ(strResult, "Visibility.None");
}

/*
 * @tc.name: setFocusable
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setFocusable, TestSize.Level1)
{
    modifier_->setFocusable(node_, 1);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_FOCUSABLE_NAME);
    EXPECT_EQ(strResult, "true");

    modifier_->setFocusable(node_, 0);
    strResult = GetStringAttribute(node_, ATTRIBUTE_FOCUSABLE_NAME);
    EXPECT_EQ(strResult, "false");
}

/*
 * @tc.name: setAlignSelf
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setAlignSelf, TestSize.Level1)
{
    modifier_->setAlignSelf(node_, ARK_ITEM_ALIGN_AUTO);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_SELF_NAME);
    EXPECT_EQ(strResult, "ItemAlign.Auto");

    modifier_->setAlignSelf(node_, ARK_ITEM_ALIGN_START);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_SELF_NAME);
    EXPECT_EQ(strResult, "ItemAlign.Start");

    modifier_->setAlignSelf(node_, ARK_ITEM_ALIGN_CENTER);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_SELF_NAME);
    EXPECT_EQ(strResult, "ItemAlign.Center");

    modifier_->setAlignSelf(node_, ARK_ITEM_ALIGN_END);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_SELF_NAME);
    EXPECT_EQ(strResult, "ItemAlign.End");

    modifier_->setAlignSelf(node_, ARK_ITEM_ALIGN_BASELINE);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_SELF_NAME);
    EXPECT_EQ(strResult, "ItemAlign.Baseline");

    modifier_->setAlignSelf(node_, ARK_ITEM_ALIGN_STRETCH);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_SELF_NAME);
    EXPECT_EQ(strResult, "ItemAlign.Stretch");
}

/*
 * @tc.name: setDisplayPriority
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setDisplayPriority, TestSize.Level1)
{
    Ark_Number value = Converter::ArkValue<Ark_Number>(0.7001);
    modifier_->setDisplayPriority(node_, &value);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_DISPLAY_PRIORITY_NAME);
    EXPECT_EQ(strResult, "0");

    value = Converter::ArkValue<Ark_Number>(12);
    modifier_->setDisplayPriority(node_, &value);
    strResult = GetStringAttribute(node_, ATTRIBUTE_DISPLAY_PRIORITY_NAME);
    EXPECT_EQ(strResult, "12");
}

/*
 * @tc.name: setZIndex
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setZIndex, TestSize.Level1)
{
    Ark_Number value = Converter::ArkValue<Ark_Number>(0.7001);
    modifier_->setZIndex(node_, &value);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_Z_INDEX_NAME);
    EXPECT_EQ(strResult, "0");

    value = Converter::ArkValue<Ark_Number>(13);
    modifier_->setZIndex(node_, &value);
    strResult = GetStringAttribute(node_, ATTRIBUTE_Z_INDEX_NAME);
    EXPECT_EQ(strResult, "13");
}

/*
 * @tc.name: setDirection
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setDirection, TestSize.Level1)
{
    modifier_->setDirection(node_, ARK_DIRECTION_LTR);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_DIRECTION_NAME);
    EXPECT_EQ(strResult, "Direction.Ltr");

    modifier_->setDirection(node_, ARK_DIRECTION_RTL);
    strResult = GetStringAttribute(node_, ATTRIBUTE_DIRECTION_NAME);
    EXPECT_EQ(strResult, "Direction.Rtl");

    modifier_->setDirection(node_, ARK_DIRECTION_AUTO);
    strResult = GetStringAttribute(node_, ATTRIBUTE_DIRECTION_NAME);
    EXPECT_EQ(strResult, "Direction.Auto");
}

/*
 * @tc.name: setAlign
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setAlign, TestSize.Level1)
{
    modifier_->setAlign(node_, ARK_ALIGNMENT_TOP_START);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_NAME);
    EXPECT_EQ(strResult, "Alignment.TopStart");

    modifier_->setAlign(node_, ARK_ALIGNMENT_TOP);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_NAME);
    EXPECT_EQ(strResult, "Alignment.Top");

    modifier_->setAlign(node_, ARK_ALIGNMENT_TOP_END);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_NAME);
    EXPECT_EQ(strResult, "Alignment.TopEnd");

    modifier_->setAlign(node_, ARK_ALIGNMENT_START);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_NAME);
    EXPECT_EQ(strResult, "Alignment.Start");

    modifier_->setAlign(node_, ARK_ALIGNMENT_CENTER);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_NAME);
    EXPECT_EQ(strResult, "Alignment.Center");

    modifier_->setAlign(node_, ARK_ALIGNMENT_END);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_NAME);
    EXPECT_EQ(strResult, "Alignment.End");

    modifier_->setAlign(node_, ARK_ALIGNMENT_BOTTOM_START);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_NAME);
    EXPECT_EQ(strResult, "Alignment.BottomStart");

    modifier_->setAlign(node_, ARK_ALIGNMENT_BOTTOM);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_NAME);
    EXPECT_EQ(strResult, "Alignment.Bottom");

    modifier_->setAlign(node_, ARK_ALIGNMENT_BOTTOM_END);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_NAME);
    EXPECT_EQ(strResult, "Alignment.BottomEnd");
}

/*
 * @tc.name: setPosition
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setPosition, TestSize.Level1)
{
    Ark_Union_Position_Edges_LocalizedEdges position = {
        .selector = 0,
        .value0 = {
            .x = Converter::ArkValue<Opt_Length>(42.0_vp),
            .y = Converter::ArkValue<Opt_Length>(12.0_px),
        }
    };
    modifier_->setPosition(node_, &position);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(strResult, "{\"x\":\"42.00vp\",\"y\":\"12.00px\"}");

    position = {
        .selector = 0,
        .value0 = {
            .y = Converter::ArkValue<Opt_Length>("13.00%"),
        }
    };
    modifier_->setPosition(node_, &position);
    strResult = GetStringAttribute(node_, ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(strResult, "{\"x\":\"0.00px\",\"y\":\"13.00%\"}");

    position = {
        .selector = 1,
        .value1 = {
            .bottom = Converter::ArkValue<Opt_Length>(42.0_px),
            .left = Converter::ArkValue<Opt_Length>(43.0_vp),
            .right = Converter::ArkValue<Opt_Length>(44.0_fp),
            .top = Converter::ArkValue<Opt_Length>("45.00%"),
        }
    };
    modifier_->setPosition(node_, &position);
    strResult = GetStringAttribute(node_, ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(strResult, "{\"x\":\"\",\"y\":\"\"}");

    position = {
        .selector = 1,
        .value1 = {
            .bottom = Converter::ArkValue<Opt_Length>(1.0_px),
            .top = Converter::ArkValue<Opt_Length>("50.00%"),
        }
    };
    modifier_->setPosition(node_, &position);
    strResult = GetStringAttribute(node_, ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(strResult, "{\"x\":\"\",\"y\":\"\"}");
}

/*
 * @tc.name: setEnabled
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setEnabled, TestSize.Level1)
{
    modifier_->setEnabled(node_, 1);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLED_NAME);
    EXPECT_EQ(strResult, "true");

    modifier_->setEnabled(node_, 0);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLED_NAME);
    EXPECT_EQ(strResult, "false");
}

/*
 * @tc.name: setAspectRatio
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setAspectRatio, TestSize.Level1)
{
    Ark_Number inputValue = Converter::ArkValue<Ark_Number>(1);
    modifier_->setAspectRatio(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_ASPECT_RATIO_NAME);
    EXPECT_EQ(strResult, "1");

    inputValue = Converter::ArkValue<Ark_Number>(16.0f / 9);
    modifier_->setAspectRatio(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ASPECT_RATIO_NAME);
    EXPECT_EQ(strResult.substr(0, 4), "1.78");
}

/*
 * @tc.name: setShadow
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setShadow, TestSize.Level1)
{
    Ark_Union_ShadowOptions_ShadowStyle inputValue = {
        .value0 = {
            .color = {
                .value = {
                    .selector = 0,
                    .value0 = ARK_COLOR_GREEN,
                }
            },
            .fill = {
                .value = Converter::ArkValue<Ark_Boolean>(1),
            },
            .type = {
                .value = Ark_ShadowType::ARK_SHADOW_TYPE_BLUR,
            },
            .offsetX = {
                .value {
                    .selector = 0,
                    .value0 = Converter::ArkValue<Ark_Number>(6),
                }
            },
            .offsetY = {
                .value {
                    .selector = 0,
                    .value0 = Converter::ArkValue<Ark_Number>(10),
                }
            },
            .radius = {
                .selector = 0,
                .value0 = Converter::ArkValue<Ark_Number>(14),
            }
        },
    };
    modifier_->setShadow(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_SHADOW_NAME);
    EXPECT_EQ(strResult, "{\"radius\":\"14.000000\",\"color\":\"#FF008000\",\"offsetX\":\"6.000000\","
                         "\"offsetY\":\"10.000000\",\"type\":\"1\",\"fill\":\"1\"}");
}

/*
 * @tc.name: setBackgroundBlurStyle
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBackgroundBlurStyle, TestSize.Level1)
{
    Ark_BlurStyle style = ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN;
    Opt_BackgroundBlurStyleOptions options = {
        .value = {
            .scale = { .value = Converter::ArkValue<Ark_Number>(2.2999999523162842f) },
            .colorMode = { .value = ARK_THEME_COLOR_MODE_DARK },
            .blurOptions = {
                .value = {
                    .grayscale = {
                        .value0 = Converter::ArkValue<Ark_Number>(7),
                        .value1 = Converter::ArkValue<Ark_Number>(7),
                    }
                }
            },
            .adaptiveColor = {
                .value = ARK_ADAPTIVE_COLOR_AVERAGE,
            }
        }
    };
    modifier_->setBackgroundBlurStyle(node_, style, &options);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_BLUR_STYLE_NAME);
    EXPECT_EQ(strResult, "{\"value\":\"BlurStyle.COMPONENT_ULTRA_THIN\","
                         "\"options\":{\"colorMode\":\"ThemeColorMode.Dark\","
                         "\"adaptiveColor\":\"AdaptiveColor.Average\","
                         "\"policy\":\"BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE\","
                         "\"type\":\"BlurType.WITHIN_WINDOW\","
                         "\"inactiveColor\":\"#FFFFFFFF\",\"scale\":2.2999999523162842}}");
}

/*
 * @tc.name: setForegroundBlurStyle
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setForegroundBlurStyle, TestSize.Level1)
{
    Ark_BlurStyle style = ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN;
    Opt_ForegroundBlurStyleOptions options = {
        .value = {
            .scale = { .value = Converter::ArkValue<Ark_Number>(2.3f) },
            .colorMode = { .value = ARK_THEME_COLOR_MODE_DARK },
            .blurOptions = {
                .value = {
                    .grayscale = {
                        .value0 = Converter::ArkValue<Ark_Number>(7),
                        .value1 = Converter::ArkValue<Ark_Number>(7),
                    }
                }
            },
            .adaptiveColor = {
                .value = ARK_ADAPTIVE_COLOR_AVERAGE,
            }
        }
    };
    modifier_->setForegroundBlurStyle(node_, style, &options);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_FOREGROUND_BLUR_STYLE_NAME);
    EXPECT_EQ(strResult, "");
}

/*
 * @tc.name: setBlur
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setBlur, TestSize.Level1)
{
    Ark_Number value = Converter::ArkValue<Ark_Number>(2.3f);
    Opt_BlurOptions options = {
        .value = {
            .grayscale = {
                .value0 = Converter::ArkValue<Ark_Number>(7),
                .value1 = Converter::ArkValue<Ark_Number>(7),
            }
        }
    };
    modifier_->setBlur(node_, &value, &options);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_BLUR_NAME);
    EXPECT_EQ(strResult, "");
}

/*
 * @tc.name: setOverlay
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setOverlay, TestSize.Level1)
{
    Ark_Union_String_CustomBuilder_ComponentContent value = {
        .selector = 0,
        .value0 = Converter::ArkValue<Ark_String>("TEST_OVERLAY"),
    };
    Opt_OverlayOptions options = {
        .value = {
            .align = { .value = ARK_ALIGNMENT_BOTTOM_END },
            .offset = {
                .value = {
                    .x = { .value = Converter::ArkValue<Ark_Number>(7) },
                    .y = { .value = Converter::ArkValue<Ark_Number>(7) },
                }
            },
        }
    };
    modifier_->setOverlay(node_, &value, &options);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_OVERLAY_NAME);
    EXPECT_EQ(strResult, "{\"title\":\"TEST_OVERLAY\",\"options\":{\"align\":\"Alignment.BottomEnd\","
                         "\"offset\":{\"x\":\"7.00vp\",\"y\":\"7.00vp\"}}}");
}

/*
 * @tc.name: setBorder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBorder, TestSize.Level1)
{
    Ark_BorderOptions inputValue = {
        .color = { .value = { .selector = 1, .value1 = { .selector = 0, .value0 = ARK_COLOR_BLUE }}},
        .dashGap = {
            .value = {
                .selector = 0,
                .value0 = {
                    .left = Converter::ArkValue<Opt_Length>("8.00%"),
                    .top = Converter::ArkValue<Opt_Length>(9.0_fp),
                    .right = Converter::ArkValue<Opt_Length>(8.0_px),
                    .bottom = Converter::ArkValue<Opt_Length>(6.0_vp),
                }
            }
        },
        .dashWidth = {
            .value = {
                .selector = 0,
                .value0 = {
                    .left = Converter::ArkValue<Opt_Length>("8.00%"),
                    .top = Converter::ArkValue<Opt_Length>(4.0_fp),
                    .right = Converter::ArkValue<Opt_Length>(3.0_px),
                    .bottom = Converter::ArkValue<Opt_Length>(1.0_vp),
                }
            }
        },
        .radius = { .value = { .selector = 1, .value1 = Converter::ArkValue<Ark_Length>(5.0_px) }},
        .style = { .value = { .selector = 1, .value1 = ARK_BORDER_STYLE_DASHED }},
        .width = { .value = { .selector = 1, .value1 = Converter::ArkValue<Ark_Length>(10.0_px) }}
    };
    modifier_->setBorder(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_BORDER_NAME);
    EXPECT_EQ(strResult, "{\"style\":\"BorderStyle.Dashed\",\"color\":\"#FF0000FF\","
                         "\"width\":\"10.00px\",\"radius\":\"5.00px\","
                         "\"dashGap\":{\"left\":\"8.00%\",\"top\":\"9.00fp\",\"start\":\"0.00vp\",\"end\":\"0.00vp\","
                         "\"right\":\"8.00px\",\"bottom\":\"6.00vp\"},"
                         "\"dashWidth\":{\"left\":\"8.00%\",\"top\":\"4.00fp\",\"start\":\"0.00vp\",\"end\":\"0.00vp\","
                         "\"right\":\"3.00px\",\"bottom\":\"1.00vp\"}}");
}

/*
 * @tc.name: setBorderStyle
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBorderStyle, TestSize.Level1)
{
    Ark_Union_BorderStyle_EdgeStyles style = {
        .selector = 1,
        .value1 = {
            .left = { .value = ARK_BORDER_STYLE_DOTTED },
            .top = { .value = ARK_BORDER_STYLE_DASHED },
            .right = { .value = ARK_BORDER_STYLE_SOLID },
            .bottom = { .value = ARK_BORDER_STYLE_DOTTED },
        }
    };
    modifier_->setBorderStyle(node_, &style);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_BORDER_STYLE_NAME);
    EXPECT_EQ(strResult, "{\"left\":\"BorderStyle.Dotted\",\"top\":\"BorderStyle.Dashed\","
                         "\"right\":\"BorderStyle.Solid\",\"bottom\":\"BorderStyle.Dotted\"}");
}

/*
 * @tc.name: setBorderWidth
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBorderWidth, TestSize.Level1)
{
    Ark_Union_Length_EdgeWidths_LocalizedEdgeWidths width = {
        .selector = 1,
        .value1 = {
            .left = Converter::ArkValue<Opt_Length>("8.00%"),
            .top = Converter::ArkValue<Opt_Length>(4.0_fp),
            .right = Converter::ArkValue<Opt_Length>(3.0_px),
            .bottom = Converter::ArkValue<Opt_Length>(1.0_vp),
        }
    };
    modifier_->setBorderWidth(node_, &width);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_BORDER_WIDTH_NAME);
    EXPECT_EQ(strResult, "{\"left\":\"8.00%\",\"top\":\"4.00fp\",\"start\":\"0.00vp\","
                         "\"end\":\"0.00vp\",\"right\":\"3.00px\",\"bottom\":\"1.00vp\"}");
}

/*
 * @tc.name: setBorderColor
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBorderColor, TestSize.Level1)
{
    Ark_Union_ResourceColor_EdgeColors_LocalizedEdgeColors color = {
        .selector = 0,
        .value0 = ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_ORANGE),
    };
    modifier_->setBorderColor(node_, &color);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_BORDER_COLOR_NAME);
    EXPECT_EQ(strResult, "#FFFFA500");
}

/*
 * @tc.name: setBorderRadius
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBorderRadius, TestSize.Level1)
{
    Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses radius = {
        .selector = 1,
        .value1 = {
            .topLeft = Converter::ArkValue<Opt_Length>("8.00%"),
            .topRight = Converter::ArkValue<Opt_Length>(7.0_px),
            .bottomRight = Converter::ArkValue<Opt_Length>(6.0_vp),
            .bottomLeft = Converter::ArkValue<Opt_Length>(5.0_fp),
        }
    };
    modifier_->setBorderRadius(node_, &radius);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_BORDER_RADIUS_NAME);
    EXPECT_EQ(strResult, "{\"topLeft\":\"8.00%\",\"topRight\":\"7.00px\",\"bottomLeft\":\"5.00fp\","
                         "\"bottomRight\":\"6.00vp\"}");
}

/*
 * @tc.name: setBorderImage
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBorderImage, TestSize.Level1)
{
    Ark_BorderImageOption image = {
        .fill =  Converter::ArkValue<Opt_Boolean>(true),
        .outset = {
            .value = {
                .selector = 0,
                .value0 = Converter::ArkValue<Ark_Length>(3.0_fp),
            }
        },
        .repeat = {
            .value = ARK_REPEAT_MODE_SPACE
        },
        .slice = {
            .value = {
                .selector = 0,
                .value0 = Converter::ArkValue<Ark_Length>(4.0_vp),
            }
        },
        .source = {
            .value = {
                .selector = 0,
                .value0 = Converter::ArkValue<Ark_String>("some_test_image.png"),
            }
        },
        .width = {
            .value = {
                .selector = 0,
                .value0 = Converter::ArkValue<Ark_Length>("1.00%"),
            }
        }
    };
    modifier_->setBorderImage(node_, &image);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_BORDER_IMAGE_NAME);
    EXPECT_EQ(strResult, "{\"source\":\"some_test_image.png\",\"slice\":\"4.00vp\",\"width\":\"1.00%\","
                         "\"outset\":\"3.00fp\",\"repeat\":\"RepeatMode.Space\",\"fill\":\"true\"}");
}

/*
 * @tc.name: setLinearGradient
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setLinearGradient, TestSize.Level1)
{
    // color stops
    std::vector<std::pair<Ark_ResourceColor, Ark_Number>> colorSteps {
        { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_RED), ArkValue<Ark_Number>(0.1f) },
        { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_GREEN), ArkValue<Ark_Number>(0.5f) },
        { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), ArkValue<Ark_Number>(0.9f) },
    };
    Converter::ArkArrayHolder<Array_Tuple_ResourceColor_Number> colorStepsHolder(colorSteps);
    Ark_Type_CommonMethod_linearGradient_value inputValue = {
        .angle = {
            .value = {
                .selector = 0,
                .value0 = Converter::ArkValue<Ark_Number>(77),
            }
        },
        .direction = {
            .value = ARK_GRADIENT_DIRECTION_LEFT_BOTTOM
        },
        .repeating = Converter::ArkValue<Opt_Boolean>(true),
        .colors = colorStepsHolder.ArkValue()
    };
    modifier_->setLinearGradient(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_LINEAR_GRADIENT_NAME);
    EXPECT_EQ(strResult, "{\"angle\":\"77.00vp\",\"direction\":\"GradientDirection.LeftBottom\","
                         "\"colors\":[[\"#FFFF0000\",\"0.100000\"],[\"#FF008000\",\"0.500000\"],"
                         "[\"#FF0000FF\",\"0.900000\"]],\"repeating\":\"true\"}");
}
/*
 * @tc.name: setSweepGradient
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setSweepGradient, TestSize.Level1)
{
    // color stops
    std::vector<std::pair<Ark_ResourceColor, Ark_Number>> colorSteps {
        { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_RED), ArkValue<Ark_Number>(0.1f) },
        { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_GREEN), ArkValue<Ark_Number>(0.5f) },
        { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), ArkValue<Ark_Number>(0.9f) },
    };
    Converter::ArkArrayHolder<Array_Tuple_ResourceColor_Number> colorStepsHolder(colorSteps);
    Ark_Type_CommonMethod_sweepGradient_value inputValue = {
        .center = {
            .value0 = Converter::ArkValue<Ark_Length>("30.00%"),
            .value1 = Converter::ArkValue<Ark_Length>("42.00%"),
        },
        .start = {
            .value = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("10vp")
        },
        .end = {
            .value = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("100.0%")
        },
        .rotation = {
            .value = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("45")
        },
        .repeating = Converter::ArkValue<Opt_Boolean>(true),
        .colors = colorStepsHolder.ArkValue()
    };


    modifier_->setSweepGradient(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_SWEEP_GRADIENT_NAME);
    EXPECT_EQ(strResult, "{\"center\":[\"30.00%\",\"42.00%\"],\"start\":\"10.00vp\",\"end\":\"100.00%\","
                         "\"colors\":[[\"#FFFF0000\",\"0.100000\"],[\"#FF008000\",\"0.500000\"],[\"#FF0000FF\","
                         "\"0.900000\"]],\"repeating\":\"true\"}");
}
} // namespace OHOS::Ace::NG