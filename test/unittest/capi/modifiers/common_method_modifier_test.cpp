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
const int64_t FAKE_RES_ID(1234);
const int64_t FAKE_RES_ID_2(1235);
const auto OPT_VALID_NUM = Converter::ArkValue<Opt_Number>(VALID_NUMBER);
const auto OPT_INVALID_NUM = Converter::ArkValue<Opt_Number>(INVALID_NUMBER);
const auto OPT_UNDEF_NUM = Converter::ArkValue<Opt_Number>();
const auto OPT_EMPTY_STR = Converter::ArkValue<Opt_String>("");
const auto ARK_EMPTY_STR = Converter::ArkValue<Ark_String>("");
const auto RES_OPT_LENGTH = Converter::ArkValue<Opt_Length>(FAKE_RES_ID);
const auto RES_ARK_LENGTH = Converter::ArkValue<Ark_Length>(FAKE_RES_ID);
const auto RES_ARK_DIMENSION = Converter::ArkValue<Ark_Dimension>(FAKE_RES_ID_2);
const auto ATTRIBUTE_WIDTH_NAME = "width";
const auto ATTRIBUTE_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_HEIGHT_NAME = "height";
const auto ATTRIBUTE_HEIGHT_DEFAULT_VALUE = "0.00vp";
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

static const std::vector<std::pair<Ark_Dimension, std::string>> DIMENSION_TEST_PLAN = {
    { Converter::ArkUnion<Ark_Dimension, Ark_Number>(2.45f), "2.45vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_Number>(0.0f), "0.00vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_Number>(-2.45f), "-2.45vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("5.0px"), "5.00px" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("-5.0px"), "-5.00px" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("22.35px"), "22.35px" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("-22.35px"), "-22.35px" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("7.0vp"), "7.00vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("-7.0vp"), "-7.00vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("1.65vp"), "1.65vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("-1.65vp"), "-1.65vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("65.0fp"), "65.00fp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("-65.0fp"), "-65.00fp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("4.3fp"), "4.30fp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("-4.3fp"), "-4.30fp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("12.00%"), "12.00%" },
    { RES_ARK_DIMENSION, "10.00px" },
};

static const std::vector<std::pair<Ark_Length, std::string>> LENGTH_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(2.45), "2.45vp" },
    { Converter::ArkValue<Ark_Length>(0.0), "0.00vp" },
    { Converter::ArkValue<Ark_Length>(-2.45), "-2.45vp" },
    { Converter::ArkValue<Ark_Length>("5.0px"), "5.00px" },
    { Converter::ArkValue<Ark_Length>("-5.0px"), "-5.00px" },
    { Converter::ArkValue<Ark_Length>("22.35px"), "22.35px" },
    { Converter::ArkValue<Ark_Length>("-22.35px"), "-22.35px" },
    { Converter::ArkValue<Ark_Length>("7.0vp"), "7.00vp" },
    { Converter::ArkValue<Ark_Length>("-7.0vp"), "-7.00vp" },
    { Converter::ArkValue<Ark_Length>("1.65vp"), "1.65vp" },
    { Converter::ArkValue<Ark_Length>("-1.65vp"), "-1.65vp" },
    { Converter::ArkValue<Ark_Length>("65.0fp"), "65.00fp" },
    { Converter::ArkValue<Ark_Length>("-65.0fp"), "-65.00fp" },
    { Converter::ArkValue<Ark_Length>("4.3fp"), "4.30fp" },
    { Converter::ArkValue<Ark_Length>("-4.3fp"), "-4.30fp" },
    { Converter::ArkValue<Ark_Length>("12.00%"), "12.00%" },
    { Converter::ArkValue<Ark_Length>("-12.00%"), "-12.00%" },
    { RES_ARK_LENGTH, "10.00px" },
};

static const std::vector<std::pair<Ark_Length, std::string>> PADDING_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
    { Converter::ArkValue<Ark_Length>(0.0), "0.00vp" },
    { Converter::ArkValue<Ark_Length>(-2.45f), ATTRIBUTE_PADDING_DEFAULT_VALUE },
    { Converter::ArkValue<Ark_Length>("5.0px"), "5.00px" },
    { Converter::ArkValue<Ark_Length>("-5.0px"), ATTRIBUTE_PADDING_DEFAULT_VALUE },
    { Converter::ArkValue<Ark_Length>("22.35px"), "22.35px" },
    { Converter::ArkValue<Ark_Length>("-22.35px"), ATTRIBUTE_PADDING_DEFAULT_VALUE },
    { Converter::ArkValue<Ark_Length>("7.0vp"), "7.00vp" },
    { Converter::ArkValue<Ark_Length>("-7.0vp"), ATTRIBUTE_PADDING_DEFAULT_VALUE },
    { Converter::ArkValue<Ark_Length>("1.65vp"), "1.65vp" },
    { Converter::ArkValue<Ark_Length>("-1.65vp"), ATTRIBUTE_PADDING_DEFAULT_VALUE },
    { Converter::ArkValue<Ark_Length>("65.0fp"), "65.00fp" },
    { Converter::ArkValue<Ark_Length>("-65.0fp"), ATTRIBUTE_PADDING_DEFAULT_VALUE },
    { Converter::ArkValue<Ark_Length>("12.00%"), "12.00%" },
    { RES_ARK_LENGTH, "10.00px" },
};

typedef std::pair<Opt_Union_F64_String, std::string> ScaleTranslateTestStep;
static const std::vector<ScaleTranslateTestStep> SCALE_TRANSLATE_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(1.0f), "1.00vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(-2.5f), "-2.50vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(0.0f), "0.00vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("1.00px"), "1.00px" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("0.00px"), "0.00px" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("2.45vp"), "2.45vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("5.00px"), "5.00px" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("-22.35px"), "-22.35px" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("7.00vp"), "7.00vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("1.65vp"), "1.65vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("65.00fp"), "65.00fp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("4.30fp"), "4.30fp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("12.00%"), "12.00%" },
};

using LengthMetrictsTestStep = std::pair<Ark_LengthMetrics, std::string>;
static const std::vector<LengthMetrictsTestStep> LENGTH_METRICS_ANY_TEST_PLAN = {
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_PX, 1.f), "1.00px" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_PX, 0.f), "0.00px" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_VP, 2.45f), "2.45vp" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_VP, -7.f), "-7.00vp" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_FP, -65.5f), "-65.50fp" },
};
} // namespace

class CommonMethodModifierTest : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_COLUMN // test common methods on frameNode for Column component
    > {
public:
    RefPtr<RenderContext> render_;

    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getColumnModifier()->construct(GetId(), 0);
    }

    void SetUp() override
    {
        ModifierTestBase::SetUp();
        auto fnode = reinterpret_cast<FrameNode *>(node_);
        ASSERT_NE(fnode, nullptr);
        render_ = fnode->GetRenderContext();
        ASSERT_NE(render_, nullptr);
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
    void UpdateFrameNode()
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node_);
        ASSERT_NE(frameNode, nullptr);
        frameNode->MarkModifyDone();
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
        { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Ark_Length>("5.0px"), "5.00px" },
        { Converter::ArkValue<Ark_Length>("22.35px"), "22.35px" },
        { Converter::ArkValue<Ark_Length>("7.0vp"), "7.00vp" },
        { Converter::ArkValue<Ark_Length>("1.65vp"), "1.65vp" },
        { Converter::ArkValue<Ark_Length>("65.0fp"), "65.00fp" },
        { Converter::ArkValue<Ark_Length>("4.3fp"), "4.30fp" },
        { Converter::ArkValue<Ark_Length>("12.00%"), "12.00%" },
        { RES_ARK_LENGTH, "10.00px" },
    };

    for (const auto &[value, expected]: testPlan) {
        auto inputValue = Converter::ArkUnion<Opt_Union_Length_LayoutPolicy, Ark_Length>(value);
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
        Converter::ArkValue<Ark_Length>(-2.45f),
        Converter::ArkValue<Ark_Length>("-5.0px"),
        Converter::ArkValue<Ark_Length>("-22.35px"),
        Converter::ArkValue<Ark_Length>("-7.0vp"),
        Converter::ArkValue<Ark_Length>("-1.65vp"),
        Converter::ArkValue<Ark_Length>("-65.0fp"),
        Converter::ArkValue<Ark_Length>("-4.3fp"),
    };

    for (const auto &value : testPlan) {
        auto inputValue = Converter::ArkUnion<Opt_Union_Length_LayoutPolicy, Ark_Length>(value);
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
        { Converter::ArkValue<Ark_Length>("5.0px"), "5.00px" },
        { Converter::ArkValue<Ark_Length>("22.35px"), "22.35px" },
        { Converter::ArkValue<Ark_Length>("7.0vp"), "7.00vp" },
        { Converter::ArkValue<Ark_Length>("1.65vp"), "1.65vp" },
        { Converter::ArkValue<Ark_Length>("65.0fp"), "65.00fp" },
        { Converter::ArkValue<Ark_Length>("4.3fp"), "4.30fp" },
        { Converter::ArkValue<Ark_Length>("12.00%"), "12.00%" },
        { RES_ARK_LENGTH, "10.00px" },
    };

    for (const auto &[value, expected]: testPlan) {
        auto inputValue = Converter::ArkUnion<Opt_Union_Length_LayoutPolicy, Ark_Length>(value);
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
        Converter::ArkValue<Ark_Length>(-2.45f),
        Converter::ArkValue<Ark_Length>("-5.0px"),
        Converter::ArkValue<Ark_Length>("-22.35px"),
        Converter::ArkValue<Ark_Length>("-7.0vp"),
        Converter::ArkValue<Ark_Length>("-1.65vp"),
        Converter::ArkValue<Ark_Length>("-65.0fp"),
        Converter::ArkValue<Ark_Length>("-4.3fp"),
    };

    for (const auto &value : testPlan) {
        auto inputValue = Converter::ArkUnion<Opt_Union_Length_LayoutPolicy, Ark_Length>(value);
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
    typedef std::pair<Opt_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Opt_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Opt_Length>("5.0px"), "5.00px" },
        { Converter::ArkValue<Opt_Length>("22.35px"), "22.35px" },
        { Converter::ArkValue<Opt_Length>("7.0vp"), "7.00vp" },
        { Converter::ArkValue<Opt_Length>("1.65vp"), "1.65vp" },
        { Converter::ArkValue<Opt_Length>("65.0fp"), "65.00fp" },
        { Converter::ArkValue<Opt_Length>("4.3fp"), "4.30fp" },
        { Converter::ArkValue<Opt_Length>("12.00%"), "12.00%" },
        { RES_OPT_LENGTH, "10.00px" },
    };
    const auto optWidth = Converter::ArkValue<Opt_Length>(Ark_Empty());
    Opt_SizeOptions inputValue;

    for (const auto &[optLength, expected]: testPlan) {
        inputValue = Converter::ArkValue<Opt_SizeOptions>(Ark_SizeOptions{.height = optLength, .width = optWidth});
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
    typedef std::pair<Opt_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Opt_Length>(2.45f), "2.45vp" },
        { Converter::ArkValue<Opt_Length>("5.0px"), "5.00px" },
        { Converter::ArkValue<Opt_Length>("22.35px"), "22.35px" },
        { Converter::ArkValue<Opt_Length>("7.0vp"), "7.00vp" },
        { Converter::ArkValue<Opt_Length>("1.65vp"), "1.65vp" },
        { Converter::ArkValue<Opt_Length>("65.0fp"), "65.00fp" },
        { Converter::ArkValue<Opt_Length>("4.3fp"), "4.30fp" },
        { Converter::ArkValue<Opt_Length>("12.00%"), "12.00%" },
        { RES_OPT_LENGTH, "10.00px" },
    };

    const auto optHeight = Converter::ArkValue<Opt_Length>(Ark_Empty());
    Opt_SizeOptions inputValue;

    for (const auto &[optWidth, expected]: testPlan) {
        inputValue = Converter::ArkValue<Opt_SizeOptions>(Ark_SizeOptions{.height = optHeight, .width = optWidth});
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
    static const std::vector<Opt_Length> testPlan = {
        Converter::ArkValue<Opt_Length>(-2.45f),
        Converter::ArkValue<Opt_Length>("-5.0px"),
        Converter::ArkValue<Opt_Length>("-22.35px"),
        Converter::ArkValue<Opt_Length>("-7.0vp"),
        Converter::ArkValue<Opt_Length>("-1.65vp"),
        Converter::ArkValue<Opt_Length>("-65.0fp"),
        Converter::ArkValue<Opt_Length>("-4.3fp"),
    };

    const auto optWidth = Converter::ArkValue<Opt_Length>(Ark_Empty());
    Opt_SizeOptions inputValue;

    for (const auto &optLength : testPlan) {
        inputValue = Converter::ArkValue<Opt_SizeOptions>(Ark_SizeOptions{.height = optLength, .width = optWidth});
        modifier_->setSize(node_, &inputValue);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_WIDTH_DEFAULT_VALUE);
        strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
        EXPECT_EQ(strResult, ATTRIBUTE_HEIGHT_DEFAULT_VALUE);
    }

    for (const auto &optHeight : testPlan) {
        inputValue = Converter::ArkValue<Opt_SizeOptions>(Ark_SizeOptions{.height = optHeight, .width = optWidth});
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setSharedTransitionTestId, TestSize.Level1)
{
    ASSERT_NE(modifier_->setSharedTransition, nullptr);

    // initial
    EXPECT_EQ(render_->GetShareId(), "");
    EXPECT_EQ(GetTransition(), nullptr);

    // verify valid
    auto inputValueOptions = ArkValue<Opt_String>("abc");
    modifier_->setSharedTransition(node_, &inputValueOptions, nullptr);
    EXPECT_EQ(render_->GetShareId(), "abc");

    // verify nullptr - expect nothing changes
    modifier_->setSharedTransition(node_, nullptr, nullptr);
    EXPECT_EQ(render_->GetShareId(), "abc");

    // verify empty
    modifier_->setSharedTransition(node_, &OPT_EMPTY_STR, nullptr);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setSharedTransitionTestOptionsCurveType, TestSize.Level1)
{
    const auto nameDefaultCurve = Framework::CreateCurve(ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR)->ToString();
    auto realInputValue = Converter::ArkValue<Opt_sharedTransitionOptions>(Ark_sharedTransitionOptions{});
    auto& inputOptionCurveValue = realInputValue.value.curve;

    ASSERT_NE(modifier_->setSharedTransition, nullptr);

    // initial
    auto transition = GetTransition();
    EXPECT_EQ(transition, nullptr);

    // verify valid type
    inputOptionCurveValue = ArkUnion<Opt_Union_curves_Curve_String_curves_ICurve, Ark_curves_Curve>(
        ARK_CURVES_CURVE_EASE_IN);
    modifier_->setSharedTransition(node_, &OPT_EMPTY_STR, &realInputValue);
    transition = GetTransition();
    ASSERT_TRUE(transition && transition->curve);
    auto nameCurveEasyIn = Framework::CreateCurve(ArkUI_AnimationCurve::ARKUI_CURVE_EASE_IN)->ToString();
    EXPECT_EQ(transition->curve->ToString(), nameCurveEasyIn);

    // verify invalid type - expect default
    inputOptionCurveValue = ArkUnion<Opt_Union_curves_Curve_String_curves_ICurve, Ark_curves_Curve>(
        static_cast<Ark_curves_Curve>(INT_MIN));
    modifier_->setSharedTransition(node_, &OPT_EMPTY_STR, &realInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setSharedTransitionTestOptionsCurveCustom, TestSize.Level1)
{
    const auto nameDefaultCurve = Framework::CreateCurve(ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR)->ToString();
    auto realInputValue = Converter::ArkValue<Opt_sharedTransitionOptions>(Ark_sharedTransitionOptions{});
    auto& inputOptionCurveValue = realInputValue.value.curve;

    ASSERT_NE(modifier_->setSharedTransition, nullptr);

    // initial
    auto transition = GetTransition();
    EXPECT_EQ(transition, nullptr);

    // verify valid custom
    inputOptionCurveValue =
        ArkUnion<Opt_Union_curves_Curve_String_curves_ICurve, Ark_String>("interpolating-spring(1, 1, 28, 34)");
    modifier_->setSharedTransition(node_, &OPT_EMPTY_STR, &realInputValue);
    transition = GetTransition();
    ASSERT_TRUE(transition && transition->curve);
    // this can't be exactly check due to SwiperPaintProperty::ToJsonValue supports the built-in Curves only
    EXPECT_NE(transition->curve->ToString(), nameDefaultCurve);

    // verify invalid custom - expect default
    inputOptionCurveValue =
        ArkUnion<Opt_Union_curves_Curve_String_curves_ICurve, Ark_String>("invalidCurveDefinition");
    modifier_->setSharedTransition(node_, &OPT_EMPTY_STR, &realInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setSharedTransitionTestOptionsCurveUndef, TestSize.Level1)
{
    const auto nameDefaultCurve = Framework::CreateCurve(ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR)->ToString();
    auto realInputValue = Converter::ArkValue<Opt_sharedTransitionOptions>(Ark_sharedTransitionOptions{});
    auto& inputOptionCurveValue = realInputValue.value.curve;

    ASSERT_NE(modifier_->setSharedTransition, nullptr);

    // initial
    EXPECT_EQ(GetTransition(), nullptr);

    // verify undef Curve - expect default
    inputOptionCurveValue = ArkUnion<Opt_Union_curves_Curve_String_curves_ICurve>(Ark_Empty());
    modifier_->setSharedTransition(node_, &OPT_EMPTY_STR, &realInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setSharedTransitionTestOptionsPath, TestSize.Level1)
{
    auto realInputValue = Converter::ArkValue<Opt_sharedTransitionOptions>(Ark_sharedTransitionOptions{});
    realInputValue.value.motionPath = Converter::ArkValue<Opt_MotionPathOptions>(Ark_MotionPathOptions{});
    auto& inputMotionPathValue = realInputValue.value.motionPath.value;

    ASSERT_NE(modifier_->setSharedTransition, nullptr);

    // initial
    EXPECT_EQ(GetTransition(), nullptr);

    // verify valid
    inputMotionPathValue = {
        .path = ArkValue<Ark_String>("abc"),
        .from = ArkValue<Opt_Float64>(123),
        .to = ArkValue<Opt_Float64>(-987.654f),
        .rotatable = ArkValue<Opt_Boolean>(true),
    };
    modifier_->setSharedTransition(node_, &OPT_EMPTY_STR, &realInputValue);
    auto transition = GetTransition();
    ASSERT_TRUE(transition);
    EXPECT_EQ(transition->motionPathOption.GetPath(), "abc");
    EXPECT_FLOAT_EQ(transition->motionPathOption.GetBegin(), 123.0f);
    EXPECT_FLOAT_EQ(transition->motionPathOption.GetEnd(), -987.654f);
    EXPECT_EQ(transition->motionPathOption.GetRotate(), true);

    // verify empty/undefined
    inputMotionPathValue = {
        .path = ARK_EMPTY_STR,
        .from = ArkValue<Opt_Float64>(),
        .to = ArkValue<Opt_Float64>(),
        .rotatable = ArkValue<Opt_Boolean>(),
    };
    modifier_->setSharedTransition(node_, &OPT_EMPTY_STR, &realInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setSharedTransitionTestOptionsOtherArgs, TestSize.Level1)
{
    auto realInputValue = Converter::ArkValue<Opt_sharedTransitionOptions>(Ark_sharedTransitionOptions{});
    Ark_sharedTransitionOptions& inputValueOptions = realInputValue.value;

    ASSERT_NE(modifier_->setSharedTransition, nullptr);

    // initial
    auto transition = GetTransition();
    EXPECT_EQ(transition, nullptr);

    const int32_t testDelay = 123;
    const int32_t testDuration = 456;
    const int32_t testIndex = 789;
    const auto testType = ARK_SHARED_TRANSITION_EFFECT_TYPE_STATIC;

    // verify valid values
    inputValueOptions.delay = Converter::ArkValue<Opt_Int32>(testDelay);
    inputValueOptions.duration = Converter::ArkValue<Opt_Int32>(testDuration);
    inputValueOptions.zIndex = Converter::ArkValue<Opt_Int32>(testIndex);
    inputValueOptions.type = ArkValue<Opt_SharedTransitionEffectType>(testType);
    modifier_->setSharedTransition(node_, &OPT_EMPTY_STR, &realInputValue);
    transition = GetTransition();
    ASSERT_NE(transition, nullptr);
    EXPECT_EQ(transition->duration, testDuration);
    EXPECT_EQ(transition->delay, testDelay);
    EXPECT_EQ(transition->zIndex, testIndex);
    EXPECT_EQ(transition->type, SharedTransitionEffectType::SHARED_EFFECT_STATIC);

    // verify undefined values - expect default
    inputValueOptions.delay = Converter::ArkValue<Opt_Int32>();
    inputValueOptions.duration = Converter::ArkValue<Opt_Int32>();
    inputValueOptions.zIndex = Converter::ArkValue<Opt_Int32>();
    inputValueOptions.type = ArkValue<Opt_SharedTransitionEffectType>(Ark_Empty());
    modifier_->setSharedTransition(node_, &OPT_EMPTY_STR, &realInputValue);
    transition = GetTransition();
    ASSERT_NE(transition, nullptr);
    EXPECT_EQ(transition->duration, CommonAnimationStyle::DEFAULT_ANIMATION_DURATION);
    EXPECT_EQ(transition->delay, 0);
    EXPECT_EQ(transition->zIndex, 0);
    EXPECT_EQ(transition->type, SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE);

    // verify invalid values - expect default
    inputValueOptions.delay = Converter::ArkValue<Opt_Int32>(-1);
    inputValueOptions.duration = Converter::ArkValue<Opt_Int32>(-1);
    inputValueOptions.zIndex = Converter::ArkValue<Opt_Int32>(-1);
    inputValueOptions.type =
        ArkValue<Opt_SharedTransitionEffectType>(static_cast<SharedTransitionEffectType>(INT_MIN));
    modifier_->setSharedTransition(node_, &OPT_EMPTY_STR, &realInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setBackgroundColorTest, TestSize.Level1)
{
    static const std::string PROP_NAME("backgroundColor");
    const auto RES_NAME = NamedResourceId{"aa.bb.cc", ResourceType::COLOR};
    const auto RES_ID = IntResourceId{11111, ResourceType::COLOR};
    static const std::string EXPECTED_RESOURCE_COLOR =
        Color::RED.ToString(); // Color::RED is result of ThemeConstants::GetColorXxxx stubs
    using TestInpType = Ark_ResourceColor;
    static const std::vector<std::pair<TestInpType, std::string>> testPlan = {
        { ArkUnion<TestInpType, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE), "#FFFFFFFF" },
        { ArkUnion<TestInpType, Ark_Int32>(0x123456), "#FF123456" },
        { ArkUnion<TestInpType, Ark_String>("#11223344"), "#11223344" },
        { ArkUnion<TestInpType, Ark_String>("65535"), "#FF00FFFF" },
        { CreateResourceUnion<TestInpType>(RES_NAME), EXPECTED_RESOURCE_COLOR },
        { CreateResourceUnion<TestInpType>(RES_ID), EXPECTED_RESOURCE_COLOR },
    };

    ASSERT_NE(modifier_->setBackgroundColor, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, Color::TRANSPARENT.ToString());

    for (const auto &[resColor, expected]: testPlan) {
        auto inputVal = ArkUnion<Opt_Union_ResourceColor_ColorMetrics, Ark_ResourceColor>(resColor);
        modifier_->setBackgroundColor(node_, &inputVal);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setMarginTestValidLengthValues, TestSize.Level1)
{
    std::string strResult;
    for (const auto &[optMargin, expected]: LENGTH_TEST_PLAN) {
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Length>(optMargin);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setMarginTestValidLeftLengthValues, TestSize.Level1)
{
    Ark_Padding inputValue;
    for (const auto &[arkMargin, expected]: LENGTH_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(arkMargin);
        inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setMarginTestValidTopLengthValues, TestSize.Level1)
{
    Ark_Padding inputValue;
    for (const auto &[arkMargin, expected]: LENGTH_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.top = Converter::ArkValue<Opt_Length>(arkMargin);
        inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setMarginTestValidTopRightValues, TestSize.Level1)
{
    Ark_Padding inputValue;
    for (const auto &[arkMargin, expected]: LENGTH_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.right = Converter::ArkValue<Opt_Length>(arkMargin);
        inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setMarginTestValidBottomLengthValues, TestSize.Level1)
{
    Ark_Padding inputValue;
    for (const auto &[arkMargin, expected]: LENGTH_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.bottom = Converter::ArkValue<Opt_Length>(arkMargin);
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);
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
    ASSERT_NE(modifier_->setDirection, nullptr);
    ASSERT_NE(modifier_->setMargin, nullptr);

    Ark_LocalizedPadding inputValue;
    auto optDirection = Converter::ArkValue<Opt_Direction>(ARK_DIRECTION_LTR);
    modifier_->setDirection(node_, &optDirection);
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_LocalizedPadding>(inputValue);
        modifier_->setMargin(node_, &value);

        UpdateFrameNode(); // apply localized values

        auto strResult = GetStringAttribute(node_, ATTRIBUTE_MARGIN_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), expected);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), ATTRIBUTE_MARGIN_DEFAULT_VALUE);
    }

    optDirection = Converter::ArkValue<Opt_Direction>(ARK_DIRECTION_RTL);
    modifier_->setDirection(node_, &optDirection);
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_LocalizedPadding>(inputValue);
        modifier_->setMargin(node_, &value);

        UpdateFrameNode(); // apply localized values

        auto strResult = GetStringAttribute(node_, ATTRIBUTE_MARGIN_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), ATTRIBUTE_MARGIN_DEFAULT_VALUE);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), expected);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), ATTRIBUTE_MARGIN_DEFAULT_VALUE);
    }
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
    for (const auto &[arkPadding, expected]: PADDING_TEST_PLAN) {
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Length>(arkPadding);
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
    for (const auto &[arkPadding, expected]: PADDING_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(arkPadding);
        inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);
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
    for (const auto &[arkPadding, expected]: PADDING_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.top = Converter::ArkValue<Opt_Length>(arkPadding);
        inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);
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
    for (const auto &[arkPadding, expected]: PADDING_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.right = Converter::ArkValue<Opt_Length>(arkPadding);
        inputValue.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);
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
    for (const auto &[arkPadding, expected]: PADDING_TEST_PLAN) {
        inputValue.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue.bottom = Converter::ArkValue<Opt_Length>(arkPadding);
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_Padding>(inputValue);
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
    ASSERT_NE(modifier_->setDirection, nullptr);
    ASSERT_NE(modifier_->setPadding, nullptr);

    Ark_LocalizedPadding inputValue;
    auto optDirection = Converter::ArkValue<Opt_Direction>(ARK_DIRECTION_LTR);
    modifier_->setDirection(node_, &optDirection);
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_LocalizedPadding>(inputValue);
        modifier_->setPadding(node_, &value);

        UpdateFrameNode(); // apply localized values

        auto strResult = GetStringAttribute(node_, ATTRIBUTE_PADDING_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), expected);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), ATTRIBUTE_PADDING_DEFAULT_VALUE);
    }

    optDirection = Converter::ArkValue<Opt_Direction>(ARK_DIRECTION_RTL);
    modifier_->setDirection(node_, &optDirection);
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        auto value = Converter::ArkUnion<Opt_Union_Padding_Length_LocalizedPadding, Ark_LocalizedPadding>(inputValue);
        modifier_->setPadding(node_, &value);

        UpdateFrameNode(); // apply localized values

        auto strResult = GetStringAttribute(node_, ATTRIBUTE_PADDING_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), ATTRIBUTE_PADDING_DEFAULT_VALUE);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), expected);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), ATTRIBUTE_PADDING_DEFAULT_VALUE);
    }
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
        position.x = Converter::ArkValue<Opt_Length>(arkLength);
        position.y = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Position>(position);
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
        position.y = Converter::ArkValue<Opt_Length>(arkLength);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Position>(position);
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
    for (const auto &[arkValue, expected]: DIMENSION_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Dimension>(arkValue);
        edges.top = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.right = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.bottom = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
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
    for (const auto &[arkValue, expected]: DIMENSION_TEST_PLAN) {
        edges.left = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.top = Converter::ArkValue<Opt_Dimension>(arkValue);
        edges.right = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.bottom = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
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
    for (const auto &[arkValue, expected]: DIMENSION_TEST_PLAN) {
        edges.left = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.top = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.right = Converter::ArkValue<Opt_Dimension>(arkValue);
        edges.bottom = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
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
    for (const auto &[arkValue, expected]: DIMENSION_TEST_PLAN) {
        edges.left = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.top = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.right = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.bottom = Converter::ArkValue<Opt_Dimension>(arkValue);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
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
 * @tc.name: setOffsetTestValidLocalizedEdgesValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setOffsetTestValidLocalizedEdgesValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDirection, nullptr);
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string ATTRIBUTE_OFFSET_DEFAULT_VALUE{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    auto optDirection = Converter::ArkValue<Opt_Direction>(ARK_DIRECTION_LTR);
    modifier_->setDirection(node_, &optDirection);
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.start = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
        modifier_->setOffset(node_, &value);
        UpdateFrameNode(); // apply localized values
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), expected);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), ATTRIBUTE_OFFSET_DEFAULT_VALUE);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), ATTRIBUTE_OFFSET_DEFAULT_VALUE);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), ATTRIBUTE_OFFSET_DEFAULT_VALUE);
    }
    optDirection = Converter::ArkValue<Opt_Direction>(ARK_DIRECTION_RTL);
    modifier_->setDirection(node_, &optDirection);
    inputValue = { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.start = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
        modifier_->setOffset(node_, &value);
        UpdateFrameNode(); // apply localized values
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), ATTRIBUTE_OFFSET_DEFAULT_VALUE);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), ATTRIBUTE_OFFSET_DEFAULT_VALUE);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), expected);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), ATTRIBUTE_OFFSET_DEFAULT_VALUE);
    }
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setRadialGradientTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_RadialGradientOptions inputValue;

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>("2.0vp");
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>("3.0vp");
    // radius
    inputValue.radius = Converter::ArkValue<Ark_Length>("4vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(true);
    // color stops
    std::vector<ColorStep> colorSteps {
        { ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE), 0.1 },
        { ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), 0.25 },
        { ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), 0.5 },
    };
    inputValue.colors = Converter::ArkValue<Array_Tuple_ResourceColor_F64>(colorSteps, Converter::FC);
    auto optInputValue = Converter::ArkValue<Opt_RadialGradientOptions>(inputValue);

    // check value
    modifier_->setRadialGradient(node_, &optInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setRadialGradientRadiusTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_RadialGradientOptions inputValue;
    Opt_RadialGradientOptions optInputValue;

    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>("5px"), "5.00px" },
        { Converter::ArkValue<Ark_Length>("22.35px"), "22.35px" },
        { Converter::ArkValue<Ark_Length>("7vp"), "7.00vp" },
        { Converter::ArkValue<Ark_Length>("1.65vp"), "1.65vp" },
        { Converter::ArkValue<Ark_Length>("65fp"), "65.00fp" },
        { Converter::ArkValue<Ark_Length>("4.3fp"), "4.30fp" },
    };

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>("2.0vp");
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>("3.0vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    // color stops
    std::vector<ColorStep> colorSteps {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#112233"), 0.5 },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#223344"), 0.9 },
    };
    inputValue.colors = Converter::ArkValue<Array_Tuple_ResourceColor_F64>(colorSteps, Converter::FC);

    // check value
    for (const auto &[arkRadius, expected]: testPlan) {
        inputValue.radius = arkRadius;
        optInputValue = Converter::ArkValue<Opt_RadialGradientOptions>(inputValue);
        modifier_->setRadialGradient(node_, &optInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setRadialGradientRadiusTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_RadialGradientOptions inputValue;
    Opt_RadialGradientOptions optInputValue;

    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>("-5px"), "0.00vp" },
        { Converter::ArkValue<Ark_Length>("-22.35px"), "0.00vp" },
        { Converter::ArkValue<Ark_Length>("-7vp"), "0.00vp" },
        { Converter::ArkValue<Ark_Length>("-1.65vp"), "0.00vp" },
        { Converter::ArkValue<Ark_Length>("-65fp"), "0.00vp" },
        { Converter::ArkValue<Ark_Length>("-4.3fp"), "0.00vp" },
    };

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>("2.0vp");
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>("3.0vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    // color stops
    std::vector<ColorStep> colorSteps {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#112233"), 0.5 },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#223344"), 0.9 },
    };
    inputValue.colors = Converter::ArkValue<Array_Tuple_ResourceColor_F64>(colorSteps, Converter::FC);

    // check value
    for (const auto &[arkRadius, expected]: testPlan) {
        inputValue.radius = arkRadius;
        optInputValue = Converter::ArkValue<Opt_RadialGradientOptions>(inputValue);
        modifier_->setRadialGradient(node_, &optInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setRadialGradientCenter1TestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_RadialGradientOptions inputValue;
    Opt_RadialGradientOptions optInputValue;

    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(2.45f), "[\"2.45vp\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>(-2.45f), "[\"-2.45vp\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("5.0px"), "[\"5.00px\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("-5.0px"), "[\"-5.00px\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("22.35px"), "[\"22.35px\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("-22.35px"), "[\"-22.35px\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("7.0vp"), "[\"7.00vp\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("-7.0vp"), "[\"-7.00vp\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("1.65vp"), "[\"1.65vp\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("-1.65vp"), "[\"-1.65vp\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("65.0fp"), "[\"65.00fp\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("-65.0fp"), "[\"-65.00fp\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("4.3fp"), "[\"4.30fp\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("-4.3fp"), "[\"-4.30fp\",\"0.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("10.00%"), "[\"1000.00%\",\"0.00vp\"]" },
        { RES_ARK_LENGTH, "[\"10.00px\",\"0.00vp\"]" },
    };

    // radius
    inputValue.radius = Converter::ArkValue<Ark_Length>("4vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    // color stops
    std::vector<ColorStep> colorSteps {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#112233"), 0.5 },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#223344"), 0.9 },
    };
    inputValue.colors = Converter::ArkValue<Array_Tuple_ResourceColor_F64>(colorSteps, Converter::FC);

    // check value
    for (const auto &[arkCenter, expected]: testPlan) {
        // center
        inputValue.center.value0 = arkCenter;
        inputValue.center.value1 = Converter::ArkValue<Ark_Length>(0.);
        optInputValue = Converter::ArkValue<Opt_RadialGradientOptions>(inputValue);
        modifier_->setRadialGradient(node_, &optInputValue);
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
    Ark_RadialGradientOptions inputValue;
    Opt_RadialGradientOptions optInputValue;

    typedef std::pair<Ark_Length, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(2.45f), "[\"0.00vp\",\"2.45vp\"]" },
        { Converter::ArkValue<Ark_Length>(-2.45f), "[\"0.00vp\",\"-2.45vp\"]" },
        { Converter::ArkValue<Ark_Length>("5.0px"), "[\"0.00vp\",\"5.00px\"]" },
        { Converter::ArkValue<Ark_Length>("-5.0px"), "[\"0.00vp\",\"-5.00px\"]" },
        { Converter::ArkValue<Ark_Length>("22.35px"), "[\"0.00vp\",\"22.35px\"]" },
        { Converter::ArkValue<Ark_Length>("-22.35px"), "[\"0.00vp\",\"-22.35px\"]" },
        { Converter::ArkValue<Ark_Length>("7.0vp"), "[\"0.00vp\",\"7.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("-7.0vp"), "[\"0.00vp\",\"-7.00vp\"]" },
        { Converter::ArkValue<Ark_Length>("1.65vp"), "[\"0.00vp\",\"1.65vp\"]" },
        { Converter::ArkValue<Ark_Length>("-1.65vp"), "[\"0.00vp\",\"-1.65vp\"]" },
        { Converter::ArkValue<Ark_Length>("65.0fp"), "[\"0.00vp\",\"65.00fp\"]" },
        { Converter::ArkValue<Ark_Length>("-65.0fp"), "[\"0.00vp\",\"-65.00fp\"]" },
        { Converter::ArkValue<Ark_Length>("4.3fp"), "[\"0.00vp\",\"4.30fp\"]" },
        { Converter::ArkValue<Ark_Length>("-4.3fp"), "[\"0.00vp\",\"-4.30fp\"]" },
        { Converter::ArkValue<Ark_Length>("10.00%"), "[\"0.00vp\",\"1000.00%\"]" },
        { RES_ARK_LENGTH, "[\"0.00vp\",\"10.00px\"]" },
    };

    // radius
    inputValue.radius = Converter::ArkValue<Ark_Length>("4vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    // color stops
    std::vector<ColorStep> colorSteps {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#112233"), 0.5 },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#223344"), 0.9 },
    };
    inputValue.colors = Converter::ArkValue<Array_Tuple_ResourceColor_F64>(colorSteps, Converter::FC);

    // check value
    for (const auto &[arkCenter, expected]: testPlan) {
        // center
        inputValue.center.value0 = Converter::ArkValue<Ark_Length>(0.);
        inputValue.center.value1 = arkCenter;
        optInputValue = Converter::ArkValue<Opt_RadialGradientOptions>(inputValue);
        modifier_->setRadialGradient(node_, &optInputValue);
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
    Ark_RadialGradientOptions inputValue;
    Opt_RadialGradientOptions optInputValue;

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>("2.0vp");
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>("3.0vp");
    // radius
    inputValue.radius = Converter::ArkValue<Ark_Length>("4vp");
    // color stops
    std::vector<ColorStep> colorSteps {
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#112233"), 0.5 },
        { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#223344"), 0.9 },
    };
    inputValue.colors = Converter::ArkValue<Array_Tuple_ResourceColor_F64>(colorSteps, Converter::FC);

    // check undefined repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    optInputValue = Converter::ArkValue<Opt_RadialGradientOptions>(inputValue);
    modifier_->setRadialGradient(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
    auto repeatingResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_REPEATING_NAME);
    EXPECT_EQ(repeatingResult, "false");

    // check true repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(true);
    optInputValue = Converter::ArkValue<Opt_RadialGradientOptions>(inputValue);
    modifier_->setRadialGradient(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
    repeatingResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_REPEATING_NAME);
    EXPECT_EQ(repeatingResult, "true");

    // check false repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(false);
    optInputValue = Converter::ArkValue<Opt_RadialGradientOptions>(inputValue);
    modifier_->setRadialGradient(node_, &optInputValue);
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
    Ark_RadialGradientOptions inputValue;
    Opt_RadialGradientOptions optInputValue;
    const auto RES_NAME = NamedResourceId{"aa.bb.cc", ResourceType::COLOR};
    const auto RES_ID = IntResourceId{11111, ResourceType::COLOR};
    static const std::string EXPECTED_RESOURCE_COLOR =
        Color::RED.ToString(); // Color::RED is result of ThemeConstants::GetColorXxxx stubs

    // center
    inputValue.center.value0 = Converter::ArkValue<Ark_Length>("2.0vp");
    inputValue.center.value1 = Converter::ArkValue<Ark_Length>("3.0vp");
    // radius
    inputValue.radius = Converter::ArkValue<Ark_Length>("4vp");
    // repeating
    inputValue.repeating = Converter::ArkValue<Opt_Boolean>(true);
    // color stops
    std::vector<ColorStep> colorSteps {
        { CreateResourceUnion<Ark_ResourceColor>(RES_NAME), 0.5 },
        { CreateResourceUnion<Ark_ResourceColor>(RES_ID), 0.9 },
    };
    inputValue.colors = Converter::ArkValue<Array_Tuple_ResourceColor_F64>(colorSteps, Converter::FC);
    optInputValue = Converter::ArkValue<Opt_RadialGradientOptions>(inputValue);

    // check value
    modifier_->setRadialGradient(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_RADIAL_GRADIENT_NAME);
    auto colResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_COLORS_NAME);
    EXPECT_EQ(colResult, "[[\"#FFFF0000\",\"0.500000\"],[\"#FFFF0000\",\"0.900000\"]]");
}

/*
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setBackgroundImage2TestValidValues, TestSize.Level1)
{
    Ark_String str = Converter::ArkValue<Ark_String>("path");
    Ark_ResourceStr resStr = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(str);
    auto src = Converter::ArkUnion<Opt_Union_ResourceStr_image_PixelMap, Ark_ResourceStr>(resStr);
    auto repeat = ARK_IMAGE_REPEAT_NO_REPEAT;

    modifier_->setBackgroundImage2(node_, &src, repeat);
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, "path, ImageRepeat.NoRepeat");

    auto resName = NamedResourceId("bi_public_ok", ResourceType::STRING);
    resStr = CreateResourceUnion<Ark_ResourceStr>(resName);
    src = Converter::ArkUnion<Opt_Union_ResourceStr_image_PixelMap, Ark_ResourceStr>(resStr);

    modifier_->setBackgroundImage2(node_, &src, repeat);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, "path_to_background_image, ImageRepeat.NoRepeat");
}

/*
 * @tc.name: setBackgroundImageRepeatValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setBackgroundImage2TestRepeatValidValues, TestSize.Level1)
{
    Ark_String str = Converter::ArkValue<Ark_String>("path");
    Ark_ResourceStr resStr = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(str);
    auto src = Converter::ArkUnion<Opt_Union_ResourceStr_image_PixelMap, Ark_ResourceStr>(resStr);
    auto repeat = ARK_IMAGE_REPEAT_X;
    modifier_->setBackgroundImage2(node_, &src, repeat);
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, "path, ImageRepeat.X");

    repeat = ARK_IMAGE_REPEAT_Y;
    modifier_->setBackgroundImage2(node_, &src, repeat);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, "path, ImageRepeat.Y");

    repeat = ARK_IMAGE_REPEAT_XY;
    modifier_->setBackgroundImage2(node_, &src, repeat);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, "path, ImageRepeat.XY");

    repeat = ARK_IMAGE_REPEAT_NO_REPEAT;
    modifier_->setBackgroundImage2(node_, &src, repeat);
    strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    EXPECT_EQ(strResult, "path, ImageRepeat.NoRepeat");
}

/*
 * @tc.name: DISABLED_setBackgroundImagePixelmapValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setBackgroundImage2TestPixelmapValues, TestSize.Level1)
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
    Opt_Union_SizeOptions_ImageSize inputValue;

    typedef std::pair<Ark_Length, std::string> OneTestStep2;
    static const std::vector<OneTestStep2> testPlan2 = {
        { Converter::ArkValue<Ark_Length>(2.45f), "2.45px" },
        { Converter::ArkValue<Ark_Length>("5.0px"), "5.00px" },
        { Converter::ArkValue<Ark_Length>("22.35px"), "22.35px" },
        { Converter::ArkValue<Ark_Length>("7.0vp"), "7.00px" },
        { Converter::ArkValue<Ark_Length>("1.65vp"), "1.65px" },
        { Converter::ArkValue<Ark_Length>("65.0fp"), "65.00px" },
        { Converter::ArkValue<Ark_Length>("4.3fp"), "4.30px" },
        { Converter::ArkValue<Ark_Length>("12.00%"), "12.00px" },
        { RES_ARK_LENGTH, "10.00px" },
    };

    for (const auto &[arkLength, expected]: testPlan2) {
        Ark_SizeOptions arkSizeOptions;
        arkSizeOptions.width = Converter::ArkValue<Opt_Length>(arkLength);
        arkSizeOptions.height = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue = Converter::ArkUnion<Opt_Union_SizeOptions_ImageSize, Ark_SizeOptions>(arkSizeOptions);
        modifier_->setBackgroundImageSize(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_NAME);
        auto width = GetAttrValue<std::string>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_WIDTH_NAME);
        EXPECT_EQ(width, expected);
        auto height = GetAttrValue<std::string>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_HEIGHT_NAME);
        EXPECT_EQ(height, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_HEIGHT_DEFAULT_VALUE);
    }

    for (const auto &[arkLength, expected]: testPlan2) {
        Ark_SizeOptions arkSizeOptions;
        arkSizeOptions.height = Converter::ArkValue<Opt_Length>(arkLength);
        arkSizeOptions.width = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue = Converter::ArkUnion<Opt_Union_SizeOptions_ImageSize, Ark_SizeOptions>(arkSizeOptions);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setBackgroundImageSizeValidEnumValues, TestSize.Level1)
{
    std::string strResult;
    Opt_Union_SizeOptions_ImageSize inputValue;

    typedef std::pair<Ark_ImageSize, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { ARK_IMAGE_SIZE_COVER, "ImageSize.Cover" },
        { ARK_IMAGE_SIZE_CONTAIN, "ImageSize.Contain" },
        { ARK_IMAGE_SIZE_FILL, "ImageSize.FILL" },
        { ARK_IMAGE_SIZE_AUTO, "ImageSize.Auto" },
    };

    for (const auto &[arkImageSize, expected]: testPlan) {
        inputValue = Converter::ArkUnion<Opt_Union_SizeOptions_ImageSize, Ark_ImageSize>(arkImageSize);
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
    Opt_Union_SizeOptions_ImageSize inputValue;

    typedef std::pair<Ark_ImageSize, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { static_cast<Ark_ImageSize>(-1), "ImageSize.Auto" },
        { static_cast<Ark_ImageSize>(4), "ImageSize.Auto" },
    };

    for (const auto &[arkImageSize, expected]: testPlan) {
        inputValue = Converter::ArkUnion<Opt_Union_SizeOptions_ImageSize, Ark_ImageSize>(arkImageSize);
        modifier_->setBackgroundImageSize(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_NAME);
        EXPECT_EQ(strResult, expected);
    }

    static const std::vector<Ark_Length> testPlan2 = {
        Converter::ArkValue<Ark_Length>(-2.45f),
        Converter::ArkValue<Ark_Length>("-5.0px"),
        Converter::ArkValue<Ark_Length>("-22.35px"),
        Converter::ArkValue<Ark_Length>("-7.0vp"),
        Converter::ArkValue<Ark_Length>("-1.65vp"),
        Converter::ArkValue<Ark_Length>("-65.0fp"),
        Converter::ArkValue<Ark_Length>("-4.3fp"),
        Converter::ArkValue<Ark_Length>("-12.00%"),
    };

    for (const auto &arkLength: testPlan2) {
        Ark_SizeOptions arkSizeOptions;
        arkSizeOptions.width = Converter::ArkValue<Opt_Length>(arkLength);
        arkSizeOptions.height = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue = Converter::ArkUnion<Opt_Union_SizeOptions_ImageSize, Ark_SizeOptions>(arkSizeOptions);
        modifier_->setBackgroundImageSize(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_NAME);
        auto width = GetAttrValue<std::string>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_WIDTH_NAME);
        EXPECT_EQ(width, "0.00px");
        auto height = GetAttrValue<std::string>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_HEIGHT_NAME);
        EXPECT_EQ(height, ATTRIBUTE_BACKGROUND_IMAGE_SIZE_HEIGHT_DEFAULT_VALUE);
    }

    for (const auto &arkLength: testPlan2) {
        Ark_SizeOptions arkSizeOptions;
        arkSizeOptions.height = Converter::ArkValue<Opt_Length>(arkLength);
        arkSizeOptions.width = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue = Converter::ArkUnion<Opt_Union_SizeOptions_ImageSize, Ark_SizeOptions>(arkSizeOptions);
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
    Opt_Union_Position_Alignment inputValue;

    typedef std::pair<Ark_Length, double> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(-2.5f), -2.5 },
        { Converter::ArkValue<Ark_Length>("5.0px"), 5.0 },
        { Converter::ArkValue<Ark_Length>("22.5px"), 22.5 },
        { Converter::ArkValue<Ark_Length>("7.0vp"), 7.0 },
        { Converter::ArkValue<Ark_Length>("1.5vp"), 1.5 },
        { Converter::ArkValue<Ark_Length>("65.0fp"), 65.0 },
        { Converter::ArkValue<Ark_Length>("4.5fp"), 4.5 },
        { RES_ARK_LENGTH, 10.0 },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        Ark_Position arkPosition;
        arkPosition.x = Converter::ArkValue<Opt_Length>(arkLength);
        arkPosition.y = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue = Converter::ArkUnion<Opt_Union_Position_Alignment, Ark_Position>(arkPosition);
        modifier_->setBackgroundImagePosition(node_, &inputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_NAME);
        auto x = GetAttrValue<double>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_X_NAME);
        EXPECT_NEAR(x, expected, FLT_EPSILON);
        auto y = GetAttrValue<double>(strResult, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_Y_NAME);
        EXPECT_NEAR(y, ATTRIBUTE_BACKGROUND_IMAGE_POSITION_Y_DEFAULT_VALUE, FLT_EPSILON);
    }

    for (const auto &[arkLength, expected]: testPlan) {
        Ark_Position arkPosition;
        arkPosition.y = Converter::ArkValue<Opt_Length>(arkLength);
        arkPosition.x = Converter::ArkValue<Opt_Length>(Ark_Empty());
        inputValue = Converter::ArkUnion<Opt_Union_Position_Alignment, Ark_Position>(arkPosition);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setBackgroundImagePositionValidAlignmentValues, TestSize.Level1)
{
    std::string strResult;
    Opt_Union_Position_Alignment inputValue;

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
        inputValue = Converter::ArkUnion<Opt_Union_Position_Alignment, Ark_Alignment>(arkAlign);
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

    auto inputVal = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setClip(node_, &inputVal);
    strResult = GetStringAttribute(node_, ATTRIBUTE_CLIP_NAME);
    EXPECT_EQ(strResult, "true");

    inputVal = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setClip(node_, &inputVal);
    strResult = GetStringAttribute(node_, ATTRIBUTE_CLIP_NAME);
    EXPECT_EQ(strResult, "false");
}

/*
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setScaleValidXValues, TestSize.Level1)
{
    std::string strResult;
    Ark_ScaleOptions inputValue;
    Opt_ScaleOptions optInputValue;

    inputValue.x = Converter::ArkValue<Opt_Float64>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Float64>(Ark_Empty());
    inputValue.centerX = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());
    inputValue.centerY = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());

    typedef std::pair<Opt_Float64, std::string> NumberTestStep;
    static const std::vector<NumberTestStep> testPlan = {
        { Converter::ArkValue<Opt_Float64>(2.0f), "2.000000" },
        { Converter::ArkValue<Opt_Float64>(0.0f), "0.000000" },
        { Converter::ArkValue<Opt_Float64>(-2.5f), "-2.500000" },
    };

    for (const auto &[optNumber, expected]: testPlan) {
        inputValue.x = optNumber;
        optInputValue = Converter::ArkValue<Opt_ScaleOptions>(inputValue);
        modifier_->setScale(node_, &optInputValue);
        strResult = GetStringAttribute(node_, ATTRIBUTE_SCALE_NAME);
        auto x = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_X_NAME);
        EXPECT_EQ(x, expected);
        auto y = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_Y_NAME);
        EXPECT_EQ(y, "1.000000");
        auto centerX = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_CENTER_X_NAME);
        EXPECT_EQ(centerX, "50.00%");
        auto centerY = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_CENTER_Y_NAME);
        EXPECT_EQ(centerY, "50.00%");
    }
}

/*
 * @tc.name: setScaleValidYValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setScaleValidYValues, TestSize.Level1)
{
    std::string strResult;
    Ark_ScaleOptions inputValue;
    Opt_ScaleOptions optInputValue;

    inputValue.x = Converter::ArkValue<Opt_Float64>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Float64>(Ark_Empty());
    inputValue.centerX = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());
    inputValue.centerY = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());

    typedef std::pair<Opt_Float64, std::string> NumberTestStep;
    static const std::vector<NumberTestStep> testPlan = {
        { Converter::ArkValue<Opt_Float64>(2.0f), "2.000000" },
        { Converter::ArkValue<Opt_Float64>(0.0f), "0.000000" },
        { Converter::ArkValue<Opt_Float64>(-2.5f), "-2.500000" },
    };

    for (const auto &[optNumber, expected]: testPlan) {
        inputValue.y = optNumber;
        optInputValue = Converter::ArkValue<Opt_ScaleOptions>(inputValue);
        modifier_->setScale(node_, &optInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setScaleValidCenterXValues, TestSize.Level1)
{
    std::string strResult;
    Ark_ScaleOptions inputValue;
    Opt_ScaleOptions optInputValue;

    inputValue.x = Converter::ArkValue<Opt_Float64>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Float64>(Ark_Empty());
    inputValue.centerX = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());
    inputValue.centerY = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());

    for (const auto &[optCenter, expected]: SCALE_TRANSLATE_TEST_PLAN) {
        inputValue.centerX = optCenter;
        optInputValue = Converter::ArkValue<Opt_ScaleOptions>(inputValue);
        modifier_->setScale(node_, &optInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setScaleValidCenterYValues, TestSize.Level1)
{
    std::string strResult;
    Ark_ScaleOptions inputValue;
    Opt_ScaleOptions optInputValue;

    inputValue.x = Converter::ArkValue<Opt_Float64>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Float64>(Ark_Empty());
    inputValue.centerX = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());
    inputValue.centerY = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());

    for (const auto &[optCenter, expected]: SCALE_TRANSLATE_TEST_PLAN) {
        inputValue.centerY= optCenter;
        optInputValue = Converter::ArkValue<Opt_ScaleOptions>(inputValue);
        modifier_->setScale(node_, &optInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setTranslateValidXValues, TestSize.Level1)
{
    std::string strResult;
    Ark_TranslateOptions inputValue;
    Opt_TranslateOptions optInputValue;

    inputValue.x = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());
    inputValue.z = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());

    for (const auto &[optTranslate, expected]: SCALE_TRANSLATE_TEST_PLAN) {
        inputValue.x = optTranslate;
        optInputValue = Converter::ArkValue<Opt_TranslateOptions>(inputValue);
        modifier_->setTranslate(node_, &optInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setTranslateValidYValues, TestSize.Level1)
{
    std::string strResult;
    Ark_TranslateOptions inputValue;
    Opt_TranslateOptions optInputValue;

    inputValue.x = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());
    inputValue.z = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());

    for (const auto &[optTranslate, expected]: SCALE_TRANSLATE_TEST_PLAN) {
        inputValue.y = optTranslate;
        optInputValue = Converter::ArkValue<Opt_TranslateOptions>(inputValue);
        modifier_->setTranslate(node_, &optInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setTranslateValidZValues, TestSize.Level1)
{
    std::string strResult;
    Ark_TranslateOptions inputValue;
    Opt_TranslateOptions optInputValue;

    inputValue.x = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());
    inputValue.y = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());
    inputValue.z = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty());

    for (const auto &[optTranslate, expected]: SCALE_TRANSLATE_TEST_PLAN) {
        inputValue.z = optTranslate;
        optInputValue = Converter::ArkValue<Opt_TranslateOptions>(inputValue);
        modifier_->setTranslate(node_, &optInputValue);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setIdValidValues, TestSize.Level1)
{
    auto inputValue = Converter::ArkValue<Opt_String>("custom_id");
    modifier_->setId(node_, &inputValue);
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_ID_NAME);
    EXPECT_EQ(strResult, "custom_id");

    inputValue = Converter::ArkValue<Opt_String>("other id");
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
    auto invalidOptString = Converter::ArkValue<Opt_String>(Ark_Empty());
    modifier_->setId(node_, &invalidOptString);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ID_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ID_DEFAULT_VALUE);
}

/*
 * @tc.name: setOnVisibleAreaChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, DISABLED_setOnVisibleAreaChangeTest, TestSize.Level1)
{
    struct CheckEvent {
        int32_t nodeId;
        bool isExpanding;
        double currentRatio;
    };
    static std::vector<CheckEvent> checkEvent;
    auto checkCallback =
        [](const Ark_Int32 resourceId, const Ark_Boolean isExpanding, const Ark_Float64 currentRatio) {
            checkEvent.push_back({
                .nodeId = resourceId,
                .isExpanding = Converter::Convert<bool>(isExpanding),
                .currentRatio = Converter::Convert<double>(currentRatio)
            });
        };
    auto arkfunc = Converter::ArkValue<VisibleAreaChangeCallback>(checkCallback, FAKE_RES_ID);
    auto func = Converter::ArkValue<Opt_VisibleAreaChangeCallback>(arkfunc);

    std::vector<double> ratioVec;
    ratioVec.push_back(0.5f);
    auto numberArrayResult = Converter::ArkValue<Opt_Array_F64>(ratioVec, Converter::FC);

    std::vector<double> ratioVecInvalid1;
    ratioVecInvalid1.push_back(-0.5f);
    auto numberArrayResultInvalid1 = Converter::ArkValue<Opt_Array_F64>(ratioVecInvalid1, Converter::FC);

    std::vector<double> ratioVecInvalid2;
    ratioVecInvalid2.push_back(1.5f);
    auto numberArrayResultInvalid2 = Converter::ArkValue<Opt_Array_F64>(ratioVecInvalid2, Converter::FC);

    EXPECT_EQ(checkEvent.size(), 0);

    modifier_->setOnVisibleAreaChange(node_, &numberArrayResult, &func);

    EXPECT_EQ(checkEvent.size(), 2);
    EXPECT_EQ(checkEvent[0].nodeId, FAKE_RES_ID);
    EXPECT_EQ(checkEvent[1].nodeId, FAKE_RES_ID);
    EXPECT_EQ(checkEvent[0].isExpanding, false);
    EXPECT_EQ(checkEvent[1].isExpanding, true);
    EXPECT_FLOAT_EQ(checkEvent[0].currentRatio, 0.0f);
    EXPECT_FLOAT_EQ(checkEvent[1].currentRatio, ratioVec[0]);

    modifier_->setOnVisibleAreaChange(node_, &numberArrayResultInvalid1, &func);
    modifier_->setOnVisibleAreaChange(node_, &numberArrayResultInvalid2, &func);

    EXPECT_EQ(checkEvent.size(), 6);
    EXPECT_FLOAT_EQ(checkEvent[3].currentRatio, 0.0f);
    EXPECT_FLOAT_EQ(checkEvent[5].currentRatio, 1.0f);
}

/*
 * @tc.name: setAnimationDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest, setAnimationDefaultValues, TestSize.Level1)
{
    Ark_AnimateParam param;
    Opt_AnimateParam optParam;
    param.duration = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    param.delay = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    param.iterations = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    param.tempo = Converter::ArkValue<Opt_Float64>(Ark_Empty());
    param.playMode = Converter::ArkValue<Opt_PlayMode>(Ark_Empty());
    param.finishCallbackType = Converter::ArkValue<Opt_FinishCallbackType>(Ark_Empty());
    param.curve = Converter::ArkValue<Opt_Union_curves_Curve_String_curves_ICurve>(Ark_Empty());
    param.expectedFrameRateRange = Converter::ArkValue<Opt_ExpectedFrameRateRange>(Ark_Empty());
    optParam = Converter::ArkValue<Opt_AnimateParam>(param);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    frameNode->MarkBuildDone();
    modifier_->setAnimation(node_, &optParam);
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
HWTEST_F(CommonMethodModifierTest, DISABLED_setCloseAnimationValidValues, TestSize.Level1)
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
    Opt_AnimateParam optParam;
    param.duration = Converter::ArkValue<Opt_Int32>(5);
    param.delay = Converter::ArkValue<Opt_Int32>(3);
    param.iterations = Converter::ArkValue<Opt_Int32>(8);
    param.tempo = Converter::ArkValue<Opt_Float64>(2.5f);
    param.playMode = Converter::ArkValue<Opt_PlayMode>(ARK_PLAY_MODE_REVERSE);
    param.finishCallbackType = Converter::ArkValue<Opt_FinishCallbackType>(ARK_FINISH_CALLBACK_TYPE_LOGICALLY);
    param.curve = Converter::ArkUnion<Opt_Union_curves_Curve_String_curves_ICurve, Ark_curves_Curve>(
        ARK_CURVES_CURVE_EASE);
    Ark_ExpectedFrameRateRange efrr;
    efrr.min = Converter::ArkValue<Ark_Int32>(30);
    efrr.max = Converter::ArkValue<Ark_Int32>(120);
    efrr.expected = Converter::ArkValue<Ark_Int32>(60);
    param.expectedFrameRateRange = Converter::ArkValue<Opt_ExpectedFrameRateRange>(efrr);
    optParam = Converter::ArkValue<Opt_AnimateParam>(param);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    frameNode->MarkBuildDone();
    modifier_->setAnimation(node_, &optParam);
    AnimationOption option = NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    EXPECT_EQ(option.GetDuration(), 5);
    EXPECT_EQ(option.GetDelay(), 3);
    EXPECT_EQ(option.GetIteration(), 8);
    EXPECT_FLOAT_EQ(option.GetTempo(), 2.5f);
    EXPECT_EQ(option.GetAnimationDirection(), AnimationDirection::REVERSE);
    EXPECT_EQ(option.GetFinishCallbackType(), FinishCallbackType::LOGICALLY);
    EXPECT_EQ(option.GetCurve(), Curves::EASE);
    RefPtr<FrameRateRange> frr = option.GetFrameRateRange();
    ASSERT_NE(frr, nullptr);
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
    Opt_AnimateParam optParam;
    param.duration = Converter::ArkValue<Opt_Int32>(5000);
    param.delay = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    param.iterations = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    param.tempo = Converter::ArkValue<Opt_Float64>(0.0f);
    param.playMode = Converter::ArkValue<Opt_PlayMode>(Ark_Empty());
    param.finishCallbackType = Converter::ArkValue<Opt_FinishCallbackType>(Ark_Empty());
    param.curve = Converter::ArkValue<Opt_Union_curves_Curve_String_curves_ICurve>(Ark_Empty());
    param.expectedFrameRateRange = Converter::ArkValue<Opt_ExpectedFrameRateRange>(Ark_Empty());
    optParam = Converter::ArkValue<Opt_AnimateParam>(param);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    frameNode->MarkBuildDone();
    modifier_->setAnimation(node_, &optParam);
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
