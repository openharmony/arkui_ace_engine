/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/app_bar_helper.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class AppBarTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void AppBarTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppBarTheme>()));
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));
}

void AppBarTestNg::TearDownTestSuite()
{
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: TestChildSize001
 * @tc.desc: Check AppBar Child size
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestChildSize001, TestSize.Level1)
{
    /**
     * The structure of container_modal is designed as follows :
     * |--AtomicService(Column)
     *   |--Stage
     *   |--MenuBarRow
     *     |--MenuBar
     *       |--menuButton
     *       |--divider
     *       |--closeButton
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);

    EXPECT_EQ(atom->GetChildren().size(), 1);
}

/**
 * @tc.name: TestGetAppBarRect002
 * @tc.desc: Test GetAppBarRect
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestGetAppBarRect002, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);

    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    pipeline->SetInstallationFree(0);
    auto rect = appBar->GetAppBarRect();
    EXPECT_EQ(rect, std::nullopt);

    pipeline->SetInstallationFree(1);
    rect = appBar->GetAppBarRect();
    EXPECT_EQ(rect, std::nullopt);
}

/**
 * @tc.name: TestBuildMenuBarRow003
 * @tc.desc: Test BuildMenuBarRow
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestBuildMenuBarRow003, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto menuBarRow = appBar->BuildMenuBarRow();
    auto layoutProperty = menuBarRow->GetLayoutProperty<LinearLayoutProperty>();
    auto renderContext = menuBarRow->GetRenderContext();

    EXPECT_EQ(layoutProperty->GetMainAxisAlign(), FlexAlign::FLEX_END);
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::TRANSPARENT);
    EXPECT_EQ(menuBarRow->GetHitTestMode(), HitTestMode::HTMTRANSPARENT_SELF);
}

/**
 * @tc.name: TestBuildMenuBar004
 * @tc.desc: Test BuildMenuBar
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestBuildMenuBar004, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto menuBar = appBar->BuildMenuBar();
    auto layoutProperty = menuBar->GetLayoutProperty<LinearLayoutProperty>();

    EXPECT_EQ(layoutProperty->GetMainAxisAlign(), FlexAlign::FLEX_START);
}

/**
 * @tc.name: TestBuildButton005
 * @tc.desc: Test BuildButton
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestBuildButton005, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto button = appBar->BuildButton(true);
    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    auto renderContext = button->GetRenderContext();
    auto focusHub = button->GetFocusHub();

    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::TRANSPARENT);
    EXPECT_EQ(layoutProperty->GetType().value_or(ButtonType::CAPSULE), ButtonType::NORMAL);
    EXPECT_EQ(focusHub->focusStyleType_, FocusStyleType::INNER_BORDER);
}

/**
 * @tc.name: TestBuildIcon006
 * @tc.desc: Test BuildIcon
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestBuildIcon006, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();

    auto menuIcon = appBar->BuildIcon(true);
    auto menuProp = menuIcon->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_TRUE(menuProp->HasImageSourceInfo());
    EXPECT_EQ(menuProp->GetImageSourceInfo()->GetResourceId(), InternalResource::ResourceId::APP_BAR_MENU_SVG);

    auto closeIcon = appBar->BuildIcon(false);
    auto closeProp = closeIcon->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_TRUE(closeProp->HasImageSourceInfo());
    EXPECT_EQ(closeProp->GetImageSourceInfo()->GetResourceId(), InternalResource::ResourceId::APP_BAR_CLOSE_SVG);
}

/**
 * @tc.name: TestGetChild007
 * @tc.desc: Test GetChild
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestGetChild007, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);
    auto pattern = atom->GetPattern<AtomicServicePattern>();

    EXPECT_EQ(atom, appBar->atomicService_.Upgrade());
}

/**
 * @tc.name: TestUpdateIconColor008
 * @tc.desc: Test UpdateIconColor
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateIconColor008, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = pipeline->GetTheme<AppBarTheme>();
    auto icon = appBar->BuildIcon(true);
    auto renderContext = icon->GetRenderContext();

    pattern->UpdateIconColor(theme, icon, true);
    EXPECT_EQ(renderContext->GetForegroundColorValue(Color::RED), theme->GetIconColorLight());
}

/**
 * @tc.name: TestUpdateMenuBarLayout009
 * @tc.desc: Test UpdateMenuBarLayout
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateMenuBarLayout009, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = pipeline->GetTheme<AppBarTheme>();
    auto menuBar = appBar->BuildMenuBar();
    auto layoutProperty = menuBar->GetLayoutProperty<LinearLayoutProperty>();

    pattern->UpdateMenuBarLayout(theme, menuBar, false);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(theme->GetMenuBarLeftMargin()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(theme->GetMenuBarRightMargin()));

    pattern->UpdateMenuBarLayout(theme, menuBar, true);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(theme->GetMenuBarRightMargin()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(theme->GetMenuBarLeftMargin()));
}

/**
 * @tc.name: TestUpdateButtonLayout010
 * @tc.desc: Test UpdateButtonLayout
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateButtonLayout010, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = pipeline->GetTheme<AppBarTheme>();
    auto button = appBar->BuildButton(true);
    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    auto bent = theme->GetBentRadius();
    auto rightAngle = theme->GetRightAngle();

    pattern->UpdateButtonLayout(theme, button, true);
    EXPECT_EQ(layoutProperty->GetBorderRadius()->radiusTopLeft.value(), bent);
    EXPECT_EQ(layoutProperty->GetBorderRadius()->radiusTopRight.value(), rightAngle);
    EXPECT_EQ(layoutProperty->GetBorderRadius()->radiusBottomRight.value(), rightAngle);
    EXPECT_EQ(layoutProperty->GetBorderRadius()->radiusBottomLeft.value(), bent);

    pattern->UpdateButtonLayout(theme, button, false);
    EXPECT_EQ(layoutProperty->GetBorderRadius()->radiusTopLeft.value(), rightAngle);
    EXPECT_EQ(layoutProperty->GetBorderRadius()->radiusTopRight.value(), bent);
    EXPECT_EQ(layoutProperty->GetBorderRadius()->radiusBottomRight.value(), bent);
    EXPECT_EQ(layoutProperty->GetBorderRadius()->radiusBottomLeft.value(), rightAngle);
}

/**
 * @tc.name: TestUpdateIconLayout011
 * @tc.desc: Test UpdateIconLayout
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateIconLayout011, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = pipeline->GetTheme<AppBarTheme>();
    auto icon = appBar->BuildIcon(true);
    auto layoutProperty = icon->GetLayoutProperty<ImageLayoutProperty>();

    pattern->UpdateIconLayout(theme, icon, true);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(theme->GetIconOutsideMargin()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(theme->GetIconInsideMargin()));

    pattern->UpdateIconLayout(theme, icon, false);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(theme->GetIconInsideMargin()));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(theme->GetIconOutsideMargin()));
}

/**
 * @tc.name: TestUpdateIconLayout012
 * @tc.desc: Test CreateServicePanel
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateIconLayout012, TestSize.Level1)
{
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    appBar->CreateServicePanel(true);
    EXPECT_EQ(appBar->sessionId_, 0);
}

/**
 * @tc.name: TestUpdateIconLayout013
 * @tc.desc: Test UpdateOverlayLayout
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateIconLayout013, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);
    auto menuBar = appBar->BuildMenuBar();
    atom->AddChild(menuBar);

    auto pattern = atom->GetPattern<AtomicServicePattern>();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = pipeline->GetTheme<AppBarTheme>();
    pattern->UpdateOverlayLayout();
    pattern->UpdateMenuBarColor(theme, menuBar, true);
    pattern->UpdateMenuBarColor(theme, menuBar, false);
    EXPECT_EQ(appBar->sessionId_, 0);
}

/**
 * @tc.name: TestUpdateIconLayout014
 * @tc.desc: Test UpdateOverlayLayout
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateIconLayout014, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = pipeline->GetTheme<AppBarTheme>();
    pipeline->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    pattern->UpdateOverlayLayout();
    EXPECT_EQ(appBar->sessionId_, 0);
}

/**
 * @tc.name: TestUpdateIconLayout015
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateIconLayout015, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = pipeline->GetTheme<AppBarTheme>();
    auto icon = appBar->BuildIcon(true);
    auto renderContext = icon->GetRenderContext();
    auto button = appBar->BuildButton(true);
    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    pipeline->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    pattern->OnColorConfigurationUpdate();
    EXPECT_EQ(appBar->sessionId_, 0);
}

/**
 * @tc.name: TestUpdateIconLayout016
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateIconLayout016, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = pipeline->GetTheme<AppBarTheme>();
    auto icon = appBar->BuildIcon(true);
    auto renderContext = icon->GetRenderContext();
    auto button = appBar->BuildButton(true);
    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    pipeline->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    pattern->settedColorMode = true;
    pattern->OnColorConfigurationUpdate();
    pattern->UpdateColor(false);
    EXPECT_EQ(appBar->sessionId_, 0);
}
} // namespace OHOS::Ace::NG
