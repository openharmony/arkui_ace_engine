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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/components/navigation_bar/navigation_bar_theme.h"
#include "core/components_ng/base/frame_node.h"
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
constexpr int SPLIT_MODE_THRESHOLD_WIDTH = 600;  // 600vp
constexpr double PIPELINE_DIPSCALE = 2.5;
constexpr int ENABLE_SPLIT_MODE_WIDTH = (SPLIT_MODE_THRESHOLD_WIDTH + 1) * PIPELINE_DIPSCALE;
constexpr int DISABLE_SPLIT_MODE_WIDTH = (SPLIT_MODE_THRESHOLD_WIDTH - 1) * PIPELINE_DIPSCALE;
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
        MockPipelineContext::GetCurrent()->stageManager_ = backupStageManager_;
    }

    void MockPipelineContextGetTheme();
    RefPtr<FrameNode> CreatePage();
    void CreatePage(RefPtr<FrameNode>& pageNode, RefPtr<ParallelPagePattern>& pagePattern);

    void IdentifyPageAsPrimaryPage(const RefPtr<ParallelStageManager>& stageManager,
        const RefPtr<FrameNode>& pageNode, RefPtr<FrameNode>& placeHolderPageOut, int32_t& placeHolderCreateCountOut);

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

void ParallelStageTestNg::IdentifyPageAsPrimaryPage(const RefPtr<ParallelStageManager>& stageManager,
    const RefPtr<FrameNode>& pageNode, RefPtr<FrameNode>& placeHolderPageOut, int32_t& placeHolderCreateCountOut)
{
    std::list<WeakPtr<FrameNode>> pageRouterStack;
    pageRouterStack.emplace_back(pageNode);
    auto placeHolderPage = CreatePage();
    placeHolderPageOut = placeHolderPage;
    placeHolderCreateCountOut = 0;
    auto createPlaceHolderPageCallback = [&placeHolderPage, &placeHolderCreateCountOut]() -> RefPtr<FrameNode> {
        placeHolderCreateCountOut++;
        return placeHolderPage;
    };
    stageManager->OnPrimaryPageDetected(pageNode, std::move(createPlaceHolderPageCallback), pageRouterStack);
    auto stageNode = stageManager->GetStageNode();
    ASSERT_NE(stageNode, nullptr);
    auto stagePattern = stageNode->GetPattern<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    const auto& children = stageNode->GetChildren();
    ASSERT_EQ(placeHolderCreateCountOut, 1);
    ASSERT_GE(children.size(), 3);
    ASSERT_TRUE(stagePattern->GetIsSplit());
    ASSERT_TRUE(stagePattern->HasDividerNode());
    {
        auto firstChild = AceType::DynamicCast<FrameNode>(children.front());
        auto preLastChild = AceType::DynamicCast<FrameNode>(*(++children.rbegin()));
        auto lastChild = AceType::DynamicCast<FrameNode>(children.back());
        ASSERT_EQ(firstChild, stagePattern->GetDividerNode());
        ASSERT_EQ(preLastChild, pageNode);
        ASSERT_EQ(lastChild, placeHolderPage);
        ASSERT_EQ(stagePattern->GetPrimaryPage().Upgrade(), preLastChild);
    }
}

/**
 * @tc.name: ParallelPagePatternTest001
 * @tc.desc: Testing basic interfaces of ParallelPagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelPagePatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelPagePattern and pageNode.
     * @tc.expected: Attributes of ParallelPagePattern has default value.
     */
    auto info = AceType::MakeRefPtr<PageInfo>();
    ASSERT_NE(info, nullptr);
    auto pagePattern = AceType::MakeRefPtr<ParallelPagePattern>(info);
    ASSERT_NE(pagePattern, nullptr);
    EXPECT_EQ(pagePattern->GetPageType(), RouterPageType::SECONDARY_PAGE);
    EXPECT_FALSE(pagePattern->IsPlaceHolderPageBuildCompleted());
    EXPECT_EQ(pagePattern->GetPrimaryPage(), nullptr);
    EXPECT_EQ(pagePattern->GetPrePrimaryPage(), nullptr);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);

    /**
     * @tc.steps: step2. Create PlaceHolderPage and set callback.
     */
    int32_t placeHolderCreateCount = 0;
    auto placeHolderPattern = AceType::MakeRefPtr<ParallelPagePattern>(info);
    ASSERT_NE(placeHolderPattern, nullptr);
    EXPECT_EQ(placeHolderPattern->GetPageType(), RouterPageType::SECONDARY_PAGE);
    auto testPlaceHolderPage = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 2, placeHolderPattern);
    auto placeHolderCreateCallback = [&placeHolderCreateCount, &testPlaceHolderPage]() -> RefPtr<FrameNode> {
        placeHolderCreateCount++;
        return testPlaceHolderPage;
    };
    pagePattern->SetLoadPlaceHolderPageCallback(std::move(placeHolderCreateCallback));

    /**
     * @tc.steps: step3. call GetOrCreatePlaceHolderPage().
     * @tc.expected: callback function will be called by only once time,
     *               the created page will be setted as PlaceHolderPage.
     */
    auto page1 = pagePattern->GetOrCreatePlaceHolderPage();
    ASSERT_EQ(placeHolderCreateCount, 1);
    ASSERT_EQ(testPlaceHolderPage, page1);
    EXPECT_EQ(placeHolderPattern->GetPageType(), RouterPageType::PLACEHOLDER_PAGE);

    /**
     * @tc.steps: step4. call GetOrCreatePlaceHolderPage() again.
     * @tc.expected: callback function will not be called.
     */
    auto page2 = pagePattern->GetOrCreatePlaceHolderPage();
    ASSERT_EQ(placeHolderCreateCount, 1);
    ASSERT_EQ(testPlaceHolderPage, page2);
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
    auto primaryPage = stagePattern->GetPrimaryPage().Upgrade();
    ASSERT_EQ(primaryPage, nullptr);

    /**
     * @tc.steps: step2. Create layoutAlgorithm.
     * @tc.expected: The layoutAlgorithm was instance of ParallelStageLayoutAlgorithm.
     */
    auto layoutAlgorithm = AceType::DynamicCast<ParallelStageLayoutAlgorithm>(stagePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. Create PrimaryPage.
     */
    auto info = AceType::MakeRefPtr<PageInfo>();
    ASSERT_NE(info, nullptr);
    auto pagePattern = AceType::MakeRefPtr<ParallelPagePattern>(info);
    ASSERT_NE(pagePattern, nullptr);
    pagePattern->SetPageType(RouterPageType::PRIMARY_PAGE);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);

    /**
     * @tc.steps: step4. Set primary page in stack mode.
     * @tc.expected: Success to set primary page, divider node will not be created.
     */
    stagePattern->mode_ = PageMode::STACK;
    stagePattern->SetPrimaryPage(pageNode);
    primaryPage = stagePattern->GetPrimaryPage().Upgrade();
    ASSERT_EQ(primaryPage, pageNode);
    ASSERT_FALSE(stagePattern->HasDividerNode());
    dividerNode = stagePattern->GetDividerNode();
    ASSERT_EQ(dividerNode, nullptr);

    /**
     * @tc.steps: step5. Reset primary page.
     * @tc.expected: Success to clear primary page.
     */
    stagePattern->SetPrimaryPage(nullptr);
    primaryPage = stagePattern->GetPrimaryPage().Upgrade();
    ASSERT_EQ(primaryPage, nullptr);

    /**
     * @tc.steps: step6. Set primary page in split mode.
     * @tc.expected: Success to set primary page, divider node will be created.
     */
    stagePattern->mode_ = PageMode::SPLIT;
    stagePattern->SetPrimaryPage(pageNode);
    primaryPage = stagePattern->GetPrimaryPage().Upgrade();
    ASSERT_EQ(primaryPage, pageNode);
    ASSERT_TRUE(stagePattern->HasDividerNode());
    dividerNode = stagePattern->GetDividerNode();
    ASSERT_NE(dividerNode, nullptr);
}

/**
 * @tc.name: ParallelStagePatternTest002
 * @tc.desc: Testing ModeChangeCallback of ParallelStagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStagePatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelStagePattern and StageNode.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 1, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    auto pipeline = stageNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->dipScale_ = PIPELINE_DIPSCALE;

    /**
     * @tc.steps: step2. Register callback to ParallelStagePattern.
     */
    std::optional<bool> isSplit;
    WeakPtr<ParallelStagePattern> weakStage = stagePattern;
    auto modeChangeCallback = [&isSplit, weakStage]() {
        auto stage = weakStage.Upgrade();
        if (stage) {
            isSplit = stage->GetIsSplit();
        }
    };
    stagePattern->SetModeChangeCallback(std::move(modeChangeCallback));

    /**
     * @tc.steps: step3. Disable force split, trigger window size change callback with large width.
     * @tc.expected: callback won't be called.
     */
    auto mockPipelineContext = AceType::DynamicCast<MockPipelineContext>(pipeline);
    ASSERT_NE(mockPipelineContext, nullptr);
    auto stageManager = mockPipelineContext->stageManager_;
    stageManager->isForceSplit_ = false;
    isSplit.reset();
    stagePattern->OnWindowSizeChanged(ENABLE_SPLIT_MODE_WIDTH, 600, WindowSizeChangeReason::RESIZE);
    ASSERT_FALSE(isSplit.has_value());

    /**
     * @tc.steps: step4. Disable force split, trigger window size change callback with small width.
     * @tc.expected: callback won't be called.
     */
    isSplit.reset();
    stagePattern->OnWindowSizeChanged(DISABLE_SPLIT_MODE_WIDTH, 600, WindowSizeChangeReason::RESIZE);
    ASSERT_FALSE(isSplit.has_value());

    /**
     * @tc.steps: step5. Enable force split, trigger window size change callback with large width.
     * @tc.expected: isSplit will be update to true.
     */
    stageManager->isForceSplit_ = true;
    isSplit.reset();
    stagePattern->OnWindowSizeChanged(ENABLE_SPLIT_MODE_WIDTH, 600, WindowSizeChangeReason::RESIZE);
    ASSERT_TRUE(isSplit.has_value());
    ASSERT_TRUE(isSplit.value());

    /**
     * @tc.steps: step6. Enable force split, trigger window size change callback with small width.
     * @tc.expected: isSplit will be update to false.
     */
    isSplit.reset();
    stagePattern->OnWindowSizeChanged(DISABLE_SPLIT_MODE_WIDTH, 600, WindowSizeChangeReason::RESIZE);
    ASSERT_TRUE(isSplit.has_value());
    ASSERT_FALSE(isSplit.value());
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
 * @tc.name: ParallelStageManagerTest006
 * @tc.desc: Testing PopPageToIndex function of ParallelStageManager work correctly in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStageManagerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelStagePattern and some ParallelPagePattern.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    const auto& children = stageNode->GetChildren();
    auto pipeline = stageNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto primaryPage = stagePattern->GetPrimaryPage().Upgrade();
    ASSERT_EQ(primaryPage, nullptr);
    auto firstNode = CreatePage();
    auto secondNode = CreatePage();
    auto thirdNode = CreatePage();
    auto fourthNode = CreatePage();

    /**
     * @tc.steps: step2. Create ParallelStageManager, trigger window size change.
     * @tc.expected: Stage enter split mode, and has no divider.
     */
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);
    pipeline->stageManager_ = stageManager;
    pipeline->stageManager_->isForceSplit_ = true;
    pipeline->dipScale_ = PIPELINE_DIPSCALE;
    stagePattern->OnWindowSizeChanged(ENABLE_SPLIT_MODE_WIDTH, 600, WindowSizeChangeReason::RESIZE);
    ASSERT_TRUE(stagePattern->GetIsSplit());
    ASSERT_FALSE(stagePattern->HasDividerNode());

    /**
     * @tc.steps: step3. Calling PopPageToIndex function.
     * @tc.expected: Children are empty and return false
     */
    ASSERT_FALSE(stageManager->PopPageToIndex(1));
    ASSERT_TRUE(children.empty());

    /**
     * @tc.steps: step4. Push firstPage, identify the page as the primarypage.
     * @tc.expected: stageNode has 3 child node: [0]dividerNode, [1]primaryPage, [2]placeHolderPage.
     */
    ASSERT_TRUE(stageManager->PushPage(firstNode));
    RefPtr<FrameNode> placeHolderPage = nullptr;
    int32_t placeHolderCreateCount = 0;
    IdentifyPageAsPrimaryPage(stageManager, firstNode, placeHolderPage, placeHolderCreateCount);
    ASSERT_EQ(children.size(), 3);

    /**
     * @tc.steps: step5. Recall PopPageToIndex.
     * @tc.expected: Page number is equal to the index and return false
     */
    ASSERT_FALSE(stageManager->PopPageToIndex(1));
    ASSERT_EQ(children.size(), 3);
    {
        auto lastChild = AceType::DynamicCast<FrameNode>(children.back());
        ASSERT_EQ(lastChild, placeHolderPage);
    }

    /**
     * @tc.steps: step6. Add second child node and recall PopPageToIndex.
     * @tc.expected: Page number is large than the index and return true
     */
    ASSERT_TRUE(stageManager->PushPage(secondNode));
    ASSERT_EQ(children.size(), 3);
    {
        auto lastChild = AceType::DynamicCast<FrameNode>(children.back());
        ASSERT_EQ(lastChild, secondNode);
    }
    ASSERT_TRUE(stageManager->PopPageToIndex(1));
    ASSERT_EQ(children.size(), 3);
    {
        auto lastChild = AceType::DynamicCast<FrameNode>(children.back());
        ASSERT_EQ(lastChild, secondNode);
    }

    /**
     * @tc.steps: step7. Add third child node and recall PopPageToIndex.
     * @tc.expected: stageManager child size meets expectations.
     */
    ASSERT_TRUE(stageManager->PushPage(thirdNode));
    ASSERT_EQ(children.size(), 4);
    {
        auto lastChild = AceType::DynamicCast<FrameNode>(children.back());
        ASSERT_EQ(lastChild, thirdNode);
    }
    ASSERT_TRUE(stageManager->PushPage(fourthNode));
    ASSERT_EQ(children.size(), 5);
    {
        auto lastChild = AceType::DynamicCast<FrameNode>(children.back());
        ASSERT_EQ(lastChild, fourthNode);
    }
    ASSERT_TRUE(stageManager->PopPageToIndex(1));
    ASSERT_EQ(children.size(), 3);
    {
        auto lastChild = AceType::DynamicCast<FrameNode>(children.back());
        ASSERT_EQ(lastChild, secondNode);
    }
    ASSERT_TRUE(stageManager->PopPageToIndex(0));
    ASSERT_EQ(children.size(), 3);
    {
        auto lastChild = AceType::DynamicCast<FrameNode>(children.back());
        ASSERT_EQ(lastChild, placeHolderPage);
    }
}

/**
 * @tc.name: ParallelStageManagerTest007
 * @tc.desc: Testing CleanPageStack Function of ParallelStageManager work correctly in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStageManagerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelStagePattern and some ParallelPagePattern.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    const auto& children = stageNode->GetChildren();
    auto pipeline = stageNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto primaryPage = stagePattern->GetPrimaryPage().Upgrade();
    ASSERT_EQ(primaryPage, nullptr);
    auto firstNode = CreatePage();
    auto secondNode = CreatePage();
    auto thirdNode = CreatePage();

    /**
     * @tc.steps: step2. Create ParallelStageManager, trigger window size change.
     * @tc.expected: Stage enter split mode, and has no divider.
     */
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);
    pipeline->stageManager_ = stageManager;
    pipeline->stageManager_->isForceSplit_ = true;
    pipeline->dipScale_ = PIPELINE_DIPSCALE;
    stagePattern->OnWindowSizeChanged(ENABLE_SPLIT_MODE_WIDTH, 600, WindowSizeChangeReason::RESIZE);
    ASSERT_TRUE(stagePattern->GetIsSplit());
    ASSERT_FALSE(stagePattern->HasDividerNode());

    /**
     * @tc.steps: step2. Call CleanPageStack function.
     * @tc.expected: Only one page and return false
     */
    ASSERT_TRUE(stageManager->PushPage(firstNode));
    ASSERT_EQ(children.size(), 1);
    EXPECT_FALSE(stageManager->CleanPageStack());

    /**
     * @tc.steps: step3. Add two pages, identify third page as primary page.
     * @tc.expected: stageNode: [0]dividerNode, [1]firstNode, [2]secondNode, [3]thirdNode, [4]placeHolder
     */
    ASSERT_TRUE(stageManager->PushPage(secondNode));
    ASSERT_TRUE(stageManager->PushPage(thirdNode));
    ASSERT_EQ(children.size(), 3);
    RefPtr<FrameNode> placeHolderPage = nullptr;
    int32_t placeHolderCreateCount = 0;
    IdentifyPageAsPrimaryPage(stageManager, thirdNode, placeHolderPage, placeHolderCreateCount);
    ASSERT_EQ(children.size(), 5);
    ASSERT_TRUE(stagePattern->GetIsSplit());
    ASSERT_TRUE(stagePattern->HasDividerNode());
    {
        auto iter = children.begin();
        auto child1 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child2 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child3 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child4 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child5 = AceType::DynamicCast<FrameNode>(*(iter++));
        ASSERT_EQ(child1, stagePattern->GetDividerNode());
        ASSERT_EQ(child2, firstNode);
        ASSERT_EQ(child3, secondNode);
        ASSERT_EQ(child4, thirdNode);
        ASSERT_EQ(child5, placeHolderPage);
        ASSERT_EQ(stagePattern->GetPrimaryPage().Upgrade(), thirdNode);
    }

    /**
     * @tc.steps: step4. Call CleanPageStack function.
     * @tc.expected: return true, stageNode: [0]dividerNode, [1]thirdNode, [2]placeHolder
     */
    EXPECT_TRUE(stageManager->CleanPageStack());
    ASSERT_EQ(children.size(), 3);
    ASSERT_TRUE(stagePattern->GetIsSplit());
    ASSERT_TRUE(stagePattern->HasDividerNode());
    {
        auto iter = children.begin();
        auto child1 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child2 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child3 = AceType::DynamicCast<FrameNode>(*(iter++));
        ASSERT_EQ(child1, stagePattern->GetDividerNode());
        ASSERT_EQ(child2, thirdNode);
        ASSERT_EQ(child3, placeHolderPage);
        ASSERT_EQ(stagePattern->GetPrimaryPage().Upgrade(), thirdNode);
    }
}

/**
 * @tc.name: ParallelStageManagerTest008
 * @tc.desc: Testing GetLastPage and MovePageToFront Function of ParallelStageManager work correctly in split mode.
 * @tc.type: FUNC
 */
HWTEST_F(ParallelStageTestNg, ParallelStageManagerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelStagePattern and some ParallelPagePattern.
     */
    auto stagePattern = AceType::MakeRefPtr<ParallelStagePattern>();
    ASSERT_NE(stagePattern, nullptr);
    ASSERT_FALSE(stagePattern->GetIsSplit());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, stagePattern);
    ASSERT_NE(stageNode, nullptr);
    const auto& children = stageNode->GetChildren();
    auto pipeline = stageNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto primaryPage = stagePattern->GetPrimaryPage().Upgrade();
    ASSERT_EQ(primaryPage, nullptr);
    auto firstNode = CreatePage();
    auto secondNode = CreatePage();

    /**
     * @tc.steps: step2. Create ParallelStageManager, trigger window size change.
     * @tc.expected: Stage enter split mode, and has no divider.
     */
    auto stageManager = AceType::MakeRefPtr<ParallelStageManager>(stageNode);
    ASSERT_NE(stageManager, nullptr);
    pipeline->stageManager_ = stageManager;
    pipeline->stageManager_->isForceSplit_ = true;
    pipeline->dipScale_ = PIPELINE_DIPSCALE;
    stagePattern->OnWindowSizeChanged(ENABLE_SPLIT_MODE_WIDTH, 600, WindowSizeChangeReason::RESIZE);
    ASSERT_TRUE(stagePattern->GetIsSplit());
    ASSERT_FALSE(stagePattern->HasDividerNode());
    ASSERT_TRUE(children.empty());

    /**
     * @tc.steps: step3. Calling the MovePageToFront function.
     * @tc.expected: return false.
     */
    ASSERT_FALSE(stageManager->MovePageToFront(firstNode));

    /**
     * @tc.steps: step4. Push firstPage, identify the page as the primarypage.
     * @tc.expected: stageNode has 3 child node: [0]dividerNode, [1]primaryPage, [2]placeHolderPage.
     */
    ASSERT_TRUE(stageManager->PushPage(firstNode));
    RefPtr<FrameNode> placeHolderPage = nullptr;
    int32_t placeHolderCreateCount = 0;
    IdentifyPageAsPrimaryPage(stageManager, firstNode, placeHolderPage, placeHolderCreateCount);
    ASSERT_EQ(children.size(), 3);

    /**
     * @tc.steps: step5. Recall MovePageToFront.
     * @tc.expected: return true.
     */
    ASSERT_TRUE(stageManager->MovePageToFront(firstNode));

    /**
     * @tc.steps: step6. ParallelStageManager another page and recall MovePageToFront with different params.
     * @tc.expected: always return true.
     */
    ASSERT_TRUE(stageManager->PushPage(secondNode));
    {
        ASSERT_EQ(children.size(), 3);
        auto iter = children.begin();
        auto child1 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child2 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child3 = AceType::DynamicCast<FrameNode>(*(iter++));
        ASSERT_EQ(child1, stagePattern->GetDividerNode());
        ASSERT_EQ(child2, firstNode);
        ASSERT_EQ(child3, secondNode);
        ASSERT_EQ(stagePattern->GetPrimaryPage().Upgrade(), firstNode);
    }
    ASSERT_TRUE(stageManager->MovePageToFront(firstNode, false, true));
    {
        ASSERT_EQ(children.size(), 4);
        auto iter = children.begin();
        auto child1 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child2 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child3 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child4 = AceType::DynamicCast<FrameNode>(*(iter++));
        ASSERT_EQ(child1, stagePattern->GetDividerNode());
        ASSERT_EQ(child2, secondNode);
        ASSERT_EQ(child3, firstNode);
        ASSERT_EQ(child4, placeHolderPage);
        ASSERT_EQ(stagePattern->GetPrimaryPage().Upgrade(), firstNode);
    }
    ASSERT_TRUE(stageManager->MovePageToFront(secondNode, true, false));
    {
        ASSERT_EQ(children.size(), 3);
        auto iter = children.begin();
        auto child1 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child2 = AceType::DynamicCast<FrameNode>(*(iter++));
        auto child3 = AceType::DynamicCast<FrameNode>(*(iter++));
        ASSERT_EQ(child1, stagePattern->GetDividerNode());
        ASSERT_EQ(child2, firstNode);
        ASSERT_EQ(child3, secondNode);
        ASSERT_EQ(stagePattern->GetPrimaryPage().Upgrade(), firstNode);
    }

    /**
     * @tc.steps: step7. Calling the GetLastPage function.
     * @tc.expected: The secondNode is last page.
     */
    ASSERT_EQ(stageManager->GetLastPage(), secondNode);
}
} // namespace OHOS::Ace::NG
