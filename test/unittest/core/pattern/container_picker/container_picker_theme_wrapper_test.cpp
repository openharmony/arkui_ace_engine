/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/container_picker/container_picker_theme_wrapper.h"
#include "ui/view/theme/token_colors.h"
#include "ui/view/theme/token_theme.h"

using namespace testing;
using namespace testing::ext;
using OHOS::Ace::ColorMode;
using OHOS::Ace::TokenColors;
using OHOS::Ace::TokenTheme;

namespace OHOS::Ace::NG {

class ContainerPickerThemeWrapperTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: ContainerPickerThemeWrapper_ApplyTokenTheme001
 * @tc.desc: ApplyTokenTheme copies token colors into font, indicator background, and divider fields.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerThemeWrapperTest, ContainerPickerThemeWrapper_ApplyTokenTheme001, TestSize.Level1)
{
    auto wrapper = AceType::MakeRefPtr<ContainerPickerThemeWrapper>();
    ASSERT_NE(wrapper, nullptr);

    auto tokenColors = AceType::MakeRefPtr<TokenColors>();
    ASSERT_NE(tokenColors, nullptr);
    const Color fontPrimary = Color::RED;
    const Color compBgTertiary = Color::GREEN;
    const Color compDivider = Color::BLUE;
    tokenColors->SetColor(static_cast<uint32_t>(TokenColors::FONT_PRIMARY), fontPrimary);
    tokenColors->SetColor(static_cast<uint32_t>(TokenColors::COMP_BACKGROUND_TERTIARY), compBgTertiary);
    tokenColors->SetColor(static_cast<uint32_t>(TokenColors::COMP_DIVIDER), compDivider);

    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(1);
    ASSERT_NE(tokenTheme, nullptr);
    tokenTheme->SetColors(tokenColors);
    tokenTheme->SetColorMode(ColorMode::LIGHT);

    wrapper->ApplyTokenTheme(*tokenTheme);

    EXPECT_EQ(wrapper->GetFontColor(), fontPrimary);
    EXPECT_EQ(wrapper->GetIndicatorBackgroundColor(), compBgTertiary);
    EXPECT_EQ(wrapper->GetIndicatorDividerColor(), compDivider);
}

/**
 * @tc.name: ContainerPickerThemeWrapper_ApplyTokenTheme002
 * @tc.desc: ApplyTokenTheme does nothing when TokenTheme has no color palette.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerThemeWrapperTest, ContainerPickerThemeWrapper_ApplyTokenTheme002, TestSize.Level1)
{
    auto wrapper = AceType::MakeRefPtr<ContainerPickerThemeWrapper>();
    ASSERT_NE(wrapper, nullptr);

    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(2);
    ASSERT_NE(tokenTheme, nullptr);
    tokenTheme->SetColorMode(ColorMode::LIGHT);

    const Color fontBefore = wrapper->GetFontColor();
    const Color bgBefore = wrapper->GetIndicatorBackgroundColor();
    const Color divBefore = wrapper->GetIndicatorDividerColor();

    wrapper->ApplyTokenTheme(*tokenTheme);

    EXPECT_EQ(wrapper->GetFontColor(), fontBefore);
    EXPECT_EQ(wrapper->GetIndicatorBackgroundColor(), bgBefore);
    EXPECT_EQ(wrapper->GetIndicatorDividerColor(), divBefore);
}

} // namespace OHOS::Ace::NG
