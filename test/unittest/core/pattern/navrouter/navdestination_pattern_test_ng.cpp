/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#define protected public
#define private public
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/base/mock_system_bar_style.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/navigation/mock_navigation_stack.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class NavDestinationPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static RefPtr<FrameNode> CreateDialogNode();
};

void NavDestinationPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void NavDestinationPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> NavDestinationPatternTestNg::CreateDialogNode()
{
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    DialogProperties dialogProperties {
        .title = "Title",
        .content = "Content",
        .width = 300,
        .height = 200,
    };
    return DialogView::CreateDialogNode(dialogProperties, contentNode);
}

/**
 * @tc.name: NeedIgnoreKeyboard001
 * @tc.desc: Branch: if (opts && (opts->type & KEYBOARD) && (opts->edges & BOTTOM)) = false
 *           Condition: opts = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, NeedIgnoreKeyboard001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    navDestinationLayoutProperty->safeAreaExpandOpts_ = nullptr;

    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    bool ret = navDestinationPattern->NeedIgnoreKeyboard();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: NeedIgnoreKeyboard002
 * @tc.desc: Branch: if (opts && (opts->type & KEYBOARD) && (opts->edges & BOTTOM)) = false
 *           Condition: opts = true, opts->type & KEYBOARD = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, NeedIgnoreKeyboard002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    navDestinationLayoutProperty->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    navDestinationLayoutProperty->safeAreaExpandOpts_->type = SAFE_AREA_TYPE_NONE;
    navDestinationLayoutProperty->safeAreaExpandOpts_->edges = SAFE_AREA_EDGE_NONE;

    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    bool ret = navDestinationPattern->NeedIgnoreKeyboard();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: NeedIgnoreKeyboard003
 * @tc.desc: Branch: if (opts && (opts->type & KEYBOARD) && (opts->edges & BOTTOM)) = false
 *           Condition: opts = true, opts->type & KEYBOARD = true, opts->edges & BOTTOM = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, NeedIgnoreKeyboard003, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    navDestinationLayoutProperty->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    navDestinationLayoutProperty->safeAreaExpandOpts_->type = SAFE_AREA_TYPE_KEYBOARD;
    navDestinationLayoutProperty->safeAreaExpandOpts_->edges = SAFE_AREA_EDGE_NONE;

    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    bool ret = navDestinationPattern->NeedIgnoreKeyboard();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: NeedIgnoreKeyboard004
 * @tc.desc: Branch: if (opts && (opts->type & KEYBOARD) && (opts->edges & BOTTOM)) = true
 *           Condition: opts = true, opts->type & KEYBOARD = true, opts->edges & BOTTOM = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, NeedIgnoreKeyboard004, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    navDestinationLayoutProperty->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    navDestinationLayoutProperty->safeAreaExpandOpts_->type = SAFE_AREA_TYPE_KEYBOARD;
    navDestinationLayoutProperty->safeAreaExpandOpts_->edges = SAFE_AREA_EDGE_BOTTOM;

    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    bool ret = navDestinationPattern->NeedIgnoreKeyboard();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: OnFontScaleConfigurationUpdate001
 * @tc.desc: Branch: if (LessNotEqual(GetFontScale(), GetDialogBigFontSizeScale()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, OnFontScaleConfigurationUpdate001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->titleBarNode_ = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    titleBarNode->backButton_ = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    ASSERT_NE(backButtonNode, nullptr);
    auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto longPressCallback = [](GestureEvent& info) { };
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(longPressCallback);
    gestureHub->SetLongPressEvent(longPressEvent);
    auto pipelineContext = navDestinationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;

    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->OnFontScaleConfigurationUpdate();
    ASSERT_NE(gestureHub->longPressEventActuator_, nullptr);
    EXPECT_EQ(gestureHub->longPressEventActuator_->longPressEvent_, nullptr);
}

/**
 * @tc.name: OnFontScaleConfigurationUpdate002
 * @tc.desc: Branch: if (LessNotEqual(GetFontScale(), GetDialogBigFontSizeScale()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, OnFontScaleConfigurationUpdate002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->titleBarNode_ = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    titleBarNode->backButton_ = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    ASSERT_NE(backButtonNode, nullptr);
    auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto longPressCallback = [](GestureEvent& info) { };
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(longPressCallback);
    gestureHub->SetLongPressEvent(longPressEvent);
    auto pipelineContext = navDestinationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() + 1.0f;

    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->OnFontScaleConfigurationUpdate();
    ASSERT_NE(gestureHub->longPressEventActuator_, nullptr);
    EXPECT_NE(gestureHub->longPressEventActuator_->longPressEvent_, nullptr);
}

/**
 * @tc.name: SetSystemBarStyle001
 * @tc.desc: Branch: if (!backupStyle_.has_value()) = true
 *           Branch: if (IsFullPageNavigation() && IsTopNavDestination(host)) = false
 *           Condition: IsFullPageNavigation() = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, SetSystemBarStyle001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->navigationNode_ = navigationNode;
    navDestinationPattern->backupStyle_ = std::nullopt;
    auto pipelineContext = navDestinationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto windowManager = pipelineContext->GetWindowManager();
    // Make GetSystemBarStyle return nullptr
    windowManager->getSystemBarStyleCallback_ = nullptr;
    navigationPattern->isFullPageNavigation_ = false;
    std::optional<RefPtr<SystemBarStyle>> systemBarStyle = std::nullopt;
    windowManager->SetSetSystemBarStyleCallBack([&systemBarStyle](const RefPtr<SystemBarStyle>& style) {
        systemBarStyle = style;
    });

    auto mockSystemBarStyle = AceType::MakeRefPtr<MockSystemBarStyle>();
    navDestinationPattern->SetSystemBarStyle(mockSystemBarStyle);
    EXPECT_EQ(navDestinationPattern->backupStyle_, nullptr);
    EXPECT_EQ(systemBarStyle, std::nullopt);
}

/**
 * @tc.name: SetSystemBarStyle002
 * @tc.desc: Branch: if (!backupStyle_.has_value()) = false
 *           Branch: if (IsFullPageNavigation() && IsTopNavDestination(host)) = false
 *           Condition: IsFullPageNavigation() = true, IsTopNavDestination(host) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, SetSystemBarStyle002, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->navigationNode_ = navigationNode;
    navDestinationPattern->backupStyle_ = AceType::MakeRefPtr<MockSystemBarStyle>();
    auto pipelineContext = navDestinationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto windowManager = pipelineContext->GetWindowManager();
    // Make GetSystemBarStyle return nullptr
    windowManager->getSystemBarStyleCallback_ = nullptr;
    navigationPattern->isFullPageNavigation_ = true;
    std::optional<RefPtr<SystemBarStyle>> systemBarStyle = std::nullopt;
    windowManager->SetSetSystemBarStyleCallBack([&systemBarStyle](const RefPtr<SystemBarStyle>& style) {
        systemBarStyle = style;
    });

    auto mockSystemBarStyle = AceType::MakeRefPtr<MockSystemBarStyle>();
    navDestinationPattern->SetSystemBarStyle(mockSystemBarStyle);
    EXPECT_NE(navDestinationPattern->backupStyle_, nullptr);
    EXPECT_EQ(systemBarStyle, std::nullopt);
}

/**
 * @tc.name: SetSystemBarStyle003
 * @tc.desc: Branch: if (IsFullPageNavigation() && IsTopNavDestination(host)) = true
 *           Condition: IsFullPageNavigation() = true, IsTopNavDestination(host) = true
 *           Branch: if (currStyle_.value() != nullptr) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, SetSystemBarStyle003, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->navigationNode_ = navigationNode;
    navDestinationPattern->backupStyle_ = AceType::MakeRefPtr<MockSystemBarStyle>();
    navigationPattern->isFullPageNavigation_ = true;
    navigationStack->navPathList_.emplace_back(std::make_pair("Page1", navDestinationNode));
    auto pipelineContext = navDestinationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto windowManager = pipelineContext->GetWindowManager();
    std::optional<RefPtr<SystemBarStyle>> systemBarStyle = std::nullopt;
    windowManager->SetSetSystemBarStyleCallBack([&systemBarStyle](const RefPtr<SystemBarStyle>& style) {
        systemBarStyle = style;
    });

    auto mockSystemBarStyle = AceType::MakeRefPtr<MockSystemBarStyle>();
    navDestinationPattern->SetSystemBarStyle(mockSystemBarStyle);
    EXPECT_EQ(systemBarStyle, mockSystemBarStyle);
}

/**
 * @tc.name: SetSystemBarStyle004
 * @tc.desc: Branch: if (IsFullPageNavigation() && IsTopNavDestination(host)) = true
 *           Condition: IsFullPageNavigation() = true, IsTopNavDestination(host) = true
 *           Branch: if (currStyle_.value() != nullptr) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, SetSystemBarStyle004, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->navigationNode_ = navigationNode;
    auto mockSystemBarStyle = AceType::MakeRefPtr<MockSystemBarStyle>();
    navDestinationPattern->backupStyle_ = mockSystemBarStyle;
    navigationPattern->backupStyle_ = mockSystemBarStyle;
    navigationPattern->isFullPageNavigation_ = true;
    navigationStack->navPathList_.emplace_back(std::make_pair("Page1", navDestinationNode));
    auto pipelineContext = navDestinationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto windowManager = pipelineContext->GetWindowManager();
    std::optional<RefPtr<SystemBarStyle>> systemBarStyle = std::nullopt;
    windowManager->SetSetSystemBarStyleCallBack([&systemBarStyle](const RefPtr<SystemBarStyle>& style) {
        systemBarStyle = style;
    });

    navDestinationPattern->SetSystemBarStyle(nullptr);
    EXPECT_EQ(systemBarStyle, mockSystemBarStyle);
}

/**
 * @tc.name: OnWindowHide001
 * @tc.desc: Branch: if (!navPathInfo->GetIsEntry()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, OnWindowHide001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto mockNavigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(mockNavigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto navDestinationContext = AceType::MakeRefPtr<NavDestinationContext>();
    auto navPathInfo = AceType::MakeRefPtr<NavPathInfo>();
    navDestinationContext->SetNavPathInfo(navPathInfo);
    navDestinationPattern->SetNavDestinationContext(navDestinationContext);
    navDestinationContext->pathInfo_->isEntry_ = false;
    mockNavigationStack->SetIsEntryByIndex(navDestinationContext->GetIndex(), true);

    navDestinationPattern->OnWindowHide();
    EXPECT_EQ(navDestinationContext->pathInfo_->GetIsEntry(), false);
    EXPECT_EQ(mockNavigationStack->mockIsEntryMap_[navDestinationContext->index_], true);
}

/**
 * @tc.name: OnWindowHide002
 * @tc.desc: Branch: if (!navPathInfo->GetIsEntry()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, OnWindowHide002, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto mockNavigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(mockNavigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto navDestinationContext = AceType::MakeRefPtr<NavDestinationContext>();
    auto navPathInfo = AceType::MakeRefPtr<NavPathInfo>();
    navDestinationContext->SetNavPathInfo(navPathInfo);
    WeakPtr<NavigationStack> navigationStackWeak = navigationPattern->GetNavigationStack();
    navDestinationContext->SetNavigationStack(navigationStackWeak);
    navDestinationPattern->SetNavDestinationContext(navDestinationContext);
    navDestinationContext->pathInfo_->isEntry_ = true;
    mockNavigationStack->SetIsEntryByIndex(navDestinationContext->GetIndex(), true);

    navDestinationPattern->OnWindowHide();
    EXPECT_EQ(navDestinationContext->pathInfo_->GetIsEntry(), false);
    EXPECT_EQ(mockNavigationStack->mockIsEntryMap_[navDestinationContext->index_], false);
}

/**
 * @tc.name: OnWindowSizeChanged001
 * @tc.desc: Branch: if (preWidth_.has_value() && preWidth_.value() != width) = false
 *           Condition: preWidth_.has_value() = false
 *           Branch: if (navDestinationGroupNode->GetPrevMenuIsCustomValue(false)) = false
 *           Branch: if (targetNum == maxMenuNums_) = false
 *           Branch: if (type == WindowSizeChangeReason::ROTATION) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, OnWindowSizeChanged001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    int32_t width = 1000.0f;
    int32_t height = 800.0f;
    navDestinationPattern->preWidth_ = std::nullopt;
    navDestinationNode->propPrevMenuIsCustom_ = false;
    AnimationOption option;
    auto propertyCallback = []() {};
    auto finishCallback = []() {};
    auto animation = AnimationUtils::StartAnimation(option, propertyCallback, finishCallback);
    navDestinationPattern->barAnimations_.emplace(101, animation);
    navDestinationPattern->maxMenuNums_ = 0;
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->dialogNode_ = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto largeFontPopUpDialogNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    titleBarPattern->largeFontPopUpDialogNode_ = AceType::WeakClaim(AceType::RawPtr(largeFontPopUpDialogNode));

    navDestinationPattern->OnWindowSizeChanged(width, height, WindowSizeChangeReason::MOVE);
    EXPECT_EQ(navDestinationPattern->barAnimations_.size(), 1);
    auto targetNum = SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE
        ? MAX_MENU_NUM_LARGE : MAX_MENU_NUM_SMALL;
    EXPECT_EQ(navDestinationPattern->maxMenuNums_, targetNum);
    EXPECT_NE(titleBarPattern->GetBackButtonDialogNode(), nullptr);
    EXPECT_NE(titleBarPattern->GetLargeFontPopUpDialogNode(), nullptr);
}

/**
 * @tc.name: OnWindowSizeChanged002
 * @tc.desc: Branch: if (preWidth_.has_value() && preWidth_.value() != width) = false
 *           Condition: preWidth_.has_value() = true, preWidth_.value() != width = false
 *           Branch: if (navDestinationGroupNode->GetPrevMenuIsCustomValue(false)) = false
 *           Branch: if (targetNum == maxMenuNums_) = true
 *           Branch: if (type == WindowSizeChangeReason::ROTATION) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, OnWindowSizeChanged002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    int32_t width = 1000.0f;
    int32_t height = 800.0f;
    navDestinationPattern->preWidth_ = width;
    navDestinationNode->propPrevMenuIsCustom_ = false;
    AnimationOption option;
    auto propertyCallback = []() {};
    auto finishCallback = []() {};
    auto animation = AnimationUtils::StartAnimation(option, propertyCallback, finishCallback);
    navDestinationPattern->barAnimations_.emplace(101, animation);
    auto targetNum = SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE
        ? MAX_MENU_NUM_LARGE : MAX_MENU_NUM_SMALL;
    navDestinationPattern->maxMenuNums_ = targetNum;
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->dialogNode_ = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto largeFontPopUpDialogNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    titleBarPattern->largeFontPopUpDialogNode_ = AceType::WeakClaim(AceType::RawPtr(largeFontPopUpDialogNode));

    navDestinationPattern->OnWindowSizeChanged(width, height, WindowSizeChangeReason::ROTATION);
    EXPECT_EQ(navDestinationPattern->barAnimations_.size(), 1);
    EXPECT_EQ(navDestinationPattern->maxMenuNums_, targetNum);
    EXPECT_EQ(titleBarPattern->GetBackButtonDialogNode(), nullptr);
    EXPECT_EQ(titleBarPattern->GetLargeFontPopUpDialogNode(), nullptr);
}

/**
 * @tc.name: OnWindowSizeChanged003
 * @tc.desc: Branch: if (preWidth_.has_value() && preWidth_.value() != width) = true
 *           Condition: preWidth_.has_value() = true, preWidth_.value() != width = true
 *           Branch: if (navDestinationGroupNode->GetPrevMenuIsCustomValue(false)) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, OnWindowSizeChanged003, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    int32_t width = 1000.0f;
    int32_t height = 800.0f;
    navDestinationPattern->preWidth_ = width / 2;
    navDestinationNode->propPrevMenuIsCustom_ = true;
    AnimationOption option;
    auto propertyCallback = [](
        
    ) {};
    auto finishCallback = []() {};
    auto animation = AnimationUtils::StartAnimation(option, propertyCallback, finishCallback);
    navDestinationPattern->barAnimations_.emplace(101, animation);
    navDestinationPattern->maxMenuNums_ = 0;

    navDestinationPattern->OnWindowSizeChanged(width, height, WindowSizeChangeReason::ROTATION);
    EXPECT_EQ(navDestinationPattern->barAnimations_.size(), 0);
    EXPECT_EQ(navDestinationPattern->maxMenuNums_, 0);
}

/**
 * @tc.name: CloseLongPressDialog001
 * @tc.desc: Branch: if (backButtonDialogNode) = true
 *           Branch: if (menuItemDialogNode) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, CloseLongPressDialog001, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->dialogNode_ = NavDestinationPatternTestNg::CreateDialogNode();
    int32_t backButtonDialogNodeId = titleBarPattern->dialogNode_->GetId();
    auto pipelineContext = navDestinationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->dialogMap_.emplace(backButtonDialogNodeId, titleBarPattern->dialogNode_);
    auto menuItemDialogNode = NavDestinationPatternTestNg::CreateDialogNode();
    int32_t menuItemDialogNodeId = menuItemDialogNode->GetId();
    titleBarPattern->largeFontPopUpDialogNode_ = AceType::WeakClaim(AceType::RawPtr(menuItemDialogNode));
    overlayManager->dialogMap_.emplace(menuItemDialogNodeId, menuItemDialogNode);

    navDestinationPattern->CloseLongPressDialog();
    EXPECT_EQ(overlayManager->dialogMap_.find(backButtonDialogNodeId), overlayManager->dialogMap_.end());
    EXPECT_EQ(overlayManager->dialogMap_.find(menuItemDialogNodeId), overlayManager->dialogMap_.end());
    EXPECT_EQ(titleBarPattern->GetBackButtonDialogNode(), nullptr);
    EXPECT_EQ(titleBarPattern->GetLargeFontPopUpDialogNode(), nullptr);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: CloseLongPressDialog002
 * @tc.desc: Branch: if (backButtonDialogNode) = false
 *           Branch: if (menuItemDialogNode) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, CloseLongPressDialog002, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->dialogNode_ = nullptr;
    titleBarPattern->largeFontPopUpDialogNode_ = nullptr;

    navDestinationPattern->CloseLongPressDialog();
    auto pipelineContext = navDestinationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 0);
    EXPECT_EQ(titleBarPattern->GetBackButtonDialogNode(), nullptr);
    EXPECT_EQ(titleBarPattern->GetLargeFontPopUpDialogNode(), nullptr);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBarHiddenOffset001
 * @tc.desc: Branch: if (ctx.isBarShowing || ctx.isBarHiding) = true
 *           Condition: ctx.isBarShowing = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, UpdateBarHiddenOffset001, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = true;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    titleBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->UpdateBarHiddenOffset(navDestinationNode, titleBarNode, 150.0f, false);
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBarHiddenOffset002
 * @tc.desc: Branch: if (ctx.isBarShowing || ctx.isBarHiding) = true
 *           Condition: ctx.isBarShowing = false, ctx.isBarHiding = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, UpdateBarHiddenOffset002, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = true;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    titleBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->UpdateBarHiddenOffset(navDestinationNode, titleBarNode, 150.0f, false);
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBarHiddenOffset003
 * @tc.desc: Branch: if (ctx.isBarShowing || ctx.isBarHiding) = false
 *           Condition: ctx.isBarShowing = false, ctx.isBarHiding = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = true
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, UpdateBarHiddenOffset003, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = false;
    titleBarNode->renderContext_ = nullptr;

    navDestinationPattern->UpdateBarHiddenOffset(navDestinationNode, titleBarNode, 150.0f, false);
    EXPECT_EQ(titleBarNode->GetRenderContext(), nullptr);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBarHiddenOffset004
 * @tc.desc: Branch: if (ctx.isBarShowing || ctx.isBarHiding) = false
 *           Condition: ctx.isBarShowing = false, ctx.isBarHiding = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = true
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = false, NearZero(barHeight) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, UpdateBarHiddenOffset004, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = false;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 0.0f));
    titleBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->UpdateBarHiddenOffset(navDestinationNode, titleBarNode, 150.0f, false);
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBarHiddenOffset005
 * @tc.desc: Branch: if (ctx.isBarShowing || ctx.isBarHiding) = false
 *           Condition: ctx.isBarShowing = false, ctx.isBarHiding = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = false
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = false, NearZero(barHeight) = false
 *           Branch: if (isTitle) = false
 *           Branch: if (GreatOrEqual(threshold, halfBarHeight)) = false
 *           Branch: if (Positive(offset) && LessNotEqual(std::abs(preTranslate), threshold) &&
 *               GreatOrEqual(std::abs(newTranslate), threshold)) = false
 *           Condition: Positive(offset) = true, LessNotEqual(std::abs(preTranslate), threshold) = false
 *           Branch: if (Negative(offset) && LessNotEqual(barHeight - std::abs(preTranslate), threshold) &&
 *               GreatOrEqual(barHeight - std::abs(newTranslate), threshold)) = false
 *           Condition: Negative(offset) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, UpdateBarHiddenOffset005, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = false;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    titleBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->UpdateBarHiddenOffset(navDestinationNode, titleBarNode, 150.0f, false);
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 0.5f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBarHiddenOffset006
 * @tc.desc: Branch: if (ctx.isBarShowing || ctx.isBarHiding) = false
 *           Condition: ctx.isBarShowing = false, ctx.isBarHiding = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = false
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = false, NearZero(barHeight) = false
 *           Branch: if (isTitle) = true
 *           Branch: if (GreatOrEqual(threshold, halfBarHeight)) = true
 *           Branch: if (Positive(offset) && LessNotEqual(std::abs(preTranslate), threshold) &&
 *               GreatOrEqual(std::abs(newTranslate), threshold)) = false
 *           Condition: Positive(offset) = true, LessNotEqual(std::abs(preTranslate), threshold) = true,
 *               GreatOrEqual(std::abs(newTranslate), threshold)) = false
 *           Branch: if (Negative(offset) && LessNotEqual(barHeight - std::abs(preTranslate), threshold) &&
 *               GreatOrEqual(barHeight - std::abs(newTranslate), threshold)) = false
 *           Condition: Negative(offset) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, UpdateBarHiddenOffset006, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = false;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 50.0f));
    titleBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->UpdateBarHiddenOffset(navDestinationNode, titleBarNode, 20.0f, true);
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 0.6f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBarHiddenOffset007
 * @tc.desc: Branch: if (ctx.isBarShowing || ctx.isBarHiding) = false
 *           Condition: ctx.isBarShowing = false, ctx.isBarHiding = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = false
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = false, NearZero(barHeight) = false
 *           Branch: if (isTitle) = false
 *           Branch: if (GreatOrEqual(threshold, halfBarHeight)) = true
 *           Branch: if (Positive(offset) && LessNotEqual(std::abs(preTranslate), threshold) &&
 *               GreatOrEqual(std::abs(newTranslate), threshold)) = true
 *           Condition: Positive(offset) = true, LessNotEqual(std::abs(preTranslate), threshold) = true,
 *               GreatOrEqual(std::abs(newTranslate), threshold)) = true
 *           Branch: if (Negative(offset) && LessNotEqual(barHeight - std::abs(preTranslate), threshold) &&
 *               GreatOrEqual(barHeight - std::abs(newTranslate), threshold)) = false
 *           Condition: Negative(offset) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, UpdateBarHiddenOffset007, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = false;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 10.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 50.0f));
    toolBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->UpdateBarHiddenOffset(navDestinationNode, toolBarNode, 20.0f, false);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 0.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBarHiddenOffset008
 * @tc.desc: Branch: if (ctx.isBarShowing || ctx.isBarHiding) = false
 *           Condition: ctx.isBarShowing = false, ctx.isBarHiding = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = false
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = false, NearZero(barHeight) = false
 *           Branch: if (isTitle) = false
 *           Branch: if (GreatOrEqual(threshold, halfBarHeight)) = false
 *           Branch: if (Positive(offset) && LessNotEqual(std::abs(preTranslate), threshold) &&
 *               GreatOrEqual(std::abs(newTranslate), threshold)) = false
 *           Condition: Positive(offset) = false
 *           Branch: if (Negative(offset) && LessNotEqual(barHeight - std::abs(preTranslate), threshold) &&
 *               GreatOrEqual(barHeight - std::abs(newTranslate), threshold)) = false
 *           Condition: Negative(offset) = true, LessNotEqual(barHeight - std::abs(preTranslate), threshold) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, UpdateBarHiddenOffset008, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = false;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 10.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 50.0f));
    toolBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->UpdateBarHiddenOffset(navDestinationNode, toolBarNode, -20.0f, false);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBarHiddenOffset009
 * @tc.desc: Branch: if (ctx.isBarShowing || ctx.isBarHiding) = false
 *           Condition: ctx.isBarShowing = false, ctx.isBarHiding = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = false
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = false, NearZero(barHeight) = false
 *           Branch: if (isTitle) = false
 *           Branch: if (GreatOrEqual(threshold, halfBarHeight)) = false
 *           Branch: if (Positive(offset) && LessNotEqual(std::abs(preTranslate), threshold) &&
 *               GreatOrEqual(std::abs(newTranslate), threshold)) = false
 *           Condition: Positive(offset) = false
 *           Branch: if (Negative(offset) && LessNotEqual(barHeight - std::abs(preTranslate), threshold) &&
 *               GreatOrEqual(barHeight - std::abs(newTranslate), threshold)) = false
 *           Condition: Negative(offset) = true, LessNotEqual(barHeight - std::abs(preTranslate), threshold) = true,
 *               GreatOrEqual(barHeight - std::abs(newTranslate), threshold)) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, UpdateBarHiddenOffset009, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = false;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 30.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 50.0f));
    toolBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->UpdateBarHiddenOffset(navDestinationNode, toolBarNode, -1.0f, false);
    EXPECT_TRUE(NearEqual(toolBarRenderContext->GetOpacity().value_or(0.0f), 0.42f));
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBarHiddenOffset010
 * @tc.desc: Branch: if (ctx.isBarShowing || ctx.isBarHiding) = false
 *           Condition: ctx.isBarShowing = false, ctx.isBarHiding = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = false
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = false, NearZero(barHeight) = false
 *           Branch: if (isTitle) = false
 *           Branch: if (GreatOrEqual(threshold, halfBarHeight)) = false
 *           Branch: if (Positive(offset) && LessNotEqual(std::abs(preTranslate), threshold) &&
 *               GreatOrEqual(std::abs(newTranslate), threshold)) = false
 *           Condition: Positive(offset) = false
 *           Branch: if (Negative(offset) && LessNotEqual(barHeight - std::abs(preTranslate), threshold) &&
 *               GreatOrEqual(barHeight - std::abs(newTranslate), threshold)) = true
 *           Condition: Negative(offset) = true, LessNotEqual(barHeight - std::abs(preTranslate), threshold) = true,
 *               GreatOrEqual(barHeight - std::abs(newTranslate), threshold)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, UpdateBarHiddenOffset010, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = false;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 30.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 50.0f));
    toolBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->UpdateBarHiddenOffset(navDestinationNode, toolBarNode, -10.0f, false);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateTitleAndToolBarHiddenOffset001
 * @tc.desc: Branch: if (EnableTitleBarSwipe(nodeBase)) = false
 *           Branch: if (EnableToolBarSwipe(nodeBase)) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, UpdateTitleAndToolBarHiddenOffset001, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    navDestinationLayoutProperty->propHideTitleBar_ = true;
    navDestinationLayoutProperty->propHideToolBar_ = true;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    titleBarRenderContext->UpdateOpacity(1.0f);
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    toolBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->UpdateTitleAndToolBarHiddenOffset(0.0f);
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 1.0f);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateTitleAndToolBarHiddenOffset002
 * @tc.desc: Branch: if (EnableTitleBarSwipe(nodeBase)) = true
 *           Branch: if (EnableToolBarSwipe(nodeBase)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, UpdateTitleAndToolBarHiddenOffset002, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    navDestinationLayoutProperty->propHideTitleBar_ = false;
    navDestinationLayoutProperty->propHideToolBar_ = false;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    titleBarRenderContext->UpdateOpacity(1.0f);
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    toolBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->UpdateTitleAndToolBarHiddenOffset(0.0f);
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 1.0f);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 0.875f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: CancelShowTitleAndToolBarTask001
 * @tc.desc: Branch: if (titleBarSwipeContext_.showBarTask) = true
 *           Branch: if (toolBarSwipeContext_.showBarTask) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, CancelShowTitleAndToolBarTask001, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->titleBarSwipeContext_.showBarTask.Reset([] { });
    navDestinationPattern->toolBarSwipeContext_.showBarTask.Reset([] { });

    navDestinationPattern->CancelShowTitleAndToolBarTask();
    EXPECT_FALSE(navDestinationPattern->titleBarSwipeContext_.showBarTask);
    EXPECT_FALSE(navDestinationPattern->toolBarSwipeContext_.showBarTask);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: CancelShowTitleAndToolBarTask002
 * @tc.desc: Branch: if (titleBarSwipeContext_.showBarTask) = false
 *           Branch: if (toolBarSwipeContext_.showBarTask) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, CancelShowTitleAndToolBarTask002, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->titleBarSwipeContext_.showBarTask.Reset(nullptr);
    navDestinationPattern->toolBarSwipeContext_.showBarTask.Reset(nullptr);

    navDestinationPattern->CancelShowTitleAndToolBarTask();
    EXPECT_FALSE(navDestinationPattern->titleBarSwipeContext_.showBarTask);
    EXPECT_FALSE(navDestinationPattern->toolBarSwipeContext_.showBarTask);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ResetBarState001
 * @tc.desc: Branch: if (ctx.isBarHiding || ctx.isBarShowing) = true
 *           Condition: ctx.isBarHiding = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ResetBarState001, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarHiding = true;
    swipeContext.isBarShowing = false;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 120.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 100.0f));
    toolBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->ResetBarState(navDestinationNode, toolBarNode, false);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ResetBarState002
 * @tc.desc: Branch: if (ctx.isBarHiding || ctx.isBarShowing) = true
 *           Condition: ctx.isBarHiding = false, ctx.isBarShowing = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ResetBarState002, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarHiding = false;
    swipeContext.isBarShowing = true;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 120.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 100.0f));
    toolBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->ResetBarState(navDestinationNode, toolBarNode, false);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ResetBarState003
 * @tc.desc: Branch: if (ctx.isBarHiding || ctx.isBarShowing) = false
 *           Condition: ctx.isBarHiding = false, ctx.isBarShowing = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = true
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ResetBarState003, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarHiding = false;
    swipeContext.isBarShowing = false;
    toolBarNode->renderContext_ = nullptr;

    navDestinationPattern->ResetBarState(navDestinationNode, toolBarNode, false);
    EXPECT_EQ(toolBarNode->GetRenderContext(), nullptr);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ResetBarState004
 * @tc.desc: Branch: if (ctx.isBarHiding || ctx.isBarShowing) = false
 *           Condition: ctx.isBarHiding = false, ctx.isBarShowing = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = true
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = false, NearZero(barHeight) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ResetBarState004, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarHiding = false;
    swipeContext.isBarShowing = false;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 120.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 0.0f));
    toolBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->ResetBarState(navDestinationNode, toolBarNode, false);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ResetBarState005
 * @tc.desc: Branch: if (ctx.isBarHiding || ctx.isBarShowing) = false
 *           Condition: ctx.isBarHiding = false, ctx.isBarShowing = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = false
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = false, NearZero(barHeight) = false
 *           Branch: if (GreatOrEqual(threshold, halfBarHeight)) = false
 *           Branch: if (GreatNotEqual(showAreaHeight, 0.0f) && LessNotEqual(showAreaHeight, threshold)) = false
 *           Condition: GreatNotEqual(showAreaHeight, 0.0f) = false
 *           Branch: if (GreatOrEqual(showAreaHeight, barHeight - threshold) &&
 *               LessNotEqual(showAreaHeight, barHeight)) = false
 *           Condition: GreatOrEqual(showAreaHeight, barHeight - threshold) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ResetBarState005, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = false;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 120.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 100.0f));
    toolBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->ResetBarState(navDestinationNode, toolBarNode, false);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ResetBarState006
 * @tc.desc: Branch: if (ctx.isBarHiding || ctx.isBarShowing) = false
 *           Condition: ctx.isBarHiding = false, ctx.isBarShowing = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = false
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = false, NearZero(barHeight) = false
 *           Branch: if (GreatOrEqual(threshold, halfBarHeight)) = true
 *           Branch: if (GreatNotEqual(showAreaHeight, 0.0f) && LessNotEqual(showAreaHeight, threshold)) = false
 *           Condition: GreatNotEqual(showAreaHeight, 0.0f) = true, LessNotEqual(showAreaHeight, threshold) = false
 *           Branch: if (GreatOrEqual(showAreaHeight, barHeight - threshold) &&
 *               LessNotEqual(showAreaHeight, barHeight)) = true
 *           Condition: GreatOrEqual(showAreaHeight, barHeight - threshold) = true,
 *               LessNotEqual(showAreaHeight, barHeight)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ResetBarState006, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = false;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 10.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 50.0f));
    toolBarRenderContext->UpdateOpacity(0.0f);

    navDestinationPattern->ResetBarState(navDestinationNode, toolBarNode, false);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ResetBarState007
 * @tc.desc: Branch: if (ctx.isBarHiding || ctx.isBarShowing) = false
 *           Condition: ctx.isBarHiding = false, ctx.isBarShowing = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = false
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = false, NearZero(barHeight) = false
 *           Branch: if (GreatOrEqual(threshold, halfBarHeight)) = true
 *           Branch: if (GreatNotEqual(showAreaHeight, 0.0f) && LessNotEqual(showAreaHeight, threshold)) = true
 *           Condition: GreatNotEqual(showAreaHeight, 0.0f) = true, LessNotEqual(showAreaHeight, threshold)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ResetBarState007, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = false;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 30.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 50.0f));
    toolBarRenderContext->UpdateOpacity(1.0f);

    navDestinationPattern->ResetBarState(navDestinationNode, toolBarNode, false);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 0.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ResetBarState008
 * @tc.desc: Branch: if (ctx.isBarHiding || ctx.isBarShowing) = false
 *           Condition: ctx.isBarHiding = false, ctx.isBarShowing = false
 *           Branch: if (!GetTitleOrToolBarTranslateAndHeight() || NearZero(barHeight)) = false
 *           Condition: !GetTitleOrToolBarTranslateAndHeight() = false, NearZero(barHeight) = false
 *           Branch: if (GreatOrEqual(threshold, halfBarHeight)) = true
 *           Branch: if (GreatNotEqual(showAreaHeight, 0.0f) && LessNotEqual(showAreaHeight, threshold)) = true
 *           Condition: GreatNotEqual(showAreaHeight, 0.0f) = true, LessNotEqual(showAreaHeight, threshold)) = true
 *           Branch: if (GreatOrEqual(showAreaHeight, barHeight - threshold) &&
 *               LessNotEqual(showAreaHeight, barHeight)) = false
 *           Condition: GreatOrEqual(showAreaHeight, barHeight - threshold) = true,
 *               LessNotEqual(showAreaHeight, barHeight)) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ResetBarState008, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(false);
    swipeContext.isBarShowing = false;
    swipeContext.isBarHiding = false;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 50.0f));
    toolBarRenderContext->UpdateOpacity(0.0f);

    navDestinationPattern->ResetBarState(navDestinationNode, toolBarNode, false);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 0.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ResetTitleAndToolBarState001
 * @tc.desc: Branch: if (EnableTitleBarSwipe(nodeBase)) = false
 *           Branch: if (EnableToolBarSwipe(nodeBase)) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ResetTitleAndToolBarState001, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    navDestinationLayoutProperty->propHideTitleBar_ = true;
    navDestinationLayoutProperty->propHideToolBar_ = true;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    titleBarRenderContext->UpdateOpacity(0.0f);
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    toolBarRenderContext->UpdateOpacity(0.0f);

    navDestinationPattern->ResetTitleAndToolBarState();
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 0.0f);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 0.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ResetTitleAndToolBarState002
 * @tc.desc: Branch: if (EnableTitleBarSwipe(nodeBase)) = true
 *           Branch: if (EnableToolBarSwipe(nodeBase)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ResetTitleAndToolBarState002, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    navDestinationLayoutProperty->propHideTitleBar_ = false;
    navDestinationLayoutProperty->propHideToolBar_ = false;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 10.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 50.0f));
    titleBarRenderContext->UpdateOpacity(0.0f);
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 10.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 50.0f));
    toolBarRenderContext->UpdateOpacity(0.0f);

    navDestinationPattern->ResetTitleAndToolBarState();
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 1.0f);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ShowTitleAndToolBar001
 * @tc.desc: Branch: if (EnableTitleBarSwipe(nodeBase)) = false
 *           Branch: if (EnableToolBarSwipe(nodeBase)) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ShowTitleAndToolBar001, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    navDestinationLayoutProperty->propHideTitleBar_ = true;
    navDestinationLayoutProperty->propHideToolBar_ = true;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    titleBarRenderContext->UpdateOpacity(0.0f);
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    toolBarRenderContext->UpdateOpacity(0.0f);

    navDestinationPattern->ShowTitleAndToolBar();
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 0.0f);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 0.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ShowTitleAndToolBar002
 * @tc.desc: Branch: if (EnableTitleBarSwipe(nodeBase)) = true
 *           Branch: if (GetTitleOrToolBarTranslateAndHeight(titleBarNode, translate, barHeight)) = false
 *           Branch: if (EnableToolBarSwipe(nodeBase)) = true
 *           Branch: if (GetTitleOrToolBarTranslateAndHeight(toolBarNode, translate, barHeight)) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ShowTitleAndToolBar002, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    navDestinationLayoutProperty->propHideTitleBar_ = false;
    titleBarNode->renderContext_ = nullptr;
    navDestinationLayoutProperty->propHideToolBar_ = false;
    toolBarNode->renderContext_ = nullptr;

    navDestinationPattern->ShowTitleAndToolBar();
    EXPECT_EQ(titleBarNode->GetRenderContext(), nullptr);
    EXPECT_EQ(toolBarNode->GetRenderContext(), nullptr);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ShowTitleAndToolBar003
 * @tc.desc: Branch: if (EnableTitleBarSwipe(nodeBase)) = true
 *           Branch: if (GetTitleOrToolBarTranslateAndHeight(titleBarNode, translate, barHeight)) = true
 *           Branch: if (titleBarSwipeContext_.showBarTask) = false
 *           Branch: if (EnableToolBarSwipe(nodeBase)) = true
 *           Branch: if (GetTitleOrToolBarTranslateAndHeight(toolBarNode, translate, barHeight)) = true
 *           Branch: if (toolBarSwipeContext_.showBarTask) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ShowTitleAndToolBar003, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    navDestinationLayoutProperty->propHideTitleBar_ = false;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    titleBarRenderContext->UpdateOpacity(0.0f);
    navDestinationPattern->titleBarSwipeContext_.showBarTask.Reset(nullptr);
    navDestinationLayoutProperty->propHideToolBar_ = false;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    toolBarRenderContext->UpdateOpacity(0.0f);
    navDestinationPattern->toolBarSwipeContext_.showBarTask.Reset(nullptr);

    navDestinationPattern->ShowTitleAndToolBar();
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 1.0f);
    EXPECT_FALSE(navDestinationPattern->titleBarSwipeContext_.showBarTask);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 1.0f);
    EXPECT_FALSE(navDestinationPattern->toolBarSwipeContext_.showBarTask);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: ShowTitleAndToolBar004
 * @tc.desc: Branch: if (EnableTitleBarSwipe(nodeBase)) = true
 *           Branch: if (GetTitleOrToolBarTranslateAndHeight(titleBarNode, translate, barHeight)) = true
 *           Branch: if (titleBarSwipeContext_.showBarTask) = true
 *           Branch: if (EnableToolBarSwipe(nodeBase)) = true
 *           Branch: if (GetTitleOrToolBarTranslateAndHeight(toolBarNode, translate, barHeight)) = true
 *           Branch: if (toolBarSwipeContext_.showBarTask) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, ShowTitleAndToolBar004, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navDestinationNode->toolBarNode_ = toolBarNode;
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    navDestinationLayoutProperty->propHideTitleBar_ = false;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    titleBarRenderContext->UpdateOpacity(0.0f);
    navDestinationPattern->titleBarSwipeContext_.showBarTask.Reset([] { });
    navDestinationLayoutProperty->propHideToolBar_ = false;
    auto toolBarRenderContext = AceType::DynamicCast<MockRenderContext>(toolBarNode->GetRenderContext());
    ASSERT_NE(toolBarRenderContext, nullptr);
    toolBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    toolBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 400.0f));
    toolBarRenderContext->UpdateOpacity(0.0f);
    navDestinationPattern->toolBarSwipeContext_.showBarTask.Reset([] { });

    navDestinationPattern->ShowTitleAndToolBar();
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 1.0f);
    EXPECT_FALSE(navDestinationPattern->titleBarSwipeContext_.showBarTask);
    EXPECT_EQ(toolBarRenderContext->GetOpacity(), 1.0f);
    EXPECT_FALSE(navDestinationPattern->toolBarSwipeContext_.showBarTask);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: StopHideBarIfNeeded001
 * @tc.desc: Branch: if (!ctx.isBarHiding) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, StopHideBarIfNeeded001, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(true);
    swipeContext.isBarHiding = true;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 100.0f));
    titleBarRenderContext->UpdateOpacity(0.0f);

    navDestinationPattern->StopHideBarIfNeeded(0.0f, true);
    EXPECT_FALSE(swipeContext.isBarHiding);
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 1.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: StopHideBarIfNeeded002
 * @tc.desc: Branch: if (!ctx.isBarHiding) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, StopHideBarIfNeeded002, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto& swipeContext = navDestinationPattern->GetSwipeContext(true);
    swipeContext.isBarHiding = false;
    auto titleBarRenderContext = AceType::DynamicCast<MockRenderContext>(titleBarNode->GetRenderContext());
    ASSERT_NE(titleBarRenderContext, nullptr);
    titleBarRenderContext->UpdateTransformTranslate({ 0.0f, 50.0f, 0.0f });
    titleBarRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 500.0f, 100.0f));
    titleBarRenderContext->UpdateOpacity(0.0f);

    navDestinationPattern->StopHideBarIfNeeded(0.0f, true);
    EXPECT_FALSE(swipeContext.isBarHiding);
    EXPECT_EQ(titleBarRenderContext->GetOpacity(), 0.0f);
    NavDestinationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetSerializedParamTest001
 * @tc.desc: Branch: if UpdateSerializedParam done
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternTestNg, GetSerializedParamTest001, TestSize.Level1)
{
    NavDestinationPatternTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    const std::string param = "{}";
    navDestinationPattern->UpdateSerializedParam(param);
    ASSERT_EQ(navDestinationPattern->GetSerializedParam(), param);
    NavDestinationPatternTestNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG