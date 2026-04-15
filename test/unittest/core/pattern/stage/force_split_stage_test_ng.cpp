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
RefPtr<ForceSplitManager> GetForceSplitManager()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    return pipeline ? pipeline->GetForceSplitManager() : nullptr;
}

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

RefPtr<ParallelStageManager> CreateParallelStageManagerForLayout(
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

RefPtr<ParallelStageManager> CreateParallelStageManager(
    RefPtr<FrameNode>& stageNode, RefPtr<ParallelStagePattern>& stagePattern)
{
    return CreateParallelStageManagerForLayout(stageNode, stagePattern);
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

void SetRouterPageFrameSize(const RefPtr<FrameNode>& page, float width)
{
    ASSERT_NE(page, nullptr);
    auto geometryNode = page->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(width, width));
}
}

class ParallelStageTestNg : public testing::Test {
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
    RefPtr<FrameNode> CreatePage();
    void CreatePage(RefPtr<FrameNode>& pageNode, RefPtr<ParallelPagePattern>& pagePattern);

    int32_t nextPageNodeId_ = 1;
    RefPtr<StageManager> backupStageManager_ = nullptr;
    DeviceOrientation preOrientation_ = DeviceOrientation::LANDSCAPE;
    DeviceType preDeviceType_ = DeviceType::UNKNOWN;
};

void ParallelStageTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

RefPtr<FrameNode> ParallelStageTestNg::CreatePage()
{
    RefPtr<FrameNode> pageNode = nullptr;
    RefPtr<ParallelPagePattern> pagePattern = nullptr;
    CreatePage(pageNode, pagePattern);
    return pageNode;
}

void ParallelStageTestNg::CreatePage(RefPtr<FrameNode>& pageNode, RefPtr<ParallelPagePattern>& pagePattern)
{
    auto info = AceType::MakeRefPtr<PageInfo>();
    ASSERT_NE(info, nullptr);
    auto pattern = AceType::MakeRefPtr<ParallelPagePattern>(info);
    ASSERT_NE(pattern, nullptr);
    auto page = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, nextPageNodeId_++, pattern);
    ASSERT_NE(page, nullptr);
    pageNode = page;
    pagePattern = pattern;
}

/**
 * @tc.name: ParallelStagePatternTest001
 * @tc.desc: Testing basic interfaces of ParallelStagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStagePatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelStagePattern and StageNode.
     * @tc.expected: Attributes of ParallelStagePattern has default value.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 1, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    ASSERT_EQ(stagePattern->mode_, PageMode::STACK);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    ASSERT_FALSE(stagePattern->HasDividerNode());
    auto dividerNode = stagePattern->GetDividerNode();
    ASSERT_EQ(dividerNode, nullptr);
    auto homePage = stagePattern->GetHomePage();
    ASSERT_EQ(homePage, nullptr);

    /**
     * @tc.steps: step2. Create layoutAlgorithm.
     * @tc.expected: The layoutAlgorithm was instance of ParallelStageLayoutAlgorithm.
     */
    auto layoutAlgorithm = AceType::DynamicCast<ParallelStageLayoutAlgorithm>(stagePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. Create home page.
     */
    auto info = AceType::MakeRefPtr<PageInfo>();
    ASSERT_NE(info, nullptr);
    auto pagePattern = AceType::MakeRefPtr<ParallelPagePattern>(info);
    ASSERT_NE(pagePattern, nullptr);
    pagePattern->SetPageType(RouterPageType::HOME_PAGE);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);

    /**
     * @tc.steps: step4. Set home page in stack mode.
     * @tc.expected: Success to set home page, divider node will not be created.
     */
    stagePattern->mode_ = PageMode::STACK;
    stagePattern->SetHomePage(pageNode);
    homePage = stagePattern->GetHomePage();
    ASSERT_EQ(homePage, pageNode);
    ASSERT_FALSE(stagePattern->HasDividerNode());
    dividerNode = stagePattern->GetDividerNode();
    ASSERT_EQ(dividerNode, nullptr);

    /**
     * @tc.steps: step5. Reset home page.
     * @tc.expected: Success to clear home page.
     */
    stagePattern->SetHomePage(nullptr);
    homePage = stagePattern->GetHomePage();
    ASSERT_EQ(homePage, nullptr);

    /**
     * @tc.steps: step6. Set home page in split mode.
     * @tc.expected: Success to set home page, divider node will be created.
     */
    stagePattern->mode_ = PageMode::SPLIT;
    stagePattern->SetHomePage(pageNode);
    homePage = stagePattern->GetHomePage();
    ASSERT_EQ(homePage, pageNode);
    ASSERT_TRUE(stagePattern->HasDividerNode());
    dividerNode = stagePattern->GetDividerNode();
    ASSERT_NE(dividerNode, nullptr);
}

/**
 * @tc.name: ParallelStagePatternTest003
 * @tc.desc: Testing StateChangeCallback of ParallelStagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStagePatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelStagePattern and StageNode.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 1, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    auto pipeline = stageNode->GetContext();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. Register callback to ParallelStagePattern.
     */
    std::optional<bool> curShow;
    auto stateChangeCallback = [&curShow](bool show) {
        curShow = show;
    };
    stagePattern->SetWindowStateChangeCallback(std::move(stateChangeCallback));

    /**
     * @tc.steps: step3. Trigger window show manually.
     * @tc.expected: curShow will be update to true.
     */
    curShow.reset();
    stagePattern->OnWindowShow();
    ASSERT_TRUE(curShow.has_value());
    ASSERT_TRUE(curShow.value());

    /**
     * @tc.steps: step4. Trigger window hide manually.
     * @tc.expected: curShow will be update to true.
     */
    curShow.reset();
    stagePattern->OnWindowHide();
    ASSERT_TRUE(curShow.has_value());
    ASSERT_FALSE(curShow.value());
}

/**
 * @tc.name: ParallelStageManagerTest002
 * @tc.desc: Testing PopPageToIndex function of ParallelStageManager work correctly in stack mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStageManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelStagePattern and some ParallelPagePattern.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    auto firstNode = CreatePage();
    auto secondNode = CreatePage();
    auto thirdNode = CreatePage();
    auto fourthNode = CreatePage();
    ParallelStageManager stageManager(stageNode);

    /**
     * @tc.steps: step2. Calling PopPageToIndex function.
     * @tc.expected: Children are empty and return false
     */
    EXPECT_FALSE(stageManager.PopPageToIndex(1));

    /**
     * @tc.steps: step3. Add first child node and recall PopPageToIndex.
     * @tc.expected: Children length is less than the current index and return false
     */
    stageManager.PushPage(firstNode);
    EXPECT_FALSE(stageManager.PopPageToIndex(1));

    /**
     * @tc.steps: step4. Add second child node and recall PopPageToIndex.
     * @tc.expected: Children length is equal to the current index and return true
     */
    stageManager.PushPage(secondNode);
    EXPECT_TRUE(stageManager.PopPageToIndex(1));

    /**
     * @tc.steps: step5. Add third child node and recall PopPageToIndex.
     * @tc.expected: stageManager child size meets expectations.
     */
    stageManager.PushPage(thirdNode);
    stageManager.PushPage(fourthNode);
    stageManager.PopPageToIndex(1);
    EXPECT_EQ(stageNode->GetChildren().size(), 3);
    stageManager.PopPageToIndex(0);
    EXPECT_EQ(stageNode->GetChildren().size(), 2);

    /**
     * @tc.steps: step6. Add third child node and recall PopPageToIndex.
     * @tc.expected: return true
     */
    stageManager.PushPage(thirdNode);
    stageManager.PushPage(fourthNode);
    EXPECT_TRUE(stageManager.PopPageToIndex(1, false, false));
}

/**
 * @tc.name: ParallelStageManagerTest003
 * @tc.desc: Testing CleanPageStack Function of ParallelStageManager work correctly in stack mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStageManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelStagePattern and ParallelPagePattern.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    auto firstNode = CreatePage();
    auto secondNode = CreatePage();
    ParallelStageManager stageManager(stageNode);

    /**
     * @tc.steps: step2. Call CleanPageStack function.
     * @tc.expected:Children just one and return false
     */
    stageManager.PushPage(firstNode);
    EXPECT_FALSE(stageManager.CleanPageStack());

    /**
     * @tc.steps: step3. Add second child node and recall CleanPageStack.
     * @tc.expected: return true
     */
    stageManager.PushPage(secondNode);
    EXPECT_TRUE(stageManager.CleanPageStack());
}

/**
 * @tc.name: ParallelStageManagerTest004
 * @tc.desc: Testing GetLastPage and MovePageToFront Function of ParallelStageManager work correctly in stack mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStageManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelStagePattern and some ParallelPagePattern.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    auto firstNode = CreatePage();
    auto secondNode = CreatePage();

    /**
     * @tc.steps: step2. Create a ParallelStageManager based on stageNode.
     */
    ParallelStageManager stageManager(stageNode);

    /**
     * @tc.steps: step3. Calling the GetLastPage function.
     * @tc.expected: The manager GetLastPage return null.
     */
    EXPECT_EQ(stageManager.GetLastPage(), nullptr);

    /**
     * @tc.steps: step4. Calling the MovePageToFront function.
     * @tc.expected: return false.
     */
    EXPECT_FALSE(stageManager.MovePageToFront(firstNode));

    /**
     * @tc.steps: step5. ParallelStageManager put a page and recall MovePageToFront.
     * @tc.expected: return true.
     */
    stageManager.PushPage(firstNode);
    EXPECT_TRUE(stageManager.MovePageToFront(firstNode));

    /**
     * @tc.steps: step6. ParallelStageManager another page and recall MovePageToFront with different params.
     * @tc.expected: always return true.
     */
    stageManager.PushPage(secondNode);
    EXPECT_TRUE(stageManager.MovePageToFront(firstNode, false, true));
    EXPECT_TRUE(stageManager.MovePageToFront(secondNode, true, false));

    /**
     * @tc.steps: step7. Calling the GetLastPage function.
     * @tc.expected: The secondNode is last page.
     */
    EXPECT_EQ(stageManager.GetLastPage(), secondNode);
}

/**
 * @tc.name: ParallelStageManagerTest009
 * @tc.desc: Testing OnWindowStateChange
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStageManagerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelStageManager and some ParallelPagePattern.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    const auto& children = stageNode->GetChildren();
    auto pipeline = stageNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);
    auto firstNode = CreatePage();

    /**
     * @tc.steps: step2. Call OnWindowStateChange with true and false.
     */
    stageManager->OnWindowStateChange(false);
    stageManager->OnWindowStateChange(true);
    auto lastPage = stageManager->GetLastPage();
    ASSERT_EQ(lastPage, nullptr);

    /**
     * @tc.steps: step3. Push firstPage, Call OnWindowStateChange with true and false.
     */
    ASSERT_TRUE(stageManager->PushPage(firstNode));
    ASSERT_EQ(children.size(), 1);

    stageManager->OnWindowStateChange(false);
    stageManager->OnWindowStateChange(true);
    lastPage = stageManager->GetLastPage();
    ASSERT_NE(lastPage, nullptr);
}

/**
 * @tc.name: ParallelStageManagerTest010
 * @tc.desc: Testing FirePageHideOnPopPage
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStageManagerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelStageManager and some ParallelPagePattern.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    auto pipeline = stageNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto firstNode = CreatePage();
    auto secondNode = CreatePage();
    auto thirdNode = CreatePage();
    auto hideTransitionType = PageTransitionType::NONE;
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);
    RefPtr<ParallelPagePattern> pagePattern = nullptr;

    /**
     * @tc.steps: step2. Call FirePageHideOnPopPage with different types.
     */
    bool res = stageManager->FirePageHideOnPopPage(firstNode, secondNode, thirdNode, pagePattern, hideTransitionType);
    ASSERT_EQ(res, true);
    hideTransitionType = PageTransitionType::ENTER;
    res = stageManager->FirePageHideOnPopPage(firstNode, secondNode, thirdNode, pagePattern, hideTransitionType);
    ASSERT_EQ(res, true);
    hideTransitionType = PageTransitionType::EXIT;
    res = stageManager->FirePageHideOnPopPage(firstNode, secondNode, thirdNode, pagePattern, hideTransitionType);
    ASSERT_EQ(res, true);
}

/**
 * @tc.name: ParallelStageManagerTest011
 * @tc.desc: Testing PopPage
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStageManagerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PopPage and some ParallelPagePattern.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    auto pipeline = stageNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    const auto& children = stageNode->GetChildren();
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);
    auto firstNode = CreatePage();
    auto secondNode = CreatePage();

    /**
     * @tc.steps: step2. Call PopPage with different parameters.
     */
    bool res = stageManager->PopPage(firstNode, false, false);
    ASSERT_EQ(res, false);

    ASSERT_TRUE(stageManager->PushPage(firstNode));
    ASSERT_TRUE(stageManager->PushPage(secondNode));
    ASSERT_EQ(children.size(), 2);

    res = stageManager->PopPage(firstNode, true, true);
    ASSERT_EQ(res, true);
}

/**
 * @tc.name: ParallelStageManagerTest012
 * @tc.desc: Testing PopPageInSplitMode
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStageManagerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PopPageInSplitMode and some ParallelPagePattern.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);
    auto firstNode = CreatePage();
    auto secondNode = CreatePage();

    /**
     * @tc.steps: step2. Call PopPageInSplitMode with different parameters.
     */
    bool res = stageManager->PopPageInSplitMode(false, false);
    ASSERT_EQ(res, false);

    ASSERT_TRUE(stageManager->PushPage(firstNode));
    ASSERT_TRUE(stageManager->PushPage(secondNode));
    const auto& children = stageNode->GetChildren();
    ASSERT_EQ(children.size(), 2);

    res = stageManager->PopPageInSplitMode(true, true);
    ASSERT_EQ(res, true);
}

/**
 * @tc.name: UpdateIsTopFullScreenPageTest001
 * @tc.desc: Testing UpdateIsTopFullScreenPage
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, UpdateIsTopFullScreenPageTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PopPageInSplitMode and ParallelStageManager.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), stagePattern);
    ASSERT_NE(stageNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);
    /**
     * @tc.steps: step2. Call UpdateIsTopFullScreenPage and do asserts.
     */
    ASSERT_FALSE(stageManager->IsTopFullScreenPageChanged());
    ASSERT_FALSE(stageManager->IsTopFullScreenPage());
    stageManager->UpdateIsTopFullScreenPage(true);
    ASSERT_TRUE(stageManager->IsTopFullScreenPageChanged());
    ASSERT_TRUE(stageManager->IsTopFullScreenPage());
    stageManager->UpdateIsTopFullScreenPage(true);
    ASSERT_FALSE(stageManager->IsTopFullScreenPageChanged());
    ASSERT_TRUE(stageManager->IsTopFullScreenPage());
    stageManager->UpdateIsTopFullScreenPage(false);
    ASSERT_TRUE(stageManager->IsTopFullScreenPageChanged());
    ASSERT_FALSE(stageManager->IsTopFullScreenPage());
}

/**
 * @tc.name: RebuildRouterColumnNodesIfNeeded001
 * @tc.desc: Test RebuildRouterColumnNodesIfNeeded records stack pages as primary nodes before home page detected.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, RebuildRouterColumnNodesIfNeeded001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage and manager.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);

    /**
     * @tc.steps: step2. Mount detail pages without a home page.
     */
    RefPtr<FrameNode> firstPage;
    RefPtr<ParallelPagePattern> firstPattern;
    CreatePage(firstPage, firstPattern);
    ASSERT_NE(firstPage, nullptr);
    ASSERT_NE(firstPattern, nullptr);
    firstPattern->SetPageType(RouterPageType::DETAIL_PAGE);
    firstPage->MountToParent(stageNode);

    RefPtr<FrameNode> secondPage;
    RefPtr<ParallelPagePattern> secondPattern;
    CreatePage(secondPage, secondPattern);
    ASSERT_NE(secondPage, nullptr);
    ASSERT_NE(secondPattern, nullptr);
    secondPattern->SetPageType(RouterPageType::DETAIL_PAGE);
    secondPage->MountToParent(stageNode);

    /**
     * @tc.steps: step3. Rebuild router column cache.
     * @tc.expected: All stack pages are temporarily recorded as primary nodes, and secondary is empty.
     */
    stageManager->routerColumnNodesDirty_ = true;
    stageManager->RebuildRouterColumnNodesIfNeeded();
    EXPECT_FALSE(stageManager->routerColumnNodesDirty_);
    EXPECT_EQ(stageManager->primaryNodes_.size(), 2);
    EXPECT_TRUE(stageManager->secondaryNodes_.empty());
    EXPECT_EQ(stageManager->GetTopPrimaryColumnPage(), secondPage);
    EXPECT_EQ(stageManager->GetTopSecondaryColumnPage(), nullptr);
}

/**
 * @tc.name: RebuildRouterColumnNodesIfNeeded002
 * @tc.desc: Test RebuildRouterColumnNodesIfNeeded splits stack pages by home page and column type.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, RebuildRouterColumnNodesIfNeeded002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage and manager.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);

    /**
     * @tc.steps: step2. Mount pages around home, plus placeholder and related pages.
     */
    RefPtr<FrameNode> beforeHomePage;
    RefPtr<ParallelPagePattern> beforeHomePattern;
    CreatePage(beforeHomePage, beforeHomePattern);
    ASSERT_NE(beforeHomePage, nullptr);
    ASSERT_NE(beforeHomePattern, nullptr);
    beforeHomePattern->SetPageType(RouterPageType::DETAIL_PAGE);
    beforeHomePage->MountToParent(stageNode);

    RefPtr<FrameNode> homePage;
    RefPtr<ParallelPagePattern> homePattern;
    CreatePage(homePage, homePattern);
    ASSERT_NE(homePage, nullptr);
    ASSERT_NE(homePattern, nullptr);
    homePattern->SetPageType(RouterPageType::HOME_PAGE);
    homePage->MountToParent(stageNode);

    RefPtr<FrameNode> primaryPage;
    RefPtr<ParallelPagePattern> primaryPattern;
    CreatePage(primaryPage, primaryPattern);
    ASSERT_NE(primaryPage, nullptr);
    ASSERT_NE(primaryPattern, nullptr);
    primaryPattern->SetPageType(RouterPageType::DETAIL_PAGE);
    primaryPattern->SetColumnType(ForceSplitPageColumnType::PRIMARY);
    primaryPage->MountToParent(stageNode);

    RefPtr<FrameNode> secondaryPage;
    RefPtr<ParallelPagePattern> secondaryPattern;
    CreatePage(secondaryPage, secondaryPattern);
    ASSERT_NE(secondaryPage, nullptr);
    ASSERT_NE(secondaryPattern, nullptr);
    secondaryPattern->SetPageType(RouterPageType::DETAIL_PAGE);
    secondaryPattern->SetColumnType(ForceSplitPageColumnType::NONE);
    secondaryPage->MountToParent(stageNode);

    RefPtr<FrameNode> placeholderPage;
    RefPtr<ParallelPagePattern> placeholderPattern;
    CreatePage(placeholderPage, placeholderPattern);
    ASSERT_NE(placeholderPage, nullptr);
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->SetPageType(RouterPageType::PLACEHOLDER_PAGE);
    placeholderPage->MountToParent(stageNode);

    RefPtr<FrameNode> relatedPage;
    RefPtr<ParallelPagePattern> relatedPattern;
    CreatePage(relatedPage, relatedPattern);
    ASSERT_NE(relatedPage, nullptr);
    ASSERT_NE(relatedPattern, nullptr);
    relatedPattern->SetPageType(RouterPageType::RELATED_PAGE);
    relatedPage->MountToParent(stageNode);

    /**
     * @tc.steps: step3. Rebuild router column cache.
     * @tc.expected: Pages before/at home and primary detail are primary nodes; default detail is secondary.
     */
    stageManager->routerColumnNodesDirty_ = true;
    stageManager->RebuildRouterColumnNodesIfNeeded();
    EXPECT_FALSE(stageManager->routerColumnNodesDirty_);
    EXPECT_EQ(stageManager->primaryNodes_.size(), 3);
    EXPECT_EQ(stageManager->secondaryNodes_.size(), 1);
    EXPECT_EQ(stageManager->GetTopPrimaryColumnPage(), primaryPage);
    EXPECT_EQ(stageManager->GetTopSecondaryColumnPage(), secondaryPage);
}

/**
 * @tc.name: RebuildRouterColumnNodesIfNeeded003
 * @tc.desc: Test RebuildRouterColumnNodesIfNeeded keeps existing cache when dirty flag is false.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, RebuildRouterColumnNodesIfNeeded003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage and manager.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);

    /**
     * @tc.steps: step2. Prepare an existing cache and mount another page.
     */
    RefPtr<FrameNode> cachedPage;
    RefPtr<ParallelPagePattern> cachedPattern;
    CreatePage(cachedPage, cachedPattern);
    ASSERT_NE(cachedPage, nullptr);
    ASSERT_NE(cachedPattern, nullptr);
    cachedPattern->SetPageType(RouterPageType::DETAIL_PAGE);
    cachedPage->MountToParent(stageNode);

    RefPtr<FrameNode> newPage;
    RefPtr<ParallelPagePattern> newPattern;
    CreatePage(newPage, newPattern);
    ASSERT_NE(newPage, nullptr);
    ASSERT_NE(newPattern, nullptr);
    newPattern->SetPageType(RouterPageType::DETAIL_PAGE);
    newPage->MountToParent(stageNode);

    stageManager->primaryNodes_.emplace_back(cachedPage);
    stageManager->routerColumnNodesDirty_ = false;

    /**
     * @tc.steps: step3. Call rebuild without invalidating the cache.
     * @tc.expected: Cached primary nodes are not rebuilt.
     */
    stageManager->RebuildRouterColumnNodesIfNeeded();
    EXPECT_FALSE(stageManager->routerColumnNodesDirty_);
    EXPECT_EQ(stageManager->primaryNodes_.size(), 1);
    EXPECT_EQ(stageManager->GetTopPrimaryColumnPage(), cachedPage);
}

/**
 * @tc.name: RouterPageColumnState001
 * @tc.desc: Test GetPageColumnType, SetPageColumnType and ClearRouterPageState.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, RouterPageColumnState001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto detailPage = CreateRouterPage("detail");
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    auto detailPattern = GetRouterPagePattern(detailPage);
    ASSERT_NE(detailPattern, nullptr);

    EXPECT_EQ(stageManager->GetPageColumnType(nullptr), ForceSplitPageColumnType::NONE);
    EXPECT_EQ(stageManager->GetPageColumnType(homePage), ForceSplitPageColumnType::PRIMARY);
    EXPECT_EQ(stageManager->GetPageColumnType(detailPage), ForceSplitPageColumnType::SECONDARY);
    EXPECT_EQ(stageManager->GetPageColumnType(placeholderPage), ForceSplitPageColumnType::NONE);

    stageManager->routerColumnNodesDirty_ = false;
    stageManager->SetPageColumnType(detailPage, ForceSplitPageColumnType::SECONDARY);
    EXPECT_EQ(detailPattern->GetColumnType(), ForceSplitPageColumnType::SECONDARY);
    EXPECT_TRUE(stageManager->routerColumnNodesDirty_);

    stageManager->routerColumnNodesDirty_ = false;
    stageManager->SetPageColumnType(detailPage, ForceSplitPageColumnType::SECONDARY);
    EXPECT_FALSE(stageManager->routerColumnNodesDirty_);

    stageManager->SetPageColumnType(detailPage, ForceSplitPageColumnType::PRIMARY);
    EXPECT_EQ(stageManager->GetPageColumnType(detailPage), ForceSplitPageColumnType::PRIMARY);
    EXPECT_TRUE(stageManager->routerColumnNodesDirty_);

    stageManager->routerColumnNodesDirty_ = false;
    stageManager->ClearRouterPageState(detailPage);
    EXPECT_EQ(detailPattern->GetColumnType(), ForceSplitPageColumnType::NONE);
    EXPECT_TRUE(stageManager->routerColumnNodesDirty_);

    stageManager->routerColumnNodesDirty_ = false;
    stageManager->ClearRouterPageState(detailPage);
    EXPECT_FALSE(stageManager->routerColumnNodesDirty_);
}

/**
 * @tc.name: ShouldMovePageToPrimaryForTransition001
 * @tc.desc: Test ShouldMovePageToPrimaryForTransition with split state, home page and page pair constraints.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ShouldMovePageToPrimaryForTransition001, TestSize.Level1)
{
    auto forceSplitManager = GetForceSplitManager();
    ASSERT_NE(forceSplitManager, nullptr);
    ResetForceSplitBehaviorConfig(forceSplitManager);
    forceSplitManager->SetBehaviorMode(ForceSplitBehaviorMode::NAVIGATION);
    std::unordered_map<std::string, std::unordered_set<std::string>> pagePairs = {
        { "list", { "detail" } },
    };
    forceSplitManager->SetPagePairs(std::move(pagePairs));

    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    ASSERT_NE(stagePattern, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    ASSERT_NE(homePage, nullptr);
    auto fromPage = CreateRouterPage("list");
    ASSERT_NE(fromPage, nullptr);
    auto toPage = CreateRouterPage("detail");
    ASSERT_NE(toPage, nullptr);
    auto otherPage = CreateRouterPage("other");
    ASSERT_NE(otherPage, nullptr);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, fromPage);
    MountRouterPage(stageNode, toPage);
    MountRouterPage(stageNode, otherPage);

    stagePattern->mode_ = PageMode::STACK;
    EXPECT_FALSE(stageManager->ShouldMovePageToPrimaryForTransition(fromPage, toPage));
    EXPECT_TRUE(stageManager->ShouldMovePageToPrimaryForTransition(fromPage, toPage, false));

    stagePattern->mode_ = PageMode::SPLIT;
    stageManager->needClearSecondaryPage_ = true;
    EXPECT_FALSE(stageManager->ShouldMovePageToPrimaryForTransition(fromPage, toPage));
    stageManager->needClearSecondaryPage_ = false;
    EXPECT_TRUE(stageManager->ShouldMovePageToPrimaryForTransition(fromPage, toPage));
    EXPECT_FALSE(stageManager->ShouldMovePageToPrimaryForTransition(fromPage, fromPage));
    EXPECT_FALSE(stageManager->ShouldMovePageToPrimaryForTransition(homePage, toPage));
    EXPECT_FALSE(stageManager->ShouldMovePageToPrimaryForTransition(fromPage, homePage));
    EXPECT_FALSE(stageManager->ShouldMovePageToPrimaryForTransition(fromPage, otherPage));
}

/**
 * @tc.name: UpdateRouterColumnsOnPush001
 * @tc.desc: Test UpdateRouterColumnsOnPush updates current and new page column types.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, UpdateRouterColumnsOnPush001, TestSize.Level1)
{
    auto forceSplitManager = GetForceSplitManager();
    ASSERT_NE(forceSplitManager, nullptr);
    ResetForceSplitBehaviorConfig(forceSplitManager);
    forceSplitManager->SetBehaviorMode(ForceSplitBehaviorMode::NAVIGATION);
    std::unordered_map<std::string, std::unordered_set<std::string>> pagePairs = {
        { "list", { "detail" } },
    };
    forceSplitManager->SetPagePairs(std::move(pagePairs));

    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    ASSERT_NE(stagePattern, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    ASSERT_NE(homePage, nullptr);
    auto currentPage = CreateRouterPage("list");
    ASSERT_NE(currentPage, nullptr);
    auto newPage = CreateRouterPage("detail");
    ASSERT_NE(newPage, nullptr);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, currentPage);
    MountRouterPage(stageNode, newPage);

    stageManager->UpdateRouterColumnsOnPush(currentPage, newPage);
    auto currentPattern = GetRouterPagePattern(currentPage);
    ASSERT_NE(currentPattern, nullptr);
    auto newPattern = GetRouterPagePattern(newPage);
    ASSERT_NE(newPattern, nullptr);
    EXPECT_EQ(currentPattern->GetColumnType(), ForceSplitPageColumnType::PRIMARY);
    EXPECT_EQ(newPattern->GetColumnType(), ForceSplitPageColumnType::SECONDARY);

    forceSplitManager->pagePairs_.clear();
    auto blockedCurrentPage = CreateRouterPage("blockedCurrent");
    auto blockedNewPage = CreateRouterPage("blockedNew");
    MountRouterPage(stageNode, blockedCurrentPage);
    MountRouterPage(stageNode, blockedNewPage);
    stageManager->UpdateRouterColumnsOnPush(blockedCurrentPage, blockedNewPage);
    auto blockedCurrentPattern = GetRouterPagePattern(blockedCurrentPage);
    ASSERT_NE(blockedCurrentPattern, nullptr);
    auto blockedNewPattern = GetRouterPagePattern(blockedNewPage);
    ASSERT_NE(blockedNewPattern, nullptr);
    EXPECT_EQ(blockedCurrentPattern->GetColumnType(), ForceSplitPageColumnType::NONE);
    EXPECT_EQ(blockedNewPattern->GetColumnType(), ForceSplitPageColumnType::SECONDARY);
}

/**
 * @tc.name: GetRouterVisiblePages001
 * @tc.desc: Test router visible page calculation for stack tree, split tree and dispatcher.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, GetRouterVisiblePages001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    ASSERT_NE(stagePattern, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto primaryPage = CreateRouterPage("primary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    auto secondaryPage = CreateRouterPage(
        "secondary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::SECONDARY);
    auto placeholderPage = CreateRouterPage("placeholder", RouterPageType::PLACEHOLDER_PAGE);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, primaryPage);
    MountRouterPage(stageNode, secondaryPage);
    MountRouterPage(stageNode, placeholderPage);
    stagePattern->SetPlaceholderPage(placeholderPage);

    stagePattern->mode_ = PageMode::STACK;
    auto stackVisible = stageManager->GetRouterVisiblePagesForCurrentStackTree();
    EXPECT_EQ(stackVisible.primary, nullptr);
    EXPECT_EQ(stackVisible.detail, secondaryPage);
    auto dispatcherVisible = stageManager->GetRouterVisiblePages();
    EXPECT_EQ(dispatcherVisible.primary, nullptr);
    EXPECT_EQ(dispatcherVisible.detail, secondaryPage);

    stagePattern->mode_ = PageMode::SPLIT;
    stageManager->InvalidateRouterColumnNodes();
    auto splitVisible = stageManager->GetRouterVisiblePagesForCurrentSplitTree();
    EXPECT_EQ(splitVisible.primary, primaryPage);
    EXPECT_EQ(splitVisible.detail, secondaryPage);
    dispatcherVisible = stageManager->GetRouterVisiblePages();
    EXPECT_EQ(dispatcherVisible.primary, primaryPage);
    EXPECT_EQ(dispatcherVisible.detail, secondaryPage);

    stageNode->RemoveChild(secondaryPage);
    stageManager->InvalidateRouterColumnNodes();
    auto fallbackVisible = stageManager->GetRouterVisiblePagesForCurrentSplitTree();
    EXPECT_EQ(fallbackVisible.primary, primaryPage);
    EXPECT_EQ(fallbackVisible.detail, placeholderPage);
}

/**
 * @tc.name: CheckRouterMoveAllowed001
 * @tc.desc: Test CheckIfMovePageToPrimaryIsAllowed and CheckIfMovePageToSecondaryIsAllowed.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, CheckRouterMoveAllowed001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto pageA = CreateRouterPage("pageA");
    auto pageB = CreateRouterPage("pageB");
    auto pageC = CreateRouterPage("pageC");

    ParallelStageManager::RouterVisiblePages prePushVisible;
    prePushVisible.primary = pageA;
    prePushVisible.detail = pageB;
    ParallelStageManager::RouterVisiblePages newPushVisible;
    newPushVisible.primary = pageB;
    newPushVisible.detail = pageC;
    EXPECT_TRUE(stageManager->CheckIfMovePageToPrimaryIsAllowed(prePushVisible, newPushVisible));
    EXPECT_FALSE(stageManager->CheckIfMovePageToSecondaryIsAllowed(prePushVisible, newPushVisible));

    ParallelStageManager::RouterVisiblePages prePopVisible;
    prePopVisible.primary = pageB;
    prePopVisible.detail = pageC;
    ParallelStageManager::RouterVisiblePages newPopVisible;
    newPopVisible.primary = pageA;
    newPopVisible.detail = pageB;
    EXPECT_FALSE(stageManager->CheckIfMovePageToPrimaryIsAllowed(prePopVisible, newPopVisible));
    EXPECT_TRUE(stageManager->CheckIfMovePageToSecondaryIsAllowed(prePopVisible, newPopVisible));

    ParallelStageManager::RouterVisiblePages invalidVisible;
    invalidVisible.primary = pageA;
    invalidVisible.detail = pageA;
    EXPECT_FALSE(stageManager->CheckIfMovePageToPrimaryIsAllowed(invalidVisible, newPushVisible));
    EXPECT_FALSE(stageManager->CheckIfMovePageToSecondaryIsAllowed(prePopVisible, invalidVisible));
}

/**
 * @tc.name: RouterPagesSplitPushTransitionStage001
 * @tc.desc: Test split push start and end dispatch target transition types to each page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, RouterPagesSplitPushTransitionStage001, TestSize.Level1)
{
    constexpr float pageWidth = 120.0f;
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
    SetRouterPageFrameSize(exitPage, pageWidth);
    SetRouterPageFrameSize(movePage, pageWidth);
    SetRouterPageFrameSize(enterPage, pageWidth);

    auto exitPattern = GetRouterPagePattern(exitPage);
    auto movePattern = GetRouterPagePattern(movePage);
    auto enterPattern = GetRouterPagePattern(enterPage);
    ASSERT_NE(exitPattern, nullptr);
    ASSERT_NE(movePattern, nullptr);
    ASSERT_NE(enterPattern, nullptr);

    constexpr int32_t animationId1 = 1;
    exitPattern->PrepareSplitTransition(animationId1, PageTransitionType::EXIT_PUSH);
    movePattern->PrepareSplitTransition(animationId1, PageTransitionType::MOVE_PUSH);
    enterPattern->PrepareSplitTransition(animationId1, PageTransitionType::ENTER_PUSH);
    stageManager->OnRouterPagesSplitPushStart(exitPage, movePage, enterPage);
    auto pushEnterOffset = enterPage->GetRenderContext()->GetTranslateXYProperty();
    auto pushEnterX = AceApplicationInfo::GetInstance().IsRightToLeft() ? -pageWidth : pageWidth;
    EXPECT_EQ(exitPage->GetRenderContext()->GetTranslateXYProperty(), OffsetF());
    EXPECT_EQ(movePage->GetRenderContext()->GetTranslateXYProperty(), OffsetF());
    EXPECT_FLOAT_EQ(pushEnterOffset.GetX(), pushEnterX);
    EXPECT_FLOAT_EQ(pushEnterOffset.GetY(), 0.0f);

    stageManager->OnRouterPagesSplitPushEnd(exitPage, movePage, enterPage);
    EXPECT_EQ(exitPattern->GetSplitTransitionType(), PageTransitionType::EXIT_PUSH);
    EXPECT_EQ(movePattern->GetSplitTransitionType(), PageTransitionType::MOVE_PUSH);
    EXPECT_EQ(enterPattern->GetSplitTransitionType(), PageTransitionType::ENTER_PUSH);
    EXPECT_EQ(exitPattern->GetSplitTransitionPhase(), SplitTransitionPhase::END);
    EXPECT_EQ(movePattern->GetSplitTransitionPhase(), SplitTransitionPhase::END);
    EXPECT_EQ(enterPattern->GetSplitTransitionPhase(), SplitTransitionPhase::END);
}

/**
 * @tc.name: RouterPagesSplitPopTransitionStage001
 * @tc.desc: Test split pop start and end dispatch target transition types to each page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, RouterPagesSplitPopTransitionStage001, TestSize.Level1)
{
    constexpr float pageWidth = 120.0f;
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
    SetRouterPageFrameSize(enterPage, pageWidth);
    SetRouterPageFrameSize(exitPage, pageWidth);
    SetRouterPageFrameSize(movePage, pageWidth);

    auto enterPattern = GetRouterPagePattern(enterPage);
    auto exitPattern = GetRouterPagePattern(exitPage);
    auto movePattern = GetRouterPagePattern(movePage);
    ASSERT_NE(enterPattern, nullptr);
    ASSERT_NE(exitPattern, nullptr);
    ASSERT_NE(movePattern, nullptr);

    constexpr int32_t animationId = 1;
    enterPattern->PrepareSplitTransition(animationId, PageTransitionType::ENTER_POP);
    movePattern->PrepareSplitTransition(animationId, PageTransitionType::MOVE_POP);
    exitPattern->PrepareSplitTransition(animationId, PageTransitionType::EXIT_POP);
    stageManager->OnRouterPagesSplitPopStart(enterPage, exitPage, movePage);
    auto popEnterOffset = enterPage->GetRenderContext()->GetTranslateXYProperty();
    auto popEnterX = AceApplicationInfo::GetInstance().IsRightToLeft() ? pageWidth : -pageWidth;
    EXPECT_FLOAT_EQ(popEnterOffset.GetX(), popEnterX);
    EXPECT_FLOAT_EQ(popEnterOffset.GetY(), 0.0f);

    stageManager->OnRouterPagesSplitPopEnd(enterPage, exitPage, movePage);
    EXPECT_EQ(enterPattern->GetSplitTransitionType(), PageTransitionType::ENTER_POP);
    EXPECT_EQ(movePattern->GetSplitTransitionType(), PageTransitionType::MOVE_POP);
    EXPECT_EQ(exitPattern->GetSplitTransitionType(), PageTransitionType::EXIT_POP);
    EXPECT_EQ(enterPattern->GetSplitTransitionPhase(), SplitTransitionPhase::END);
    EXPECT_EQ(movePattern->GetSplitTransitionPhase(), SplitTransitionPhase::END);
    EXPECT_EQ(exitPattern->GetSplitTransitionPhase(), SplitTransitionPhase::END);
}

/**
 * @tc.name: ParallelPagePatternSplitTransitionColumnType001
 * @tc.desc: Test split transition phase and type map to expected column types.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelPagePatternSplitTransitionColumnType001, TestSize.Level1)
{
    auto page = CreateRouterPage("detail");
    auto pattern = GetRouterPagePattern(page);
    ASSERT_NE(pattern, nullptr);

    EXPECT_EQ(pattern->GetSplitTransitionColumnType(), ForceSplitPageColumnType::NONE);
    EXPECT_FALSE(pattern->IsInSplitTransitionLayout());

    pattern->SetPageInTransition(true);
    pattern->UpdateSplitTransitionState(PageTransitionType::EXIT_PUSH, SplitTransitionPhase::START);
    EXPECT_EQ(pattern->GetSplitTransitionColumnType(), ForceSplitPageColumnType::PRIMARY);
    EXPECT_TRUE(pattern->IsInSplitTransitionLayout());

    pattern->UpdateSplitTransitionState(PageTransitionType::ENTER_PUSH, SplitTransitionPhase::START);
    EXPECT_EQ(pattern->GetSplitTransitionColumnType(), ForceSplitPageColumnType::SECONDARY);

    pattern->UpdateSplitTransitionState(PageTransitionType::MOVE_PUSH, SplitTransitionPhase::START);
    EXPECT_EQ(pattern->GetSplitTransitionColumnType(), ForceSplitPageColumnType::SECONDARY);
    pattern->UpdateSplitTransitionState(PageTransitionType::MOVE_PUSH, SplitTransitionPhase::END);
    EXPECT_EQ(pattern->GetSplitTransitionColumnType(), ForceSplitPageColumnType::PRIMARY);

    pattern->UpdateSplitTransitionState(PageTransitionType::ENTER_POP, SplitTransitionPhase::START);
    EXPECT_EQ(pattern->GetSplitTransitionColumnType(), ForceSplitPageColumnType::PRIMARY);

    pattern->UpdateSplitTransitionState(PageTransitionType::EXIT_POP, SplitTransitionPhase::START);
    EXPECT_EQ(pattern->GetSplitTransitionColumnType(), ForceSplitPageColumnType::SECONDARY);

    pattern->UpdateSplitTransitionState(PageTransitionType::MOVE_POP, SplitTransitionPhase::START);
    EXPECT_EQ(pattern->GetSplitTransitionColumnType(), ForceSplitPageColumnType::PRIMARY);
    pattern->UpdateSplitTransitionState(PageTransitionType::MOVE_POP, SplitTransitionPhase::END);
    EXPECT_EQ(pattern->GetSplitTransitionColumnType(), ForceSplitPageColumnType::SECONDARY);

    pattern->UpdateSplitTransitionState(PageTransitionType::MOVE_POP, SplitTransitionPhase::NONE);
    EXPECT_EQ(pattern->GetSplitTransitionColumnType(), ForceSplitPageColumnType::NONE);
    EXPECT_FALSE(pattern->IsInSplitTransitionLayout());
}

/**
 * @tc.name: ParallelPagePatternPrepareAbortSplitTransition001
 * @tc.desc: Test PrepareSplitTransition records transition state and AbortSplitTransition clears it.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelPagePatternPrepareAbortSplitTransition001, TestSize.Level1)
{
    constexpr float pageWidth = 100.0f;
    constexpr int32_t animationId = 101;
    auto page = CreateRouterPage("detail");
    auto pattern = GetRouterPagePattern(page);
    ASSERT_NE(pattern, nullptr);
    SetRouterPageFrameSize(page, pageWidth);
    auto eventHub = page->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->IsEnabled());

    pattern->PrepareSplitTransition(animationId, PageTransitionType::EXIT_POP);
    EXPECT_TRUE(pattern->GetPageInTransition());
    EXPECT_EQ(pattern->GetAnimationId(), animationId);
    EXPECT_EQ(pattern->GetSplitTransitionType(), PageTransitionType::EXIT_POP);
    EXPECT_EQ(pattern->GetSplitTransitionPhase(), SplitTransitionPhase::START);
    EXPECT_TRUE(pattern->hasSplitTransitionVisualOffset_);
    EXPECT_FALSE(eventHub->IsEnabled());

    pattern->OnSplitTransitionEnd(PageTransitionType::EXIT_POP);
    auto exitPopEndX = AceApplicationInfo::GetInstance().IsRightToLeft() ? -pageWidth : pageWidth;
    EXPECT_FLOAT_EQ(page->GetRenderContext()->GetTranslateXYProperty().GetX(), exitPopEndX);

    pattern->AbortSplitTransition();
    EXPECT_FALSE(pattern->GetPageInTransition());
    EXPECT_EQ(pattern->GetSplitTransitionType(), PageTransitionType::NONE);
    EXPECT_EQ(pattern->GetSplitTransitionPhase(), SplitTransitionPhase::NONE);
    EXPECT_FALSE(pattern->hasSplitTransitionVisualOffset_);
    EXPECT_TRUE(eventHub->IsEnabled());
    EXPECT_EQ(page->GetRenderContext()->GetTranslateXYProperty(), OffsetF());
}

/**
 * @tc.name: ParallelPagePatternFinishSplitTransition001
 * @tc.desc: Test OnSplitTransitionFinish ignores stale animation and clears current transition.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelPagePatternFinishSplitTransition001, TestSize.Level1)
{
    constexpr float pageWidth = 100.0f;
    constexpr int32_t animationId = 201;
    auto page = CreateRouterPage("detail");
    auto pattern = GetRouterPagePattern(page);
    ASSERT_NE(pattern, nullptr);
    SetRouterPageFrameSize(page, pageWidth);

    pattern->PrepareSplitTransition(animationId, PageTransitionType::ENTER_PUSH);
    pattern->OnSplitTransitionStart(PageTransitionType::ENTER_PUSH);
    EXPECT_TRUE(pattern->GetPageInTransition());
    EXPECT_NE(page->GetRenderContext()->GetTranslateXYProperty().GetX(), 0.0f);

    EXPECT_FALSE(pattern->OnSplitTransitionFinish(animationId + 1, PageTransitionType::ENTER_PUSH));
    EXPECT_TRUE(pattern->GetPageInTransition());
    EXPECT_EQ(pattern->GetSplitTransitionType(), PageTransitionType::ENTER_PUSH);
    EXPECT_EQ(pattern->GetSplitTransitionPhase(), SplitTransitionPhase::START);

    EXPECT_TRUE(pattern->OnSplitTransitionFinish(animationId, PageTransitionType::ENTER_PUSH));
    EXPECT_FALSE(pattern->GetPageInTransition());
    EXPECT_EQ(pattern->GetSplitTransitionType(), PageTransitionType::NONE);
    EXPECT_EQ(pattern->GetSplitTransitionPhase(), SplitTransitionPhase::NONE);
    EXPECT_FALSE(pattern->hasSplitTransitionVisualOffset_);
    EXPECT_EQ(page->GetRenderContext()->GetTranslateXYProperty(), OffsetF());
}

/**
 * @tc.name: ParallelPagePatternFinishExitTransition001
 * @tc.desc: Test exit push hides page and exit pop removes page from parent after finish.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelPagePatternFinishExitTransition001, TestSize.Level1)
{
    constexpr int32_t exitPushAnimationId = 301;
    constexpr int32_t exitPopAnimationId = 302;
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto exitPushPage = CreateRouterPage("exitPush");
    auto exitPushPattern = GetRouterPagePattern(exitPushPage);
    ASSERT_NE(exitPushPattern, nullptr);
    MountRouterPage(stageNode, exitPushPage);
    exitPushPattern->PrepareSplitTransition(exitPushAnimationId, PageTransitionType::EXIT_PUSH);
    EXPECT_TRUE(exitPushPattern->OnSplitTransitionFinish(exitPushAnimationId, PageTransitionType::EXIT_PUSH));
    EXPECT_EQ(stageNode->GetChildIndex(exitPushPage), 0);
    EXPECT_EQ(exitPushPage->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);

    auto exitPopPage = CreateRouterPage("exitPop");
    auto exitPopPattern = GetRouterPagePattern(exitPopPage);
    ASSERT_NE(exitPopPattern, nullptr);
    MountRouterPage(stageNode, exitPopPage);
    ASSERT_GE(stageNode->GetChildIndex(exitPopPage), 0);
    exitPopPattern->PrepareSplitTransition(exitPopAnimationId, PageTransitionType::EXIT_POP);
    EXPECT_TRUE(exitPopPattern->OnSplitTransitionFinish(exitPopAnimationId, PageTransitionType::EXIT_POP));
    EXPECT_LT(stageNode->GetChildIndex(exitPopPage), 0);
}

/**
 * @tc.name: ParallelPagePatternInitOnTouchEventForVirtualStack001
 * @tc.desc: Test InitOnTouchEvent records touched primary or secondary page in virtual stack split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelPagePatternInitOnTouchEventForVirtualStack001, TestSize.Level1)
{
    auto forceSplitManager = GetForceSplitManager();
    ASSERT_NE(forceSplitManager, nullptr);
    ResetForceSplitBehaviorConfig(forceSplitManager);
    std::unordered_map<std::string, std::unordered_set<std::string>> pagePairs = {
        { "primary", { "secondary" } },
    };
    forceSplitManager->SetPagePairs(std::move(pagePairs));

    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    ASSERT_NE(stagePattern, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto primaryPage = CreateRouterPage("primary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    auto secondaryPage =
        CreateRouterPage("secondary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::SECONDARY);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, primaryPage);
    MountRouterPage(stageNode, secondaryPage);
    stagePattern->mode_ = PageMode::SPLIT;
    stageManager->InvalidateRouterColumnNodes();

    auto primaryPattern = GetRouterPagePattern(primaryPage);
    auto secondaryPattern = GetRouterPagePattern(secondaryPage);
    ASSERT_NE(primaryPattern, nullptr);
    ASSERT_NE(secondaryPattern, nullptr);

    auto oldStageManager = context->stageManager_;
    context->stageManager_ = stageManager;
    primaryPattern->InitOnTouchEvent();
    secondaryPattern->InitOnTouchEvent();
    if (!primaryPattern->touchListener_ || !secondaryPattern->touchListener_) {
        context->stageManager_ = oldStageManager;
        ResetForceSplitBehaviorConfig(forceSplitManager);
        FAIL();
    }
    TouchEventInfo touchInfo("touch");

    (*secondaryPattern->touchListener_)(touchInfo);
    EXPECT_EQ(stageManager->GetTouchedPrimaryColumnPage(), nullptr);
    EXPECT_EQ(stageManager->TakeTouchedSecondaryColumnPage(), secondaryPage);

    (*primaryPattern->touchListener_)(touchInfo);
    EXPECT_EQ(stageManager->GetTouchedPrimaryColumnPage(), primaryPage);
    EXPECT_EQ(stageManager->TakeTouchedSecondaryColumnPage(), nullptr);

    primaryPattern->RemoveOnTouchEvent();
    secondaryPattern->RemoveOnTouchEvent();
    EXPECT_EQ(primaryPattern->touchListener_, nullptr);
    EXPECT_EQ(secondaryPattern->touchListener_, nullptr);
    context->stageManager_ = oldStageManager;
    ResetForceSplitBehaviorConfig(forceSplitManager);
}

/**
 * @tc.name: ParallelPagePatternRelatedPageLifecycle001
 * @tc.desc: Test related page attach, detach and NotifyAboutToDisappear lifecycle state.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelPagePatternRelatedPageLifecycle001, TestSize.Level1)
{
    auto relatedPage = CreateRouterPage("related", RouterPageType::RELATED_PAGE);
    auto relatedPattern = GetRouterPagePattern(relatedPage);
    ASSERT_NE(relatedPattern, nullptr);

    EXPECT_TRUE(relatedPattern->needNotifyRelatedPageAboutToAppear_);
    relatedPattern->OnAttachToMainTree();
    EXPECT_FALSE(relatedPattern->needNotifyRelatedPageAboutToAppear_);
    EXPECT_EQ(relatedPattern->GetPageInfo()->GetPageIndex(), -1);
    EXPECT_EQ(relatedPattern->state_, RouterPageState::ABOUT_TO_APPEAR);

    relatedPattern->SetNeedNotifyRelatedPageAboutToDisappear(true);
    relatedPattern->OnDetachFromMainTree();
    EXPECT_FALSE(relatedPattern->needNotifyRelatedPageAboutToDisappear_);
    EXPECT_EQ(relatedPattern->state_, RouterPageState::ABOUT_TO_DISAPPEAR);

    relatedPattern->NotifyAboutToDisappear();
    EXPECT_TRUE(relatedPattern->needNotifyRelatedPageAboutToAppear_);
    EXPECT_EQ(relatedPattern->state_, RouterPageState::ABOUT_TO_DISAPPEAR);
}

/**
 * @tc.name: ParallelStageLayoutAlgorithmPageColumnType001
 * @tc.desc: Test GetPageLayoutColumnType with visible pages, invisible pages, placeholder and transition pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStageLayoutAlgorithmPageColumnType001, TestSize.Level1)
{
    ParallelStageLayoutAlgorithm algorithm;
    algorithm.primaryIndex_ = 1;
    algorithm.secondaryIndex_ = 2;

    RefPtr<FrameNode> primaryPage;
    RefPtr<ParallelPagePattern> primaryPattern;
    CreatePage(primaryPage, primaryPattern);
    ASSERT_NE(primaryPage, nullptr);
    ASSERT_NE(primaryPattern, nullptr);
    primaryPattern->SetPageType(RouterPageType::DETAIL_PAGE);
    EXPECT_EQ(algorithm.GetPageLayoutColumnType(primaryPage, 1), ForceSplitPageColumnType::PRIMARY);

    RefPtr<FrameNode> secondaryPage;
    RefPtr<ParallelPagePattern> secondaryPattern;
    CreatePage(secondaryPage, secondaryPattern);
    ASSERT_NE(secondaryPage, nullptr);
    ASSERT_NE(secondaryPattern, nullptr);
    secondaryPattern->SetPageType(RouterPageType::DETAIL_PAGE);
    EXPECT_EQ(algorithm.GetPageLayoutColumnType(secondaryPage, 2), ForceSplitPageColumnType::SECONDARY);

    RefPtr<FrameNode> invisiblePage;
    RefPtr<ParallelPagePattern> invisiblePattern;
    CreatePage(invisiblePage, invisiblePattern);
    ASSERT_NE(invisiblePage, nullptr);
    ASSERT_NE(invisiblePattern, nullptr);
    invisiblePattern->SetPageType(RouterPageType::DETAIL_PAGE);
    invisiblePage->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    EXPECT_EQ(algorithm.GetPageLayoutColumnType(invisiblePage, 1), ForceSplitPageColumnType::NONE);

    RefPtr<FrameNode> transitionPage;
    RefPtr<ParallelPagePattern> transitionPattern;
    CreatePage(transitionPage, transitionPattern);
    ASSERT_NE(transitionPage, nullptr);
    ASSERT_NE(transitionPattern, nullptr);
    transitionPattern->SetPageType(RouterPageType::DETAIL_PAGE);
    transitionPage->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    transitionPattern->SetPageInTransition(true);
    transitionPattern->UpdateSplitTransitionState(PageTransitionType::MOVE_PUSH, SplitTransitionPhase::START);
    EXPECT_EQ(algorithm.GetPageLayoutColumnType(transitionPage, 3), ForceSplitPageColumnType::SECONDARY);

    RefPtr<FrameNode> placeholderPage;
    RefPtr<ParallelPagePattern> placeholderPattern;
    CreatePage(placeholderPage, placeholderPattern);
    ASSERT_NE(placeholderPage, nullptr);
    ASSERT_NE(placeholderPattern, nullptr);
    placeholderPattern->SetPageType(RouterPageType::PLACEHOLDER_PAGE);
    EXPECT_EQ(algorithm.GetPageLayoutColumnType(placeholderPage, 1), ForceSplitPageColumnType::NONE);
    EXPECT_EQ(algorithm.GetPageLayoutColumnType(placeholderPage, 2), ForceSplitPageColumnType::SECONDARY);
}

/**
 * @tc.name: ParallelStageLayoutAlgorithmSlotOffset001
 * @tc.desc: Test primary, secondary and divider offsets in LTR and RTL directions.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStageLayoutAlgorithmSlotOffset001, TestSize.Level1)
{
    constexpr float primaryWidth = 300.0f;
    constexpr float secondaryWidth = 419.0f;
    constexpr float dividerWidth =1.0f;
    constexpr float stageHeight = 600.0f;
    constexpr float narrowPrimaryPageWidth = 200.0f;
    constexpr float widePrimaryPageWidth = 400.0f;
    constexpr float ltrPrimaryOffsetX = primaryWidth - narrowPrimaryPageWidth;
    constexpr float ltrSecondaryOffsetX = primaryWidth + dividerWidth;
    constexpr float rtlPrimaryOffsetX = secondaryWidth + dividerWidth + ltrPrimaryOffsetX;
    ParallelStageLayoutAlgorithm algorithm;
    algorithm.primarySize_ = SizeF(primaryWidth, stageHeight);
    algorithm.secondarySize_ = SizeF(secondaryWidth, stageHeight);
    algorithm.dividerSize_ = SizeF(dividerWidth, stageHeight);

    auto& applicationInfo = AceApplicationInfo::GetInstance();
    auto oldRtl = applicationInfo.isRightToLeft_;
    applicationInfo.isRightToLeft_ = false;
    EXPECT_FLOAT_EQ(algorithm.GetDividerOffsetX(), primaryWidth);
    EXPECT_EQ(algorithm.GetPrimarySlotOffset(narrowPrimaryPageWidth), OffsetF(ltrPrimaryOffsetX, 0.0f));
    EXPECT_EQ(algorithm.GetPrimarySlotOffset(widePrimaryPageWidth), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(algorithm.GetSecondarySlotOffset(), OffsetF(ltrSecondaryOffsetX, 0.0f));

    applicationInfo.isRightToLeft_ = true;
    EXPECT_FLOAT_EQ(algorithm.GetDividerOffsetX(), secondaryWidth);
    EXPECT_EQ(algorithm.GetPrimarySlotOffset(narrowPrimaryPageWidth), OffsetF(rtlPrimaryOffsetX, 0.0f));
    EXPECT_EQ(algorithm.GetSecondarySlotOffset(), OffsetF(0.0f, 0.0f));
    applicationInfo.isRightToLeft_ = oldRtl;
}
} // namespace OHOS::Ace::NG
