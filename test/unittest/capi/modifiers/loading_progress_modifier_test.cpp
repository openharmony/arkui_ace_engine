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

#include "core/components/progress/progress_theme.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

const Color THEME_LOADING_COLOR(0xFFAABBCC);

namespace {
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

class LoadingProgressModifierTest : public ModifierTestBase<GENERATED_ArkUILoadingProgressModifier,
    &GENERATED_ArkUINodeModifiers::getLoadingProgressModifier, GENERATED_ARKUI_LOADING_PROGRESS> {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();

        // assume using of test/mock/core/common/mock_theme_constants.cpp in build
        auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
        themeStyle->SetAttr("fg_progress_color", { .value = THEME_LOADING_COLOR });
        MockThemeStyle::GetInstance()->SetAttr("progress_pattern", { .value = themeStyle });
        themeConstants->LoadTheme(0);

        auto builder = ProgressTheme::Builder();
        auto theme = builder.Build(themeConstants);

        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetThemeConstants(testing::_, testing::_)).WillRepeatedly(Return(themeConstants));
        EXPECT_CALL(*themeManager, GetTheme(testing::_)).WillRepeatedly(Return(theme));

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
 * @tc.name: LoadingProgressModifierTest001
 * @tc.desc: Test color attribute
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressModifierTest, LoadingProgressModifierTest001, TestSize.Level1)
{
    static const std::string PROP_NAME("color");
    ASSERT_NE(modifier_->setColor, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, THEME_LOADING_COLOR.ToString());

    Ark_ResourceColor color = ArkUnion<Ark_ResourceColor, Ark_Color, int>(0xFF123400);
    modifier_->setColor(node_, &color);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "#FF123400");

    Ark_ResourceColor numberInt = ArkUnion<Ark_ResourceColor, Ark_Number>(0x123401);
    modifier_->setColor(node_, &numberInt);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "#FF123401");

    Ark_ResourceColor numberFlt = ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f);
    modifier_->setColor(node_, &numberFlt);
    auto checkVal4 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal4, "#00000000");

    Ark_ResourceColor strColor = ArkUnion<Ark_ResourceColor, Ark_String>("#11223344");
    modifier_->setColor(node_, &strColor);
    auto checkVal5 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal5, "#11223344");

    Ark_ResourceColor strNumber = ArkUnion<Ark_ResourceColor, Ark_String>("65535");
    modifier_->setColor(node_, &strNumber);
    auto checkVal6 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal6, "#FF00FFFF");

    auto resName = ArkValue<Ark_String>("aa.bb.cc");
    Ark_ResourceColor resNameColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&resName));
    modifier_->setColor(node_, &resNameColor);
    auto checkVal7 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal7, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColorByName

    Ark_ResourceColor resIdColor = ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 1234));
    modifier_->setColor(node_, &resIdColor);
    auto checkVal8 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal8, "#FFFF0000"); // Color::RED is result of mocked ThemeConstants::GetColor(int)
}

/**
 * @tc.name: LoadingProgressModifierTest001
 * @tc.desc: Test enableLoading attribute
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressModifierTest, LoadingProgressModifierTest002, TestSize.Level1)
{
    static const std::string PROP_NAME("enableLoading");
    ASSERT_NE(modifier_->setEnableLoading, nullptr);

    auto checkVal1 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal1, "true");

    modifier_->setEnableLoading(node_, false);
    auto checkVal2 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal2, "false");

    modifier_->setEnableLoading(node_, true);
    auto checkVal3 = GetStringAttribute(node_, PROP_NAME);
    EXPECT_EQ(checkVal3, "true");
}

} // namespace OHOS::Ace::NG