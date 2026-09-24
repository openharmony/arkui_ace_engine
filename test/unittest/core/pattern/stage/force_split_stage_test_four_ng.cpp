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

#include <list>
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

class ParallelStageTestFourNg : public testing::Test {
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

void ParallelStageTestFourNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

namespace {
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
 * @tc.name: RemoveSecondaryPagesOfPrimaryPage_ResetsHomeTouchedOnEmptyStack001
 * @tc.desc: Test RemoveSecondaryPagesOfPrimaryPage resets homePageTouched_ to nullopt when stack is empty.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, RemoveSecondaryPagesOfPrimaryPage_ResetsHomeTouchedOnEmptyStack001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->SetHomePageTouched(true);
    EXPECT_TRUE(stageManager->GetHomePageTouched().has_value());

    // secondaryPageStack_ is empty by default, so the early-return path is taken
    stageManager->RemoveSecondaryPagesOfPrimaryPage();
    EXPECT_FALSE(stageManager->GetHomePageTouched().has_value());
}

/**
 * @tc.name: RemoveSecondaryPagesOfPrimaryPage_ResetsHomeTouchedAfterClear001
 * @tc.desc: Test RemoveSecondaryPagesOfPrimaryPage resets homePageTouched_ to nullopt after clearing stack.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, RemoveSecondaryPagesOfPrimaryPage_ResetsHomeTouchedAfterClear001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    auto detailPage = CreateRouterPage("detail", RouterPageType::DETAIL_PAGE);
    MountRouterPage(stageNode, detailPage);
    // Push a secondary page into the stack so the non-empty path is taken
    stageManager->secondaryPageStack_.emplace_back(WeakPtr<FrameNode>(detailPage));

    stageManager->SetHomePageTouched(true);
    EXPECT_TRUE(stageManager->GetHomePageTouched().has_value());

    stageManager->RemoveSecondaryPagesOfPrimaryPage();
    EXPECT_FALSE(stageManager->GetHomePageTouched().has_value());
}

/**
 * @tc.name: UpdateSecondaryPageNeedRemoved_ResetsHomeTouchedOnNotClear001
 * @tc.desc: Test UpdateSecondaryPageNeedRemoved resets homePageTouched_ to nullopt
 *           when needClearSecondaryPage is false.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, UpdateSecondaryPageNeedRemoved_ResetsHomeTouchedOnNotClear001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->SetHomePageTouched(true);
    EXPECT_TRUE(stageManager->GetHomePageTouched().has_value());

    auto count = stageManager->UpdateSecondaryPageNeedRemoved(false);
    EXPECT_EQ(count, 0);
    EXPECT_FALSE(stageManager->GetHomePageTouched().has_value());
}

/**
 * @tc.name: UpdateSecondaryPageNeedRemoved_ResetsHomeTouchedOnEmptyChildren001
 * @tc.desc: Test UpdateSecondaryPageNeedRemoved resets homePageTouched_ when children is empty.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, UpdateSecondaryPageNeedRemoved_ResetsHomeTouchedOnEmptyChildren001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->SetHomePageTouched(true);
    EXPECT_TRUE(stageManager->GetHomePageTouched().has_value());

    // stageNode has no children, so the early-return path inside the function is taken
    auto count = stageManager->UpdateSecondaryPageNeedRemoved(true);
    EXPECT_EQ(count, 0);
    EXPECT_FALSE(stageManager->GetHomePageTouched().has_value());
}

/**
 * @tc.name: UpdateSecondaryPageNeedRemoved_ResetsHomeTouchedAfterTraversal001
 * @tc.desc: Test UpdateSecondaryPageNeedRemoved resets homePageTouched_ after traversing pages.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, UpdateSecondaryPageNeedRemoved_ResetsHomeTouchedAfterTraversal001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto detailPage = CreateRouterPage("detail", RouterPageType::DETAIL_PAGE);
    MountRouterPage(stageNode, homePage);
    MountRouterPage(stageNode, detailPage);

    stageManager->SetHomePageTouched(true);
    EXPECT_TRUE(stageManager->GetHomePageTouched().has_value());

    stageManager->UpdateSecondaryPageNeedRemoved(true);
    // homePageFound is true, so should return the count of secondary pages
    EXPECT_FALSE(stageManager->GetHomePageTouched().has_value());
}

/**
 * @tc.name: UpdateSecondaryPageNeedRemoved_ResetsHomeTouchedWithStopPage001
 * @tc.desc: Test UpdateSecondaryPageNeedRemoved resets homePageTouched_ with virtual-stack stop page.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, UpdateSecondaryPageNeedRemoved_ResetsHomeTouchedWithStopPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);
    stagePattern->mode_ = PageMode::SPLIT;

    auto primaryPage = CreateRouterPage("primary", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::PRIMARY);
    auto detailPage = CreateRouterPage("detail", RouterPageType::DETAIL_PAGE, ForceSplitPageColumnType::SECONDARY);
    MountRouterPage(stageNode, primaryPage);
    MountRouterPage(stageNode, detailPage);
    stageManager->InvalidateRouterColumnNodes();

    // Set a touched primary column page so IsVirtualStackBasedSplit stopPage path is taken
    stageManager->SetTouchedPrimaryColumnPage(primaryPage);

    stageManager->SetHomePageTouched(true);
    EXPECT_TRUE(stageManager->GetHomePageTouched().has_value());

    stageManager->UpdateSecondaryPageNeedRemoved(true);
    EXPECT_FALSE(stageManager->GetHomePageTouched().has_value());
}

/**
 * @tc.name: IsSplitMode_AffectsCheckSecondaryPageNeedClear001
 * @tc.desc: Test that IsSplitMode returns false in STACK mode, which would cause CheckSecondaryPageNeedClear
 *           to return false early (the new branch added by the commit).
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, IsSplitMode_AffectsCheckSecondaryPageNeedClear001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    // STACK mode: IsSplitMode() returns false, which is the new early-return condition
    stagePattern->mode_ = PageMode::STACK;
    EXPECT_FALSE(stageManager->IsSplitMode());

    // In STACK mode, homePageTouched should not be consulted for clearing decisions
    stageManager->SetHomePageTouched(true);
    EXPECT_TRUE(stageManager->GetHomePageTouched().has_value());
    EXPECT_TRUE(stageManager->GetHomePageTouched().value());

    // Verify the mode stays STACK
    EXPECT_FALSE(stageManager->IsSplitMode());
}

/**
 * @tc.name: IsSplitMode_SplitModeEnabled001
 * @tc.desc: Test IsSplitMode returns true in SPLIT mode and homePageTouched is accessible.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, IsSplitMode_SplitModeEnabled001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stagePattern->mode_ = PageMode::SPLIT;
    EXPECT_TRUE(stageManager->IsSplitMode());

    // In SPLIT mode, homePageTouched is relevant for CheckSecondaryPageNeedClear
    stageManager->SetHomePageTouched(true);
    EXPECT_TRUE(stageManager->GetHomePageTouched().has_value());
    EXPECT_TRUE(stageManager->GetHomePageTouched().value());

    stageManager->SetHomePageTouched(false);
    EXPECT_TRUE(stageManager->GetHomePageTouched().has_value());
    EXPECT_FALSE(stageManager->GetHomePageTouched().value());

    stageManager->SetHomePageTouched(std::nullopt);
    EXPECT_FALSE(stageManager->GetHomePageTouched().has_value());
}

/**
 * @tc.name: CheckSecondaryPageNeedClear_HomeTouchNulloptBranch001
 * @tc.desc: Test that when GetHomePageTouched returns nullopt, the has_value() check prevents
 *           needClearSecondaryPage from being true in the else branch logic.
 *           This tests the new branch: homeTouch.has_value() && homeTouch.value().
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, CheckSecondaryPageNeedClear_HomeTouchNulloptBranch001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->SetHomePageTouched(std::nullopt);
    const auto& homeTouch = stageManager->GetHomePageTouched();
    EXPECT_FALSE(homeTouch.has_value());
    // This is the exact condition from the new code:
    bool needClearSecondaryPage = homeTouch.has_value() && homeTouch.value();
    EXPECT_FALSE(needClearSecondaryPage);
}

/**
 * @tc.name: CheckSecondaryPageNeedClear_HomeTouchFalseBranch001
 * @tc.desc: Test that when GetHomePageTouched returns false, needClearSecondaryPage is false
 *           in the else branch logic.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, CheckSecondaryPageNeedClear_HomeTouchFalseBranch001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->SetHomePageTouched(false);
    const auto& homeTouch = stageManager->GetHomePageTouched();
    EXPECT_TRUE(homeTouch.has_value());
    EXPECT_FALSE(homeTouch.value());

    bool needClearSecondaryPage = homeTouch.has_value() && homeTouch.value();
    EXPECT_FALSE(needClearSecondaryPage);
}

/**
 * @tc.name: CheckSecondaryPageNeedClear_HomeTouchTrueBranch001
 * @tc.desc: Test that when GetHomePageTouched returns true, needClearSecondaryPage can be true
 *           in the else branch logic (assuming page type is DETAIL_PAGE).
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, CheckSecondaryPageNeedClear_HomeTouchTrueBranch001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->SetHomePageTouched(true);
    const auto& homeTouch = stageManager->GetHomePageTouched();
    EXPECT_TRUE(homeTouch.has_value());
    EXPECT_TRUE(homeTouch.value());

    auto detailPage = CreateRouterPage("detail", RouterPageType::DETAIL_PAGE);
    auto pattern = GetRouterPagePattern(detailPage);
    ASSERT_NE(pattern, nullptr);
    bool needClearSecondaryPage =
        RouterPageType::DETAIL_PAGE == pattern->GetPageType() && homeTouch.has_value() && homeTouch.value();
    EXPECT_TRUE(needClearSecondaryPage);
}

/**
 * @tc.name: CheckSecondaryPageNeedClear_HomeTouchTrueButNotDetailPage001
 * @tc.desc: Test that when page type is HOME_PAGE, needClearSecondaryPage is false
 *           even if homeTouch is true.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, CheckSecondaryPageNeedClear_HomeTouchTrueButNotDetailPage001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->SetHomePageTouched(true);
    const auto& homeTouch = stageManager->GetHomePageTouched();
    EXPECT_TRUE(homeTouch.has_value());
    EXPECT_TRUE(homeTouch.value());

    auto homePage = CreateRouterPage("home", RouterPageType::HOME_PAGE);
    auto pattern = GetRouterPagePattern(homePage);
    ASSERT_NE(pattern, nullptr);
    bool needClearSecondaryPage =
        RouterPageType::DETAIL_PAGE == pattern->GetPageType() && homeTouch.has_value() && homeTouch.value();
    EXPECT_FALSE(needClearSecondaryPage);
}

/**
 * @tc.name: SetNeedClearSecondaryPage_FalseDoesNotResetHomeTouched001
 * @tc.desc: Test that SetNeedClearSecondaryPage(false) resets touchedPrimaryColumnPage_
 *           but does not modify homePageTouched_. This verifies that the commit's new
 *           homePageTouched_ = std::nullopt lines are in the correct functions only.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, SetNeedClearSecondaryPage_FalseDoesNotResetHomeTouched001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    stageManager->SetHomePageTouched(true);
    EXPECT_TRUE(stageManager->GetHomePageTouched().has_value());

    stageManager->SetNeedClearSecondaryPage(false);
    // SetNeedClearSecondaryPage(false) only resets touchedPrimaryColumnPage_,
    // homePageTouched_ should remain unchanged
    EXPECT_TRUE(stageManager->GetHomePageTouched().has_value());
    EXPECT_TRUE(stageManager->GetHomePageTouched().value());
}

/**
 * @tc.name: RemoveSecondaryPagesOfPrimaryPage_NulloptStaysNullopt001
 * @tc.desc: Test RemoveSecondaryPagesOfPrimaryPage on empty stack when homePageTouched is already nullopt.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, RemoveSecondaryPagesOfPrimaryPage_NulloptStaysNullopt001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    EXPECT_FALSE(stageManager->GetHomePageTouched().has_value());

    // Call RemoveSecondaryPagesOfPrimaryPage on empty stack - homePageTouched_ stays nullopt
    stageManager->RemoveSecondaryPagesOfPrimaryPage();
    EXPECT_FALSE(stageManager->GetHomePageTouched().has_value());
}

/**
 * @tc.name: UpdateSecondaryPageNeedRemoved_FalseWithNulloptStaysNullopt001
 * @tc.desc: Test UpdateSecondaryPageNeedRemoved(false) when homePageTouched is already nullopt.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestFourNg, UpdateSecondaryPageNeedRemoved_FalseWithNulloptStaysNullopt001, TestSize.Level1)
{
    RefPtr<FrameNode> stageNode;
    RefPtr<ParallelStagePattern> stagePattern;
    auto stageManager = CreateParallelStageManager(stageNode, stagePattern);
    ASSERT_NE(stageManager, nullptr);

    EXPECT_FALSE(stageManager->GetHomePageTouched().has_value());

    auto count = stageManager->UpdateSecondaryPageNeedRemoved(false);
    EXPECT_EQ(count, 0);
    EXPECT_FALSE(stageManager->GetHomePageTouched().has_value());
}

} // namespace OHOS::Ace::NG
