/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
#include "test/unittest/core/pattern/navigation/mock_navigation_stack.h"
#include "test/unittest/core/pattern/navigation/mock_navigation_route.h"

#define protected public
#define private public
#include "base/i18n/localization.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/navigation/navdestination_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/navigation_toolbar_util.h"
#include "core/components_ng/property/menu_property.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_context.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_static.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_scrollable_processor.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string TEST_NAV_TITLE = "NavDestinationStaticTest";
const std::string TEST_NAV_SUBTITLE = "NavDestinationStaticSubTitle";
const std::string TEST_IMAGE_SRC = "test_icon.png";
const std::string TEST_ACCESSIBILITY_TEXT = "back_accessibility";
const std::string TEST_INSPECTOR_ID = "test_inspector_id";
constexpr int32_t TEST_REASON = 1;
const Dimension TEST_TITLE_HEIGHT = 56.0_vp;
const Color TEST_BG_COLOR = Color::BLUE;
const Color TEST_SYSTEM_BAR_COLOR = Color::WHITE;
constexpr bool TEST_HIDE_TITLE_BAR = true;
constexpr bool TEST_HIDE_TOOL_BAR = true;
constexpr bool TEST_HIDE_BACK_BUTTON = true;
constexpr bool TEST_ANIMATED = true;
constexpr bool TEST_RECOVERABLE = true;
constexpr bool TEST_IS_HIDE_ITEM_TEXT = true;

class MockNavDestinationScrollableProcessor : public NavDestinationScrollableProcessor {
    DECLARE_ACE_TYPE(MockNavDestinationScrollableProcessor, NavDestinationScrollableProcessor);

public:
    MockNavDestinationScrollableProcessor() = default;
    ~MockNavDestinationScrollableProcessor() override = default;

    MOCK_METHOD0(UpdateBindingRelation, void());
    MOCK_METHOD1(SetNodeId, void(int32_t id));
    MOCK_METHOD1(SetNavDestinationPattern, void(WeakPtr<NavDestinationPattern> pattern));
    MOCK_METHOD0(UnbindAllScrollers, void());
};

RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == NavigationBarTheme::TypeId()) {
        return AceType::MakeRefPtr<NavigationBarTheme>();
    } else {
        return nullptr;
    }
}
} // namespace

class NavDestinationModelStaticTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}
    RefPtr<NavDestinationGroupNode> CreateNavDestinationNode();
    RefPtr<NavDestinationGroupNode> CreateNavDestinationNodeWithContent();
};

void NavDestinationModelStaticTestNg::SetUpTestCase()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void NavDestinationModelStaticTestNg::TearDownTestCase()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

RefPtr<NavDestinationGroupNode> NavDestinationModelStaticTestNg::CreateNavDestinationNode()
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    pattern->frameNode_ = WeakPtr<FrameNode>(navDestinationNode);
    auto toolBarPattern = AceType::MakeRefPtr<NavToolbarPattern>();
    auto toolBarNode = AceType::MakeRefPtr<NavToolbarNode>(
        V2::TOOL_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), toolBarPattern);
    navDestinationNode->toolBarNode_ = toolBarNode;
    navDestinationNode->preToolBarNode_ = toolBarNode;
    navDestinationNode->AddChild(toolBarNode);
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>(
        V2::TITLE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), titleBarPattern);
    auto backButtonNode = FrameNode::CreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    titleBarNode->SetBackButton(backButtonNode);
    titleBarNode->AddChild(backButtonNode);
    navDestinationNode->titleBarNode_ = titleBarNode;
    navDestinationNode->AddChild(titleBarNode);
    return navDestinationNode;
}

RefPtr<NavDestinationGroupNode> NavDestinationModelStaticTestNg::CreateNavDestinationNodeWithContent()
{
    auto node = CreateNavDestinationNode();
    if (node) {
        auto contentPattern = AceType::MakeRefPtr<NavDestinationContentPattern>(true);
        auto contentNode = AceType::MakeRefPtr<FrameNode>(
            V2::NAVDESTINATION_CONTENT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), contentPattern);
        node->contentNode_ = contentNode;
    }
    return node;
}

HWTEST_F(NavDestinationModelStaticTestNg, NavDestinationNodeSetup001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    EXPECT_NE(navDestinationNode->GetTitleBarNode(), nullptr);
    EXPECT_NE(navDestinationNode->GetPattern<NavDestinationPattern>(), nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, NavDestinationNodeSetup002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, NavDestinationNodeSetup003, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto existingTitleBar = navDestinationNode->GetTitleBarNode();
    ASSERT_NE(existingTitleBar, nullptr);
    EXPECT_EQ(navDestinationNode->GetTitleBarNode(), existingTitleBar);
    EXPECT_NE(navDestinationNode->GetPattern<NavDestinationPattern>(), nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, NavDestinationNodeSetup004, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto layoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetHideTitleBar001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    ASSERT_NE(frameNode, nullptr);
    NavDestinationModelStatic::SetHideTitleBar(frameNode, TEST_HIDE_TITLE_BAR, TEST_ANIMATED);
    auto layoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->GetHideTitleBarValue(false));
    EXPECT_TRUE(layoutProperty->GetIsAnimatedTitleBarValue(false));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetHideTitleBar002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    ASSERT_NE(frameNode, nullptr);
    NavDestinationModelStatic::SetHideTitleBar(frameNode, false, false);
    auto layoutProperty = navDestinationNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetHideTitleBarValue(true));
    EXPECT_FALSE(layoutProperty->GetIsAnimatedTitleBarValue(true));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetHideToolBar001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    ASSERT_NE(frameNode, nullptr);
    NavDestinationModelStatic::SetHideToolBar(frameNode, TEST_HIDE_TOOL_BAR, TEST_ANIMATED);
    auto layoutProperty = navDestinationNode->GetLayoutPropertyPtr<NavDestinationLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->GetHideToolBarValue(false));
    EXPECT_TRUE(layoutProperty->GetIsAnimatedToolBarValue(false));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetHideToolBar002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto layoutProperty = navDestinationNode->GetLayoutPropertyPtr<NavDestinationLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetHideToolBarValue(false));
    NavDestinationModelStatic::SetHideToolBar(nullptr, TEST_HIDE_TOOL_BAR, TEST_ANIMATED);
    EXPECT_FALSE(layoutProperty->GetHideToolBarValue(false));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetHideToolBar003, TestSize.Level1)
{
    SetUpTestCase();
    auto otherNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(otherNode, nullptr);
    NavDestinationModelStatic::SetHideToolBar(AceType::RawPtr(otherNode), TEST_HIDE_TOOL_BAR, TEST_ANIMATED);
    auto layoutProperty = otherNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    EXPECT_EQ(layoutProperty, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetHideBackButton001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->SetNeedResetMainTitleProperty(false);
    titleBarPattern->SetNeedResetSubTitleProperty(false);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetHideBackButton(frameNode, TEST_HIDE_BACK_BUTTON);
    EXPECT_TRUE(titleBarPattern->shouldResetMainTitleProperty_);
    EXPECT_TRUE(titleBarPattern->shouldResetSubTitleProperty_);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetHideBackButton002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto layoutProperty = navDestinationNode->GetLayoutPropertyPtr<NavDestinationLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propHideBackButton_ = false;
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->SetNeedResetMainTitleProperty(false);
    titleBarPattern->SetNeedResetSubTitleProperty(false);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetHideBackButton(frameNode, true);
    EXPECT_TRUE(titleBarPattern->shouldResetMainTitleProperty_);
    EXPECT_TRUE(titleBarPattern->shouldResetSubTitleProperty_);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetHideBackButton003, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto layoutProperty = navDestinationNode->GetLayoutPropertyPtr<NavDestinationLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propHideBackButton_ = false;
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->SetNeedResetMainTitleProperty(false);
    titleBarPattern->SetNeedResetSubTitleProperty(false);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetHideBackButton(frameNode, false);
    EXPECT_FALSE(titleBarPattern->shouldResetMainTitleProperty_);
    EXPECT_FALSE(titleBarPattern->shouldResetSubTitleProperty_);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetBackgroundColor001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->SetIsUserDefinedBgColor(false);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetBackgroundColor(frameNode, TEST_BG_COLOR, true);
    EXPECT_TRUE(navDestinationPattern->IsUserDefinedBgColor());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetBackgroundColor002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->SetIsUserDefinedBgColor(true);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetBackgroundColor(frameNode, TEST_BG_COLOR, false);
    EXPECT_FALSE(navDestinationPattern->IsUserDefinedBgColor());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetBackgroundColor003, TestSize.Level1)
{
    SetUpTestCase();
    auto otherNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(otherNode, nullptr);
    NavDestinationModelStatic::SetBackgroundColor(AceType::RawPtr(otherNode), TEST_BG_COLOR, true);
    auto layoutProperty = otherNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    EXPECT_EQ(layoutProperty, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetNavDestinationMode001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetNavDestinationMode(frameNode, NavDestinationMode::DIALOG);
    EXPECT_EQ(navDestinationNode->GetNavDestinationMode(), NavDestinationMode::DIALOG);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetNavDestinationMode002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetNavDestinationMode(frameNode, std::nullopt);
    EXPECT_EQ(navDestinationNode->GetNavDestinationMode(), NavDestinationMode::STANDARD);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetNavDestinationMode003, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    EXPECT_EQ(navDestinationNode->GetNavDestinationMode(), NavDestinationMode::STANDARD);
    NavDestinationModelStatic::SetNavDestinationMode(nullptr, NavDestinationMode::STANDARD);
    EXPECT_EQ(navDestinationNode->GetNavDestinationMode(), NavDestinationMode::STANDARD);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetRecoverable001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetRecoverable(frameNode, TEST_RECOVERABLE);
    EXPECT_TRUE(navDestinationNode->CanRecovery());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetRecoverable002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetRecoverable(frameNode, std::nullopt);
    EXPECT_TRUE(navDestinationNode->CanRecovery());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetRecoverable003, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetRecoverable(frameNode, false);
    EXPECT_FALSE(navDestinationNode->CanRecovery());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetSystemTransitionType001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetSystemTransitionType(frameNode, NavigationSystemTransitionType::FADE);
    EXPECT_EQ(navDestinationNode->GetSystemTransitionType(), NavigationSystemTransitionType::FADE);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnActive001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    bool onActiveFired = false;
    auto onActive = [&onActiveFired](int32_t reason) { onActiveFired = true; };
    NavDestinationModelStatic::SetOnActive(frameNode, std::move(onActive));
    auto eventHub = navDestinationNode->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnActive(TEST_REASON);
    EXPECT_TRUE(onActiveFired);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnActive002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto eventHub = navDestinationNode->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->onActive_ == nullptr);
    auto onActive = [](int32_t reason) {};
    NavDestinationModelStatic::SetOnActive(nullptr, std::move(onActive));
    EXPECT_TRUE(eventHub->onActive_ == nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnInactive001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    bool onInactiveFired = false;
    auto onInactive = [&onInactiveFired](int32_t reason) { onInactiveFired = true; };
    NavDestinationModelStatic::SetOnInactive(frameNode, std::move(onInactive));
    auto eventHub = navDestinationNode->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnInactive(TEST_REASON);
    EXPECT_TRUE(onInactiveFired);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnInactive002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto eventHub = navDestinationNode->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->onInactive_ == nullptr);
    auto onInactive = [](int32_t reason) {};
    NavDestinationModelStatic::SetOnInactive(nullptr, std::move(onInactive));
    EXPECT_TRUE(eventHub->onInactive_ == nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomTransition001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationTransitionDelegate delegate =
        [](NavigationOperation operation, bool isEnter) -> std::optional<std::vector<NavDestinationTransition>> {
        return std::nullopt;
    };
    NavDestinationModelStatic::SetCustomTransition(frameNode, std::move(delegate));
    EXPECT_TRUE(navDestinationNode->navDestinationTransitionDelegate_);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomTransition002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationTransitionDelegate delegate = nullptr;
    NavDestinationModelStatic::SetCustomTransition(frameNode, std::move(delegate));
    EXPECT_FALSE(navDestinationNode->navDestinationTransitionDelegate_);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnShown001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    bool onShownFired = false;
    auto onShown = [&onShownFired](int32_t reason) { onShownFired = true; };
    NavDestinationModelStatic::SetOnShown(frameNode, std::move(onShown));
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->onShownEvent_, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnShown002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->onShownEvent_ == nullptr);
    auto onShown = [](int32_t reason) {};
    NavDestinationModelStatic::SetOnShown(nullptr, std::move(onShown));
    EXPECT_TRUE(eventHub->onShownEvent_ == nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnHidden001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    bool onHiddenFired = false;
    auto onHidden = [&onHiddenFired](int32_t reason) { onHiddenFired = true; };
    NavDestinationModelStatic::SetOnHidden(frameNode, std::move(onHidden));
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->onHiddenEvent_, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnHidden002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->onHiddenEvent_ == nullptr);
    auto onHidden = [](int32_t reason) {};
    NavDestinationModelStatic::SetOnHidden(nullptr, std::move(onHidden));
    EXPECT_TRUE(eventHub->onHiddenEvent_ == nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnBackPressed001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    auto onBackPressed = []() -> bool { return true; };
    NavDestinationModelStatic::SetOnBackPressed(frameNode, std::move(onBackPressed));
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->onBackPressedEvent_, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnBackPressed002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->onBackPressedEvent_ == nullptr);
    auto onBackPressed = []() -> bool { return true; };
    NavDestinationModelStatic::SetOnBackPressed(nullptr, std::move(onBackPressed));
    EXPECT_TRUE(eventHub->onBackPressedEvent_ == nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnReady001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    bool onReadyFired = false;
    auto onReady = [&onReadyFired](RefPtr<NavDestinationContext>) { onReadyFired = true; };
    NavDestinationModelStatic::SetOnReady(frameNode, std::move(onReady));
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->onReadyEvent_, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnReady002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->onReadyEvent_ == nullptr);
    auto onReady = [](RefPtr<NavDestinationContext>) {};
    NavDestinationModelStatic::SetOnReady(nullptr, std::move(onReady));
    EXPECT_TRUE(eventHub->onReadyEvent_ == nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnWillAppear001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    bool willAppearFired = false;
    auto willAppear = [&willAppearFired]() { willAppearFired = true; };
    NavDestinationModelStatic::SetOnWillAppear(frameNode, std::move(willAppear));
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->onWillAppear_, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnWillAppear002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->onWillAppear_ == nullptr);
    auto willAppear = []() {};
    NavDestinationModelStatic::SetOnWillAppear(nullptr, std::move(willAppear));
    EXPECT_TRUE(eventHub->onWillAppear_ == nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnWillDisAppear001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    bool willDisAppearFired = false;
    auto willDisAppear = [&willDisAppearFired]() { willDisAppearFired = true; };
    NavDestinationModelStatic::SetOnWillDisAppear(frameNode, std::move(willDisAppear));
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->onWillDisAppear_, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnWillDisAppear002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->onWillDisAppear_ == nullptr);
    auto willDisAppear = []() {};
    NavDestinationModelStatic::SetOnWillDisAppear(nullptr, std::move(willDisAppear));
    EXPECT_TRUE(eventHub->onWillDisAppear_ == nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnWillShow001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    bool willShowFired = false;
    auto willShow = [&willShowFired]() { willShowFired = true; };
    NavDestinationModelStatic::SetOnWillShow(frameNode, std::move(willShow));
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->onWillShow_, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnWillShow002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->onWillShow_ == nullptr);
    auto willShow = []() {};
    NavDestinationModelStatic::SetOnWillShow(nullptr, std::move(willShow));
    EXPECT_TRUE(eventHub->onWillShow_ == nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnWillHide001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    bool willHideFired = false;
    auto willHide = [&willHideFired]() { willHideFired = true; };
    NavDestinationModelStatic::SetOnWillHide(frameNode, std::move(willHide));
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->onWillHide_, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnWillHide002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto eventHub = AceType::DynamicCast<NavDestinationEventHub>(
        navDestinationNode->GetEventHub<EventHub>());
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->onWillHide_ == nullptr);
    auto willHide = []() {};
    NavDestinationModelStatic::SetOnWillHide(nullptr, std::move(willHide));
    EXPECT_TRUE(eventHub->onWillHide_ == nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetTitleHeight001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetTitleHeight(frameNode, TEST_TITLE_HEIGHT, true);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    EXPECT_TRUE(titleBarLayoutProperty->HasTitleHeight());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetTitleHeight002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleHeight(TEST_TITLE_HEIGHT);
    EXPECT_TRUE(titleBarLayoutProperty->HasTitleHeight());
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetTitleHeight(frameNode, TEST_TITLE_HEIGHT, false);
    EXPECT_FALSE(titleBarLayoutProperty->HasTitleHeight());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetMenuItems001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    navDestinationNode->UpdatePrevMenuIsCustom(true);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    std::vector<NG::BarItem> menuItems;
    NavDestinationModelStatic::SetMenuItems(frameNode, std::move(menuItems));
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::REPLACE);
    EXPECT_FALSE(navDestinationNode->GetPrevMenuIsCustomValue(false));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetMenuItems002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    navDestinationNode->UpdatePrevMenuIsCustom(false);
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(-1, "Menu", MenuType::NAVIGATION_MENU));
    navDestinationNode->SetMenu(menuNode);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    std::vector<NG::BarItem> menuItems;
    NavDestinationModelStatic::SetMenuItems(frameNode, std::move(menuItems));
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::REPLACE);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetMenuItems003, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    navDestinationNode->UpdatePrevMenuIsCustom(false);
    navDestinationNode->SetMenu(nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    std::vector<NG::BarItem> menuItems;
    NavDestinationModelStatic::SetMenuItems(frameNode, std::move(menuItems));
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::ADD);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetMenuItems004, TestSize.Level1)
{
    SetUpTestCase();
    auto otherNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(otherNode, nullptr);
    std::vector<NG::BarItem> menuItems;
    NavDestinationModelStatic::SetMenuItems(AceType::RawPtr(otherNode), std::move(menuItems));
    auto layoutProperty = otherNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    EXPECT_EQ(layoutProperty, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomMenu001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto customNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
    navDestinationNode->SetMenu(customNode);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetCustomMenu(frameNode, customNode);
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::NONE);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomMenu002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto existingMenu = AceType::MakeRefPtr<FrameNode>(
        V2::MENU_ETS_TAG, 10000, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    navDestinationNode->menu_ = existingMenu;
    ASSERT_NE(navDestinationNode->GetMenu(), nullptr);
    auto customNode = AceType::MakeRefPtr<FrameNode>(
        V2::ROW_ETS_TAG, 20000, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(customNode->GetId(), navDestinationNode->GetMenu()->GetId());
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetCustomMenu(frameNode, customNode);
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::NONE);
    EXPECT_TRUE(navDestinationNode->GetPrevMenuIsCustomValue(false));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomMenu003, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    navDestinationNode->menu_ = nullptr;
    ASSERT_EQ(navDestinationNode->GetMenu(), nullptr);
    auto customNode = AceType::MakeRefPtr<FrameNode>(
        V2::ROW_ETS_TAG, 20000, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetCustomMenu(frameNode, customNode);
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::NONE);
    EXPECT_TRUE(navDestinationNode->GetPrevMenuIsCustomValue(false));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomMenu004, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    EXPECT_TRUE(navDestinationNode->GetPrevMenuIsCustomValue(false) == false);
    auto customNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
    NavDestinationModelStatic::SetCustomMenu(nullptr, customNode);
    EXPECT_TRUE(navDestinationNode->GetPrevMenuIsCustomValue(false) == false);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomTitle001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    navDestinationNode->UpdatePrevTitleIsCustom(false);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto customNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetCustomTitle(frameNode, customNode);
    EXPECT_TRUE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    EXPECT_EQ(titleBarNode->GetTitle(), customNode);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomTitle002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    navDestinationNode->UpdatePrevTitleIsCustom(true);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto customNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetCustomTitle(frameNode, customNode);
    EXPECT_TRUE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomTitle003, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto customNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetTitle(customNode);
    titleBarNode->AddChild(customNode);
    navDestinationNode->UpdatePrevTitleIsCustom(true);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetCustomTitle(frameNode, customNode);
    EXPECT_EQ(titleBarNode->GetTitle(), customNode);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomTitle004, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto oldTitle = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetTitle(oldTitle);
    titleBarNode->AddChild(oldTitle);
    navDestinationNode->UpdatePrevTitleIsCustom(true);
    auto customNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetCustomTitle(frameNode, customNode);
    EXPECT_EQ(titleBarNode->GetTitle(), customNode);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomTitle005, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    EXPECT_FALSE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    auto customNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    NavDestinationModelStatic::SetCustomTitle(nullptr, customNode);
    EXPECT_FALSE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomTitle006, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetCustomTitle(frameNode, nullptr);
    EXPECT_EQ(titleBarNode->GetTitle(), nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetBackButtonIcon001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    std::vector<std::string> nameList = { "", "" };
    ImageOption imageOption;
    imageOption.noPixMap = true;
    imageOption.isValidImage = true;
    RefPtr<PixelMap> pixMap = nullptr;
    auto iconSymbol = [](WeakPtr<NG::FrameNode>) {};
    NavDestinationModelStatic::SetBackButtonIcon(frameNode, iconSymbol, TEST_IMAGE_SRC, imageOption, pixMap,
        nameList, true, TEST_ACCESSIBILITY_TEXT);
    EXPECT_EQ(titleBarLayoutProperty->GetImageSourceValue().GetSrc(), TEST_IMAGE_SRC);
    EXPECT_TRUE(titleBarLayoutProperty->GetNoPixMap());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetBackButtonIcon002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    std::vector<std::string> nameList = { "", "" };
    ImageOption imageOption;
    imageOption.noPixMap = true;
    imageOption.isValidImage = true;
    RefPtr<PixelMap> pixMap = nullptr;
    auto iconSymbol = [](WeakPtr<NG::FrameNode>) {};
    NavDestinationModelStatic::SetBackButtonIcon(frameNode, iconSymbol, TEST_IMAGE_SRC, imageOption, pixMap,
        nameList, false, "");
    EXPECT_EQ(titleBarLayoutProperty->GetImageSourceValue().GetSrc(), TEST_IMAGE_SRC);
    EXPECT_TRUE(titleBarLayoutProperty->GetNoPixMap());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetBackButtonIcon003, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    EXPECT_FALSE(titleBarLayoutProperty->HasImageSource());
    std::vector<std::string> nameList = { "", "" };
    ImageOption imageOption;
    RefPtr<PixelMap> pixMap = nullptr;
    NavDestinationModelStatic::SetBackButtonIcon(nullptr, nullptr, TEST_IMAGE_SRC, imageOption, pixMap, nameList);
    EXPECT_FALSE(titleBarLayoutProperty->HasImageSource());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetMenuOptions001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavigationMenuOptions opt;
    NavDestinationModelStatic::SetMenuOptions(frameNode, std::move(opt));
    auto menuOpts = navDestinationPattern->GetMenuOptions();
    EXPECT_EQ(menuOpts.mbOptions, MoreButtonOptions());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetMenuOptions002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto defaultMenuOpts = navDestinationPattern->GetMenuOptions();
    NavigationMenuOptions opt;
    NavDestinationModelStatic::SetMenuOptions(nullptr, std::move(opt));
    EXPECT_EQ(navDestinationPattern->GetMenuOptions(), defaultMenuOpts);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetTitlebarOptions001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavigationTitlebarOptions opt;
    opt.brOptions.barStyle = BarStyle::STANDARD;
    NavDestinationModelStatic::SetTitlebarOptions(frameNode, std::move(opt));
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    EXPECT_TRUE(navDestinationPattern->GetTitleBarStyle().has_value());
    EXPECT_EQ(navDestinationPattern->GetTitleBarStyle().value(), BarStyle::STANDARD);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetTitlebarOptions002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    EXPECT_FALSE(navDestinationPattern->GetTitleBarStyle().has_value());
    NavigationTitlebarOptions opt;
    NavDestinationModelStatic::SetTitlebarOptions(nullptr, std::move(opt));
    EXPECT_FALSE(navDestinationPattern->GetTitleBarStyle().has_value());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, ParseCommonTitle001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NG::NavigationTitleInfo titleInfo;
    titleInfo.hasMainTitle = false;
    titleInfo.hasSubTitle = false;
    NavDestinationModelStatic::ParseCommonTitle(frameNode, titleInfo);
    EXPECT_FALSE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, ParseCommonTitle002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    navDestinationNode->UpdatePrevTitleIsCustom(false);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NG::NavigationTitleInfo titleInfo;
    titleInfo.hasMainTitle = true;
    titleInfo.hasSubTitle = true;
    titleInfo.title = TEST_NAV_TITLE;
    titleInfo.subtitle = TEST_NAV_SUBTITLE;
    NavDestinationModelStatic::ParseCommonTitle(frameNode, titleInfo);
    EXPECT_FALSE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, ParseCommonTitle003, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    navDestinationNode->UpdatePrevTitleIsCustom(true);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto customTitleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetTitle(customTitleNode);
    titleBarNode->AddChild(customTitleNode);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NG::NavigationTitleInfo titleInfo;
    titleInfo.hasMainTitle = true;
    titleInfo.hasSubTitle = true;
    titleInfo.title = TEST_NAV_TITLE;
    titleInfo.subtitle = TEST_NAV_SUBTITLE;
    NavDestinationModelStatic::ParseCommonTitle(frameNode, titleInfo);
    EXPECT_FALSE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, ParseCommonTitle004, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    navDestinationNode->UpdatePrevTitleIsCustom(true);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto customTitleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetTitle(customTitleNode);
    titleBarNode->AddChild(customTitleNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleHeight(TEST_TITLE_HEIGHT);
    EXPECT_TRUE(titleBarLayoutProperty->HasTitleHeight());
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NG::NavigationTitleInfo titleInfo;
    titleInfo.hasMainTitle = true;
    titleInfo.hasSubTitle = true;
    titleInfo.title = TEST_NAV_TITLE;
    titleInfo.subtitle = TEST_NAV_SUBTITLE;
    NavDestinationModelStatic::ParseCommonTitle(frameNode, titleInfo);
    EXPECT_FALSE(titleBarLayoutProperty->HasTitleHeight());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetIgnoreLayoutSafeArea001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNodeWithContent();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NG::IgnoreLayoutSafeAreaOpts opts;
    opts.type = LAYOUT_SAFE_AREA_TYPE_SYSTEM;
    opts.edges = LAYOUT_SAFE_AREA_EDGE_TOP;
    NavDestinationModelStatic::SetIgnoreLayoutSafeArea(frameNode, opts);
    auto content = AceType::DynamicCast<FrameNode>(navDestinationNode->GetContentNode());
    ASSERT_NE(content, nullptr);
    auto contentLayoutProperty = content->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    EXPECT_TRUE(contentLayoutProperty->GetIgnoreLayoutSafeAreaOpts() != nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetIgnoreLayoutSafeArea002, TestSize.Level1)
{
    SetUpTestCase();
    auto otherNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(otherNode, nullptr);
    NG::IgnoreLayoutSafeAreaOpts opts;
    NavDestinationModelStatic::SetIgnoreLayoutSafeArea(AceType::RawPtr(otherNode), opts);
    auto layoutProperty = otherNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    EXPECT_EQ(layoutProperty, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetEnableStatusBar001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    std::optional<std::pair<bool, bool>> statusBar = std::make_pair(true, true);
    NavDestinationModelStatic::SetEnableStatusBar(frameNode, statusBar);
    EXPECT_TRUE(navDestinationNode->GetStatusBarConfig().has_value());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetEnableStatusBar002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    EXPECT_FALSE(navDestinationNode->GetStatusBarConfig().has_value());
    std::optional<std::pair<bool, bool>> statusBar = std::make_pair(true, true);
    NavDestinationModelStatic::SetEnableStatusBar(nullptr, statusBar);
    EXPECT_FALSE(navDestinationNode->GetStatusBarConfig().has_value());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetEnableNavigationIndicator001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetEnableNavigationIndicator(frameNode, true);
    EXPECT_TRUE(navDestinationNode->GetNavigationIndicatorConfig().has_value());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetEnableNavigationIndicator002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    EXPECT_FALSE(navDestinationNode->GetNavigationIndicatorConfig().has_value());
    NavDestinationModelStatic::SetEnableNavigationIndicator(nullptr, true);
    EXPECT_FALSE(navDestinationNode->GetNavigationIndicatorConfig().has_value());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetPreferredOrientation001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetPreferredOrientation(frameNode, Orientation::VERTICAL);
    EXPECT_TRUE(navDestinationNode->GetOrientation().has_value());
    EXPECT_EQ(navDestinationNode->GetOrientation().value(), Orientation::VERTICAL);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetPreferredOrientation002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    EXPECT_FALSE(navDestinationNode->GetOrientation().has_value());
    NavDestinationModelStatic::SetPreferredOrientation(nullptr, Orientation::VERTICAL);
    EXPECT_FALSE(navDestinationNode->GetOrientation().has_value());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetSystemBarStyle001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetSystemBarStyle(frameNode, TEST_SYSTEM_BAR_COLOR);
    EXPECT_TRUE(navDestinationPattern->GetCurrentStyle().has_value());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetSystemBarStyle002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    EXPECT_FALSE(navDestinationPattern->GetCurrentStyle().has_value());
    NavDestinationModelStatic::SetSystemBarStyle(nullptr, TEST_SYSTEM_BAR_COLOR);
    EXPECT_FALSE(navDestinationPattern->GetCurrentStyle().has_value());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnNewParam001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    bool onNewParamFired = false;
    auto onNewParam = [&onNewParamFired](const RefPtr<NavPathInfo>&) { onNewParamFired = true; };
    NavDestinationModelStatic::SetOnNewParam(frameNode, std::move(onNewParam));
    auto eventHub = navDestinationNode->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_NE(eventHub->onNewParamCallbackStatic_, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnNewParam002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto eventHub = navDestinationNode->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->onNewParamCallbackStatic_ == nullptr);
    auto onNewParam = [](const RefPtr<NavPathInfo>&) {};
    NavDestinationModelStatic::SetOnNewParam(nullptr, std::move(onNewParam));
    EXPECT_TRUE(eventHub->onNewParamCallbackStatic_ == nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnPop001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto navPathInfo = AceType::MakeRefPtr<NavPathInfo>(TEST_NAV_TITLE);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    navDestinationPattern->SetNavDestinationContext(context);
    context->SetNavPathInfo(navPathInfo);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    bool onPopFired = false;
    auto onPop = [&onPopFired](const RefPtr<NavPathInfo>&) { onPopFired = true; };
    NavDestinationModelStatic::SetOnPop(frameNode, std::move(onPop));
    EXPECT_TRUE(onPopFired);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetOnPop002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    EXPECT_EQ(navDestinationPattern->GetNavDestinationContext(), nullptr);
    NavDestinationModelStatic::SetOnPop(AceType::RawPtr(navDestinationNode), nullptr);
    EXPECT_EQ(navDestinationPattern->GetNavDestinationContext(), nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetScrollableProcessor001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto mockProcessor = AceType::MakeRefPtr<MockNavDestinationScrollableProcessor>();
    EXPECT_CALL(*mockProcessor, SetNodeId(_)).Times(1);
    EXPECT_CALL(*mockProcessor, SetNavDestinationPattern(_)).Times(1);
    auto creator = [mockProcessor]() -> RefPtr<NavDestinationScrollableProcessor> { return mockProcessor; };
    NavDestinationModelStatic::SetScrollableProcessor(navDestinationNode, creator);
    EXPECT_EQ(navDestinationPattern->GetScrollableProcessor(), mockProcessor);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetScrollableProcessor002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto existingProcessor = AceType::MakeRefPtr<MockNavDestinationScrollableProcessor>();
    navDestinationPattern->SetScrollableProcessor(existingProcessor);
    auto creator = []() -> RefPtr<NavDestinationScrollableProcessor> {
        return AceType::MakeRefPtr<MockNavDestinationScrollableProcessor>();
    };
    NavDestinationModelStatic::SetScrollableProcessor(navDestinationNode, creator);
    EXPECT_EQ(navDestinationPattern->GetScrollableProcessor(), existingProcessor);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetScrollableProcessor003, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto creator = []() -> RefPtr<NavDestinationScrollableProcessor> { return nullptr; };
    NavDestinationModelStatic::SetScrollableProcessor(navDestinationNode, creator);
    EXPECT_EQ(navDestinationPattern->GetScrollableProcessor(), nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetScrollableProcessor004, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    NavDestinationModelStatic::SetScrollableProcessor(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    EXPECT_EQ(navDestinationPattern->GetScrollableProcessor(), nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, UpdateBindingWithScrollable001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto mockProcessor = AceType::MakeRefPtr<MockNavDestinationScrollableProcessor>();
    navDestinationPattern->SetScrollableProcessor(mockProcessor);
    bool callbackFired = false;
    auto callback = [&callbackFired, &mockProcessor](const RefPtr<NG::NavDestinationScrollableProcessor>& processor) {
        callbackFired = true;
        EXPECT_EQ(processor, mockProcessor);
    };
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::UpdateBindingWithScrollable(frameNode, std::move(callback));
    EXPECT_TRUE(callbackFired);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, UpdateBindingWithScrollable002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    EXPECT_EQ(navDestinationPattern->GetScrollableProcessor(), nullptr);
    auto callback = [](const RefPtr<NG::NavDestinationScrollableProcessor>&) {};
    NavDestinationModelStatic::UpdateBindingWithScrollable(nullptr, std::move(callback));
    EXPECT_EQ(navDestinationPattern->GetScrollableProcessor(), nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetHideItemText001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navDestinationNode->GetToolBarNode());
    ASSERT_NE(toolBarNode, nullptr);
    EXPECT_FALSE(toolBarNode->IsHideItemText());
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetHideItemText(frameNode, TEST_IS_HIDE_ITEM_TEXT);
    EXPECT_TRUE(toolBarNode->IsHideItemText());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetHideItemText002, TestSize.Level1)
{
    SetUpTestCase();
    auto otherNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(otherNode, nullptr);
    NavDestinationModelStatic::SetHideItemText(AceType::RawPtr(otherNode), TEST_IS_HIDE_ITEM_TEXT);
    auto layoutProperty = otherNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    EXPECT_EQ(layoutProperty, nullptr);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetCustomToolBar001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto customNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavDestinationModelStatic::SetCustomToolBar(frameNode, customNode);
    EXPECT_TRUE(navDestinationNode->GetPrevToolBarIsCustomValue(false));
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetToolbarConfiguration001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto hub = navDestinationNode->GetEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);
    hub->SetEnabled(true);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    std::vector<NG::BarItem> toolBarItems;
    NavDestinationModelStatic::SetToolbarConfiguration(frameNode, std::move(toolBarItems));
    EXPECT_EQ(navDestinationNode->GetToolBarNodeOperation(), ChildNodeOperation::ADD);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetToolbarConfiguration002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    std::vector<NG::BarItem> toolBarItems;
    NavDestinationModelStatic::SetToolbarConfiguration(frameNode, std::move(toolBarItems));
    EXPECT_EQ(navDestinationNode->GetToolBarNodeOperation(), ChildNodeOperation::ADD);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetToolBarOptions001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    NavigationToolbarOptions opt;
    opt.brOptions.barStyle = BarStyle::STANDARD;
    NavDestinationModelStatic::SetToolBarOptions(frameNode, std::move(opt));
    EXPECT_TRUE(navDestinationPattern->GetToolBarStyle().has_value());
    EXPECT_EQ(navDestinationPattern->GetToolBarStyle().value(), BarStyle::STANDARD);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetToolBarOptions002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    EXPECT_FALSE(navDestinationPattern->GetToolBarStyle().has_value());
    NavigationToolbarOptions opt;
    NavDestinationModelStatic::SetToolBarOptions(nullptr, std::move(opt));
    EXPECT_FALSE(navDestinationPattern->GetToolBarStyle().has_value());
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetToolbarMorebuttonOptions001, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navDestinationNode->GetToolBarNode());
    ASSERT_NE(toolBarNode, nullptr);
    auto toolBarPattern = toolBarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolBarPattern, nullptr);
    auto frameNode = AceType::RawPtr(navDestinationNode);
    MoreButtonOptions opt;
    opt.bgOptions.color = TEST_BG_COLOR;
    NavDestinationModelStatic::SetToolbarMorebuttonOptions(frameNode, std::move(opt));
    auto result = toolBarPattern->GetToolbarMoreButtonOptions();
    EXPECT_TRUE(result.bgOptions.color.has_value());
    EXPECT_EQ(result.bgOptions.color.value(), TEST_BG_COLOR);
    TearDownTestCase();
}

HWTEST_F(NavDestinationModelStaticTestNg, SetToolbarMorebuttonOptions002, TestSize.Level1)
{
    SetUpTestCase();
    auto navDestinationNode = CreateNavDestinationNode();
    ASSERT_NE(navDestinationNode, nullptr);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navDestinationNode->GetToolBarNode());
    ASSERT_NE(toolBarNode, nullptr);
    auto toolBarPattern = toolBarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolBarPattern, nullptr);
    EXPECT_FALSE(toolBarPattern->GetToolbarMoreButtonOptions().bgOptions.color.has_value());
    MoreButtonOptions opt;
    opt.bgOptions.color = TEST_BG_COLOR;
    NavDestinationModelStatic::SetToolbarMorebuttonOptions(nullptr, std::move(opt));
    EXPECT_FALSE(toolBarPattern->GetToolbarMoreButtonOptions().bgOptions.color.has_value());
    TearDownTestCase();
}

} // namespace OHOS::Ace::NG