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
} // namespace

class BlankModifierTest : public ModifierTestBase<GENERATED_ArkUIBlankModifier,
    &GENERATED_ArkUINodeModifiers::getBlankModifier, GENERATED_ARKUI_BLANK> {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        // assume using of test/mock/core/common/mock_theme_constants.cpp in build
        auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
        EXPECT_CALL(*themeManager, GetThemeConstants(testing::_, testing::_)).WillRepeatedly(Return(themeConstants));
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::SetUp(MockPipelineContext::GetCurrent());
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: BlankModifierTest001
 * @tc.desc: Check the functionality of BlankModifier.setColor
 * @tc.type: FUNC
 */
HWTEST_F(BlankModifierTest, BlankModifierTest001, TestSize.Level1)
{
    static const std::string PROP_NAME("color");
    ASSERT_NE(modifier_->setColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, "#00000000");
    Ark_ResourceColor color = { .selector = 0, .value0 = 0x12345678 };
    modifier_->setColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "#12345678");

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
}

/**
 * @tc.name: BlankModifierTest002
 * @tc.desc: Check the functionality of BlankModifier.setBlankOptions
 * @tc.type: FUNC
 */
HWTEST_F(BlankModifierTest, BlankModifierTest002, TestSize.Level1)
{
    static const std::string PROP_NAME("min");
    ASSERT_NE(modifier_->setBlankOptions, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, "0.00px");

    Opt_Type_BlankInterface_setBlankOptions_Arg0 intVal
        = { .tag = ARK_TAG_OBJECT, .value = { .selector = 0, .value0 = ArkNum(123) } };
    modifier_->setBlankOptions(node_, &intVal);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "123.00vp");

    Opt_Type_BlankInterface_setBlankOptions_Arg0 floatVal
        = { .tag = ARK_TAG_OBJECT, .value = { .selector = 0, .value0 = ArkNum(1.23f) } };
    modifier_->setBlankOptions(node_, &floatVal);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "1.23vp");

    Opt_Type_BlankInterface_setBlankOptions_Arg0 pxVal
        = { .tag = ARK_TAG_OBJECT, .value = { .selector = 1, .value1 = ArkStr("45px") } };
    modifier_->setBlankOptions(node_, &pxVal);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "45.00px");

    Opt_Type_BlankInterface_setBlankOptions_Arg0 vpVal
        = { .tag = ARK_TAG_OBJECT, .value = { .selector = 1, .value1 = ArkStr("5.6vp") } };
    modifier_->setBlankOptions(node_, &vpVal);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, "5.60vp");

    Opt_Type_BlankInterface_setBlankOptions_Arg0 intNegVal
        = { .tag = ARK_TAG_OBJECT, .value = { .selector = 0, .value0 = ArkNum(-123) } };
    modifier_->setBlankOptions(node_, &intNegVal);
    auto checkVal7 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal7, "0.00vp");

    Opt_Type_BlankInterface_setBlankOptions_Arg0 floatNegVal
        = { .tag = ARK_TAG_OBJECT, .value = { .selector = 0, .value0 = ArkNum(-1.23f) } };
    modifier_->setBlankOptions(node_, &floatNegVal);
    auto checkVal8 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal8, "0.00vp");

    Opt_Type_BlankInterface_setBlankOptions_Arg0 pxNegVal
        = { .tag = ARK_TAG_OBJECT, .value = { .selector = 1, .value1 = ArkStr("-4.5px") } };
    modifier_->setBlankOptions(node_, &pxNegVal);
    auto checkVal9 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal9, "0.00vp");

    Opt_Type_BlankInterface_setBlankOptions_Arg0 vpNegVal
        = { .tag = ARK_TAG_OBJECT, .value = { .selector = 1, .value1 = ArkStr("-56vp") } };
    modifier_->setBlankOptions(node_, &vpNegVal);
    auto checkVal10 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal10, "0.00vp");

    Opt_Type_BlankInterface_setBlankOptions_Arg0 undefVal = { .tag = ARK_TAG_UNDEFINED };
    modifier_->setBlankOptions(node_, &undefVal);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "0.00px");
}
} // namespace OHOS::Ace::NG
