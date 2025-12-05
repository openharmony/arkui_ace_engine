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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
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
const auto ATTRIBUTE_MARK_ANCHOR_NAME = "markAnchor";
const auto ATTRIBUTE_MARK_ANCHOR_X_NAME = "x";
const auto ATTRIBUTE_MARK_ANCHOR_Y_NAME = "y";
const auto ATTRIBUTE_FOCUS_SCOPE_ID_NAME = "focusScopeId";
const auto ATTRIBUTE_FOCUS_SCOPE_ID_NAME_DEFAULT_VALUE = "";
const auto ATTRIBUTE_IS_GROUP_NAME = "isGroup";
const auto ATTRIBUTE_FOCUS_IS_GROUP_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_FOCUS_ARROW_STEP_OUT_NAME = "arrowStepOut";
const auto ATTRIBUTE_FOCUS_ARROW_STEP_OUT_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_FOCUS_SCOPE_PRIORITY_NAME = "focusScopePriority";
const auto ATTRIBUTE_FOCUS_SCOPE_PRIORITY_DEFAULT_VALUE = "FocusPriority.AUTO";
const auto ATTRIBUTE_SYS_OPTIONS_DISABLE_ADAPTATION_DEFAULT_VALUE = true;

static const float VALID_VAL = 123.4567f;
static const Opt_Length OPT_LEN_EMPTY = Converter::ArkValue<Opt_Length>(Ark_Empty());
static const Opt_Length OPT_LEN_VALID = Converter::ArkValue<Opt_Length>(VALID_VAL);

constexpr double OFFSET_X = 60.4;
constexpr double OFFSET_Y = 85.5;

constexpr int32_t GRAYSCALE_MAX = 127;
constexpr int32_t GRAYSCALE_MIN = 0;

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
} // namespace

namespace GeneratedModifier {
    const GENERATED_ArkUIClickEventAccessor* GetClickEventAccessor();
    const GENERATED_ArkUIKeyEventAccessor* GetKeyEventAccessor();
}

namespace Converter {
    template<>
    Ark_BlurOptions ArkCreate(double v0, double v1)
    {
        Ark_BlurOptions result;
        Ark_Tuple_F64_F64 grayscale = {ArkValue<Ark_Float64>(v0), ArkValue<Ark_Float64>(v1)};
        result.grayscale = ArkValue<Opt_Tuple_F64_F64>(grayscale);
        return result;
    }
}

class CommonMethodModifierTest2 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }

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
HWTEST_F(CommonMethodModifierTest2, DISABLED_setResponseRegionTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setResponseRegion, nullptr);

    // init state - the nothing region is expected
    auto gestureEventHub = GetGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    EXPECT_TRUE(gestureEventHub->GetResponseRegion().empty());

    // set the empty region, the default value of region is expected
    auto inputValueEmpty = Converter::ArkUnion<Opt_Union_Array_Rectangle_Rectangle, Ark_Rectangle>(ARK_RECT_EMPTY);
    modifier_->setResponseRegion(node_, &inputValueEmpty);
    ASSERT_FALSE(gestureEventHub->GetResponseRegion().empty());
    EXPECT_TRUE(gestureEventHub->GetResponseRegion().front() == EXPECTED_DIM_RECT_DEFAULT);

    // set the valid region, the matched region is expected
    auto inputValueValid = Converter::ArkUnion<Opt_Union_Array_Rectangle_Rectangle, Ark_Rectangle>(ARK_RECT_VALID);
    modifier_->setResponseRegion(node_, &inputValueValid);
    ASSERT_FALSE(gestureEventHub->GetResponseRegion().empty());
    EXPECT_TRUE(gestureEventHub->GetResponseRegion().front() == EXPECTED_DIM_RECT_VALID);

    // set the array of valid regions, the matched regions are expected
    Converter::ArkArrayHolder<Array_Rectangle> arrayHolder {
        ARK_RECT_VALID, ARK_RECT_EMPTY,
    };
    auto inputValueArray =
        Converter::ArkUnion<Opt_Union_Array_Rectangle_Rectangle, Array_Rectangle>(arrayHolder.ArkValue());
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
HWTEST_F(CommonMethodModifierTest2, DISABLED_setMouseResponseRegionTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMouseResponseRegion, nullptr);

    // init state - the nothing region is expected
    auto gestureEventHub = GetGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    EXPECT_TRUE(gestureEventHub->GetMouseResponseRegion().empty());

    // set the empty region, the default value of region is expected
    auto inputValueEmpty = Converter::ArkUnion<Opt_Union_Array_Rectangle_Rectangle, Ark_Rectangle>(ARK_RECT_EMPTY);
    modifier_->setMouseResponseRegion(node_, &inputValueEmpty);
    ASSERT_FALSE(gestureEventHub->GetMouseResponseRegion().empty());
    EXPECT_TRUE(gestureEventHub->GetMouseResponseRegion().front() == EXPECTED_DIM_RECT_DEFAULT);

    // set the valid region, the matched region is expected
    auto inputValueValid = Converter::ArkUnion<Opt_Union_Array_Rectangle_Rectangle, Ark_Rectangle>(ARK_RECT_VALID);
    modifier_->setMouseResponseRegion(node_, &inputValueValid);
    ASSERT_FALSE(gestureEventHub->GetMouseResponseRegion().empty());
    EXPECT_TRUE(gestureEventHub->GetMouseResponseRegion().front() == EXPECTED_DIM_RECT_VALID);

    // set the array of valid regions, the matched regions are expected
    Converter::ArkArrayHolder<Array_Rectangle> arrayHolder {
        ARK_RECT_VALID, ARK_RECT_EMPTY,
    };
    auto inputValueArray =
        Converter::ArkUnion<Opt_Union_Array_Rectangle_Rectangle, Array_Rectangle>(arrayHolder.ArkValue());
    modifier_->setMouseResponseRegion(node_, &inputValueArray);
    ASSERT_FALSE(gestureEventHub->GetMouseResponseRegion().empty());
    EXPECT_TRUE(gestureEventHub->GetMouseResponseRegion().front() == EXPECTED_DIM_RECT_VALID);
    EXPECT_TRUE(gestureEventHub->GetMouseResponseRegion().back() == EXPECTED_DIM_RECT_DEFAULT);
}

/*
 * @tc.name: setOnClick0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setOnClick0Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnClick0, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = GetGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    struct CheckEvent {
        int32_t resourceId;
        Ark_Int32 offsetX = -1;
        Ark_Int32 offsetY = -1;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onClick = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_ClickEvent event) {
        auto peer = event;
        ASSERT_NE(peer, nullptr);
        auto accessor = GeneratedModifier::GetClickEventAccessor();
        checkEvent = {
            .resourceId = resourceId,
            .offsetX = Converter::Convert<int32_t>(accessor->getWindowX(peer)),
            .offsetY = Converter::Convert<int32_t>(accessor->getWindowY(peer)),
        };
        accessor->destroyPeer(peer);
    };

    const int32_t contextId = 123;
    auto func = Converter::ArkValue<Callback_ClickEvent_Void>(onClick, contextId);
    auto optFunc = Converter::ArkValue<Opt_Callback_ClickEvent_Void>(func);
    modifier_->setOnClick0(node_, &optFunc);

    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameOffset({OFFSET_X, OFFSET_Y});

    gestureEventHub->ActClick();
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->offsetX, static_cast<int32_t>(OFFSET_X));
    EXPECT_EQ(checkEvent->offsetY, static_cast<int32_t>(OFFSET_Y));
}

/*
 * @tc.name: setOnClick1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setOnClick1Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnClick1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = GetGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    struct CheckEvent {
        int32_t resourceId;
        Ark_Int32 offsetX = -1;
        Ark_Int32 offsetY = -1;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto onClick = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_ClickEvent event) {
        auto peer = event;
        ASSERT_NE(peer, nullptr);
        auto accessor = GeneratedModifier::GetClickEventAccessor();
        checkEvent = {
            .resourceId = resourceId,
            .offsetX = Converter::Convert<int32_t>(accessor->getWindowX(peer)),
            .offsetY = Converter::Convert<int32_t>(accessor->getWindowY(peer)),
        };
        accessor->destroyPeer(peer);
    };

    const int32_t contextId = 123;
    auto distanceThreshold = Converter::ArkValue<Opt_Float64>(1.0);
    auto func = Converter::ArkValue<Callback_ClickEvent_Void>(onClick, contextId);
    auto optFunc = Converter::ArkValue<Opt_Callback_ClickEvent_Void>(func);
    modifier_->setOnClick1(node_, &optFunc, &distanceThreshold);

    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameOffset({OFFSET_X, OFFSET_Y});

    gestureEventHub->ActClick();
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(checkEvent->offsetX, static_cast<int32_t>(OFFSET_X));
    EXPECT_EQ(checkEvent->offsetY, static_cast<int32_t>(OFFSET_Y));
}

/*
 * @tc.name: setOnKeyPreImeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setOnKeyPreImeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnKeyPreIme, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    struct CheckEvent {
        int32_t resourceId = -1;
        KeyCode code = KeyCode::KEY_UNKNOWN;
    };
    static const int32_t expectedResId = 123;
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_KeyEvent parameter, const Callback_Boolean_Void continuation) {
        auto peer = parameter;
        ASSERT_NE(peer, nullptr);
        auto info = peer->GetEventInfo();
        auto accessor = GeneratedModifier::GetKeyEventAccessor();
        checkEvent = {
            .resourceId = resourceId,
            .code = info->GetKeyCode()
        };
        accessor->destroyPeer(peer);
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(true));
    };
    auto arkCallback = Converter::ArkValue<Callback_KeyEvent_Boolean>(nullptr, checkCallback, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_Callback_KeyEvent_Boolean>(arkCallback);
    modifier_->setOnKeyPreIme(node_, &optCallback);

    auto callOnKeyPreIme = focusHub->GetOnKeyPreIme();
    ASSERT_NE(callOnKeyPreIme, nullptr);
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_FN;
    auto eventInfo = KeyEventInfo(keyEvent);
    EXPECT_FALSE(checkEvent.has_value());
    auto result = callOnKeyPreIme(eventInfo);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, expectedResId);
    EXPECT_TRUE(result);
    EXPECT_EQ(checkEvent->code, keyEvent.code);
}


/*
 * @tc.name: setOnKeyEvent0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setOnKeyEvent0Test, TestSize.Level1)
{
#ifdef WRONG_GEN_SIG
    ASSERT_NE(modifier_->setOnKeyEvent, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    struct CheckEvent {
        int32_t resourceId = -1;
        KeyCode code = KeyCode::KEY_UNKNOWN;
    };
    static const int32_t expectedResId = 123;
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto checkCallback = [](Ark_VMContext, const Ark_Int32 resourceId, const Ark_KeyEvent event,
        Callback_Boolean_Void callback) {
        auto peer = event;
        ASSERT_NE(peer, nullptr);
        auto accessor = GeneratedModifier::GetKeyEventAccessor();
        auto info = peer->GetEventInfo();
        checkEvent = {
            .resourceId = resourceId,
            .code = info->GetKeyCode()
        };
        accessor->destroyPeer(peer);
        auto ret = CallbackHelper(callback);
        ret.InvokeSync(Converter::ArkValue<Ark_Boolean>(true));
    };

    auto arkCallback = Converter::ArkValue<Callback_KeyEvent_Boolean>(checkCallback, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_Callback_KeyEvent_Boolean>(arkCallback);
    modifier_->setOnKeyEvent(node_, &optCallback);

    auto callOnKeyEvent = focusHub->GetOnKeyCallback();
    ASSERT_NE(callOnKeyEvent, nullptr);
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_FN;
    auto eventInfo = KeyEventInfo(keyEvent);
    EXPECT_FALSE(checkEvent.has_value());
    callOnKeyEvent(eventInfo);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, expectedResId);
    EXPECT_EQ(checkEvent->code, keyEvent.code);
#endif // WRONG_GEN_SIG
}

/*
 * @tc.name: setOnKeyEvent1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setOnKeyEvent1Test, TestSize.Level1)
{
#ifdef WRONG_GEN_SIG
    ASSERT_NE(modifier_->setOnKeyEvent, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    struct CheckEvent {
        int32_t resourceId = -1;
        KeyCode code = KeyCode::KEY_UNKNOWN;
    };
    static const int32_t expectedResId = 123;
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto checkCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_KeyEvent parameter, const Callback_Boolean_Void continuation) {
        auto peer = parameter;
        ASSERT_NE(peer, nullptr);
        auto accessor = GeneratedModifier::GetKeyEventAccessor();
        auto info = peer->GetEventInfo();
        ASSERT_NE(info, nullptr);
        checkEvent = {
            .resourceId = resourceId,
            .code = info->GetKeyCode()
        };
        accessor->destroyPeer(peer);
        CallbackHelper(continuation).Invoke(Converter::ArkValue<Ark_Boolean>(true));
    };

    auto arkCallback = Converter::ArkValue<Callback_KeyEvent_Boolean>(nullptr, checkCallback, expectedResId);
    auto optCallback = Converter::ArkValue<Opt_Callback_KeyEvent_Boolean>(arkCallback);
    modifier_->setOnKeyPreIme(node_, &optCallback);

    auto callOnKeyEvent = focusHub->GetOnKeyCallback();
    ASSERT_NE(callOnKeyEvent, nullptr);
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_FN;
    auto eventInfo = KeyEventInfo(keyEvent);
    EXPECT_FALSE(checkEvent.has_value());
    auto result = callOnKeyEvent(eventInfo);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, expectedResId);
    EXPECT_TRUE(result);
    EXPECT_EQ(checkEvent->code, keyEvent.code);
#endif // WRONG_GEN_SIG
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
    Opt_PixelRoundPolicy inputVal;

    for (auto [value, expected]: testPlan) {
        auto valueOpt = Converter::ArkValue<Opt_PixelRoundCalcPolicy>(value);
        inputVal = Converter::ArkValue<Opt_PixelRoundPolicy>(
            Ark_PixelRoundPolicy { valueOpt, valueOpt, valueOpt, valueOpt });
        modifier_->setPixelRound(node_, &inputVal);
        checker(GetJsonValue(node_), expected);
    }
}

/*
 * @tc.name: setBackgroundEffectTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setBackgroundEffectTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBackgroundEffect, nullptr);

    EffectOption expectedBgEffect {
        .radius = 123.45_vp,
        .saturation = 0.123f,
        .brightness = 100,
        .color = Color(0xFF123123),
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .blurOption = {.grayscale = {20, 30}},
        .policy = BlurStyleActivePolicy::ALWAYS_ACTIVE,
        .inactiveColor = Color(0xFF00FFFF),
        .blurType = BlurType::WITHIN_WINDOW
    };

    auto renderMock = GetMockRenderContext();
    ASSERT_NE(renderMock, nullptr);

    Ark_BackgroundEffectOptions arkInputValValid = {
        .radius = ArkValue<Opt_Float64>(123.45f),
        .saturation = ArkValue<Opt_Float64>(0.123f),
        .brightness = ArkValue<Opt_Float64>(100),
        .color = ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123123),
        .adaptiveColor = ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
        .blurOptions = ArkCreate<Opt_BlurOptions>(20., 30.),
        .policy = ArkValue<Opt_BlurStyleActivePolicy>(ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE),
        .inactiveColor = ArkUnion<Opt_ResourceColor, Ark_String>("65535"),
    };
    auto inputValValid = Converter::ArkValue<Opt_BackgroundEffectOptions>(arkInputValValid);
    auto sysOptions = Converter::ArkValue<Opt_SystemAdaptiveOptions>(Ark_Empty());
    modifier_->setBackgroundEffect(node_, &inputValValid, &sysOptions);
    EXPECT_EQ(renderMock->GetOrCreateBackground()->propEffectOption, expectedBgEffect);
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

    Ark_ForegroundEffectOptions arkInputValValid = {
        .radius = ArkValue<Opt_Float64>(VALID_VAL),
    };
    auto inputValValid = Converter::ArkValue<Opt_ForegroundEffectOptions>(arkInputValValid);
    modifier_->setForegroundEffect(node_, &inputValValid);
    ASSERT_TRUE(renderMock->GetForegroundEffect().has_value());
    EXPECT_EQ(renderMock->GetForegroundEffect().value(), VALID_VAL);

    Ark_ForegroundEffectOptions arkInputValInvalid = {
        .radius = ArkValue<Opt_Float64>(INT_MIN),
    };
    auto inputValInvalid = Converter::ArkValue<Opt_ForegroundEffectOptions>(arkInputValInvalid);
    modifier_->setForegroundEffect(node_, &inputValInvalid);
    EXPECT_FALSE(renderMock->GetForegroundEffect().has_value());
}

/*
 * @tc.name: setBackgroundBlurStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setBackgroundBlurStyleTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBackgroundBlurStyle, nullptr);

    const BlurStyleOption expected {
        .blurStyle = BlurStyle::BACKGROUND_REGULAR,
        .colorMode = ThemeColorMode::DARK,
        .scale = 0.123,
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .blurOption = {.grayscale = {20, 30}},
        .policy = BlurStyleActivePolicy::ALWAYS_ACTIVE,
        .blurType = BlurType::WITHIN_WINDOW,
        .inactiveColor = Color(0xFF00FFFF),
    };

    auto inputStyleValid = Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_BACKGROUND_REGULAR);
    auto inputOptionValid = ArkValue<Opt_BackgroundBlurStyleOptions>(
        Ark_BackgroundBlurStyleOptions {
            .colorMode  = ArkValue<Opt_ThemeColorMode>(ARK_THEME_COLOR_MODE_DARK),
            .adaptiveColor = ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
            .scale = ArkValue<Opt_Float64>(0.123),
            .blurOptions = ArkCreate<Opt_BlurOptions>(20., 30.),
            .policy = ArkValue<Opt_BlurStyleActivePolicy>(ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE),
            .inactiveColor = ArkUnion<Opt_ResourceColor, Ark_String>("65535"),
        }
    );
    modifier_->setBackgroundBlurStyle(node_, &inputStyleValid, &inputOptionValid, nullptr);

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
HWTEST_F(CommonMethodModifierTest2, DISABLED_setResponseRegion, TestSize.Level1)
{
    Ark_Union_Array_Rectangle_Rectangle inputValue;
    inputValue.selector = 1;
    inputValue.value1.x = Converter::ArkValue<Opt_Length>("0.0vp");
    inputValue.value1.y = Converter::ArkValue<Opt_Length>("0.0vp");
    inputValue.value1.width = Converter::ArkValue<Opt_Length>("20.0vp");
    inputValue.value1.height = Converter::ArkValue<Opt_Length>("20.0vp");
    auto optInputValue = Converter::ArkValue<Opt_Union_Array_Rectangle_Rectangle>(inputValue);
    modifier_->setResponseRegion(node_, &optInputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_RESPONSE_REGION_NAME);
    EXPECT_EQ(strResult, "[\"{\\\"x\\\":\\\"0.00vp\\\",\\\"y\\\":\\\"0.00vp\\\","
                         "\\\"width\\\":\\\"20.00vp\\\",\\\"height\\\":\\\"20.00vp\\\"}\"]");

    inputValue.selector = 0;
    inputValue.value0.length = 2;
    inputValue.value0.array = new Ark_Rectangle[] {
        {
            Converter::ArkValue<Opt_Length>(),
            Converter::ArkValue<Opt_Length>("20.0vp"),
            Converter::ArkValue<Opt_Length>("50.0vp"),
            Converter::ArkValue<Opt_Length>(),
        },
        {
            Converter::ArkValue<Opt_Length>("-100.0vp"),
            Converter::ArkValue<Opt_Length>("-100.0vp"),
            Converter::ArkValue<Opt_Length>("200.0vp"),
            Converter::ArkValue<Opt_Length>("200.0vp"),
        }
    };
    optInputValue = Converter::ArkValue<Opt_Union_Array_Rectangle_Rectangle>(inputValue);
    modifier_->setResponseRegion(node_, &optInputValue);
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
    inputValue.minWidth = Converter::ArkValue<Opt_Length>("10.0vp");
    inputValue.maxWidth = Converter::ArkValue<Opt_Length>("370.0vp");
    inputValue.minHeight = Converter::ArkValue<Opt_Length>("10.0vp");
    inputValue.maxHeight = Converter::ArkValue<Opt_Length>("55.0vp");
    auto optInputValue = Converter::ArkValue<Opt_ConstraintSizeOptions>(inputValue);
    modifier_->setConstraintSize(node_, &optInputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_CONSTRAINT_SIZE_NAME);
    EXPECT_EQ(strResult, "{\"minWidth\":\"10.00vp\",\"minHeight\":\"10.00vp\","
                         "\"maxWidth\":\"370.00vp\",\"maxHeight\":\"55.00vp\"}");
}

/*
 * @tc.name: setLayoutWeight
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setLayoutWeight, TestSize.Level1)
{
    auto inputValue = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(1.1001f);
    modifier_->setLayoutWeight(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_WEIGHT_NAME);
    EXPECT_EQ(strResult.substr(0, 3), "1.1");

    inputValue = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("17");
    modifier_->setLayoutWeight(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_WEIGHT_NAME);
    EXPECT_EQ(strResult, "17");
}

/*
 * @tc.name: setHitTestBehavior
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setHitTestBehavior, TestSize.Level1)
{
    typedef std::pair<Opt_HitTestMode, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Opt_HitTestMode>(ARK_HIT_TEST_MODE_DEFAULT), "HitTestMode.Default" },
        { Converter::ArkValue<Opt_HitTestMode>(ARK_HIT_TEST_MODE_BLOCK), "HitTestMode.Block" },
        { Converter::ArkValue<Opt_HitTestMode>(ARK_HIT_TEST_MODE_TRANSPARENT), "HitTestMode.Transparent" },
        { Converter::ArkValue<Opt_HitTestMode>(ARK_HIT_TEST_MODE_NONE), "HitTestMode.None" },
    };

    for (const auto &[inputValue, expectedValue]: testPlan) {
        modifier_->setHitTestBehavior(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_HIT_TEST_MODE_NAME);
        EXPECT_EQ(strResult, expectedValue);
    }
}

/*
 * @tc.name: setOpacity
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setOpacity, TestSize.Level1)
{
    auto inputValue = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(0.7001);
    modifier_->setOpacity(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_OPACITY_NAME);
    EXPECT_EQ(strResult.substr(0, 3), "0.7");
}

/**
 * @tc.name: setForegroundColorTest
 * @tc.desc: Check the functionality of CommonMethodModifierTest2.setForegroundColor
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setForegroundColor, TestSize.Level1)
{
    using OneTestStep = std::pair<Opt_Union_ResourceColor_ColoringStrategy, std::string>;
    static const std::string PROP_NAME("foregroundColor");
    const auto RES_NAME = NamedResourceId{"aa.bb.cc", ResourceType::COLOR};
    const auto RES_ID = IntResourceId{11111, ResourceType::COLOR};
    static const std::string EXPECTED_RESOURCE_COLOR =
        Color::RED.ToString(); // Color::RED is result of ThemeConstants::GetColorXxxx stubs
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Opt_Union_ResourceColor_ColoringStrategy, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE)), "#FFFFFFFF" },
        { ArkUnion<Opt_Union_ResourceColor_ColoringStrategy, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456)), "#FF123456" },
        { ArkUnion<Opt_Union_ResourceColor_ColoringStrategy, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_Int32>(0.5f)), "#00000000" },
        { ArkUnion<Opt_Union_ResourceColor_ColoringStrategy, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_String>("#11223344")), "#11223344" },
        { ArkUnion<Opt_Union_ResourceColor_ColoringStrategy, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_String>("65535")), "#FF00FFFF" },
        { ArkUnion<Opt_Union_ResourceColor_ColoringStrategy, Ark_ResourceColor>(
            CreateResourceUnion<Ark_ResourceColor>(RES_NAME)), EXPECTED_RESOURCE_COLOR },
        { ArkUnion<Opt_Union_ResourceColor_ColoringStrategy, Ark_ResourceColor>(
            CreateResourceUnion<Ark_ResourceColor>(RES_ID)), EXPECTED_RESOURCE_COLOR },
        { ArkUnion<Opt_Union_ResourceColor_ColoringStrategy, Ark_ColoringStrategy>(
            Ark_ColoringStrategy::ARK_COLORING_STRATEGY_INVERT), "#00000001" },
        { ArkUnion<Opt_Union_ResourceColor_ColoringStrategy, Ark_ColoringStrategy>(
            Ark_ColoringStrategy::ARK_COLORING_STRATEGY_AVERAGE), "#00000001" },
        { ArkUnion<Opt_Union_ResourceColor_ColoringStrategy, Ark_ColoringStrategy>(
            Ark_ColoringStrategy::ARK_COLORING_STRATEGY_PRIMARY), "#00000001" },
    };

    ASSERT_NE(modifier_->setForegroundColor, nullptr);

    for (const auto &[value, expected]: testPlan) {
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
HWTEST_F(CommonMethodModifierTest2, DISABLED_setHoverEffect, TestSize.Level1)
{
    using OneTestStep = std::pair<Opt_HoverEffect, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { ArkValue<Opt_HoverEffect>(ARK_HOVER_EFFECT_NONE), "HoverEffect.None" },
        { ArkValue<Opt_HoverEffect>(ARK_HOVER_EFFECT_AUTO), "HoverEffect.Auto" },
        { ArkValue<Opt_HoverEffect>(ARK_HOVER_EFFECT_SCALE), "HoverEffect.Scale" },
        { ArkValue<Opt_HoverEffect>(ARK_HOVER_EFFECT_HIGHLIGHT), "HoverEffect.Highlight" },
    };
    std::string resultStr;
    auto renderMock = GetMockRenderContext();
    EXPECT_CALL(*renderMock, AnimateHoverEffectScale(false)).Times(AnyNumber());
    for (const auto &[value, expected]: testPlan) {
        modifier_->setHoverEffect(node_, &value);
        resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_HOVER_EFFECT_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setVisibility
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setVisibility, TestSize.Level1)
{
    using OneTestStep = std::pair<Opt_Visibility, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { ArkValue<Opt_Visibility>(ARK_VISIBILITY_VISIBLE), "Visibility.Visible" },
        { ArkValue<Opt_Visibility>(ARK_VISIBILITY_HIDDEN), "Visibility.Hidden" },
        { ArkValue<Opt_Visibility>(ARK_VISIBILITY_NONE), "Visibility.None" },
    };
    std::string resultStr;
    for (const auto &[value, expected]: testPlan) {
        modifier_->setVisibility(node_, &value);
        resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_VISIBILITY_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setFocusable
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setFocusable, TestSize.Level1)
{
    auto inputValue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setFocusable(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_FOCUSABLE_NAME);
    EXPECT_EQ(strResult, "true");

    inputValue = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setFocusable(node_, &inputValue);
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
    using OneTestStep = std::pair<Opt_ItemAlign, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { ArkValue<Opt_ItemAlign>(ARK_ITEM_ALIGN_AUTO), "ItemAlign.Auto" },
        { ArkValue<Opt_ItemAlign>(ARK_ITEM_ALIGN_START), "ItemAlign.Start" },
        { ArkValue<Opt_ItemAlign>(ARK_ITEM_ALIGN_CENTER), "ItemAlign.Center" },
        { ArkValue<Opt_ItemAlign>(ARK_ITEM_ALIGN_END), "ItemAlign.End" },
        { ArkValue<Opt_ItemAlign>(ARK_ITEM_ALIGN_BASELINE), "ItemAlign.Baseline" },
        { ArkValue<Opt_ItemAlign>(ARK_ITEM_ALIGN_STRETCH), "ItemAlign.Stretch" },
    };
    std::string resultStr;
    for (const auto &[value, expected]: testPlan) {
        modifier_->setAlignSelf(node_, &value);
        resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_ALIGN_SELF_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setDisplayPriority
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setDisplayPriority, TestSize.Level1)
{
    auto value = Converter::ArkValue<Opt_Float64>(0.7001);
    modifier_->setDisplayPriority(node_, &value);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_DISPLAY_PRIORITY_NAME);
    EXPECT_EQ(strResult, "0");

    value = Converter::ArkValue<Opt_Float64>(12);
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
    auto value = Converter::ArkValue<Opt_Int32>(0.7001);
    modifier_->setZIndex(node_, &value);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_Z_INDEX_NAME);
    EXPECT_EQ(strResult, "0");

    value = Converter::ArkValue<Opt_Int32>(13);
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
    using OneTestStep = std::pair<Opt_Direction, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { ArkValue<Opt_Direction>(ARK_DIRECTION_LTR), "Direction.Ltr" },
        { ArkValue<Opt_Direction>(ARK_DIRECTION_RTL), "Direction.Rtl" },
        { ArkValue<Opt_Direction>(ARK_DIRECTION_AUTO), "Direction.Auto" },
    };
    std::string resultStr;
    for (const auto &[value, expected]: testPlan) {
        modifier_->setDirection(node_, &value);
        resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_DIRECTION_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setAlign
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setAlign, TestSize.Level1)
{
    using OneTestStep = std::pair<Opt_Alignment, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { ArkValue<Opt_Alignment>(ARK_ALIGNMENT_TOP_START), "Alignment.TopStart" },
        { ArkValue<Opt_Alignment>(ARK_ALIGNMENT_TOP), "Alignment.Top" },
        { ArkValue<Opt_Alignment>(ARK_ALIGNMENT_TOP_END), "Alignment.TopEnd" },
        { ArkValue<Opt_Alignment>(ARK_ALIGNMENT_START), "Alignment.Start" },
        { ArkValue<Opt_Alignment>(ARK_ALIGNMENT_CENTER), "Alignment.Center" },
        { ArkValue<Opt_Alignment>(ARK_ALIGNMENT_END), "Alignment.End" },
        { ArkValue<Opt_Alignment>(ARK_ALIGNMENT_BOTTOM_START), "Alignment.BottomStart" },
        { ArkValue<Opt_Alignment>(ARK_ALIGNMENT_BOTTOM), "Alignment.Bottom" },
        { ArkValue<Opt_Alignment>(ARK_ALIGNMENT_BOTTOM_END), "Alignment.BottomEnd" },
    };
    std::string resultStr;
    for (const auto &[value, expected]: testPlan) {
        modifier_->setAlign(node_, &value);
        resultStr = GetAttrValue<std::string>(node_, ATTRIBUTE_ALIGN_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setPosition
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setPosition, TestSize.Level1)
{
    auto position = Ark_Position {
        .x = Converter::ArkUnion<Opt_Length, Ark_String>(Converter::ArkValue<Ark_String>("42.0vp")),
        .y = Converter::ArkUnion<Opt_Length, Ark_String>(Converter::ArkValue<Ark_String>("12.0px")),
    };
    auto optInputValue = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Position>(position);
    modifier_->setPosition(node_, &optInputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(strResult, "{\"x\":\"42.00vp\",\"y\":\"12.00px\"}");

    position = Ark_Position { .y = Converter::ArkValue<Opt_Length>("13.00%") };
    optInputValue = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Position>(position);
    modifier_->setPosition(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(strResult, "{\"x\":\"0.00px\",\"y\":\"13.00%\"}");

    auto edges = Ark_Edges {
        .bottom = Converter::ArkValue<Opt_Dimension>("42.0px"),
        .left = Converter::ArkValue<Opt_Dimension>("43.0vp"),
        .right = Converter::ArkValue<Opt_Dimension>("44.0fp"),
        .top = Converter::ArkValue<Opt_Dimension>("45.00%"),
    };
    optInputValue = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
    modifier_->setPosition(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(strResult, "{\"x\":\"\",\"y\":\"\"}");

    edges = Ark_Edges {
        .bottom = Converter::ArkValue<Opt_Dimension>("1.0px"),
        .top = Converter::ArkValue<Opt_Dimension>("50.00%"),
    };
    optInputValue = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
    modifier_->setPosition(node_, &optInputValue);
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
    auto inputValue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setEnabled(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLED_NAME);
    EXPECT_EQ(strResult, "true");

    inputValue = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setEnabled(node_, &inputValue);
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
    auto inputValue = Converter::ArkValue<Opt_Float64>(1);
    modifier_->setAspectRatio(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_ASPECT_RATIO_NAME);
    EXPECT_EQ(strResult, "1");

    inputValue = Converter::ArkValue<Opt_Float64>(16.0f / 9);
    modifier_->setAspectRatio(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ASPECT_RATIO_NAME);
    EXPECT_EQ(strResult.substr(0, 4), "1.78");
}

/*
 * @tc.name: setShadow
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setShadow, TestSize.Level1)
{
    auto arkShadowOptions = Ark_ShadowOptions {
        .color = Converter::ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
            Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREEN),
        .fill = Converter::ArkValue<Opt_Boolean>(true),
        .type = Converter::ArkValue<Opt_ShadowType>(Ark_ShadowType::ARK_SHADOW_TYPE_BLUR),
        .offsetX = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(6),
        .offsetY = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(10),
        .radius = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(14),
    };
    auto inputValue = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);
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
HWTEST_F(CommonMethodModifierTest2, DISABLED_setBackgroundBlurStyle, TestSize.Level1)
{
    auto style = Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN);
    auto options = Converter::ArkValue<Opt_BackgroundBlurStyleOptions>(Ark_BackgroundBlurStyleOptions {
        .scale = Converter::ArkValue<Opt_Float64>(2.2999999523162842),
        .colorMode = Converter::ArkValue<Opt_ThemeColorMode>(ARK_THEME_COLOR_MODE_DARK),
        .blurOptions = ArkCreate<Opt_BlurOptions>(7., 7.),
        .adaptiveColor = Converter::ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
    });
    modifier_->setBackgroundBlurStyle(node_, &style, &options, nullptr);
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
    auto style = Converter::ArkValue<Opt_BlurStyle>(ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN);
    auto options = Ark_ForegroundBlurStyleOptions {
        .scale = Converter::ArkValue<Opt_Float64>(2.3),
        .colorMode = Converter::ArkValue<Opt_ThemeColorMode>(ARK_THEME_COLOR_MODE_DARK),
        .blurOptions = ArkCreate<Opt_BlurOptions>(7., 7.),
        .adaptiveColor = Converter::ArkValue<Opt_AdaptiveColor>(ARK_ADAPTIVE_COLOR_AVERAGE),
    };
    auto optOptions = Converter::ArkValue<Opt_ForegroundBlurStyleOptions>(options);
    modifier_->setForegroundBlurStyle(node_, &style, &optOptions, nullptr);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_FOREGROUND_BLUR_STYLE_NAME);
    EXPECT_EQ(strResult, "");
}

/*
 * @tc.name: setBlurValid1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBlurValid1, TestSize.Level1)
{
    double blurRadiusBefore = 3.1415;
    auto value = Converter::ArkValue<Opt_Float64>(blurRadiusBefore);
    Opt_BlurOptions optionOpt = Converter::ArkValue<Opt_BlurOptions>(Ark_Empty());
    modifier_->setBlur(node_, &value, &optionOpt, nullptr);
    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, ATTRIBUTE_BLUR_NAME);
    EXPECT_NEAR(blurRadiusBefore, blurRadiusAfter, FLT_EPSILON);
    auto renderMock = GetMockRenderContext();
    ASSERT_EQ(renderMock->foregroundBlurOption.grayscale.size(), 0);
}

/*
 * @tc.name: setBlurValid2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBlurValid2, TestSize.Level1)
{
    double blurRadiusBefore = 3.1415;
    double grayCoeff1 = 7;
    double grayCoeff2 = 14;
    auto value = Converter::ArkValue<Opt_Float64>(blurRadiusBefore);
    auto optionOpt = ArkCreate<Opt_BlurOptions>(grayCoeff1, grayCoeff2);
    modifier_->setBlur(node_, &value, &optionOpt, nullptr);
    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, ATTRIBUTE_BLUR_NAME);
    EXPECT_NEAR(blurRadiusBefore, blurRadiusAfter, FLT_EPSILON);
    auto renderMock = GetMockRenderContext();
    ASSERT_EQ(renderMock->foregroundBlurOption.grayscale.size(), 2);
    EXPECT_DOUBLE_EQ(renderMock->foregroundBlurOption.grayscale[0], grayCoeff1);
    EXPECT_DOUBLE_EQ(renderMock->foregroundBlurOption.grayscale[1], grayCoeff2);
}

/*
 * @tc.name: setBlurInvalid1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBlurInvalid1, TestSize.Level1)
{
    double blurRadiusBefore = 3.1415;
    double grayCoeff1 = GRAYSCALE_MIN - 1;
    double grayCoeff2 = GRAYSCALE_MAX + 1;
    auto value = Converter::ArkValue<Opt_Float64>(blurRadiusBefore);
    auto optionOpt = ArkCreate<Opt_BlurOptions>(grayCoeff1, grayCoeff2);
    modifier_->setBlur(node_, &value, &optionOpt, nullptr);
    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, ATTRIBUTE_BLUR_NAME);
    EXPECT_NEAR(blurRadiusBefore, blurRadiusAfter, FLT_EPSILON);
    auto renderMock = GetMockRenderContext();
    ASSERT_EQ(renderMock->foregroundBlurOption.grayscale.size(), 2);
    EXPECT_DOUBLE_EQ(renderMock->foregroundBlurOption.grayscale[0], 0);
    EXPECT_DOUBLE_EQ(renderMock->foregroundBlurOption.grayscale[1], 0);
}

/*
 * @tc.name: setBlurInvalid2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBlurInvalid2, TestSize.Level1)
{
    double blurRadiusBefore = 3.1415;
    double grayCoeff1 = GRAYSCALE_MAX + 1;
    double grayCoeff2 = GRAYSCALE_MIN - 1;
    auto value = Converter::ArkValue<Opt_Float64>(blurRadiusBefore);
    auto optionOpt = ArkCreate<Opt_BlurOptions>(grayCoeff1, grayCoeff2);
    modifier_->setBlur(node_, &value, &optionOpt, nullptr);
    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, ATTRIBUTE_BLUR_NAME);
    EXPECT_NEAR(blurRadiusBefore, blurRadiusAfter, FLT_EPSILON);
    auto renderMock = GetMockRenderContext();
    ASSERT_EQ(renderMock->foregroundBlurOption.grayscale.size(), 2);
    EXPECT_DOUBLE_EQ(renderMock->foregroundBlurOption.grayscale[0], 0);
    EXPECT_DOUBLE_EQ(renderMock->foregroundBlurOption.grayscale[1], 0);
}

/*
 * @tc.name: setOverlay
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setOverlay, TestSize.Level1)
{
    auto value = Converter::ArkUnion<Opt_Union_String_CustomNodeBuilder_ComponentContent, Ark_String>("TEST_OVERLAY");
    auto options = Converter::ArkValue<Opt_OverlayOptions>(
        Ark_OverlayOptions {
            .align = Converter::ArkValue<Opt_Alignment>(ARK_ALIGNMENT_BOTTOM_END),
            .offset = Converter::ArkValue<Opt_OverlayOffset>(
                Ark_OverlayOffset {
                    .x = Converter::ArkValue<Opt_Float64>(7),
                    .y = Converter::ArkValue<Opt_Float64>(7),
                }
            ),
        }
    );
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
    Ark_BorderOptions arkInputValue = {
        .color = ArkUnion<Opt_Union_EdgeColors_ResourceColor_LocalizedEdgeColors, Ark_ResourceColor>(
            ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE)),
        .dashGap = ArkUnion<Opt_Union_EdgeWidths_LengthMetrics_LocalizedEdgeWidths, Ark_EdgeWidths>(
            Ark_EdgeWidths {
                .left = Converter::ArkValue<Opt_Length>("8.00%"),
                .top = Converter::ArkValue<Opt_Length>("9.0fp"),
                .right = Converter::ArkValue<Opt_Length>("8.0px"),
                .bottom = Converter::ArkValue<Opt_Length>("6.0vp")}),
        .dashWidth = ArkUnion<Opt_Union_EdgeWidths_LengthMetrics_LocalizedEdgeWidths, Ark_EdgeWidths>(
            Ark_EdgeWidths {
                .left = Converter::ArkValue<Opt_Length>("8.00%"),
                .top = Converter::ArkValue<Opt_Length>("4.0fp"),
                .right = Converter::ArkValue<Opt_Length>("3.0px"),
                .bottom = Converter::ArkValue<Opt_Length>("1.0vp")}),
        .radius = ArkUnion<Opt_Union_BorderRadiuses_Length_LocalizedBorderRadiuses, Ark_Length>("5.0px"),
        .style = ArkUnion<Opt_Union_EdgeStyles_BorderStyle, Ark_BorderStyle>(ARK_BORDER_STYLE_DASHED),
        .width = ArkUnion<Opt_Union_EdgeWidths_Length_LocalizedEdgeWidths, Ark_Length>("10.0px")};
    auto inputValue = Converter::ArkValue<Opt_BorderOptions>(arkInputValue);
    modifier_->setBorder(node_, &inputValue);

    auto jsonValue = GetJsonValue(node_);
    auto border = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BORDER_NAME);
    auto dashGap = GetAttrValue<std::unique_ptr<JsonValue>>(border, "dashGap");
    auto dashWidth = GetAttrValue<std::unique_ptr<JsonValue>>(border, "dashWidth");

    auto borderStyle = GetAttrValue<std::string>(border, "style");
    EXPECT_EQ(borderStyle, "BorderStyle.Dashed");
    auto borderColor = GetAttrValue<std::string>(border, "color");
    EXPECT_EQ(borderColor, "#FF0000FF");
    auto borderWidth = GetAttrValue<std::string>(border, "width");
    EXPECT_EQ(borderWidth, "10.00px");
    auto borderRadius = GetAttrValue<std::string>(border, "radius");
    EXPECT_EQ(borderRadius, "5.00px");
    auto dashGapLeft = GetAttrValue<std::string>(dashGap, "left");
    EXPECT_EQ(dashGapLeft, "0.00px");
    auto dashGapTop = GetAttrValue<std::string>(dashGap, "top");
    EXPECT_EQ(dashGapTop, "9.00fp");
    auto dashGapRight = GetAttrValue<std::string>(dashGap, "right");
    EXPECT_EQ(dashGapRight, "8.00px");
    auto dashGapBottom = GetAttrValue<std::string>(dashGap, "bottom");
    EXPECT_EQ(dashGapBottom, "6.00vp");
    auto dashWidthLeft = GetAttrValue<std::string>(dashWidth, "left");
    EXPECT_EQ(dashWidthLeft, "0.00px");
    auto dashWidthTop = GetAttrValue<std::string>(dashWidth, "top");
    EXPECT_EQ(dashWidthTop, "4.00fp");
    auto dashWidthRight = GetAttrValue<std::string>(dashWidth, "right");
    EXPECT_EQ(dashWidthRight, "3.00px");
    auto dashWidthBottom = GetAttrValue<std::string>(dashWidth, "bottom");
    EXPECT_EQ(dashWidthBottom, "1.00vp");
}

/*
 * @tc.name: setBorderStyle
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBorderStyle, TestSize.Level1)
{
    auto arkStyle = Ark_EdgeStyles {
        .left = Converter::ArkValue<Opt_BorderStyle>(ARK_BORDER_STYLE_DOTTED),
        .top = Converter::ArkValue<Opt_BorderStyle>(ARK_BORDER_STYLE_DASHED),
        .right = Converter::ArkValue<Opt_BorderStyle>(ARK_BORDER_STYLE_SOLID),
        .bottom = Converter::ArkValue<Opt_BorderStyle>(ARK_BORDER_STYLE_DOTTED),
    };
    auto style = Converter::ArkUnion<Opt_Union_BorderStyle_EdgeStyles, Ark_EdgeStyles>(arkStyle);
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
    auto arkWidth = Ark_EdgeWidths {
        .left = Converter::ArkValue<Opt_Length>("8.00%"),
        .top = Converter::ArkValue<Opt_Length>("4.0fp"),
        .right = Converter::ArkValue<Opt_Length>("3.0px"),
        .bottom = Converter::ArkValue<Opt_Length>("1.0vp"),
    };
    auto width = Converter::ArkUnion<Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths, Ark_EdgeWidths>(arkWidth);
    modifier_->setBorderWidth(node_, &width);

    auto jsonValue = GetJsonValue(node_);
    auto dashWidth = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BORDER_WIDTH_NAME);

    auto dashWidthLeft = GetAttrValue<std::string>(dashWidth, "left");
    EXPECT_EQ(dashWidthLeft, "0.00px");
    auto dashWidthTop = GetAttrValue<std::string>(dashWidth, "top");
    EXPECT_EQ(dashWidthTop, "4.00fp");
    auto dashWidthRight = GetAttrValue<std::string>(dashWidth, "right");
    EXPECT_EQ(dashWidthRight, "3.00px");
    auto dashWidthBottom = GetAttrValue<std::string>(dashWidth, "bottom");
    EXPECT_EQ(dashWidthBottom, "1.00vp");
}

/*
 * @tc.name: setBorderColor
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setBorderColor, TestSize.Level1)
{
    auto arkResourceColor = ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_ORANGE);
    auto color = Converter::ArkUnion<Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors, Ark_ResourceColor>(
        arkResourceColor);
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
    auto arkRadius =  Ark_BorderRadiuses {
        .topLeft = Converter::ArkValue<Opt_Length>("8.00%"),
        .topRight = Converter::ArkValue<Opt_Length>("7.0px"),
        .bottomRight = Converter::ArkValue<Opt_Length>("6.0vp"),
        .bottomLeft = Converter::ArkValue<Opt_Length>("5.0fp"),
    };
    auto radius = Converter::ArkUnion<Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses, Ark_BorderRadiuses>(
        arkRadius);
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
    auto arkImage = Ark_BorderImageOption {
        .fill =  Converter::ArkValue<Opt_Boolean>(true),
        .outset = Converter::ArkUnion<Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths, Ark_Length>("3.0fp"),
        .repeat = Converter::ArkValue<Opt_RepeatMode>(ARK_REPEAT_MODE_SPACE),
        .slice = Converter::ArkUnion<Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths, Ark_Length>("4.0vp"),
        .source = Converter::ArkUnion<Opt_Union_String_Resource_LinearGradientOptions, Ark_String>(
            "some_test_image.png"),
        .width = Converter::ArkUnion<Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths, Ark_Length>("1.00%"),
    };
    auto image = Converter::ArkValue<Opt_BorderImageOption>(arkImage);
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
HWTEST_F(CommonMethodModifierTest2, DISABLED_setLinearGradient, TestSize.Level1)
{
    // color stops
    std::vector<ColorStep> colorSteps {
        { ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_RED), 0.1 },
        { ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREEN), 0.5 },
        { ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_YELLOW), 0.7 },
        { ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE), 0.9 },
    };
    auto arkInputValue = Ark_LinearGradientOptions {
        .angle = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(77),
        .direction = Converter::ArkValue<Opt_GradientDirection>(ARK_GRADIENT_DIRECTION_LEFT_BOTTOM),
        .repeating = Converter::ArkValue<Opt_Boolean>(true),
        .colors = Converter::ArkValue<Array_Tuple_ResourceColor_F64>(colorSteps, Converter::FC),
    };
    auto inputValue = Converter::ArkValue<Opt_LinearGradientOptions>(arkInputValue);
    modifier_->setLinearGradient(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_LINEAR_GRADIENT_NAME);
    EXPECT_EQ(strResult, "{\"angle\":\"77.00vp\",\"direction\":\"GradientDirection.LeftBottom\","
                         "\"colors\":[[\"#FFFF0000\",\"0.100000\"],[\"#FF008000\",\"0.500000\"],"
                         "[\"#FFFFFF00\",\"0.700000\"],[\"#FF0000FF\",\"0.900000\"]],\"repeating\":\"true\"}");
}
/*
 * @tc.name: setSweepGradient
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setSweepGradient, TestSize.Level1)
{
    // color stops
    std::vector<ColorStep> colorSteps {
        { ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_RED), 0.1 },
        { ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREEN), 0.5 },
        { ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE), 0.9 },
    };
    auto arkInputValue = Ark_SweepGradientOptions {
        .center = Ark_Tuple_Length_Length { Converter::ArkValue<Ark_Length>("30.00%"),
            Converter::ArkValue<Ark_Length>("42.00%")},
        .start = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("10vp"),
        .end = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("100.0%"),
        .rotation = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("45"),
        .repeating = Converter::ArkValue<Opt_Boolean>(true),
        .colors = Converter::ArkValue<Array_Tuple_ResourceColor_F64>(colorSteps, Converter::FC),
    };
    auto inputValue = Converter::ArkValue<Opt_SweepGradientOptions>(arkInputValue);

    modifier_->setSweepGradient(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_SWEEP_GRADIENT_NAME);
    EXPECT_EQ(strResult, "{\"center\":[\"30.00%\",\"42.00%\"],\"start\":\"10.00vp\",\"end\":\"100.00%\","
                         "\"colors\":[[\"#FFFF0000\",\"0.100000\"],[\"#FF008000\",\"0.500000\"],[\"#FF0000FF\","
                         "\"0.900000\"]],\"repeating\":\"true\"}");
}

/*
 * @tc.name: backdropBlur0_setValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur0_setValues, TestSize.Level1)
{
    // see ./components_ng/render/adapter/rosen_render_context.cpp for details or possible operation
    double blurRadiusBefore = 3.1415;
    double grayCoeff1 = 2;
    double grayCoeff2 = 5;
    auto radius = Converter::ArkValue<Opt_Float64>(blurRadiusBefore);
    auto options = ArkCreate<Opt_BlurOptions>(grayCoeff1, grayCoeff2);

    modifier_->setBackdropBlur(node_, &radius, &options, nullptr);

    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);

    auto renderMock = GetMockRenderContext();
    ASSERT_EQ(renderMock->backdropBlurOption.grayscale.size(), 2);
    EXPECT_DOUBLE_EQ(renderMock->backdropBlurOption.grayscale[0], grayCoeff1);
    EXPECT_DOUBLE_EQ(renderMock->backdropBlurOption.grayscale[1], grayCoeff2);
}

/*
 * @tc.name: backdropBlur0_setNullRadiusValue
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur0_setNullRadiusValue, TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusBefore = GetAttrValue<double>(json, "backdropBlur");
    auto options = ArkCreate<Opt_BlurOptions>(2., 3.);

    modifier_->setBackdropBlur(node_, nullptr, &options, nullptr);

    json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    EXPECT_DOUBLE_EQ(blurRadiusBefore, blurRadiusAfter);
}

/*
 * @tc.name: backdropBlur0_setBadRadiusValue
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur0_setBadRadiusValue, TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusBefore = GetAttrValue<double>(json, "backdropBlur");

    auto radius = Converter::ArkValue<Opt_Float64>(0);
    auto options = ArkCreate<Opt_BlurOptions>(2., 3.);

    modifier_->setBackdropBlur(node_, &radius, &options, nullptr);

    json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    EXPECT_DOUBLE_EQ(blurRadiusBefore, blurRadiusAfter);
}

/*
 * @tc.name: backdropBlur0_setNullOption
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur0_setNullOption, TestSize.Level1)
{
    auto renderMock = GetMockRenderContext();
    double blurRadiusBefore = 3.1415;
    auto radius = Converter::ArkValue<Opt_Float64>(blurRadiusBefore);

    modifier_->setBackdropBlur(node_, &radius, nullptr, nullptr);

    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);

    ASSERT_TRUE(renderMock->backdropBlurOption.grayscale.empty());
}

/*
 * @tc.name: backdropBlur0_setValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur0_setShortOption, TestSize.Level1)
{
    auto renderMock = GetMockRenderContext();
    double blurRadiusBefore = 3.1415;
    auto radius = Converter::ArkValue<Opt_Float64>(blurRadiusBefore);
    double emptyNumberFloat = 0.0;
    double goodNumberFloat = 123.0;
    renderMock->backdropBlurOption.grayscale.clear();

    auto options = ArkCreate<Opt_BlurOptions>(emptyNumberFloat, emptyNumberFloat);
    modifier_->setBackdropBlur(node_, &radius, &options, nullptr);

    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    EXPECT_DOUBLE_EQ(blurRadiusBefore, blurRadiusAfter);

    ASSERT_FALSE(renderMock->backdropBlurOption.grayscale.empty());
    EXPECT_DOUBLE_EQ(emptyNumberFloat, renderMock->backdropBlurOption.grayscale[0]);
    EXPECT_DOUBLE_EQ(emptyNumberFloat, renderMock->backdropBlurOption.grayscale[1]);

    renderMock->backdropBlurOption.grayscale.clear();
    options = ArkCreate<Opt_BlurOptions>(goodNumberFloat, emptyNumberFloat);
    modifier_->setBackdropBlur(node_, &radius, &options, nullptr);

    json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    EXPECT_DOUBLE_EQ(blurRadiusBefore, blurRadiusAfter);

    ASSERT_FALSE(renderMock->backdropBlurOption.grayscale.empty());
    EXPECT_DOUBLE_EQ(goodNumberFloat, renderMock->backdropBlurOption.grayscale[0]);
    EXPECT_DOUBLE_EQ(emptyNumberFloat, renderMock->backdropBlurOption.grayscale[1]);

    renderMock->backdropBlurOption.grayscale.clear();
    options = ArkCreate<Opt_BlurOptions>(emptyNumberFloat, goodNumberFloat);
    modifier_->setBackdropBlur(node_, &radius, &options, nullptr);

    json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    EXPECT_DOUBLE_EQ(blurRadiusBefore, blurRadiusAfter);

    ASSERT_FALSE(renderMock->backdropBlurOption.grayscale.empty());
    EXPECT_DOUBLE_EQ(emptyNumberFloat, renderMock->backdropBlurOption.grayscale[0]);
    EXPECT_DOUBLE_EQ(goodNumberFloat, renderMock->backdropBlurOption.grayscale[1]);
}

/*
 * @tc.name: backdropBlur1_setValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur1_setValues, TestSize.Level1)
{
    // see ./components_ng/render/adapter/rosen_render_context.cpp for details or possible operation
    double blurRadiusBefore = 3.1415;
    double grayCoeff1 = 2;
    double grayCoeff2 = 5;
    auto radius = Converter::ArkValue<Opt_Float64>(blurRadiusBefore);
    auto options = ArkCreate<Opt_BlurOptions>(grayCoeff1, grayCoeff2);
    auto sysOptions = ArkValue<Opt_SystemAdaptiveOptions>(Ark_SystemAdaptiveOptions {
        .disableSystemAdaptation = ArkValue<Opt_Boolean>(false),
    });
    modifier_->setBackdropBlur(node_, &radius, &options, &sysOptions);

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
 * @tc.name: backdropBlur1_setNullRadiusValue
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur1_setNullRadiusValue, TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusBefore = GetAttrValue<double>(json, "backdropBlur");
    auto options = ArkCreate<Opt_BlurOptions>(2., 3.);
    auto sysOptions = ArkValue<Opt_SystemAdaptiveOptions>(Ark_SystemAdaptiveOptions {
        .disableSystemAdaptation = ArkValue<Opt_Boolean>(false),
    });
    modifier_->setBackdropBlur(node_, nullptr, &options, &sysOptions);

    json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);
}

/*
 * @tc.name: backdropBlur1_setBadRadiusValue
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur1_setBadRadiusValue, TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusBefore = GetAttrValue<double>(json, "backdropBlur");

    auto radius = Converter::ArkValue<Opt_Float64>(0);
    auto options = ArkCreate<Opt_BlurOptions>(2., 3.);
    auto sysOptions = ArkValue<Opt_SystemAdaptiveOptions>(Ark_SystemAdaptiveOptions {
        .disableSystemAdaptation = ArkValue<Opt_Boolean>(false),
    });
    modifier_->setBackdropBlur(node_, &radius, &options, &sysOptions);

    json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);
}

/*
 * @tc.name: backdropBlur1_setNullOption
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur1_setNullOption, TestSize.Level1)
{
    auto renderMock = GetMockRenderContext();
    double blurRadiusBefore = 3.1415;
    auto radius = Converter::ArkValue<Opt_Float64>(blurRadiusBefore);
    auto sysOptions = ArkValue<Opt_SystemAdaptiveOptions>(Ark_SystemAdaptiveOptions {
        .disableSystemAdaptation = ArkValue<Opt_Boolean>(false),
    });
    modifier_->setBackdropBlur(node_, &radius, nullptr, &sysOptions);

    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);

    ASSERT_TRUE(renderMock->backdropBlurOption.grayscale.empty());
}

/*
 * @tc.name: backdropBlur1_setShortOption
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur1_setShortOption, TestSize.Level1)
{
    auto renderMock = GetMockRenderContext();
    double blurRadiusBefore = 3.1415;
    auto radius = Converter::ArkValue<Opt_Float64>(blurRadiusBefore);
    double emptyNumberFloat = 0.0;
    double goodNumberFloat = 123.0;
    renderMock->backdropBlurOption.grayscale.clear();

    auto options = ArkCreate<Opt_BlurOptions>(emptyNumberFloat, emptyNumberFloat);
    auto sysOptions = ArkValue<Opt_SystemAdaptiveOptions>(Ark_SystemAdaptiveOptions {
        .disableSystemAdaptation = ArkValue<Opt_Boolean>(false),
    });
    modifier_->setBackdropBlur(node_, &radius, &options, &sysOptions);

    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    EXPECT_DOUBLE_EQ(blurRadiusBefore, blurRadiusAfter);

    ASSERT_FALSE(renderMock->backdropBlurOption.grayscale.empty());
    EXPECT_DOUBLE_EQ(emptyNumberFloat, renderMock->backdropBlurOption.grayscale[0]);
    EXPECT_DOUBLE_EQ(emptyNumberFloat, renderMock->backdropBlurOption.grayscale[1]);

    renderMock->backdropBlurOption.grayscale.clear();
    options = ArkCreate<Opt_BlurOptions>(goodNumberFloat, emptyNumberFloat);
    modifier_->setBackdropBlur(node_, &radius, &options, &sysOptions);

    json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    EXPECT_DOUBLE_EQ(blurRadiusBefore, blurRadiusAfter);

    ASSERT_FALSE(renderMock->backdropBlurOption.grayscale.empty());
    EXPECT_DOUBLE_EQ(goodNumberFloat, renderMock->backdropBlurOption.grayscale[0]);
    EXPECT_DOUBLE_EQ(emptyNumberFloat, renderMock->backdropBlurOption.grayscale[1]);

    renderMock->backdropBlurOption.grayscale.clear();
    options = ArkCreate<Opt_BlurOptions>(emptyNumberFloat, goodNumberFloat);
    modifier_->setBackdropBlur(node_, &radius, &options, &sysOptions);

    json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    EXPECT_DOUBLE_EQ(blurRadiusBefore, blurRadiusAfter);

    ASSERT_FALSE(renderMock->backdropBlurOption.grayscale.empty());
    EXPECT_DOUBLE_EQ(emptyNumberFloat, renderMock->backdropBlurOption.grayscale[0]);
    EXPECT_DOUBLE_EQ(goodNumberFloat, renderMock->backdropBlurOption.grayscale[1]);
}

/*
 * @tc.name: backdropBlur1_setNullSysOption
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur1_setNullSysOption, TestSize.Level1)
{
    auto renderMock = GetMockRenderContext();
    double blurRadiusBefore = 3.1415;
    auto radius = Converter::ArkValue<Opt_Float64>(blurRadiusBefore);
    auto options = ArkCreate<Opt_BlurOptions>(2., 3.);
    modifier_->setBackdropBlur(node_, &radius, &options, nullptr);

    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);

    ASSERT_TRUE(renderMock->GetSysOptions().has_value());
    EXPECT_EQ(renderMock->GetSysOptions().value().disableSystemAdaptation,
        ATTRIBUTE_SYS_OPTIONS_DISABLE_ADAPTATION_DEFAULT_VALUE);
}

/*
 * @tc.name: backdropBlur1_setSysOption
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, backdropBlur1_setSysOption, TestSize.Level1)
{
    auto renderMock = GetMockRenderContext();
    double blurRadiusBefore = 3.1415;
    auto radius = Converter::ArkValue<Opt_Float64>(blurRadiusBefore);
    auto options = ArkCreate<Opt_BlurOptions>(2., 3.);
    auto sysOptions = ArkValue<Opt_SystemAdaptiveOptions>(Ark_SystemAdaptiveOptions {
        .disableSystemAdaptation = ArkValue<Opt_Boolean>(false),
    });
    modifier_->setBackdropBlur(node_, &radius, &options, &sysOptions);

    auto json = GetJsonValue(node_);
    ASSERT_NE(json, nullptr);
    double blurRadiusAfter = GetAttrValue<double>(json, "backdropBlur");
    ASSERT_NEAR(blurRadiusBefore, blurRadiusAfter, 0.00001);

    ASSERT_TRUE(renderMock->GetSysOptions().has_value());
    EXPECT_EQ(renderMock->GetSysOptions().value().disableSystemAdaptation, false);
}

/*
 * @tc.name: ChainModeImpl_SetValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, ChainModeImpl_SetGoodValues, TestSize.Level1)
{
    auto direction = Converter::ArkValue<Opt_Axis>(Ark_Axis::ARK_AXIS_HORIZONTAL);
    auto style = Converter::ArkValue<Opt_ChainStyle>(Ark_ChainStyle::ARK_CHAIN_STYLE_SPREAD_INSIDE);
    modifier_->setChainMode(node_, &direction, &style);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_NE(layoutProperty->GetFlexItemProperty(), nullptr);

    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());
    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());

    auto storedChainMode = layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue();
    ASSERT_TRUE(storedChainMode.direction.has_value());
    EXPECT_EQ(LineDirection::HORIZONTAL, storedChainMode.direction.value());
    ASSERT_TRUE(storedChainMode.style.has_value());
    EXPECT_EQ(ChainStyle::SPREAD_INSIDE, storedChainMode.style.value());

    style = Converter::ArkValue<Opt_ChainStyle>(Ark_ChainStyle::ARK_CHAIN_STYLE_SPREAD);
    modifier_->setChainMode(node_, &direction, &style);

    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());
    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());

    storedChainMode = layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue();
    ASSERT_TRUE(storedChainMode.direction.has_value());
    EXPECT_EQ(LineDirection::HORIZONTAL, storedChainMode.direction.value());
    ASSERT_TRUE(storedChainMode.style.has_value());
    EXPECT_EQ(ChainStyle::SPREAD, storedChainMode.style.value());

    direction = Converter::ArkValue<Opt_Axis>(Ark_Axis::ARK_AXIS_VERTICAL);
    style = Converter::ArkValue<Opt_ChainStyle>(Ark_ChainStyle::ARK_CHAIN_STYLE_PACKED);
    modifier_->setChainMode(node_, &direction, &style);

    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());
    EXPECT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());

    storedChainMode = layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue();
    ASSERT_TRUE(storedChainMode.direction.has_value());
    EXPECT_EQ(LineDirection::VERTICAL, storedChainMode.direction.value());
    ASSERT_TRUE(storedChainMode.style.has_value());
    EXPECT_EQ(ChainStyle::PACKED, storedChainMode.style.value());

    storedChainMode = layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue();
    ASSERT_TRUE(storedChainMode.direction.has_value());
    EXPECT_EQ(LineDirection::HORIZONTAL, storedChainMode.direction.value());
    ASSERT_TRUE(storedChainMode.style.has_value());
    EXPECT_EQ(ChainStyle::SPREAD, storedChainMode.style.value());
}

/*
 * @tc.name: ChainModeImpl_SetBadDirectionValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, ChainModeImpl_SetBadDirectionValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_EQ(layoutProperty->GetFlexItemProperty(), nullptr);

    auto direction = Converter::ArkValue<Opt_Axis>(static_cast<Ark_Axis>(INT_MAX));
    auto style = Converter::ArkValue<Opt_ChainStyle>(Ark_ChainStyle::ARK_CHAIN_STYLE_SPREAD_INSIDE);
    modifier_->setChainMode(node_, &direction, &style);
    // empty direction optional creates both ChainStyle components but sets the style part of the VerticalChainStyle
    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue().direction.has_value());
    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue().style.has_value());
    EXPECT_EQ(ChainStyle::SPREAD_INSIDE,
        layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue().style.value());

    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().direction.has_value());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().style.has_value());
}

/*
 * @tc.name: ChainModeImpl_SetBadStyleValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, ChainModeImpl_SetBadStyleValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_EQ(layoutProperty->GetFlexItemProperty(), nullptr);

    auto direction = Converter::ArkValue<Opt_Axis>(Ark_Axis::ARK_AXIS_HORIZONTAL);
    auto style = Converter::ArkValue<Opt_ChainStyle>(static_cast<Ark_ChainStyle>(INT_MIN));
    modifier_->setChainMode(node_, &direction, &style);

    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());

    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());
    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().direction.has_value());
    EXPECT_EQ(LineDirection::HORIZONTAL,
        layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().direction.value());

    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().style.has_value());
}

/*
 * @tc.name: ChainModeImpl_SetBadBothValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, ChainModeImpl_SetBadBothValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_EQ(layoutProperty->GetFlexItemProperty(), nullptr);

    auto direction = Converter::ArkValue<Opt_Axis>(static_cast<Ark_Axis>(INT_MAX));
    auto style = Converter::ArkValue<Opt_ChainStyle>(static_cast<Ark_ChainStyle>(INT_MIN));
    modifier_->setChainMode(node_, &direction, &style);

    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue().direction.has_value());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue().style.has_value());

    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().direction.has_value());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().style.has_value());
}

static const std::vector<std::pair<Ark_Length, std::string>> LENGTH_TEST_PLAN_1 = {
    { Converter::ArkValue<Ark_Length>("22.35px"), "22.35px" },
    { Converter::ArkValue<Ark_Length>("-22.35px"), "-22.35px" },
    { Converter::ArkValue<Ark_Length>("1.65vp"), "1.65vp" },
    { Converter::ArkValue<Ark_Length>("-1.65vp"), "-1.65vp" },
    { Converter::ArkValue<Ark_Length>("65.0fp"), "65.00fp" },
    { Converter::ArkValue<Ark_Length>("-65.0fp"), "-65.00fp" },
    { Converter::ArkValue<Ark_Length>("4.3fp"), "4.30fp" },
    { Converter::ArkValue<Ark_Length>("-4.3fp"), "-4.30fp" },
    { Converter::ArkValue<Ark_Length>("12.00%"), "12.00%" },
};
/*
 * @tc.name: setMarkAnchorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setMarkAnchorTestValidValues, TestSize.Level1)
{
    Ark_Position position;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN_1) {
        position.x = Converter::ArkValue<Opt_Length>(arkLength);
        position.y = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Opt_Union_Position_LocalizedPosition, Ark_Position>(position);
        modifier_->setMarkAnchor(node_, &value);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MARK_ANCHOR_NAME);
        auto xResult = GetAttrValue<std::string>(resultStr, ATTRIBUTE_MARK_ANCHOR_X_NAME);
        EXPECT_EQ(xResult, expected);
        auto yResult = GetAttrValue<std::string>(resultStr, ATTRIBUTE_MARK_ANCHOR_Y_NAME);
        EXPECT_EQ(yResult, "0.00px");
    }
}

/*
 * @tc.name: setFocusScopeIdTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setFocusScopeIdTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_ID_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FOCUS_SCOPE_ID_NAME_DEFAULT_VALUE) <<
        "Default value for attribute 'focusScopeId.id'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_GROUP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FOCUS_IS_GROUP_DEFAULT_VALUE) <<
        "Default value for attribute 'focusScopeId.isGroup'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_ARROW_STEP_OUT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FOCUS_ARROW_STEP_OUT_DEFAULT_VALUE) <<
        "Default value for attribute 'focusScopeId.arrowStepOut'";
}

// Fixture 'String' for type 'Ark_String'
std::vector<std::tuple<std::string, Opt_String, std::string>> testFixtureStringValidValues = {
    { "\"abc\"", Converter::ArkValue<Opt_String>("abc"), "abc" },
    { "\"\"", Converter::ArkValue<Opt_String>(""), "" },
    { "\"xyz\"", Converter::ArkValue<Opt_String>("xyz"), "xyz" },
};

std::vector<std::tuple<std::string, Opt_Boolean, std::string>> testFixtureBooleanValidValues = {
    { "true", Converter::ArkValue<Opt_Boolean>(true), "true" },
    { "false", Converter::ArkValue<Opt_Boolean>(false), "false" },
};

/*
 * @tc.name: setFocusScopeIdTestFocusScopeIdValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setFocusScopeIdTestFocusScopeIdValidValues, TestSize.Level1)
{
    Opt_String initValueFocusScopeId;
    Opt_Boolean initValueIsGroup;

    // Initial setup
    initValueFocusScopeId = std::get<1>(testFixtureStringValidValues[0]);
    initValueIsGroup = ArkValue<Opt_Boolean>(std::get<1>(testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFocusScopeId, &initValueIsGroup](
                          const std::string& input, const Opt_String& value, const std::string& expectedStr) {
        Opt_String inputValueFocusScopeId = initValueFocusScopeId;
        Opt_Boolean inputValueIsGroup = initValueIsGroup;

        inputValueFocusScopeId = value;
        modifier_->setFocusScopeId(node_, &inputValueFocusScopeId, &inputValueIsGroup, nullptr);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_ID_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFocusScopeId, attribute: focusScopeId";
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetFocusType(FocusType::SCOPE);
    for (auto& [input, value, expected] : testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFocusScopeIdTestIsGroupValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setFocusScopeIdTestIsGroupValidValues, TestSize.Level1)
{
    Opt_String initValueFocusScopeId;
    Opt_Boolean initValueIsGroup;

    // Initial setup
    initValueFocusScopeId = std::get<1>(testFixtureStringValidValues[0]);
    initValueIsGroup = ArkValue<Opt_Boolean>(std::get<1>(testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFocusScopeId, &initValueIsGroup](
                          const std::string& input, const Opt_Boolean& value, const std::string& expectedStr) {
        Opt_String inputValueFocusScopeId = initValueFocusScopeId;
        Opt_Boolean inputValueIsGroup = initValueIsGroup;

        inputValueIsGroup = value;
        modifier_->setFocusScopeId(node_, &inputValueFocusScopeId, &inputValueIsGroup, nullptr);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_IS_GROUP_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFocusScopeId, attribute: isGroup";
    };
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetFocusType(FocusType::SCOPE);
    for (auto& [input, value, expected] : testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFocusScopeIdTestIsArrowStepOutValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, DISABLED_setFocusScopeIdTestIsArrowStepOutValidValues, TestSize.Level1)
{
    Opt_String initValueFocusScopeId;
    Opt_Boolean initValueIsGroup;
    Opt_Boolean initValueArrowStepOut;

    // Initial setup
    initValueFocusScopeId = std::get<1>(testFixtureStringValidValues[0]);
    initValueIsGroup = ArkValue<Opt_Boolean>(std::get<1>(testFixtureBooleanValidValues[0]));
    initValueArrowStepOut = ArkValue<Opt_Boolean>(std::get<1>(testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFocusScopeId, &initValueIsGroup, &initValueArrowStepOut](
                          const std::string& input, const Opt_Boolean& value, const std::string& expectedStr) {
        Opt_String inputValueFocusScopeId = initValueFocusScopeId;
        Opt_Boolean inputValueIsGroup = initValueIsGroup;
        Opt_Boolean inputValueArrowStepOut = initValueArrowStepOut;

        inputValueArrowStepOut = value;
        modifier_->setFocusScopeId(node_, &inputValueFocusScopeId, &inputValueIsGroup,
            &inputValueArrowStepOut);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_ARROW_STEP_OUT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFocusScopeId, attribute: arrowStepOut";
    };
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetFocusType(FocusType::SCOPE);
    for (auto& [input, value, expected] : testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFocusScopePriorityTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setFocusScopePriorityTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_PRIORITY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FOCUS_SCOPE_PRIORITY_DEFAULT_VALUE)<<"Default value for focusScopePriority";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_ID_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FOCUS_SCOPE_ID_NAME_DEFAULT_VALUE) << "Default value for attribute 'priority'";
}

std::vector<std::tuple<std::string, Ark_FocusPriority, std::string>> testFixtureEnumFocusPriorityValidValues = {
    { "ARK_FOCUS_PRIORITY_AUTO", ARK_FOCUS_PRIORITY_AUTO, "FocusPriority.AUTO" },
    { "ARK_FOCUS_PRIORITY_PRIOR", ARK_FOCUS_PRIORITY_PRIOR, "FocusPriority.PRIOR" },
    { "ARK_FOCUS_PRIORITY_PREVIOUS", ARK_FOCUS_PRIORITY_PREVIOUS, "FocusPriority.PREVIOUS" },
};

std::vector<std::tuple<std::string, Ark_FocusPriority>> testFixtureEnumFocusPriorityInvalidValues = {
    { "-1", static_cast<Ark_FocusPriority>(-1) },
    { "INT_MAX", static_cast<Ark_FocusPriority>(INT_MAX) },
};

/*
 * @tc.name: setFocusScopePriorityTestFocusScopePriorityValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setFocusScopePriorityTestFocusScopePriorityValidValues, TestSize.Level1)
{
    Opt_String initValueFocusScopeId;
    Opt_FocusPriority initValuePriority;

    // Initial setup
    initValueFocusScopeId = std::get<1>(testFixtureStringValidValues[0]);
    initValuePriority = ArkValue<Opt_FocusPriority>(std::get<1>(testFixtureEnumFocusPriorityValidValues[0]));

    auto checkValue = [this, &initValueFocusScopeId, &initValuePriority](
                          const std::string& input, const Ark_FocusPriority& value, const std::string& expectedStr) {
        Opt_String inputValueFocusScopeId = initValueFocusScopeId;
        Opt_FocusPriority inputValuePriority = initValuePriority;

        inputValuePriority = ArkValue<Opt_FocusPriority>(value);
        modifier_->setFocusScopePriority(node_, &inputValueFocusScopeId, &inputValuePriority);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_PRIORITY_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setFocusScopePriority, attribute: focusScopePriority";
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_ID_NAME);
        EXPECT_EQ(resultStr, "abc")
            << "Input value is: " << "abc" << ", method: setFocusScopePriority, attribute: focusScopeId";
    };

    for (auto& [input, value, expected] : testFixtureEnumFocusPriorityValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFocusScopePriorityTestPriorityInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest2, setFocusScopePriorityTestPriorityInvalidValues, TestSize.Level1)
{
    Opt_String initValueFocusScopePriority;
    Opt_FocusPriority initValuePriority;

    // Initial setup
    initValueFocusScopePriority = std::get<1>(testFixtureStringValidValues[0]);
    initValuePriority = ArkValue<Opt_FocusPriority>(std::get<1>(testFixtureEnumFocusPriorityValidValues[0]));

    auto checkValue = [this, &initValueFocusScopePriority, &initValuePriority](
                          const std::string& input, const Opt_FocusPriority& value) {
        Opt_String inputValueFocusScopePriority = initValueFocusScopePriority;
        Opt_FocusPriority inputValuePriority = initValuePriority;

        modifier_->setFocusScopePriority(node_, &inputValueFocusScopePriority, &inputValuePriority);
        inputValuePriority = value;
        modifier_->setFocusScopePriority(node_, &inputValueFocusScopePriority, &inputValuePriority);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUS_SCOPE_PRIORITY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FOCUS_SCOPE_PRIORITY_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setFocusScopePriority, attribute: priority";
    };

    for (auto& [input, value] : testFixtureEnumFocusPriorityInvalidValues) {
        checkValue(input, ArkValue<Opt_FocusPriority>(value));
    }
}
} // namespace OHOS::Ace::NG
