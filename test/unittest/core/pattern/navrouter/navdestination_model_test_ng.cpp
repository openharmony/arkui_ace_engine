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
#include "test/unittest/core/pattern/navigation/mock_navigation_stack.h"
#include "test/unittest/core/pattern/navigation/mock_navigation_route.h"

#define protected public
#define private public
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string PAGE01 = "Page01";
const std::string BUNDLE_NAME = "com.example.test";
const std::string MODULE_NAME = "entry";
}

class NavDestinationModelTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void NavDestinationModelTestNg::SetUpTestCase()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == NavigationBarTheme::TypeId()) {
            return AceType::MakeRefPtr<NavigationBarTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void NavDestinationModelTestNg::TearDownTestCase()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

class MockNavDestinationScrollableProcessor : public NavDestinationScrollableProcessor {
    DECLARE_ACE_TYPE(MockNavDestinationScrollableProcessor, NavDestinationScrollableProcessor);

    MOCK_METHOD0(UpdateBindingRelation, void());
    MOCK_METHOD1(SetNodeId, void(int32_t id));
    MOCK_METHOD1(SetNavDestinationPattern, void(WeakPtr<NavDestinationPattern> pattern));
    MOCK_METHOD0(UnbindAllScrollers, void());
};

/**
 * @tc.name: SetHideBackButton001
 * @tc.desc: Branch: if (!HasHideBackButton() || (hideBackButton != GetHideBackButtonValue())) = true
 *           Condition: !HasHideBackButton() = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetHideBackButton001, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->SetNeedResetMainTitleProperty(false);
    titleBarPattern->SetNeedResetSubTitleProperty(false);

    NavDestinationModelNG::SetHideBackButton(AceType::RawPtr(navDestinationNode), true);
    EXPECT_TRUE(titleBarPattern->shouldResetMainTitleProperty_);
    EXPECT_TRUE(titleBarPattern->shouldResetSubTitleProperty_);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetHideBackButton002
 * @tc.desc: Branch: if (!HasHideBackButton() || (hideBackButton != GetHideBackButtonValue())) = true
 *           Condition: !HasHideBackButton() = false, (hideBackButton != GetHideBackButtonValue()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetHideBackButton002, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutPropertyPtr<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    navDestinationLayoutProperty->propHideBackButton_ = false;
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->SetNeedResetMainTitleProperty(false);
    titleBarPattern->SetNeedResetSubTitleProperty(false);

    NavDestinationModelNG::SetHideBackButton(AceType::RawPtr(navDestinationNode), true);
    EXPECT_TRUE(titleBarPattern->shouldResetMainTitleProperty_);
    EXPECT_TRUE(titleBarPattern->shouldResetSubTitleProperty_);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetHideBackButton003
 * @tc.desc: Branch: if (!HasHideBackButton() || (hideBackButton != GetHideBackButtonValue())) = false
 *           Condition: !HasHideBackButton() = false, (hideBackButton != GetHideBackButtonValue()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetHideBackButton003, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationLayoutProperty = navDestinationNode->GetLayoutPropertyPtr<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    navDestinationLayoutProperty->propHideBackButton_ = false;
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->SetNeedResetMainTitleProperty(false);
    titleBarPattern->SetNeedResetSubTitleProperty(false);

    NavDestinationModelNG::SetHideBackButton(AceType::RawPtr(navDestinationNode), false);
    EXPECT_FALSE(titleBarPattern->shouldResetMainTitleProperty_);
    EXPECT_FALSE(titleBarPattern->shouldResetSubTitleProperty_);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetBackgroundColor001
 * @tc.desc: Branch: if (!isVaild) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetBackgroundColor001, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::WHITE);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->SetIsUserDefinedBgColor(false);

    navdestinationModel.SetBackgroundColor(Color::BLUE, true, nullptr);
    EXPECT_EQ(renderContext->propBackgroundColor_, Color::BLUE);
    EXPECT_TRUE(navDestinationPattern->IsUserDefinedBgColor());
    std::string BUNDLE_NAME = "com.example.test";
    std::string MODULE_NAME = "entry";
    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> bgColorResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navdestinationModel.SetBackgroundColor(Color::RED, true, bgColorResObj);
    EXPECT_EQ(renderContext->propBackgroundColor_, Color::RED);
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetBackgroundColor002
 * @tc.desc: Branch: if (!isVaild) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetBackgroundColor002, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::WHITE);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->SetIsUserDefinedBgColor(true);

    navdestinationModel.SetBackgroundColor(Color::BLUE, false, nullptr);
    EXPECT_EQ(renderContext->propBackgroundColor_, Color::WHITE);
    EXPECT_FALSE(navDestinationPattern->IsUserDefinedBgColor());
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetBackgroundColor101
 * @tc.desc: Branch: if (!isVaild) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetBackgroundColor101, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto renderContext = navDestinationNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::WHITE);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->SetIsUserDefinedBgColor(false);

    NavDestinationModelNG::SetBackgroundColor(AceType::RawPtr(navDestinationNode), Color::BLUE, true, nullptr);
    EXPECT_EQ(renderContext->propBackgroundColor_, Color::BLUE);
    EXPECT_TRUE(navDestinationPattern->IsUserDefinedBgColor());
    std::string BUNDLE_NAME = "com.example.test";
    std::string MODULE_NAME = "entry";
    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> bgColorResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    NavDestinationModelNG::SetBackgroundColor(AceType::RawPtr(navDestinationNode), Color::RED, true, bgColorResObj);
    EXPECT_EQ(renderContext->propBackgroundColor_, Color::RED);
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetBackgroundColor102
 * @tc.desc: Branch: if (!isVaild) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetBackgroundColor102, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto renderContext = navDestinationNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::WHITE);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->SetIsUserDefinedBgColor(false);

    NavDestinationModelNG::SetBackgroundColor(AceType::RawPtr(navDestinationNode), Color::BLUE, false, nullptr);
    EXPECT_EQ(renderContext->propBackgroundColor_, Color::WHITE);
    EXPECT_FALSE(navDestinationPattern->IsUserDefinedBgColor());
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: ParseCommonTitle001
 * @tc.desc: Branch: if (!titleInfo.hasSubTitle && !titleInfo.hasMainTitle) = false
 *           Condition: !titleInfo.hasSubTitle = false
 *           Branch: if (navDestinationNode->GetPrevTitleIsCustomValue(false)) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, ParseCommonTitle001, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = textNode;
    navDestinationNode->titleBarNode_ = titleBarNode;
    NavigationTitleInfo titleInfo;
    titleInfo.hasSubTitle = true;
    titleInfo.hasMainTitle = true;
    navDestinationNode->UpdatePrevTitleIsCustom(false);
    RefPtr<ResourceObject> mainResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    RefPtr<ResourceObject> subResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);

    NavDestinationModelNG::ParseCommonTitle(AceType::RawPtr(navDestinationNode), titleInfo);
    NavDestinationModelNG::ParseCommonTitle(AceType::RawPtr(navDestinationNode), mainResObj, subResObj);
    EXPECT_TRUE(navDestinationNode->propPrevTitleIsCustom_);
    EXPECT_EQ(titleBarNode->GetTitle(), textNode);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: ParseCommonTitle002
 * @tc.desc: Branch: if (!titleInfo.hasSubTitle && !titleInfo.hasMainTitle) = false
 *           Condition: !titleInfo.hasSubTitle = true, !titleInfo.hasMainTitle = false
 *           Branch: if (navDestinationNode->GetPrevTitleIsCustomValue(false)) = true
 *           Branch: if (titleBarLayoutProperty->HasTitleHeight()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, ParseCommonTitle002, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = textNode;
    navDestinationNode->titleBarNode_ = titleBarNode;
    NavigationTitleInfo titleInfo;
    titleInfo.hasSubTitle = false;
    titleInfo.hasMainTitle = true;
    navDestinationNode->UpdatePrevTitleIsCustom(true);
    RefPtr<ResourceObject> mainResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    RefPtr<ResourceObject> subResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);

    NavDestinationModelNG::ParseCommonTitle(AceType::RawPtr(navDestinationNode), titleInfo);
    NavDestinationModelNG::ParseCommonTitle(AceType::RawPtr(navDestinationNode), mainResObj, subResObj);
    EXPECT_TRUE(navDestinationNode->propPrevTitleIsCustom_);
    EXPECT_NE(titleBarNode->GetTitle(), nullptr);
    EXPECT_NE(titleBarNode->GetTitle(), textNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    EXPECT_FALSE(titleBarLayoutProperty->HasTitleHeight());
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: ParseCommonTitle003
 * @tc.desc: Branch: if (!titleInfo.hasSubTitle && !titleInfo.hasMainTitle) = false
 *           Condition: !titleInfo.hasSubTitle = true, !titleInfo.hasMainTitle = false
 *           Branch: if (navDestinationNode->GetPrevTitleIsCustomValue(false)) = true
 *           Branch: if (titleBarLayoutProperty->HasTitleHeight()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, ParseCommonTitle003, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = textNode;
    navDestinationNode->titleBarNode_ = titleBarNode;
    NavigationTitleInfo titleInfo;
    titleInfo.hasSubTitle = false;
    titleInfo.hasMainTitle = true;
    navDestinationNode->UpdatePrevTitleIsCustom(true);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    Dimension titleHeight = 40.0_vp;
    titleBarLayoutProperty->UpdateTitleHeight(titleHeight);
    RefPtr<ResourceObject> mainResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    RefPtr<ResourceObject> subResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);

    NavDestinationModelNG::ParseCommonTitle(AceType::RawPtr(navDestinationNode), titleInfo);
    NavDestinationModelNG::ParseCommonTitle(AceType::RawPtr(navDestinationNode), mainResObj, subResObj);
    EXPECT_TRUE(navDestinationNode->propPrevTitleIsCustom_);
    EXPECT_NE(titleBarNode->GetTitle(), nullptr);
    EXPECT_NE(titleBarNode->GetTitle(), textNode);
    EXPECT_FALSE(titleBarLayoutProperty->HasTitleHeight());
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: ParseCommonTitle004
 * @tc.desc: Branch: if (!titleInfo.hasSubTitle && !titleInfo.hasMainTitle) = true
 *           Condition: !titleInfo.hasSubTitle = true, !titleInfo.hasMainTitle = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, ParseCommonTitle004, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = textNode;
    navDestinationNode->titleBarNode_ = titleBarNode;
    NavigationTitleInfo titleInfo;
    titleInfo.hasSubTitle = false;
    titleInfo.hasMainTitle = false;
    navDestinationNode->UpdatePrevTitleIsCustom(true);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    Dimension titleHeight = 40.0_vp;
    titleBarLayoutProperty->UpdateTitleHeight(titleHeight);
    RefPtr<ResourceObject> mainResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    RefPtr<ResourceObject> subResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);

    NavDestinationModelNG::ParseCommonTitle(AceType::RawPtr(navDestinationNode), titleInfo);
    NavDestinationModelNG::ParseCommonTitle(AceType::RawPtr(navDestinationNode), mainResObj, subResObj);
    EXPECT_TRUE(navDestinationNode->propPrevTitleIsCustom_);
    EXPECT_EQ(titleBarNode->GetTitle(), textNode);
    EXPECT_EQ(titleBarLayoutProperty->GetTitleHeight(), titleHeight);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMenuItems001
 * @tc.desc: Branch: if (navDestinationGroupNode->GetPrevMenuIsCustom().value_or(false)) = false
 *           Branch: if (navDestinationGroupNode->GetMenu()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetMenuItems001, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    navDestinationNode->UpdatePrevMenuIsCustom(false);
    navDestinationNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);

    NavDestinationModelNG::SetMenuItems(AceType::RawPtr(navDestinationNode), std::move(menuItems));
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::ADD);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    std::vector<NG::BarItem> titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    EXPECT_EQ(titleBarMenuItems.at(0).icon, "Add");
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMenuItems002
 * @tc.desc: Branch: if (navDestinationGroupNode->GetPrevMenuIsCustom().value_or(false)) = false
 *           Branch: if (navDestinationGroupNode->GetMenu()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetMenuItems002, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navDestinationNode->menu_ = columnNode;
    navDestinationNode->UpdatePrevMenuIsCustom(false);
    navDestinationNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);

    NavDestinationModelNG::SetMenuItems(AceType::RawPtr(navDestinationNode), std::move(menuItems));
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::REPLACE);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    std::vector<NG::BarItem> titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    EXPECT_EQ(titleBarMenuItems.at(0).icon, "Add");
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMenuItems003
 * @tc.desc: Branch: if (navDestinationGroupNode->GetPrevMenuIsCustom().value_or(false)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetMenuItems003, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navDestinationNode->menu_ = columnNode;
    navDestinationNode->UpdatePrevMenuIsCustom(true);
    navDestinationNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);

    NavDestinationModelNG::SetMenuItems(AceType::RawPtr(navDestinationNode), std::move(menuItems));
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::REPLACE);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    std::vector<NG::BarItem> titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    EXPECT_EQ(titleBarMenuItems.at(0).icon, "Add");
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMenuItems101
 * @tc.desc: Branch: if (navDestinationGroupNode->GetPrevMenuIsCustom().value_or(false)) = false
 *           Branch: if (navDestinationGroupNode->GetMenu()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetMenuItems101, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    navDestinationNode->UpdatePrevMenuIsCustom(false);
    navDestinationNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);

    navdestinationModel.SetMenuItems(std::move(menuItems));
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::ADD);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    std::vector<NG::BarItem> titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    EXPECT_EQ(titleBarMenuItems.at(0).icon, "Add");
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMenuItems102
 * @tc.desc: Branch: if (navDestinationGroupNode->GetPrevMenuIsCustom().value_or(false)) = false
 *           Branch: if (navDestinationGroupNode->GetMenu()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetMenuItems102, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navDestinationNode->menu_ = columnNode;
    navDestinationNode->UpdatePrevMenuIsCustom(false);
    navDestinationNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);

    navdestinationModel.SetMenuItems(std::move(menuItems));
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::REPLACE);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    std::vector<NG::BarItem> titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    EXPECT_EQ(titleBarMenuItems.at(0).icon, "Add");
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMenuItems103
 * @tc.desc: Branch: if (navDestinationGroupNode->GetPrevMenuIsCustom().value_or(false)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetMenuItems103, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navDestinationNode->menu_ = columnNode;
    navDestinationNode->UpdatePrevMenuIsCustom(true);
    navDestinationNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);

    navdestinationModel.SetMenuItems(std::move(menuItems));
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::REPLACE);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    std::vector<NG::BarItem> titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    EXPECT_EQ(titleBarMenuItems.at(0).icon, "Add");
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMenuItems104
 * @tc.desc: Branch: if (!SystemProperties::ConfigChangePerform()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetMenuItems104, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navDestinationNode->menu_ = columnNode;
    navDestinationNode->UpdatePrevMenuIsCustom(true);
    navDestinationNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);
    g_isConfigChangePerform = true;

    navdestinationModel.SetMenuItems(std::move(menuItems));
    EXPECT_EQ(navDestinationNode->GetMenuNodeOperation(), ChildNodeOperation::REPLACE);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->OnColorModeChange(1);
    std::vector<NG::BarItem> titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    EXPECT_EQ(titleBarMenuItems.at(0).icon, "Add");
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMenuItemAction001
 * @tc.desc: Branch: if (menuItems.size() > index) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetMenuItemAction001, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navDestinationNode->menu_ = columnNode;
    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->SetTitleBarMenuItems(menuItems);
    int32_t addAction = 0;
    auto actionFunc = [&addAction]() {
        addAction++;
    };

    NavDestinationModelNG::SetMenuItemAction(AceType::RawPtr(navDestinationNode), std::move(actionFunc), 0);
    std::vector<NG::BarItem> titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    ASSERT_NE(titleBarMenuItems.at(0).action, nullptr);
    titleBarMenuItems.at(0).action();
    EXPECT_EQ(addAction, 1);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMenuItemAction002
 * @tc.desc: Branch: if (menuItems.size() > index) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetMenuItemAction002, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navDestinationNode->menu_ = columnNode;
    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->SetTitleBarMenuItems(menuItems);
    int32_t addAction = 0;
    auto actionFunc = [&addAction]() {
        addAction++;
    };

    NavDestinationModelNG::SetMenuItemAction(AceType::RawPtr(navDestinationNode), std::move(actionFunc), 1);
    std::vector<NG::BarItem> titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    EXPECT_EQ(titleBarMenuItems.at(0).action, nullptr);
    EXPECT_EQ(addAction, 0);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMenuItemSymbol001
 * @tc.desc: Branch: if (menuItems.size() > index) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetMenuItemSymbol001, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navDestinationNode->menu_ = columnNode;
    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->SetTitleBarMenuItems(menuItems);
    int32_t addSymbol = 0;
    auto symbolFunc = [&addSymbol](WeakPtr<NG::FrameNode> symbol) {
        addSymbol++;
    };

    NavDestinationModelNG::SetMenuItemSymbol(AceType::RawPtr(navDestinationNode), std::move(symbolFunc), 0);
    std::vector<NG::BarItem> titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    ASSERT_NE(titleBarMenuItems.at(0).iconSymbol, std::nullopt);
    titleBarMenuItems.at(0).iconSymbol.value()(nullptr);
    EXPECT_EQ(addSymbol, 1);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMenuItemSymbol002
 * @tc.desc: Branch: if (menuItems.size() > index) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetMenuItemSymbol002, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navDestinationNode->menu_ = columnNode;
    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->SetTitleBarMenuItems(menuItems);
    int32_t addSymbol = 0;
    auto symbolFunc = [&addSymbol](WeakPtr<NG::FrameNode> symbol) {
        addSymbol++;
    };

    NavDestinationModelNG::SetMenuItemSymbol(AceType::RawPtr(navDestinationNode), std::move(symbolFunc), 1);
    std::vector<NG::BarItem> titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    EXPECT_EQ(titleBarMenuItems.at(0).iconSymbol, std::nullopt);
    EXPECT_EQ(addSymbol, 0);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetScrollableProcessor001
 * @tc.desc: Branch: if (!pattern->GetScrollableProcessor()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetScrollableProcessor001, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto processor1 = AceType::MakeRefPtr<MockNavDestinationScrollableProcessor>();
    navDestinationPattern->SetScrollableProcessor(processor1);
    auto processor2 = AceType::MakeRefPtr<MockNavDestinationScrollableProcessor>();
    auto creator = [&processor2]() {
        return processor2;
    };

    navdestinationModel.SetScrollableProcessor(std::move(creator));
    EXPECT_EQ(navDestinationPattern->GetScrollableProcessor(), processor1);
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetScrollableProcessor002
 * @tc.desc: Branch: if (!pattern->GetScrollableProcessor()) = true
 *           Branch: if (processor) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetScrollableProcessor002, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->SetScrollableProcessor(nullptr);
    auto creator = []() {
        return nullptr;
    };

    navdestinationModel.SetScrollableProcessor(std::move(creator));
    EXPECT_EQ(navDestinationPattern->GetScrollableProcessor(), nullptr);
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetScrollableProcessor003
 * @tc.desc: Branch: if (!pattern->GetScrollableProcessor()) = true
 *           Branch: if (processor) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetScrollableProcessor003, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->SetScrollableProcessor(nullptr);
    auto processor1 = AceType::MakeRefPtr<MockNavDestinationScrollableProcessor>();
    auto creator = [&processor1]() {
        return processor1;
    };

    navdestinationModel.SetScrollableProcessor(std::move(creator));
    EXPECT_EQ(navDestinationPattern->GetScrollableProcessor(), processor1);
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetOnPop001
 * @tc.desc: Branch: if (!onPop) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetOnPop001, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto navDestinationContext = AceType::MakeRefPtr<NG::NavDestinationContext>();
    auto navPathInfo = AceType::MakeRefPtr<NavPathInfo>(PAGE01, false);
    navDestinationContext->SetNavPathInfo(navPathInfo);
    navDestinationPattern->SetNavDestinationContext(navDestinationContext);
    std::string popName = "";
    auto onPop = [&popName](const RefPtr<NavPathInfo>& info) {
        popName = info->GetName();
    };

    navdestinationModel.SetOnPop(std::move(onPop));
    EXPECT_EQ(popName, PAGE01);
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetOnPop002
 * @tc.desc: Branch: if (!onPop) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetOnPop002, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto navDestinationContext = AceType::MakeRefPtr<NG::NavDestinationContext>();
    auto navPathInfo = AceType::MakeRefPtr<NavPathInfo>(PAGE01, false);
    navDestinationContext->SetNavPathInfo(navPathInfo);
    navDestinationPattern->SetNavDestinationContext(navDestinationContext);
    auto onPop = nullptr;

    navdestinationModel.SetOnPop(onPop);
    EXPECT_EQ(onPop, nullptr);
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetCustomTitle001
 * @tc.desc: Branch: if (!navDestinationNode->GetPrevTitleIsCustomValue(false)) = true
 *           Branch: if (currentTitle && customTitle->GetId() == currentTitle->GetId()) = false
 *           Condition: currentTitle = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetCustomTitle001, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    navDestinationNode->UpdatePrevTitleIsCustom(false);
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(titleBarNode->layoutProperty_, nullptr);
    titleBarNode->layoutProperty_->CleanDirty();

    NavDestinationModelNG::SetCustomTitle(AceType::RawPtr(navDestinationNode), columnNode);
    EXPECT_EQ(titleBarNode->GetTitle(), columnNode);
    EXPECT_EQ(titleBarNode->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetCustomTitle002
 * @tc.desc: Branch: if (!navDestinationNode->GetPrevTitleIsCustomValue(false)) = false
 *           Branch: if (currentTitle && customTitle->GetId() == currentTitle->GetId()) = false
 *           Condition: currentTitle = true, customTitle->GetId() == currentTitle->GetId() = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetCustomTitle002, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = textNode;
    navDestinationNode->titleBarNode_ = titleBarNode;
    navDestinationNode->UpdatePrevTitleIsCustom(true);
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(titleBarNode->layoutProperty_, nullptr);
    titleBarNode->layoutProperty_->CleanDirty();

    NavDestinationModelNG::SetCustomTitle(AceType::RawPtr(navDestinationNode), columnNode);
    EXPECT_EQ(titleBarNode->GetTitle(), columnNode);
    EXPECT_EQ(titleBarNode->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetCustomTitle003
 * @tc.desc: Branch: if (!navDestinationNode->GetPrevTitleIsCustomValue(false)) = false
 *           Branch: if (currentTitle && customTitle->GetId() == currentTitle->GetId()) = true
 *           Condition: currentTitle = true, customTitle->GetId() == currentTitle->GetId() = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetCustomTitle003, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = textNode;
    navDestinationNode->titleBarNode_ = titleBarNode;
    navDestinationNode->UpdatePrevTitleIsCustom(true);
    ASSERT_NE(titleBarNode->layoutProperty_, nullptr);
    titleBarNode->layoutProperty_->CleanDirty();

    NavDestinationModelNG::SetCustomTitle(AceType::RawPtr(navDestinationNode), textNode);
    EXPECT_EQ(titleBarNode->GetTitle(), textNode);
    EXPECT_EQ(titleBarNode->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetTitleHeight001
 * @tc.desc: Branch: if (isValid) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetTitleHeight001, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = textNode;
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->UpdateTitleHeight(Dimension(20.0_vp));

    NavDestinationModelNG::SetTitleHeight(AceType::RawPtr(navDestinationNode), Dimension(25.0_vp), false);
    EXPECT_EQ(titleBarLayoutProperty->GetTitleHeight(), std::nullopt);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetTitleHeight002
 * @tc.desc: Branch: if (isValid) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetTitleHeight002, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = textNode;
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->UpdateTitleHeight(Dimension(20.0_vp));

    NavDestinationModelNG::SetTitleHeight(AceType::RawPtr(navDestinationNode), Dimension(25.0_vp), true);
    EXPECT_EQ(titleBarLayoutProperty->GetTitleHeight(), Dimension(25.0_vp));
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetTitleHeight101
 * @tc.desc: Branch: if (isValid) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetTitleHeight101, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = textNode;
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->UpdateTitleHeight(Dimension(20.0_vp));

    navdestinationModel.SetTitleHeight(Dimension(25.0_vp), false);
    EXPECT_EQ(titleBarLayoutProperty->GetTitleHeight(), std::nullopt);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navdestinationModel.SetTitleHeight(resObj, false);
    std::string titleHeightKey = "navDestination.title.customtitle";
    CalcDimension height = navdestinationModel.ParseTitleHeight(resObj);
    EXPECT_EQ(titleBarLayoutProperty->GetTitleHeight(), std::nullopt);
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetTitleHeight102
 * @tc.desc: Branch: if (isValid) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetTitleHeight102, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = textNode;
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->UpdateTitleHeight(Dimension(20.0_vp));

    navdestinationModel.SetTitleHeight(Dimension(25.0_vp), true);
    EXPECT_EQ(titleBarLayoutProperty->GetTitleHeight(), Dimension(25.0_vp));
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navdestinationModel.SetTitleHeight(resObj, true);
    std::string titleHeightKey = "navDestination.title.customtitle";
    CalcDimension height = navdestinationModel.ParseTitleHeight(resObj);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(titleHeightKey), height.ToString());
    ViewStackProcessor::GetInstance()->ClearStack();
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetOnHiddenTest001
 * @tc.desc: Branch: if frameNode valid
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetOnHiddenTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination and call SetOnHidden.
     */
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto navdestinationNode =
        AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navdestinationNode, nullptr);
    bool isCallbackCalled = false;
    NavDestinationModelNG::SetOnHidden(Referenced::RawPtr(navdestinationNode), [&isCallbackCalled]() {
        isCallbackCalled = true;
    });
    /**
     * @tc.steps: step2. verify the onHidden callback valid.
     */
    auto eventHub = navdestinationNode->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(eventHub->onHiddenEvent_, nullptr);
    ASSERT_EQ(isCallbackCalled, false);
    eventHub->onHiddenEvent_();
    ASSERT_EQ(isCallbackCalled, true);
}

/**
 * @tc.name: SetOnHiddenTest002
 * @tc.desc: Branch: if frameNode valid && callback == nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetOnHiddenTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination and call SetOnHidden.
     */
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto navdestinationNode =
        AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navdestinationNode, nullptr);
    NavDestinationModelNG::SetOnHidden(Referenced::RawPtr(navdestinationNode), nullptr);
    /**
     * @tc.steps: step2. verify the onHidden callback valid.
     */
    auto eventHub = navdestinationNode->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_EQ(eventHub->onHiddenEvent_, nullptr);
}

/**
 * @tc.name: SetOnShownTest001
 * @tc.desc: Branch: if frameNode valid
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetOnShownTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination and call SetOnShown.
     */
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto navdestinationNode =
        AceType::DynamicCast<NavDestinationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navdestinationNode, nullptr);
    bool isCallbackCalled = false;
    NavDestinationModelNG::SetOnShown(Referenced::RawPtr(navdestinationNode), [&isCallbackCalled]() {
        isCallbackCalled = true;
    });
    /**
     * @tc.steps: step2. verify the onHidden callback valid.
     */
    auto eventHub = navdestinationNode->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(eventHub->onShownEvent_, nullptr);
    ASSERT_EQ(isCallbackCalled, false);
    eventHub->onShownEvent_();
    ASSERT_EQ(isCallbackCalled, true);
}

/**
 * @tc.name: SetOnShownTest002
 * @tc.desc: Branch: if frameNode valid && callback == nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetOnShownTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination and call SetOnHidden.
     */
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto navdestinationNode =
        AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navdestinationNode, nullptr);
    NavDestinationModelNG::SetOnShown(Referenced::RawPtr(navdestinationNode), nullptr);
    /**
     * @tc.steps: step2. verify the onHidden callback valid.
     */
    auto eventHub = navdestinationNode->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_EQ(eventHub->onShownEvent_, nullptr);
}

/**
 * @tc.name: CreateEmptyTest001
 * @tc.desc: Branch: if need create empty
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, CreateEmptyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination and call SetOnShown.
     */
    NavDestinationModelNG navdestinationModel;
    auto emptyFrameNode = AceType::DynamicCast<FrameNode>(navdestinationModel.CreateEmpty());
    ASSERT_NE(emptyFrameNode, nullptr);
    auto emptyNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(emptyFrameNode);
    ASSERT_NE(emptyNavDestination, nullptr);
    const int32_t emptyNavDestinationChildrenCount = 3;
    ASSERT_EQ(static_cast<int32_t>(emptyNavDestination->GetChildren().size()), emptyNavDestinationChildrenCount);
    auto navdestinationContent = emptyNavDestination->GetContentNode();
    ASSERT_NE(navdestinationContent, nullptr);
    ASSERT_EQ(navdestinationContent->GetChildren().size(), 0);
}

/**
 * @tc.name: SetHideTitleBarTest001
 * @tc.desc: Branch: if frameNode valid
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetHideTitleBarTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination and call SetOnHidden.
     */
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto navdestinationNode =
        AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navdestinationNode, nullptr);
    auto layoutProperty = navdestinationNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_EQ(layoutProperty->GetHideTitleBar(), std::nullopt);
    ASSERT_EQ(layoutProperty->GetIsAnimatedTitleBar(), std::nullopt);
    /**
     * @tc.steps: step2. verify.
     */
    NavDestinationModelNG::SetHideTitleBar(Referenced::RawPtr(navdestinationNode), true, true);
    ASSERT_EQ(layoutProperty->GetHideTitleBarValue(), true);
    ASSERT_EQ(layoutProperty->GetIsAnimatedTitleBarValue(), true);
    NavDestinationModelNG::SetHideTitleBar(Referenced::RawPtr(navdestinationNode), false, false);
    ASSERT_EQ(layoutProperty->GetHideTitleBarValue(), false);
    ASSERT_EQ(layoutProperty->GetIsAnimatedTitleBarValue(), false);
}

/**
 * @tc.name: SetNavDestinationModeTest001
 * @tc.desc: Branch: if frameNode valid
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetNavDestinationModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination and call SetOnHidden.
     */
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto navdestinationNode =
        AceType::DynamicCast<NavDestinationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navdestinationNode, nullptr);
    ASSERT_EQ(navdestinationNode->mode_, NavDestinationMode::STANDARD);
    /**
     * @tc.steps: step2. call the function and verify the value.
     */
    NavDestinationModelNG::SetNavDestinationMode(Referenced::RawPtr(navdestinationNode), NavDestinationMode::DIALOG);
    ASSERT_EQ(navdestinationNode->mode_, NavDestinationMode::DIALOG);
    NavDestinationModelNG::SetNavDestinationMode(Referenced::RawPtr(navdestinationNode), NavDestinationMode::STANDARD);
    ASSERT_EQ(navdestinationNode->mode_, NavDestinationMode::STANDARD);
}

/**
 * @tc.name: SetRecoverableTest001
 * @tc.desc: Branch: if use static function and frameNode valid
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetRecoverableTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination and call SetOnHidden.
     */
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto navdestinationNode =
        AceType::DynamicCast<NavDestinationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navdestinationNode, nullptr);
    ASSERT_EQ(navdestinationNode->recoverable_, true);
    /**
     * @tc.steps: step2. call the function and verify the value.
     */
    NavDestinationModelNG::SetRecoverable(Referenced::RawPtr(navdestinationNode), false);
    ASSERT_EQ(navdestinationNode->recoverable_, false);
    NavDestinationModelNG::SetRecoverable(Referenced::RawPtr(navdestinationNode), true);
    ASSERT_EQ(navdestinationNode->recoverable_, true);
}

/**
 * @tc.name: SetRecoverableTest002
 * @tc.desc: Branch: if use non-static function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetRecoverableTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination and call SetOnHidden.
     */
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto navdestinationNode =
        AceType::DynamicCast<NavDestinationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navdestinationNode, nullptr);
    ASSERT_EQ(navdestinationNode->recoverable_, true);
    /**
     * @tc.steps: step2. call the function and verify the value.
     */
    navdestinationModel.SetRecoverable(false);
    ASSERT_EQ(navdestinationNode->recoverable_, false);
    navdestinationModel.SetRecoverable(true);
    ASSERT_EQ(navdestinationNode->recoverable_, true);
}

/**
 * @tc.name: CanRecoveryTest001
 * @tc.desc: Branch: if recoverable_ == true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, CanRecoveryTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination and call SetOnHidden.
     */
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto navdestinationNode =
        AceType::DynamicCast<NavDestinationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navdestinationNode, nullptr);
    ASSERT_EQ(navdestinationNode->recoverable_, true);
    /**
     * @tc.steps: step2. call the function and verify the value.
     */
    navdestinationNode->fromNavrouterAndNoRouteInfo_ = false;
    ASSERT_EQ(navdestinationNode->CanRecovery(), true);
    navdestinationNode->fromNavrouterAndNoRouteInfo_ = true;
    ASSERT_EQ(navdestinationNode->CanRecovery(), false);
}

/**
 * @tc.name: CanRecoveryTest002
 * @tc.desc: Branch: if recoverable_ == false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, CanRecoveryTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination and call SetOnHidden.
     */
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto navdestinationNode =
        AceType::DynamicCast<NavDestinationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navdestinationNode, nullptr);
    navdestinationModel.SetRecoverable(false);
    ASSERT_EQ(navdestinationNode->recoverable_, false);
    /**
     * @tc.steps: step2. call the function and verify the value.
     */
    navdestinationNode->fromNavrouterAndNoRouteInfo_ = false;
    ASSERT_EQ(navdestinationNode->CanRecovery(), false);
    navdestinationNode->fromNavrouterAndNoRouteInfo_ = true;
    ASSERT_EQ(navdestinationNode->CanRecovery(), false);
}

/**
 * @tc.name: ParseCommonTitle005
 * @tc.desc: Test ParseCommonTitle with resObj and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, ParseCommonTitle005, TestSize.Level1)
{
    NavDestinationModelTestNg::SetUpTestCase();
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = textNode;
    navDestinationNode->titleBarNode_ = titleBarNode;
    bool hasMainTitle = true;
    bool hasSubTitle = true;
    RefPtr<ResourceObject> mainResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    RefPtr<ResourceObject> subResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    bool result = navdestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, subResObj, mainResObj);
    EXPECT_TRUE(result);
    hasSubTitle = false;
    result = navdestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, subResObj, mainResObj);
    EXPECT_TRUE(result);
    hasMainTitle = false;
    result = navdestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, subResObj, mainResObj);
    EXPECT_FALSE(result);
    hasSubTitle = true;
    result = navdestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, subResObj, mainResObj);
    EXPECT_TRUE(result);
    NavDestinationModelTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateTitle001
 * @tc.desc: Test UpdateMainTitle and UpdateSubTitle with Specific frameNode.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, UpdateTitle001, TestSize.Level1)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    titleBarNode->title_ = FrameNode::CreateFrameNode("title", 101, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->subtitle_ = FrameNode::CreateFrameNode("subTitle", 102, AceType::MakeRefPtr<TextPattern>());
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    RefPtr<ResourceObject> titleResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    RefPtr<ResourceObject> subtitleResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navdestinationModel.UpdateMainTitle(titleBarNode, titleResObj);
    NavDestinationModelNG::UpdateMainTitleInfo(titleBarNode, titleResObj);
    std::string mainTitleKey = "navDestination.title.commonMainTitle";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(mainTitleKey), "");
    navdestinationModel.UpdateSubTitle(titleBarNode, subtitleResObj);
    NavDestinationModelNG::UpdateSubTitleInfo(titleBarNode, subtitleResObj);
    std::string subTitleKey = "navDestination.title.commonSubTitle";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(subTitleKey), "");
    titleBarPattern->OnColorModeChange(1);
    std::string mainTitle;
    ResourceParseUtils::ParseResString(titleResObj, mainTitle);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(mainTitleKey), mainTitle);
    std::string subTitle;
    ResourceParseUtils::ParseResString(subtitleResObj, subTitle);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(subTitleKey), subTitle);
}

/**
 * @tc.name: SetBackButtonIcon001
 * @tc.desc: Test SetBackButtonIcon with Specific frameNode.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetBackButtonIcon001, TestSize.Level1)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    bool noPixMap = true;
    RefPtr<PixelMap> pixMap = nullptr;
    std::vector<std::string> nameList;
    ImageOption imageOption;
    nameList.push_back("");
    nameList.push_back("");
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = true;
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
    };
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = onApply;
    std::string backButtonIconKey = "navDestination.backButtonIcon.icon";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), "");
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navdestinationModel.SetBackButtonIcon(iconSymbol, resObj, imageOption, pixMap, nameList);

    titleBarPattern->OnColorModeChange(1);
    std::string result;
    ResourceParseUtils::ParseResMedia(resObj, result);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), result);
}

/**
 * @tc.name: SetBackButtonIcon002
 * @tc.desc: Test SetBackButtonIconSrcAndTextRes with Specific frameNode.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetBackButtonIcon002, TestSize.Level1)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    bool noPixMap = true;
    RefPtr<PixelMap> pixMap = nullptr;
    std::vector<std::string> nameList;
    ImageOption imageOption;
    nameList.push_back("");
    nameList.push_back("");
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = true;
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
    };
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = onApply;
    std::string backButtonIconKey = "navDestination.backButtonIcon.icon";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), "");
    std::string backButtonTextKey = "navDestination.backButtonIcon.accessibilityText";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonTextKey), "");
    RefPtr<ResourceObject> backButtonIconResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    RefPtr<ResourceObject> backButtonTextResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navdestinationModel.SetBackButtonIconSrcAndTextRes(
        iconSymbol, backButtonIconResObj, imageOption, pixMap, nameList, true, backButtonTextResObj);

    titleBarPattern->OnColorModeChange(1);
    std::string icon;
    ResourceParseUtils::ParseResMedia(backButtonIconResObj, icon);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), icon);
    std::string text;
    ResourceParseUtils::ParseResString(backButtonIconResObj, text);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), text);
}

/**
 * @tc.name: SetBackButtonIcon003
 * @tc.desc: Test UpdateBackButtonIcon with Specific frameNode.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetBackButtonIcon003, TestSize.Level1)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    std::vector<std::string> nameList;
    nameList.push_back("");
    nameList.push_back("");
    std::string backButtonIconKey = "navDestination.backButtonIcon.icon";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), "");
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navdestinationModel.UpdateBackButtonIcon(nameList, titleBarNode, resObj);

    titleBarPattern->OnColorModeChange(1);
    std::string result;
    ResourceParseUtils::ParseResMedia(resObj, result);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), result);
}

/**
 * @tc.name: SetBackButtonIcon004
 * @tc.desc: Test UpdateBackButtonIconText with Specific frameNode.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetBackButtonIcon004, TestSize.Level1)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    std::string backButtonTextKey = "navDestination.backButtonIcon.accessibilityText";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonTextKey), "");
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navdestinationModel.UpdateBackButtonIconText(true, titleBarNode, resObj);

    titleBarPattern->OnColorModeChange(1);
    std::string result;
    ResourceParseUtils::ParseResString(resObj, result);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonTextKey), result);
}

/**
 * @tc.name: SetBackButtonIcon005
 * @tc.desc: Test SetBackButtonIconTextRes with Specific frameNode.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetBackButtonIcon005, TestSize.Level1)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    std::string imageSource = "src";
    bool noPixMap = true;
    RefPtr<PixelMap> pixMap = nullptr;
    std::vector<std::string> nameList;
    ImageOption imageOption;
    nameList.push_back("");
    nameList.push_back("");
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = true;
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
    };
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = onApply;
    std::string backButtonTextKey = "navDestination.backButtonIcon.accessibilityText";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonTextKey), "");
    RefPtr<ResourceObject> backButtonTextResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navdestinationModel.SetBackButtonIconTextRes(
        iconSymbol, imageSource, imageOption, pixMap, nameList, true, backButtonTextResObj);

    titleBarPattern->OnColorModeChange(1);
    std::string result;
    ResourceParseUtils::ParseResString(backButtonTextResObj, result);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonTextKey), result);
}

/**
 * @tc.name: SetBackButtonIcon006
 * @tc.desc: Test SetBackButtonIcon modifier with Specific frameNode.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetBackButtonIcon006, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    bool noPixMap = true;
    RefPtr<PixelMap> pixMap = nullptr;
    std::string backButtonIconKey = "navDestination.backButtonIcon.icon";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), "");
    RefPtr<ResourceObject> backButtonIconResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    NavDestinationModelNG::SetBackButtonIcon(frameNode, noPixMap, pixMap, backButtonIconResObj);

    titleBarPattern->OnColorModeChange(1);
    std::string result;
    ResourceParseUtils::ParseResMedia(backButtonIconResObj, result);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), result);
}

/**
 * @tc.name: ParseTitleHeight001
 * @tc.desc: Test ParseTitleHeight
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, ParseTitleHeight001, TestSize.Level1)
{
    /**
     * @tc.steps1: init
     * @tc.expected: All pointer is non-null.
     */
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    /**
     * @tc.steps: step2. call the function and verify the value.
     */
    std::string heighValue;
    std::string key = "navigation.title.customtitle";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navdestinationModel.ParseTitleHeight(resObj);
    std::string heighString = titleBarPattern->GetResCacheMapByKey(key);
    EXPECT_EQ(heighString, "");
    ResourceParseUtils::ParseResString(resObj, key);
    CalcDimension height;
    bool isValid = ResourceParseUtils::ParseResDimensionVpNG(resObj, height);
    EXPECT_EQ(isValid, false);
}

/**
 * @tc.name: SetBeforeCreateLayoutWrapperCallBack001
 * @tc.desc: Branch: if frameNode valid
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationModelTestNg, SetBeforeCreateLayoutWrapperCallBack001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination and call SetBeforeCreateLayoutWrapperCallBack.
     */
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto navdestinationNode =
        AceType::DynamicCast<NavDestinationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navdestinationNode, nullptr);
    bool isCallbackCalled = false;
    NavDestinationModelNG::SetBeforeCreateLayoutWrapperCallBack(
        Referenced::RawPtr(navdestinationNode), [&isCallbackCalled]() {
        isCallbackCalled = true;
    });
    /**
     * @tc.steps: step2. verify the BeforeCreateLayoutWrapper callback valid.
     */
    auto eventHub = navdestinationNode->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(eventHub->beforeCreateLayoutWrapper_, nullptr);
    ASSERT_EQ(isCallbackCalled, false);
    eventHub->beforeCreateLayoutWrapper_();
    ASSERT_EQ(isCallbackCalled, true);
}
} // namespace OHOS::Ace::NG