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
#include <unistd.h>
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
#include "core/common/ace_engine.h"
#include "core/common/app_bar_helper.h"
#include "core/common/container.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
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

    void SetUp() override
    {
        ViewStackProcessor::GetInstance()->SetCustomAppBarNode(nullptr);
    }
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

/**
 * @tc.name: TestUpdateIconLayout017
 * @tc.desc: Test UpdateOverlayLayout
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateIconLayout017, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);
    auto menuBar = appBar->BuildMenuBar();
    auto button = appBar->BuildButton(true);
    auto driver = appBar->BuildDivider();
    atom->AddChild(menuBar);
    atom->AddChild(button);
    atom->AddChild(driver);

    auto pattern = atom->GetPattern<AtomicServicePattern>();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = pipeline->GetTheme<AppBarTheme>();
    pattern->UpdateOverlayLayout();
    pattern->UpdateColor(std::nullopt);
    theme->clickEffectColorLight_ = Color::RED;
    theme->focusedOutlineColorLight_ = Color::RED;
    pattern->UpdateButtonColor(theme, button, true);
    pattern->UpdateDividerColor(theme, driver, true);
    auto buttonPattern1 = button->GetPattern<ButtonPattern>();
    EXPECT_EQ(buttonPattern1->clickedColor_, Color::RED);
    EXPECT_EQ(buttonPattern1->focusBorderColor_, Color::RED);

    theme->clickEffectColorDark_ = Color::BLUE;
    theme->focusedOutlineColorDark_ = Color::BLUE;
    pattern->UpdateButtonColor(theme, button, false);
    pattern->UpdateDividerColor(theme, driver, false);
    auto buttonPattern2 = button->GetPattern<ButtonPattern>();
    EXPECT_EQ(buttonPattern2->clickedColor_, Color::BLUE);
    EXPECT_EQ(buttonPattern2->focusBorderColor_, Color::BLUE);
}

/**
 * @tc.name: TestUpdateIconLayout018
 * @tc.desc: Test BeforeCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateIconLayout018, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto atom = appBar->Create(stage);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    pattern->BeforeCreateLayoutWrapper();

    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetSafeAreaManager();
    manager->keyboardSafeAreaEnabled_ = true;
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(appBar->sessionId_, 0);
}

/**
 * @tc.name: TestOnMenuClick019
 * @tc.desc: Test OnMenuClick
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestOnMenuClick019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage , appBar , atom ,pattern , pipeline and theme.
     * @tc.expected: stage , appBar , atom ,pattern , pipeline and theme are not null.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    EXPECT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<AppBarTheme>();
    EXPECT_NE(theme, nullptr);
    appBar->OnMenuClick();
    EXPECT_NE(appBar, nullptr);
}

/**
 * @tc.name: TestOnCloseClick020
 * @tc.desc: Test OnCloseClick
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestOnCloseClick020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage , appBar , atom ,pattern , pipeline and theme.
     * @tc.expected: stage , appBar , atom ,pattern , pipeline and theme are not null.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    EXPECT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<AppBarTheme>();
    EXPECT_NE(theme, nullptr);
    int32_t containerId = 100;
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    appBar->OnCloseClick();
    EXPECT_NE(appBar, nullptr);
}

/**
 * @tc.name: TestSetStatusBarItemColor021
 * @tc.desc: Test SetStatusBarItemColor
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestSetStatusBarItemColor021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage , appBar , atom ,pattern , pipeline.
     * @tc.expected: stage , appBar , atom ,pattern , pipeline are not null.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    EXPECT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    /**
     * @tc.steps: step2. Expect settedColorMode is true after using SetStatusBarItemColor.
     */
    appBar->SetStatusBarItemColor(true);
    EXPECT_EQ(pattern->settedColorMode, true);
}

/**
 * @tc.name: TestUpdateColor022
 * @tc.desc: Test UpdateColor
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateColor022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage , appBar , atom ,pattern , pipeline.
     * @tc.expected: stage , appBar , atom ,pattern , pipeline are not null.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    EXPECT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    /**
      * @tc.steps: step2. Create theme, icon, renderContext, button, layoutProperty.
      * @tc.expected: theme, icon, renderContext, button, layoutProperty are not null.
      */
    auto theme = pipeline->GetTheme<AppBarTheme>();
    EXPECT_NE(theme, nullptr);
    auto icon = appBar->BuildIcon(true);
    EXPECT_NE(icon, nullptr);
    auto renderContext = icon->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    auto button = appBar->BuildButton(true);
    EXPECT_NE(button, nullptr);
    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    pipeline->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    pattern->settedColorMode = true;

    /**
      * @tc.steps: step3. Expect appBar->sessionId_ is 0 after using UpdateColor.
      */
    pattern->OnColorConfigurationUpdate();
    pattern->UpdateColor(false);
    EXPECT_EQ(appBar->sessionId_, 0);
}

/**
 * @tc.name: TestUpdateMenuBarColor023
 * @tc.desc: Test UpdateMenuBarColor1
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateMenuBarColor023, TestSize.Level1)
{
    /**
      * @tc.steps: step1. Create stage, appBar, atom, pattern, pipeline.
      * @tc.expected: stage, appBar, atom, pattern, pipeline are not null.
      */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);
    auto menuBar = appBar->BuildMenuBar();
    atom->AddChild(menuBar);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    EXPECT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    /**
      * @tc.steps: step2. Create theme, icon, renderContext, button, layoutProperty.
      * @tc.expected: theme, icon, renderContext, button, layoutProperty are not null.
      */
    auto theme = pipeline->GetTheme<AppBarTheme>();
    EXPECT_NE(theme, nullptr);
    auto icon = appBar->BuildIcon(true);
    EXPECT_NE(icon, nullptr);
    auto renderContext = icon->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    auto button = appBar->BuildButton(true);
    EXPECT_NE(button, nullptr);
    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    /**
      * @tc.steps: step3. Expect appBar->sessionId_ is 0 after using UpdateMenuBarColor.
      */
    pattern->UpdateOverlayLayout();
    pattern->UpdateMenuBarColor(theme, menuBar, true);
    EXPECT_EQ(appBar->sessionId_, 0);
}

/**
 * @tc.name: TestUpdateMenuBarColor024
 * @tc.desc: Test UpdateMenuBarColor2
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateMenuBarColor024, TestSize.Level1)
{
    /**
      * @tc.steps: step1. Create stage, appBar, atom, pattern, pipeline.
      * @tc.expected: stage, appBar, atom, pattern, pipeline are not null.
      */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);
    auto menuBar = appBar->BuildMenuBar();
    atom->AddChild(menuBar);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    EXPECT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    /**
      * @tc.steps: step2. Create theme, icon, renderContext, button, layoutProperty.
      * @tc.expected: theme, icon, renderContext, button, layoutProperty are not null.
      */
    auto theme = pipeline->GetTheme<AppBarTheme>();
    EXPECT_NE(theme, nullptr);
    auto icon = appBar->BuildIcon(true);
    EXPECT_NE(icon, nullptr);
    auto renderContext = icon->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    auto button = appBar->BuildButton(true);
    EXPECT_NE(button, nullptr);
    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    /**
      * @tc.steps: step3. Expect appBar->sessionId_ is 0 after using UpdateMenuBarColor.
      */
    pattern->UpdateOverlayLayout();
    pattern->UpdateMenuBarColor(theme, menuBar, false);
    EXPECT_EQ(appBar->sessionId_, 0);
}

/**
 * @tc.name: TestUpdateButtonColor025
 * @tc.desc: Test UpdateButtonColor1
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateButtonColor025, TestSize.Level1)
{
    /**
      * @tc.steps: step1. Create stage, appBar, atom, pattern, pipeline.
      * @tc.expected: stage, appBar, atom, pattern, pipeline are not null.
      */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);
    auto menuBar = appBar->BuildMenuBar();
    atom->AddChild(menuBar);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    EXPECT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    /**
      * @tc.steps: step2. Create theme, icon, renderContext, button, layoutProperty, driver.
      * @tc.expected: theme, icon, renderContext, button, layoutProperty, driver are not null.
      */
    auto theme = pipeline->GetTheme<AppBarTheme>();
    EXPECT_NE(theme, nullptr);
    auto icon = appBar->BuildIcon(true);
    EXPECT_NE(icon, nullptr);
    auto renderContext = icon->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    auto button = appBar->BuildButton(true);
    EXPECT_NE(button, nullptr);
    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto driver = appBar->BuildDivider();
    EXPECT_NE(driver, nullptr);
    atom->AddChild(menuBar);
    atom->AddChild(button);
    atom->AddChild(driver);

    /**
      * @tc.steps: step3. Set clickEffectColorLight_ is red.
      * @tc.expected: clickedColor_ is red after using UpdateButtonColor.
      */
    theme->clickEffectColorLight_ = Color::RED;
    pattern->UpdateButtonColor(theme, button, true);
    auto buttonPattern1 = button->GetPattern<ButtonPattern>();
    EXPECT_EQ(buttonPattern1->clickedColor_, Color::RED);
}

/**
 * @tc.name: TestUpdateButtonColor026
 * @tc.desc: Test UpdateButtonColor2
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestUpdateButtonColor026, TestSize.Level1)
{
    /**
      * @tc.steps: step1. Create stage, appBar, atom, pattern, pipeline.
      * @tc.expected: stage, appBar, atom, pattern, pipeline are not null.
      */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);
    auto menuBar = appBar->BuildMenuBar();
    atom->AddChild(menuBar);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    EXPECT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);

    /**
      * @tc.steps: step2. Create theme, icon, renderContext, button, layoutProperty, driver.
      * @tc.expected: theme, icon, renderContext, button, layoutProperty, driver are not null.
      */
    auto theme = pipeline->GetTheme<AppBarTheme>();
    EXPECT_NE(theme, nullptr);
    auto icon = appBar->BuildIcon(true);
    EXPECT_NE(icon, nullptr);
    auto renderContext = icon->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    auto button = appBar->BuildButton(true);
    EXPECT_NE(button, nullptr);
    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto driver = appBar->BuildDivider();
    EXPECT_NE(driver, nullptr);
    atom->AddChild(menuBar);
    atom->AddChild(button);
    atom->AddChild(driver);

    /**
      * @tc.steps: step3. Set clickEffectColorLight_ is blue.
      * @tc.expected: clickedColor_ is blue after using UpdateButtonColor.
      */
    theme->clickEffectColorDark_ = Color::BLUE;
    pattern->UpdateButtonColor(theme, button, false);
    auto buttonPattern = button->GetPattern<ButtonPattern>();
    EXPECT_EQ(buttonPattern->clickedColor_, Color::BLUE);
}

/**
 * @tc.name: TestColorConfigurationCallBack027
 * @tc.desc: Test ColorConfigurationCallBack
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestColorConfigurationCallBack027, TestSize.Level1)
{
    /**
      * @tc.steps: step1. Create stage, appBar, atom, pattern.
      * @tc.expected: stage, appBar, atom, pattern are not null.
      */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);
    auto menuBar = appBar->BuildMenuBar();
    atom->AddChild(menuBar);
    auto pattern = atom->GetPattern<AtomicServicePattern>();

    /**
     * @tc.steps: step2. Create CustomAppBarNode.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);

    /**
     * @tc.steps: step3. Set callback.
     */
    bool isExecute = false;
    std::string name1 = "qw";
    auto callback = [&isExecute, &name1](const std::string& name, const std::string& value) mutable {
        name1 = name;
        isExecute = true;
    };

    /**
     * @tc.steps: step4. Add the callback in customAppBarNode.
     */
    custom->SetCustomCallback(std::move(callback));
    auto customAppBar = pattern->GetJSAppBarContainer();
    EXPECT_NE(customAppBar, nullptr);
    auto context = pattern->GetContext();
    EXPECT_NE(context, nullptr);

    /**
     * @tc.steps: step5. Expect the callback is used.
     */
    pattern->ColorConfigurationCallBack();
    EXPECT_EQ(name1, "arkui_app_bar_color_configuration");
    EXPECT_EQ(isExecute, true);
}

/**
 * @tc.name: TestAppInfoCallBack028
 * @tc.desc: Test AppInfoCallBack
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestAppInfoCallBack028, TestSize.Level1)
{
    /**
      * @tc.steps: step1. Create stage, appBar, atom, pattern, atomTwo, pipeline, themeManager, themeConstants,
      * windowManager.
      * @tc.expected: stage, appBar, atom, themeManager, themeConstants, windowManagerare not null.
      */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);
    auto menuBar = appBar->BuildMenuBar();
    atom->AddChild(menuBar);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    auto atomTwo = pattern->GetHost();
    EXPECT_NE(atomTwo, nullptr);
    auto pipeline = atomTwo->GetContextRefPtr();
    EXPECT_NE(pipeline, nullptr);
    auto themeManager = pipeline->GetThemeManager();
    EXPECT_NE(themeManager, nullptr);
    auto themeConstants = themeManager->GetThemeConstants();
    EXPECT_NE(themeConstants, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    EXPECT_NE(windowManager, nullptr);

    /**
     * @tc.steps: step2. Create CustomAppBarNode.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);

    /**
     * @tc.steps: step3. Set callback.
     */
    bool isExecute = false;
    std::string name1 = "qw";
    auto callback = [&isExecute, &name1](const std::string& name, const std::string& value) mutable {
        name1 = name;
        isExecute = true;
    };

    /**
     * @tc.steps: step4. Add the callback in customAppBarNode.
     */
    custom->SetCustomCallback(std::move(callback));
    auto customAppBar = pattern->GetJSAppBarContainer();
    EXPECT_NE(customAppBar, nullptr);

    /**
     * @tc.steps: step5. Expect the callback is used.
     */
    pattern->AppInfoCallBack();
    EXPECT_EQ(name1, "arkui_app_bar_info");
    EXPECT_EQ(isExecute, true);
}

/**
 * @tc.name: TestAppBgColorCallBack029
 * @tc.desc: Test AppBgColorCallBack
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestAppBgColorCallBack029, TestSize.Level1)
{
    /**
      * @tc.steps: step1. Create stage, appBar, atom, pattern.
      * @tc.expected: stage, appBar, atom, pattern are not null.
      */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);
    auto menuBar = appBar->BuildMenuBar();
    atom->AddChild(menuBar);
    auto pattern = atom->GetPattern<AtomicServicePattern>();

    /**
     * @tc.steps: step2. Create CustomAppBarNode.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);

    /**
     * @tc.steps: step3. Set callback.
     */
    bool isExecute = false;
    std::string name1 = "qw";
    auto callback = [&isExecute, &name1](const std::string& name, const std::string& value) mutable {
        name1 = name;
        isExecute = true;
    };

    /**
     * @tc.steps: step4. Add the callback in customAppBarNode.
     */
    custom->SetCustomCallback(std::move(callback));
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto pipeline = host->GetContextRefPtr();
    EXPECT_NE(pipeline, nullptr);
    auto customAppBar = pattern->GetJSAppBarContainer();
    EXPECT_NE(customAppBar, nullptr);

    /**
     * @tc.steps: step5. Expect the callback is used.
     */
    pattern->AppBgColorCallBack();
    EXPECT_EQ(isExecute, true);
    EXPECT_EQ(name1, "arkui_app_bg_color");
}

/**
 * @tc.name: TestAppScreenCallBack030
 * @tc.desc: Test AppScreenCallBack
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestAppScreenCallBack030, TestSize.Level1)
{
    /**
      * @tc.steps: step1. Create stage, atomicServicePattern, customAppBar.
      * @tc.expected: stage, atomicServicePattern, customAppBar are not null.
      */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    RefPtr<AtomicServicePattern> atomicServicePattern = AceType::MakeRefPtr<AtomicServicePattern>();
    ASSERT_NE(atomicServicePattern, nullptr);
    NG::ViewStackProcessor::GetInstance()->SetCustomAppBarNode(stage);
    auto customAppBar = atomicServicePattern->GetJSAppBarContainer();
    CHECK_NULL_VOID(customAppBar);

    /**
     * @tc.steps: step2. Expect the callback is used.
     */
    std::string name1 = "qw";
    customAppBar->customCallback_ = [&name1](const std::string& name, const std::string& value) { name1 = "test"; };
    atomicServicePattern->AppScreenCallBack();
    EXPECT_EQ(name1, "test");
}

/**
 * @tc.name: TestAppScreenCallBack031
 * @tc.desc: Test AppScreenCallBack
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestAppScreenCallBack031, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);;

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    AppBarView::BuildAppbar(pipeline);
    EXPECT_EQ(atom, appBar->atomicService_.Upgrade());
}

/**
 * @tc.name: TestOnBackPressedCallback032
 * @tc.desc: Test OnBackPressedCallback function
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, TestOnBackPressedCallback032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage, appBar, atom, pattern.
     * @tc.expected: stage, appBar, atom, pattern are not null.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create CustomAppBarNode and set callback.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);

    bool callbackCalled = false;
    std::string callbackName;
    std::string callbackValue;
    
    auto callback =
        [&callbackCalled, &callbackName, &callbackValue](const std::string& name, const std::string& value) mutable {
        callbackCalled = true;
        callbackName = name;
        callbackValue = value;
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto appBar = container->GetAppBar();
        CHECK_NULL_VOID(appBar);
        appBar->SetOnBackPressedConsumed();
    };

    custom->SetCustomCallback(std::move(callback));
    auto customAppBar = pattern->GetJSAppBarContainer();
    ASSERT_NE(customAppBar, nullptr);

    /**
     * @tc.steps: step3. Call OnBackPressedCallback and verify the callback is triggered.
     * @tc.expected: The callback should be called with ARKUI_APP_BAR_ON_BACK_PRESSED and value "true".
     */
    pattern->OnBackPressedCallback();
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(callbackName, ARKUI_APP_BAR_ON_BACK_PRESSED);
    EXPECT_EQ(callbackValue, "true");

    /**
     * @tc.steps: step4. Verify onBackPressedConsumed_ flag is reset correctly.
     * @tc.expected: The flag should be reset (no value) after the callback is executed.
     */
    EXPECT_FALSE(pattern->onBackPressedConsumed_.has_value());
}

/**
 * @tc.name: TestCreateServicePanel033
 * @tc.desc: Test CreateServicePanel with bundleName
 * @tc.type: FUNC
 */
 HWTEST_F(AppBarTestNg, TestCreateServicePanel033, TestSize.Level1)
{
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    std::string bundleName = "com.hmos.asde";
    std::string abilityName = "PanelAbility";
    std::map<std::string, std::string> params = {
        {"bundleName", "com.hmos.asde"},
        {"abilityName", "MainAbility"},
        {"module", "entry"},
        {"pageName", "DETAIL"},
        {"ability.want.params.uiExtensionType", "sysDialog/atomicServicePanel"},
        {"TopNavPathInfo", ""},
    };
    appBar->CreateServicePanel(bundleName, abilityName, params);
    EXPECT_EQ(appBar->sessionId_, 0);
}

/**
 * @tc.name: BuildAppbar001
 * @tc.desc: Test BuildAppbar
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, BuildAppbar001, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    EXPECT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    EXPECT_NE(atom, nullptr);;

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    AppBarView::BuildAppbar(pipeline);
    EXPECT_EQ(atom, appBar->atomicService_.Upgrade());
}
} // namespace OHOS::Ace::NG
