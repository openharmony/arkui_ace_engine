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

struct EventsTracker {
    static inline GENERATED_ArkUICommonMethodEventsReceiver commonMethodsEventsReceiver {};

    static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
        .getCommonMethodEventsReceiver = [] () -> const GENERATED_ArkUICommonMethodEventsReceiver* {
            return &commonMethodsEventsReceiver;
        }
    };
}; // EventsTracker

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
<<<<<<< HEAD
const auto ATTRIBUTE_BACKGROUND_IMAGE_NAME = "backgroundImage";
const auto ATTRIBUTE_BACKGROUND_IMAGE_DEFAULT_VALUE = "NONE";
const auto ATTRIBUTE_BACKGROUND_IMAGE_SIZE_NAME = "backgroundImageSize";
const auto ATTRIBUTE_BACKGROUND_IMAGE_SIZE_DEFAULT_VALUE = "ImageSize.Auto";
const auto ATTRIBUTE_BACKGROUND_IMAGE_SIZE_WIDTH_NAME = "width";
const auto ATTRIBUTE_BACKGROUND_IMAGE_SIZE_WIDTH_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_BACKGROUND_IMAGE_SIZE_HEIGHT_NAME = "height";
const auto ATTRIBUTE_BACKGROUND_IMAGE_SIZE_HEIGHT_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_BACKGROUND_IMAGE_POSITION_NAME = "backgroundImagePosition";
const auto ATTRIBUTE_BACKGROUND_IMAGE_POSITION_X_NAME = "x";
const auto ATTRIBUTE_BACKGROUND_IMAGE_POSITION_X_DEFAULT_VALUE = 0.0;
const auto ATTRIBUTE_BACKGROUND_IMAGE_POSITION_Y_NAME = "y";
const auto ATTRIBUTE_BACKGROUND_IMAGE_POSITION_Y_DEFAULT_VALUE = 0.0;
const auto ATTRIBUTE_CLIP_NAME = "clip";
const auto ATTRIBUTE_CLIP_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_SCALE_NAME = "scale";
const auto ATTRIBUTE_SCALE_X_NAME = "x";
const auto ATTRIBUTE_SCALE_Y_NAME = "y";
const auto ATTRIBUTE_SCALE_CENTER_X_NAME = "centerX";
const auto ATTRIBUTE_SCALE_CENTER_Y_NAME = "centerY";
const auto ATTRIBUTE_SCALE_DEFAULT_VALUE = "{}";
const auto ATTRIBUTE_TRANSLATE_NAME = "translate";
const auto ATTRIBUTE_TRANSLATE_DEFAULT_VALUE = "{}";
const auto ATTRIBUTE_TRANSLATE_X_NAME = "x";
const auto ATTRIBUTE_TRANSLATE_Y_NAME = "y";
const auto ATTRIBUTE_TRANSLATE_Z_NAME = "z";
const auto ATTRIBUTE_ID_NAME = "id";
const auto ATTRIBUTE_ID_DEFAULT_VALUE = "";
=======
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
>>>>>>> e3b895f77c (Unit tests)

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

typedef std::pair<Opt_Union_Number_String, std::string> ScaleTranslateTestStep;
static const std::vector<ScaleTranslateTestStep> SCALE_TRANSLATE_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(1.0f), "1.00vp" },
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(-2.5f), "-2.50vp" },
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(0.0f), "0.00vp" },
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("1.00px"), "1.00px" },
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("0.00px"), "0.00px" },
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("2.45vp"), "2.45vp" },
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("5.00px"), "5.00px" },
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("-22.35px"), "-22.35px" },
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("7.00vp"), "7.00vp" },
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("1.65vp"), "1.65vp" },
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("65.00fp"), "65.00fp" },
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("4.30fp"), "4.30fp" },
    { Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("12.00%"), "12.00%" },
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
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
        AddResource("bi_public_ok", "path_to_background_image");
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
    using OneTestStep = std::pair<Union_Color_Number_String_Resource, std::string>;
    static const std::string PROP_NAME("backgroundColor");
    static Ark_String resName = ArkValue<Ark_String>("aa.bb.cc");
    static const std::string EXPECTED_RESOURCE_COLOR =
        Color::RED.ToString(); // Color::RED is result of ThemeConstants::GetColorXxxx stubs
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Number>(0x123456), "#FF123456" },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Number>(0.5f), "#00000000" },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#11223344"), "#11223344" },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_String>("65535"), "#FF00FFFF" },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Resource>(ArkRes(&resName)), EXPECTED_RESOURCE_COLOR },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Resource>(ArkRes(nullptr, 1234)), EXPECTED_RESOURCE_COLOR },
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
        auto value = Converter::ArkUnion<Ark_Union_Margin_Length_LocalizedMargin, Ark_Length>(arkMargin);
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
        auto value = Converter::ArkUnion<Ark_Union_Margin_Length_LocalizedMargin, Ark_Padding>(inputValue);
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
        auto value = Converter::ArkUnion<Ark_Union_Margin_Length_LocalizedMargin, Ark_Padding>(inputValue);
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
        auto value = Converter::ArkUnion<Ark_Union_Margin_Length_LocalizedMargin, Ark_Padding>(inputValue);
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
        auto value = Converter::ArkUnion<Ark_Union_Margin_Length_LocalizedMargin, Ark_Padding>(inputValue);
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
        auto value = Converter::ArkUnion<Ark_Union_Padding_Length_LocalizedPadding, Ark_Length>(arkPadding);
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
        auto value = Converter::ArkUnion<Ark_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);
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
        auto value = Converter::ArkUnion<Ark_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);
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
        auto value = Converter::ArkUnion<Ark_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);
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
        auto value = Converter::ArkUnion<Ark_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);
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
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Position>(position);
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
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Position>(position);
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
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
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
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
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
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
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
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
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
    Ark_Type_CommonMethod_radialGradient_value inputValue;

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>(2.0_vp);
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>(3.0_vp);
    // radius
    inputValue.radius = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("4vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(std::optional(true));
    // color stops
    std::vector<std::pair<Union_Color_Number_String_Resource, Ark_Number>> colorSteps {
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Color>(ARK_COLOR_WHITE), ArkValue<Ark_Number>(0.1f) },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Number>(0x123456), ArkValue<Ark_Number>(0.25f) },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#11223344"), ArkValue<Ark_Number>(0.5f) },
    };
    Converter::ArkArrayHolder<Array_Tuple_ResourceColor_Number> colorStepsHolder(colorSteps);
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
    Ark_Type_CommonMethod_radialGradient_value inputValue;

    typedef std::pair<Ark_Union_Number_String, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(1), "1.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(0), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(2.45f), "2.45vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("5px"), "5.00px" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("22.35px"), "22.35px" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("7vp"), "7.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("1.65vp"), "1.65vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("65fp"), "65.00fp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("4.3fp"), "4.30fp" },
    };

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>(2.0_vp);
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>(3.0_vp);
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    // color stops
    std::vector<std::pair<Union_Color_Number_String_Resource, Ark_Number>> colorSteps {
        { Converter::ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#112233"),
            Converter::ArkValue<Ark_Number>(0.5f) },
        { Converter::ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#223344"),
            Converter::ArkValue<Ark_Number>(0.9f) }
    };
    Converter::ArkArrayHolder<Array_Tuple_ResourceColor_Number> colorStepsHolder(colorSteps);
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
    Ark_Type_CommonMethod_radialGradient_value inputValue;

    typedef std::pair<Ark_Union_Number_String, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(-1), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(-2.45f), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-5px"), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-22.35px"), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-7vp"), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-1.65vp"), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-65fp"), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-4.3fp"), "0.00vp" },
    };

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>(2.0_vp);
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>(3.0_vp);
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    // color stops
    std::vector<std::pair<Union_Color_Number_String_Resource, Ark_Number>> colorSteps {
        { Converter::ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#112233"),
            Converter::ArkValue<Ark_Number>(0.5f) },
        { Converter::ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#223344"),
            Converter::ArkValue<Ark_Number>(0.9f) }
    };
    Converter::ArkArrayHolder<Array_Tuple_ResourceColor_Number> colorStepsHolder(colorSteps);
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
    Ark_Type_CommonMethod_radialGradient_value inputValue;

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
    inputValue.radius = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("4vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    // color stops
    std::vector<std::pair<Union_Color_Number_String_Resource, Ark_Number>> colorSteps {
        { Converter::ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#112233"),
            Converter::ArkValue<Ark_Number>(0.5f) },
        { Converter::ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#223344"),
            Converter::ArkValue<Ark_Number>(0.9f) }
    };
    Converter::ArkArrayHolder<Array_Tuple_ResourceColor_Number> colorStepsHolder(colorSteps);
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
    Ark_Type_CommonMethod_radialGradient_value inputValue;

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
    inputValue.radius = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("4vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    // color stops
    std::vector<std::pair<Union_Color_Number_String_Resource, Ark_Number>> colorSteps {
        { Converter::ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#112233"),
            Converter::ArkValue<Ark_Number>(0.5f) },
        { Converter::ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#223344"),
            Converter::ArkValue<Ark_Number>(0.9f) }
    };
    Converter::ArkArrayHolder<Array_Tuple_ResourceColor_Number> colorStepsHolder(colorSteps);
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
    Ark_Type_CommonMethod_radialGradient_value inputValue;

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>(2.0_vp);
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>(3.0_vp);
    // radius
    inputValue.radius = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("4vp");
    // color stops
    std::vector<std::pair<Union_Color_Number_String_Resource, Ark_Number>> colorSteps {
        { Converter::ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#112233"),
            Converter::ArkValue<Ark_Number>(0.5f) },
        { Converter::ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#223344"),
            Converter::ArkValue<Ark_Number>(0.9f) }
    };
    Converter::ArkArrayHolder<Array_Tuple_ResourceColor_Number> colorStepsHolder(colorSteps);
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
    Ark_Type_CommonMethod_radialGradient_value inputValue;
    static Ark_String resName = ArkValue<Ark_String>("aa.bb.cc");
    static const std::string EXPECTED_RESOURCE_COLOR =
        Color::RED.ToString(); // Color::RED is result of ThemeConstants::GetColorXxxx stubs

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>(2.0_vp);
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>(3.0_vp);
    // radius
    inputValue.radius = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("4vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(std::optional(true));
    // color stops
    std::vector<std::pair<Union_Color_Number_String_Resource, Ark_Number>> colorSteps {
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Resource>(ArkRes(&resName)), ArkValue<Ark_Number>(0.5f) },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Resource>(ArkRes(nullptr, FAKE_RES_ID)),
            ArkValue<Ark_Number>(0.9f)  },
    };
    Converter::ArkArrayHolder<Array_Tuple_ResourceColor_Number> colorStepsHolder(colorSteps);
    inputValue.colors = colorStepsHolder.ArkValue();

    // check value
    modifier_->setRadialGradient(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
    auto colResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_COLORS_NAME);
    EXPECT_EQ(colResult, "[[\"#FFFF0000\",\"0.500000\"],[\"#FFFF0000\",\"0.900000\"]]");
}

/*
<<<<<<< HEAD
 * @tc.name: setBackgroundImageDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setBackgroundImageDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_BACKGROUND_IMAGE_DEFAULT_VALUE);
}

/*
 * @tc.name: setBackgroundImageValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setBackgroundImageValidValues, TestSize.Level1)
{
    Ark_String str = Converter::ArkValue<Ark_String>("path");
    Ark_ResourceStr resStr = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(str);
    auto src = Converter::ArkUnion<Ark_Union_ResourceStr_PixelMap, Ark_ResourceStr>(resStr);
    Opt_ImageRepeat repeat = Converter::ArkValue<Opt_ImageRepeat>(Ark_Empty());

    modifier_->setBackgroundImage(node_, &src, &repeat);
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, "path, ImageRepeat.NoRepeat");

    const Ark_String resName = Converter::ArkValue<Ark_String>("bi_public_ok");
    auto resource = ArkRes(const_cast<Ark_String*>(&resName), -1, NodeModifier::ResourceType::STRING);
    resStr = Converter::ArkUnion<Ark_ResourceStr, Ark_Resource>(resource);
    src = Converter::ArkUnion<Ark_Union_ResourceStr_PixelMap, Ark_ResourceStr>(resStr);

    modifier_->setBackgroundImage(node_, &src, nullptr);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, "path_to_background_image, ImageRepeat.NoRepeat");
}

/*
 * @tc.name: setBackgroundImageRepeatValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setBackgroundImageRepeatValidValues, TestSize.Level1)
{
    Ark_String str = Converter::ArkValue<Ark_String>("path");
    Ark_ResourceStr resStr = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(str);
    auto src = Converter::ArkUnion<Ark_Union_ResourceStr_PixelMap, Ark_ResourceStr>(resStr);
    Opt_ImageRepeat repeat = Converter::ArkValue<Opt_ImageRepeat>(
        std::optional<Ark_ImageRepeat>(ARK_IMAGE_REPEAT_X));
    modifier_->setBackgroundImage(node_, &src, &repeat);
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, "path, ImageRepeat.X");

    repeat = Converter::ArkValue<Opt_ImageRepeat>(std::optional<Ark_ImageRepeat>(ARK_IMAGE_REPEAT_Y));
    modifier_->setBackgroundImage(node_, &src, &repeat);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, "path, ImageRepeat.Y");

    repeat = Converter::ArkValue<Opt_ImageRepeat>(std::optional<Ark_ImageRepeat>(ARK_IMAGE_REPEAT_XY));
    modifier_->setBackgroundImage(node_, &src, &repeat);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, "path, ImageRepeat.XY");

    repeat = Converter::ArkValue<Opt_ImageRepeat>(std::optional<Ark_ImageRepeat>(ARK_IMAGE_REPEAT_NO_REPEAT));
    modifier_->setBackgroundImage(node_, &src, &repeat);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, "path, ImageRepeat.NoRepeat");
}

/*
 * @tc.name: DISABLED_setBackgroundImagePixelmapValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setBackgroundImagePixelmapValues, TestSize.Level1)
{
    // pixelmap attribute is not supported yet
}

/*
 * @tc.name: setBackgroundImageSizeDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setBackgroundImageSizeDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_DEFAULT_VALUE);
}

/*
 * @tc.name: setBackgroundImageSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setBackgroundImageSizeValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Union_SizeOptions_ImageSize inputValue;

    typedef std::pair<Ark_Length, std::string> OneTestStep2;
    static const std::vector<OneTestStep2> testPlan2 = {
        { Converter::ArkValue<Ark_Length>(1), "1.00px" },
        { Converter::ArkValue<Ark_Length>(0), "0.00px" },
        { Converter::ArkValue<Ark_Length>(2.45f), "2.45px" },
        { Converter::ArkValue<Ark_Length>(5.0_px), "5.00px" },
        { Converter::ArkValue<Ark_Length>(22.35_px), "22.35px" },
        { Converter::ArkValue<Ark_Length>(7.0_vp), "7.00px" },
        { Converter::ArkValue<Ark_Length>(1.65_vp), "1.65px" },
        { Converter::ArkValue<Ark_Length>(65.0_fp), "65.00px" },
        { Converter::ArkValue<Ark_Length>(4.3_fp), "4.30px" },
        { Converter::ArkValue<Ark_Length>(0.12_pct), "0.12px" },
        { RES_ARK_LENGTH, "10.00px" },
    };

    for (const auto &[arkLength, expected]: testPlan2) {
        Ark_SizeOptions arkSizeOptions;
        arkSizeOptions.width = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkLength));
        arkSizeOptions.height = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue = Converter::ArkUnion<Ark_Union_SizeOptions_ImageSize, Ark_SizeOptions>(arkSizeOptions);
        modifier_->setBackgroundImageSize(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_NAME);
        auto width = GetAttrValue<std::string>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_WIDTH_NAME);
        EXPECT_EQ(width, expected);
        auto height = GetAttrValue<std::string>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_HEIGHT_NAME);
        EXPECT_EQ(height, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_HEIGHT_DEFAULT_VALUE);
    }

    for (const auto &[arkLength, expected]: testPlan2) {
        Ark_SizeOptions arkSizeOptions;
        arkSizeOptions.height = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkLength));
        arkSizeOptions.width = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue = Converter::ArkUnion<Ark_Union_SizeOptions_ImageSize, Ark_SizeOptions>(arkSizeOptions);
        modifier_->setBackgroundImageSize(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_NAME);
        auto width = GetAttrValue<std::string>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_WIDTH_NAME);
        EXPECT_EQ(width, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_WIDTH_DEFAULT_VALUE);
        auto height = GetAttrValue<std::string>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_HEIGHT_NAME);
        EXPECT_EQ(height, expected);
    }
}

/*
 * @tc.name: setBackgroundImageSizeValidEnumValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setBackgroundImageSizeValidEnumValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Union_SizeOptions_ImageSize inputValue;

    typedef std::pair<Ark_ImageSize, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { ARK_IMAGE_SIZE_COVER, "ImageSize.Cover" },
        { ARK_IMAGE_SIZE_CONTAIN, "ImageSize.Contain" },
        { ARK_IMAGE_SIZE_FILL, "ImageSize.FILL" },
        { ARK_IMAGE_SIZE_AUTO, "ImageSize.Auto" },
    };

    for (const auto &[arkImageSize, expected]: testPlan) {
        inputValue = Converter::ArkUnion<Ark_Union_SizeOptions_ImageSize, Ark_ImageSize>(arkImageSize);
        modifier_->setBackgroundImageSize(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setBackgroundImageSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setBackgroundImageSizeInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Union_SizeOptions_ImageSize inputValue;

    typedef std::pair<Ark_ImageSize, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { static_cast<Ark_ImageSize>(-1), "ImageSize.Auto" },
        { static_cast<Ark_ImageSize>(4), "ImageSize.Auto" },
    };

    for (const auto &[arkImageSize, expected]: testPlan) {
        inputValue = Converter::ArkUnion<Ark_Union_SizeOptions_ImageSize, Ark_ImageSize>(arkImageSize);
        modifier_->setBackgroundImageSize(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_NAME);
        EXPECT_EQ(strResult, expected);
    }

    static const std::vector<Ark_Length> testPlan2 = {
        Converter::ArkValue<Ark_Length>(-1),
        Converter::ArkValue<Ark_Length>(-2.45f),
        Converter::ArkValue<Ark_Length>(-5.0_px),
        Converter::ArkValue<Ark_Length>(-22.35_px),
        Converter::ArkValue<Ark_Length>(-7.0_vp),
        Converter::ArkValue<Ark_Length>(-1.65_vp),
        Converter::ArkValue<Ark_Length>(-65.0_fp),
        Converter::ArkValue<Ark_Length>(-4.3_fp),
        Converter::ArkValue<Ark_Length>(-0.12_pct),
    };

    for (const auto &arkLength: testPlan2) {
        Ark_SizeOptions arkSizeOptions;
        arkSizeOptions.width = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkLength));
        arkSizeOptions.height = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue = Converter::ArkUnion<Ark_Union_SizeOptions_ImageSize, Ark_SizeOptions>(arkSizeOptions);
        modifier_->setBackgroundImageSize(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_NAME);
        auto width = GetAttrValue<std::string>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_WIDTH_NAME);
        EXPECT_EQ(width, "0.00px");
        auto height = GetAttrValue<std::string>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_HEIGHT_NAME);
        EXPECT_EQ(height, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_HEIGHT_DEFAULT_VALUE);
    }

    for (const auto &arkLength: testPlan2) {
        Ark_SizeOptions arkSizeOptions;
        arkSizeOptions.height = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkLength));
        arkSizeOptions.width = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue = Converter::ArkUnion<Ark_Union_SizeOptions_ImageSize, Ark_SizeOptions>(arkSizeOptions);
        modifier_->setBackgroundImageSize(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_NAME);
        auto width = GetAttrValue<std::string>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_WIDTH_NAME);
        EXPECT_EQ(width, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_WIDTH_DEFAULT_VALUE);
        auto height = GetAttrValue<std::string>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_HEIGHT_NAME);
        EXPECT_EQ(height, "0.00px");
    }
}

/*
 * @tc.name: setBackgroundImagePositionDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setBackgroundImagePositionDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_NAME);
    auto x = GetAttrValue<double>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_X_NAME);
    EXPECT_NEAR(x, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_X_DEFAULT_VALUE, FLT_EPSILON);
    auto y = GetAttrValue<double>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_Y_NAME);
    EXPECT_NEAR(y, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_Y_DEFAULT_VALUE, FLT_EPSILON);
}

/*
 * @tc.name: setBackgroundImagePositionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setBackgroundImagePositionValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Union_Position_Alignment inputValue;

    typedef std::pair<Ark_Length, double> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), 1.0 },
        { Converter::ArkValue<Ark_Length>(0), 0.0 },
        { Converter::ArkValue<Ark_Length>(-2.5f), -2.5 },
        { Converter::ArkValue<Ark_Length>(5.0_px), 5.0 },
        { Converter::ArkValue<Ark_Length>(22.5_px), 22.5 },
        { Converter::ArkValue<Ark_Length>(7.0_vp), 7.0 },
        { Converter::ArkValue<Ark_Length>(1.5_vp), 1.5 },
        { Converter::ArkValue<Ark_Length>(65.0_fp), 65.0 },
        { Converter::ArkValue<Ark_Length>(4.5_fp), 4.5 },
        { RES_ARK_LENGTH, 10.0 },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        Ark_Position arkPosition;
        arkPosition.x = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkLength));
        arkPosition.y = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue = Converter::ArkUnion<Ark_Union_Position_Alignment, Ark_Position>(arkPosition);
        modifier_->setBackgroundImagePosition(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_NAME);
        auto x = GetAttrValue<double>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_X_NAME);
        EXPECT_NEAR(x, expected, FLT_EPSILON);
        auto y = GetAttrValue<double>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_Y_NAME);
        EXPECT_NEAR(y, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_Y_DEFAULT_VALUE, FLT_EPSILON);
    }

    for (const auto &[arkLength, expected]: testPlan) {
        Ark_Position arkPosition;
        arkPosition.y = Converter::ArkValue<Opt_Length>(std::optional<Ark_Length>(arkLength));
        arkPosition.x = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue = Converter::ArkUnion<Ark_Union_Position_Alignment, Ark_Position>(arkPosition);
        modifier_->setBackgroundImagePosition(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_NAME);
        auto x = GetAttrValue<double>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_X_NAME);
        EXPECT_NEAR(x, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_X_DEFAULT_VALUE, FLT_EPSILON);
        auto y = GetAttrValue<double>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_Y_NAME);
        EXPECT_NEAR(y, expected, FLT_EPSILON);
    }
}

/*
 * @tc.name: setBackgroundImagePositionValidAlignmentValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setBackgroundImagePositionValidAlignmentValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Union_Position_Alignment inputValue;

    typedef std::pair<Ark_Alignment, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { ARK_ALIGNMENT_TOP_START, "Alignment.TopStart" },
        { ARK_ALIGNMENT_TOP, "Alignment.Top" },
        { ARK_ALIGNMENT_TOP_END, "Alignment.TopEnd" },
        { ARK_ALIGNMENT_START, "Alignment.Start" },
        { ARK_ALIGNMENT_CENTER, "Alignment.Center" },
        { ARK_ALIGNMENT_END, "Alignment.End" },
        { ARK_ALIGNMENT_BOTTOM_START, "Alignment.BottomStart" },
        { ARK_ALIGNMENT_BOTTOM, "Alignment.Bottom" },
        { ARK_ALIGNMENT_BOTTOM_END, "Alignment.BottomEnd" },
    };

    for (const auto &[arkAlign, expected]: testPlan) {
        inputValue = Converter::ArkUnion<Ark_Union_Position_Alignment, Ark_Alignment>(arkAlign);
        modifier_->setBackgroundImagePosition(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setClipBoolValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setClipBoolValues, TestSize.Level1)
{
    // default
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_CLIP_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_CLIP_DEFAULT_VALUE);

    modifier_->setClip0(node_, true);
    strResult = GetStringAttribute(node_, ATTRIBUTE_CLIP_NAME);
    EXPECT_EQ(strResult, "true");

    modifier_->setClip0(node_, false);
    strResult = GetStringAttribute(node_, ATTRIBUTE_CLIP_NAME);
    EXPECT_EQ(strResult, "false");

    Ark_Type_CommonMethod_clip_value arg = ArkUnion<Ark_Type_CommonMethod_clip_value, Ark_Boolean>(ArkValue<Ark_Boolean>(true));
    modifier_->setClip1(node_, &arg);
    strResult = GetStringAttribute(node_, ATTRIBUTE_CLIP_NAME);
    EXPECT_EQ(strResult, "true");

    arg = ArkUnion<Ark_Type_CommonMethod_clip_value, Ark_Boolean>(ArkValue<Ark_Boolean>(false));
    modifier_->setClip1(node_, &arg);
    strResult = GetStringAttribute(node_, ATTRIBUTE_CLIP_NAME);
=======
 * @tc.name: setResponseRegion
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setResponseRegion, TestSize.Level1)
{
    Union_Array_Rectangle_Rectangle inputValue;
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
    EXPECT_EQ(strResult, "[\"{\\\"x\\\":\\\"0.00px\\\",\\\"y\\\":\\\"20.00vp\\\",\\\"width\\\":\\\"50.00vp\\\","
                         "\\\"height\\\":\\\"0.00px\\\"}\","
                         "\"{\\\"x\\\":\\\"-100.00vp\\\",\\\"y\\\":\\\"-100.00vp\\\",\\\"width\\\":\\\"200.00vp\\\","
                         "\\\"height\\\":\\\"200.00vp\\\"}\"]");
}

/*
 * @tc.name: setConstraintSize
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setConstraintSize, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, setTouchable, TestSize.Level1)
{
    modifier_->setTouchable(node_, 1); // true
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_TOUCHABLE_NAME);
    EXPECT_EQ(strResult, "true");

    modifier_->setTouchable(node_, 0); // false
    strResult = GetStringAttribute(node_, ATTRIBUTE_TOUCHABLE_NAME);
>>>>>>> e3b895f77c (Unit tests)
    EXPECT_EQ(strResult, "false");
}

/*
<<<<<<< HEAD
 * @tc.name: DISABLED_setClipShapeValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setClipShapeValues, TestSize.Level1)
{
    // Ark_CircleAttribute, Ark_EllipseAttribute, Ark_PathAttribute, Ark_RectAttribute are not supported yet!
}

/*
 * @tc.name: setScaleDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setScaleDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_SCALE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SCALE_DEFAULT_VALUE);
}

/*
 * @tc.name: setScaleValidXValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setScaleValidXValues, TestSize.Level1)
{
    std::string strResult;
    Ark_ScaleOptions inputValue;

    inputValue.x = Converter::ArkValue<Opt_Number>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Number>(Ark_Empty());
    inputValue.centerX = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());
    inputValue.centerY = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());

    typedef std::pair<Opt_Number, std::string> NumberTestStep;
    static const std::vector<NumberTestStep> testPlan = {
        { Converter::ArkValue<Opt_Number>(std::optional<float>(2.0f)), "2.000000" },
        { Converter::ArkValue<Opt_Number>(std::optional<float>(0.0f)), "0.000000" },
        { Converter::ArkValue<Opt_Number>(std::optional<float>(-2.5f)), "-2.500000" },
    };

    for (const auto &[arkNumber, expected]: testPlan) {
        inputValue.x = Converter::ArkValue<Opt_Number>(arkNumber);
        modifier_->setScale(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_SCALE_NAME);
        auto x = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_X_NAME);
        EXPECT_EQ(x, expected);
        auto y = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_Y_NAME);
        EXPECT_EQ(y, "1.000000");
        auto centerX = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_CENTER_X_NAME);
        EXPECT_EQ(centerX, "50.00%");
        auto centerY = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_CENTER_Y_NAME);
        EXPECT_EQ(centerY, "50.00%");
=======
 * @tc.name: setLayoutWeight
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setLayoutWeight, TestSize.Level1)
{
    Union_Number_String inputValue;
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
HWTEST_F(CommonMethodModifierTest, setHitTestBehavior, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, setOpacity, TestSize.Level1)
{
    Union_Number_Resource inputValue;
    inputValue.selector = 0;
    inputValue.value0 = Converter::ArkValue<Ark_Number>(0.7001);
    modifier_->setOpacity(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_OPACITY_NAME);
    EXPECT_EQ(strResult.substr(0, 3), "0.7");
}

/**
 * @tc.name: setForegroundColorTest
 * @tc.desc: Check the functionality of CommonMethodModifierTest.setForegroundColor
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setForegroundColor, TestSize.Level1)
{
    using OneTestStep = std::pair<Union_Color_Number_String_Resource, std::string>;
    static const std::string PROP_NAME("foregroundColor");
    static Ark_String resName = ArkValue<Ark_String>("aa.bb.cc");
    static const std::string EXPECTED_RESOURCE_COLOR =
        Color::RED.ToString(); // Color::RED is result of ThemeConstants::GetColorXxxx stubs
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Number>(0x123456), "#FF123456" },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Number>(0.5f), "#00000000" },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_String>("#11223344"), "#11223344" },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_String>("65535"), "#FF00FFFF" },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Resource>(ArkRes(&resName)), EXPECTED_RESOURCE_COLOR },
        { ArkUnion<Union_Color_Number_String_Resource, Ark_Resource>(ArkRes(nullptr, 1234)), EXPECTED_RESOURCE_COLOR },
    };

    ASSERT_NE(modifier_->setForegroundColor, nullptr);

    for (const auto &[arkResColor, expected]: testPlan) {
        Union_Union_Color_Number_String_Resource_ColoringStrategy value = {
            .selector = 0,
            .value0 = arkResColor
        };
        modifier_->setForegroundColor(node_, &value);
        auto checkColor = GetAttrValue<std::string>(node_, PROP_NAME);
        EXPECT_EQ(checkColor, expected);
>>>>>>> e3b895f77c (Unit tests)
    }
}

/*
<<<<<<< HEAD
 * @tc.name: setScaleValidYValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setScaleValidYValues, TestSize.Level1)
{
    std::string strResult;
    Ark_ScaleOptions inputValue;

    inputValue.x = Converter::ArkValue<Opt_Number>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Number>(Ark_Empty());
    inputValue.centerX = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());
    inputValue.centerY = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());

    typedef std::pair<Opt_Number, std::string> NumberTestStep;
    static const std::vector<NumberTestStep> testPlan = {
        { Converter::ArkValue<Opt_Number>(std::optional<float>(2.0f)), "2.000000" },
        { Converter::ArkValue<Opt_Number>(std::optional<float>(0.0f)), "0.000000" },
        { Converter::ArkValue<Opt_Number>(std::optional<float>(-2.5f)), "-2.500000" },
    };

    for (const auto &[arkNumber, expected]: testPlan) {
        inputValue.y = Converter::ArkValue<Opt_Number>(arkNumber);
        modifier_->setScale(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_SCALE_NAME);
        auto x = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_X_NAME);
        EXPECT_EQ(x, "1.000000");
        auto y = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_Y_NAME);
        EXPECT_EQ(y, expected);
        auto centerX = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_CENTER_X_NAME);
        EXPECT_EQ(centerX, "50.00%");
        auto centerY = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_CENTER_Y_NAME);
        EXPECT_EQ(centerY, "50.00%");
    }
}

/*
 * @tc.name: setScaleValidCenterXValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setScaleValidCenterXValues, TestSize.Level1)
{
    std::string strResult;
    Ark_ScaleOptions inputValue;

    inputValue.x = Converter::ArkValue<Opt_Number>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Number>(Ark_Empty());
    inputValue.centerX = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());
    inputValue.centerY = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());

    for (const auto &[arkCenter, expected]: SCALE_TRANSLATE_TEST_PLAN) {
        inputValue.centerX = arkCenter;
        modifier_->setScale(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_SCALE_NAME);
        auto x = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_X_NAME);
        EXPECT_EQ(x, "1.000000");
        auto y = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_Y_NAME);
        EXPECT_EQ(y, "1.000000");
        auto centerX = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_CENTER_X_NAME);
        EXPECT_EQ(centerX, expected);
        auto centerY = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_CENTER_Y_NAME);
        EXPECT_EQ(centerY, "50.00%");
    }
}

/*
 * @tc.name: setScaleValidCenterYValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setScaleValidCenterYValues, TestSize.Level1)
{
    std::string strResult;
    Ark_ScaleOptions inputValue;

    inputValue.x = Converter::ArkValue<Opt_Number>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Number>(Ark_Empty());
    inputValue.centerX = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());
    inputValue.centerY = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());

    for (const auto &[arkCenter, expected]: SCALE_TRANSLATE_TEST_PLAN) {
        inputValue.centerY= arkCenter;
        modifier_->setScale(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_SCALE_NAME);
        auto x = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_X_NAME);
        EXPECT_EQ(x, "1.000000");
        auto y = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_Y_NAME);
        EXPECT_EQ(y, "1.000000");
        auto centerX = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_CENTER_X_NAME);
        EXPECT_EQ(centerX, "50.00%");
        auto centerY = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_CENTER_Y_NAME);
        EXPECT_EQ(centerY, expected);
    }
}

/*
 * @tc.name: setTranslateDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setTranslateDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_TRANSLATE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_TRANSLATE_DEFAULT_VALUE);
}

/*
 * @tc.name: setTranslateValidXValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setTranslateValidXValues, TestSize.Level1)
{
    std::string strResult;
    Ark_TranslateOptions inputValue;

    inputValue.x = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());
    inputValue.z = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());

    for (const auto &[arkTranslate, expected]: SCALE_TRANSLATE_TEST_PLAN) {
        inputValue.x = arkTranslate;
        modifier_->setTranslate(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_TRANSLATE_NAME);
        auto x = GetAttrValue<std::string>(strResult, ATTRIBUTE_TRANSLATE_X_NAME);
        EXPECT_EQ(x, expected);
        auto y = GetAttrValue<std::string>(strResult, ATTRIBUTE_TRANSLATE_Y_NAME);
        EXPECT_EQ(y, "0.00px");
        auto z = GetAttrValue<std::string>(strResult, ATTRIBUTE_TRANSLATE_Z_NAME);
        EXPECT_EQ(z, "0.00px");
    }
}

/*
 * @tc.name: setTranslateValidYValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setTranslateValidYValues, TestSize.Level1)
{
    std::string strResult;
    Ark_TranslateOptions inputValue;

    inputValue.x = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());
    inputValue.z = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());

    for (const auto &[arkTranslate, expected]: SCALE_TRANSLATE_TEST_PLAN) {
        inputValue.y = arkTranslate;
        modifier_->setTranslate(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_TRANSLATE_NAME);
        auto x = GetAttrValue<std::string>(strResult, ATTRIBUTE_TRANSLATE_X_NAME);
        EXPECT_EQ(x, "0.00px");
        auto y = GetAttrValue<std::string>(strResult, ATTRIBUTE_TRANSLATE_Y_NAME);
        EXPECT_EQ(y, expected);
        auto z = GetAttrValue<std::string>(strResult, ATTRIBUTE_TRANSLATE_Z_NAME);
        EXPECT_EQ(z, "0.00px");
    }
}

/*
 * @tc.name: setTranslateValidZValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setTranslateValidZValues, TestSize.Level1)
{
    std::string strResult;
    Ark_TranslateOptions inputValue;

    inputValue.x = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());
    inputValue.z = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty());

    for (const auto &[arkTranslate, expected]: SCALE_TRANSLATE_TEST_PLAN) {
        inputValue.z = arkTranslate;
        modifier_->setTranslate(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_TRANSLATE_NAME);
        auto x = GetAttrValue<std::string>(strResult, ATTRIBUTE_TRANSLATE_X_NAME);
        EXPECT_EQ(x, "0.00px");
        auto y = GetAttrValue<std::string>(strResult, ATTRIBUTE_TRANSLATE_Y_NAME);
        EXPECT_EQ(y, "0.00px");
        auto z = GetAttrValue<std::string>(strResult, ATTRIBUTE_TRANSLATE_Z_NAME);
        EXPECT_EQ(z, expected);
    }
}

/*
 * @tc.name: setIdDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setIdDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_ID_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ID_DEFAULT_VALUE);
}

/*
 * @tc.name: setIdValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setIdValidValues, TestSize.Level1)
{
    Ark_String inputValue = Converter::ArkValue<Ark_String>("custom_id");
    modifier_->setId(node_, &inputValue);
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_ID_NAME);
    EXPECT_EQ(strResult, "custom_id");

    inputValue = Converter::ArkValue<Ark_String>("other id");
    modifier_->setId(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ID_NAME);
    EXPECT_EQ(strResult, "other id");
}

/*
 * @tc.name: setIdInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setIdInvalidValues, TestSize.Level1)
{
    modifier_->setId(node_, nullptr);
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_ID_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ID_DEFAULT_VALUE);
}

/*
 * @tc.name: setOnVisibleAreaChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setOnVisibleAreaChangeTest, TestSize.Level1)
{
    Ark_Function func = {};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);

    struct CheckEvent {
        int32_t nodeId;
        bool isExpanding;
        float currentRatio;
    };
    static std::vector<CheckEvent> checkEvent;
    EventsTracker::commonMethodsEventsReceiver.onVisibleAreaChange =
        [](Ark_Int32 nodeId, const Ark_Boolean isExpanding, const Ark_Number currentRatio)
    {
        checkEvent.push_back({
            .nodeId = Converter::Convert<int32_t>(nodeId),
            .isExpanding = Converter::Convert<bool>(isExpanding),
            .currentRatio = Converter::Convert<float>(currentRatio)
        });
    };

    std::vector<float> ratioVec;
    ratioVec.push_back(0.5f);
    Converter::ArkArrayHolder<Array_Number> vecHolder(ratioVec);
    Array_Number numberArrayResult = vecHolder.ArkValue();

    std::vector<float> ratioVecInvalid1;
    ratioVecInvalid1.push_back(-0.5f);
    Converter::ArkArrayHolder<Array_Number> vecHolderInvalid1(ratioVecInvalid1);
    Array_Number numberArrayResultInvalid1 = vecHolderInvalid1.ArkValue();

    std::vector<float> ratioVecInvalid2;
    ratioVecInvalid2.push_back(1.5f);
    Converter::ArkArrayHolder<Array_Number> vecHolderInvalid2(ratioVecInvalid2);
    Array_Number numberArrayResultInvalid2 = vecHolderInvalid2.ArkValue();

    EXPECT_EQ(checkEvent.size(), 0);

    modifier_->setOnVisibleAreaChange(node_, &numberArrayResult, func);

    EXPECT_EQ(checkEvent.size(), 2);
    EXPECT_EQ(checkEvent[0].nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent[1].nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent[0].isExpanding, false);
    EXPECT_EQ(checkEvent[1].isExpanding, true);
    EXPECT_EQ(checkEvent[0].currentRatio, 0.0f);
    EXPECT_EQ(checkEvent[1].currentRatio, ratioVec[0]);

    modifier_->setOnVisibleAreaChange(node_, &numberArrayResultInvalid1, func);
    modifier_->setOnVisibleAreaChange(node_, &numberArrayResultInvalid2, func);

    EXPECT_EQ(checkEvent.size(), 6);
    EXPECT_EQ(checkEvent[3].currentRatio, 0.0f);
    EXPECT_EQ(checkEvent[5].currentRatio, 1.0f);
}

/*
 * @tc.name: setAnimationDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setAnimationDefaultValues, TestSize.Level1)
{
    Ark_AnimateParam param;
    param.duration = Converter::ArkValue<Opt_Number>(Ark_Empty());
    param.delay = Converter::ArkValue<Opt_Number>(Ark_Empty());
    param.iterations = Converter::ArkValue<Opt_Number>(Ark_Empty());
    param.tempo = Converter::ArkValue<Opt_Number>(Ark_Empty());
    param.playMode = Converter::ArkValue<Opt_PlayMode>(Ark_Empty());
    param.finishCallbackType = Converter::ArkValue<Opt_FinishCallbackType>(Ark_Empty());
    param.curve = Converter::ArkValue<Opt_Union_Curve_String_ICurve>(Ark_Empty());
    param.expectedFrameRateRange = Converter::ArkValue<Opt_ExpectedFrameRateRange>(Ark_Empty());

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    frameNode->MarkBuildDone();
    modifier_->setAnimation(node_, &param);
    AnimationOption option = NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    EXPECT_EQ(option.GetDuration(), 1000);
    EXPECT_EQ(option.GetDelay(), 0);
    EXPECT_EQ(option.GetIteration(), 1);
    EXPECT_EQ(option.GetTempo(), 1.0f);
    EXPECT_EQ(option.GetAnimationDirection(), AnimationDirection::NORMAL);
    EXPECT_EQ(option.GetFinishCallbackType(), FinishCallbackType::REMOVED);
    EXPECT_EQ(option.GetCurve(), Curves::EASE_IN_OUT);
    RefPtr<FrameRateRange> frr = option.GetFrameRateRange();
    EXPECT_NE(frr, nullptr);
    EXPECT_EQ(frr->min_, 0);
    EXPECT_EQ(frr->max_, 0);
    EXPECT_EQ(frr->preferred_, 0);
    EXPECT_EQ(option.GetOnFinishEvent(), nullptr);
}

/*
 * @tc.name: setCloseAnimationValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setCloseAnimationValidValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    frameNode->MarkBuildDone();
    modifier_->setAnimation(node_, nullptr);
    AnimationOption option = NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    EXPECT_EQ(option.GetDuration(), 0);
    EXPECT_EQ(option.GetDelay(), 0);
    EXPECT_EQ(option.GetIteration(), 1);
    EXPECT_EQ(option.GetTempo(), 1.0f);
    EXPECT_EQ(option.GetAnimationDirection(), AnimationDirection::NORMAL);
    EXPECT_EQ(option.GetFinishCallbackType(), FinishCallbackType::REMOVED);
    EXPECT_EQ(option.GetCurve(), nullptr);
    EXPECT_EQ(option.GetFrameRateRange(), nullptr);
    EXPECT_EQ(option.GetOnFinishEvent(), nullptr);
}

/*
 * @tc.name: setOpenAnimationValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setOpenAnimationValidValues, TestSize.Level1)
{
    Ark_AnimateParam param;
    param.duration = Converter::ArkValue<Opt_Number>(std::optional<int32_t>(5));
    param.delay = Converter::ArkValue<Opt_Number>(std::optional<int32_t>(3));
    param.iterations = Converter::ArkValue<Opt_Number>(std::optional<int32_t>(8));
    param.tempo = Converter::ArkValue<Opt_Number>(std::optional<float>(2.5f));
    param.playMode = Converter::ArkValue<Opt_PlayMode>(std::optional<Ark_PlayMode>(ARK_PLAY_MODE_REVERSE));
    param.finishCallbackType = Converter::ArkValue<Opt_FinishCallbackType>(
        std::optional<Ark_FinishCallbackType>(ARK_FINISH_CALLBACK_TYPE_LOGICALLY));
    param.curve = Converter::ArkUnion<Opt_Union_Curve_String_ICurve, Ark_Curve>(ARK_CURVE_EASE);
    Ark_ExpectedFrameRateRange efrr;
    efrr.min = Converter::ArkValue<Ark_Number>(30);
    efrr.max = Converter::ArkValue<Ark_Number>(120);
    efrr.expected = Converter::ArkValue<Ark_Number>(60);
    param.expectedFrameRateRange = Converter::ArkValue<Opt_ExpectedFrameRateRange>(
        std::optional<Ark_ExpectedFrameRateRange>(efrr));

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    frameNode->MarkBuildDone();
    modifier_->setAnimation(node_, &param);
    AnimationOption option = NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    EXPECT_EQ(option.GetDuration(), 5);
    EXPECT_EQ(option.GetDelay(), 3);
    EXPECT_EQ(option.GetIteration(), 8);
    EXPECT_NEAR(option.GetTempo(), 2.5f, FLT_EPSILON);
    EXPECT_EQ(option.GetAnimationDirection(), AnimationDirection::REVERSE);
    EXPECT_EQ(option.GetFinishCallbackType(), FinishCallbackType::LOGICALLY);
    EXPECT_EQ(option.GetCurve(), Curves::EASE);
    RefPtr<FrameRateRange> frr = option.GetFrameRateRange();
    EXPECT_NE(frr, nullptr);
    EXPECT_EQ(frr->min_, 30);
    EXPECT_EQ(frr->max_, 120);
    EXPECT_EQ(frr->preferred_, 60);
    EXPECT_EQ(option.GetOnFinishEvent(), nullptr);
}

/*
 * @tc.name: setAnimationInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setAnimationInvalidValues, TestSize.Level1)
{
    Ark_AnimateParam param;
    param.duration = Converter::ArkValue<Opt_Number>(std::optional<int32_t>(5000));
    param.delay = Converter::ArkValue<Opt_Number>(Ark_Empty());
    param.iterations = Converter::ArkValue<Opt_Number>(Ark_Empty());
    param.tempo = Converter::ArkValue<Opt_Number>(std::optional<float>(0.0f));
    param.playMode = Converter::ArkValue<Opt_PlayMode>(Ark_Empty());
    param.finishCallbackType = Converter::ArkValue<Opt_FinishCallbackType>(Ark_Empty());
    param.curve = Converter::ArkValue<Opt_Union_Curve_String_ICurve>(Ark_Empty());
    param.expectedFrameRateRange = Converter::ArkValue<Opt_ExpectedFrameRateRange>(Ark_Empty());

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    frameNode->MarkBuildDone();
    modifier_->setAnimation(node_, &param);
    AnimationOption option = NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    EXPECT_EQ(option.GetDuration(), 0);
    EXPECT_EQ(option.GetDelay(), 0);
    EXPECT_EQ(option.GetIteration(), 1);
    EXPECT_EQ(option.GetTempo(), 0.0f);
    EXPECT_EQ(option.GetAnimationDirection(), AnimationDirection::NORMAL);
    EXPECT_EQ(option.GetFinishCallbackType(), FinishCallbackType::REMOVED);
    EXPECT_EQ(option.GetCurve(), Curves::EASE_IN_OUT);
    RefPtr<FrameRateRange> frr = option.GetFrameRateRange();
    EXPECT_NE(frr, nullptr);
    EXPECT_EQ(frr->min_, 0);
    EXPECT_EQ(frr->max_, 0);
    EXPECT_EQ(frr->preferred_, 0);
    EXPECT_EQ(option.GetOnFinishEvent(), nullptr);
}

/*
 * @tc.name: DISABLED_setAnimationOnFinishEventValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setAnimationOnFinishEventValues, TestSize.Level1)
{
    // OnFinishEvent does not supported yet
}
} // namespace OHOS::Ace::NG
=======
 * @tc.name: setHoverEffect
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setHoverEffect, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, setVisibility, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setFocusable, TestSize.Level1)
{
    // TODO: [GetStringAttribute] with [focusable] returns non suitable string result.
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
HWTEST_F(CommonMethodModifierTest, setAlignSelf, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, setDisplayPriority, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, setZIndex, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, setDirection, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, setAlign, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, setPosition, TestSize.Level1)
{
    Union_Position_Edges_LocalizedEdges position = {
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
            .y = Converter::ArkValue<Opt_Length>(13.0_pct),
        }
    };
    modifier_->setPosition(node_, &position);
    strResult = GetStringAttribute(node_, ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(strResult, "{\"x\":\"0.00px\",\"y\":\"13.00%\"}");

    position = {
        .selector = 1,
        .value1 = {
            .bottom =Converter::ArkValue<Opt_Length>(42.0_px),
            .left =Converter::ArkValue<Opt_Length>(43.0_vp),
            .right =Converter::ArkValue<Opt_Length>(44.0_fp),
            .top =Converter::ArkValue<Opt_Length>(45.0_pct),
        }
    };
    modifier_->setPosition(node_, &position);
    strResult = GetStringAttribute(node_, ATTRIBUTE_POSITION_NAME);
    EXPECT_EQ(strResult, "{\"x\":\"\",\"y\":\"\"}");

    position = {
        .selector = 1,
        .value1 = {
            .bottom =Converter::ArkValue<Opt_Length>(1.0_px),
            .top =Converter::ArkValue<Opt_Length>(50.0_pct),
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
HWTEST_F(CommonMethodModifierTest, setEnabled, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, setAspectRatio, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, setShadow, TestSize.Level1)
{
    Union_ShadowOptions_ShadowStyle inputValue = {
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
HWTEST_F(CommonMethodModifierTest, setBackgroundBlurStyle, TestSize.Level1)
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
                         "\"policy\":\"BlurStyleActivePolicy.ALWAYS_ACTIVE\","
                         "\"type\":\"BlurType.WITHIN_WINDOW\","
                         "\"inactiveColor\":\"#00000000\",\"scale\":2.2999999523162842}}");
}

/*
 * @tc.name: setForegroundBlurStyle
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setForegroundBlurStyle, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setBlur, TestSize.Level1)
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
HWTEST_F(CommonMethodModifierTest, setOverlay, TestSize.Level1)
{
    Union_String_CustomBuilder_ComponentContent value = {
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
HWTEST_F(CommonMethodModifierTest, setBorder, TestSize.Level1)
{
    Ark_BorderOptions inputValue = {
        .color = {
            .value = {
                .selector = 1,
                .value1 = {
                    .selector = 0,
                    .value0 = ARK_COLOR_BLUE
                }
            }
        },
        .dashGap = {
            .value = {
                .selector = 0,
                .value0 = {
                    .left = Converter::ArkValue<Opt_Length>(8.0_pct),
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
                    .left = Converter::ArkValue<Opt_Length>(8.0_pct),
                    .top = Converter::ArkValue<Opt_Length>(4.0_fp),
                    .right = Converter::ArkValue<Opt_Length>(3.0_px),
                    .bottom = Converter::ArkValue<Opt_Length>(1.0_vp),
                }
            }
        },
        .radius = {
            .value = {
                .selector = 1,
                .value1 = Converter::ArkValue<Ark_Length>(5.0_px),
            }
        },
        .style = {
            .value = {
                .selector = 1,
                .value1 = ARK_BORDER_STYLE_DASHED,
            }
        },
        .width = {
            .value = {
                .selector = 1,
                .value1 = Converter::ArkValue<Ark_Length>(10.0_px),
            }
        }
    };
    modifier_->setBorder(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_BORDER_NAME);
    EXPECT_EQ(strResult, "{\"style\":\"BorderStyle.Dashed\",\"color\":\"#FF0000FF\","
                         "\"width\":\"10.00px\",\"radius\":{\"topLeft\":\"5.00px\","
                         "\"topRight\":\"5.00px\",\"bottomLeft\":\"5.00px\","
                         "\"bottomRight\":\"5.00px\"},\"dashGap\":\"8.00%\","
                         "\"dashWidth\":\"8.00%\"}");


    Union_BorderStyle_EdgeStyles style = {
        .selector = 1,
        .value1 = {
            .left = { .value = ARK_BORDER_STYLE_DOTTED },
            .top = { .value = ARK_BORDER_STYLE_DASHED },
            .right = { .value = ARK_BORDER_STYLE_SOLID },
            .bottom = { .value = ARK_BORDER_STYLE_DOTTED },
        }
    };
    modifier_->setBorderStyle(node_, &style);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BORDER_STYLE_NAME);
    EXPECT_EQ(strResult, "BorderStyle.Dotted");

    Union_Length_EdgeWidths_LocalizedEdgeWidths width = {
        .selector = 1,
        .value1 = {
            .left = Converter::ArkValue<Opt_Length>(8.0_pct),
            .top = Converter::ArkValue<Opt_Length>(4.0_fp),
            .right = Converter::ArkValue<Opt_Length>(3.0_px),
            .bottom = Converter::ArkValue<Opt_Length>(1.0_vp),
        }
    };
    modifier_->setBorderWidth(node_, &width);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BORDER_WIDTH_NAME);
    EXPECT_EQ(strResult, "8.00%");

    Union_Union_Color_Number_String_Resource_EdgeColors_LocalizedEdgeColors color = {
        .selector = 0,
        .value0 = ArkUnion<Union_Color_Number_String_Resource, Ark_Color>(ARK_COLOR_ORANGE),
    };
    modifier_->setBorderColor(node_, &color);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BORDER_COLOR_NAME);
    EXPECT_EQ(strResult, "#FFFFA500");

    Union_Length_BorderRadiuses_LocalizedBorderRadiuses radius = {
        .selector = 1,
        .value1 = {
            .topLeft = Converter::ArkValue<Opt_Length>(8.0_pct),
            .topRight = Converter::ArkValue<Opt_Length>(7.0_px),
            .bottomRight = Converter::ArkValue<Opt_Length>(6.0_vp),
            .bottomLeft = Converter::ArkValue<Opt_Length>(5.0_fp),
        }
    };
    modifier_->setBorderRadius(node_, &radius);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BORDER_RADIUS_NAME);
    EXPECT_EQ(strResult, "{\"topLeft\":\"8.00%\",\"topRight\":\"7.00px\",\"bottomLeft\":\"5.00fp\","
                         "\"bottomRight\":\"6.00vp\"}");

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
                .value0 = Converter::ArkValue<Ark_Length>(1.0_pct),
            }
        }
    };
    modifier_->setBorderImage(node_, &image);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BORDER_IMAGE_NAME);
    EXPECT_EQ(strResult, "{\"source\":\"some_test_image.png\",\"slice\":\"4.00vp\",\"width\":\"1.00%\","
                         "\"outset\":\"3.00fp\",\"repeat\":\"RepeatMode.Space\",\"fill\":\"true\"}");
}

/*
 * @tc.name: setLinearGradient
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setLinearGradient, TestSize.Level1)
{
    Ark_CommonMethod_linearGradient_Object inputValue = {
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
        .colors = {
            .length = 3,
            .array = new Ark_CommonMethod_linearGradient_Object_colors_Param0_Tuple[] {
                {
                    ArkUnion<Union_Color_Number_String_Resource, Ark_Color>(ARK_COLOR_RED),
                    Converter::ArkValue<Ark_Number>(0.1f),
                },
                {
                    ArkUnion<Union_Color_Number_String_Resource, Ark_Color>(ARK_COLOR_GREEN),
                    Converter::ArkValue<Ark_Number>(0.5f),
                },
                {
                    ArkUnion<Union_Color_Number_String_Resource, Ark_Color>(ARK_COLOR_BLUE),
                    Converter::ArkValue<Ark_Number>(0.9f),
                }
            }
        }
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
HWTEST_F(CommonMethodModifierTest, setSweepGradient, TestSize.Level1)
{
    Ark_CommonMethod_sweepGradient_Object inputValue = {
        .center = {
            .value0 = Converter::ArkValue<Ark_Length>(30.0_pct),
            .value1 = Converter::ArkValue<Ark_Length>(42.0_pct),
        },
        .start = {
            .value = Converter::ArkUnion<Union_Number_String, Ark_String>("10vp")
        },
        .end = {
            .value = Converter::ArkUnion<Union_Number_String, Ark_String>("100.0%")
        },
        .rotation = {
            .value = Converter::ArkUnion<Union_Number_String, Ark_String>("45")
        },
        .repeating = Converter::ArkValue<Opt_Boolean>(true),
        .colors = {
            .length = 3,
            .array = new Ark_CommonMethod_sweepGradient_Object_colors_Param0_Tuple[] {
                {
                    ArkUnion<Union_Color_Number_String_Resource, Ark_Color>(ARK_COLOR_RED),
                    Converter::ArkValue<Ark_Number>(0.1f),
                },
                {
                    ArkUnion<Union_Color_Number_String_Resource, Ark_Color>(ARK_COLOR_GREEN),
                    Converter::ArkValue<Ark_Number>(0.5f),
                },
                {
                    ArkUnion<Union_Color_Number_String_Resource, Ark_Color>(ARK_COLOR_BLUE),
                    Converter::ArkValue<Ark_Number>(0.9f),
                }
            }
        }
    };
    modifier_->setSweepGradient(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_SWEEP_GRADIENT_NAME);
    EXPECT_EQ(strResult, "{\"center\":[\"30.00%\",\"42.00%\"],\"start\":\"10.00vp\",\"end\":\"100.00%\","
                         "\"colors\":[[\"#FFFF0000\",\"0.100000\"],[\"#FF008000\",\"0.500000\"],[\"#FF0000FF\","
                         "\"0.900000\"]],\"repeating\":\"true\"}");
}
} // namespace OHOS::Ace::NG

/*
 * @tc.name: set
 * @tc.desc:
 * @tc.type: FUNC
 */
// HWTEST_F(CommonMethodModifierTest, set, TestSize.Level1)
// {
//     Ark_ inputValue;
//     modifier_->set(node_, &inputValue);
//     auto strResult = GetStringAttribute(node_, ATTRIBUTE__NAME);
//     EXPECT_EQ(strResult, "");
// }
>>>>>>> e3b895f77c (Unit tests)
