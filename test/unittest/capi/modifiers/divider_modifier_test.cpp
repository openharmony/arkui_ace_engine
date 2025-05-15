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

/**
 * @tc.name: DividerModifierTest001
 * @tc.desc: Check the functionality of DividerModifier.setColor
 * @tc.type: FUNC
 */
HWTEST_F(DividerModifierTest, DividerModifierTest001, TestSize.Level1)
{
    static const std::string PROP_NAME("color");
    ASSERT_NE(modifier_->setColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, "#FF000000");
    Ark_ResourceColor color = Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE);
    auto optValue = Converter::ArkValue<Opt_ResourceColor>(color);
    modifier_->setColor(node_, &optValue);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = { .selector = 1, .value1 = Converter::ArkValue<Ark_Number>(0x123456) };
    optValue = Converter::ArkValue<Opt_ResourceColor>(numberInt);
    modifier_->setColor(node_, &optValue);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "#FF123456");

    Ark_ResourceColor numberFlt = { .selector = 1, .value1 = Converter::ArkValue<Ark_Number>(0.5f) };
    optValue = Converter::ArkValue<Opt_ResourceColor>(numberFlt);
    modifier_->setColor(node_, &optValue);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = { .selector = 2, .value2 = Converter::ArkValue<Ark_String>("#11223344") };
    optValue = Converter::ArkValue<Opt_ResourceColor>(strColor);
    modifier_->setColor(node_, &optValue);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = { .selector = 2, .value2 = Converter::ArkValue<Ark_String>("65535") };
    optValue = Converter::ArkValue<Opt_ResourceColor>(strNumber);
    modifier_->setColor(node_, &optValue);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resNameColor = CreateResourceUnion<Ark_ResourceColor>(
        NamedResourceId{"aa.bb.cc", Converter::ResourceType::COLOR});
    optValue = Converter::ArkValue<Opt_ResourceColor>(resNameColor);
    modifier_->setColor(node_, &optValue);
    auto checkVal7 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    auto resIdColor = CreateResourceUnion<Ark_ResourceColor>(IntResourceId{1234, Converter::ResourceType::COLOR});
    optValue = Converter::ArkValue<Opt_ResourceColor>(resIdColor);
    modifier_->setColor(node_, &optValue);
    auto checkVal8 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)

    resNameColor = CreateResourceUnion<Ark_ResourceColor>(
        NamedResourceId{"incorrect_color", Converter::ResourceType::STRING});
    optValue = Converter::ArkValue<Opt_ResourceColor>(resNameColor);
    modifier_->setColor(node_, &optValue);
    auto checkVal9 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal9, "#FFFF0000"); // Should be Color::RED, but converter from Resource works incorrect now.
                                       // So modifier pass Color::BLACK to divider component int this case

    strNumber = { .selector = 2, .value2 = Converter::ArkValue<Ark_String>("incorrect_color") };
    optValue = Converter::ArkValue<Opt_ResourceColor>(strNumber);
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

    Ark_Union_Number_String intVal = { .selector = 0, .value0 = Converter::ArkValue<Ark_Number>(123) };
    auto optValue = Converter::ArkValue<Opt_Union_Number_String>(intVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123.00vp");

    Ark_Union_Number_String floatVal = { .selector = 0, .value0 = Converter::ArkValue<Ark_Number>(1.23f) };
    optValue = Converter::ArkValue<Opt_Union_Number_String>(floatVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1.23vp");

    Ark_Union_Number_String pxVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("45px") };
    optValue = Converter::ArkValue<Opt_Union_Number_String>(pxVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "45.00px");

    Ark_Union_Number_String vpVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("5.6vp") };
    optValue = Converter::ArkValue<Opt_Union_Number_String>(vpVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "5.60vp");

    Ark_Union_Number_String percentVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("10%") };
    optValue = Converter::ArkValue<Opt_Union_Number_String>(percentVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, DEFAULT_STROKE_WIDTH);
}

/**
 * @tc.name: DividerModifierTest005
 * @tc.desc: Check the functionality of DividerModifier.setStrokeWidth for negative values
 * @tc.type: FUNC
 */
HWTEST_F(DividerModifierTest, DividerModifierTest005, TestSize.Level1)
{
    static const std::string PROP_NAME("strokeWidth");
    ASSERT_NE(modifier_->setStrokeWidth, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, DEFAULT_STROKE_WIDTH);

    Ark_Union_Number_String intNegVal = { .selector = 0, .value0 = Converter::ArkValue<Ark_Number>(-123) };
    auto optValue = Converter::ArkValue<Opt_Union_Number_String>(intNegVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "-123.00vp");

    Ark_Union_Number_String floatNegVal = { .selector = 0, .value0 = Converter::ArkValue<Ark_Number>(-1.23f) };
    optValue = Converter::ArkValue<Opt_Union_Number_String>(floatNegVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "-1.23vp");

    Ark_Union_Number_String pxNegVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("-4.5px") };
    optValue = Converter::ArkValue<Opt_Union_Number_String>(pxNegVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "-4.50px");

    Ark_Union_Number_String vpNegVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("-56vp") };
    optValue = Converter::ArkValue<Opt_Union_Number_String>(vpNegVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "-56.00vp");

    Ark_Union_Number_String undefVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("undefVal") };
    optValue = Converter::ArkValue<Opt_Union_Number_String>(undefVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, "0.00fp");

    Ark_Union_Number_String percentNegVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("-10%") };
    optValue = Converter::ArkValue<Opt_Union_Number_String>(percentNegVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal7 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal7, DEFAULT_STROKE_WIDTH);

    Ark_Union_Number_String emptyVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("") };
    optValue = Converter::ArkValue<Opt_Union_Number_String>(emptyVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal8 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal8, "0.00fp");

    Ark_Union_Number_String invalidVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("qw111vp") };
    optValue = Converter::ArkValue<Opt_Union_Number_String>(invalidVal);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal9 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal9, "0.00vp");

    Ark_Union_Number_String invalidVal2 = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("qw111") };
    optValue = Converter::ArkValue<Opt_Union_Number_String>(invalidVal2);
    modifier_->setStrokeWidth(node_, &optValue);
    auto checkVal10 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal10, "0.00fp");
}
} // namespace OHOS::Ace::NG
