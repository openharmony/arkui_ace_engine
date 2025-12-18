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

#include "core/components/divider/divider_theme.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const std::string LINE_CUP_BUTT = "BUTT";
const std::string LINE_CUP_ROUND = "ROUND";
const std::string LINE_CUP_SQUARE = "SQUARE";
const std::string DEFAULT_STROKE_WIDTH = "1.00px";
} // namespace

class DividerModifierTest : public ModifierTestBase<GENERATED_ArkUIDividerModifier,
    &GENERATED_ArkUINodeModifiers::getDividerModifier, GENERATED_ARKUI_DIVIDER> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<DividerTheme>();
    }
};

using OneColorStep = std::tuple<Ark_ResourceColor, std::string>;
const std::vector<OneColorStep> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE),
        "#FFFFFFFF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(Converter::ArkValue<Ark_Int32>(0x123456)), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(Converter::ArkValue<Ark_Int32>(0.5f)), "#00000000" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(Converter::ArkValue<Ark_String>("#11223344")), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>(Converter::ArkValue<Ark_String>("65535")), "#FF00FFFF" },
    { CreateResourceUnion<Ark_ResourceColor>(NamedResourceId{"aa.bb.cc", ResourceType::COLOR}),
        "#FFFF0000" },
    { CreateResourceUnion<Ark_ResourceColor>(IntResourceId{1234, ResourceType::COLOR}), "#FFFF0000" },
    { CreateResourceUnion<Ark_ResourceColor>(NamedResourceId{"incorrect_color", ResourceType::STRING}),
        "#FFFF0000" },
};

/**
 * @tc.name: DividerModifierTest001
 * @tc.desc: Check the functionality of DividerModifier.setColor
 * @tc.type: FUNC
 */
HWTEST_F(DividerModifierTest, DISABLED_DividerModifierTest001, TestSize.Level1)
{
    static const std::string PROP_NAME("color");
    ASSERT_NE(modifier_->setColor, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, "#FF000000");

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        auto color = Converter::ArkValue<Opt_ResourceColor>(value);
        modifier_->setColor(node_, &color);
        auto fullJson = GetJsonValue(node_);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }

    Ark_ResourceColor strNumber = { .selector = 2, .value2 = Converter::ArkValue<Ark_String>("incorrect_color") };
    auto optValue = Converter::ArkValue<Opt_ResourceColor>(strNumber);
    modifier_->setColor(node_, &optValue);
    auto checkVal10 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal10, "#FF000000");

    strNumber = { .selector = 2, .value2 = Converter::ArkValue<Ark_String>("") };
    optValue = Converter::ArkValue<Opt_ResourceColor>(strNumber);
    modifier_->setColor(node_, &optValue);
    auto checkVal11 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal11, "#FF000000");
}

/**
 * @tc.name: DividerModifierTest002
 * @tc.desc: Check the functionality of DividerModifier.setVertical
 * @tc.type: FUNC
 */
HWTEST_F(DividerModifierTest, DividerModifierTest002, TestSize.Level1)
{
    static const std::string PROP_NAME("vertical");
    ASSERT_NE(modifier_->setVertical, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, "true");

    auto optValue = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setVertical(node_, &optValue);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "false");

    optValue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setVertical(node_, &optValue);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "true");

    optValue = Converter::ArkValue<Opt_Boolean>(-25);
    modifier_->setVertical(node_, &optValue);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "true");

    optValue = Converter::ArkValue<Opt_Boolean>(0);
    modifier_->setVertical(node_, &optValue);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, "false");

    optValue = Converter::ArkValue<Opt_Boolean>(25);
    modifier_->setVertical(node_, &optValue);
    auto checkVal7 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal7, "true");
}

/**
 * @tc.name: DividerModifierTest003
 * @tc.desc: Check the functionality of DividerModifier.setLineCap
 * @tc.type: FUNC
 */
HWTEST_F(DividerModifierTest, DividerModifierTest003, TestSize.Level1)
{
    static const std::string PROP_NAME("lineCap");
    ASSERT_NE(modifier_->setLineCap, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, LINE_CUP_BUTT);

    auto optValue = Converter::ArkValue<Opt_LineCapStyle>(ARK_LINE_CAP_STYLE_SQUARE);
    modifier_->setLineCap(node_, &optValue);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, LINE_CUP_SQUARE);

    optValue = Converter::ArkValue<Opt_LineCapStyle>(ARK_LINE_CAP_STYLE_BUTT);
    modifier_->setLineCap(node_, &optValue);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, LINE_CUP_BUTT);

    optValue = Converter::ArkValue<Opt_LineCapStyle>(ARK_LINE_CAP_STYLE_ROUND);
    modifier_->setLineCap(node_, &optValue);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, LINE_CUP_ROUND);

    optValue = Converter::ArkValue<Opt_LineCapStyle>(static_cast<Ark_LineCapStyle>(-25));
    modifier_->setLineCap(node_, &optValue);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, LINE_CUP_BUTT);
}

/**
 * @tc.name: DividerModifierTest004
 * @tc.desc: Check the functionality of DividerModifier.setStrokeWidth
 * @tc.type: FUNC
 */
HWTEST_F(DividerModifierTest, DividerModifierTest004, TestSize.Level1)
{
    static const std::string PROP_NAME("strokeWidth");
    ASSERT_NE(modifier_->setStrokeWidth, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_STROKE_WIDTH);

    Opt_Union_F64_String intVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(123);
    modifier_->setStrokeWidth(node_, &intVal);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123.00vp");

    Opt_Union_F64_String floatVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(1.23f);
    modifier_->setStrokeWidth(node_, &floatVal);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1.23vp");

    Opt_Union_F64_String pxVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("45px");
    modifier_->setStrokeWidth(node_, &pxVal);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "45.00px");

    Opt_Union_F64_String vpVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("5.6vp");
    modifier_->setStrokeWidth(node_, &vpVal);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "5.60vp");

    Opt_Union_F64_String percentVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("10%");
    modifier_->setStrokeWidth(node_, &percentVal);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, DEFAULT_STROKE_WIDTH);
}

using OneWidthStep = std::tuple<Opt_Union_F64_String, std::string>;
const std::vector<OneWidthStep> WIDTH_TEST_PLAN = {
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(-123), "-123.00vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(-1.23f), "-1.23vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("-4.5px"), "-4.50px" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("-56vp"), "-56.00vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("undefVal"), "0.00vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("-10%"), DEFAULT_STROKE_WIDTH },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>(""), "0.00vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("qw111vp"), "0.00vp" },
    { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("qw111"), "0.00vp" },
};

/**
 * @tc.name: DividerModifierTest005
 * @tc.desc: Check the functionality of DividerModifier.setStrokeWidth for negative values
 * @tc.type: FUNC
 */
HWTEST_F(DividerModifierTest, DividerModifierTest005, TestSize.Level1)
{
    static const std::string PROP_NAME("strokeWidth");
    ASSERT_NE(modifier_->setStrokeWidth, nullptr);

    auto checkVal = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal, DEFAULT_STROKE_WIDTH);

    for (const auto& [value, expectVal] : WIDTH_TEST_PLAN) {
        auto width = Converter::ArkValue<Opt_Union_F64_String>(value);
        modifier_->setStrokeWidth(node_, &width);
        auto fullJson = GetJsonValue(node_);
        checkVal = GetStringAttribute(node_, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}
} // namespace OHOS::Ace::NG
