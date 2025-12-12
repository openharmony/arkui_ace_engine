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
}

void TransparentNodeDetectorTestNg::TearDownTestSuite()
{
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
    EXPECT_TRUE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId, isNavigation));
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
    EXPECT_TRUE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId, isNavigation));
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
    EXPECT_FALSE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId, isNavigation));
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
    EXPECT_FALSE(TransparentNodeDetector::GetInstance().CheckWindowTransparent(root, containerId, isNavigation));
}
} // namespace OHOS::Ace::NG