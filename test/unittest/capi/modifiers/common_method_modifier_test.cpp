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

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace  {
const int32_t VALID_NUMBER = INT_MAX;
const int32_t INVALID_NUMBER = INT_MIN;
const Ark_Int32 FAKE_RES_ID(1234);
const auto OPT_VALID_NUM = ArkValue<Opt_Number>(VALID_NUMBER);
const auto OPT_INVALID_NUM = ArkValue<Opt_Number>(INVALID_NUMBER);
const auto OPT_UNDEF_NUM = ArkValue<Opt_Number>();
const auto ARK_EMPTY_STR = ArkValue<Ark_String>("");
const Ark_Length RES_ARK_LENGTH = { .type = ARK_TAG_RESOURCE, .resource = FAKE_RES_ID };

const auto ATTRIBUTE_WIDTH_NAME = "width";
const auto ATTRIBUTE_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_HEIGHT_NAME = "height";
const auto ATTRIBUTE_HEIGHT_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_MARGIN_NAME = "margin";
const auto ATTRIBUTE_MARGIN_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_PADDING_NAME = "padding";
const auto ATTRIBUTE_PADDING_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_LEFT_NAME = "left";
const auto ATTRIBUTE_TOP_NAME = "top";
const auto ATTRIBUTE_RIGHT_NAME = "right";
const auto ATTRIBUTE_BOTTOM_NAME = "bottom";
const auto ATTRIBUTE_OFFSET_NAME = "offset";
const auto ATTRIBUTE_OFFSET_X_NAME = "x";
const auto ATTRIBUTE_OFFSET_X_DEFAULT_VALUE = "";
const auto ATTRIBUTE_OFFSET_Y_NAME = "y";
const auto ATTRIBUTE_OFFSET_Y_DEFAULT_VALUE = "";
const auto ATTRIBUTE_OFFSET_LEFT_NAME = "left";
const auto ATTRIBUTE_OFFSET_TOP_NAME = "top";
const auto ATTRIBUTE_OFFSET_RIGHT_NAME = "right";
const auto ATTRIBUTE_OFFSET_BOTTOM_NAME = "bottom";
const auto ATTRIBUTE_RADIAL_GRADIENT_NAME = "radialGradient";
const auto ATTRIBUTE_RADIAL_GRADIENT_DEFAULT_VALUE = "{}";
const auto ATTRIBUTE_CENTER_NAME = "center";
const auto ATTRIBUTE_RADIUS_NAME = "radius";
const auto ATTRIBUTE_COLORS_NAME = "colors";
const auto ATTRIBUTE_REPEATING_NAME = "repeating";

typedef std::pair<Ark_Length, std::string> MarginPaddingOneTestStep;
static const std::vector<MarginPaddingOneTestStep> LENGTH_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(1), "1.00px" },
    { Converter::ArkValue<Ark_Length>(-1), "-1.00px" },
    { Converter::ArkValue<Ark_Length>(0), "0.00px" },
    { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
    { Converter::ArkValue<Ark_Length>(-2.45f), "-2.45vp" },
    { Converter::ArkValue<Ark_Length>(5.0_px), "5.00px" },
    { Converter::ArkValue<Ark_Length>(-5.0_px), "-5.00px" },
    { Converter::ArkValue<Ark_Length>(22.35_px), "22.35px" },
    { Converter::ArkValue<Ark_Length>(-22.35_px), "-22.35px" },
    { Converter::ArkValue<Ark_Length>(7.0_vp), "7.00vp" },
    { Converter::ArkValue<Ark_Length>(-7.0_vp), "-7.00vp" },
    { Converter::ArkValue<Ark_Length>(1.65_vp), "1.65vp" },
    { Converter::ArkValue<Ark_Length>(-1.65_vp), "-1.65vp" },
    { Converter::ArkValue<Ark_Length>(65.0_fp), "65.00fp" },
    { Converter::ArkValue<Ark_Length>(-65.0_fp), "-65.00fp" },
    { Converter::ArkValue<Ark_Length>(4.3_fp), "4.30fp" },
    { Converter::ArkValue<Ark_Length>(-4.3_fp), "-4.30fp" },
    { Converter::ArkValue<Ark_Length>(0.12_pct), "12.00%" },
    { RES_ARK_LENGTH, "10.00px" },
};

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
        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
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

/*
 * @tc.name: setWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setWidthTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
}

/*
 * @tc.name: setWidthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setWidthTestValidValues, TestSize.Level1)
{
    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), "1.00px" },
        { Converter::ArkValue<Ark_Length>(0), "0.00px" },
        { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Ark_Length>(5.0_px), "5.00px" },
        { Converter::ArkValue<Ark_Length>(22.35_px), "22.35px" },
        { Converter::ArkValue<Ark_Length>(7.0_vp), "7.00vp" },
        { Converter::ArkValue<Ark_Length>(1.65_vp), "1.65vp" },
        { Converter::ArkValue<Ark_Length>(65.0_fp), "65.00fp" },
        { Converter::ArkValue<Ark_Length>(4.3_fp), "4.30fp" },
        { Converter::ArkValue<Ark_Length>(0.12_pct), "12.00%" },
        { RES_ARK_LENGTH, "10.00px" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        Ark_Length inputValue = Converter::ArkValue<Ark_Length>(arkLength);
        modifier_->setWidth(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setWidthTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setWidthTestInvalidValues, TestSize.Level1)
{
    static const std::vector<Ark_Length> testPlan = {
        Converter::ArkValue<Ark_Length>(-1),
        Converter::ArkValue<Ark_Length>(-2.45f),
        Converter::ArkValue<Ark_Length>(-5.0_px),
        Converter::ArkValue<Ark_Length>(-22.35_px),
        Converter::ArkValue<Ark_Length>(-7.0_vp),
        Converter::ArkValue<Ark_Length>(-1.65_vp),
        Converter::ArkValue<Ark_Length>(-65.0_fp),
        Converter::ArkValue<Ark_Length>(-4.3_fp),
    };

    for (const auto arkLength : testPlan) {
        Ark_Length inputValue = Converter::ArkValue<Ark_Length>(arkLength);
        modifier_->setWidth(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
    }

    modifier_->setWidth(node_, nullptr);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
}

/*
 * @tc.name: setHeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setHeightTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
}

/*
 * @tc.name: setHeightTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setHeightTestValidValues, TestSize.Level1)
{
    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), "1.00px" },
        { Converter::ArkValue<Ark_Length>(0), "0.00px" },
        { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Ark_Length>(5.0_px), "5.00px" },
        { Converter::ArkValue<Ark_Length>(22.35_px), "22.35px" },
        { Converter::ArkValue<Ark_Length>(7.0_vp), "7.00vp" },
        { Converter::ArkValue<Ark_Length>(1.65_vp), "1.65vp" },
        { Converter::ArkValue<Ark_Length>(65.0_fp), "65.00fp" },
        { Converter::ArkValue<Ark_Length>(4.3_fp), "4.30fp" },
        { Converter::ArkValue<Ark_Length>(0.12_pct), "12.00%" },
        { RES_ARK_LENGTH, "10.00px" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        Ark_Length inputValue = Converter::ArkValue<Ark_Length>(arkLength);
        modifier_->setHeight(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setHeightTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setHeightTestInvalidValues, TestSize.Level1)
{
    static const std::vector<Ark_Length> testPlan = {
        Converter::ArkValue<Ark_Length>(-1),
        Converter::ArkValue<Ark_Length>(-2.45f),
        Converter::ArkValue<Ark_Length>(-5.0_px),
        Converter::ArkValue<Ark_Length>(-22.35_px),
        Converter::ArkValue<Ark_Length>(-7.0_vp),
        Converter::ArkValue<Ark_Length>(-1.65_vp),
        Converter::ArkValue<Ark_Length>(-65.0_fp),
        Converter::ArkValue<Ark_Length>(-4.3_fp),
    };

    for (const auto &arkLength : testPlan) {
        Ark_Length inputValue = Converter::ArkValue<Ark_Length>(arkLength);
        modifier_->setHeight(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
    }

    modifier_->setHeight(node_, nullptr);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
}

/*
 * @tc.name: setSizeTestValidHeightValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setSizeTestValidHeightValues, TestSize.Level1)
{
    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), "1.00px" },
        { Converter::ArkValue<Ark_Length>(0), "0.00px" },
        { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Ark_Length>(5.0_px), "5.00px" },
        { Converter::ArkValue<Ark_Length>(22.35_px), "22.35px" },
        { Converter::ArkValue<Ark_Length>(7.0_vp), "7.00vp" },
        { Converter::ArkValue<Ark_Length>(1.65_vp), "1.65vp" },
        { Converter::ArkValue<Ark_Length>(65.0_fp), "65.00fp" },
        { Converter::ArkValue<Ark_Length>(4.3_fp), "4.30fp" },
        { Converter::ArkValue<Ark_Length>(0.12_pct), "12.00%" },
        { RES_ARK_LENGTH, "10.00px" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        Ark_SizeOptions inputValue;
        inputValue.height = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        inputValue.width = Converter::ArkValue<Opt_Length>(Ark_Empty());
        modifier_->setSize(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, expected);
        strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setSizeTestValidWidthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setSizeTestValidWidthValues, TestSize.Level1)
{
    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), "1.00px" },
        { Converter::ArkValue<Ark_Length>(0), "0.00px" },
        { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Ark_Length>(5.0_px), "5.00px" },
        { Converter::ArkValue<Ark_Length>(22.35_px), "22.35px" },
        { Converter::ArkValue<Ark_Length>(7.0_vp), "7.00vp" },
        { Converter::ArkValue<Ark_Length>(1.65_vp), "1.65vp" },
        { Converter::ArkValue<Ark_Length>(65.0_fp), "65.00fp" },
        { Converter::ArkValue<Ark_Length>(4.3_fp), "4.30fp" },
        { Converter::ArkValue<Ark_Length>(0.12_pct), "12.00%" },
        { RES_ARK_LENGTH, "10.00px" },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        Ark_SizeOptions inputValue;
        inputValue.width = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        inputValue.height = Converter::ArkValue<Opt_Length>(Ark_Empty());
        modifier_->setSize(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, expected);
        strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setSizeTestInvalidValues, TestSize.Level1)
{
    Ark_SizeOptions inputValue;

    static const std::vector<Ark_Length> testPlan = {
        Converter::ArkValue<Ark_Length>(-1),
        Converter::ArkValue<Ark_Length>(-2.45f),
        Converter::ArkValue<Ark_Length>(-5.0_px),
        Converter::ArkValue<Ark_Length>(-22.35_px),
        Converter::ArkValue<Ark_Length>(-7.0_vp),
        Converter::ArkValue<Ark_Length>(-1.65_vp),
        Converter::ArkValue<Ark_Length>(-65.0_fp),
        Converter::ArkValue<Ark_Length>(-4.3_fp),
    };

    for (const auto &arkLength : testPlan) {
        inputValue.width = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        inputValue.height = Converter::ArkValue<Opt_Length>(Ark_Empty());
        modifier_->setSize(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
        strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
    }

    for (const auto &arkLength : testPlan) {
        inputValue.height = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        inputValue.width = Converter::ArkValue<Opt_Length>(Ark_Empty());
        modifier_->setSize(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
        strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
    }

    modifier_->setSize(node_, nullptr);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
    strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
}

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

/*
 * @tc.name: setMarginTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setMarginTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_MARGIN_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
}

/*
 * @tc.name: setMarginTestValidLengthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setMarginTestValidLengthValues, TestSize.Level1)
{
    std::string strResult;
    for (const auto &[arkMargin, expected]: LENGTH_TEST_PLAN) {
        auto value = Converter::ArkUnion<Type_CommonMethod_margin_Arg0, Ark_Length>(arkMargin);
        modifier_->setMargin(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_MARGIN_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setMarginTestValidLeftLengthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setMarginTestValidLeftLengthValues, TestSize.Level1)
{
    Ark_Padding inputValue;
    for (const auto &[arkMargin, expected]: LENGTH_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkMargin));
        inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Type_CommonMethod_margin_Arg0, Ark_Padding>(inputValue);
        modifier_->setMargin(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_MARGIN_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME);
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME);
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME);
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME);
        EXPECT_EQ(leftResult, expected);
        EXPECT_EQ(topResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(rightResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(bottomResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setMarginTestValidTopLengthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setMarginTestValidTopLengthValues, TestSize.Level1)
{
    Ark_Padding inputValue;
    for (const auto &[arkMargin, expected]: LENGTH_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.top = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkMargin));
        inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Type_CommonMethod_margin_Arg0, Ark_Padding>(inputValue);
        modifier_->setMargin(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_MARGIN_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME);
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME);
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME);
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME);
        EXPECT_EQ(leftResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(topResult, expected);
        EXPECT_EQ(rightResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(bottomResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setMarginTestValidRightLengthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setMarginTestValidTopRightValues, TestSize.Level1)
{
    Ark_Padding inputValue;
    for (const auto &[arkMargin, expected]: LENGTH_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.right = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkMargin));
        inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Type_CommonMethod_margin_Arg0, Ark_Padding>(inputValue);
        modifier_->setMargin(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_MARGIN_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME);
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME);
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME);
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME);
        EXPECT_EQ(leftResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(topResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(rightResult, expected);
        EXPECT_EQ(bottomResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setMarginTestValidBottomLengthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setMarginTestValidBottomLengthValues, TestSize.Level1)
{
    Ark_Padding inputValue;
    for (const auto &[arkMargin, expected]: LENGTH_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.bottom = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkMargin));
        auto value = Converter::ArkUnion<Type_CommonMethod_margin_Arg0, Ark_Padding>(inputValue);
        modifier_->setMargin(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_MARGIN_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME);
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME);
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME);
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME);
        EXPECT_EQ(leftResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(topResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(rightResult, ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(bottomResult, expected);
    }
}

/*
 * @tc.name: DISABLED_setMarginTestValidLocalizedMarginValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setMarginTestValidLocalizedMarginValues, TestSize.Level1)
{
    // test is not implemented because LocalizedMargin type is not supported yet
}

/*
 * @tc.name: setPaddingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setPaddingTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_PADDING_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
}

/*
 * @tc.name: setPaddingTestValidLengthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setPaddingTestValidLengthValues, TestSize.Level1)
{
    std::string strResult;
    for (const auto &[arkPadding, expected]: LENGTH_TEST_PLAN) {
        auto value = Converter::ArkUnion<Type_CommonMethod_padding_Arg0, Ark_Length>(arkPadding);
        modifier_->setPadding(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_PADDING_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setPaddingTestValidLeftLengthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setPaddingTestValidLeftLengthValues, TestSize.Level1)
{
    Ark_Padding inputValue;
    for (const auto &[arkPadding, expected]: LENGTH_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkPadding));
        inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Type_CommonMethod_padding_Arg0, Ark_Padding>(inputValue);
        modifier_->setPadding(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_PADDING_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME);
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME);
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME);
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME);
        EXPECT_EQ(leftResult, expected);
        EXPECT_EQ(topResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(rightResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(bottomResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setPaddingTestValidTopLengthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setPaddingTestValidTopLengthValues, TestSize.Level1)
{
    Ark_Padding inputValue;
    for (const auto &[arkPadding, expected]: LENGTH_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.top = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkPadding));
        inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Type_CommonMethod_padding_Arg0, Ark_Padding>(inputValue);
        modifier_->setPadding(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_PADDING_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME);
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME);
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME);
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME);
        EXPECT_EQ(leftResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(topResult, expected);
        EXPECT_EQ(rightResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(bottomResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setPaddingTestValidRightLengthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setPaddingTestValidTopRightValues, TestSize.Level1)
{
    Ark_Padding inputValue;
    for (const auto &[arkPadding, expected]: LENGTH_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.right = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkPadding));
        inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Type_CommonMethod_padding_Arg0, Ark_Padding>(inputValue);
        modifier_->setPadding(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_PADDING_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME);
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME);
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME);
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME);
        EXPECT_EQ(leftResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(topResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(rightResult, expected);
        EXPECT_EQ(bottomResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setPaddingTestValidBottomLengthValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setPaddingTestValidBottomLengthValues, TestSize.Level1)
{
    Ark_Padding inputValue;
    for (const auto &[arkPadding, expected]: LENGTH_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.bottom = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkPadding));
        auto value = Converter::ArkUnion<Type_CommonMethod_padding_Arg0, Ark_Padding>(inputValue);
        modifier_->setPadding(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_PADDING_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME);
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME);
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME);
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME);
        EXPECT_EQ(leftResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(topResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(rightResult, ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(bottomResult, expected);
    }
}

/*
 * @tc.name: DISABLED_setPaddingTestValidLocalizedPaddingValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setPaddingTestValidLocalizedPaddingValues, TestSize.Level1)
{
    // test is not implemented because LocalizedPadding type is not supported yet
}

/*
 * @tc.name: setOffsetTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setOffsetTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
    auto xResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_X_NAME);
    EXPECT_EQ(xResult, ATTRIBUTE_OFFSET_X_DEFAULT_VALUE);
    auto yResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_Y_NAME);
    EXPECT_EQ(yResult, ATTRIBUTE_OFFSET_Y_DEFAULT_VALUE);
}

/*
 * @tc.name: setOffsetTestValidPositionXValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setOffsetTestValidPositionXValues, TestSize.Level1)
{
    Ark_Position position;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        position.x = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        position.y = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Type_CommonMethod_offset_Arg0, Ark_Position>(position);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto xResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_X_NAME);
        EXPECT_EQ(xResult, expected);
        auto yResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_Y_NAME);
        EXPECT_EQ(yResult, "0.00px");
    }
}

/*
 * @tc.name: setOffsetTestValidPositionYValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setOffsetTestValidPositionYValues, TestSize.Level1)
{
    Ark_Position position;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        position.x = Converter::ArkValue<Opt_Length>(Ark_Empty());
        position.y = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        auto value = Converter::ArkUnion<Type_CommonMethod_offset_Arg0, Ark_Position>(position);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto xResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_X_NAME);
        EXPECT_EQ(xResult, "0.00px");
        auto yResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_Y_NAME);
        EXPECT_EQ(yResult, expected);
    }
}

/*
 * @tc.name: setOffsetTestValidEdgesLeftValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setOffsetTestValidEdgesLeftValues, TestSize.Level1)
{
    Ark_Edges edges;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        edges.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Type_CommonMethod_offset_Arg0, Ark_Edges>(edges);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_LEFT_NAME);
        EXPECT_EQ(leftResult, expected);
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_TOP_NAME);
        EXPECT_EQ(topResult, "");
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_RIGHT_NAME);
        EXPECT_EQ(rightResult, "");
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_BOTTOM_NAME);
        EXPECT_EQ(bottomResult, "");
    }
}

/*
 * @tc.name: setOffsetTestValidEdgesTopValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setOffsetTestValidEdgesTopValues, TestSize.Level1)
{
    Ark_Edges edges;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.top = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        edges.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Type_CommonMethod_offset_Arg0, Ark_Edges>(edges);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_LEFT_NAME);
        EXPECT_EQ(leftResult, "");
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_TOP_NAME);
        EXPECT_EQ(topResult, expected);
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_RIGHT_NAME);
        EXPECT_EQ(rightResult, "");
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_BOTTOM_NAME);
        EXPECT_EQ(bottomResult, "");
    }
}

/*
 * @tc.name: setOffsetTestValidEdgesRightValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setOffsetTestValidEdgesRightValues, TestSize.Level1)
{
    Ark_Edges edges;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.right = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        edges.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Type_CommonMethod_offset_Arg0, Ark_Edges>(edges);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_LEFT_NAME);
        EXPECT_EQ(leftResult, "");
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_TOP_NAME);
        EXPECT_EQ(topResult, "");
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_RIGHT_NAME);
        EXPECT_EQ(rightResult, expected);
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_BOTTOM_NAME);
        EXPECT_EQ(bottomResult, "");
    }
}

/*
 * @tc.name: setOffsetTestValidEdgesBottomValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setOffsetTestValidEdgesBottomValues, TestSize.Level1)
{
    Ark_Edges edges;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.bottom = Converter::ArkValue<Opt_Length>(std::optional(arkLength));
        auto value = Converter::ArkUnion<Type_CommonMethod_offset_Arg0, Ark_Edges>(edges);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_LEFT_NAME);
        EXPECT_EQ(leftResult, "");
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_TOP_NAME);
        EXPECT_EQ(topResult, "");
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_RIGHT_NAME);
        EXPECT_EQ(rightResult, "");
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_BOTTOM_NAME);
        EXPECT_EQ(bottomResult, expected);
    }
}

/*
 * @tc.name: DISABLED_setOffsetTestValidLocalizedEdgesValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setOffsetTestValidLocalizedEdgesValues, TestSize.Level1)
{
    // test is not implemented because LocalizedEdges type is not supported yet
}

/*
 * @tc.name: setRadialGradientTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setRadialGradientTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_RADIAL_GRADIENT_DEFAULT_VALUE);
}

/*
 * @tc.name: setRadialGradientTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setRadialGradientTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Type_CommonMethod_radialGradient_Arg0 inputValue;

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>(2.0_vp);
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>(3.0_vp);
    // radius
    inputValue.radius = Converter::ArkUnion<Union_Number_String, Ark_String>("4vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(std::optional(true));
    // color stops
    std::vector<std::pair<Ark_ResourceColor, Ark_Number>> colorSteps {
        { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), ArkValue<Ark_Number>(0.1f) },
        { ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), ArkValue<Ark_Number>(0.25f) },
        { ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), ArkValue<Ark_Number>(0.5f) },
    };
    Converter::ArkArrayHolder<Array_Tuple_Ark_ResourceColor_Number> colorStepsHolder(colorSteps);
    inputValue.colors = colorStepsHolder.ArkValue();

    // check value
    modifier_->setRadialGradient(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
    auto centerResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_CENTER_NAME);
    EXPECT_EQ(centerResult, "[\"2.00vp\",\"3.00vp\"]");
    auto radiusResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_RADIUS_NAME);
    EXPECT_EQ(radiusResult, "4.00vp");
    auto repeatingResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_REPEATING_NAME);
    EXPECT_EQ(repeatingResult, "true");
    auto colResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_COLORS_NAME);
    EXPECT_EQ(colResult, "[[\"#FFFFFFFF\",\"0.100000\"],[\"#FF123456\",\"0.250000\"],[\"#11223344\",\"0.500000\"]]");
}

/*
 * @tc.name: setRadialGradientRadiusTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setRadialGradientRadiusTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Type_CommonMethod_radialGradient_Arg0 inputValue;

    typedef std::pair<Union_Number_String, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Union_Number_String, Ark_Number>(1), "1.00vp" },
        { Converter::ArkUnion<Union_Number_String, Ark_Number>(0), "0.00vp" },
        { Converter::ArkUnion<Union_Number_String, Ark_Number>(2.45f), "2.45vp" },
        { Converter::ArkUnion<Union_Number_String, Ark_String>("5px"), "5.00px" },
        { Converter::ArkUnion<Union_Number_String, Ark_String>("22.35px"), "22.35px" },
        { Converter::ArkUnion<Union_Number_String, Ark_String>("7vp"), "7.00vp" },
        { Converter::ArkUnion<Union_Number_String, Ark_String>("1.65vp"), "1.65vp" },
        { Converter::ArkUnion<Union_Number_String, Ark_String>("65fp"), "65.00fp" },
        { Converter::ArkUnion<Union_Number_String, Ark_String>("4.3fp"), "4.30fp" },
    };

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>(2.0_vp);
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>(3.0_vp);
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    // color stops
    std::vector<std::pair<Ark_ResourceColor, Ark_Number>> colorSteps {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#112233"), Converter::ArkValue<Ark_Number>(0.5f) },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#223344"), Converter::ArkValue<Ark_Number>(0.9f) }
    };
    Converter::ArkArrayHolder<Array_Tuple_Ark_ResourceColor_Number> colorStepsHolder(colorSteps);
    inputValue.colors = colorStepsHolder.ArkValue();

    // check value
    for (const auto &[arkRadius, expected]: testPlan) {
        inputValue.radius = arkRadius;
        modifier_->setRadialGradient(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
        auto radiusResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_RADIUS_NAME);
        EXPECT_EQ(radiusResult, expected);
    }
}

/*
 * @tc.name: setRadialGradientRadiusTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setRadialGradientRadiusTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Type_CommonMethod_radialGradient_Arg0 inputValue;

    typedef std::pair<Union_Number_String, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Union_Number_String, Ark_Number>(-1), "0.00vp" },
        { Converter::ArkUnion<Union_Number_String, Ark_Number>(-2.45f), "0.00vp" },
        { Converter::ArkUnion<Union_Number_String, Ark_String>("-5px"), "0.00vp" },
        { Converter::ArkUnion<Union_Number_String, Ark_String>("-22.35px"), "0.00vp" },
        { Converter::ArkUnion<Union_Number_String, Ark_String>("-7vp"), "0.00vp" },
        { Converter::ArkUnion<Union_Number_String, Ark_String>("-1.65vp"), "0.00vp" },
        { Converter::ArkUnion<Union_Number_String, Ark_String>("-65fp"), "0.00vp" },
        { Converter::ArkUnion<Union_Number_String, Ark_String>("-4.3fp"), "0.00vp" },
    };

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>(2.0_vp);
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>(3.0_vp);
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    // color stops
    std::vector<std::pair<Ark_ResourceColor, Ark_Number>> colorSteps {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#112233"), Converter::ArkValue<Ark_Number>(0.5f) },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#223344"), Converter::ArkValue<Ark_Number>(0.9f) }
    };
    Converter::ArkArrayHolder<Array_Tuple_Ark_ResourceColor_Number> colorStepsHolder(colorSteps);
    inputValue.colors = colorStepsHolder.ArkValue();

    // check value
    for (const auto &[arkRadius, expected]: testPlan) {
        inputValue.radius = arkRadius;
        modifier_->setRadialGradient(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
        auto radiusResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_RADIUS_NAME);
        EXPECT_EQ(radiusResult, expected);
    }
}

/*
 * @tc.name: setRadialGradientCenter1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setRadialGradientCenter1TestValidValues, TestSize.Level1)
{
    std::string strResult;
    Type_CommonMethod_radialGradient_Arg0 inputValue;

    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), "[\"1.00px\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(-1), "[\"-1.00px\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(2.45f), "[\"2.45vp\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(-2.45f), "[\"-2.45vp\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(5.0_px), "[\"5.00px\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(-5.0_px), "[\"-5.00px\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(22.35_px), "[\"22.35px\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(-22.35_px), "[\"-22.35px\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(7.0_vp), "[\"7.00vp\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(-7.0_vp), "[\"-7.00vp\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(1.65_vp), "[\"1.65vp\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(-1.65_vp), "[\"-1.65vp\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(65.0_fp), "[\"65.00fp\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(-65.0_fp), "[\"-65.00fp\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(4.3_fp), "[\"4.30fp\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(-4.3_fp), "[\"-4.30fp\",\"0.00px\"]" },
        { Converter::ArkValue<Ark_Length>(0.1_pct), "[\"10.00%\",\"0.00px\"]" },
        { RES_ARK_LENGTH, "[\"10.00px\",\"0.00px\"]" },
    };

    // radius
    inputValue.radius = Converter::ArkUnion<Union_Number_String, Ark_String>("4vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    // color stops
    std::vector<std::pair<Ark_ResourceColor, Ark_Number>> colorSteps {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#112233"), Converter::ArkValue<Ark_Number>(0.5f) },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#223344"), Converter::ArkValue<Ark_Number>(0.9f) }
    };
    Converter::ArkArrayHolder<Array_Tuple_Ark_ResourceColor_Number> colorStepsHolder(colorSteps);
    inputValue.colors = colorStepsHolder.ArkValue();

    // check value
    for (const auto &[arkCenter, expected]: testPlan) {
        // center
        inputValue.center.value0 = arkCenter;
        inputValue.center.value1 = Converter::ArkValue<Ark_Length>(0);
        modifier_->setRadialGradient(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
        auto centerResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_CENTER_NAME);
        EXPECT_EQ(centerResult, expected);
    }
}

/*
 * @tc.name: setRadialGradientCenter2TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setRadialGradientCenter2TestValidValues, TestSize.Level1)
{
    std::string strResult;
    Type_CommonMethod_radialGradient_Arg0 inputValue;

    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), "[\"0.00px\",\"1.00px\"]" },
        { Converter::ArkValue<Ark_Length>(-1), "[\"0.00px\",\"-1.00px\"]" },
        { Converter::ArkValue<Ark_Length>(2.45f), "[\"0.00px\",\"2.45vp\"]" },
        { Converter::ArkValue<Ark_Length>(-2.45f), "[\"0.00px\",\"-2.45vp\"]" },
        { Converter::ArkValue<Ark_Length>(5.0_px), "[\"0.00px\",\"5.00px\"]" },
        { Converter::ArkValue<Ark_Length>(-5.0_px), "[\"0.00px\",\"-5.00px\"]" },
        { Converter::ArkValue<Ark_Length>(22.35_px), "[\"0.00px\",\"22.35px\"]" },
        { Converter::ArkValue<Ark_Length>(-22.35_px), "[\"0.00px\",\"-22.35px\"]" },
        { Converter::ArkValue<Ark_Length>(7.0_vp), "[\"0.00px\",\"7.00vp\"]" },
        { Converter::ArkValue<Ark_Length>(-7.0_vp), "[\"0.00px\",\"-7.00vp\"]" },
        { Converter::ArkValue<Ark_Length>(1.65_vp), "[\"0.00px\",\"1.65vp\"]" },
        { Converter::ArkValue<Ark_Length>(-1.65_vp), "[\"0.00px\",\"-1.65vp\"]" },
        { Converter::ArkValue<Ark_Length>(65.0_fp), "[\"0.00px\",\"65.00fp\"]" },
        { Converter::ArkValue<Ark_Length>(-65.0_fp), "[\"0.00px\",\"-65.00fp\"]" },
        { Converter::ArkValue<Ark_Length>(4.3_fp), "[\"0.00px\",\"4.30fp\"]" },
        { Converter::ArkValue<Ark_Length>(-4.3_fp), "[\"0.00px\",\"-4.30fp\"]" },
        { Converter::ArkValue<Ark_Length>(0.1_pct), "[\"0.00px\",\"10.00%\"]" },
        { RES_ARK_LENGTH, "[\"0.00px\",\"10.00px\"]" },
    };

    // radius
    inputValue.radius = Converter::ArkUnion<Union_Number_String, Ark_String>("4vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    // color stops
    std::vector<std::pair<Ark_ResourceColor, Ark_Number>> colorSteps {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#112233"), Converter::ArkValue<Ark_Number>(0.5f) },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#223344"), Converter::ArkValue<Ark_Number>(0.9f) }
    };
    Converter::ArkArrayHolder<Array_Tuple_Ark_ResourceColor_Number> colorStepsHolder(colorSteps);
    inputValue.colors = colorStepsHolder.ArkValue();

    // check value
    for (const auto &[arkCenter, expected]: testPlan) {
        // center
        inputValue.center.value0 = Converter::ArkValue<Ark_Length>(0);
        inputValue.center.value1 = arkCenter;
        modifier_->setRadialGradient(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
        auto centerResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_CENTER_NAME);
        EXPECT_EQ(centerResult, expected);
    }
}

/*
 * @tc.name: setRadialGradientRepeatingTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setRadialGradientRepeatingTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Type_CommonMethod_radialGradient_Arg0 inputValue;

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>(2.0_vp);
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>(3.0_vp);
    // radius
    inputValue.radius = Converter::ArkUnion<Union_Number_String, Ark_String>("4vp");
    // color stops
    std::vector<std::pair<Ark_ResourceColor, Ark_Number>> colorSteps {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#112233"), Converter::ArkValue<Ark_Number>(0.5f) },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#223344"), Converter::ArkValue<Ark_Number>(0.9f) }
    };
    Converter::ArkArrayHolder<Array_Tuple_Ark_ResourceColor_Number> colorStepsHolder(colorSteps);
    inputValue.colors = colorStepsHolder.ArkValue();

    // check undefined repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    modifier_->setRadialGradient(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
    auto repeatingResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_REPEATING_NAME);
    EXPECT_EQ(repeatingResult, "false");

    // check true repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(std::optional(true));
    modifier_->setRadialGradient(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
    repeatingResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_REPEATING_NAME);
    EXPECT_EQ(repeatingResult, "true");

    // check false repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(std::optional(false));
    modifier_->setRadialGradient(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
    repeatingResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_REPEATING_NAME);
    EXPECT_EQ(repeatingResult, "false");
}

/*
 * @tc.name: setRadialGradientResourcesColorStopsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setRadialGradientResourcesColorStopsTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Type_CommonMethod_radialGradient_Arg0 inputValue;
    static Ark_String resName = ArkValue<Ark_String>("aa.bb.cc");
    static const std::string EXPECTED_RESOURCE_COLOR =
        Color::RED.ToString(); // Color::RED is result of ThemeConstants::GetColorXxxx stubs

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>(2.0_vp);
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>(3.0_vp);
    // radius
    inputValue.radius = Converter::ArkUnion<Union_Number_String, Ark_String>("4vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(std::optional(true));
    // color stops
    std::vector<std::pair<Ark_ResourceColor, Ark_Number>> colorSteps {
        { ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&resName)), ArkValue<Ark_Number>(0.5f) },
        { ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, FAKE_RES_ID)), ArkValue<Ark_Number>(0.9f)  },
    };
    Converter::ArkArrayHolder<Array_Tuple_Ark_ResourceColor_Number> colorStepsHolder(colorSteps);
    inputValue.colors = colorStepsHolder.ArkValue();

    // check value
    modifier_->setRadialGradient(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
    auto colResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_COLORS_NAME);
    EXPECT_EQ(colResult, "[[\"#FFFF0000\",\"0.500000\"],[\"#FFFF0000\",\"0.900000\"]]");
}
} // namespace OHOS::Ace::NG