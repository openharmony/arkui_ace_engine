/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "generated/type_helpers.h"

#include "core/components/progress/progress_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_VALUE_NAME = "value";
    const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "0.000000";
    const auto ATTRIBUTE_TOTAL_NAME = "total";
    const auto ATTRIBUTE_TOTAL_DEFAULT_VALUE = "100.000000";
    const auto ATTRIBUTE_TYPE_NAME = "type";
    const auto ATTRIBUTE_TYPE_DEFAULT_VALUE = "ProgressStyle.Linear";
    const auto ATTRIBUTE_COLOR_NAME = "color";
    const auto ATTRIBUTE_COLOR_DEFAULT_VALUE = "#FF000000";
    const auto ATTRIBUTE_GRADIENT_NAME = "progressGradientColor";
    const auto ATTRIBUTE_GRADIENT_DEFAULT_VALUE =
        "[{\"color\":\"#FF000000\",\"offset\":\"0.000000\"},{\"color\":\"#FF000000\",\"offset\":\"1.000000\"}]";
    const auto ATTRIBUTE_LINEAR_STYLE_NAME = "linearStyle";
    const auto ATTRIBUTE_RING_STYLE_NAME = "ringStyle";
    const auto ATTRIBUTE_CAPSULE_STYLE_NAME = "capsuleStyle";
    const auto ATTRIBUTE_STYLE_NAME = "style";
    const auto ATTRIBUTE_STROKE_WIDTH_NAME = "strokeWidth";
    const auto ATTRIBUTE_STROKE_WIDTH_DEFAULT_VALUE = "0.00px";
    const auto ATTRIBUTE_STROKE_RADIUS_NAME = "strokeRadius";
    const auto ATTRIBUTE_STROKE_RADIUS_DEFAULT_VALUE = "0.00px";
    const auto ATTRIBUTE_ENABLE_SCAN_EFFECT_NAME = "enableScanEffect";
    const auto ATTRIBUTE_ENABLE_SCAN_EFFECT_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_SHADOW_NAME = "shadow";
    const auto ATTRIBUTE_SHADOW_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_STATUS_NAME = "status";
    const auto ATTRIBUTE_STATUS_DEFAULT_VALUE = "ProgressStatus.PROGRESSING";
    const auto ATTRIBUTE_BORDER_WIDTH_NAME = "borderWidth";
    const auto ATTRIBUTE_BORDER_WIDTH_DEFAULT_VALUE = "0.00px";
    const auto ATTRIBUTE_BORDER_COLOR_NAME = "borderColor";
    const auto ATTRIBUTE_BORDER_COLOR_DEFAULT_VALUE = "#FF000000";
    const auto ATTRIBUTE_FONT_COLOR_NAME = "fontColor";
    const auto ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE = "#FF000000";
    const auto ATTRIBUTE_CONTENT_NAME = "content";
    const auto ATTRIBUTE_CONTENT_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_SHOW_DEFAULT_PERCENTAGE_NAME = "showDefaultPercentage";
    const auto ATTRIBUTE_SHOW_DEFAULT_PERCENTAGE_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_FONT_NAME = "font";
    const auto ATTRIBUTE_FONT_SIZE_NAME = "size";
    const auto ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE = "0.00px";
    const auto ATTRIBUTE_FONT_STYLE_NAME = "style";
    const auto ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE = "FontStyle.Normal";
    const auto ATTRIBUTE_FONT_WEIGHT_NAME = "weight";
    const auto ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE = "FontWeight.Normal";
    const auto ATTRIBUTE_FONT_FAMILY_NAME = "family";
    const auto ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE = "Sans";
    const auto ATTRIBUTE_SCALE_COUNT_NAME = "scaleCount";
    const auto ATTRIBUTE_SCALE_COUNT_DEFAULT_VALUE = "0";
    const auto ATTRIBUTE_SCALE_WIDTH_NAME = "scaleWidth";
    const auto ATTRIBUTE_SCALE_WIDTH_DEFAULT_VALUE = "0.00px";
    const auto ATTRIBUTE_ENABLE_SMOOTH_EFFECT_NAME = "enableSmoothEffect";
    const auto ATTRIBUTE_ENABLE_SMOOTH_EFFECT_DEFAULT_VALUE = "true";
    const auto RES_NAME_ID = "RES_NAME_ID";
    const auto RES_NAME_NEG_ID = "RES_NAME_NEG_ID";

    Ark_CapsuleStyleOptions getEmptyCapsuleStyleOptions()
    {
        Ark_CapsuleStyleOptions capsuleStyle;
        capsuleStyle.enableScanEffect = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
        capsuleStyle.borderColor = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        capsuleStyle.borderWidth = Converter::ArkValue<Opt_Length>(Ark_Empty());
        capsuleStyle.content = Converter::ArkValue<Opt_String>(Ark_Empty());
        capsuleStyle.font = Converter::ArkValue<Opt_Font>(Ark_Empty());
        capsuleStyle.fontColor = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        capsuleStyle.showDefaultPercentage = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
        capsuleStyle.borderRadius = Converter::ArkValue<Opt_LengthMetrics>(Ark_Empty());
        return capsuleStyle;
    }

    Ark_ProgressOptions getCapsuleProgressOptions()
    {
        Ark_ProgressOptions progressOptions;
        const auto value = 5;
        const auto total = 20;
        progressOptions.value = Converter::ArkValue<Ark_Number>(value);
        progressOptions.total = Converter::ArkValue<Opt_Number>(total);
        progressOptions.type = Converter::ArkValue<Opt_ProgressType>(ARK_PROGRESS_TYPE_CAPSULE);
        return progressOptions;
    }
} // namespace

class ProgressModifierTest : public ModifierTestBase<GENERATED_ArkUIProgressModifier,
    &GENERATED_ArkUINodeModifiers::getProgressModifier, GENERATED_ARKUI_PROGRESS> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<ProgressTheme>();
        AddResource(RES_NAME_ID, 22.55_px);
        AddResource(RES_NAME_NEG_ID, -56.73_px);
    }
};

/*
 * @tc.name: setProgressOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_VALUE_DEFAULT_VALUE);

    strResult = GetStringAttribute(node_, ATTRIBUTE_TOTAL_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_TOTAL_DEFAULT_VALUE);

    strResult = GetStringAttribute(node_, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_TYPE_DEFAULT_VALUE);
}

/*
 * @tc.name: setProgressOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestValidValues, TestSize.Level1)
{
    Ark_ProgressOptions options;
    options.value = Converter::ArkValue<Ark_Number>(5);
    options.total = Converter::ArkValue<Opt_Number>(20);
    options.type = Converter::ArkValue<Opt_ProgressType>(ARK_PROGRESS_TYPE_RING);
    modifier_->setProgressOptions(node_, &options);

    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(strResult, "5.000000");

    strResult = GetStringAttribute(node_, ATTRIBUTE_TOTAL_NAME);
    EXPECT_EQ(strResult, "20.000000");

    strResult = GetStringAttribute(node_, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(strResult, "ProgressStyle.Ring");
}

/*
 * @tc.name: setProgressOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressOptionsTestInvalidValues, TestSize.Level1)
{
    Ark_ProgressOptions options;
    options.value = Converter::ArkValue<Ark_Number>(105);
    options.total = Converter::ArkValue<Opt_Number>(20);
    options.type = Converter::ArkValue<Opt_ProgressType>(Ark_Empty());
    modifier_->setProgressOptions(node_, &options);

    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(strResult, "20.000000");

    strResult = GetStringAttribute(node_, ATTRIBUTE_TOTAL_NAME);
    EXPECT_EQ(strResult, "20.000000");

    strResult = GetStringAttribute(node_, ATTRIBUTE_TYPE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_TYPE_DEFAULT_VALUE);
}

/*
 * @tc.name: setValueTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setValueTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_VALUE_DEFAULT_VALUE);
}

/*
 * @tc.name: setValueTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setValueTestValidValues, TestSize.Level1)
{
    Opt_Number value = Converter::ArkValue<Opt_Number>(8);
    modifier_->setValue(node_, &value);

    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(strResult, "8.000000");
}

/*
 * @tc.name: setValueTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setValueTestInvalidValues, TestSize.Level1)
{
    Opt_Number value = Converter::ArkValue<Opt_Number>(254);
    modifier_->setValue(node_, &value);

    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_TOTAL_DEFAULT_VALUE);
}

/*
 * @tc.name: setColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setColorTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_COLOR_DEFAULT_VALUE);

    strResult = GetStringAttribute(node_, ATTRIBUTE_GRADIENT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_GRADIENT_DEFAULT_VALUE);
}

/*
 * @tc.name: setColorTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setColorTestValidValues, TestSize.Level1)
{
    Ark_ResourceColor color = Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    Opt_Union_ResourceColor_LinearGradient options =
        Converter::ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_ResourceColor>(color);
    modifier_->setColor(node_, &options);

    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_COLOR_NAME);
    EXPECT_EQ(strResult, "#11223344");

    strResult = GetStringAttribute(node_, ATTRIBUTE_GRADIENT_NAME);
    EXPECT_EQ(strResult,
        "[{\"color\":\"#11223344\",\"offset\":\"0.000000\"},{\"color\":\"#11223344\",\"offset\":\"1.000000\"}]");

    Ark_LinearGradient gradient{};
#ifdef WRONG_TYPE
    Ark_Tuple_ResourceColor_Number gradientValue1;
    gradientValue1.value0 = Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#44223311");
    gradientValue1.value1 = Converter::ArkValue<Ark_Number>(0.5f);

    Ark_Tuple_ResourceColor_Number gradientValue2;
    gradientValue2.value0 = Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#33112244");
    gradientValue2.value1 = Converter::ArkValue<Ark_Number>(0.9f);

    std::vector<Ark_Tuple_ResourceColor_Number> colors = { gradientValue1, gradientValue2 };
    Converter::ArkArrayHolder<Array_Tuple_ResourceColor_Number> colorsHolder(colors);
    gradient.colors = colorsHolder.ArkValue();
#endif

    options = Converter::ArkUnion<Opt_Union_ResourceColor_LinearGradient, Ark_LinearGradient>(gradient);
    modifier_->setColor(node_, &options);
    strResult = GetStringAttribute(node_, ATTRIBUTE_GRADIENT_NAME);
    EXPECT_EQ(strResult,
        "[{\"color\":\"#44223311\",\"offset\":\"0.500000\"},{\"color\":\"#33112244\",\"offset\":\"0.900000\"}]");
}

/*
 * @tc.name: setLinearStyleDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setLinearStyleDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_LINEAR_STYLE_NAME);
    std::string result = GetAttrValue<std::string>(strResult, ATTRIBUTE_STROKE_WIDTH_NAME);
    EXPECT_EQ(result, ATTRIBUTE_STROKE_WIDTH_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_STROKE_RADIUS_NAME);
    EXPECT_EQ(result, ATTRIBUTE_STROKE_RADIUS_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_ENABLE_SCAN_EFFECT_NAME);
    EXPECT_EQ(result, ATTRIBUTE_ENABLE_SCAN_EFFECT_DEFAULT_VALUE);
}

/*
 * @tc.name: setLinearStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setLinearStyleValidValues, TestSize.Level1)
{
    Ark_LinearStyleOptions linearStyle;
    linearStyle.enableScanEffect = Converter::ArkValue<Opt_Boolean>(true);
    linearStyle.strokeRadius = Converter::ArkValue<Opt_Union_String_F64_Resource>(Ark_Empty());
    linearStyle.strokeWidth = Converter::ArkValue<Opt_Length>("3px");
    auto options =
        Converter::ArkUnion<Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions,
            Ark_LinearStyleOptions>(linearStyle);
    modifier_->setStyle(node_, &options);

    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_LINEAR_STYLE_NAME);
    std::string result = GetAttrValue<std::string>(strResult, ATTRIBUTE_STROKE_WIDTH_NAME);
    EXPECT_EQ(result, "3.00px");
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_ENABLE_SCAN_EFFECT_NAME);
    EXPECT_EQ(result, "true");
}

/*
 * @tc.name: setLinearStyleStrokeRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setLinearStyleStrokeRadiusValidValues, TestSize.Level1)
{
    Ark_LinearStyleOptions linearStyle;
    linearStyle.enableScanEffect = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    linearStyle.strokeWidth = Converter::ArkValue<Opt_Length>("50px");
    auto options =
        Converter::ArkUnion<Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions,
            Ark_LinearStyleOptions>(linearStyle);
    auto checkValue =
        [this](const Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions& input,
            const std::string& expectedStr) {
            modifier_->setStyle(node_, &input);
            auto strResult = GetStringAttribute(node_, ATTRIBUTE_LINEAR_STYLE_NAME);
            auto result = GetAttrValue<std::string>(strResult, ATTRIBUTE_STROKE_RADIUS_NAME);
            EXPECT_EQ(result, expectedStr);
        };
    auto value = Converter::ArkUnion<Opt_Union_String_F64_Resource, Ark_Number>(12.34);
    TypeHelper::WriteToUnion<Ark_LinearStyleOptions>(options.value).strokeRadius = value;
    checkValue(options, "12.34vp");

    value = Converter::ArkUnion<Opt_Union_String_F64_Resource, Ark_String>("1.00");
    TypeHelper::WriteToUnion<Ark_LinearStyleOptions>(options.value).strokeRadius = value;
    checkValue(options, "1.00vp");

    auto strokeRes = CreateResource(RES_NAME_ID, ResourceType::FLOAT);
    value = Converter::ArkUnion<Opt_Union_String_F64_Resource, Ark_Resource>(strokeRes);
    TypeHelper::WriteToUnion<Ark_LinearStyleOptions>(options.value).strokeRadius = value;
    checkValue(options, "22.55px");

    strokeRes = CreateResource(RES_NAME_NEG_ID, ResourceType::FLOAT);
    value = Converter::ArkUnion<Opt_Union_String_F64_Resource, Ark_Resource>(strokeRes);
    TypeHelper::WriteToUnion<Ark_LinearStyleOptions>(options.value).strokeRadius = value;
    checkValue(options, "25.00px");
}

/*
 * @tc.name: setRingStyleDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setRingStyleDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_RING_STYLE_NAME);
    std::string result = GetAttrValue<std::string>(strResult, ATTRIBUTE_STROKE_WIDTH_NAME);
    EXPECT_EQ(result, ATTRIBUTE_STROKE_WIDTH_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_SHADOW_NAME);
    EXPECT_EQ(result, ATTRIBUTE_SHADOW_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_ENABLE_SCAN_EFFECT_NAME);
    EXPECT_EQ(result, ATTRIBUTE_ENABLE_SCAN_EFFECT_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_STATUS_NAME);
    EXPECT_EQ(result, ATTRIBUTE_STATUS_DEFAULT_VALUE);
}

/*
 * @tc.name: setRingStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setRingStyleValidValues, TestSize.Level1)
{
    Ark_RingStyleOptions ringStyle;
    ringStyle.enableScanEffect = Converter::ArkValue<Opt_Boolean>(true);
    ringStyle.shadow = Converter::ArkValue<Opt_Boolean>(true);
    ringStyle.strokeWidth = Converter::ArkValue<Opt_Length>("5px");
    ringStyle.status = Converter::ArkValue<Opt_ProgressStatus>(ARK_PROGRESS_STATUS_LOADING);
    auto options =
        Converter::ArkUnion<Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions,
            Ark_RingStyleOptions>(ringStyle);
    modifier_->setStyle(node_, &options);

    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_RING_STYLE_NAME);
    std::string result = GetAttrValue<std::string>(strResult, ATTRIBUTE_STROKE_WIDTH_NAME);
    EXPECT_EQ(result, "5.00px");
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_ENABLE_SCAN_EFFECT_NAME);
    EXPECT_EQ(result, "true");
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_SHADOW_NAME);
    EXPECT_EQ(result, "true");
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_STATUS_NAME);
    EXPECT_EQ(result, "ProgressStatus.LOADING");
}

/*
 * @tc.name: setCapsuleStyleDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setCapsuleStyleDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_CAPSULE_STYLE_NAME);
    std::string result = GetAttrValue<std::string>(strResult, ATTRIBUTE_BORDER_WIDTH_NAME);
    EXPECT_EQ(result, ATTRIBUTE_BORDER_WIDTH_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_BORDER_COLOR_NAME);
    EXPECT_EQ(result, ATTRIBUTE_BORDER_COLOR_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_ENABLE_SCAN_EFFECT_NAME);
    EXPECT_EQ(result, ATTRIBUTE_ENABLE_SCAN_EFFECT_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(result, ATTRIBUTE_FONT_COLOR_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_CONTENT_NAME);
    EXPECT_EQ(result, ATTRIBUTE_CONTENT_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_SHOW_DEFAULT_PERCENTAGE_NAME);
    EXPECT_EQ(result, ATTRIBUTE_SHOW_DEFAULT_PERCENTAGE_DEFAULT_VALUE);
    std::string fontResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_FONT_NAME);
    result = GetAttrValue<std::string>(fontResult, ATTRIBUTE_FONT_SIZE_NAME);
    EXPECT_EQ(result, ATTRIBUTE_FONT_SIZE_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(fontResult, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(result, ATTRIBUTE_FONT_WEIGHT_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(fontResult, ATTRIBUTE_FONT_STYLE_NAME);
    EXPECT_EQ(result, ATTRIBUTE_FONT_STYLE_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(fontResult, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(result, ATTRIBUTE_FONT_FAMILY_DEFAULT_VALUE);
}

/*
 * @tc.name: setCapsuleStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setCapsuleStyleValidValues, TestSize.Level1)
{
    Ark_ProgressOptions progressOptions = getCapsuleProgressOptions();
    modifier_->setProgressOptions(node_, &progressOptions);

    Ark_CapsuleStyleOptions capsuleStyle = getEmptyCapsuleStyleOptions();
    capsuleStyle.enableScanEffect = Converter::ArkValue<Opt_Boolean>(true);
    capsuleStyle.borderColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#12131415");
    capsuleStyle.borderWidth = Converter::ArkValue<Opt_Length>("7px");
    capsuleStyle.fontColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#23456134");
    capsuleStyle.showDefaultPercentage = Converter::ArkValue<Opt_Boolean>(true);
    auto options =
        Converter::ArkUnion<Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions,
            Ark_CapsuleStyleOptions>(capsuleStyle);
    modifier_->setStyle(node_, &options);

    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_CAPSULE_STYLE_NAME);
    std::string result = GetAttrValue<std::string>(strResult, ATTRIBUTE_BORDER_COLOR_NAME);
    EXPECT_EQ(result, "#12131415");
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_BORDER_WIDTH_NAME);
    EXPECT_EQ(result, "7.00px");
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_ENABLE_SCAN_EFFECT_NAME);
    EXPECT_EQ(result, "true");
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_FONT_COLOR_NAME);
    EXPECT_EQ(result, "#23456134");
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_SHOW_DEFAULT_PERCENTAGE_NAME);
    EXPECT_EQ(result, "true");
}

/*
 * @tc.name: setCapsuleStyleValidContentValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setCapsuleStyleValidContentValues, TestSize.Level1)
{
    Ark_ProgressOptions progressOptions = getCapsuleProgressOptions();
    modifier_->setProgressOptions(node_, &progressOptions);

    Ark_CapsuleStyleOptions capsuleStyle = getEmptyCapsuleStyleOptions();
    capsuleStyle.content = Converter::ArkValue<Opt_String>("content");
    auto options =
        Converter::ArkUnion<Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions,
            Ark_CapsuleStyleOptions>(capsuleStyle);
    modifier_->setStyle(node_, &options);

    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_CAPSULE_STYLE_NAME);
    std::string result = GetAttrValue<std::string>(strResult, ATTRIBUTE_CONTENT_NAME);
    EXPECT_EQ(result, "content");
}

/*
 * @tc.name: setCapsuleStyleValidFontValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setCapsuleStyleValidFontValues, TestSize.Level1)
{
    Ark_ProgressOptions progressOptions = getCapsuleProgressOptions();
    modifier_->setProgressOptions(node_, &progressOptions);

    Ark_CapsuleStyleOptions capsuleStyle = getEmptyCapsuleStyleOptions();
    Ark_Font font;
    Ark_Union_String_Resource family = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(
        Converter::ArkValue<Ark_String>("Family"));
    font.family = Converter::ArkValue<Opt_Union_String_Resource>(family);
    font.size = Converter::ArkValue<Opt_Length>("9px");
    font.style = Converter::ArkValue<Opt_FontStyle>(ARK_FONT_STYLE_ITALIC);
    font.weight = Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLD);
    capsuleStyle.font = Converter::ArkValue<Opt_Font>(font);
    auto options =
        Converter::ArkUnion<Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions,
            Ark_CapsuleStyleOptions>(capsuleStyle);
    modifier_->setStyle(node_, &options);

    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_CAPSULE_STYLE_NAME);
    std::string fontResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_FONT_NAME);
    strResult = GetAttrValue<std::string>(fontResult, ATTRIBUTE_FONT_SIZE_NAME);
    EXPECT_EQ(strResult, "9.00px");
    strResult = GetAttrValue<std::string>(fontResult, ATTRIBUTE_FONT_WEIGHT_NAME);
    EXPECT_EQ(strResult, "FontWeight.Bold");
    strResult = GetAttrValue<std::string>(fontResult, ATTRIBUTE_FONT_STYLE_NAME);
    EXPECT_EQ(strResult, "FontStyle.Italic");
    strResult = GetAttrValue<std::string>(fontResult, ATTRIBUTE_FONT_FAMILY_NAME);
    EXPECT_EQ(strResult, "Family");
}

/*
 * @tc.name: setProgressStyleDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, setProgressStyleDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_STYLE_NAME);
    std::string result = GetAttrValue<std::string>(strResult, ATTRIBUTE_STROKE_WIDTH_NAME);
    EXPECT_EQ(result, ATTRIBUTE_STROKE_WIDTH_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_COUNT_NAME);
    EXPECT_EQ(result, ATTRIBUTE_SCALE_COUNT_DEFAULT_VALUE);
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_WIDTH_NAME);
    EXPECT_EQ(result, ATTRIBUTE_SCALE_WIDTH_DEFAULT_VALUE);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_SMOOTH_EFFECT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ENABLE_SMOOTH_EFFECT_DEFAULT_VALUE);
}

/*
 * @tc.name: setProgressStyleValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ProgressModifierTest, DISABLED_setProgressStyleValidValues, TestSize.Level1)
{
    Ark_ProgressStyleOptions progressStyle;
    progressStyle.enableSmoothEffect = Converter::ArkValue<Opt_Boolean>(false);
    progressStyle.scaleWidth = Converter::ArkValue<Opt_Length>("15px");
    progressStyle.strokeWidth = Converter::ArkValue<Opt_Length>("25px");
    progressStyle.scaleCount = Converter::ArkValue<Opt_Number>(5);
    auto options =
        Converter::ArkUnion<Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions,
            Ark_ProgressStyleOptions>(progressStyle);
    modifier_->setStyle(node_, &options);

    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_STYLE_NAME);
    std::string result = GetAttrValue<std::string>(strResult, ATTRIBUTE_STROKE_WIDTH_NAME);
    EXPECT_EQ(result, "25.00px");
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_COUNT_NAME);
    EXPECT_EQ(result, "5");
    result = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCALE_WIDTH_NAME);
    EXPECT_EQ(result, "15.00px");
    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_SMOOTH_EFFECT_NAME);
    EXPECT_EQ(strResult, "false");
}

/*
* @tc.name: setCapsuleStyleValidBorderRadiusValues
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(ProgressModifierTest, setCapsuleStyleValidBorderRadiusValues, TestSize.Level1)
{
    Ark_ProgressOptions progressOptions = getCapsuleProgressOptions();
    modifier_->setProgressOptions(node_, &progressOptions);

    Ark_CapsuleStyleOptions capsuleStyle = getEmptyCapsuleStyleOptions();
    capsuleStyle.borderRadius = Converter::ArkValue<Opt_LengthMetrics>(Dimension(11, DimensionUnit::VP));
    auto options =
        Converter::ArkUnion<Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions,
            Ark_CapsuleStyleOptions>(capsuleStyle);
    modifier_->setStyle(node_, &options);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto borderRadius = paintProperty->GetBorderRadius();
    ASSERT_TRUE(borderRadius.has_value());
    EXPECT_EQ(borderRadius->ToString(), "11.00vp");
}
} // namespace OHOS::Ace::NG
