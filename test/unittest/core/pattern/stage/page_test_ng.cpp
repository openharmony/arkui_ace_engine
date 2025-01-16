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

#define private public
#define protected public

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/page_transition_effect.h"
#include "core/components_ng/pattern/stage/page_transition_model_ng.h"
#include "core/components_ng/pattern/stage/stage_layout_algorithm.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/pipeline/base/element_register.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

int $g_gpageOneIndex = 0;
int $g_gpageTwoIndex = 0;

class PageTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        auto pipeline = AceType::DynamicCast<NG::MockPipelineContext>(PipelineBase::GetCurrentContext());
        auto stageNode = FrameNode::CreateFrameNode(
            V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
        pipeline->sharedTransitionManager_ = AceType::MakeRefPtr<SharedOverlayManager>(stageNode);
        MockContainer::SetUp();
        EXPECT_CALL(*MockContainer::Current(), WindowIsShow())
            .Times(testing::AtLeast(1))
            .WillRepeatedly(Return(true));
        const int32_t containerId = 100;
        ContainerScope::UpdateCurrent(containerId);
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }

    void SetUp() {}

    void TearDown() {}
};

/**
 * @tc.name: PageTransitionTest001
 * @tc.desc: Test page transition in push animation
 * @tc.type: FUNC
 */
HWTEST_F(PageTestNg, PageTransitionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create stage node and stage manager
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    EXPECT_FALSE(stageNode == nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_FALSE(stageManager == nullptr);

    /**
     * @tc.steps: step2.create src page node and attach page node to stage
     */
    auto srcPage = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<PagePattern>(
        AceType::MakeRefPtr<PageInfo>()));
    EXPECT_FALSE(srcPage == nullptr);
    stageManager->SetSrcPage(srcPage);
    auto destPage = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 2, AceType::MakeRefPtr<PagePattern>(
        AceType::MakeRefPtr<PageInfo>()));
    EXPECT_FALSE(destPage == nullptr);

    /**
     * @tc.steps: step3.start page transition
     * @tc.expected: step3.src page is invisible
     */
    stageManager->PushPage(destPage, true, true);
    auto srcProperty = srcPage->GetLayoutProperty();
    EXPECT_FALSE(srcProperty == nullptr);
    EXPECT_FALSE(srcProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::INVISIBLE);
}

/**
 * @tc.name: PageTransitionTest001
 * @tc.desc: Test page transition in push animation
 * @tc.type: FUNC
 */
HWTEST_F(PageTestNg, PageTransitionTset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init stage param
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    EXPECT_FALSE(stageNode == nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_FALSE(stageManager == nullptr);
    auto srcPage = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<PagePattern>(
        AceType::MakeRefPtr<PageInfo>()));
    EXPECT_FALSE(srcPage == nullptr);

    /**
     * @tc.steps: step2.add srcPage to stageNode
     * @tc.expected: step2. current page is srcPage
     */
    auto destPage = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<PagePattern>(
        AceType::MakeRefPtr<PageInfo>()));
    EXPECT_FALSE(destPage == nullptr);
    stageManager->SetSrcPage(srcPage);
    stageManager->PushPage(srcPage);
    auto children = stageNode->GetChildren();
    EXPECT_TRUE(children.size() == 1);
    auto child = children.back();
    EXPECT_TRUE(child == srcPage);

    /**
     * @tc.steps: step2. add pageTwo to stage
     * @tc.expected: step2. current page is pageTwo
     */
    stageManager->SetSrcPage(srcPage);
    stageManager->PushPage(destPage);
    children = stageNode->GetChildren();
    EXPECT_TRUE(children.size() == 2);
    auto lastChild = children.back();
    EXPECT_TRUE(lastChild == destPage);

    /**
     * @tc.steps: step3. pop page
     * @tc.expected: step3. current page is srcPage
     */
    stageManager->SetSrcPage(destPage);
    stageManager->PopPage(srcPage);
    children = stageNode->GetChildren();
    EXPECT_TRUE(children.size() == 1);
    lastChild = children.back();
    EXPECT_TRUE(lastChild == srcPage);
}

/**
 * @tc.name: PageTransitionTset003
 * @tc.desc: Test page transition in push animation
 * @tc.type: FUNC
 */
HWTEST_F(PageTestNg, PageTransitionTset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init route page stack, add srcPage to stageNode
     * @tc.steps: step2. srcPage is added to stageNode
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    EXPECT_FALSE(stageNode == nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_FALSE(stageManager == nullptr);
    auto srcPage = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<PagePattern>(
        AceType::MakeRefPtr<PageInfo>()));
    EXPECT_FALSE(srcPage == nullptr);
    srcPage->MountToParent(stageNode);

    /**
     * @tc.steps: step2. push destPage to page stack
     * @tc.expected: step2. srcPage is invisible
     */
    auto destPage = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<PagePattern>(
        AceType::MakeRefPtr<PageInfo>()));
    EXPECT_FALSE(destPage == nullptr);
    stageManager->SetSrcPage(srcPage);
    stageManager->PushPage(destPage);
    EXPECT_TRUE(stageNode->GetChildren().size() == 2);
}

/**
 * @tc.name: PageTransitionTest004
 * @tc.desc: Test page pop to index
 * @tc.type: FUNC
 */
HWTEST_F(PageTestNg, PageTransitionTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.init stage
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 0, AceType::MakeRefPtr<StagePattern>());
    EXPECT_FALSE(stageNode == nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_FALSE(stageManager == nullptr);

    /**
     * @tc.steps: step2. push pageOne, pageTwo, pageThree to stage
     */
    auto pageOneInfo = AceType::MakeRefPtr<PageInfo>();
    EXPECT_FALSE(pageOneInfo == nullptr);
    pageOneInfo->url_ = "pages/pageOne";
    auto pageOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1,
        AceType::MakeRefPtr<PagePattern>(pageOneInfo));
    EXPECT_FALSE(pageOne == nullptr);
    auto pageTwoInfo = AceType::MakeRefPtr<PageInfo>();
    pageTwoInfo->url_ = "pages/pageTwo";
    auto pageTwo = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 2,
        AceType::MakeRefPtr<PagePattern>(pageTwoInfo));
    EXPECT_FALSE(pageTwo == nullptr);

    auto pageThreeInfo = AceType::MakeRefPtr<PageInfo>();
    EXPECT_FALSE(pageThreeInfo == nullptr);
    pageThreeInfo->url_ = "pages/pageThree";
    auto pageThree = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 3,
        AceType::MakeRefPtr<PagePattern>(pageThreeInfo));
    EXPECT_FALSE(pageThree == nullptr);

    stageManager->PushPage(pageOne);
    stageManager->SetSrcPage(pageOne);
    stageManager->PushPage(pageTwo);
    stageManager->SetSrcPage(pageTwo);
    stageManager->PushPage(pageThree);

    /**
     * @tc.steps: step3. set pageTwo is onAnimation, and pop page to pageOne
     * @tc.expected: step3. pageOne is visible, pageTwo is visible, pageThree is invisible
     */
    auto pagePattern = pageTwo->GetPattern<PagePattern>();
    EXPECT_FALSE(pagePattern == nullptr);
    pagePattern->isPageInTransition_ = true;
    stageManager->SetSrcPage(pageThree);
    stageManager->PopPageToIndex(0);

    auto pageOneProperty = pageOne->GetLayoutProperty();
    EXPECT_FALSE(pageOneProperty == nullptr);
    EXPECT_TRUE(pageOneProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE);

    EXPECT_FALSE(stageNode->GetChildIndex(pageTwo) == -1);

    EXPECT_TRUE(stageNode->GetChildIndex(pageThree) == -1);
}

/**
 * @tc.name: PageTransitionTest005
 * @tc.desc: Test clear page stack
 * @tc.type: FUNC
 */
HWTEST_F(PageTestNg, PageTransitionTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create stage node and stageManager
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, -1,
        AceType::MakeRefPtr<StagePattern>());
    EXPECT_FALSE(stageNode == nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_FALSE(stageManager == nullptr);

    /**
     * @tc.steps: step2. push pageOne, pageTwo, pageThree to stage
     */
    auto pageOneInfo = AceType::MakeRefPtr<PageInfo>();
    EXPECT_FALSE(pageOneInfo == nullptr);
    pageOneInfo->url_ = "pages/pageOne";
    auto pageOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1,
        AceType::MakeRefPtr<PagePattern>(pageOneInfo));
    EXPECT_FALSE(pageOne == nullptr);
    auto pageTwoInfo = AceType::MakeRefPtr<PageInfo>();
    pageTwoInfo->url_ = "pages/pageTwo";
    auto pageTwo = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 2,
        AceType::MakeRefPtr<PagePattern>(pageTwoInfo));
    EXPECT_FALSE(pageTwo == nullptr);

    auto pageThreeInfo = AceType::MakeRefPtr<PageInfo>();
    EXPECT_FALSE(pageThreeInfo == nullptr);
    pageThreeInfo->url_ = "pages/pageThree";
    auto pageThree = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 3,
        AceType::MakeRefPtr<PagePattern>(pageThreeInfo));
    EXPECT_FALSE(pageThree == nullptr);

    stageManager->PushPage(pageOne);
    stageManager->SetSrcPage(pageOne);
    stageManager->PushPage(pageTwo);
    stageManager->SetSrcPage(pageTwo);
    stageManager->PushPage(pageThree);

    /**
     * @tc.steps: step3.clear stack
     * @tc.expected: step3. pageThree is on tree, other page is not on tree
     */
    stageManager->CleanPageStack();
    EXPECT_FALSE(stageNode->GetChildIndex(pageThree) == -1);
    EXPECT_TRUE(stageNode->GetChildIndex(pageTwo) == -1);
    EXPECT_TRUE(stageNode->GetChildIndex(pageOne) == -1);
}

/**
 * @tc.name: PageTransitionTest006
 * @tc.desc: Test move page to front
 * @tc.type: FUNC
 */
HWTEST_F(PageTestNg, PageTransitionTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create stage node and stageManager
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, -1,
        AceType::MakeRefPtr<StagePattern>());
    EXPECT_FALSE(stageNode == nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_FALSE(stageManager == nullptr);

    /**
     * @tc.steps: step2. push pageOne, pageTwo, pageThree to stage
     */
    auto pageOneInfo = AceType::MakeRefPtr<PageInfo>();
    EXPECT_FALSE(pageOneInfo == nullptr);
    pageOneInfo->url_ = "pages/pageOne";
    auto pageOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1,
        AceType::MakeRefPtr<PagePattern>(pageOneInfo));
    EXPECT_FALSE(pageOne == nullptr);
    auto pageTwoInfo = AceType::MakeRefPtr<PageInfo>();
    pageTwoInfo->url_ = "pages/pageTwo";
    auto pageTwo = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 2,
        AceType::MakeRefPtr<PagePattern>(pageTwoInfo));
    EXPECT_FALSE(pageTwo == nullptr);

    auto pageThreeInfo = AceType::MakeRefPtr<PageInfo>();
    EXPECT_FALSE(pageThreeInfo == nullptr);
    pageThreeInfo->url_ = "pages/pageThree";
    auto pageThree = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 3,
        AceType::MakeRefPtr<PagePattern>(pageThreeInfo));
    EXPECT_FALSE(pageThree == nullptr);

    stageManager->PushPage(pageOne);
    stageManager->SetSrcPage(pageOne);
    stageManager->PushPage(pageTwo);
    stageManager->SetSrcPage(pageTwo);
    stageManager->PushPage(pageThree);

    /**
     * @tc.steps: step3.move pageOne to top
     * @tc.steps: step3. pageOne is visible, and pageOne position is top
     */
    stageManager->SetSrcPage(pageThree);
    stageManager->MovePageToFront(pageOne);
    auto pageOneLayoutProperty = pageOne->GetLayoutProperty();
    EXPECT_FALSE(pageOneLayoutProperty == nullptr);
    EXPECT_TRUE(pageOneLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE);
    auto pageThreeLayoutProperty = pageThree->GetLayoutProperty();
    EXPECT_FALSE(pageThreeLayoutProperty == nullptr);
    EXPECT_TRUE(pageThreeLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::INVISIBLE);
    auto maxPageIndex = 2;
    EXPECT_TRUE(stageNode->GetChildIndex(pageOne) == maxPageIndex);
    EXPECT_TRUE(stageNode->GetChildIndex(pageTwo) == 0);
    EXPECT_TRUE(stageNode->GetChildIndex(pageThree) == 1);
}

/**
 * @tc.name: PageTransitionTest007
 * @tc.desc: Test move page not exit to top
 * @tc.type: FUNC
 */
HWTEST_F(PageTestNg, PageTransitionTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create stage node and stageManager
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, -1,
        AceType::MakeRefPtr<StagePattern>());
    EXPECT_FALSE(stageNode == nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_FALSE(stageManager == nullptr);

    /**
     * @tc.steps: step2. push pageOne, pageTwo, pageThree to stage
     */
    auto pageOneInfo = AceType::MakeRefPtr<PageInfo>();
    EXPECT_FALSE(pageOneInfo == nullptr);
    pageOneInfo->url_ = "pages/pageOne";
    auto pageOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1,
        AceType::MakeRefPtr<PagePattern>(pageOneInfo));
    EXPECT_FALSE(pageOne == nullptr);
    auto pageTwoInfo = AceType::MakeRefPtr<PageInfo>();
    pageTwoInfo->url_ = "pages/pageTwo";
    auto pageTwo = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 2,
        AceType::MakeRefPtr<PagePattern>(pageTwoInfo));
    EXPECT_FALSE(pageTwo == nullptr);

    stageManager->PushPage(pageOne);
    stageManager->SetSrcPage(pageOne);
    stageManager->PushPage(pageTwo);

    /**
     * @tc.steps: step3. clear page stack
     */
    stageManager->SetSrcPage(pageTwo);
    stageManager->CleanPageStack();
    EXPECT_FALSE(stageNode->GetChildIndex(pageTwo) == -1);
    EXPECT_TRUE(stageNode->GetChildIndex(pageOne) == -1);

    /**
     * @tc.steps: step3.move pageOne to top
     * @tc.steps: step3. pageOne is not on main tree
     */
    stageManager->SetSrcPage(pageTwo);
    stageManager->MovePageToFront(pageOne);
    auto pageOneLayoutProperty = pageOne->GetLayoutProperty();
    EXPECT_FALSE(pageOneLayoutProperty == nullptr);
    EXPECT_TRUE(pageOneLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE);
    EXPECT_TRUE(stageNode->GetChildIndex(pageOne) == -1);
}

/**
 * @tc.name: PageLifecycleTest001
 * @tc.desc: Test move page not exit to top
 * @tc.type: FUNC
 */
HWTEST_F(PageTestNg, PageLifecycleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create stage node
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, -1,
        AceType::MakeRefPtr<StagePattern>());
    EXPECT_FALSE(stageNode == nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_FALSE(stageManager == nullptr);

    /**
     * @tc.steps:step1.create pageOne and pageTwo, and set lifecycle callback
     */
    auto pageInfo = AceType::MakeRefPtr<PageInfo>();
    EXPECT_FALSE(pageInfo == nullptr);
    pageInfo->url_ = "pages/PageOne";
    auto pageOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 0,
        AceType::MakeRefPtr<PagePattern>(pageInfo));
    EXPECT_FALSE(pageOne == nullptr);
    auto pagePattern = pageOne->GetPattern<PagePattern>();
    EXPECT_FALSE(pagePattern == nullptr);
    pagePattern->isRenderDone_ = true;
    pagePattern->onPageShow_ = []() {
        $g_gpageOneIndex++;
    };
    pagePattern->onPageHide_ = []() {
        $g_gpageOneIndex--;
    };
    /**
     * @tc.steps: step2. push pageOne
     * @tc.expected: step2. fire pageShow
     */
    stageManager->PushPage(pageOne);
    EXPECT_TRUE($g_gpageOneIndex == 1);

    /**
     * @tc.steps: step3. create pageTwo and set pageTwo lifecycle
     */
    auto pageTwoInfo = AceType::MakeRefPtr<PageInfo>();
    pageTwoInfo->url_ = "pages/pageTwo";
    auto pageTwo = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<PagePattern>(pageTwoInfo));
    EXPECT_FALSE(pageTwo == nullptr);
    auto pageTwoPattern = pageTwo->GetPattern<PagePattern>();
    EXPECT_FALSE(pageTwoPattern == nullptr);
    pageTwoPattern->isRenderDone_ = true;
    pageTwoPattern->onPageShow_ = []() {
        $g_gpageTwoIndex ++;
    };
    pageTwoPattern->onPageHide_ = []() {
        $g_gpageTwoIndex--;
    };

    /**
     * @tc.steps: step4. push pageTwo
     * @tc.expected: step4. pageOneIndex is 0, pageTwoIndex is 1
     */
    stageManager->SetSrcPage(pageOne);
    stageManager->PushPage(pageTwo);
    EXPECT_TRUE($g_gpageOneIndex == 0);
    EXPECT_EQ($g_gpageTwoIndex, 1);
}

/**
 * @tc.name: PageLifecycleTest002
 * @tc.desc: Test pop lifecycle
 * @tc.type: FUNC
 */
HWTEST_F(PageTestNg, PageLifecycleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create stage node
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, -1,
        AceType::MakeRefPtr<StagePattern>());
    EXPECT_FALSE(stageNode == nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_FALSE(stageManager == nullptr);
    $g_gpageOneIndex = 0;
    $g_gpageTwoIndex = 0;

    /**
     * @tc.steps:step1.create pageOne and pageTwo, and set lifecycle callback
     */
    auto pageInfo = AceType::MakeRefPtr<PageInfo>();
    EXPECT_FALSE(pageInfo == nullptr);
    pageInfo->url_ = "pages/PageOne";
    auto pageOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 0,
        AceType::MakeRefPtr<PagePattern>(pageInfo));
    EXPECT_FALSE(pageOne == nullptr);
    auto pagePattern = pageOne->GetPattern<PagePattern>();
    EXPECT_FALSE(pagePattern == nullptr);
    pagePattern->isRenderDone_ = true;
    pagePattern->onPageShow_ = []() {
        $g_gpageOneIndex++;
    };
    pagePattern->onPageHide_ = []() {
        $g_gpageOneIndex--;
    };
    /**
     * @tc.steps: step2. push pageOne
     * @tc.expected: step2. fire pageShow
     */
    stageManager->PushPage(pageOne);
    EXPECT_TRUE($g_gpageOneIndex == 1);

    /**
     * @tc.steps: step3. create pageTwo and set pageTwo lifecycle
     */
    auto pageTwoInfo = AceType::MakeRefPtr<PageInfo>();
    pageTwoInfo->url_ = "pages/pageTwo";
    auto pageTwo = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<PagePattern>(pageTwoInfo));
    EXPECT_FALSE(pageTwo == nullptr);
    auto pageTwoPattern = pageTwo->GetPattern<PagePattern>();
    EXPECT_FALSE(pageTwoPattern == nullptr);
    pageTwoPattern->isRenderDone_ = true;
    pageTwoPattern->onPageShow_ = []() {
        $g_gpageTwoIndex ++;
    };
    pageTwoPattern->onPageHide_ = []() {
        $g_gpageTwoIndex--;
    };

    /**
     * @tc.steps: step4. push pageTwo
     * @tc.expected: step4. pageOneIndex is 0, pageTwoIndex is 1
     */
    stageManager->SetSrcPage(pageOne);
    stageManager->PushPage(pageTwo);
    EXPECT_TRUE($g_gpageOneIndex == 0);
    EXPECT_EQ($g_gpageTwoIndex, 1);

    /**
     * @tc.steps: step5. pop page
     * @tc.expected: step5. pop page
     */
    stageManager->SetSrcPage(pageTwo);
    stageManager->PopPage(pageOne);
    EXPECT_TRUE($g_gpageOneIndex == 1);
    EXPECT_TRUE($g_gpageTwoIndex == 0);
}

/**
 * @tc.name: PageLifecycleTest003
 * @tc.desc: Test replace lifecycle
 * @tc.type: FUNC
 */
HWTEST_F(PageTestNg, PageLifecycleTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create stage node
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, -1,
        AceType::MakeRefPtr<StagePattern>());
    EXPECT_FALSE(stageNode == nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_FALSE(stageManager == nullptr);
    $g_gpageOneIndex = 0;
    $g_gpageTwoIndex = 0;

    /**
     * @tc.steps:step1.create pageOne and pageTwo, and set lifecycle callback
     */
    auto pageInfo = AceType::MakeRefPtr<PageInfo>();
    EXPECT_FALSE(pageInfo == nullptr);
    pageInfo->url_ = "pages/PageOne";
    auto pageOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 0,
        AceType::MakeRefPtr<PagePattern>(pageInfo));
    EXPECT_FALSE(pageOne == nullptr);
    auto pagePattern = pageOne->GetPattern<PagePattern>();
    EXPECT_FALSE(pagePattern == nullptr);
    pagePattern->isRenderDone_ = true;
    pagePattern->onPageShow_ = []() {
        $g_gpageOneIndex++;
    };
    pagePattern->onPageHide_ = []() {
        $g_gpageOneIndex--;
    };
    /**
     * @tc.steps: step2. push pageOne
     * @tc.expected: step2. fire pageShow
     */
    stageManager->PushPage(pageOne);
    EXPECT_TRUE($g_gpageOneIndex == 1);

    /**
     * @tc.steps: step3. create pageTwo and set pageTwo lifecycle
     */
    auto pageTwoInfo = AceType::MakeRefPtr<PageInfo>();
    pageTwoInfo->url_ = "pages/pageTwo";
    auto pageTwo = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<PagePattern>(pageTwoInfo));
    EXPECT_FALSE(pageTwo == nullptr);
    auto pageTwoPattern = pageTwo->GetPattern<PagePattern>();
    EXPECT_FALSE(pageTwoPattern == nullptr);
    pageTwoPattern->isRenderDone_ = true;
    pageTwoPattern->onPageShow_ = []() {
        $g_gpageTwoIndex ++;
    };
    pageTwoPattern->onPageHide_ = []() {
        $g_gpageTwoIndex--;
    };

    /**
     * @tc.steps: step4. replace pageOne lifecycle
     * @tc.expected: step4. pageOneIndex is 0, pageTwoIndex is 1
     */
    stageManager->PushPage(pageOne, true, false);
    pageTwo->MovePosition(1);
    stageManager->PopPage(pageTwo, false, false);
    EXPECT_TRUE($g_gpageOneIndex == 1);
    EXPECT_TRUE($g_gpageTwoIndex == 0);
}

/**
 * @tc.name: PageLifecycleTest004
 * @tc.desc: Test movePageToFront lifecycle
 * @tc.type: FUNC
 */
HWTEST_F(PageTestNg, PageLifecycleTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create stage node
     */
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, -1,
        AceType::MakeRefPtr<StagePattern>());
    EXPECT_FALSE(stageNode == nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    EXPECT_FALSE(stageManager == nullptr);
    $g_gpageOneIndex = 0;
    $g_gpageTwoIndex = 0;

    /**
     * @tc.steps:step1.create pageOne and pageTwo, and set lifecycle callback
     */
    auto pageInfo = AceType::MakeRefPtr<PageInfo>();
    EXPECT_FALSE(pageInfo == nullptr);
    pageInfo->url_ = "pages/PageOne";
    auto pageOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 0,
        AceType::MakeRefPtr<PagePattern>(pageInfo));
    EXPECT_FALSE(pageOne == nullptr);
    auto pagePattern = pageOne->GetPattern<PagePattern>();
    EXPECT_FALSE(pagePattern == nullptr);
    pagePattern->isRenderDone_ = true;
    pagePattern->onPageShow_ = []() {
        $g_gpageOneIndex++;
    };
    pagePattern->onPageHide_ = []() {
        $g_gpageOneIndex--;
    };
    /**
     * @tc.steps: step2. push pageOne
     * @tc.expected: step2. fire pageShow
     */
    stageManager->PushPage(pageOne);
    EXPECT_TRUE($g_gpageOneIndex == 1);

    /**
     * @tc.steps: step3. create pageTwo and set pageTwo lifecycle
     */
    auto pageTwoInfo = AceType::MakeRefPtr<PageInfo>();
    pageTwoInfo->url_ = "pages/pageTwo";
    auto pageTwo = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<PagePattern>(pageTwoInfo));
    EXPECT_FALSE(pageTwo == nullptr);
    auto pageTwoPattern = pageTwo->GetPattern<PagePattern>();
    EXPECT_FALSE(pageTwoPattern == nullptr);
    pageTwoPattern->isRenderDone_ = true;
    pageTwoPattern->onPageShow_ = []() {
        $g_gpageTwoIndex ++;
    };
    pageTwoPattern->onPageHide_ = []() {
        $g_gpageTwoIndex--;
    };

    /**
     * @tc.steps: step4. push page two
     */
    stageManager->SetSrcPage(pageOne);
    stageManager->PushPage(pageTwo, true, false);
    EXPECT_TRUE($g_gpageOneIndex == 0);
    EXPECT_TRUE($g_gpageTwoIndex == 1);

    /**
     * @tc.steps: step5. move page to front
     */
    stageManager->SetSrcPage(pageTwo);
    stageManager->MovePageToFront(pageOne, true, true);
    EXPECT_TRUE($g_gpageOneIndex == 1);
    EXPECT_TRUE($g_gpageTwoIndex == 0);
}
}