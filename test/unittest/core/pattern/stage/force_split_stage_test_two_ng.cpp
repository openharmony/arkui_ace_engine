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

#include <optional>
#include <unordered_map>
#include <unordered_set>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_application_info.h"
#include "core/components/navigation_bar/navigation_bar_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/manager/force_split/force_split_manager.h"
#include "core/components_ng/pattern/stage/page_info.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

#include "core/components_ng/pattern/stage/force_split/parallel_page_pattern.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_layout_algorithm.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_manager.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
void ResetForceSplitBehaviorConfig(const RefPtr<ForceSplitManager>& manager)
{
    if (!manager) {
        return;
    }
    manager->behaviorMode_ = ForceSplitBehaviorMode::NAVIGATION;
    manager->pagePairs_.clear();
    manager->transPages_.clear();
    manager->fullScreenPages_.clear();
}
}

class ParallelStageTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }

    void SetUp()
    {
        nextPageNodeId_ = 1;
        MockPipelineContextGetTheme();
        backupStageManager_ = MockPipelineContext::GetCurrent()->GetStageManager();
        preOrientation_ = SystemProperties::orientation_;
        SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
        preDeviceType_ = SystemProperties::deviceType_;
        SystemProperties::deviceType_ = DeviceType::TABLET;
        if (MockContainer::container_) {
            ON_CALL(*MockContainer::container_, WindowIsShow()).WillByDefault(Return(true));
        }
    }
    void TearDown()
    {
        SystemProperties::orientation_ = preOrientation_;
        SystemProperties::deviceType_ = preDeviceType_;
        auto forceSplitManager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
        ResetForceSplitBehaviorConfig(forceSplitManager);
        MockPipelineContext::GetCurrent()->stageManager_ = backupStageManager_;
    }

    void MockPipelineContextGetTheme();

    int32_t nextPageNodeId_ = 1;
    RefPtr<StageManager> backupStageManager_ = nullptr;
    DeviceOrientation preOrientation_ = DeviceOrientation::LANDSCAPE;
    DeviceType preDeviceType_ = DeviceType::UNKNOWN;
};

void ParallelStageTestTwoNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

namespace {
RefPtr<ForceSplitManager> GetForceSplitManager()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    return pipeline ? pipeline->GetForceSplitManager() : nullptr;
}

RefPtr<ParallelStageManager> CreateParallelStageManager(
    RefPtr<FrameNode>& stageNode, RefPtr<ParallelStagePattern>& stagePattern)
{
    stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), stagePattern);
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    auto context = MockPipelineContext::GetCurrent();
    if (context) {
        context->stageManager_ = stageManager;
    }
    return stageManager;
}

RefPtr<FrameNode> CreateRouterPage(
    const std::string& url, RouterPageType pageType = RouterPageType::DETAIL_PAGE,
    ForceSplitPageColumnType columnType = ForceSplitPageColumnType::NONE)
{
    auto pageInfo = AceType::MakeRefPtr<PageInfo>(ElementRegister::GetInstance()->MakeUniqueId(), url, url);
    auto pagePattern = AceType::MakeRefPtr<ParallelPagePattern>(pageInfo);
    pagePattern->SetPageType(pageType);
    pagePattern->SetColumnType(columnType);
    return FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
}

RefPtr<ParallelPagePattern> GetRouterPagePattern(const RefPtr<FrameNode>& page)
{
    return page ? page->GetPattern<ParallelPagePattern>() : nullptr;
}

void MountRouterPage(const RefPtr<FrameNode>& stageNode, const RefPtr<FrameNode>& page)
{
    ASSERT_NE(stageNode, nullptr);
    ASSERT_NE(page, nullptr);
    page->MountToParent(stageNode);
}
}

/**
 * @tc.name: FirePageHideOnPushPage_DetailNotHome001
 * @tc.desc: Test FirePageHideOnPushPage hides lastPage when lastPage != preHomePage.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPushPage_DetailNotHome001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto preHomePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto lastPage = CreateRouterPage("detail", RouterPageType::DETAIL_PAGE);
    MountRouterPage(stageNode, preHomePage);
    MountRouterPage(stageNode, lastPage);

    auto lastPattern = GetRouterPagePattern(lastPage);
    ASSERT_NE(lastPattern, nullptr);
    lastPattern->isOnShow_ = true;

    stageManager->isInStageOperation_ = true;
    stageManager->FirePageHideOnPushPage(
        RouterPageType::DETAIL_PAGE, lastPage, nullptr, preHomePage, PageTransitionType::NONE, false);
    EXPECT_FALSE(lastPattern->GetIsShow());
}

/**
 * @tc.name: FirePageHideOnPushPage_DetailIsHome001
 * @tc.desc: Test FirePageHideOnPushPage does NOT hide lastPage when lastPage == preHomePage and !fullScreen.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPushPage_DetailIsHome001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stageManager->isNewPageReplacing_ = false;

    auto preHomePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    MountRouterPage(stageNode, preHomePage);

    auto homePattern = GetRouterPagePattern(preHomePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = true;

    stageManager->isInStageOperation_ = true;
    stageManager->FirePageHideOnPushPage(
        RouterPageType::DETAIL_PAGE, preHomePage, nullptr, preHomePage, PageTransitionType::NONE, false);
    EXPECT_TRUE(homePattern->GetIsShow());
}

/**
 * @tc.name: FirePageHideOnPushPage_DetailFullScreen001
 * @tc.desc: Test FirePageHideOnPushPage hides lastPage when newPageIsFullScreenPage=true.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPushPage_DetailFullScreen001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto preHomePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    MountRouterPage(stageNode, preHomePage);

    auto homePattern = GetRouterPagePattern(preHomePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = true;

    stageManager->isInStageOperation_ = true;
    stageManager->FirePageHideOnPushPage(
        RouterPageType::DETAIL_PAGE, preHomePage, nullptr, preHomePage, PageTransitionType::NONE, true);
    EXPECT_FALSE(homePattern->GetIsShow());
}

/**
 * @tc.name: FirePageHideOnPushPage_DetailReplacingPlaceholder001
 * @tc.desc: Test FirePageHideOnPushPage hides preHomePage when replacing placeholder page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPushPage_DetailReplacingPlaceholder001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    

    auto preHomePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    MountRouterPage(stageNode, preHomePage);
    MountRouterPage(stageNode, placeholderPage);

    auto homePattern = GetRouterPagePattern(preHomePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = true;

    stageManager->isInStageOperation_ = true;
    stageManager->isNewPageReplacing_ = true;
    stageManager->FirePageHideOnPushPage(
        RouterPageType::DETAIL_PAGE, placeholderPage, nullptr, preHomePage, PageTransitionType::NONE, false);
    EXPECT_FALSE(homePattern->GetIsShow());
    
}

/**
 * @tc.name: FirePageHideOnPushPage_DetailReplacingRelated001
 * @tc.desc: Test FirePageHideOnPushPage hides preHomePage when replacing related page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPushPage_DetailReplacingRelated001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    

    auto preHomePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto relatedPage = CreateRouterPage("related", RouterPageType::RELATED_PAGE);
    MountRouterPage(stageNode, preHomePage);
    MountRouterPage(stageNode, relatedPage);

    auto homePattern = GetRouterPagePattern(preHomePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = true;

    stageManager->isInStageOperation_ = true;
    stageManager->isNewPageReplacing_ = true;
    stageManager->FirePageHideOnPushPage(
        RouterPageType::DETAIL_PAGE, relatedPage, nullptr, preHomePage, PageTransitionType::NONE, false);
    EXPECT_FALSE(homePattern->GetIsShow());
    
}

/**
 * @tc.name: FirePageHideOnPushPage_DetailReplacingIsHome001
 * @tc.desc: Test FirePageHideOnPushPage hides preHomePage when lastPage == preHomePage replacing.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPushPage_DetailReplacingIsHome001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    

    auto preHomePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    MountRouterPage(stageNode, preHomePage);

    auto homePattern = GetRouterPagePattern(preHomePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = true;

    stageManager->isInStageOperation_ = true;
    stageManager->isNewPageReplacing_ = true;
    stageManager->FirePageHideOnPushPage(
        RouterPageType::DETAIL_PAGE, preHomePage, nullptr, preHomePage, PageTransitionType::NONE, false);
    EXPECT_FALSE(homePattern->GetIsShow());
    
}

/**
 * @tc.name: FirePageHideOnPushPage_HomeWithRelated001
 * @tc.desc: Test FirePageHideOnPushPage hides preHomePage when HOME_PAGE with topRelatedOrPhPage.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPushPage_HomeWithRelated001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto preHomePage = CreateRouterPage("home1", RouterPageType::HOME_PAGE);
    auto lastPage = CreateRouterPage("detail", RouterPageType::DETAIL_PAGE);
    auto relatedPage = CreateRouterPage("related", RouterPageType::RELATED_PAGE);
    MountRouterPage(stageNode, preHomePage);
    MountRouterPage(stageNode, lastPage);
    MountRouterPage(stageNode, relatedPage);

    auto homePattern = GetRouterPagePattern(preHomePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = true;

    stageManager->isInStageOperation_ = true;
    stageManager->FirePageHideOnPushPage(
        RouterPageType::HOME_PAGE, lastPage, relatedPage, preHomePage, PageTransitionType::NONE, false);
    EXPECT_FALSE(homePattern->GetIsShow());
}

/**
 * @tc.name: FirePageHideOnPushPage_HomeWithoutRelated001
 * @tc.desc: Test FirePageHideOnPushPage hides lastPage and preHomePage when HOME_PAGE without topRelatedOrPhPage.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPushPage_HomeWithoutRelated001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto preHomePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto lastPage = CreateRouterPage("detail", RouterPageType::DETAIL_PAGE);
    MountRouterPage(stageNode, preHomePage);
    MountRouterPage(stageNode, lastPage);

    auto homePattern = GetRouterPagePattern(preHomePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = true;
    auto lastPattern = GetRouterPagePattern(lastPage);
    ASSERT_NE(lastPattern, nullptr);
    lastPattern->isOnShow_ = true;

    stageManager->isInStageOperation_ = true;
    stageManager->FirePageHideOnPushPage(
        RouterPageType::HOME_PAGE, lastPage, nullptr, preHomePage, PageTransitionType::NONE, false);
    EXPECT_FALSE(lastPattern->GetIsShow());
    EXPECT_FALSE(homePattern->GetIsShow());
}

/**
 * @tc.name: FirePageHideOnPushPage_HomeNoPreHome001
 * @tc.desc: Test FirePageHideOnPushPage only hides lastPage when no preHomePage.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPushPage_HomeNoPreHome001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto lastPage = CreateRouterPage("detail", RouterPageType::DETAIL_PAGE);
    MountRouterPage(stageNode, lastPage);

    auto lastPattern = GetRouterPagePattern(lastPage);
    ASSERT_NE(lastPattern, nullptr);
    lastPattern->isOnShow_ = true;

    stageManager->isInStageOperation_ = true;
    stageManager->FirePageHideOnPushPage(
        RouterPageType::HOME_PAGE, lastPage, nullptr, nullptr, PageTransitionType::NONE, false);
    EXPECT_FALSE(lastPattern->GetIsShow());
}

/**
 * @tc.name: FirePageShowOnPushPage_DetailPage001
 * @tc.desc: Test FirePageShowOnPushPage shows newTopPage when DETAIL_PAGE.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageShowOnPushPage_DetailPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto newTopPage = CreateRouterPage("detail", RouterPageType::DETAIL_PAGE);
    auto newTopPattern = GetRouterPagePattern(newTopPage);
    ASSERT_NE(newTopPattern, nullptr);
    newTopPattern->isOnShow_ = false;
    newTopPattern->isRenderDone_ = true;
    MountRouterPage(stageNode, newTopPage);

    stageManager->isInStageOperation_ = true;
    stageManager->FirePageShowOnPushPage(newTopPage, newTopPattern, PageTransitionType::NONE);
    EXPECT_TRUE(newTopPattern->GetIsShow());
}

/**
 * @tc.name: FirePageShowOnPushPage_HomePageReplacing001
 * @tc.desc: Test FirePageShowOnPushPage shows homePage but NOT placeholder when replacing.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageShowOnPushPage_HomePageReplacing001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto homePattern = GetRouterPagePattern(homePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = false;
    homePattern->isRenderDone_ = true;
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    stagePattern->SetPlaceholderPage(placeholderPage);
    MountRouterPage(stageNode, homePage);

    stageManager->isInStageOperation_ = true;
    stageManager->isNewPageReplacing_ = true;
    stageManager->FirePageShowOnPushPage(homePage, homePattern, PageTransitionType::NONE);
    EXPECT_TRUE(homePattern->GetIsShow());
    EXPECT_LT(stageNode->GetChildIndex(placeholderPage), 0);
}

/**
 * @tc.name: FirePageShowOnPushPage_HomePageMountPlaceholder001
 * @tc.desc: Test FirePageShowOnPushPage shows homePage AND mounts placeholder when NOT replacing.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageShowOnPushPage_HomePageMountPlaceholder001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;
    stageManager->isNewPageReplacing_ = false;
    stageManager->isInStageOperation_ = true;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto homePattern = GetRouterPagePattern(homePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = false;
    homePattern->isRenderDone_ = true;
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    auto placeholderPattern = GetRouterPagePattern(placeholderPage);
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->isRenderDone_ = true;
    placeholderPattern->isOnShow_ = false;
    stagePattern->SetPlaceholderPage(placeholderPage);
    MountRouterPage(stageNode, homePage);

    stageManager->FirePageShowOnPushPage(homePage, homePattern, PageTransitionType::NONE);
    EXPECT_TRUE(homePattern->GetIsShow());
    EXPECT_GE(stageNode->GetChildIndex(placeholderPage), 0);
    EXPECT_TRUE(placeholderPattern->GetIsShow());
}

/**
 * @tc.name: FirePageHideOnPopPage_DetailToDetail001
 * @tc.desc: Test FirePageHideOnPopPage hides preTopPage when both are DETAIL_PAGE.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPopPage_DetailToDetail001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto preTopPage = CreateRouterPage("preTop", RouterPageType::DETAIL_PAGE);
    auto newTopPage = CreateRouterPage("newTop", RouterPageType::DETAIL_PAGE);
    MountRouterPage(stageNode, preTopPage);
    MountRouterPage(stageNode, newTopPage);

    auto preTopPattern = GetRouterPagePattern(preTopPage);
    ASSERT_NE(preTopPattern, nullptr);
    preTopPattern->isOnShow_ = true;

    auto result = stageManager->isInStageOperation_ = true;
    stageManager->FirePageHideOnPopPage(
        nullptr, preTopPage, newTopPage, GetRouterPagePattern(newTopPage), PageTransitionType::NONE);
    EXPECT_TRUE(result);
    EXPECT_FALSE(preTopPattern->GetIsShow());
}

/**
 * @tc.name: FirePageHideOnPopPage_HomeToDetail001
 * @tc.desc: Test FirePageHideOnPopPage hides relatedPage and homePage when preTop is HOME_PAGE.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPopPage_HomeToDetail001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto relatedPage = CreateRouterPage("related", RouterPageType::RELATED_PAGE);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, relatedPage);

    auto homePattern = GetRouterPagePattern(homePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = true;
    auto relatedPattern = GetRouterPagePattern(relatedPage);
    ASSERT_NE(relatedPattern, nullptr);
    relatedPattern->isOnShow_ = true;

    auto result = stageManager->isInStageOperation_ = true;
    stageManager->FirePageHideOnPopPage(
        relatedPage, homePage, nullptr, nullptr, PageTransitionType::NONE);
    EXPECT_TRUE(result);
    EXPECT_FALSE(relatedPattern->GetIsShow());
    EXPECT_FALSE(homePattern->GetIsShow());
}

/**
 * @tc.name: FirePageHideOnPopPage_HomeReplacingNoRelated001
 * @tc.desc: Test FirePageHideOnPopPage hides homePage when replacing and no relatedPage passed.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPopPage_HomeReplacingNoRelated001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, placeholderPage);

    auto homePattern = GetRouterPagePattern(homePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = true;
    auto placeholderPattern = GetRouterPagePattern(placeholderPage);
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->isOnShow_ = true;

    stageManager->InvalidateRouterColumnNodes();
    auto result = stageManager->isInStageOperation_ = true;
    stageManager->FirePageHideOnPopPage(
        nullptr, homePage, nullptr, nullptr, PageTransitionType::NONE);
    EXPECT_TRUE(result);
    EXPECT_FALSE(homePattern->GetIsShow());
}

/**
 * @tc.name: FirePageShowOnPopPage_DetailToDetail001
 * @tc.desc: Test FirePageShowOnPopPage shows newTopPage when both are DETAIL_PAGE.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageShowOnPopPage_DetailToDetail001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto preTopPage = CreateRouterPage("preTop", RouterPageType::DETAIL_PAGE);
    auto newTopPage = CreateRouterPage("newTop", RouterPageType::DETAIL_PAGE);
    MountRouterPage(stageNode, preTopPage);
    MountRouterPage(stageNode, newTopPage);

    auto newTopPattern = GetRouterPagePattern(newTopPage);
    ASSERT_NE(newTopPattern, nullptr);
    newTopPattern->isOnShow_ = false;
    newTopPattern->isRenderDone_ = true;

    stageManager->isInStageOperation_ = true;
    auto result = stageManager->FirePageShowOnPopPage(
        nullptr, preTopPage, GetRouterPagePattern(preTopPage), newTopPage, newTopPattern, PageTransitionType::NONE);
    EXPECT_TRUE(result);
    EXPECT_TRUE(newTopPattern->GetIsShow());
}

/**
 * @tc.name: FirePageShowOnPopPage_DetailToHome001
 * @tc.desc: Test FirePageShowOnPopPage mounts placeholder when DETAIL_PAGE -> HOME_PAGE.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageShowOnPopPage_DetailToHome001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto preTopPage = CreateRouterPage("preTop", RouterPageType::DETAIL_PAGE);
    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    stagePattern->SetPlaceholderPage(placeholderPage);
    MountRouterPage(stageNode, preTopPage);
    MountRouterPage(stageNode, homePage);

    auto placeholderPattern = GetRouterPagePattern(placeholderPage);
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->isRenderDone_ = true;
    placeholderPattern->isOnShow_ = false;

    auto result = stageManager->isInStageOperation_ = true;
    stageManager->FirePageShowOnPopPage(
        nullptr, preTopPage, GetRouterPagePattern(preTopPage), homePage,
        GetRouterPagePattern(homePage), PageTransitionType::NONE);
    EXPECT_TRUE(result);
    EXPECT_GE(stageNode->GetChildIndex(placeholderPage), 0);
    EXPECT_TRUE(placeholderPattern->GetIsShow());
}

/**
 * @tc.name: FirePageShowOnPopPage_HomeToDetail001
 * @tc.desc: Test FirePageShowOnPopPage shows newTopPage when HOME_PAGE -> DETAIL_PAGE.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageShowOnPopPage_HomeToDetail001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto relatedPage = CreateRouterPage("related", RouterPageType::RELATED_PAGE);
    auto newTopPage = CreateRouterPage("newTop", RouterPageType::DETAIL_PAGE);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, relatedPage);
    MountRouterPage(stageNode, newTopPage);

    auto newTopPattern = GetRouterPagePattern(newTopPage);
    ASSERT_NE(newTopPattern, nullptr);
    newTopPattern->isOnShow_ = false;
    newTopPattern->isRenderDone_ = true;

    stageManager->isInStageOperation_ = true;
    auto result = stageManager->FirePageShowOnPopPage(
        relatedPage, homePage, GetRouterPagePattern(homePage), newTopPage, newTopPattern, PageTransitionType::NONE);
    EXPECT_TRUE(result);
    EXPECT_TRUE(newTopPattern->GetIsShow());
}

/**
 * @tc.name: FirePageShowOnPopPage_HomeToHome001
 * @tc.desc: Test FirePageShowOnPopPage shows homePage and mounts placeholder when HOME_PAGE -> HOME_PAGE.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageShowOnPopPage_HomeToHome001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage1 = CreateRouterPage("home1", RouterPageType::HOME_PAGE);
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    auto homePage2 = CreateRouterPage("home2", RouterPageType::HOME_PAGE);
    stagePattern->SetPlaceholderPage(placeholderPage);
    MountRouterPage(stageNode, homePage1);
    MountRouterPage(stageNode, homePage2);

    auto home2Pattern = GetRouterPagePattern(homePage2);
    ASSERT_NE(home2Pattern, nullptr);
    home2Pattern->isOnShow_ = false;
    home2Pattern->isRenderDone_ = true;
    auto placeholderPattern = GetRouterPagePattern(placeholderPage);
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->isRenderDone_ = true;
    placeholderPattern->isOnShow_ = false;

    auto result = stageManager->isInStageOperation_ = true;
    stageManager->FirePageShowOnPopPage(
        nullptr, homePage1, GetRouterPagePattern(homePage1), homePage2, home2Pattern, PageTransitionType::NONE);
    EXPECT_TRUE(result);
    EXPECT_TRUE(home2Pattern->GetIsShow());
    EXPECT_GE(stageNode->GetChildIndex(placeholderPage), 0);
    EXPECT_TRUE(placeholderPattern->GetIsShow());
}

/**
 * @tc.name: FirePageHideOnPopPageToIndex001
 * @tc.desc: Test FirePageHideOnPopPageToIndex hides pages for pop size.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnPopPageToIndex001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    auto pageC = CreateRouterPage("pageC");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);
    MountRouterPage(stageNode, pageC);

    auto pageCPattern = GetRouterPagePattern(pageC);
    ASSERT_NE(pageCPattern, nullptr);
    pageCPattern->isOnShow_ = true;
    auto pageBPattern = GetRouterPagePattern(pageB);
    ASSERT_NE(pageBPattern, nullptr);
    pageBPattern->isOnShow_ = true;

    constexpr int32_t popSize = 2;
    auto result = stageManager->isInStageOperation_ = true;
    stageManager->FirePageHideOnPopPageToIndex(popSize);
    EXPECT_TRUE(result);
    EXPECT_FALSE(pageCPattern->GetIsShow());
    EXPECT_FALSE(pageBPattern->GetIsShow());
}

/**
 * @tc.name: FirePageShowOnPopPageToIndex001
 * @tc.desc: Test FirePageShowOnPopPageToIndex shows to page when popping to detail.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageShowOnPopPageToIndex001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto toPage = CreateRouterPage("toPage");
    auto toPattern = GetRouterPagePattern(toPage);
    ASSERT_NE(toPattern, nullptr);
    toPattern->SetPageType(RouterPageType::DETAIL_PAGE);
    toPattern->isRenderDone_ = true;
    toPattern->isOnShow_ = false;
    MountRouterPage(stageNode, toPage);

    bool addRelatedOrPhPage = false;
    auto result = stageManager->isInStageOperation_ = true;
    stageManager->FirePageShowOnPopPageToIndex(
        stagePattern, toPage, addRelatedOrPhPage, PageTransitionType::NONE);
    EXPECT_TRUE(result);
    EXPECT_FALSE(addRelatedOrPhPage);
    EXPECT_TRUE(toPattern->GetIsShow());
}

/**
 * @tc.name: GetPageNumberExcludeRelatedOrPlaceHolderPage001
 * @tc.desc: Test GetPageNumberExcludeRelatedOrPlaceHolderPage counts pages excluding placeholder.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, GetPageNumberExcludeRelatedOrPlaceHolderPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, placeholderPage);

    int32_t pageNumber = 0;
    auto result = stageManager->GetPageNumberExcludeRelatedOrPlaceHolderPage(pageNumber);
    EXPECT_TRUE(result);
    EXPECT_EQ(pageNumber, 1);
}

/**
 * @tc.name: FirePageHideOnMovePageToFront001
 * @tc.desc: Test FirePageHideOnMovePageToFront hides last page when moving detail to front.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnMovePageToFront001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto lastPage = CreateRouterPage("last");
    MountRouterPage(stageNode, lastPage);
    auto lastPattern = GetRouterPagePattern(lastPage);
    ASSERT_NE(lastPattern, nullptr);
    lastPattern->isOnShow_ = true;

    stageManager->isInStageOperation_ = true;
    stageManager->FirePageHideOnMovePageToFront(RouterPageType::DETAIL_PAGE, lastPage, PageTransitionType::NONE);
    EXPECT_FALSE(lastPattern->GetIsShow());
}

/**
 * @tc.name: FirePageHideOnMovePageToFrontHomePage001
 * @tc.desc: Test FirePageHideOnMovePageToFront hides last page when moving home to front.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageHideOnMovePageToFrontHomePage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto lastPage = CreateRouterPage("last");
    MountRouterPage(stageNode, lastPage);
    auto lastPattern = GetRouterPagePattern(lastPage);
    ASSERT_NE(lastPattern, nullptr);
    lastPattern->isOnShow_ = true;

    stageManager->isInStageOperation_ = true;
    stageManager->FirePageHideOnMovePageToFront(RouterPageType::HOME_PAGE, lastPage, PageTransitionType::NONE);
    EXPECT_FALSE(lastPattern->GetIsShow());
}

/**
 * @tc.name: FirePageShowOnMovePageToFront001
 * @tc.desc: Test FirePageShowOnMovePageToFront shows new page when moving detail to front.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageShowOnMovePageToFront001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto preTopPage = CreateRouterPage("preTop");
    auto preTopPattern = GetRouterPagePattern(preTopPage);
    ASSERT_NE(preTopPattern, nullptr);
    auto newTopPage = CreateRouterPage("newTop");
    auto newTopPattern = GetRouterPagePattern(newTopPage);
    ASSERT_NE(newTopPattern, nullptr);
    newTopPattern->SetPageType(RouterPageType::DETAIL_PAGE);
    newTopPattern->isRenderDone_ = true;
    newTopPattern->isOnShow_ = false;
    MountRouterPage(stageNode, preTopPage);
    MountRouterPage(stageNode, newTopPage);

    stageManager->isInStageOperation_ = true;
    stageManager->FirePageShowOnMovePageToFront(
        preTopPage, preTopPattern, newTopPage, newTopPattern, PageTransitionType::NONE);
    EXPECT_TRUE(newTopPattern->GetIsShow());
}

/**
 * @tc.name: FirePageShowOnMovePageToFrontHomePage001
 * @tc.desc: Test FirePageShowOnMovePageToFront mounts placeholder when moving home to front.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FirePageShowOnMovePageToFrontHomePage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto preTopPage = CreateRouterPage("preTop");
    auto preTopPattern = GetRouterPagePattern(preTopPage);
    ASSERT_NE(preTopPattern, nullptr);
    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto homePattern = GetRouterPagePattern(homePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isRenderDone_ = true;
    homePattern->isOnShow_ = false;
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    auto placeholderPattern = GetRouterPagePattern(placeholderPage);
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->isRenderDone_ = true;
    placeholderPattern->isOnShow_ = false;
    stagePattern->SetPlaceholderPage(placeholderPage);
    MountRouterPage(stageNode, preTopPage);
    MountRouterPage(stageNode, homePage);

    stageManager->isInStageOperation_ = true;
    stageManager->FirePageShowOnMovePageToFront(
        preTopPage, preTopPattern, homePage, homePattern, PageTransitionType::NONE);
    EXPECT_GE(stageNode->GetChildIndex(placeholderPage), 0);
    EXPECT_TRUE(placeholderPattern->GetIsShow());
}

/**
 * @tc.name: RemoveRelatedOrPlaceHolderPageIfExist001
 * @tc.desc: Test RemoveRelatedOrPlaceHolderPageIfExist removes placeholder when needed.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, RemoveRelatedOrPlaceHolderPageIfExist001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, placeholderPage);

    RefPtr<FrameNode> removedPage;
    auto result = stageManager->RemoveRelatedOrPlaceHolderPageIfExist(removedPage, true);
    EXPECT_TRUE(result);
    EXPECT_EQ(removedPage, placeholderPage);
    EXPECT_LT(stageNode->GetChildIndex(placeholderPage), 0);
}

/**
 * @tc.name: OnHomePageDetected001
 * @tc.desc: Test OnHomePageDetected sets page type and shows home page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, OnHomePageDetected001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home");
    auto homePattern = GetRouterPagePattern(homePage);
    ASSERT_NE(homePattern, nullptr);
    MountRouterPage(stageNode, homePage);
    std::list<WeakPtr<FrameNode>> pageStack;
    pageStack.emplace_back(homePage);

    auto result = stageManager->OnHomePageDetected(homePage, pageStack);
    EXPECT_TRUE(result);
    EXPECT_EQ(homePattern->GetPageType(), RouterPageType::HOME_PAGE);
}

/**
 * @tc.name: MountAndShowRelatedOrPlaceHolderPageIfNeeded001
 * @tc.desc: Test MountAndShowRelatedOrPlaceHolderPageIfNeeded mounts and shows placeholder.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, MountAndShowRelatedOrPlaceHolderPageIfNeeded001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;
    stageManager->isInStageOperation_ = true;

    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    auto placeholderPattern = GetRouterPagePattern(placeholderPage);
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->isRenderDone_ = true;
    placeholderPattern->isOnShow_ = false;

    stageManager->MountAndShowRelatedOrPlaceHolderPageIfNeeded(placeholderPage, PageTransitionType::NONE);
    EXPECT_GE(stageNode->GetChildIndex(placeholderPage), 0);
    EXPECT_TRUE(placeholderPattern->GetIsShow());
    EXPECT_TRUE(placeholderPattern->IsPageBuildCompleted());
}

/**
 * @tc.name: ShouldCurrentPushPageToPrimary001
 * @tc.desc: Test ShouldCurrentPushPageToPrimary returns false in non-virtual stack split.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, ShouldCurrentPushPageToPrimary001, TestSize.Level1)
{
    auto forceSplitManager = GetForceSplitManager();
    ASSERT_NE(forceSplitManager, nullptr);
    ResetForceSplitBehaviorConfig(forceSplitManager);
    forceSplitManager->SetBehaviorMode(ForceSplitBehaviorMode::DISPLACE);

    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto oldPage = CreateRouterPage("old");
    MountRouterPage(stageNode, oldPage);
    auto newPage = CreateRouterPage("new");
    MountRouterPage(stageNode, newPage);

    EXPECT_FALSE(stageManager->ShouldCurrentPushPageToPrimary(oldPage, newPage));
}

/**
 * @tc.name: GetRouterVisiblePagesExcluding001
 * @tc.desc: Test GetRouterVisiblePagesExcluding excludes specified pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, GetRouterVisiblePagesExcluding001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    std::vector<RefPtr<FrameNode>> excludedPages = { pageA };
    auto visiblePages = stageManager->GetRouterVisiblePagesExcluding(excludedPages);
    EXPECT_NE(visiblePages.detail, pageA);
    EXPECT_EQ(visiblePages.detail, pageB);
}

/**
 * @tc.name: NormalizeRouterColumnsAfterStackChangeWithVisible001
 * @tc.desc: Test NormalizeRouterColumnsAfterStackChange sets column types based on visible pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, NormalizeRouterColumnsAfterStackChangeWithVisible001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto detailPage = CreateRouterPage("detail");
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, detailPage);
    stageManager->InvalidateRouterColumnNodes();

    ParallelStageManager::RouterVisiblePages afterVisible;
    afterVisible.primary = homePage;
    afterVisible.detail = detailPage;

    stageManager->NormalizeRouterColumnsAfterStackChange(afterVisible);
    auto detailPattern = GetRouterPagePattern(detailPage);
    ASSERT_NE(detailPattern, nullptr);
    EXPECT_EQ(detailPattern->GetColumnType(), ForceSplitPageColumnType::SECONDARY);
}

/**
 * @tc.name: SetRouterDividerVisible001
 * @tc.desc: Test SetRouterDividerVisible updates divider visibility.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, SetRouterDividerVisible001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    MountRouterPage(stageNode, homePage);
    stagePattern->SetHomePage(homePage);
    auto dividerNode = stagePattern->GetDividerNode();
    ASSERT_NE(dividerNode, nullptr);

    stageManager->SetRouterDividerVisible(false);
    EXPECT_EQ(dividerNode->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);

    stageManager->SetRouterDividerVisible(true);
    EXPECT_EQ(dividerNode->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: OnRouterPagesSplitFinish001
 * @tc.desc: Test OnRouterPagesSplitFinish calls finish callback for animated pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, OnRouterPagesSplitFinish001, TestSize.Level1)
{
    constexpr int32_t testAnimationId = 100;
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("detail");
    auto pattern = GetRouterPagePattern(page);
    ASSERT_NE(pattern, nullptr);
    pattern->PrepareSplitTransition(testAnimationId, PageTransitionType::ENTER_PUSH);

    std::vector<ParallelStageManager::RouterAnimatedPageInfo> animatedPages;
    ParallelStageManager::RouterAnimatedPageInfo info;
    info.page = page;
    info.transitionType = PageTransitionType::ENTER_PUSH;
    animatedPages.push_back(info);

    stageManager->OnRouterPagesSplitFinish(animatedPages, testAnimationId);
    EXPECT_FALSE(pattern->GetPageInTransition());
    EXPECT_EQ(pattern->GetSplitTransitionType(), PageTransitionType::NONE);
}

/**
 * @tc.name: ResetRouterAnimatedPages001
 * @tc.desc: Test ResetRouterAnimatedPages aborts transitions and removes pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, ResetRouterAnimatedPages001, TestSize.Level1)
{
    constexpr int32_t testAnimationId = 200;
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto exitPushPage = CreateRouterPage("exitPush");
    auto exitPushPattern = GetRouterPagePattern(exitPushPage);
    ASSERT_NE(exitPushPattern, nullptr);
    exitPushPattern->PrepareSplitTransition(testAnimationId, PageTransitionType::EXIT_PUSH);
    MountRouterPage(stageNode, exitPushPage);

    auto exitPopPage = CreateRouterPage("exitPop");
    auto exitPopPattern = GetRouterPagePattern(exitPopPage);
    ASSERT_NE(exitPopPattern, nullptr);
    exitPopPattern->PrepareSplitTransition(testAnimationId, PageTransitionType::EXIT_POP);
    MountRouterPage(stageNode, exitPopPage);

    ParallelStageManager::RouterAnimatedPageInfo info1;
    info1.page = exitPushPage;
    info1.transitionType = PageTransitionType::EXIT_PUSH;
    stageManager->routerAnimatedPages_.push_back(info1);
    ParallelStageManager::RouterAnimatedPageInfo info2;
    info2.page = exitPopPage;
    info2.transitionType = PageTransitionType::EXIT_POP;
    stageManager->routerAnimatedPages_.push_back(info2);

    stageManager->ResetRouterAnimatedPages();
    EXPECT_LT(stageNode->GetChildIndex(exitPopPage), 0);
}

/**
 * @tc.name: StartSplitPushAnimationNotAllowed001
 * @tc.desc: Test StartSplitPushAnimation returns false when move to primary not allowed.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, StartSplitPushAnimationNotAllowed001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    ParallelStageManager::RouterVisiblePages preVisible;
    preVisible.primary = pageA;
    preVisible.detail = pageB;
    ParallelStageManager::RouterVisiblePages newVisible;
    newVisible.primary = pageA;
    newVisible.detail = pageB;

    auto result = stageManager->StartSplitPushAnimation(preVisible, newVisible);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: StartSplitPopAnimationNotAllowed001
 * @tc.desc: Test StartSplitPopAnimation returns false when move to secondary not allowed.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, StartSplitPopAnimationNotAllowed001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    ParallelStageManager::RouterVisiblePages preVisible;
    preVisible.primary = pageA;
    preVisible.detail = pageB;
    ParallelStageManager::RouterVisiblePages newVisible;
    newVisible.primary = pageA;
    newVisible.detail = pageB;

    auto result = stageManager->StartSplitPopAnimation(preVisible, newVisible);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FireLifecycleOnPopByVisibleDiff001
 * @tc.desc: Test FireLifecycleOnPopByVisibleDiff fires hide and show lifecycle.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FireLifecycleOnPopByVisibleDiff001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    auto pageAPattern = GetRouterPagePattern(pageA);
    ASSERT_NE(pageAPattern, nullptr);
    auto pageBPattern = GetRouterPagePattern(pageB);
    ASSERT_NE(pageBPattern, nullptr);

    ParallelStageManager::RouterVisiblePages preVisible;
    preVisible.primary = pageA;
    preVisible.detail = pageB;
    ParallelStageManager::RouterVisiblePages newVisible;
    newVisible.primary = nullptr;
    newVisible.detail = pageB;

    stageManager->isInStageOperation_ = true;
    stageManager->FireLifecycleOnPopByVisibleDiff(
        preVisible, newVisible, false, PageTransitionType::NONE, PageTransitionType::NONE);
    EXPECT_FALSE(pageAPattern->GetIsShow());
}

// Tests moved from force_split_stage_test_ng.cpp to keep file under 2000 lines

/**
 * @tc.name: OnModeChangeEmptyChildren001
 * @tc.desc: Test OnModeChange returns early when children are empty.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, OnModeChangeEmptyChildren001, TestSize.Level1)
{
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);

    stageManager->OnModeChange();
    EXPECT_EQ(stageNode->GetChildren().size(), 0);
}

/**
 * @tc.name: OnModeChangeHomePageNotLastPage001
 * @tc.desc: Test OnModeChange shows home page when homePage != lastPage in stack->split.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, OnModeChangeHomePageNotLastPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::STACK;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto detailPage = CreateRouterPage("detail");
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, detailPage);

    auto homePattern = GetRouterPagePattern(homePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = false;
    homePattern->isRenderDone_ = true;

    stagePattern->mode_ = PageMode::SPLIT;
    stageManager->OnModeChange();
    EXPECT_TRUE(stagePattern->GetIsSplit());
    EXPECT_TRUE(homePattern->GetIsShow());
}

/**
 * @tc.name: OnModeChangeHomePageIsLastPage001
 * @tc.desc: Test OnModeChange mounts placeholder when homePage == lastPage in stack->split.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, OnModeChangeHomePageIsLastPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::STACK;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    MountRouterPage(stageNode, homePage);
    stagePattern->SetHomePage(homePage);
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    auto placeholderPattern = GetRouterPagePattern(placeholderPage);
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->isRenderDone_ = true;
    placeholderPattern->isOnShow_ = false;
    stagePattern->SetPlaceholderPage(placeholderPage);

    stagePattern->mode_ = PageMode::SPLIT;
    stageManager->OnModeChange();
    EXPECT_TRUE(stagePattern->GetIsSplit());
    EXPECT_GE(stageNode->GetChildIndex(placeholderPage), 0);
    EXPECT_TRUE(placeholderPattern->GetIsShow());
}

/**
 * @tc.name: OnModeChangeSplitToStackDetailPage001
 * @tc.desc: Test OnModeChange hides home page when split->stack with detail page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, OnModeChangeSplitToStackDetailPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto detailPage = CreateRouterPage("detail");
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, detailPage);
    stagePattern->SetHomePage(homePage);

    auto homePattern = GetRouterPagePattern(homePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = true;

    stagePattern->mode_ = PageMode::STACK;
    stageManager->OnModeChange();
    EXPECT_FALSE(stagePattern->GetIsSplit());
    EXPECT_FALSE(homePattern->GetIsShow());
}

/**
 * @tc.name: OnWindowStateChangeStackShow001
 * @tc.desc: Test OnWindowStateChange calls OnShow in stack mode when show=true.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, OnWindowStateChangeStackShow001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::STACK;

    auto page = CreateRouterPage("detail");
    MountRouterPage(stageNode, page);
    auto pattern = GetRouterPagePattern(page);
    ASSERT_NE(pattern, nullptr);
    pattern->isOnShow_ = false;
    pattern->isRenderDone_ = true;

    stageManager->OnWindowStateChange(true);
    EXPECT_TRUE(pattern->GetIsShow());
}

/**
 * @tc.name: OnWindowStateChangeStackHide001
 * @tc.desc: Test OnWindowStateChange calls OnHide in stack mode when show=false.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, OnWindowStateChangeStackHide001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::STACK;

    auto page = CreateRouterPage("detail");
    MountRouterPage(stageNode, page);
    auto pattern = GetRouterPagePattern(page);
    ASSERT_NE(pattern, nullptr);
    pattern->isOnShow_ = true;

    stageManager->OnWindowStateChange(false);
    EXPECT_FALSE(pattern->GetIsShow());
}

/**
 * @tc.name: OnWindowStateChangeSplitShowHomePage001
 * @tc.desc: Test OnWindowStateChange shows home and last page in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, OnWindowStateChangeSplitShowHomePage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto detailPage = CreateRouterPage("detail");
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, detailPage);
    stagePattern->SetHomePage(homePage);

    auto homePattern = GetRouterPagePattern(homePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = false;
    homePattern->isRenderDone_ = true;
    auto detailPattern = GetRouterPagePattern(detailPage);
    ASSERT_NE(detailPattern, nullptr);
    detailPattern->isOnShow_ = false;
    detailPattern->isRenderDone_ = true;

    stageManager->OnWindowStateChange(true);
    EXPECT_TRUE(homePattern->GetIsShow());
    EXPECT_TRUE(detailPattern->GetIsShow());
}

/**
 * @tc.name: OnWindowStateChangeSplitHideHomePage001
 * @tc.desc: Test OnWindowStateChange hides home and last page in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, OnWindowStateChangeSplitHideHomePage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto detailPage = CreateRouterPage("detail");
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, detailPage);
    stagePattern->SetHomePage(homePage);

    auto homePattern = GetRouterPagePattern(homePage);
    ASSERT_NE(homePattern, nullptr);
    homePattern->isOnShow_ = true;
    auto detailPattern = GetRouterPagePattern(detailPage);
    ASSERT_NE(detailPattern, nullptr);
    detailPattern->isOnShow_ = true;

    stageManager->OnWindowStateChange(false);
    EXPECT_FALSE(detailPattern->GetIsShow());
    EXPECT_FALSE(homePattern->GetIsShow());
}

/**
 * @tc.name: PushPageNotSplitMode001
 * @tc.desc: Test PushPage uses StageManager::PushPage when not in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, PushPageNotSplitMode001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::STACK;

    auto page = CreateRouterPage("detail");
    auto result = stageManager->PushPage(page);
    EXPECT_TRUE(result);
    EXPECT_EQ(stageNode->GetChildren().size(), 1);
}

/**
 * @tc.name: PushPageNotDetailPageInSplit001
 * @tc.desc: Test PushPage returns false when page is not detail in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, PushPageNotDetailPageInSplit001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto result = stageManager->PushPage(homePage);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PushPageEmptyInSplitMode001
 * @tc.desc: Test PushPage succeeds when stage is empty in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, PushPageEmptyInSplitMode001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto detailPage = CreateRouterPage("detail");
    auto result = stageManager->PushPage(detailPage);
    EXPECT_TRUE(result);
    EXPECT_EQ(stageNode->GetChildren().size(), 1);
}

/**
 * @tc.name: PopPageNotSplitMode001
 * @tc.desc: Test PopPage uses StageManager::PopPage when not in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, PopPageNotSplitMode001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::STACK;

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    stageManager->PushPage(pageA);
    stageManager->SetSrcPage(pageB);
    stageManager->PushPage(pageB);
    EXPECT_EQ(stageNode->GetChildren().size(), 2);

    stageManager->SetSrcPage(pageB);
    auto result = stageManager->PopPage(pageB, true, false);
    EXPECT_TRUE(result);
    EXPECT_EQ(stageNode->GetChildren().size(), 1);
}

/**
 * @tc.name: PopPageEmptyInSplitMode001
 * @tc.desc: Test PopPage returns false when stage is empty in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, PopPageEmptyInSplitMode001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto page = CreateRouterPage("detail");
    auto result = stageManager->PopPage(page, true, false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PopPageToIndexNotSplitMode001
 * @tc.desc: Test PopPageToIndex uses StageManager when not in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, PopPageToIndexNotSplitMode001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::STACK;

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    auto pageC = CreateRouterPage("pageC");
    stageManager->PushPage(pageA);
    stageManager->PushPage(pageB);
    stageManager->PushPage(pageC);
    EXPECT_EQ(stageNode->GetChildren().size(), 3);

    auto result = stageManager->PopPageToIndex(1, true, false);
    EXPECT_TRUE(result);
    EXPECT_EQ(stageNode->GetChildren().size(), 2);
}

/**
 * @tc.name: PopPageToIndexEmptyInSplitMode001
 * @tc.desc: Test PopPageToIndex returns false when empty in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, PopPageToIndexEmptyInSplitMode001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto result = stageManager->PopPageToIndex(0, true, false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CleanPageStackNotSplitMode001
 * @tc.desc: Test CleanPageStack uses StageManager when not in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, CleanPageStackNotSplitMode001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::STACK;

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    stageManager->PushPage(pageA);
    stageManager->PushPage(pageB);
    EXPECT_EQ(stageNode->GetChildren().size(), 2);

    auto result = stageManager->CleanPageStack();
    EXPECT_TRUE(result);
    EXPECT_EQ(stageNode->GetChildren().size(), 1);
}

/**
 * @tc.name: MovePageToFrontNotSplitMode001
 * @tc.desc: Test MovePageToFront uses StageManager when not in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, MovePageToFrontNotSplitMode001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::STACK;

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    stageManager->PushPage(pageA);
    stageManager->PushPage(pageB);

    auto result = stageManager->MovePageToFront(pageA);
    EXPECT_TRUE(result);
    EXPECT_EQ(stageManager->GetLastPage(), pageA);
}

/**
 * @tc.name: MovePageToFrontEmptyInSplitMode001
 * @tc.desc: Test MovePageToFront returns false when empty in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, MovePageToFrontEmptyInSplitMode001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto page = CreateRouterPage("detail");
    auto result = stageManager->MovePageToFront(page);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MovePageToFrontNotHomePageOrDetail001
 * @tc.desc: Test MovePageToFront returns false when page is not home or detail.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, MovePageToFrontNotHomePageOrDetail001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, placeholderPage);

    auto result = stageManager->MovePageToFront(placeholderPage);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MovePageToFrontIsLastPage001
 * @tc.desc: Test MovePageToFront returns true when page is already last page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, MovePageToFrontIsLastPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto detailPage = CreateRouterPage("detail");
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, detailPage);

    auto result = stageManager->MovePageToFront(detailPage);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FireRouterHideByVisibleDiff001
 * @tc.desc: Test FireRouterHideByVisibleDiff hides primary page when it's not in newVisiblePages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FireRouterHideByVisibleDiff001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    auto pageAPattern = GetRouterPagePattern(pageA);
    ASSERT_NE(pageAPattern, nullptr);
    pageAPattern->isOnShow_ = true;
    auto pageBPattern = GetRouterPagePattern(pageB);
    ASSERT_NE(pageBPattern, nullptr);
    pageBPattern->isOnShow_ = true;

    ParallelStageManager::RouterVisiblePages preVisible;
    preVisible.primary = pageA;
    preVisible.detail = pageB;
    ParallelStageManager::RouterVisiblePages newVisible;
    newVisible.primary = nullptr;
    newVisible.detail = pageB;

    stageManager->isInStageOperation_ = true;
    stageManager->FireRouterHideByVisibleDiff(preVisible, newVisible, PageTransitionType::NONE);
    EXPECT_FALSE(pageAPattern->GetIsShow());
    EXPECT_TRUE(pageBPattern->GetIsShow());
}

/**
 * @tc.name: FireRouterHideByVisibleDiff_HideDetail001
 * @tc.desc: Test FireRouterHideByVisibleDiff hides detail page when it's not in newVisiblePages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FireRouterHideByVisibleDiff_HideDetail001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    auto pageAPattern = GetRouterPagePattern(pageA);
    ASSERT_NE(pageAPattern, nullptr);
    pageAPattern->isOnShow_ = true;
    auto pageBPattern = GetRouterPagePattern(pageB);
    ASSERT_NE(pageBPattern, nullptr);
    pageBPattern->isOnShow_ = true;

    ParallelStageManager::RouterVisiblePages preVisible;
    preVisible.primary = pageA;
    preVisible.detail = pageB;
    ParallelStageManager::RouterVisiblePages newVisible;
    newVisible.primary = pageA;
    newVisible.detail = nullptr;

    stageManager->isInStageOperation_ = true;
    stageManager->FireRouterHideByVisibleDiff(preVisible, newVisible, PageTransitionType::NONE);
    EXPECT_TRUE(pageAPattern->GetIsShow());
    EXPECT_FALSE(pageBPattern->GetIsShow());
}

/**
 * @tc.name: FireRouterHideByVisibleDiff_HideBoth001
 * @tc.desc: Test FireRouterHideByVisibleDiff hides both pages when neither is in newVisiblePages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FireRouterHideByVisibleDiff_HideBoth001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    auto pageC = CreateRouterPage("pageC");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);
    MountRouterPage(stageNode, pageC);

    auto pageAPattern = GetRouterPagePattern(pageA);
    ASSERT_NE(pageAPattern, nullptr);
    pageAPattern->isOnShow_ = true;
    auto pageBPattern = GetRouterPagePattern(pageB);
    ASSERT_NE(pageBPattern, nullptr);
    pageBPattern->isOnShow_ = true;

    ParallelStageManager::RouterVisiblePages preVisible;
    preVisible.primary = pageA;
    preVisible.detail = pageB;
    ParallelStageManager::RouterVisiblePages newVisible;
    newVisible.primary = pageC;
    newVisible.detail = pageC;

    stageManager->isInStageOperation_ = true;
    stageManager->FireRouterHideByVisibleDiff(preVisible, newVisible, PageTransitionType::NONE);
    EXPECT_FALSE(pageAPattern->GetIsShow());
    EXPECT_FALSE(pageBPattern->GetIsShow());
}

/**
 * @tc.name: FireRouterHideByVisibleDiff_SamePrimaryDetail001
 * @tc.desc: Test FireRouterHideByVisibleDiff skips hiding when primary == detail in preVisiblePages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FireRouterHideByVisibleDiff_SamePrimaryDetail001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    MountRouterPage(stageNode, pageA);

    auto pageAPattern = GetRouterPagePattern(pageA);
    ASSERT_NE(pageAPattern, nullptr);
    pageAPattern->isOnShow_ = true;

    ParallelStageManager::RouterVisiblePages preVisible;
    preVisible.primary = pageA;
    preVisible.detail = pageA;
    ParallelStageManager::RouterVisiblePages newVisible;
    newVisible.primary = nullptr;
    newVisible.detail = nullptr;

    stageManager->isInStageOperation_ = true;
    stageManager->FireRouterHideByVisibleDiff(preVisible, newVisible, PageTransitionType::NONE);
    EXPECT_FALSE(pageAPattern->GetIsShow());
}

/**
 * @tc.name: FireRouterHideByVisibleDiff_NoHide001
 * @tc.desc: Test FireRouterHideByVisibleDiff does NOT hide when pages still in newVisiblePages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestTwoNg, FireRouterHideByVisibleDiff_NoHide001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    auto pageAPattern = GetRouterPagePattern(pageA);
    ASSERT_NE(pageAPattern, nullptr);
    pageAPattern->isOnShow_ = true;
    auto pageBPattern = GetRouterPagePattern(pageB);
    ASSERT_NE(pageBPattern, nullptr);
    pageBPattern->isOnShow_ = true;

    ParallelStageManager::RouterVisiblePages preVisible;
    preVisible.primary = pageA;
    preVisible.detail = pageB;
    ParallelStageManager::RouterVisiblePages newVisible;
    newVisible.primary = pageA;
    newVisible.detail = pageB;

    stageManager->isInStageOperation_ = true;
    stageManager->FireRouterHideByVisibleDiff(preVisible, newVisible, PageTransitionType::NONE);
    EXPECT_TRUE(pageAPattern->GetIsShow());
    EXPECT_TRUE(pageBPattern->GetIsShow());
}
} // namespace OHOS::Ace::NG
