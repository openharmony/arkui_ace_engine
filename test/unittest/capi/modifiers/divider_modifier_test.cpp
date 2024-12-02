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
    modifier_->setColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "#FFFFFFFF");

    Ark_ResourceColor numberInt = { .selector = 1, .value1 = Converter::ArkValue<Ark_Number>(0x123456) };
    modifier_->setColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "#FF123456");

    Ark_ResourceColor numberFlt = { .selector = 1, .value1 = Converter::ArkValue<Ark_Number>(0.5f) };
    modifier_->setColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = { .selector = 2, .value2 = Converter::ArkValue<Ark_String>("#11223344") };
    modifier_->setColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = { .selector = 2, .value2 = Converter::ArkValue<Ark_String>("65535") };
    modifier_->setColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resNameColor = CreateResourceUnion<Ark_ResourceColor>(
        NamedResourceId{"aa.bb.cc", Converter::ResourceType::COLOR});
    modifier_->setColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    auto resIdColor = CreateResourceUnion<Ark_ResourceColor>(IntResourceId{1234, Converter::ResourceType::COLOR});
    modifier_->setColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)

    resNameColor = CreateResourceUnion<Ark_ResourceColor>(
        NamedResourceId{"incorrect_color", Converter::ResourceType::STRING});
    modifier_->setColor(node_, &resNameColor);
    auto checkVal9 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal9, "#FFFF0000");

    strNumber = { .selector = 2, .value2 = Converter::ArkValue<Ark_String>("incorrect_color") };
    modifier_->setColor(node_, &strNumber);
    auto checkVal10 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal10, "#FF000000");

    strNumber = { .selector = 2, .value2 = Converter::ArkValue<Ark_String>("") };
    modifier_->setColor(node_, &strNumber);
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

    modifier_->setVertical(node_, false);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "false");

    modifier_->setVertical(node_, true);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "true");

    modifier_->setVertical(node_, 0);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "false");

    modifier_->setVertical(node_, -25);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "true");

    modifier_->setVertical(node_, 0);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, "false");

    modifier_->setVertical(node_, 25);
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
    ASSERT_NE(modifier_->setVertical, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, LINE_CUP_BUTT);

    modifier_->setLineCap(node_, ARK_LINE_CAP_STYLE_SQUARE);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, LINE_CUP_SQUARE);

    modifier_->setLineCap(node_, ARK_LINE_CAP_STYLE_BUTT);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, LINE_CUP_BUTT);

    modifier_->setLineCap(node_, ARK_LINE_CAP_STYLE_ROUND);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, LINE_CUP_ROUND);

    modifier_->setLineCap(node_, static_cast<Ark_LineCapStyle>(-25));
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
    modifier_->setStrokeWidth(node_, &intVal);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123.00vp");

    Ark_Union_Number_String floatVal = { .selector = 0, .value0 = Converter::ArkValue<Ark_Number>(1.23f) };
    modifier_->setStrokeWidth(node_, &floatVal);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1.23vp");

    Ark_Union_Number_String pxVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("45px") };
    modifier_->setStrokeWidth(node_, &pxVal);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "45.00px");

    Ark_Union_Number_String vpVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("5.6vp") };
    modifier_->setStrokeWidth(node_, &vpVal);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "5.60vp");

    Ark_Union_Number_String percentVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("10%") };
    modifier_->setStrokeWidth(node_, &percentVal);
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
    modifier_->setStrokeWidth(node_, &intNegVal);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "-123.00vp");

    Ark_Union_Number_String floatNegVal = { .selector = 0, .value0 = Converter::ArkValue<Ark_Number>(-1.23f) };
    modifier_->setStrokeWidth(node_, &floatNegVal);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "-1.23vp");

    Ark_Union_Number_String pxNegVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("-4.5px") };
    modifier_->setStrokeWidth(node_, &pxNegVal);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "-4.50px");

    Ark_Union_Number_String vpNegVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("-56vp") };
    modifier_->setStrokeWidth(node_, &vpNegVal);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "-56.00vp");

    Ark_Union_Number_String undefVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("undefVal") };
    modifier_->setStrokeWidth(node_, &undefVal);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, "0.00fp");

    Ark_Union_Number_String percentNegVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("-10%") };
    modifier_->setStrokeWidth(node_, &percentNegVal);
    auto checkVal7 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal7, DEFAULT_STROKE_WIDTH);

    Ark_Union_Number_String emptyVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("") };
    modifier_->setStrokeWidth(node_, &emptyVal);
    auto checkVal8 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal8, "0.00fp");

    Ark_Union_Number_String invalidVal = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("qw111vp") };
    modifier_->setStrokeWidth(node_, &invalidVal);
    auto checkVal9 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal9, "0.00vp");

    Ark_Union_Number_String invalidVal2 = { .selector = 1, .value1 = Converter::ArkValue<Ark_String>("qw111") };
    modifier_->setStrokeWidth(node_, &invalidVal2);
    auto checkVal10 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal10, "0.00fp");
}
} // namespace OHOS::Ace::NG
