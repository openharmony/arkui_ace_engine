/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/unittest/core/base/frame_node_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

/**
 * @tc.name: FrameNodeOnGenerateOneDepthVisibleFrameWithOffset01
 * @tc.desc: Test the function OnGenerateOneDepthVisibleFrameWithOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnGenerateOneDepthVisibleFrameWithOffset01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutNode_ = true;
    frameNode->isActive_ = true;
    frameNode->overlayNode_ = nullptr;

    /**
     * @tc.steps: step2. call the function OnGenerateOneDepthVisibleFrameWithOffset.
     */
    OffsetF Offset = { 0.0, 0.0 };
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->OnGenerateOneDepthVisibleFrameWithOffset(children, Offset);
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    frameNode->OnGenerateOneDepthVisibleFrameWithOffset(children, Offset);
}

/**
 * @tc.name: FrameNodeOnGenerateOneDepthVisibleFrameWithOffset02
 * @tc.desc: Test the function OnGenerateOneDepthVisibleFrameWithOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnGenerateOneDepthVisibleFrameWithOffset02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutNode_ = false;
    frameNode->isActive_ = true;
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. call the function OnGenerateOneDepthVisibleFrameWithOffset.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    OffsetF Offset = { 0.0, 0.0 };
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->OnGenerateOneDepthVisibleFrameWithOffset(children, Offset);
}

/**
 * @tc.name: FrameNodeOnGenerateOneDepthVisibleFrameWithOffset03
 * @tc.desc: Test the function OnGenerateOneDepthVisibleFrameWithOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnGenerateOneDepthVisibleFrameWithOffset03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutNode_ = false;
    frameNode->isActive_ = true;
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. call the function OnGenerateOneDepthVisibleFrameWithOffset.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;
    OffsetF Offset = { 0.0, 0.0 };
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->OnGenerateOneDepthVisibleFrameWithOffset(children, Offset);
}

/**
 * @tc.name: FrameNodeOnGenerateOneDepthVisibleFrameWithOffset04
 * @tc.desc: Test the function OnGenerateOneDepthVisibleFrameWithOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeOnGenerateOneDepthVisibleFrameWithOffset04, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto childNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->isLayoutNode_ = false;
    frameNode->isActive_ = false;
    frameNode->overlayNode_ = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. call the function OnGenerateOneDepthVisibleFrameWithOffset.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;
    OffsetF Offset = { 0.0, 0.0 };
    std::list<RefPtr<FrameNode>> children;
    children.push_back(childNode);
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->OnGenerateOneDepthVisibleFrameWithOffset(children, Offset);
}

/**
 * @tc.name: FrameNodeIsOutOfTouchTestRegion01
 * @tc.desc: Test the function IsOutOfTouchTestRegion
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeIsOutOfTouchTestRegion01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto testNode = FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call the function IsOutOfTouchTestRegion.
     */
    NG::PointF point { 1.0, 1.0 };
    frameNode->renderContext_->UpdateClipEdge(true);
    frameNode->IsOutOfTouchTestRegion(point, 1);
    testNode->renderContext_->UpdateClipEdge(false);
    testNode->IsOutOfTouchTestRegion(point, 1);
}

/**
 * @tc.name: FrameNodeAddJudgeToTargetComponent01
 * @tc.desc: Test the function AddJudgeToTargetComponent
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAddJudgeToTargetComponent01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call the function AddJudgeToTargetComponent.
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo,
                                const std::shared_ptr<BaseGestureEvent>&) -> GestureJudgeResult {
        return GestureJudgeResult(1);
    };
    gestureHub->SetOnGestureJudgeNativeBegin(gestureJudgeFunc);
    RefPtr<TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    frameNode->AddJudgeToTargetComponent(targetComponent);
}

/**
 * @tc.name: FrameNodeAddJudgeToTargetComponent02
 * @tc.desc: Test the function AddJudgeToTargetComponent
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeAddJudgeToTargetComponent02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call the function AddJudgeToTargetComponent.
     */
    frameNode->eventHub_->gestureEventHub_ = nullptr;
    RefPtr<TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    frameNode->AddJudgeToTargetComponent(targetComponent);
}
} // namespace OHOS::Ace::NG