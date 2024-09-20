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
#include "node_api.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/divider/divider_theme.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
inline Ark_Number ArkNum(float src)
{
    return {.tag= ARK_TAG_FLOAT32, .f32 = static_cast<Ark_Float32>(src)
    };
}

inline Ark_Number ArkNum(int src)
{
    return {.tag= ARK_TAG_INT32, .i32 = static_cast<Ark_Int32>(src)
    };
}

inline Ark_String ArkStr(const char *s)
{
    return {.chars = s, .length = strlen(s)
    };
}

inline Ark_Resource ArkRes(Ark_String *name, int id = -1,
    NodeModifier::ResourceType type = NodeModifier::ResourceType::COLOR,
    const char *module = "", const char *bundle = "")
{
    return {
        .id = ArkNum(id),
        .type = ArkNum(static_cast<int>(type)),
        .moduleName = ArkStr(module),
        .bundleName = ArkStr(bundle),
        .params = { .tag = ARK_TAG_OBJECT, .value = {.array = name, .length = name ? 1 : 0} }
    };
}

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
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            auto builder = DividerTheme::Builder();
            auto dividerTheme = builder.Build(nullptr);
            return dividerTheme;
        });
        auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
        EXPECT_CALL(*themeManager, GetThemeConstants(testing::_, testing::_)).WillRepeatedly(Return(themeConstants));
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::SetUp(MockPipelineContext::GetCurrent());
        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
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

    Ark_ResourceColor numberInt = { .selector = 1, .value1 = ArkNum(0x123456) };
    modifier_->setColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "#FF123456");

    Ark_ResourceColor numberFlt = { .selector = 1, .value1 = ArkNum(0.5f) };
    modifier_->setColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = { .selector = 2, .value2 = ArkStr("#11223344") };
    modifier_->setColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = { .selector = 2, .value2 = ArkStr("65535") };
    modifier_->setColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resName = ArkStr("aa.bb.cc");
    Ark_ResourceColor resNameColor = { .selector = 3, .value3 = ArkRes(&resName) };
    modifier_->setColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    Ark_ResourceColor resIdColor = { .selector = 3, .value3 = ArkRes(nullptr, 1234) };
    modifier_->setColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)

    resName = ArkStr("incorrect_color");
    resNameColor = { .selector = 3, .value3 = ArkRes(&resName, 2,  NodeModifier::ResourceType::STRING) };
    modifier_->setColor(node_, &resNameColor);
    auto checkVal9 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal9, "#FF000000"); // Should be Color::RED, but converter from Resource works incorrect now.
                                       // So modifier pass Color::BLACK to divider component int this case

    strNumber = { .selector = 2, .value2 = ArkStr("incorrect_color") };
    modifier_->setColor(node_, &strNumber);
    auto checkVal10 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal10, "#FF000000");

    strNumber = { .selector = 2, .value2 = ArkStr("") };
    modifier_->setColor(node_, &strNumber);
    auto checkVal11 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal11, "#00000000");
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

    Type_DividerAttribute_strokeWidth_Arg0 intVal = { .selector = 0, .value0 = ArkNum(123) };
    modifier_->setStrokeWidth(node_, &intVal);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "123.00vp");

    Type_DividerAttribute_strokeWidth_Arg0 floatVal = { .selector = 0, .value0 = ArkNum(1.23f) };
    modifier_->setStrokeWidth(node_, &floatVal);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "1.23vp");

    Type_DividerAttribute_strokeWidth_Arg0 pxVal = { .selector = 1, .value1 = ArkStr("45px") };
    modifier_->setStrokeWidth(node_, &pxVal);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "45.00px");

    Type_DividerAttribute_strokeWidth_Arg0 vpVal = { .selector = 1, .value1 = ArkStr("5.6vp") };
    modifier_->setStrokeWidth(node_, &vpVal);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "5.60vp");

    Type_DividerAttribute_strokeWidth_Arg0 percentVal = { .selector = 1, .value1 = ArkStr("10%") };
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

    Type_DividerAttribute_strokeWidth_Arg0 intNegVal = { .selector = 0, .value0 = ArkNum(-123) };
    modifier_->setStrokeWidth(node_, &intNegVal);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "-123.00vp");

    Type_DividerAttribute_strokeWidth_Arg0 floatNegVal = { .selector = 0, .value0 = ArkNum(-1.23f) };
    modifier_->setStrokeWidth(node_, &floatNegVal);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "-1.23vp");

    Type_DividerAttribute_strokeWidth_Arg0 pxNegVal = { .selector = 1, .value1 = ArkStr("-4.5px") };
    modifier_->setStrokeWidth(node_, &pxNegVal);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "-4.50px");

    Type_DividerAttribute_strokeWidth_Arg0 vpNegVal = { .selector = 1, .value1 = ArkStr("-56vp") };
    modifier_->setStrokeWidth(node_, &vpNegVal);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "-56.00vp");

    Type_DividerAttribute_strokeWidth_Arg0 undefVal = { .selector = 1, .value1 = ArkStr("undefVal") };
    modifier_->setStrokeWidth(node_, &undefVal);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, "0.00fp");

    Type_DividerAttribute_strokeWidth_Arg0 percentNegVal = { .selector = 1, .value1 = ArkStr("-10%") };
    modifier_->setStrokeWidth(node_, &percentNegVal);
    auto checkVal7 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal7, DEFAULT_STROKE_WIDTH);

    Type_DividerAttribute_strokeWidth_Arg0 emptyVal = { .selector = 1, .value1 = ArkStr("") };
    modifier_->setStrokeWidth(node_, &emptyVal);
    auto checkVal8 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal8, "0.00fp");

    Type_DividerAttribute_strokeWidth_Arg0 invalidVal = { .selector = 1, .value1 = ArkStr("qw111vp") };
    modifier_->setStrokeWidth(node_, &invalidVal);
    auto checkVal9 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal9, "0.00vp");

    Type_DividerAttribute_strokeWidth_Arg0 invalidVal2 = { .selector = 1, .value1 = ArkStr("qw111") };
    modifier_->setStrokeWidth(node_, &invalidVal2);
    auto checkVal10 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal10, "0.00fp");
}
} // namespace OHOS::Ace::NG
