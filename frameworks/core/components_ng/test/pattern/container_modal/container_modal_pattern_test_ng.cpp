/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "base/log/log_wrapper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class ContainerModalPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ContainerModalPatternTestNg::SetUpTestCase()
{
    const std::string tag = "test";
    const auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, 0, AceType::MakeRefPtr<Pattern>());
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNode);
    MockPipelineBase::SetUp();
}

void ContainerModalPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: ContainerModalPatternTest001
 * @tc.desc: Test IsMeasureBoundary and IsAtomicNode.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternTestNg, ContainerModalPatternTest001, TestSize.Level1)
{
    auto containerModalPattern = AceType::MakeRefPtr<ContainerModalPattern>();
    EXPECT_TRUE(containerModalPattern->IsMeasureBoundary());
    EXPECT_FALSE(containerModalPattern->IsAtomicNode());
}

/**
 * @tc.name: ContainerModalPatternTest002
 * @tc.desc: Test OnWindowFocused and OnWindowUnfocused.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternTestNg, ContainerModalPatternTest002, TestSize.Level1)
{
    auto containerModalPattern = AceType::MakeRefPtr<ContainerModalPattern>();
    std::string tag = "test";
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, 0, AceType::MakeRefPtr<Pattern>());
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNode);
    EXPECT_NE(frameNode, nullptr);

    auto frameNodeChild = AceType::MakeRefPtr<FrameNode>(tag, 1, AceType::MakeRefPtr<Pattern>());
    frameNodeChild->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_NE(frameNodeChild, nullptr);
    frameNode->AddChild(frameNodeChild);
    containerModalPattern->OnWindowFocused();
    containerModalPattern->OnWindowUnfocused();
}

/**
 * @tc.name: ContainerModalPatternTest003
 * @tc.desc: Test InitContainerEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternTestNg, ContainerModalPatternTest003, TestSize.Level1)
{
    std::string tag = "test";
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, 0, AceType::MakeRefPtr<Pattern>());
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNode);
    EXPECT_NE(frameNode, nullptr);

    auto frameNodeChild = AceType::MakeRefPtr<FrameNode>(tag, 1, AceType::MakeRefPtr<Pattern>());
    frameNodeChild->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_NE(frameNodeChild, nullptr);
    frameNode->AddChild(frameNodeChild);

    ContainerModalPattern containerModalPattern;
    containerModalPattern.AttachToFrameNode(frameNode);
    containerModalPattern.InitContainerEvent();
}

/**
 * @tc.name: ContainerModalPatternTest004
 * @tc.desc: Test ShowTitle is true.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternTestNg, ContainerModalPatternTest004, TestSize.Level1)
{
    std::string tag = "test";
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, 0, AceType::MakeRefPtr<Pattern>());
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNode);
    EXPECT_NE(frameNode, nullptr);

    auto frameNodeChild = AceType::MakeRefPtr<FrameNode>(tag, 1, AceType::MakeRefPtr<Pattern>());
    frameNodeChild->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_NE(frameNodeChild, nullptr);

    auto frameNodeChildTwo = AceType::MakeRefPtr<FrameNode>(tag, 2, AceType::MakeRefPtr<Pattern>());
    frameNodeChildTwo->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_NE(frameNodeChildTwo, nullptr);

    frameNode->AddChild(frameNodeChild);
    frameNode->AddChild(frameNodeChildTwo);
    auto containerNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    EXPECT_NE(containerNode, nullptr);
    EXPECT_NE(AceType::DynamicCast<FrameNode>(frameNode->GetChildren().back()), nullptr);

    ContainerModalPattern containerModalPattern;
    containerModalPattern.AttachToFrameNode(frameNode);
    containerModalPattern.ShowTitle(true);
}

/**
 * @tc.name: ContainerModalPatternTest005
 * @tc.desc: Test ShowTitle is false.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternTestNg, ContainerModalPatternTest005, TestSize.Level1)
{
    std::string tag = "test";
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, 0, AceType::MakeRefPtr<Pattern>());
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNode);
    EXPECT_NE(frameNode, nullptr);

    auto frameNodeChild = AceType::MakeRefPtr<FrameNode>(tag, 1, AceType::MakeRefPtr<Pattern>());
    frameNodeChild->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_NE(frameNodeChild, nullptr);

    auto frameNodeChildTwo = AceType::MakeRefPtr<FrameNode>(tag, 2, AceType::MakeRefPtr<Pattern>());
    frameNodeChildTwo->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_NE(frameNodeChildTwo, nullptr);

    frameNode->AddChild(frameNodeChild);
    frameNode->AddChild(frameNodeChildTwo);
    auto containerNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    EXPECT_NE(containerNode, nullptr);
    EXPECT_NE(AceType::DynamicCast<FrameNode>(frameNode->GetChildren().back()), nullptr);

    ContainerModalPattern containerModalPattern;
    containerModalPattern.AttachToFrameNode(frameNode);
    containerModalPattern.ShowTitle(false);
}

/**
 * @tc.name: ContainerModalPatternTest006
 * @tc.desc: Test ShowTitle CHECK_NULL_VOID.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternTestNg, ContainerModalPatternTest006, TestSize.Level1)
{
    ContainerModalPattern containerModalPattern;
    containerModalPattern.ShowTitle(false);
    std::string tag = "test";
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, 0, AceType::MakeRefPtr<Pattern>());
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNode);

    EXPECT_NE(frameNode, nullptr);
    containerModalPattern.AttachToFrameNode(frameNode);
    containerModalPattern.ShowTitle(false);

    auto frameNodeChild = AceType::MakeRefPtr<FrameNode>(tag, 1, AceType::MakeRefPtr<Pattern>());
    frameNodeChild->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_NE(frameNodeChild, nullptr);

    auto frameNodeChildTwo = AceType::MakeRefPtr<FrameNode>(tag, 2, AceType::MakeRefPtr<Pattern>());
    frameNodeChildTwo->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    EXPECT_NE(frameNodeChildTwo, nullptr);

    frameNode->AddChild(frameNodeChild);
    frameNode->AddChild(frameNodeChildTwo);
    auto containerNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    EXPECT_NE(containerNode, nullptr);
    EXPECT_NE(AceType::DynamicCast<FrameNode>(frameNode->GetChildren().back()), nullptr);

    containerModalPattern.AttachToFrameNode(frameNode);
    containerModalPattern.ShowTitle(false);
}

/**
 * @tc.name: ContainerModalPatternTest007
 * @tc.desc: Test SetAppIcon.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternTestNg, ContainerModalPatternTest007, TestSize.Level1)
{
    std::string tag = "test";
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, 0, AceType::MakeRefPtr<Pattern>());
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNode);
    EXPECT_NE(frameNode, nullptr);

    auto frameNodeChild = AceType::MakeRefPtr<FrameNode>(tag, 1, AceType::MakeRefPtr<Pattern>());
    frameNodeChild->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNodeChild);
    EXPECT_NE(frameNodeChild, nullptr);

    auto frameNodeChildTwo = AceType::MakeRefPtr<FrameNode>(tag, 2, AceType::MakeRefPtr<Pattern>());
    frameNodeChildTwo->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNodeChildTwo);
    EXPECT_NE(frameNodeChildTwo, nullptr);

    frameNode->AddChild(frameNodeChild);
    frameNodeChild->AddChild(frameNodeChildTwo);
    auto containerNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    EXPECT_NE(AceType::DynamicCast<FrameNode>(frameNode->GetChildren().back()), nullptr);

    ContainerModalPattern containerModalPattern;
    containerModalPattern.AttachToFrameNode(frameNode);

    RefPtr<PixelMap> pixelMap;
    containerModalPattern.SetAppIcon(pixelMap);
}

/**
 * @tc.name: ContainerModalPatternTest008
 * @tc.desc: Test OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternTestNg, ContainerModalPatternTest008, TestSize.Level1)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto containerModalPattern = AceType::MakeRefPtr<ContainerModalPattern>();
    containerModalPattern->OnModifyDone();
}

/**
 * @tc.name: ContainerModalPatternTest009
 * @tc.desc: Test ChangeFloatingTitle.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternTestNg, ContainerModalPatternTest009, TestSize.Level1)
{
    auto containerModalPattern = AceType::MakeRefPtr<ContainerModalPattern>();

    const std::string tag = "test";
    containerModalPattern->frameNode_ = AceType::MakeRefPtr<FrameNode>(tag, 0, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> result = containerModalPattern->GetHost();
    containerModalPattern->ChangeFloatingTitle(result, true);
}

/**
 * @tc.name: ContainerModalPatternTest010
 * @tc.desc: Test ChangeTitleButtonIcon.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalPatternTestNg, ContainerModalPatternTest010, TestSize.Level1)
{
    std::string tag = "Button";
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, 0, AceType::MakeRefPtr<Pattern>());
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNode);
    EXPECT_NE(frameNode, nullptr);

    auto containerModalPattern = AceType::MakeRefPtr<ContainerModalPattern>();
    containerModalPattern->ChangeTitleButtonIcon(
        frameNode, InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT, true);
}
} // namespace OHOS::Ace::NG
