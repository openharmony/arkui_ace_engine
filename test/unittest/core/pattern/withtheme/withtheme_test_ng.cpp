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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/with_theme_node.h"
#include "core/components_ng/token_theme/token_theme_storage.h"

#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/theme_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct TestProperty {
    const ArkUI_Uint32 colors_[TokenColors::TOTAL_NUMBER] = {
        // id for color value for test
        125830976, /* BRAND = 0 */
        125830979, /* WARNING = 1; */
        125830980, /* ALERT = 2 */
        125830981, /* CONFIRM = 3 */
        125830982, /* FONT_PRIMARY = 4 */
        125830983, /* FONT_SECONDARY = 5 */
        125830984, /* FONT_TERTIARY = 6 */
        125830985, /* FONT_FOURTH = 7 */
        125830986, /* FONT_EMPHASIZE = 8 */
        125830987, /* FONT_ON_PRIMARY = 9 */
        125830988, /* FONT_ON_SECONDARY = 10 */
        125830989, /* FONT_ON_TERTIARY = 11 */
        125830990, /* FONT_ON_FOURTH = 12 */
        125830991, /* ICON_PRIMARY = 13 */
        125830992, /* ICON_SECONDARY = 14 */
        125830993, /* ICON_TERTIARY = 15 */
        125830994, /* ICON_FOURTH = 16 */
        125830995, /* ICON_EMPHASIZE = 17 */
        125830996, /* ICON_SUB_EMPHASIZE = 18 */
        125831057, /* ICON_ON_PRIMARY = 19 */
        125831058, /* ICON_ON_SECONDARY = 20 */
        125831059, /* ICON_ON_TERTIARY = 21 */
        125831060, /* ICON_ON_FOURTH = 22 */
        125831061, /* BACKGROUND_PRIMARY = 23 */
        125831062, /* BACKGROUND_SECONDARY = 24 */
        125831063, /* BACKGROUND_TERTIARY = 25 */
        125831064, /* BACKGROUND_FOURTH = 26 */
        125831065, /* BACKGROUND_EMPHASIZE = 27 */
        125831003, /* COMP_FOREGROUND_PRIMARY = 28 */
        125831004, /* COMP_BACKGROUND_PRIMARY = 29 */
        -1,        /* COMP_BACKGROUND_PRIMARY_TRAN = 30 */
        125831005, /* COMP_BACKGROUND_PRIMARY_CONTRARY = 31 */
        125831006, /* COMP_BACKGROUND_GRAY = 32 */
        125831007, /* COMP_BACKGROUND_SECONDARY = 33 */
        125831008, /* COMP_BACKGROUND_TERTIARY = 34 */
        125831009, /* COMP_BACKGROUND_EMPHASIZE = 35 */
        125831066, /* COMP_BACKGROUND_NEUTRAL = 36 */
        125831011, /* COMP_EMPHASIZE_SECONDARY = 37 */
        125831012, /* COMP_EMPHASIZE_TERTIARY = 38 */
        125831013, /* COMP_DIVIDER = 39 */
        125831014, /* COMP_COMMON_CONTRARY = 40 */
        125831015, /* COMP_BACKGROUND_FOCUS = 41 */
        125831016, /* COMP_FOCUSED_PRIMARY = 42 */
        125831017, /* COMP_FOCUSED_SECONDARY = 43 */
        125831018, /* COMP_FOCUSED_TERTIARY = 44 */
        125831019, /* INTERACTIVE_HOVER = 45 */
        125831020, /* INTERACTIVE_PRESSED = 46 */
        125831021, /* INTERACTIVE_FOCUS = 47 */
        125831022, /* INTERACTIVE_ACTIVE = 48 */
        125831023, /* INTERACTIVE_SELECT = 49 */
        125831024, /* INTERACTIVE_CLICK = 50 */
    };
    RefPtr<WithThemeNode> withThemeNode_;
    RefPtr<TokenColors> tokenColors_;
};
namespace {
    constexpr uint32_t WITH_THEME_NODE_ID = 10086;
    constexpr uint32_t TOKEN_THEME_ID = 10001;
    constexpr ColorMode THEME_COLOR_MODE = ColorMode::DARK;
    TestProperty g_testProperty;
}

class WithThemeTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp();
    void TearDown() {}

protected:
    static RefPtr<WithThemeNode> CreateWithThemeNode();
};

void WithThemeTestNg::SetUpTestSuite()
{
    g_testProperty.withThemeNode_ = CreateWithThemeNode();
    std::vector<Color> colors;
    colors.reserve(TokenColors::TOTAL_NUMBER);
    for (int i = 0; i < TokenColors::TOTAL_NUMBER; i++) {
        colors.push_back(Color(g_testProperty.colors_[i]));
    }
    auto themeColors = AceType::MakeRefPtr<TokenColors>();
    themeColors->SetColors(std::move(colors));
    g_testProperty.tokenColors_ = themeColors;
}

void WithThemeTestNg::TearDownTestSuite()
{
}

void WithThemeTestNg::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<WithThemeNode> WithThemeTestNg::CreateWithThemeNode()
{
    return WithThemeNode::CreateWithThemeNode(WITH_THEME_NODE_ID);
}

/**
 * @tc.name: WithThemeTestNg001
 * @tc.desc: Create withThemeNode.
 * @tc.type: FUNC
 */
HWTEST_F(WithThemeTestNg, WithThemeTest001, TestSize.Level1)
{
    EXPECT_TRUE(g_testProperty.withThemeNode_);
    EXPECT_EQ(g_testProperty.withThemeNode_->GetTag(), V2::JS_WITH_THEME_ETS_TAG);
}

/**
 * @tc.name: WithThemeTestNg002
 * @tc.desc: Get withThemeNode
 * @tc.type: FUNC
 */
HWTEST_F(WithThemeTestNg, WithThemeTest002, TestSize.Level1)
{
    auto withThemeNode = WithThemeNode::GetWithThemeNode(WITH_THEME_NODE_ID);
    EXPECT_TRUE(withThemeNode);
}

/**
 * @tc.name: WithThemeTestNg003
 * @tc.desc: Create Theme
 * @tc.type: FUNC
 */
HWTEST_F(WithThemeTestNg, WithThemeTest003, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<TokenTheme>(TOKEN_THEME_ID);
    theme->SetColors(g_testProperty.tokenColors_);
    theme->SetColorMode(THEME_COLOR_MODE);
    TokenThemeStorage::GetInstance()->CacheSet(theme);
    EXPECT_TRUE(theme);
}

/**
 * @tc.name: WithThemeTestNg004
 * @tc.desc: Get Theme
 * @tc.type: FUNC
 */
HWTEST_F(WithThemeTestNg, WithThemeTest004, TestSize.Level1)
{
    auto theme = TokenThemeStorage::GetInstance()->CacheGet(TOKEN_THEME_ID);
    EXPECT_TRUE(theme);
    EXPECT_EQ(theme->GetColorMode(), ColorMode::DARK);
}

/**
 * @tc.name: WithThemeTestNg005
 * @tc.desc: Get Theme Colors
 * @tc.type: FUNC
 */
HWTEST_F(WithThemeTestNg, WithThemeTest005, TestSize.Level1)
{
    auto theme = TokenThemeStorage::GetInstance()->CacheGet(TOKEN_THEME_ID);
    EXPECT_TRUE(theme);
    auto colors = theme->Colors();
    EXPECT_TRUE(colors);
    auto gColors = g_testProperty.colors_;
    EXPECT_EQ(colors->Brand(), Color(gColors[TokenColors::BRAND]));
    EXPECT_EQ(colors->Warning(), Color(gColors[TokenColors::WARNING]));
    EXPECT_EQ(colors->Alert(), Color(gColors[TokenColors::ALERT]));
    EXPECT_EQ(colors->Confirm(), Color(gColors[TokenColors::CONFIRM]));
    EXPECT_EQ(colors->FontPrimary(), Color(gColors[TokenColors::FONT_PRIMARY]));
    EXPECT_EQ(colors->FontSecondary(), Color(gColors[TokenColors::FONT_SECONDARY]));
    EXPECT_EQ(colors->FontTertiary(), Color(gColors[TokenColors::FONT_TERTIARY]));
    EXPECT_EQ(colors->FontFourth(), Color(gColors[TokenColors::FONT_FOURTH]));
    EXPECT_EQ(colors->FontEmphasize(), Color(gColors[TokenColors::FONT_EMPHASIZE]));
    EXPECT_EQ(colors->FontOnPrimary(), Color(gColors[TokenColors::FONT_ON_PRIMARY]));
    EXPECT_EQ(colors->FontOnSecondary(), Color(gColors[TokenColors::FONT_ON_SECONDARY]));
    EXPECT_EQ(colors->FontOnTertiary(), Color(gColors[TokenColors::FONT_ON_TERTIARY]));
    EXPECT_EQ(colors->FontOnFourth(), Color(gColors[TokenColors::FONT_ON_FOURTH]));
    EXPECT_EQ(colors->IconPrimary(), Color(gColors[TokenColors::ICON_PRIMARY]));
    EXPECT_EQ(colors->IconSecondary(), Color(gColors[TokenColors::ICON_SECONDARY]));
    EXPECT_EQ(colors->IconTertiary(), Color(gColors[TokenColors::ICON_TERTIARY]));
    EXPECT_EQ(colors->IconFourth(), Color(gColors[TokenColors::ICON_FOURTH]));
    EXPECT_EQ(colors->IconEmphasize(), Color(gColors[TokenColors::ICON_EMPHASIZE]));
    EXPECT_EQ(colors->IconSubEmphasize(), Color(gColors[TokenColors::ICON_SUB_EMPHASIZE]));
    EXPECT_EQ(colors->IconOnPrimary(), Color(gColors[TokenColors::ICON_ON_PRIMARY]));
    EXPECT_EQ(colors->IconOnSecondary(), Color(gColors[TokenColors::ICON_ON_SECONDARY]));
    EXPECT_EQ(colors->IconOnTertiary(), Color(gColors[TokenColors::ICON_ON_TERTIARY]));
    EXPECT_EQ(colors->IconOnFourth(), Color(gColors[TokenColors::ICON_ON_FOURTH]));
    EXPECT_EQ(colors->BackgroundPrimary(), Color(gColors[TokenColors::BACKGROUND_PRIMARY]));
    EXPECT_EQ(colors->BackgroundSecondary(), Color(gColors[TokenColors::BACKGROUND_SECONDARY]));
    EXPECT_EQ(colors->BackgroundTertiary(), Color(gColors[TokenColors::BACKGROUND_TERTIARY]));
    EXPECT_EQ(colors->BackgroundFourth(), Color(gColors[TokenColors::BACKGROUND_FOURTH]));
    EXPECT_EQ(colors->BackgroundEmphasize(), Color(gColors[TokenColors::BACKGROUND_EMPHASIZE]));
    EXPECT_EQ(colors->CompForegroundPrimary(), Color(gColors[TokenColors::COMP_FOREGROUND_PRIMARY]));
    EXPECT_EQ(colors->CompBackgroundPrimary(), Color(gColors[TokenColors::COMP_BACKGROUND_PRIMARY]));
    EXPECT_EQ(colors->CompBackgroundPrimaryTran(), Color(gColors[TokenColors::COMP_BACKGROUND_PRIMARY_TRAN]));
    EXPECT_EQ(colors->CompBackgroundPrimaryContrary(), Color(gColors[TokenColors::COMP_BACKGROUND_PRIMARY_CONTRARY]));
    EXPECT_EQ(colors->CompBackgroundGray(), Color(gColors[TokenColors::COMP_BACKGROUND_GRAY]));
    EXPECT_EQ(colors->CompBackgroundSecondary(), Color(gColors[TokenColors::COMP_BACKGROUND_SECONDARY]));
    EXPECT_EQ(colors->CompBackgroundTertiary(), Color(gColors[TokenColors::COMP_BACKGROUND_TERTIARY]));
    EXPECT_EQ(colors->CompBackgroundEmphasize(), Color(gColors[TokenColors::COMP_BACKGROUND_EMPHASIZE]));
    EXPECT_EQ(colors->CompBackgroundNeutral(), Color(gColors[TokenColors::COMP_BACKGROUND_NEUTRAL]));
    EXPECT_EQ(colors->CompEmphasizeSecondary(), Color(gColors[TokenColors::COMP_EMPHASIZE_SECONDARY]));
    EXPECT_EQ(colors->CompEmphasizeTertiary(), Color(gColors[TokenColors::COMP_EMPHASIZE_TERTIARY]));
    EXPECT_EQ(colors->CompDivider(), Color(gColors[TokenColors::COMP_DIVIDER]));
    EXPECT_EQ(colors->CompCommonContrary(), Color(gColors[TokenColors::COMP_COMMON_CONTRARY]));
    EXPECT_EQ(colors->CompBackgroundFocus(), Color(gColors[TokenColors::COMP_BACKGROUND_FOCUS]));
    EXPECT_EQ(colors->CompFocusedPrimary(), Color(gColors[TokenColors::COMP_FOCUSED_PRIMARY]));
    EXPECT_EQ(colors->CompFocusedSecondary(), Color(gColors[TokenColors::COMP_FOCUSED_SECONDARY]));
    EXPECT_EQ(colors->CompFocusedTertiary(), Color(gColors[TokenColors::COMP_FOCUSED_TERTIARY]));
    EXPECT_EQ(colors->InteractiveHover(), Color(gColors[TokenColors::INTERACTIVE_HOVER]));
    EXPECT_EQ(colors->InteractivePressed(), Color(gColors[TokenColors::INTERACTIVE_PRESSED]));
    EXPECT_EQ(colors->InteractiveFocus(), Color(gColors[TokenColors::INTERACTIVE_FOCUS]));
    EXPECT_EQ(colors->InteractiveActive(), Color(gColors[TokenColors::INTERACTIVE_ACTIVE]));
    EXPECT_EQ(colors->InteractiveSelect(), Color(gColors[TokenColors::INTERACTIVE_SELECT]));
    EXPECT_EQ(colors->InteractiveClick(), Color(gColors[TokenColors::INTERACTIVE_CLICK]));
}
} //namespace OHOS::Ace::NG
