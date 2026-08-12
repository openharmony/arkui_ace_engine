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
#include "core/common/container.h"
#include "ui/base/versions.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme_wrapper.h"
#include "ui/view/theme/token_colors.h"
#include "ui/view/theme/token_theme.h"

using namespace testing;
using namespace testing::ext;
using OHOS::Ace::ColorMode;
using OHOS::Ace::Color;
using OHOS::Ace::TokenColors;
using OHOS::Ace::TokenTheme;

namespace OHOS::Ace::NG {

class RichEditorThemeWrapperTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->SetApiTargetVersion(
            static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    }
    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: RichEditorThemeWrapper_ApplyTokenTheme002
 * @tc.desc: ApplyTokenTheme does nothing when TokenTheme has no color palette.
 * @tc.type: FUNC
 * @tc.steps: step1. Create RichEditorThemeWrapper.
 *             step2. Create TokenTheme without colors.
 *             step3. Record default values before ApplyTokenTheme.
 *             step4. Call ApplyTokenTheme.
 *             step5. Verify all values remain unchanged.
 */
HWTEST_F(RichEditorThemeWrapperTest, RichEditorThemeWrapper_ApplyTokenTheme002, TestSize.Level1)
{
    auto wrapper = AceType::MakeRefPtr<RichEditorThemeWrapper>();
    ASSERT_NE(wrapper, nullptr);

    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(2);
    ASSERT_NE(tokenTheme, nullptr);
    tokenTheme->SetColorMode(ColorMode::LIGHT);

    const Color caretBefore = wrapper->GetCaretColor();
    const Color selectedBgBefore = wrapper->GetSelectedBackgroundColor();
    const Color dragBgBefore = wrapper->GetDragBackgroundColor();
    const Color placeholderBefore = wrapper->GetPlaceholderColor();
    const Color popIconBefore = wrapper->GetPopIconColor();
    const Color menuTitleBefore = wrapper->GetMenuTitleColor();
    const Color menuTextBefore = wrapper->GetMenuTextColor();
    const Color menuIconBefore = wrapper->GetMenuIconColor();

    wrapper->ApplyTokenTheme(*tokenTheme);

    EXPECT_EQ(wrapper->GetCaretColor(), caretBefore);
    EXPECT_EQ(wrapper->GetSelectedBackgroundColor(), selectedBgBefore);
    EXPECT_EQ(wrapper->GetDragBackgroundColor(), dragBgBefore);
    EXPECT_EQ(wrapper->GetPlaceholderColor(), placeholderBefore);
    EXPECT_EQ(wrapper->GetPopIconColor(), popIconBefore);
    EXPECT_EQ(wrapper->GetMenuTitleColor(), menuTitleBefore);
    EXPECT_EQ(wrapper->GetMenuTextColor(), menuTextBefore);
    EXPECT_EQ(wrapper->GetMenuIconColor(), menuIconBefore);
}

/**
 * @tc.name: RichEditorThemeWrapper_ApplyTokenTheme003
 * @tc.desc: ApplyTokenTheme does nothing when API target version is less than VERSION_TWENTY.
 * @tc.type: FUNC
 * @tc.steps: step1. Set API target version below VERSION_TWENTY.
 *             step2. Create RichEditorThemeWrapper and TokenTheme with colors.
 *             step3. Record default values before ApplyTokenTheme.
 *             step4. Call ApplyTokenTheme.
 *             step5. Verify all values remain unchanged due to version gate.
 */
HWTEST_F(RichEditorThemeWrapperTest, RichEditorThemeWrapper_ApplyTokenTheme003, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    auto wrapper = AceType::MakeRefPtr<RichEditorThemeWrapper>();
    ASSERT_NE(wrapper, nullptr);

    auto tokenColors = AceType::MakeRefPtr<TokenColors>();
    ASSERT_NE(tokenColors, nullptr);
    tokenColors->SetColor(static_cast<uint32_t>(TokenColors::FONT_PRIMARY), Color(0xFF111111));
    tokenColors->SetColor(static_cast<uint32_t>(TokenColors::COMP_BACKGROUND_EMPHASIZE), Color(0xFF666666));

    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(3);
    ASSERT_NE(tokenTheme, nullptr);
    tokenTheme->SetColors(tokenColors);
    tokenTheme->SetColorMode(ColorMode::LIGHT);

    const Color caretBefore = wrapper->GetCaretColor();
    const Color placeholderBefore = wrapper->GetPlaceholderColor();

    wrapper->ApplyTokenTheme(*tokenTheme);

    EXPECT_EQ(wrapper->GetCaretColor(), caretBefore);
    EXPECT_EQ(wrapper->GetPlaceholderColor(), placeholderBefore);

    // Restore API version for subsequent tests
    MockContainer::Current()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
}

} // namespace OHOS::Ace::NG
