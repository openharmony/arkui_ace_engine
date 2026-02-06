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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/transparent_node_detector.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class TransparentNodeDetectorTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void TransparentNodeDetectorTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrentContext();
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(true);
    MockPipelineContext::GetCurrent()->SetTaskExecutor(taskExecutor);
}

void TransparentNodeDetectorTestNg::TearDownTestSuite()
{
    MockPipelineContext::GetCurrent()->SetTaskExecutor(nullptr);
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: TransparentNodeDetectorTestNg001
 * @tc.desc: CheckWindowTransparent test isNavigation is true
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg001, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    bool isNavigation = true;
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto containerId = pipelineContext->GetInstanceId();

    auto stageNode = FrameNode::CreateFrameNode("testFrameNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stageNode->AddChild(firstNode);
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); }
    );
    RefPtr<NavigationPattern> navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    firstNode->AddChild(navigationGroupNode);

    auto navDestinationNode1 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 21, AceType::MakeRefPtr<Pattern>(), true);
    auto navDestinationNode2 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, AceType::MakeRefPtr<Pattern>(), true);
    auto navDestinationNode3 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 23, AceType::MakeRefPtr<Pattern>(), true);
    auto navDestinationNode4 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 24, AceType::MakeRefPtr<Pattern>(), true);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", navDestinationNode1));
    navPathList.emplace_back(std::make_pair("pageTwo", navDestinationNode2));
    navPathList.emplace_back(std::make_pair("pageThree", navDestinationNode3));
    navPathList.emplace_back(std::make_pair("pageFour", navDestinationNode4));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    root->AddChild(stageNode);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext, nullptr);
    renderContext->rect_ = { 0.0f, 0.0f, 0.0f, 0.0f };
    navDestinationNode4->renderContext_ = renderContext;
    auto layoutProperty = navDestinationNode4->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    EXPECT_FALSE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        0, 0, 0, isNavigation));
}

/**
 * @tc.name: TransparentNodeDetectorTestNg002
 * @tc.desc: CheckWindowTransparent test isNavigation is false
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg002, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    bool isNavigation = false;
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto containerId = pipelineContext->GetInstanceId();

    auto stageNode = FrameNode::CreateFrameNode("stageNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode("pageNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto jsViewNode = FrameNode::CreateFrameNode("jsview", 0, AceType::MakeRefPtr<StagePattern>());
    auto columnNode = FrameNode::CreateFrameNode("column", 0, AceType::MakeRefPtr<StagePattern>());
    auto TextNode = FrameNode::CreateFrameNode("text", 0, AceType::MakeRefPtr<StagePattern>());
    root->AddChild(stageNode);
    stageNode->AddChild(pageNode);
    pageNode->AddChild(jsViewNode);
    jsViewNode->AddChild(columnNode);
    columnNode->AddChild(TextNode);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext, nullptr);
    renderContext->rect_ = { 0.0f, 0.0f, 0.0f, 0.0f };
    columnNode->renderContext_ = renderContext;
    auto layoutProperty = columnNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    EXPECT_TRUE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        0, 0, 0, isNavigation));
}

/**
 * @tc.name: TransparentNodeDetectorTestNg003
 * @tc.desc: CheckWindowTransparent test isNavigation is false
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg003, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    bool isNavigation = false;
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto containerId = pipelineContext->GetInstanceId();

    auto stageNode = FrameNode::CreateFrameNode("stageNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode("pageNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto jsViewNode = FrameNode::CreateFrameNode("jsview", 0, AceType::MakeRefPtr<StagePattern>());
    auto columnNode = FrameNode::CreateFrameNode("column", 0, AceType::MakeRefPtr<StagePattern>());
    auto TextNode = FrameNode::CreateFrameNode("text", 0, AceType::MakeRefPtr<StagePattern>());
    root->AddChild(stageNode);
    stageNode->AddChild(pageNode);
    pageNode->AddChild(jsViewNode);
    jsViewNode->AddChild(columnNode);
    columnNode->AddChild(TextNode);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext, nullptr);
    renderContext->rect_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    columnNode->renderContext_ = renderContext;
    auto layoutProperty = columnNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    EXPECT_FALSE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        0, 0, 0, isNavigation));
}

/**
 * @tc.name: TransparentNodeDetectorTestNg004
 * @tc.desc: CheckWindowTransparent test isNavigation is true
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg004, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    bool isNavigation = true;
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto containerId = pipelineContext->GetInstanceId();

    auto stageNode = FrameNode::CreateFrameNode("testFrameNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stageNode->AddChild(firstNode);
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); }
    );
    RefPtr<NavigationPattern> navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    firstNode->AddChild(navigationGroupNode);

    auto navDestinationNode1 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 21, AceType::MakeRefPtr<Pattern>(), true);
    auto navDestinationNode2 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, AceType::MakeRefPtr<Pattern>(), true);
    auto navDestinationNode3 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 23, AceType::MakeRefPtr<Pattern>(), true);
    auto navDestinationNode4 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 24, AceType::MakeRefPtr<Pattern>(), true);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", navDestinationNode1));
    navPathList.emplace_back(std::make_pair("pageTwo", navDestinationNode2));
    navPathList.emplace_back(std::make_pair("pageThree", navDestinationNode3));
    navPathList.emplace_back(std::make_pair("pageFour", navDestinationNode4));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    root->AddChild(stageNode);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext, nullptr);
    renderContext->rect_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    navDestinationNode4->renderContext_ = renderContext;
    auto layoutProperty = navDestinationNode4->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    EXPECT_FALSE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        0, 0, 0, isNavigation));
}

/**
 * @tc.name: TransparentNodeDetectorTestNg005
 * @tc.desc: PostCheckNodeTransparentTask test
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg005, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto stageNode = FrameNode::CreateFrameNode("stageNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode("pageNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto jsViewNode = FrameNode::CreateFrameNode("jsview", 0, AceType::MakeRefPtr<StagePattern>());
    auto columnNode = FrameNode::CreateFrameNode("column", 0, AceType::MakeRefPtr<StagePattern>());
    auto TextNode = FrameNode::CreateFrameNode("text", 0, AceType::MakeRefPtr<StagePattern>());

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    root->AddChild(stageNode);
    stageNode->AddChild(pageNode);
    pageNode->AddChild(jsViewNode);
    jsViewNode->AddChild(columnNode);
    columnNode->AddChild(TextNode);

    NG::TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(root, "startUrl");
    EXPECT_NE(context->GetTaskExecutor(), nullptr);
}


/**
 * @tc.name: TransparentNodeDetectorTestNg006
 * @tc.desc: PostCheckNodeTransparentTask test post task
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg006, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto stageNode = FrameNode::CreateFrameNode("stageNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode("pageNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto jsViewNode = FrameNode::CreateFrameNode("jsview", 0, AceType::MakeRefPtr<StagePattern>());
    auto columnNode = FrameNode::CreateFrameNode("column", 0, AceType::MakeRefPtr<StagePattern>());
    auto TextNode = FrameNode::CreateFrameNode("text", 0, AceType::MakeRefPtr<StagePattern>());

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    root->AddChild(stageNode);
    stageNode->AddChild(pageNode);
    pageNode->AddChild(jsViewNode);
    jsViewNode->AddChild(columnNode);
    columnNode->AddChild(TextNode);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext, nullptr);
    renderContext->rect_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    columnNode->renderContext_ = renderContext;
    auto layoutProperty = columnNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    context->onFocus_ = true;
    NG::TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(root, "startUr2");
    EXPECT_EQ(context->GetTaskExecutor(), 1);
}

/**
 * @tc.name: TransparentNodeDetectorTestNg007
 * @tc.desc: CheckWindowTransparent test with null root
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg007, TestSize.Level1)
{
    RefPtr<FrameNode> root = nullptr;
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();

    EXPECT_FALSE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        false, false, false, false));
}

/**
 * @tc.name: TransparentNodeDetectorTestNg008
 * @tc.desc: CheckWindowTransparent test with isUECWindow true, size below threshold
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg008, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();

    // Set root size smaller than device size * 0.85
    MockPipelineContext::GetCurrent()->SetRootSize(500, 500);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext, nullptr);
    renderContext->rect_ = { 0.0f, 0.0f, 0.0f, 0.0f };
    root->renderContext_ = renderContext;

    EXPECT_FALSE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        true, false, false, false));
}

/**
 * @tc.name: TransparentNodeDetectorTestNg009
 * @tc.desc: CheckWindowTransparent test with isSubWindow true, size below threshold
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg009, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();

    // Set root size smaller than device size * 0.85
    MockPipelineContext::GetCurrent()->SetRootSize(500, 500);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext, nullptr);
    renderContext->rect_ = { 0.0f, 0.0f, 0.0f, 0.0f };
    root->renderContext_ = renderContext;

    EXPECT_FALSE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        false, true, false, false));
}

/**
 * @tc.name: TransparentNodeDetectorTestNg010
 * @tc.desc: CheckWindowTransparent test with isDialogWindow true, size below threshold
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg010, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();

    // Set root size smaller than device size * 0.85
    MockPipelineContext::GetCurrent()->SetRootSize(500, 500);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext, nullptr);
    renderContext->rect_ = { 0.0f, 0.0f, 0.0f, 0.0f };
    root->renderContext_ = renderContext;

    EXPECT_FALSE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        false, false, true, false));
}

/**
 * @tc.name: TransparentNodeDetectorTestNg011
 * @tc.desc: CheckWindowTransparent test with isUECWindow true, size meets threshold but not transparent
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg011, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();

    // Set root size to meet threshold
    MockPipelineContext::GetCurrent()->SetRootSize(720, 1280);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext, nullptr);
    renderContext->rect_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    root->renderContext_ = renderContext;
    auto layoutProperty = root->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);

    EXPECT_TRUE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        true, false, false, false));
}

/**
 * @tc.name: TransparentNodeDetectorTestNg012
 * @tc.desc: CheckWindowTransparent test with isUECWindow true, size meets threshold and transparent
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg012, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();

    // Set root size to meet threshold
    MockPipelineContext::GetCurrent()->SetRootSize(720, 1280);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext, nullptr);
    renderContext->rect_ = { 0.0f, 0.0f, 0.0f, 0.0f };
    root->renderContext_ = renderContext;

    EXPECT_TRUE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        true, false, false, false));
}

/**
 * @tc.name: TransparentNodeDetectorTestNg013
 * @tc.desc: CheckWindowTransparent test with isNavigation true and empty navDesNodes
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg013, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    bool isNavigation = true;
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();

    auto stageNode = FrameNode::CreateFrameNode("testFrameNode", 0, AceType::MakeRefPtr<StagePattern>());
    root->AddChild(stageNode);

    EXPECT_FALSE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        false, false, false, isNavigation));
}

/**
 * @tc.name: TransparentNodeDetectorTestNg014
 * @tc.desc: PostCheckNodeTransparentTask test with detectCount exceeding MAX_DETECT_COUNT
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg014, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto stageNode = FrameNode::CreateFrameNode("stageNode", 0, AceType::MakeRefPtr<StagePattern>());
    root->AddChild(stageNode);

    NG::TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(root, "testUrl",
        false, TransparentNodeDetector::MAX_DETECT_COUNT + 1);
    // Should return early without posting task
}

/**
 * @tc.name: TransparentNodeDetectorTestNg015
 * @tc.desc: PostCheckNodeTransparentTask test with detectCount equal to 0
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg015, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto stageNode = FrameNode::CreateFrameNode("stageNode", 0, AceType::MakeRefPtr<StagePattern>());
    root->AddChild(stageNode);

    NG::TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(root, "testUrl",
        false, 0);
    // Should return early without posting task
}

/**
 * @tc.name: TransparentNodeDetectorTestNg016
 * @tc.desc: PostCheckNodeTransparentTask test with null node
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg016, TestSize.Level1)
{
    RefPtr<FrameNode> root = nullptr;

    NG::TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(root, "testUrl",
        false, 1);
    // Should return early without posting task
}

/**
 * @tc.name: TransparentNodeDetectorTestNg017
 * @tc.desc: PostCheckNodeTransparentTask test with window not focused
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg017, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    auto stageNode = FrameNode::CreateFrameNode("stageNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode("pageNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto jsViewNode = FrameNode::CreateFrameNode("jsview", 0, AceType::MakeRefPtr<StagePattern>());
    auto columnNode = FrameNode::CreateFrameNode("column", 0, AceType::MakeRefPtr<StagePattern>());
    auto TextNode = FrameNode::CreateFrameNode("text", 0, AceType::MakeRefPtr<StagePattern>());

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    root->AddChild(stageNode);
    stageNode->AddChild(pageNode);
    pageNode->AddChild(jsViewNode);
    jsViewNode->AddChild(columnNode);
    columnNode->AddChild(TextNode);

    // Set window to not focused
    context->WindowFocus(false);

    NG::TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(root, "testUrl",
        false, 1);
    // Should return early without posting task
}

/**
 * @tc.name: TransparentNodeDetectorTestNg018
 * @tc.desc: CheckWindowTransparent test with isNavigation true and transparent rootNodes
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg018, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    bool isNavigation = true;
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto containerId = pipelineContext->GetInstanceId();

    auto stageNode = FrameNode::CreateFrameNode("testFrameNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto firstNode =
        FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stageNode->AddChild(firstNode);
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); }
    );
    RefPtr<NavigationPattern> navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    firstNode->AddChild(navigationGroupNode);

    auto navDestinationNode1 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 21, AceType::MakeRefPtr<Pattern>(), true);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", navDestinationNode1));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    root->AddChild(stageNode);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext, nullptr);
    renderContext->rect_ = { 0.0f, 0.0f, 0.0f, 0.0f };
    navDestinationNode1->renderContext_ = renderContext;

    EXPECT_FALSE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        false, false, false, isNavigation));
}

/**
 * @tc.name: TransparentNodeDetectorTestNg019
 * @tc.desc: CheckWindowTransparent test with non-navigation and transparent rootNodeCurrentPage
 * @tc.type: FUNC
 */
HWTEST_F(TransparentNodeDetectorTestNg, TransparentNodeDetectorTestNg019, TestSize.Level1)
{
    const RefPtr<FrameNode> root = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>(), true);
    bool isNavigation = false;
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();

    auto stageNode = FrameNode::CreateFrameNode("stageNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode("pageNode", 0, AceType::MakeRefPtr<StagePattern>());
    auto jsViewNode = FrameNode::CreateFrameNode("jsview", 0, AceType::MakeRefPtr<StagePattern>());
    auto columnNode = FrameNode::CreateFrameNode("column", 0, AceType::MakeRefPtr<StagePattern>());
    auto TextNode = FrameNode::CreateFrameNode("text", 0, AceType::MakeRefPtr<StagePattern>());
    root->AddChild(stageNode);
    stageNode->AddChild(pageNode);
    pageNode->AddChild(jsViewNode);
    jsViewNode->AddChild(columnNode);
    columnNode->AddChild(TextNode);

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(renderContext, nullptr);
    renderContext->rect_ = { 0.0f, 0.0f, 0.0f, 0.0f };
    columnNode->renderContext_ = renderContext;

    EXPECT_TRUE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId,
        false, false, false, isNavigation));
}
} // namespace OHOS::Ace::NG