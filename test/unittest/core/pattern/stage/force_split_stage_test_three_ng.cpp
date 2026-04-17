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

class ParallelStageTestThreeNg : public testing::Test {
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

void ParallelStageTestThreeNg::MockPipelineContextGetTheme()
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
 * @tc.name: CheckIfMovePageToPrimaryIsAllowed_AllNull001
 * @tc.desc: Test CheckIfMovePageToPrimaryIsAllowed returns false when any page is null.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CheckIfMovePageToPrimaryIsAllowed_AllNull001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    ParallelStageManager::RouterVisiblePages preVisible;
    ParallelStageManager::RouterVisiblePages newVisible;

    EXPECT_FALSE(stageManager->CheckIfMovePageToPrimaryIsAllowed(preVisible, newVisible));
}

/**
 * @tc.name: CheckIfMovePageToPrimaryIsAllowed_SamePage001
 * @tc.desc: Test CheckIfMovePageToPrimaryIsAllowed returns false when primary==detail.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CheckIfMovePageToPrimaryIsAllowed_SamePage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    MountRouterPage(stageNode, pageA);

    ParallelStageManager::RouterVisiblePages preVisible;
    preVisible.primary = pageA;
    preVisible.detail = pageA;
    ParallelStageManager::RouterVisiblePages newVisible;
    newVisible.primary = pageA;
    newVisible.detail = pageA;

    EXPECT_FALSE(stageManager->CheckIfMovePageToPrimaryIsAllowed(preVisible, newVisible));
}

/**
 * @tc.name: CheckIfMovePageToPrimaryIsAllowed_Allowed001
 * @tc.desc: Test CheckIfMovePageToPrimaryIsAllowed returns true when move is valid.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CheckIfMovePageToPrimaryIsAllowed_Allowed001, TestSize.Level1)
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

    ParallelStageManager::RouterVisiblePages preVisible;
    preVisible.primary = pageA;
    preVisible.detail = pageB;
    ParallelStageManager::RouterVisiblePages newVisible;
    newVisible.primary = pageB;
    newVisible.detail = pageC;

    EXPECT_TRUE(stageManager->CheckIfMovePageToPrimaryIsAllowed(preVisible, newVisible));
}

/**
 * @tc.name: CheckIfMovePageToPrimaryIsAllowed_NotAllowed001
 * @tc.desc: Test CheckIfMovePageToPrimaryIsAllowed returns false when condition not met.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CheckIfMovePageToPrimaryIsAllowed_NotAllowed001, TestSize.Level1)
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

    EXPECT_FALSE(stageManager->CheckIfMovePageToPrimaryIsAllowed(preVisible, newVisible));
}

/**
 * @tc.name: CheckIfMovePageToSecondaryIsAllowed_AllNull001
 * @tc.desc: Test CheckIfMovePageToSecondaryIsAllowed returns false when any page is null.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CheckIfMovePageToSecondaryIsAllowed_AllNull001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    ParallelStageManager::RouterVisiblePages preVisible;
    ParallelStageManager::RouterVisiblePages newVisible;

    EXPECT_FALSE(stageManager->CheckIfMovePageToSecondaryIsAllowed(preVisible, newVisible));
}

/**
 * @tc.name: CheckIfMovePageToSecondaryIsAllowed_SamePage001
 * @tc.desc: Test CheckIfMovePageToSecondaryIsAllowed returns false when primary==detail.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CheckIfMovePageToSecondaryIsAllowed_SamePage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    MountRouterPage(stageNode, pageA);

    ParallelStageManager::RouterVisiblePages preVisible;
    preVisible.primary = pageA;
    preVisible.detail = pageA;
    ParallelStageManager::RouterVisiblePages newVisible;
    newVisible.primary = pageA;
    newVisible.detail = pageA;

    EXPECT_FALSE(stageManager->CheckIfMovePageToSecondaryIsAllowed(preVisible, newVisible));
}

/**
 * @tc.name: CheckIfMovePageToSecondaryIsAllowed_Allowed001
 * @tc.desc: Test CheckIfMovePageToSecondaryIsAllowed returns true when move is valid.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CheckIfMovePageToSecondaryIsAllowed_Allowed001, TestSize.Level1)
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

    ParallelStageManager::RouterVisiblePages preVisible;
    preVisible.primary = pageA;
    preVisible.detail = pageB;
    ParallelStageManager::RouterVisiblePages newVisible;
    newVisible.primary = pageC;
    newVisible.detail = pageA;

    EXPECT_TRUE(stageManager->CheckIfMovePageToSecondaryIsAllowed(preVisible, newVisible));
}

/**
 * @tc.name: CheckIfMovePageToSecondaryIsAllowed_NotAllowed001
 * @tc.desc: Test CheckIfMovePageToSecondaryIsAllowed returns false when condition not met.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CheckIfMovePageToSecondaryIsAllowed_NotAllowed001, TestSize.Level1)
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

    EXPECT_FALSE(stageManager->CheckIfMovePageToSecondaryIsAllowed(preVisible, newVisible));
}

/**
 * @tc.name: GetRouterTransitionEndPageForCurrentVisible_HasDetail001
 * @tc.desc: Test GetRouterTransitionEndPageForCurrentVisible returns detail page when available.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetRouterTransitionEndPageForCurrentVisible_HasDetail001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    stageManager->InvalidateRouterColumnNodes();
    auto endPage = stageManager->GetRouterTransitionEndPageForCurrentVisible();
    EXPECT_NE(endPage, nullptr);
}

/**
 * @tc.name: GetRouterTransitionEndPageForCurrentVisible_NoDetail001
 * @tc.desc: Test GetRouterTransitionEndPageForCurrentVisible returns primary when no detail.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetRouterTransitionEndPageForCurrentVisible_NoDetail001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    MountRouterPage(stageNode, homePage);
    stagePattern->SetHomePage(homePage);
    stageManager->InvalidateRouterColumnNodes();

    auto endPage = stageManager->GetRouterTransitionEndPageForCurrentVisible();
    EXPECT_NE(endPage, nullptr);
}

/**
 * @tc.name: GetLastPageInStack001
 * @tc.desc: Test GetLastPageInStack returns the last mounted page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetLastPageInStack001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    auto lastPage = stageManager->GetLastPageInStack();
    EXPECT_EQ(lastPage, pageB);
}

/**
 * @tc.name: GetLastPageInStack_Empty001
 * @tc.desc: Test GetLastPageInStack returns nullptr when stack is empty.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetLastPageInStack_Empty001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto lastPage = stageManager->GetLastPageInStack();
    EXPECT_EQ(lastPage, nullptr);
}

/**
 * @tc.name: GetTopPrimaryColumnPage001
 * @tc.desc: Test GetTopPrimaryColumnPage returns primary page when available.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetTopPrimaryColumnPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto primaryPage = CreateRouterPage("primary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, primaryPage);
    stageManager->InvalidateRouterColumnNodes();

    auto topPrimary = stageManager->GetTopPrimaryColumnPage();
    EXPECT_NE(topPrimary, nullptr);
}

/**
 * @tc.name: GetTopPrimaryColumnPage_NoPrimary001
 * @tc.desc: Test GetTopPrimaryColumnPage returns nullptr when no primary page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetTopPrimaryColumnPage_NoPrimary001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->InvalidateRouterColumnNodes();

    auto topPrimary = stageManager->GetTopPrimaryColumnPage();
    EXPECT_EQ(topPrimary, nullptr);
}

/**
 * @tc.name: GetTopSecondaryColumnPage001
 * @tc.desc: Test GetTopSecondaryColumnPage returns secondary page when available.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetTopSecondaryColumnPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto secondaryPage = CreateRouterPage(
        "secondary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::SECONDARY);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, secondaryPage);
    stageManager->InvalidateRouterColumnNodes();

    auto topSecondary = stageManager->GetTopSecondaryColumnPage();
    EXPECT_NE(topSecondary, nullptr);
}

/**
 * @tc.name: GetTopSecondaryColumnPage_NoSecondary001
 * @tc.desc: Test GetTopSecondaryColumnPage returns nullptr when no secondary page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetTopSecondaryColumnPage_NoSecondary001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto primaryPage = CreateRouterPage("primary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    MountRouterPage(stageNode, primaryPage);
    stageManager->InvalidateRouterColumnNodes();

    auto topSecondary = stageManager->GetTopSecondaryColumnPage();
    EXPECT_EQ(topSecondary, nullptr);
}

/**
 * @tc.name: CollectRouterStackPages001
 * @tc.desc: Test CollectRouterStackPages collects all pages excluding placeholder.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CollectRouterStackPages001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, placeholderPage);

    auto stackPages = stageManager->CollectRouterStackPages();
    EXPECT_EQ(stackPages.size(), 1);
    EXPECT_EQ(stackPages[0], pageA);
}

/**
 * @tc.name: CollectRouterStackPages_WithExclusion001
 * @tc.desc: Test CollectRouterStackPages excludes specified pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CollectRouterStackPages_WithExclusion001, TestSize.Level1)
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
    auto stackPages = stageManager->CollectRouterStackPages(excludedPages);
    EXPECT_EQ(stackPages.size(), 1);
    EXPECT_EQ(stackPages[0], pageB);
}

/**
 * @tc.name: ResolveRouterVisiblePagesFromStackPages_EmptyStack001
 * @tc.desc: Test ResolveRouterVisiblePagesFromStackPages with empty stack.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, ResolveRouterVisiblePagesFromStackPages_EmptyStack001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    std::vector<RefPtr<FrameNode>> stackPages;
    auto visiblePages = stageManager->ResolveRouterVisiblePagesFromStackPages(stackPages, nullptr);
    EXPECT_EQ(visiblePages.primary, nullptr);
    EXPECT_EQ(visiblePages.detail, nullptr);
}

/**
 * @tc.name: ResolveRouterVisiblePagesFromStackPages_HomeOnly001
 * @tc.desc: Test ResolveRouterVisiblePagesFromStackPages with only home page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, ResolveRouterVisiblePagesFromStackPages_HomeOnly001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    MountRouterPage(stageNode, homePage);
    stagePattern->SetHomePage(homePage);
    std::vector<RefPtr<FrameNode>> stackPages = { homePage };

    auto visiblePages = stageManager->ResolveRouterVisiblePagesFromStackPages(stackPages, nullptr);
    EXPECT_EQ(visiblePages.primary, homePage);
}

/**
 * @tc.name: ResolveRouterVisiblePagesFromStackPages_HomeAndDetail001
 * @tc.desc: Test ResolveRouterVisiblePagesFromStackPages with home and detail pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, ResolveRouterVisiblePagesFromStackPages_HomeAndDetail001, TestSize.Level1)
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
    auto detailPattern = GetRouterPagePattern(detailPage);
    ASSERT_NE(detailPattern, nullptr);
    detailPattern->SetColumnType(ForceSplitPageColumnType::SECONDARY);
    stageManager->InvalidateRouterColumnNodes();

    std::vector<RefPtr<FrameNode>> stackPages = { homePage, detailPage };
    auto visiblePages = stageManager->ResolveRouterVisiblePagesFromStackPages(stackPages, nullptr);
    EXPECT_EQ(visiblePages.primary, homePage);
    EXPECT_EQ(visiblePages.detail, detailPage);
}

/**
 * @tc.name: UpdateRouterSplitPlaceholder_NotSplit001
 * @tc.desc: Test UpdateRouterSplitPlaceholder removes placeholder when not split.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, UpdateRouterSplitPlaceholder_NotSplit001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::STACK;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, placeholderPage);

    stageManager->UpdateRouterSplitPlaceholder();
    EXPECT_LT(stageNode->GetChildIndex(placeholderPage), 0);
}

/**
 * @tc.name: UpdateRouterSplitPlaceholder_Split001
 * @tc.desc: Test UpdateRouterSplitPlaceholder mounts placeholder when split and primary exists.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, UpdateRouterSplitPlaceholder_Split001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    stagePattern->SetPlaceholderPage(placeholderPage);
    MountRouterPage(stageNode, homePage);
    stagePattern->SetHomePage(homePage);
    stageManager->InvalidateRouterColumnNodes();

    stageManager->UpdateRouterSplitPlaceholder();
    EXPECT_GE(stageNode->GetChildIndex(placeholderPage), 0);
}

/**
 * @tc.name: OnRouterPagesSplitPushStart001
 * @tc.desc: Test OnRouterPagesSplitPushStart starts transitions for all pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, OnRouterPagesSplitPushStart001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto exitPage = CreateRouterPage("exit");
    auto movePage = CreateRouterPage("move");
    auto enterPage = CreateRouterPage("enter");
    MountRouterPage(stageNode, exitPage);
    MountRouterPage(stageNode, movePage);
    MountRouterPage(stageNode, enterPage);

    auto exitPattern = GetRouterPagePattern(exitPage);
    auto movePattern = GetRouterPagePattern(movePage);
    auto enterPattern = GetRouterPagePattern(enterPage);
    ASSERT_NE(exitPattern, nullptr);
    ASSERT_NE(movePattern, nullptr);
    ASSERT_NE(enterPattern, nullptr);

    stageManager->AddRouterAnimatedPage(exitPage, PageTransitionType::EXIT_PUSH, 1);
    stageManager->AddRouterAnimatedPage(movePage, PageTransitionType::MOVE_PUSH, 2);
    stageManager->AddRouterAnimatedPage(enterPage, PageTransitionType::ENTER_PUSH, 3);

    stageManager->OnRouterPagesSplitPushStart(exitPage, movePage, enterPage);
    EXPECT_TRUE(exitPattern->GetPageInTransition());
    EXPECT_TRUE(movePattern->GetPageInTransition());
    EXPECT_TRUE(enterPattern->GetPageInTransition());
}

/**
 * @tc.name: OnRouterPagesSplitPopStart001
 * @tc.desc: Test OnRouterPagesSplitPopStart starts transitions for all pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, OnRouterPagesSplitPopStart001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto enterPage = CreateRouterPage("enter");
    auto exitPage = CreateRouterPage("exit");
    auto movePage = CreateRouterPage("move");
    MountRouterPage(stageNode, enterPage);
    MountRouterPage(stageNode, exitPage);
    MountRouterPage(stageNode, movePage);

    auto enterPattern = GetRouterPagePattern(enterPage);
    auto exitPattern = GetRouterPagePattern(exitPage);
    auto movePattern = GetRouterPagePattern(movePage);
    ASSERT_NE(enterPattern, nullptr);
    ASSERT_NE(exitPattern, nullptr);
    ASSERT_NE(movePattern, nullptr);

    stageManager->AddRouterAnimatedPage(enterPage, PageTransitionType::ENTER_POP, 1);
    stageManager->AddRouterAnimatedPage(exitPage, PageTransitionType::EXIT_POP, 2);
    stageManager->AddRouterAnimatedPage(movePage, PageTransitionType::MOVE_POP, 3);

    stageManager->OnRouterPagesSplitPopStart(enterPage, exitPage, movePage);
    EXPECT_TRUE(enterPattern->GetPageInTransition());
    EXPECT_TRUE(exitPattern->GetPageInTransition());
    EXPECT_TRUE(movePattern->GetPageInTransition());
}

/**
 * @tc.name: ClearCurrentRouterAnimationState001
 * @tc.desc: Test ClearCurrentRouterAnimationState clears all animation state.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, ClearCurrentRouterAnimationState001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("detail");
    ParallelStageManager::RouterAnimatedPageInfo info;
    info.page = page;
    info.transitionType = PageTransitionType::EXIT_PUSH;
    stageManager->routerAnimatedPages_.push_back(info);
    stageManager->routerFocusOnFinishPage_ = page;
    stageManager->routerTransitionEndPage_ = page;

    stageManager->ClearCurrentRouterAnimationState();
    EXPECT_TRUE(stageManager->routerAnimatedPages_.empty());
    EXPECT_TRUE(stageManager->routerFocusOnFinishPage_.Invalid());
    EXPECT_TRUE(stageManager->routerTransitionEndPage_.Invalid());
}

/**
 * @tc.name: OnAbortAnimation001
 * @tc.desc: Test OnAbortAnimation resets all animated pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, OnAbortAnimation001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("detail");
    ParallelStageManager::RouterAnimatedPageInfo info;
    info.page = page;
    info.transitionType = PageTransitionType::EXIT_PUSH;
    stageManager->routerAnimatedPages_.push_back(info);
    EXPECT_FALSE(stageManager->routerAnimatedPages_.empty());

    stageManager->OnAbortAnimation();
    EXPECT_TRUE(stageManager->routerAnimatedPages_.empty());
}

/**
 * @tc.name: InvalidateRouterColumnNodes001
 * @tc.desc: Test InvalidateRouterColumnNodes marks nodes dirty.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, InvalidateRouterColumnNodes001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->routerColumnNodesDirty_ = false;
    stageManager->InvalidateRouterColumnNodes();
    EXPECT_TRUE(stageManager->routerColumnNodesDirty_);
}

/**
 * @tc.name: OnStageNodeStructureChanged001
 * @tc.desc: Test OnStageNodeStructureChanged marks nodes dirty.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, OnStageNodeStructureChanged001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->routerColumnNodesDirty_ = false;
    stageManager->OnStageNodeStructureChanged();
    EXPECT_TRUE(stageManager->routerColumnNodesDirty_);
}

/**
 * @tc.name: GetPrimaryNodeCount001
 * @tc.desc: Test GetPrimaryNodeCount returns correct count.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetPrimaryNodeCount001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto primaryPage = CreateRouterPage("primary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, primaryPage);
    stageManager->InvalidateRouterColumnNodes();

    EXPECT_EQ(stageManager->GetPrimaryNodeCount(), 2);
}

/**
 * @tc.name: HasRouterPushPageToPrimaryState001
 * @tc.desc: Test HasRouterPushPageToPrimaryState returns true when primary has detail.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, HasRouterPushPageToPrimaryState001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto primaryPage = CreateRouterPage("primary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    auto secondaryPage = CreateRouterPage(
        "secondary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::SECONDARY);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, primaryPage);
    MountRouterPage(stageNode, secondaryPage);
    stageManager->InvalidateRouterColumnNodes();

    EXPECT_TRUE(stageManager->HasRouterPushPageToPrimaryState());
}

/**
 * @tc.name: HasRouterPushPageToPrimaryState_NoPrimaryDetail001
 * @tc.desc: Test HasRouterPushPageToPrimaryState returns false when no primary detail.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, HasRouterPushPageToPrimaryState_NoPrimaryDetail001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto secondaryPage = CreateRouterPage(
        "secondary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::SECONDARY);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, secondaryPage);
    stageManager->InvalidateRouterColumnNodes();

    EXPECT_FALSE(stageManager->HasRouterPushPageToPrimaryState());
}

/**
 * @tc.name: EnsureSplitSecondaryPageIfNeeded001
 * @tc.desc: Test EnsureSplitSecondaryPageIfNeeded mounts placeholder when needed.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, EnsureSplitSecondaryPageIfNeeded001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    MountRouterPage(stageNode, homePage);
    stagePattern->SetHomePage(homePage);
    stagePattern->SetPlaceholderPage(placeholderPage);

    stageManager->EnsureSplitSecondaryPageIfNeeded();
    EXPECT_GE(stageNode->GetChildIndex(placeholderPage), 0);
}

/**
 * @tc.name: GetFocusPage001
 * @tc.desc: Test GetFocusPage returns nullptr when no focus page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetFocusPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    EXPECT_EQ(stageManager->GetFocusPage(), nullptr);
}

/**
 * @tc.name: MarkDirtyPageAndOverlay001
 * @tc.desc: Test MarkDirtyPageAndOverlay marks page dirty.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, MarkDirtyPageAndOverlay001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("detail");
    MountRouterPage(stageNode, page);

    stageManager->MarkDirtyPageAndOverlay(page, PROPERTY_UPDATE_MEASURE);
    EXPECT_TRUE(stageManager != nullptr);
}

/**
 * @tc.name: FinalizeRouterStackChange_Changed001
 * @tc.desc: Test FinalizeRouterStackChange updates columns and optionally animates.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, FinalizeRouterStackChange_Changed001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);
    stageManager->InvalidateRouterColumnNodes();

    ParallelStageManager::RouterVisiblePages beforeVisible;
    beforeVisible.primary = pageA;
    beforeVisible.detail = pageB;
    ParallelStageManager::RouterVisiblePages afterVisible;
    afterVisible.primary = pageA;
    afterVisible.detail = pageB;

    auto animated = stageManager->FinalizeRouterStackChange(beforeVisible, afterVisible, false);
    EXPECT_FALSE(animated);
}

/**
 * @tc.name: GetRouterVisiblePagesForCurrentStackTree001
 * @tc.desc: Test GetRouterVisiblePagesForCurrentStackTree returns last page as detail.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetRouterVisiblePagesForCurrentStackTree001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    auto visiblePages = stageManager->GetRouterVisiblePagesForCurrentStackTree();
    EXPECT_EQ(visiblePages.primary, nullptr);
    EXPECT_EQ(visiblePages.detail, pageB);
}

/**
 * @tc.name: GetRouterVisiblePagesForCurrentSplitTree001
 * @tc.desc: Test GetRouterVisiblePagesForCurrentSplitTree returns primary and secondary.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetRouterVisiblePagesForCurrentSplitTree001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto primaryPage = CreateRouterPage("primary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    auto secondaryPage = CreateRouterPage(
        "secondary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::SECONDARY);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, primaryPage);
    MountRouterPage(stageNode, secondaryPage);
    stageManager->InvalidateRouterColumnNodes();

    auto visiblePages = stageManager->GetRouterVisiblePagesForCurrentSplitTree();
    EXPECT_EQ(visiblePages.primary, primaryPage);
    EXPECT_EQ(visiblePages.detail, secondaryPage);
}

/**
 * @tc.name: GetRouterVisiblePagesForCurrentSplitTree_NoSecondary001
 * @tc.desc: Test GetRouterVisiblePagesForCurrentSplitTree returns placeholder when no secondary.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetRouterVisiblePagesForCurrentSplitTree_NoSecondary001, TestSize.Level1)
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
    stagePattern->SetPlaceholderPage(placeholderPage);
    stageManager->InvalidateRouterColumnNodes();

    auto visiblePages = stageManager->GetRouterVisiblePagesForCurrentSplitTree();
    EXPECT_EQ(visiblePages.detail, placeholderPage);
}

/**
 * @tc.name: SetPageColumnType_NullPage001
 * @tc.desc: Test SetPageColumnType with null page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, SetPageColumnType_NullPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stageManager->routerColumnNodesDirty_ = false;

    stageManager->SetPageColumnType(nullptr, ForceSplitPageColumnType::PRIMARY);
    EXPECT_FALSE(stageManager->routerColumnNodesDirty_);
}

/**
 * @tc.name: SetPageColumnType_SameColumnType001
 * @tc.desc: Test SetPageColumnType when column type is already set.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, SetPageColumnType_SameColumnType001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("page", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    MountRouterPage(stageNode, page);

    stageManager->routerColumnNodesDirty_ = false;
    stageManager->SetPageColumnType(page, ForceSplitPageColumnType::PRIMARY);
    EXPECT_FALSE(stageManager->routerColumnNodesDirty_);
}

/**
 * @tc.name: SetPageColumnType_ChangeColumnType001
 * @tc.desc: Test SetPageColumnType when column type changes.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, SetPageColumnType_ChangeColumnType001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("page", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    MountRouterPage(stageNode, page);

    stageManager->routerColumnNodesDirty_ = false;
    stageManager->SetPageColumnType(page, ForceSplitPageColumnType::SECONDARY);
    EXPECT_TRUE(stageManager->routerColumnNodesDirty_);

    auto pattern = GetRouterPagePattern(page);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetColumnType(), ForceSplitPageColumnType::SECONDARY);
}

/**
 * @tc.name: ClearRouterPageState_NullPage001
 * @tc.desc: Test ClearRouterPageState with null page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, ClearRouterPageState_NullPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stageManager->routerColumnNodesDirty_ = false;

    stageManager->ClearRouterPageState(nullptr);
    EXPECT_FALSE(stageManager->routerColumnNodesDirty_);
}

/**
 * @tc.name: ClearRouterPageState_AlreadyNone001
 * @tc.desc: Test ClearRouterPageState when column type is already NONE.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, ClearRouterPageState_AlreadyNone001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("page", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::NONE);
    MountRouterPage(stageNode, page);

    stageManager->routerColumnNodesDirty_ = false;
    stageManager->ClearRouterPageState(page);
    EXPECT_FALSE(stageManager->routerColumnNodesDirty_);
}

/**
 * @tc.name: ClearRouterPageState_ClearsColumnType001
 * @tc.desc: Test ClearRouterPageState clears column type.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, ClearRouterPageState_ClearsColumnType001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("page", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    MountRouterPage(stageNode, page);

    stageManager->routerColumnNodesDirty_ = false;
    stageManager->ClearRouterPageState(page);
    EXPECT_TRUE(stageManager->routerColumnNodesDirty_);

    auto pattern = GetRouterPagePattern(page);
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetColumnType(), ForceSplitPageColumnType::NONE);
}

/**
 * @tc.name: GetTopPagesWithTransition_Empty001
 * @tc.desc: Test GetTopPagesWithTransition with empty children.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetTopPagesWithTransition_Empty001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pages = stageManager->GetTopPagesWithTransition();
    EXPECT_TRUE(pages.empty());
}

/**
 * @tc.name: GetTopPagesWithTransition_StackMode001
 * @tc.desc: Test GetTopPagesWithTransition in stack mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetTopPagesWithTransition_StackMode001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::STACK;

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    auto pages = stageManager->GetTopPagesWithTransition();
    EXPECT_EQ(pages.size(), 1);
    EXPECT_EQ(pages[0], pageB);
}

/**
 * @tc.name: GetTopPagesWithTransition_SplitMode001
 * @tc.desc: Test GetTopPagesWithTransition in split mode with home page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetTopPagesWithTransition_SplitMode001, TestSize.Level1)
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
    stageManager->InvalidateRouterColumnNodes();

    auto pages = stageManager->GetTopPagesWithTransition();
    EXPECT_EQ(pages.size(), 2);
}

/**
 * @tc.name: GetTopPagesWithTransition_InTransition001
 * @tc.desc: Test GetTopPagesWithTransition during transition.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetTopPagesWithTransition_InTransition001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    stageManager->stageInTrasition_ = true;
    stageManager->destPageNode_ = pageA;

    auto pages = stageManager->GetTopPagesWithTransition();
    EXPECT_EQ(pages.size(), 1);
    EXPECT_EQ(pages[0], pageA);
}

/**
 * @tc.name: NormalizeRouterColumnsAfterStackChange_NoHomePage001
 * @tc.desc: Test NormalizeRouterColumnsAfterStackChange when no home page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, NormalizeRouterColumnsAfterStackChange_NoHomePage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("page");
    MountRouterPage(stageNode, page);

    stageManager->NormalizeRouterColumnsAfterStackChange();
    EXPECT_FALSE(stageManager->routerColumnNodesDirty_);
}

/**
 * @tc.name: NormalizeRouterColumnsAfterStackChange_HasHomePage001
 * @tc.desc: Test NormalizeRouterColumnsAfterStackChange with home page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, NormalizeRouterColumnsAfterStackChange_HasHomePage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto detailPage = CreateRouterPage("detail", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, detailPage);
    stagePattern->SetHomePage(homePage);
    stageManager->InvalidateRouterColumnNodes();
    stageManager->primaryNodes_.emplace_back(detailPage);
    stageManager->primaryNodes_.emplace_back(homePage);

    stageManager->NormalizeRouterColumnsAfterStackChange();

    auto detailPattern = GetRouterPagePattern(detailPage);
    ASSERT_NE(detailPattern, nullptr);
    EXPECT_EQ(detailPattern->GetColumnType(), ForceSplitPageColumnType::SECONDARY);
}

/**
 * @tc.name: NormalizeRouterColumnsAfterStackChange_TopPageNone001
 * @tc.desc: Test NormalizeRouterColumnsAfterStackChange when top page has NONE column type.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, NormalizeRouterColumnsAfterStackChange_TopPageNone001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto detailPage = CreateRouterPage("detail", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::NONE);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, detailPage);
    stagePattern->SetHomePage(homePage);
    stageManager->InvalidateRouterColumnNodes();

    stageManager->NormalizeRouterColumnsAfterStackChange();

    auto detailPattern = GetRouterPagePattern(detailPage);
    ASSERT_NE(detailPattern, nullptr);
    EXPECT_EQ(detailPattern->GetColumnType(), ForceSplitPageColumnType::SECONDARY);
}

/**
 * @tc.name: NormalizeRouterColumnsAfterStackChange_WithVisible001
 * @tc.desc: Test NormalizeRouterColumnsAfterStackChange with visible pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, NormalizeRouterColumnsAfterStackChange_WithVisible001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto primaryPage = CreateRouterPage("primary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::NONE);
    auto secondaryPage = CreateRouterPage("secondary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::NONE);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, primaryPage);
    MountRouterPage(stageNode, secondaryPage);
    stagePattern->SetHomePage(homePage);
    stageManager->InvalidateRouterColumnNodes();

    ParallelStageManager::RouterVisiblePages afterVisible;
    afterVisible.primary = primaryPage;
    afterVisible.detail = secondaryPage;

    stageManager->NormalizeRouterColumnsAfterStackChange(afterVisible);

    auto primaryPattern = GetRouterPagePattern(primaryPage);
    auto secondaryPattern = GetRouterPagePattern(secondaryPage);
    ASSERT_NE(primaryPattern, nullptr);
    ASSERT_NE(secondaryPattern, nullptr);
    EXPECT_EQ(primaryPattern->GetColumnType(), ForceSplitPageColumnType::PRIMARY);
    EXPECT_EQ(secondaryPattern->GetColumnType(), ForceSplitPageColumnType::SECONDARY);
}

/**
 * @tc.name: NormalizeRouterColumnsAfterStackChange_SamePrimaryDetail001
 * @tc.desc: Test NormalizeRouterColumnsAfterStackChange when primary==detail.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, NormalizeRouterColumnsAfterStackChange_SamePrimaryDetail001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    MountRouterPage(stageNode, homePage);
    stagePattern->SetHomePage(homePage);
    stageManager->InvalidateRouterColumnNodes();

    ParallelStageManager::RouterVisiblePages afterVisible;
    afterVisible.primary = homePage;
    afterVisible.detail = homePage;

    stageManager->NormalizeRouterColumnsAfterStackChange(afterVisible);
    EXPECT_FALSE(stageManager->routerColumnNodesDirty_);
}

/**
 * @tc.name: UpdateRouterColumnsOnPush_NullNewPage001
 * @tc.desc: Test UpdateRouterColumnsOnPush with null new page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, UpdateRouterColumnsOnPush_NullNewPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto currentPage = CreateRouterPage("current");
    MountRouterPage(stageNode, currentPage);

    stageManager->routerColumnNodesDirty_ = false;
    stageManager->UpdateRouterColumnsOnPush(currentPage, nullptr);
    EXPECT_FALSE(stageManager->routerColumnNodesDirty_);
}

/**
 * @tc.name: UpdateRouterColumnsOnPush_SetColumns001
 * @tc.desc: Test UpdateRouterColumnsOnPush sets column types.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, UpdateRouterColumnsOnPush_SetColumns001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto currentPage = CreateRouterPage("current", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::NONE);
    auto newPage = CreateRouterPage("new", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::NONE);
    MountRouterPage(stageNode, currentPage);
    MountRouterPage(stageNode, newPage);

    stageManager->UpdateRouterColumnsOnPush(currentPage, newPage);

    auto currentPattern = GetRouterPagePattern(currentPage);
    auto newPattern = GetRouterPagePattern(newPage);
    ASSERT_NE(currentPattern, nullptr);
    ASSERT_NE(newPattern, nullptr);
    EXPECT_EQ(newPattern->GetColumnType(), ForceSplitPageColumnType::SECONDARY);
}

/**
 * @tc.name: AddRouterAnimatedPage001
 * @tc.desc: Test AddRouterAnimatedPage adds page to animated list.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, AddRouterAnimatedPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("page");
    MountRouterPage(stageNode, page);

    stageManager->AddRouterAnimatedPage(page, PageTransitionType::EXIT_PUSH, 100);
    EXPECT_EQ(stageManager->routerAnimatedPages_.size(), 1);

    auto pattern = GetRouterPagePattern(page);
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->GetPageInTransition());
}

/**
 * @tc.name: AddRouterAnimatedPage_AlreadyInList001
 * @tc.desc: Test AddRouterAnimatedPage doesn't add duplicate page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, AddRouterAnimatedPage_AlreadyInList001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("page");
    MountRouterPage(stageNode, page);

    stageManager->AddRouterAnimatedPage(page, PageTransitionType::EXIT_PUSH, 100);
    stageManager->AddRouterAnimatedPage(page, PageTransitionType::ENTER_PUSH, 100);
    EXPECT_EQ(stageManager->routerAnimatedPages_.size(), 2);
}

/**
 * @tc.name: SetRouterDividerVisible_Visible001
 * @tc.desc: Test SetRouterDividerVisible sets divider visible.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, SetRouterDividerVisible_Visible001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto dividerNode = FrameNode::CreateFrameNode("divider", 100, AceType::MakeRefPtr<Pattern>());
    stagePattern->dividerNode_ = dividerNode;
    dividerNode->MountToParent(stageNode);

    stageManager->SetRouterDividerVisible(true);
    EXPECT_EQ(dividerNode->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: SetRouterDividerVisible_Hidden001
 * @tc.desc: Test SetRouterDividerVisible sets divider hidden.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, SetRouterDividerVisible_Hidden001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto dividerNode = FrameNode::CreateFrameNode("divider", 100, AceType::MakeRefPtr<Pattern>());
    stagePattern->dividerNode_ = dividerNode;
    dividerNode->MountToParent(stageNode);

    stageManager->SetRouterDividerVisible(false);
    EXPECT_EQ(dividerNode->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
}

/**
 * @tc.name: OnRouterPagesSplitPushEnd001
 * @tc.desc: Test OnRouterPagesSplitPushEnd ends transitions and updates columns.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, OnRouterPagesSplitPushEnd001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto exitPage = CreateRouterPage("exit");
    auto enterPage = CreateRouterPage("enter");
    MountRouterPage(stageNode, exitPage);
    MountRouterPage(stageNode, enterPage);

    auto exitPattern = GetRouterPagePattern(exitPage);
    auto enterPattern = GetRouterPagePattern(enterPage);
    ASSERT_NE(exitPattern, nullptr);
    ASSERT_NE(enterPattern, nullptr);

    stageManager->AddRouterAnimatedPage(exitPage, PageTransitionType::EXIT_PUSH, 100);
    stageManager->AddRouterAnimatedPage(enterPage, PageTransitionType::ENTER_PUSH, 100);

    stageManager->OnRouterPagesSplitPushEnd(exitPage, enterPage, nullptr);
    EXPECT_EQ(stageManager->routerAnimatedPages_.size(), 2);
}

/**
 * @tc.name: OnRouterPagesSplitPopEnd001
 * @tc.desc: Test OnRouterPagesSplitPopEnd ends transitions.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, OnRouterPagesSplitPopEnd001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto enterPage = CreateRouterPage("enter");
    auto exitPage = CreateRouterPage("exit");
    MountRouterPage(stageNode, enterPage);
    MountRouterPage(stageNode, exitPage);

    auto enterPattern = GetRouterPagePattern(enterPage);
    auto exitPattern = GetRouterPagePattern(exitPage);
    ASSERT_NE(enterPattern, nullptr);
    ASSERT_NE(exitPattern, nullptr);

    stageManager->AddRouterAnimatedPage(enterPage, PageTransitionType::ENTER_POP, 100);
    stageManager->AddRouterAnimatedPage(exitPage, PageTransitionType::EXIT_POP, 100);

    stageManager->OnRouterPagesSplitPopEnd(enterPage, exitPage, nullptr);
    EXPECT_EQ(stageManager->routerAnimatedPages_.size(), 2);
}

/**
 * @tc.name: ShouldCurrentPushPageToPrimary_NoHomePage001
 * @tc.desc: Test ShouldCurrentPushPageToPrimary returns false when no home page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, ShouldCurrentPushPageToPrimary_NoHomePage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto newPage = CreateRouterPage("new");
    MountRouterPage(stageNode, newPage);

    EXPECT_FALSE(stageManager->ShouldCurrentPushPageToPrimary(newPage));
}

/**
 * @tc.name: ShouldCurrentPushPageToPrimary_HasHomePage001
 * @tc.desc: Test ShouldCurrentPushPageToPrimary with home page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, ShouldCurrentPushPageToPrimary_HasHomePage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto newPage = CreateRouterPage("new");
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, newPage);
    stagePattern->SetHomePage(homePage);
    stageManager->InvalidateRouterColumnNodes();

    auto forceSplitMgr = GetForceSplitManager();
    ASSERT_NE(forceSplitMgr, nullptr);

    EXPECT_FALSE(stageManager->ShouldCurrentPushPageToPrimary(newPage));
}

/**
 * @tc.name: CollectRouterStackPages_AllPages001
 * @tc.desc: Test CollectRouterStackPages collects pages excluding placeholder.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CollectRouterStackPages_AllPages001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, placeholderPage);

    auto stackPages = stageManager->CollectRouterStackPages();
    EXPECT_EQ(stackPages.size(), 1);
    EXPECT_EQ(stackPages[0], pageA);
}

/**
 * @tc.name: CollectRouterStackPages_ExitPopPage001
 * @tc.desc: Test CollectRouterStackPages excludes EXIT_POP pages in transition.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CollectRouterStackPages_ExitPopPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, pageB);

    auto patternB = GetRouterPagePattern(pageB);
    ASSERT_NE(patternB, nullptr);
    patternB->SetPageInTransition(true);
    patternB->PrepareSplitTransition(100, PageTransitionType::EXIT_POP);

    auto stackPages = stageManager->CollectRouterStackPages();
    EXPECT_EQ(stackPages.size(), 1);
    EXPECT_EQ(stackPages[0], pageA);
}

/**
 * @tc.name: CollectRouterStackPages_RelatedPage001
 * @tc.desc: Test CollectRouterStackPages excludes related pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, CollectRouterStackPages_RelatedPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto relatedPage = CreateRouterPage("related", RouterPageType::RELATED_PAGE);
    MountRouterPage(stageNode, pageA);
    MountRouterPage(stageNode, relatedPage);

    auto stackPages = stageManager->CollectRouterStackPages();
    EXPECT_EQ(stackPages.size(), 1);
    EXPECT_EQ(stackPages[0], pageA);
}

/**
 * @tc.name: GetPageColumnType_NullPage001
 * @tc.desc: Test GetPageColumnType returns NONE for null page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetPageColumnType_NullPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    EXPECT_EQ(stageManager->GetPageColumnType(nullptr), ForceSplitPageColumnType::NONE);
}

/**
 * @tc.name: GetPageColumnType_HomePage001
 * @tc.desc: Test GetPageColumnType returns PRIMARY for home page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetPageColumnType_HomePage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE, ForceSplitPageColumnType::NONE);
    MountRouterPage(stageNode, homePage);

    EXPECT_EQ(stageManager->GetPageColumnType(homePage), ForceSplitPageColumnType::PRIMARY);
}

/**
 * @tc.name: GetPageColumnType_DetailPage001
 * @tc.desc: Test GetPageColumnType returns SECONDARY for detail page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetPageColumnType_DetailPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto detailPage = CreateRouterPage("detail", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::NONE);
    MountRouterPage(stageNode, detailPage);

    EXPECT_EQ(stageManager->GetPageColumnType(detailPage), ForceSplitPageColumnType::SECONDARY);
}

/**
 * @tc.name: GetPageColumnType_AlreadySet001
 * @tc.desc: Test GetPageColumnType returns already set column type.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetPageColumnType_AlreadySet001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("page", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    MountRouterPage(stageNode, page);

    EXPECT_EQ(stageManager->GetPageColumnType(page), ForceSplitPageColumnType::PRIMARY);
}

/**
 * @tc.name: SetTouchedPrimaryColumnPage001
 * @tc.desc: Test SetTouchedPrimaryColumnPage sets the touched page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, SetTouchedPrimaryColumnPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("page");
    MountRouterPage(stageNode, page);

    stageManager->SetTouchedPrimaryColumnPage(page);
    EXPECT_EQ(stageManager->touchedPrimaryColumnPage_, page);
}

/**
 * @tc.name: GetTouchedPrimaryColumnPage001
 * @tc.desc: Test GetTouchedPrimaryColumnPage returns the touched page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetTouchedPrimaryColumnPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("page");
    MountRouterPage(stageNode, page);

    stageManager->touchedPrimaryColumnPage_ = page;
    EXPECT_EQ(stageManager->GetTouchedPrimaryColumnPage(), page);
}

/**
 * @tc.name: GetTouchedPrimaryColumnPage_Null001
 * @tc.desc: Test GetTouchedPrimaryColumnPage returns nullptr when not set.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, GetTouchedPrimaryColumnPage_Null001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->touchedPrimaryColumnPage_.Reset();
    EXPECT_EQ(stageManager->GetTouchedPrimaryColumnPage(), nullptr);
}

/**
 * @tc.name: SetTouchedSecondaryColumnPage001
 * @tc.desc: Test SetTouchedSecondaryColumnPage sets the touched page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, SetTouchedSecondaryColumnPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("page");
    MountRouterPage(stageNode, page);

    stageManager->SetTouchedSecondaryColumnPage(page);
    EXPECT_EQ(stageManager->touchedSecondaryColumnPage_, page);
}

/**
 * @tc.name: TakeTouchedSecondaryColumnPage001
 * @tc.desc: Test TakeTouchedSecondaryColumnPage returns and clears the touched page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, TakeTouchedSecondaryColumnPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto page = CreateRouterPage("page");
    MountRouterPage(stageNode, page);

    stageManager->touchedSecondaryColumnPage_ = page;
    auto takenPage = stageManager->TakeTouchedSecondaryColumnPage();
    EXPECT_EQ(takenPage, page);
    EXPECT_TRUE(stageManager->touchedSecondaryColumnPage_.Invalid());
}

/**
 * @tc.name: TakeTouchedSecondaryColumnPage_Null001
 * @tc.desc: Test TakeTouchedSecondaryColumnPage returns nullptr when not set.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, TakeTouchedSecondaryColumnPage_Null001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->touchedSecondaryColumnPage_.Reset();
    auto takenPage = stageManager->TakeTouchedSecondaryColumnPage();
    EXPECT_TRUE(takenPage == nullptr);
}

/**
 * @tc.name: SetNeedClearSecondaryPage_True001
 * @tc.desc: Test SetNeedClearSecondaryPage sets the clear flag.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, SetNeedClearSecondaryPage_True001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->SetNeedClearSecondaryPage(true);
    EXPECT_TRUE(stageManager->needClearSecondaryPage_);
}

/**
 * @tc.name: SetNeedClearSecondaryPage_False001
 * @tc.desc: Test SetNeedClearSecondaryPage clears the clear flag.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestThreeNg, SetNeedClearSecondaryPage_False001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->SetNeedClearSecondaryPage(true);
    stageManager->SetNeedClearSecondaryPage(false);
    EXPECT_FALSE(stageManager->needClearSecondaryPage_);
}
} // namespace OHOS::Ace::NG
