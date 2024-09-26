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
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace  {
const int32_t VALID_NUMBER = INT_MAX;
const int32_t INVALID_NUMBER = INT_MIN;
const auto OPT_VALID_NUM = ArkValue<Opt_Number>(VALID_NUMBER);
const auto OPT_INVALID_NUM = ArkValue<Opt_Number>(INVALID_NUMBER);
const auto OPT_UNDEF_NUM = ArkValue<Opt_Number>();
const auto ARK_EMPTY_STR = ArkValue<Ark_String>("");

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

class CommonMethodModifierTest : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    void SetUp() override
    {
        ModifierTestBase::SetUp();
        auto fnode = reinterpret_cast<FrameNode *>(node_);
        ASSERT_NE(fnode, nullptr);
        render_ = fnode->GetRenderContext();
        ASSERT_NE(render_, nullptr);
    }
    void TearDown()
    {
        render_ = nullptr;
    }
    std::shared_ptr<SharedTransitionOption> GetTransition()
    {
        return render_ ? render_->GetSharedTransitionOption() : nullptr;
    }
};

/**
 * @tc.name: setSwiperOptionsTest
 * @tc.desc: Check the functionality of CommonMethodModifier.setSharedTransition
 * with Id argument and nullptr Options argument
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setSharedTransitionTestId, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSharedTransition, nullptr);

    // initial
    EXPECT_EQ(render_->GetShareId(), "");
    EXPECT_EQ(GetTransition(), nullptr);

    // verify valid
    auto inputValueOptions = ArkValue<Ark_String>("abc");
    modifier_->setSharedTransition(node_, &inputValueOptions, nullptr);
    EXPECT_EQ(render_->GetShareId(), "abc");

    // verify nullptr - expect nothing changes
    modifier_->setSharedTransition(node_, nullptr, nullptr);
    EXPECT_EQ(render_->GetShareId(), "abc");

    // verify empty
    modifier_->setSharedTransition(node_, &ARK_EMPTY_STR, nullptr);
    EXPECT_EQ(render_->GetShareId(), "");

    // verify the optional property state after nullptr argument
    auto transition = GetTransition();
    ASSERT_NE(transition, nullptr);
    EXPECT_EQ(transition->duration, 0);
    EXPECT_EQ(transition->delay, 0);
}

/**
 * @tc.name: setSharedTransitionTestOptionsCurveType
 * @tc.desc: Check the functionality of CommonMethodModifier.setSharedTransition
 * with Curve Type attribute in optional argument
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setSharedTransitionTestOptionsCurveType, TestSize.Level1)
{
    const auto nameDefaultCurve = Framework::CreateCurve(ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR)->ToString();
    Opt_sharedTransitionOptions realInputValue = {.tag = ARK_TAG_OBJECT, .value = {}};
    auto& inputOptionCurveValue = realInputValue.value.curve;

    ASSERT_NE(modifier_->setSharedTransition, nullptr);

    // initial
    auto transition = GetTransition();
    EXPECT_EQ(transition, nullptr);

    // verify valid type
    inputOptionCurveValue = ArkUnion<Opt_Union_Curve_String_ICurve, Ark_Curve>(ARK_CURVE_EASE_IN);
    modifier_->setSharedTransition(node_, &ARK_EMPTY_STR, &realInputValue);
    transition = GetTransition();
    ASSERT_TRUE(transition && transition->curve);
    auto nameCurveEasyIn = Framework::CreateCurve(ArkUI_AnimationCurve::ARKUI_CURVE_EASE_IN)->ToString();
    EXPECT_EQ(transition->curve->ToString(), nameCurveEasyIn);

    // verify invalid type - expect default
    inputOptionCurveValue = ArkUnion<Opt_Union_Curve_String_ICurve, Ark_Curve>(
        static_cast<Ark_Curve>(INT_MIN));
    modifier_->setSharedTransition(node_, &ARK_EMPTY_STR, &realInputValue);
    transition = GetTransition();
    ASSERT_TRUE(transition && transition->curve);
    EXPECT_EQ(transition->curve->ToString(), nameDefaultCurve);
}

/**
 * @tc.name: setSharedTransitionTestOptionsCurveCustom
 * @tc.desc: Check the functionality of CommonMethodModifier.setSharedTransition
 * with Curve Custom attribute in optional argument
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setSharedTransitionTestOptionsCurveCustom, TestSize.Level1)
{
    const auto nameDefaultCurve = Framework::CreateCurve(ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR)->ToString();
    Opt_sharedTransitionOptions realInputValue = {.tag = ARK_TAG_OBJECT, .value = {}};
    auto& inputOptionCurveValue = realInputValue.value.curve;

    ASSERT_NE(modifier_->setSharedTransition, nullptr);

    // initial
    auto transition = GetTransition();
    EXPECT_EQ(transition, nullptr);

    // verify valid custom
    inputOptionCurveValue =
        ArkUnion<Opt_Union_Curve_String_ICurve, Ark_String>("interpolating-spring(1, 1, 28, 34)");
    modifier_->setSharedTransition(node_, &ARK_EMPTY_STR, &realInputValue);
    transition = GetTransition();
    ASSERT_TRUE(transition && transition->curve);
    // this can't be exactly check due to SwiperPaintProperty::ToJsonValue supports the built-in Curves only
    EXPECT_NE(transition->curve->ToString(), nameDefaultCurve);

    // verify invalid custom - expect default
    inputOptionCurveValue =
        ArkUnion<Opt_Union_Curve_String_ICurve, Ark_String>("invalidCurveDefinition");
    modifier_->setSharedTransition(node_, &ARK_EMPTY_STR, &realInputValue);
    transition = GetTransition();
    ASSERT_TRUE(transition && transition->curve);
    EXPECT_EQ(transition->curve->ToString(), nameDefaultCurve);
}

/**
 * @tc.name: setSharedTransitionTestOptionsCurveUndef
 * @tc.desc: Check the functionality of CommonMethodModifier.setSharedTransition
 * with undefined Curve attribute in optional argument
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setSharedTransitionTestOptionsCurveUndef, TestSize.Level1)
{
    const auto nameDefaultCurve = Framework::CreateCurve(ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR)->ToString();
    Opt_sharedTransitionOptions realInputValue = {.tag = ARK_TAG_OBJECT, .value = {}};
    auto& inputOptionCurveValue = realInputValue.value.curve;

    ASSERT_NE(modifier_->setSharedTransition, nullptr);

    // initial
    EXPECT_EQ(GetTransition(), nullptr);

    // verify undef Curve - expect default
    inputOptionCurveValue = ArkUnion<Opt_Union_Curve_String_ICurve>(Ark_Empty());
    modifier_->setSharedTransition(node_, &ARK_EMPTY_STR, &realInputValue);
    auto transition = GetTransition();
    ASSERT_TRUE(transition && transition->curve);
    EXPECT_EQ(transition->curve->ToString(), nameDefaultCurve);
}

/**
 * @tc.name: DISABLED_setSharedTransitionTestOptionsCurveICurve
 * @tc.desc: Check the functionality of CommonMethodModifier.setSharedTransition
 * with Curve external callback attribute in optional argument
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setSharedTransitionTestOptionsCurveICurve, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSharedTransition, nullptr);
    // support of the external callbacks not implemented
}


/**
 * @tc.name: setSharedTransitionTestOptionsPath
 * @tc.desc: Check the functionality of CommonMethodModifier.setSharedTransition
 * with MovingPath attribute in optional argument
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setSharedTransitionTestOptionsPath, TestSize.Level1)
{
    Opt_sharedTransitionOptions realInputValue = {.tag = ARK_TAG_OBJECT, .value = {}};
    realInputValue.value.motionPath = {.tag = ARK_TAG_OBJECT, .value = {}};
    auto& inputMotionPathValue = realInputValue.value.motionPath.value;

    ASSERT_NE(modifier_->setSharedTransition, nullptr);

    // initial
    EXPECT_EQ(GetTransition(), nullptr);

    // verify valid
    inputMotionPathValue = {
        .path = ArkValue<Ark_String>("abc"),
        .from = ArkValue<Opt_Number>(123),
        .to = ArkValue<Opt_Number>(-987.654f),
        .rotatable = ArkValue<Opt_Boolean>(true),
    };
    modifier_->setSharedTransition(node_, &ARK_EMPTY_STR, &realInputValue);
    auto transition = GetTransition();
    ASSERT_TRUE(transition);
    EXPECT_EQ(transition->motionPathOption.GetPath(), "abc");
    EXPECT_FLOAT_EQ(transition->motionPathOption.GetBegin(), 123.0f);
    EXPECT_FLOAT_EQ(transition->motionPathOption.GetEnd(), -987.654f);
    EXPECT_EQ(transition->motionPathOption.GetRotate(), true);

    // verify empty/undefined
    inputMotionPathValue = {
        .path = ARK_EMPTY_STR,
        .from = ArkValue<Opt_Number>(),
        .to = ArkValue<Opt_Number>(),
        .rotatable = ArkValue<Opt_Boolean>(),
    };
    modifier_->setSharedTransition(node_, &ARK_EMPTY_STR, &realInputValue);
    transition = GetTransition();
    ASSERT_TRUE(transition);
    EXPECT_EQ(transition->motionPathOption.GetPath(), "");
    EXPECT_FLOAT_EQ(transition->motionPathOption.GetBegin(), 0.0f);
    EXPECT_FLOAT_EQ(transition->motionPathOption.GetEnd(), 1.0f);
    EXPECT_EQ(transition->motionPathOption.GetRotate(), false);
}

/**
 * @tc.name: setSharedTransitionTestOptionsOtherArgs
 * @tc.desc: Check the functionality of CommonMethodModifier.setSharedTransition
 * with number attributes for optional argument
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setSharedTransitionTestOptionsOtherArgs, TestSize.Level1)
{
    Opt_sharedTransitionOptions realInputValue = {.tag = ARK_TAG_OBJECT, .value = {}};
    Ark_sharedTransitionOptions& inputValueOptions = realInputValue.value;

    ASSERT_NE(modifier_->setSharedTransition, nullptr);

    // initial
    auto transition = GetTransition();
    EXPECT_EQ(transition, nullptr);

    // verify valid values
    inputValueOptions.delay = OPT_VALID_NUM;
    inputValueOptions.duration = OPT_VALID_NUM;
    inputValueOptions.zIndex = OPT_VALID_NUM;
    inputValueOptions.type =
        ArkValue<Opt_SharedTransitionEffectType>(ARK_SHARED_TRANSITION_EFFECT_TYPE_STATIC);
    modifier_->setSharedTransition(node_, &ARK_EMPTY_STR, &realInputValue);
    transition = GetTransition();
    ASSERT_NE(transition, nullptr);
    EXPECT_EQ(transition->duration, VALID_NUMBER);
    EXPECT_EQ(transition->delay, VALID_NUMBER);
    EXPECT_EQ(transition->zIndex, VALID_NUMBER);
    EXPECT_EQ(transition->type, SharedTransitionEffectType::SHARED_EFFECT_STATIC);

    // verify undefined values - expect default
    inputValueOptions.delay = OPT_UNDEF_NUM;
    inputValueOptions.duration = OPT_UNDEF_NUM;
    inputValueOptions.zIndex = OPT_UNDEF_NUM;
    inputValueOptions.type = ArkValue<Opt_SharedTransitionEffectType>(Ark_Empty());
    modifier_->setSharedTransition(node_, &ARK_EMPTY_STR, &realInputValue);
    transition = GetTransition();
    ASSERT_NE(transition, nullptr);
    EXPECT_EQ(transition->duration, CommonAnimationStyle::DEFAULT_ANIMATION_DURATION);
    EXPECT_EQ(transition->delay, 0);
    EXPECT_EQ(transition->zIndex, 0);
    EXPECT_EQ(transition->type, SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE);

    // verify invalid values - expect default
    inputValueOptions.delay = OPT_INVALID_NUM;
    inputValueOptions.duration = OPT_INVALID_NUM;
    inputValueOptions.zIndex = OPT_INVALID_NUM;
    inputValueOptions.type =
        ArkValue<Opt_SharedTransitionEffectType>(static_cast<SharedTransitionEffectType>(INT_MIN));
    modifier_->setSharedTransition(node_, &ARK_EMPTY_STR, &realInputValue);
    transition = GetTransition();
    ASSERT_NE(transition, nullptr);
    EXPECT_EQ(transition->duration, CommonAnimationStyle::DEFAULT_ANIMATION_DURATION);
    EXPECT_EQ(transition->delay, 0);
    EXPECT_EQ(transition->zIndex, 0);
    EXPECT_EQ(transition->type, SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE);
}

/**
 * @tc.name: setBackgroundColorTest
 * @tc.desc: Check the functionality of CommonMethodModifierTest.setBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setBackgroundColorTest, TestSize.Level1)
{
    using OneTestStep = std::pair<Ark_ResourceColor, std::string>;
    static const std::string PROP_NAME("backgroundColor");
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

    ASSERT_NE(modifier_->setBackgroundColor, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, Color::TRANSPARENT.ToString());

    for (const auto &[arkResColor, expected]: testPlan) {
        modifier_->setBackgroundColor(node_, &arkResColor);
        auto checkColor = GetAttrValue<std::string>(node_, PROP_NAME);
        EXPECT_EQ(checkColor, expected);
    }
}

} // namespace OHOS::Ace::NG