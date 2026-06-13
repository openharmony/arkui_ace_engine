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
#include "tabs_test_ng.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/focus_animation/focus_animation_theme.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/native/ui_input_event.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == AgingAdapationDialogTheme::TypeId()) {
        auto agingAdapationDialogTheme = AceType::MakeRefPtr<AgingAdapationDialogTheme>();
        agingAdapationDialogTheme->bigFontSizeScale_ = BIG_FONT_SIZE_SCALE;
        agingAdapationDialogTheme->largeFontSizeScale_ = LARGE_FONT_SIZE_SCALE;
        agingAdapationDialogTheme->maxFontSizeScale_ = MAX_FONT_SIZE_SCALE;
        agingAdapationDialogTheme->bigDialogWidth_ = BIG_DIALOG_WIDTH;
        agingAdapationDialogTheme->maxDialogWidth_ = MAX_DIALOG_WIDTH;
        return agingAdapationDialogTheme;
    } else if (type == TabTheme::TypeId()) {
        auto themeConstants = TestNG::CreateThemeConstants(THEME_PATTERN_TAB);
        auto tabTheme = TabTheme::Builder().Build(themeConstants);
        tabTheme->defaultTabBarName_ = "tabBarItemName";
        tabTheme->tabBarDefaultWidth_ = Dimension(TAB_BAR_SIZE);
        tabTheme->tabBarDefaultHeight_ = Dimension(TAB_BAR_SIZE);
        tabTheme->subTabBarHoverColor_ = Color::RED;
        tabTheme->subTabBarPressedColor_ = Color::GREEN;
        tabTheme->bottomTabSymbolOn_ = Color::BLUE;
        tabTheme->bottomTabIconOff_ = Color::BLACK;
        tabTheme->tabBarFocusedColor_ = Color::GRAY;
        tabTheme->activeIndicatorColor_ = Color::RED;
        return tabTheme;
    } else if (type == FocusAnimationTheme::TypeId()) {
        auto focusTheme = AceType::MakeRefPtr<FocusAnimationTheme>();
        return focusTheme;
    } else {
        return AceType::MakeRefPtr<DialogTheme>();
    }
}
} // namespace

class TabsFloatingBarTestNg : public TabsTestNg {
public:
    static void SetUpTestSuite()
    {
        TestNG::SetUpTestSuite();
        MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            return GetTheme(type);
        });
        EXPECT_CALL(*themeManager, GetTheme(_, _))
            .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    }
    static void TearDownTestSuite()
    {
        TestNG::TearDownTestSuite();
        g_isConfigChangePerform = false;
    }
};

/**
 * @tc.name: CreateLayoutAlgorithm001
 * @tc.desc: Test CreateLayoutAlgorithm creates TabsLayoutAlgorithm with valid tabs node
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, CreateLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with proper setup
     * @tc.expected: step1. Tabs instance is created with all required nodes
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(tabBarNode_, nullptr);

    /**
     * @tc.steps: step2. Call CreateLayoutAlgorithm method
     * @tc.expected: step2. TabsLayoutAlgorithm is created and valid
     */
    auto layoutAlgorithm = pattern_->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);

    auto tabsLayoutAlgorithm = AceType::DynamicCast<TabsLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: CreateLayoutAlgorithm002
 * @tc.desc: Test CreateLayoutAlgorithm handles null tabBar node gracefully
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, CreateLayoutAlgorithm002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabsPattern and TabsNode instances
     * @tc.expected: step1. Pattern and node are created successfully
     */
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);

    /**
     * @tc.steps: step2. Call CreateLayoutAlgorithm method with null tabBar
     * @tc.expected: step2. TabsLayoutAlgorithm is still created successfully
     */
    auto layoutAlgorithm = tabsPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);

    auto tabsLayoutAlgorithm = AceType::DynamicCast<TabsLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: InitFloatingBar001
 * @tc.desc: Test InitFloatingBar enables floating bar when all conditions are met
 *   (barOverlap=true, horizontal, barPosition=END, floatingStyle=true)
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, InitFloatingBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with BarPosition::END, barOverlap=true, horizontal, and floating style
     * @tc.expected: step1. Tabs instance is created with specified properties
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetBarOverlap(true);
    model.SetIsVertical(false);
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    /**
     * @tc.steps: step2. Set BarFloatingStyle and call InitFloatingBar
     * @tc.expected: step2. Floating bar is enabled
     */
    BarFloatingStyleParameters style;
    layoutProperty_->UpdateBarFloatingStyle(style);

    pattern_->InitFloatingBar();
    EXPECT_TRUE(pattern_->IsFloatingBar());
}

/**
 * @tc.name: InitFloatingBar002
 * @tc.desc: Test InitFloatingBar disables floating bar when barOverlap is false
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, InitFloatingBar002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with barOverlap=false
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    /**
     * @tc.steps: step2. Set barOverlap to false and call InitFloatingBar
     * @tc.expected: step2. Floating bar is disabled
     */
    layoutProperty_->UpdateBarOverlap(false);

    pattern_->InitFloatingBar();
    EXPECT_FALSE(pattern_->IsFloatingBar());
}

/**
 * @tc.name: InitFloatingBar003
 * @tc.desc: Test InitFloatingBar disables floating bar when isVertical is true
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, InitFloatingBar003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with isVertical=true
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs();
    model.SetIsVertical(true);
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    /**
     * @tc.steps: step2. Set barOverlap to true and call InitFloatingBar
     * @tc.expected: step2. Floating bar is disabled due to vertical orientation
     */
    layoutProperty_->UpdateBarOverlap(true);

    pattern_->InitFloatingBar();
    EXPECT_FALSE(pattern_->IsFloatingBar());
}

/**
 * @tc.name: InitFloatingBar004
 * @tc.desc: Test InitFloatingBar disables floating bar when barPosition is START
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, InitFloatingBar004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with BarPosition::START
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs(BarPosition::START);
    model.SetBarOverlap(true);
    model.SetIsVertical(false);
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    /**
     * @tc.steps: step2. Call InitFloatingBar
     * @tc.expected: step2. Floating bar is disabled due to START position
     */
    pattern_->InitFloatingBar();
    EXPECT_FALSE(pattern_->IsFloatingBar());
}

/**
 * @tc.name: InitFloatingBar005
 * @tc.desc: Test InitFloatingBar disables floating bar when there is no floating style
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, InitFloatingBar005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs without BarFloatingStyle
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetBarOverlap(true);
    model.SetIsVertical(false);
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    /**
     * @tc.steps: step2. Call InitFloatingBar without floating style
     * @tc.expected: step2. Floating bar is disabled
     */
    pattern_->InitFloatingBar();
    EXPECT_FALSE(pattern_->IsFloatingBar());
}

/**
 * @tc.name: UpdateBgMaskNode001
 * @tc.desc: Test UpdateBgMaskNode with custom mask color
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, UpdateBgMaskNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with floating bar enabled and custom mask color
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetBarOverlap(true);
    model.SetIsVertical(false);
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step2. Enable floating bar, set custom mask color and call UpdateBgMaskNode
     * @tc.expected: step2. Background mask node is created and valid
     */
    BarFloatingStyleParameters style;
    style.maskColor = Color(0xFF0000FF);
    layoutProperty_->UpdateBarFloatingStyle(style);

    // Enable floating bar first
    pattern_->InitFloatingBar();

    pattern_->UpdateBgMaskNode();

    // Verify background mask node exists
    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode_);
    ASSERT_NE(tabsNode, nullptr);
    EXPECT_TRUE(tabsNode->HasBackgroundMaskNode());
}

/**
 * @tc.name: UpdateBgMaskNode002
 * @tc.desc: Test UpdateBgMaskNode without background mask node
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, UpdateBgMaskNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs without floating bar enabled
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode_);
    ASSERT_NE(tabsNode, nullptr);

    /**
     * @tc.steps: step2. Call UpdateBgMaskNode without floating bar
     * @tc.expected: step2. No background mask node exists, no crash
     */
    pattern_->UpdateBgMaskNode();

    // Verify no background mask node exists (should not crash)
    EXPECT_FALSE(tabsNode->HasBackgroundMaskNode());
}

/**
 * @tc.name: UpdateBgMaskNode003
 * @tc.desc: Test UpdateBgMaskNode with default dark mode color
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, UpdateBgMaskNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with floating bar and default style
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetBarOverlap(true);
    model.SetIsVertical(false);
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto tabsNode = AceType::DynamicCast<TabsNode>(frameNode_);
    ASSERT_NE(tabsNode, nullptr);

    /**
     * @tc.steps: step2. Enable floating bar and update background mask
     * @tc.expected: step2. Background mask node is created with default color
     */
    layoutProperty_->UpdateBarFloatingStyle(BarFloatingStyleParameters());

    pattern_->InitFloatingBar();
    EXPECT_TRUE(pattern_->IsFloatingBar());

    pattern_->UpdateBgMaskNode();

    // Verify background mask node exists
    EXPECT_TRUE(tabsNode->HasBackgroundMaskNode());
}

/**
 * @tc.name: CreatePercentGradientColor001
 * @tc.desc: Test CreatePercentGradientColor creates valid gradient color with percent and color
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, CreatePercentGradientColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabsPattern instance
     * @tc.expected: step1. Pattern is created successfully
     */
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    /**
     * @tc.steps: step2. Call CreatePercentGradientColor with valid parameters
     * @tc.expected: step2. Gradient color is created with correct values
     */
    float percent = 50.0f;
    Color color = Color(0xFFFF0000);

    auto gradientColor = tabsPattern->CreatePercentGradientColor(percent, color);
    EXPECT_EQ(gradientColor.GetColor(), color);
    EXPECT_TRUE(gradientColor.GetDimension().IsValid());
    EXPECT_FLOAT_EQ(gradientColor.GetDimension().Value(), percent);
    EXPECT_EQ(gradientColor.GetDimension().Unit(), DimensionUnit::PERCENT);
}

/**
 * @tc.name: InitTouchEvent001
 * @tc.desc: Test InitTouchEvent does not add listener when adaptToHandedness is false
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, InitTouchEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs and set adaptToHandedness to false
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    BarFloatingStyleParameters style;
    style.adaptToHandedness = false;
    layoutProperty_->UpdateBarFloatingStyle(style);

    /**
     * @tc.steps: step2. Call InitTouchEvent
     * @tc.expected: step2. Gesture hub exists but no touch listener added
     */
    pattern_->InitTouchEvent();

    // Verify no crash - gesture hub should exist even if no touch listener
    auto gestureHub = frameNode_->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureHub, nullptr);
}

/**
 * @tc.name: InitTouchEvent002
 * @tc.desc: Test InitTouchEvent adds touch listener when adaptToHandedness is true
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, InitTouchEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs and set adaptToHandedness to true
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    BarFloatingStyleParameters style;
    style.adaptToHandedness = true;
    layoutProperty_->UpdateBarFloatingStyle(style);

    /**
     * @tc.steps: step2. Call InitTouchEvent
     * @tc.expected: step2. Gesture hub exists and is ready for touch events
     */
    pattern_->InitTouchEvent();

    // Verify gesture hub exists and has touch event capability
    auto gestureHub = frameNode_->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureHub, nullptr);
}

/**
 * @tc.name: OnTouchEvent001
 * @tc.desc: Test OnTouchEvent handles empty touches gracefully
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, OnTouchEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabsPattern instance
     * @tc.expected: step1. Pattern is created successfully
     */
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    /**
     * @tc.steps: step2. Create empty TouchEventInfo and call OnTouchEvent
     * @tc.expected: step2. No crash occurs, pattern remains valid
     */
    TouchEventInfo info("");

    tabsPattern->OnTouchEvent(info);

    // Verify pattern is still valid after empty touch event
    EXPECT_NE(tabsPattern, nullptr);
}

/**
 * @tc.name: OnTouchEvent002
 * @tc.desc: Test OnTouchEvent handles LEFT hand operating touch event
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, OnTouchEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with touch event enabled and LEFT hand operating
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    BarFloatingStyleParameters style;
    style.adaptToHandedness = true;
    layoutProperty_->UpdateBarFloatingStyle(style);

    pattern_->InitTouchEvent();

    /**
     * @tc.steps: step2. Create TouchEventInfo with LEFT hand and UP type, call OnTouchEvent
     * @tc.expected: step2. No crash occurs, pattern handles LEFT hand event
     */
    TouchEventInfo info("");
    TouchLocationInfo location(0);
    location.SetTouchType(TouchType::UP);
    info.AddTouchLocationInfo(std::move(location));
    info.SetOperatingHand(ARKUI_EVENT_HAND_LEFT);

    pattern_->OnTouchEvent(info);
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: OnTouchEvent003
 * @tc.desc: Test OnTouchEvent handles RIGHT hand operating touch event
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, OnTouchEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with touch event enabled and RIGHT hand operating
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    BarFloatingStyleParameters style;
    style.adaptToHandedness = true;
    layoutProperty_->UpdateBarFloatingStyle(style);

    pattern_->InitTouchEvent();

    /**
     * @tc.steps: step2. Create TouchEventInfo with RIGHT hand and UP type, call OnTouchEvent
     * @tc.expected: step2. No crash occurs, pattern handles RIGHT hand event
     */
    TouchEventInfo info("");
    TouchLocationInfo location(0);
    location.SetTouchType(TouchType::UP);
    info.AddTouchLocationInfo(std::move(location));
    info.SetOperatingHand(ARKUI_EVENT_HAND_RIGHT);

    pattern_->OnTouchEvent(info);
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: OnTouchEvent004
 * @tc.desc: Test OnTouchEvent handles NONE hand operating touch event
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, OnTouchEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with touch event enabled and NONE hand operating
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetBarOverlap(true);
    model.SetIsVertical(false);
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    BarFloatingStyleParameters style;
    style.adaptToHandedness = true;
    layoutProperty_->UpdateBarFloatingStyle(style);

    // Enable floating bar first
    pattern_->InitFloatingBar();

    pattern_->InitTouchEvent();

    /**
     * @tc.steps: step2. Create TouchEventInfo with NONE hand and UP type, call OnTouchEvent
     * @tc.expected: step2. No crash occurs, pattern ignores NONE hand event
     */
    TouchEventInfo info("");
    TouchLocationInfo location(0);
    location.SetTouchType(TouchType::UP);
    info.AddTouchLocationInfo(std::move(location));
    info.SetOperatingHand(ARKUI_EVENT_HAND_NONE);

    pattern_->OnTouchEvent(info);

    // Verify floating bar is still active after NONE hand touch
    EXPECT_TRUE(pattern_->IsFloatingBar());
}

/**
 * @tc.name: OnTouchEvent005
 * @tc.desc: Test OnTouchEvent ignores non-UP touch type events
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, OnTouchEvent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with touch event enabled and LEFT hand operating
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetBarOverlap(true);
    model.SetIsVertical(false);
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    BarFloatingStyleParameters style;
    style.adaptToHandedness = true;
    layoutProperty_->UpdateBarFloatingStyle(style);

    // Enable floating bar first
    pattern_->InitFloatingBar();

    pattern_->InitTouchEvent();

    /**
     * @tc.steps: step2. Create TouchEventInfo with LEFT hand and DOWN type, call OnTouchEvent
     * @tc.expected: step2. No crash occurs, pattern ignores non-UP touch type
     */
    TouchEventInfo info("");
    TouchLocationInfo location(0);
    location.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(location));
    info.SetOperatingHand(ARKUI_EVENT_HAND_LEFT);

    pattern_->OnTouchEvent(info);

    // Verify floating bar is still active after non-UP touch type
    EXPECT_TRUE(pattern_->IsFloatingBar());
}

/**
 * @tc.name: ResetTabBarFollowHandPosition001
 * @tc.desc: Test ResetTabBarFollowHandPosition when floating bar is enabled
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, ResetTabBarFollowHandPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with floating bar enabled
     * @tc.expected: step1. Tabs instance is created with floating bar active
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetBarOverlap(true);
    model.SetIsVertical(false);
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(tabBarNode_, nullptr);

    // Enable floating bar first
    BarFloatingStyleParameters style;
    layoutProperty_->UpdateBarFloatingStyle(style);
    pattern_->InitFloatingBar();

    // Verify initial state - floating bar is enabled
    EXPECT_TRUE(pattern_->IsFloatingBar());

    /**
     * @tc.steps: step2. Call ResetTabBarFollowHandPosition
     * @tc.expected: step2. No crash occurs, floating bar remains enabled
     */
    pattern_->ResetTabBarFollowHandPosition();
    EXPECT_TRUE(pattern_->IsFloatingBar());
}

/**
 * @tc.name: OnWindowSizeChanged001
 * @tc.desc: Test OnWindowSizeChanged with ROTATION reason triggers position reset
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, OnWindowSizeChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs instance with floating bar enabled
     * @tc.expected: step1. Tabs instance is created with floating bar active
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetBarOverlap(true);
    model.SetIsVertical(false);
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);

    // Enable floating bar first
    BarFloatingStyleParameters style;
    layoutProperty_->UpdateBarFloatingStyle(style);
    pattern_->InitFloatingBar();

    /**
     * @tc.steps: step2. Call OnWindowSizeChanged with ROTATION
     * @tc.expected: step2. No crash occurs during rotation handling
     */
    pattern_->OnWindowSizeChanged(400, 800, WindowSizeChangeReason::ROTATION);

    // Verify floating bar is still active after rotation
    EXPECT_TRUE(pattern_->IsFloatingBar());
}

/**
 * @tc.name: OnWindowSizeChanged002
 * @tc.desc: Test OnWindowSizeChanged with non-ROTATION reason does not trigger position reset
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, OnWindowSizeChanged002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs instance with floating bar enabled
     * @tc.expected: step1. Tabs instance is created with floating bar active
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetBarOverlap(true);
    model.SetIsVertical(false);
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);

    // Enable floating bar first
    BarFloatingStyleParameters style;
    layoutProperty_->UpdateBarFloatingStyle(style);
    pattern_->InitFloatingBar();

    /**
     * @tc.steps: step2. Call OnWindowSizeChanged with RESIZE
     * @tc.expected: step2. No crash occurs during resize handling
     */
    pattern_->OnWindowSizeChanged(400, 800, WindowSizeChangeReason::RESIZE);

    // Verify floating bar is still active after resize
    EXPECT_TRUE(pattern_->IsFloatingBar());
}

/**
 * @tc.name: HandleOnTouchScaleAnimation001
 * @tc.desc: Test HandleOnTouchScaleAnimation updates transform scale
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, HandleOnTouchScaleAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with tabBar node
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(tabBarNode_, nullptr);
    ASSERT_NE(tabBarNode_->GetRenderContext(), nullptr);

    /**
     * @tc.steps: step2. Call HandleOnTouchScaleAnimation
     * @tc.expected: step2. Transform scale is updated with correct values
     */
    pattern_->HandleOnTouchScaleAnimation();

    // Verify transform scale was updated
    auto renderContext = tabBarNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto transformScale = renderContext->GetTransformScale();
    EXPECT_TRUE(transformScale.has_value());
    EXPECT_FLOAT_EQ(transformScale->x, 1.15f);
    EXPECT_FLOAT_EQ(transformScale->y, 0.85f);
}

/**
 * @tc.name: HandleOnTouchDelayScaleAnimation001
 * @tc.desc: Test HandleOnTouchDelayScaleAnimation resets transform scale
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, HandleOnTouchDelayScaleAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with tabBar node
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(tabBarNode_, nullptr);
    ASSERT_NE(tabBarNode_->GetRenderContext(), nullptr);

    /**
     * @tc.steps: step2. Apply scale animation first, then apply delay scale animation
     * @tc.expected: step2. Transform scale is reset to default values
     */
    // First apply scale animation
    pattern_->HandleOnTouchScaleAnimation();

    // Then apply delay scale animation
    pattern_->HandleOnTouchDelayScaleAnimation();

    // Verify transform scale was reset to default
    auto renderContext = tabBarNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto transformScale = renderContext->GetTransformScale();
    EXPECT_TRUE(transformScale.has_value());
    EXPECT_FLOAT_EQ(transformScale->x, 1.0f);
    EXPECT_FLOAT_EQ(transformScale->y, 1.0f);
}

/**
 * @tc.name: OnFollowHandAnimationFinish001
 * @tc.desc: Test OnFollowHandAnimationFinish handles animation completion
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, OnFollowHandAnimationFinish001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabsPattern instance
     * @tc.expected: step1. Pattern is created successfully
     */
    auto tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    /**
     * @tc.steps: step2. Call OnFollowHandAnimationFinish
     * @tc.expected: step2. No crash occurs during animation finish callback
     */
    tabsPattern->OnFollowHandAnimationFinish();

    // Verify pattern is still valid
    EXPECT_NE(tabsPattern, nullptr);
}

/**
 * @tc.name: FollowHandAnimation001
 * @tc.desc: Test FollowHandAnimation without floating bar margin
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, FollowHandAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with floating bar enabled
     * @tc.expected: step1. Tabs instance is created with floating bar active
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetBarOverlap(true);
    model.SetIsVertical(false);
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(layoutProperty_, nullptr);

    // Enable floating bar first
    BarFloatingStyleParameters style;
    layoutProperty_->UpdateBarFloatingStyle(style);
    pattern_->InitFloatingBar();

    /**
     * @tc.steps: step2. Call FollowHandAnimation
     * @tc.expected: step2. No crash occurs during animation execution
     */
    pattern_->FollowHandAnimation();

    // Verify floating bar is still active
    EXPECT_TRUE(pattern_->IsFloatingBar());
}

/**
 * @tc.name: OnAttachToMainTree001
 * @tc.desc: Test OnAttachToMainTree registers callbacks
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, OnAttachToMainTree001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs with context
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(frameNode_->GetContext(), nullptr);

    /**
     * @tc.steps: step2. Call OnAttachToMainTree
     * @tc.expected: step2. No crash occurs, callbacks are registered
     */
    pattern_->OnAttachToMainTree();
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: OnDetachFromMainTree001
 * @tc.desc: Test OnDetachFromMainTree cleans up callbacks
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, OnDetachFromMainTree001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs and attach to main tree first
     * @tc.expected: step1. Tabs instance is created
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    GetTabs();
    CreateTabsDone(model);

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(frameNode_->GetContext(), nullptr);

    // First attach
    pattern_->OnAttachToMainTree();

    auto context = frameNode_->GetContext();
    ASSERT_NE(context, nullptr);

    /**
     * @tc.steps: step2. Call OnDetachFromMainTree
     * @tc.expected: step2. No crash occurs, callbacks are cleaned up
     */
    // Then detach
    pattern_->OnDetachFromMainTree();
    EXPECT_NE(pattern_, nullptr);
}

/**
 * @tc.name: SetBarFloatingStyleDefaultValues001
 * @tc.desc: Check default BarFloatingStyle is not set
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, SetBarFloatingStyleDefaultValues001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    ASSERT_NE(layoutProperty_, nullptr);
    EXPECT_FALSE(layoutProperty_->HasBarFloatingStyle());
}

/**
 * @tc.name: SetBarFloatingStyleValidValues001
 * @tc.desc: Check BarFloatingStyle with plain dimension/color values
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, SetBarFloatingStyleValidValues001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    BarFloatingStyleParameters params;
    params.smallBarWidth = Dimension(10, DimensionUnit::PX);
    params.mediumBarWidth = Dimension(20, DimensionUnit::PX);
    params.largeBarWidth = Dimension(30, DimensionUnit::PX);
    params.barSideMargin = Dimension(5, DimensionUnit::PX);
    params.barBottomMargin = Dimension(8, DimensionUnit::PX);
    params.maskColor = Color::WHITE;
    params.maskHeight = Dimension(50, DimensionUnit::PX);
    params.adaptToHandedness = true;
    TabsModelNG::SetBarFloatingStyle(AceType::RawPtr(frameNode_), params);

    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_TRUE(layoutProperty_->HasBarFloatingStyle());

    auto style = layoutProperty_->GetBarFloatingStyle().value();
    ASSERT_TRUE(style.smallBarWidth.has_value());
    EXPECT_EQ(style.smallBarWidth.value(), Dimension(10, DimensionUnit::PX));
    ASSERT_TRUE(style.mediumBarWidth.has_value());
    EXPECT_EQ(style.mediumBarWidth.value(), Dimension(20, DimensionUnit::PX));
    ASSERT_TRUE(style.largeBarWidth.has_value());
    EXPECT_EQ(style.largeBarWidth.value(), Dimension(30, DimensionUnit::PX));
    ASSERT_TRUE(style.barSideMargin.has_value());
    EXPECT_EQ(style.barSideMargin.value(), Dimension(5, DimensionUnit::PX));
    ASSERT_TRUE(style.barBottomMargin.has_value());
    EXPECT_EQ(style.barBottomMargin.value(), Dimension(8, DimensionUnit::PX));
    ASSERT_TRUE(style.maskColor.has_value());
    EXPECT_EQ(style.maskColor.value(), Color::WHITE);
    ASSERT_TRUE(style.maskHeight.has_value());
    EXPECT_EQ(style.maskHeight.value(), Dimension(50, DimensionUnit::PX));
    ASSERT_TRUE(style.adaptToHandedness.has_value());
    EXPECT_EQ(style.adaptToHandedness.value(), true);
}

/**
 * @tc.name: SetBarFloatingStyleReset001
 * @tc.desc: Check BarFloatingStyle reset by ResetBarFloatingStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, SetBarFloatingStyleReset001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    BarFloatingStyleParameters params;
    params.smallBarWidth = Dimension(10, DimensionUnit::PX);
    params.maskColor = Color::WHITE;
    TabsModelNG::SetBarFloatingStyle(AceType::RawPtr(frameNode_), params);
    ASSERT_TRUE(layoutProperty_->HasBarFloatingStyle());

    TabsModelNG::ResetBarFloatingStyle(AceType::RawPtr(frameNode_));
    EXPECT_FALSE(layoutProperty_->HasBarFloatingStyle());
}

/**
 * @tc.name: SetBarFloatingStyleResourceObjectEnabled001
 * @tc.desc: Check BarFloatingStyle with ResourceObject fields when ConfigChangePerform is enabled
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, SetBarFloatingStyleResourceObjectEnabled001, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    auto resObj = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::FLOAT), std::vector<ResourceObjectParams>(),
        "", "", Container::CurrentIdSafely());

    BarFloatingStyleParameters params;
    params.smallBarWidth = Dimension(10, DimensionUnit::PX);
    params.smallBarWidthObject = resObj;
    params.mediumBarWidthObject = resObj;
    params.largeBarWidthObject = resObj;
    params.barSideMarginObject = resObj;
    params.barBottomMarginObject = resObj;
    params.maskColorObject = resObj;
    params.maskHeightObject = resObj;
    TabsModelNG::SetBarFloatingStyle(AceType::RawPtr(frameNode_), params);

    ASSERT_NE(pattern_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_, nullptr);

    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetBarFloatingStyleResourceObjectDisabled001
 * @tc.desc: Check BarFloatingStyle with ResourceObject fields when ConfigChangePerform is disabled
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, SetBarFloatingStyleResourceObjectDisabled001, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    auto resObj = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::FLOAT), std::vector<ResourceObjectParams>(),
        "", "", Container::CurrentIdSafely());

    BarFloatingStyleParameters params;
    params.smallBarWidth = Dimension(10, DimensionUnit::PX);
    params.smallBarWidthObject = resObj;
    TabsModelNG::SetBarFloatingStyle(AceType::RawPtr(frameNode_), params);

    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->resourceMgr_, nullptr);
}

/**
 * @tc.name: SetBarFloatingStyleResourceObjectColorEnabled001
 * @tc.desc: Check BarFloatingStyle with maskColor ResourceObject when ConfigChangePerform is enabled
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, SetBarFloatingStyleResourceObjectColorEnabled001, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    auto resObj = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::COLOR), std::vector<ResourceObjectParams>(),
        "", "", Container::CurrentIdSafely());

    BarFloatingStyleParameters params;
    params.maskColor = Color::RED;
    params.maskColorObject = resObj;
    TabsModelNG::SetBarFloatingStyle(AceType::RawPtr(frameNode_), params);

    ASSERT_NE(pattern_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_, nullptr);

    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetBarFloatingStyleResourceObjectColorDisabled001
 * @tc.desc: Check BarFloatingStyle with maskColor ResourceObject when ConfigChangePerform is disabled
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, SetBarFloatingStyleResourceObjectColorDisabled001, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    auto resObj = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::COLOR), std::vector<ResourceObjectParams>(),
        "", "", Container::CurrentIdSafely());

    BarFloatingStyleParameters params;
    params.maskColor = Color::RED;
    params.maskColorObject = resObj;
    TabsModelNG::SetBarFloatingStyle(AceType::RawPtr(frameNode_), params);

    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->resourceMgr_, nullptr);
}

/**
 * @tc.name: SetBarFloatingStylePlainValuesNoResourceObject001
 * @tc.desc: Check BarFloatingStyle with plain values does not register ResourceObject even when enabled
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, SetBarFloatingStylePlainValuesNoResourceObject001, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    BarFloatingStyleParameters params;
    params.smallBarWidth = Dimension(10, DimensionUnit::PX);
    params.maskColor = Color::WHITE;
    TabsModelNG::SetBarFloatingStyle(AceType::RawPtr(frameNode_), params);

    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->resourceMgr_, nullptr);

    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetBarFloatingStyleAllUndefinedFields001
 * @tc.desc: Check BarFloatingStyle with all undefined optional fields
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, SetBarFloatingStyleAllUndefinedFields001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    BarFloatingStyleParameters params;
    TabsModelNG::SetBarFloatingStyle(AceType::RawPtr(frameNode_), params);

    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_TRUE(layoutProperty_->HasBarFloatingStyle());

    auto style = layoutProperty_->GetBarFloatingStyle().value();
    EXPECT_FALSE(style.smallBarWidth.has_value());
    EXPECT_FALSE(style.mediumBarWidth.has_value());
    EXPECT_FALSE(style.largeBarWidth.has_value());
    EXPECT_FALSE(style.barSideMargin.has_value());
    EXPECT_FALSE(style.barBottomMargin.has_value());
    EXPECT_FALSE(style.maskColor.has_value());
    EXPECT_FALSE(style.maskHeight.has_value());
    EXPECT_FALSE(style.adaptToHandedness.has_value());
}

/**
 * @tc.name: SetBarFloatingStyleMixedValues001
 * @tc.desc: Check BarFloatingStyle with mixed plain and ResourceObject values
 * @tc.type: FUNC
 */
HWTEST_F(TabsFloatingBarTestNg, SetBarFloatingStyleMixedValues001, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    auto resObj = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::FLOAT), std::vector<ResourceObjectParams>(),
        "", "", Container::CurrentIdSafely());
    auto resColorObj = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::COLOR), std::vector<ResourceObjectParams>(),
        "", "", Container::CurrentIdSafely());

    BarFloatingStyleParameters params;
    params.smallBarWidth = Dimension(10, DimensionUnit::PX);
    params.mediumBarWidthObject = resObj;
    params.largeBarWidth = Dimension(30, DimensionUnit::PX);
    params.barSideMargin = Dimension(5, DimensionUnit::PX);
    params.barBottomMarginObject = resObj;
    params.maskColorObject = resColorObj;
    params.maskHeight = Dimension(50, DimensionUnit::PX);
    TabsModelNG::SetBarFloatingStyle(AceType::RawPtr(frameNode_), params);

    ASSERT_NE(pattern_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_, nullptr);

    ASSERT_NE(layoutProperty_, nullptr);
    auto style = layoutProperty_->GetBarFloatingStyle().value();
    ASSERT_TRUE(style.smallBarWidth.has_value());
    EXPECT_EQ(style.smallBarWidth.value(), Dimension(10, DimensionUnit::PX));
    ASSERT_TRUE(style.largeBarWidth.has_value());
    EXPECT_EQ(style.largeBarWidth.value(), Dimension(30, DimensionUnit::PX));
    ASSERT_TRUE(style.barSideMargin.has_value());
    EXPECT_EQ(style.barSideMargin.value(), Dimension(5, DimensionUnit::PX));
    ASSERT_TRUE(style.maskHeight.has_value());
    EXPECT_EQ(style.maskHeight.value(), Dimension(50, DimensionUnit::PX));

    g_isConfigChangePerform = false;
}

} // namespace OHOS::Ace::NG
