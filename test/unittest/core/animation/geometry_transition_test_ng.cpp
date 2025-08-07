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
#include <string>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/animation/geometry_transition.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
auto node1 = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
WeakPtr<FrameNode> weakNode1 = AceType::WeakClaim(AceType::RawPtr(node1));

auto node2 = AceType::MakeRefPtr<FrameNode>("test2", 2, AceType::MakeRefPtr<Pattern>());
WeakPtr<FrameNode> weakNode2 = AceType::WeakClaim(AceType::RawPtr(node2));

auto node3 = AceType::MakeRefPtr<FrameNode>("test3", 3, AceType::MakeRefPtr<Pattern>());
WeakPtr<FrameNode> weakNode3 = AceType::WeakClaim(AceType::RawPtr(node3));

const int32_t DURATION_TIMES = 100;
} // namespace

class GeometryTransitionTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    void Create(const WeakPtr<FrameNode>& frameNode,
        bool followWithoutTransition = false, bool doRegisterSharedTransition = true);

    RefPtr<FrameNode> CreateHolderNode(const RefPtr<FrameNode>& node);
    RefPtr<GeometryTransition> gt_;
};

void GeometryTransitionTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    node2->AddChild(node1);
}

void GeometryTransitionTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void GeometryTransitionTestNg::SetUp() {}

void GeometryTransitionTestNg::TearDown()
{
    gt_ = nullptr;
}

void GeometryTransitionTestNg::Create(const WeakPtr<FrameNode>& node,
    bool followWithoutTransition, bool doRegisterSharedTransition)
{
    gt_ = AceType::MakeRefPtr<GeometryTransition>("test", followWithoutTransition, doRegisterSharedTransition);
    // The constructor has been modified and requires additional assignments
    gt_->inNode_ = node;
}

RefPtr<FrameNode> GeometryTransitionTestNg::CreateHolderNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto newNode = FrameNode::CreateFrameNode(
        node->GetTag(), ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    newNode->SetGeometryNode(node->GetGeometryNode()->Clone());
    auto frameSize = node->GetGeometryNode()->GetFrameSize();
    newNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(frameSize.Width()), CalcLength(frameSize.Height())));
    return newNode;
}

/**
 * @tc.name: GeometryTransition001
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build with empty node.
     * @tc.expected: hasInAnim_ and hasOutAnim_ are false
     */
    Create(nullptr);
    EXPECT_TRUE(gt_->IsInAndOutEmpty());
    gt_->Build(nullptr, true);
    EXPECT_FALSE(gt_->hasInAnim_);
    EXPECT_FALSE(gt_->hasOutAnim_);

    Create(weakNode1, true, true);
    gt_->Build(weakNode1, false);
    gt_->WillLayout(node1);
    gt_->DidLayout(node1);
    gt_->Build(weakNode2, true);
    gt_->WillLayout(node2);
    gt_->DidLayout(node2);
    EXPECT_TRUE(gt_->hasInAnim_);
    EXPECT_TRUE(gt_->hasOutAnim_);

    Create(weakNode1, true, true);
    gt_->Build(weakNode1, true);
    gt_->WillLayout(node1);
    gt_->DidLayout(node1);
    EXPECT_FALSE(gt_->hasInAnim_);
    EXPECT_FALSE(gt_->hasOutAnim_);

    Create(weakNode1, true, true);
    gt_->Build(weakNode2, true);
    gt_->WillLayout(node2);
    gt_->DidLayout(node2);
    EXPECT_TRUE(gt_->hasInAnim_);
    EXPECT_FALSE(gt_->hasOutAnim_);

    Create(weakNode1, true, true);
    weakNode2.Upgrade()->isRemoving_ = true;
    gt_->Build(weakNode2, true);
    gt_->WillLayout(node2);
    gt_->DidLayout(node2);
    EXPECT_TRUE(gt_->hasInAnim_);
    EXPECT_FALSE(gt_->hasOutAnim_);

    /**
     * @tc.steps: step1. Build with empty node.
     * @tc.expected: hasInAnim_ and hasOutAnim_ are false and state_ is ACTIVE
     */
    auto weakNodeTemp = weakNode3.Upgrade();
    weakNode2.Upgrade()->isRemoving_ = false;
    weakNodeTemp->isRemoving_ = false;
    weakNodeTemp->onMainTree_ = true;
    Create(weakNode3, true, true);
    gt_->outNode_ = weakNode1;
    gt_->Build(weakNode2, true);
    gt_->WillLayout(node2);
    gt_->DidLayout(node2);
    EXPECT_FALSE(gt_->hasInAnim_);
    EXPECT_FALSE(gt_->hasOutAnim_);
    EXPECT_FALSE(gt_->state_ == GeometryTransition::State::ACTIVE);
}

/**
 * @tc.name: GeometryTransition002
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransition002, TestSize.Level1)
{
    Create(weakNode1, true, true);
    gt_->inNode_ = weakNode1;
    gt_->outNode_ = weakNode2;
    gt_->WillLayout(node2);
    gt_->DidLayout(node2);
    node2->SetRootMeasureNode();
    node1->SetRootMeasureNode();
    gt_->WillLayout(node2);
    gt_->DidLayout(node2);
    gt_->SyncGeometry(true);
    gt_->hasOutAnim_ = true;
    gt_->WillLayout(node2);
    node2->GetLayoutProperty()->UpdateAspectRatio(1.0f);
    gt_->WillLayout(node2);
    gt_->inNode_.Upgrade()->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
    gt_->WillLayout(node2);
    gt_->DidLayout(node2);
    gt_->state_ = GeometryTransition::State::ACTIVE;
    gt_->hasInAnim_ = true;
    gt_->WillLayout(node1);
    gt_->DidLayout(node1);
    gt_->state_ = GeometryTransition::State::IDENTITY;
    gt_->DidLayout(node1);
    gt_->outNode_.Upgrade()->isRemoving_ = true;
    gt_->SyncGeometry(true);
    gt_->outNode_.Upgrade()->isRemoving_ = false;
    bool ret = gt_->Update(weakNode1, weakNode1);
    EXPECT_TRUE(ret);
    ret = gt_->Update(weakNode2, weakNode2);
    EXPECT_TRUE(ret);
    ret = gt_->Update(nullptr, weakNode2);
    EXPECT_FALSE(ret);
    gt_->SyncGeometry(false);
    weakNode1.Upgrade()->MarkRemoving();
    gt_->SyncGeometry(false);
}

/**
 * @tc.name: GeometryTransition003
 * @tc.desc: Test the Build function in the GeometryTransition
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransition003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with weakNode1.
     */
    Create(weakNode1, true, true);
    weakNode1.Upgrade()->isRemoving_ = false;
    /**
     * @tc.steps: step2. try build with some condition.
     * @tc.expected: weakNode1 in the GeometryTransition swap to weakNode2.
     */
    gt_->Build(weakNode1, false);
    gt_->Build(weakNode1, false);
    gt_->Build(weakNode2, false);
    EXPECT_EQ(weakNode1, gt_->outNode_);
    gt_->inNode_ = weakNode2;
    /**
     * @tc.steps: step3. try change node status.
     * @tc.expected: the location of weakNode1 and weakNode2 meetings expectations.
     */
    gt_->Build(weakNode1, true);
    EXPECT_EQ(gt_->inNode_, gt_->outNode_);
    gt_->inNode_.Upgrade()->isRemoving_ = true;
    gt_->outNode_ = weakNode2;
    gt_->Build(gt_->inNode_, true);

    /**
     * @tc.steps:  Cover all situations for InAnim and OutAnim
     * @tc.expected: the location of weakNode1 and weakNode2 meetings expectations.
     */
    bool bFlagIn = gt_->hasInAnim_;
    bool bFlagOut = gt_->hasOutAnim_;
    bool bFlagFollow = gt_->followWithoutTransition_;
    gt_->hasInAnim_ = false;
    gt_->hasOutAnim_ = true;
    gt_->followWithoutTransition_ = true;
    gt_->Build(weakNode2, true);

    /**
     * @tc.steps:  Cover all situations for InAnim and OutAnim
     */
    gt_->hasInAnim_ = false;
    gt_->hasOutAnim_ = false;
    gt_->Build(weakNode2, true);

    /**
     * @tc.step:  Cover all situations for InAnim and OutAnim
     */
    gt_->hasInAnim_ = true;
    gt_->hasOutAnim_ = false;
    gt_->Build(weakNode2, true);

    /**
     * @tc.expected: IsRunning is false.
     */
    bool bResult = false;
    bResult = gt_->IsRunning(weakNode3);
    EXPECT_FALSE(bResult);

    /**
     * @tc.expected: IsRunning is true.
     */
    weakNode2.Upgrade()->layoutPriority_ = 1;
    bResult = gt_->IsRunning(weakNode2);
    EXPECT_TRUE(bResult);
    /**
     * @tc.steps: Reduction
     */
    gt_->hasInAnim_ = bFlagIn;
    gt_->hasOutAnim_ = bFlagOut;
    gt_->followWithoutTransition_ = bFlagFollow;

    EXPECT_EQ(weakNode2, gt_->inNode_);
    gt_->hasInAnim_ = false;
    gt_->Build(weakNode2, false);
    gt_->inNode_.Upgrade()->isRemoving_ = false;
    gt_->inNode_.Upgrade()->onMainTree_ = true;
    gt_->hasOutAnim_ = false;
    gt_->Build(weakNode2, true);
    EXPECT_EQ(weakNode2, gt_->inNode_);
    gt_->outNode_.Upgrade()->onMainTree_ = false;
    weakNode1.Upgrade()->isRemoving_ = false;
    gt_->Build(weakNode1, true);
    EXPECT_EQ(weakNode1, gt_->inNode_);
}

/**
 * @tc.name: GeometryTransition004
 * @tc.desc: Test the OnReSync and OnAdditionalLayout function in the GeometryTransition
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransition004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with weakNode1.
     */
    Create(weakNode1, true, true);
    node2->AddChild(node1);
    gt_->inNode_ = weakNode1;
    gt_->outNode_ = weakNode2;
    /**
     * @tc.steps: step2. call OnReSync with some useless condition.
     * @tc.expected: hasOutAnim_ in GeometryTransition is false
     */
    gt_->holder_ = CreateHolderNode(gt_->outNode_.Upgrade());
    gt_->OnReSync();
    weakNode1.Upgrade()->GetRenderContext()->isSynced_ = true;
    gt_->OnReSync();
    weakNode2.Upgrade()->MarkRemoving();
    gt_->OnReSync();
    EXPECT_FALSE(gt_->hasOutAnim_);
    /**
     * @tc.steps: step3. make outNodeTargetAbsRect_ and recall OnReSync.
     * @tc.expected: hasOutAnim_ in GeometryTransition is true
     */
    gt_->outNodeTargetAbsRect_ = RectF(1.0f, 1.0f, 1.0f, 1.0f);
    gt_->OnReSync();
    EXPECT_FALSE(gt_->hasOutAnim_);

    /**
     * @tc.steps: step4. during outNode animation is running target inNode's frame is changed
     */
    gt_->RecordAnimationOption(weakNode3, AnimationOption());
    EXPECT_FALSE(gt_->animationOption_.IsValid());

    /**
     * @tc.steps: step5. call OnAdditionalLayout with different condition.
     * @tc.expected: the result meetings expectations.
     */
    EXPECT_FALSE(gt_->OnAdditionalLayout(weakNode1));
    EXPECT_FALSE(gt_->OnAdditionalLayout(weakNode2));
    gt_->hasInAnim_ = true;
    gt_->state_ = GeometryTransition::State::ACTIVE;
    EXPECT_TRUE(gt_->OnAdditionalLayout(weakNode1));
    weakNode1.Upgrade()->parent_ = nullptr;
    EXPECT_FALSE(gt_->OnAdditionalLayout(weakNode1));

    auto weakNodeTemp = weakNode1.Upgrade();
    weakNodeTemp->onMainTree_ = true;
    weakNodeTemp->renderContext_->isSynced_ = true;
    weakNode2.Upgrade()->isRemoving_ = true;
    gt_->outNodeTargetAbsRect_ = RectF(10.0f, 10.0f, 10.0f, 10.0f);
    gt_->inNode_ = weakNode1;
    gt_->outNode_ = weakNode2;
    RefPtr<FrameNode> trigger = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    gt_->OnReSync(trigger);
    gt_->OnReSync();
    gt_->ToString();
    EXPECT_FALSE(gt_->hasOutAnim_);

    // posChanged  is true
    gt_->hasOutAnim_ = false;
    gt_->outNodeTargetAbsRect_ = RectF(1.0f, 10.0f, 1.0f, 1.0f);
    gt_->OnReSync();
    EXPECT_FALSE(gt_->hasOutAnim_);

    // posChanged is true
    gt_->outNodeTargetAbsRect_ = RectF(10.0f, 1.0f, 1.0f, 1.0f);
    gt_->OnReSync();
    EXPECT_FALSE(gt_->hasOutAnim_);

    // sizeChanged  is true
    gt_->outNodeTargetAbsRect_ = RectF(1.0f, 1.0f, 10.0f, 1.0f);
    gt_->OnReSync();
    EXPECT_FALSE(gt_->hasOutAnim_);

    // sizeChanged  is true
    gt_->outNodeTargetAbsRect_ = RectF(1.0f, 1.0f, 1.0f, 10.0f);
    gt_->OnReSync();
    EXPECT_FALSE(gt_->hasOutAnim_);
}

/**
 * @tc.name: GeometryTransitionTest005
 * @tc.desc: Test OnFollowWithoutTransition()
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransitionTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with weakNode1.
     */
    Create(weakNode1, true, true);
    node2->AddChild(node1);
    gt_->inNode_ = weakNode1;
    gt_->outNode_ = weakNode2;

    /**
     * @tc.steps: step2. assign value to followWithoutTransition_ and call OnFollowWithoutTransition.
     * @tc.expected: called OnFollowWithoutTransition and result is expected
     */
    gt_->followWithoutTransition_ = true;
    bool result = gt_->OnFollowWithoutTransition(true);
    EXPECT_FALSE(result);

    // direction has value is false
    RefPtr<FrameNode> trigger = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    gt_->holder_ = CreateHolderNode(gt_->outNode_.Upgrade());
    trigger->AddChild(gt_->holder_);
    result = gt_->OnFollowWithoutTransition();
    EXPECT_FALSE(result);

    // direction is true
    gt_->followWithoutTransition_ = false;
    result = gt_->OnFollowWithoutTransition(true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GeometryTransitionTest006
 * @tc.desc: Test RecordAnimationOption()
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransitionTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with node.
     */
    Create(weakNode1, true, true);
    node2->AddChild(node1);
    gt_->inNode_ = weakNode1;
    gt_->outNode_ = weakNode2;

    /**
     * @tc.steps: step2. construt input parameters and call OnReSync RecordAnimationOption.
     * @tc.expected: called RecordAnimationOption and result is expected.
     */
    RefPtr<FrameNode> trigger = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    AnimationOption option = AnimationOption();
    gt_->RecordAnimationOption(trigger, option);
    bool result = option.IsValid();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3.set animation option attribute and call OnReSync RecordAnimationOption.
     * @tc.expected: called RecordAnimationOption and cover branch animationOption is false.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto implicitAnimationOption = stack->GetImplicitAnimationOption();
    implicitAnimationOption.SetDuration(DURATION_TIMES);
    gt_->RecordAnimationOption(trigger, option);
    result = option.IsValid();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. set animation option attribute and call OnReSync RecordAnimationOption.
     * @tc.expected: called RecordAnimationOption and cover branch animationOption is true.
     */
    option.SetDuration(DURATION_TIMES);
    gt_->RecordAnimationOption(trigger, option);
    result = option.IsValid();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: IsParent(trigger, inNode_) is true
     * @tc.expected: option is not IsValid
     */
    trigger->AddChild(gt_->inNode_.Upgrade());
    gt_->RecordAnimationOption(trigger, option);
    result = option.IsValid();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: set option Duration(0);
     * @tc.expected: option is not IsValid
     */
    option.SetDuration(0);
    AnimationOption optionTemp = AnimationOption();
    optionTemp.SetDuration(DURATION_TIMES);
    stack->SetImplicitAnimationOption(optionTemp);
    gt_->RecordAnimationOption(trigger, option);
    result = option.IsValid();
    EXPECT_FALSE(result);

    stack->SetImplicitAnimationOption(option);
    gt_->animationOption_ = optionTemp;
    result = option.IsValid();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: Remove inNode from trigger
     */
    trigger->RemoveChild(gt_->inNode_.Upgrade());
    gt_->RecordAnimationOption(trigger, option);
    result = option.IsValid();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GeometryTransition007
 * @tc.desc: Test the Build function in the GeometryTransition
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransition007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with weakNode1.
     */
    Create(weakNode1, true, true);

    gt_->hasInAnim_ = false;
    gt_->outNode_ = weakNode2;
    gt_->hasOutAnim_ = true;

    /**
     * @tc.steps: step2. create holder_ with out.
     */
    gt_->holder_ = CreateHolderNode(gt_->outNode_.Upgrade());

    /**
     * @tc.steps: step3. set holder_ is son of node1.
     */
    RefPtr<FrameNode> trigger = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    trigger->AddChild(gt_->holder_);

    /**
     * @tc.steps: step4. call Build.
     * @tc.expected: gt_->holder_ is nullptr and hasout is true.
     */
    gt_->Build(weakNode3, false);
    EXPECT_FALSE(gt_->holder_);
    EXPECT_TRUE(gt_->hasOutAnim_);
}

/**
 * @tc.name: GeometryTransitionTest008
 * @tc.desc: Test OnAdditionalLayout()
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransition008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with weakNode1.
     */
    Create(weakNode1, true, true);
    gt_->state_ = GeometryTransition::State::IDENTITY;

    /**
     * @tc.steps: step2. set Out is weakNode2.
     */
    gt_->outNode_ = weakNode2;
    gt_->hasOutAnim_ = true;

    /**
     * @tc.steps: step3. call OnAdditionalLayout.
     * @tc.expected: True.
     */
    bool bResult = gt_->OnAdditionalLayout(weakNode2);
    EXPECT_TRUE(bResult);
}

/**
 * @tc.name: GeometryTransitionTest009
 * @tc.desc: Test RecordAnimationOption()
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransitionTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with node.
     */
    Create(weakNode1, true, true);
    node2->AddChild(node1);
    gt_->inNode_ = weakNode1;
    gt_->outNode_ = weakNode2;

    /**
     * @tc.steps: step2. construt input parameters and call OnReSync RecordAnimationOption.
     * @tc.expected: called RecordAnimationOption and result is expected.
     */
    RefPtr<FrameNode> trigger = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    AnimationOption option = AnimationOption();
    gt_->RecordAnimationOption(trigger, option);
    bool result = option.IsValid();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. set animation option attribute and call OnReSync RecordAnimationOption.
     * @tc.expected: called RecordAnimationOption and cover branch animationOption is true.
     */
    option.SetDuration(DURATION_TIMES);
    gt_->RecordAnimationOption(trigger, option);
    result = option.IsValid();
    EXPECT_TRUE(result);

    /**
     * @tc.steps:step4 IsParent(trigger, inNode_) is true
     * @tc.expected: option is not IsValid
     */
    trigger->AddChild(gt_->inNode_.Upgrade());
    gt_->RecordAnimationOption(trigger, option);
    result = option.IsValid();
    EXPECT_TRUE(result);

    /**
     * @tc.steps:step5 set option Duration(0);
     */
    option.SetDuration(0);
    AnimationOption optionTemp = AnimationOption();

    /**
     * @tc.steps:step6 set pipeline->GetSyncAnimationOption() IsValid;
     * @tc.expected: animationOption_ is not IsValid
     */
    optionTemp.SetDuration(DURATION_TIMES);
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->animationOption_ = optionTemp;
    gt_->RecordAnimationOption(trigger, option);
    EXPECT_TRUE(gt_->animationOption_.IsValid());

    /**
     * @tc.steps:step7 Remove child from trigger
     * @tc.expected: gt_->animationOption_ is not IsValid
     */
    gt_->animationOption_ = AnimationOption();
    trigger->RemoveChild(gt_->inNode_.Upgrade());
    gt_->RecordAnimationOption(trigger, option);
    EXPECT_FALSE(gt_->animationOption_.IsValid());

    /**
     * @tc.steps:step8 pipeline->animationOption_ is not Valid
     * @tc.expected: gt_->animationOption_ is not IsValid
     */
    pipeline->animationOption_ = gt_->animationOption_;
    gt_->RecordAnimationOption(trigger, option);
    EXPECT_FALSE(gt_->animationOption_.IsValid());
}

/**
 * @tc.name: GeometryTransitionTest010
 * @tc.desc: Test RecordAnimationOption()
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransitionTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with node.
     */
    Create(weakNode1, true, true);
    node2->AddChild(node1);
    gt_->inNode_ = weakNode1;
    gt_->outNode_ = weakNode2;

    /**
     * @tc.steps: step2. construt input parameters and call OnReSync RecordAnimationOption.
     * @tc.expected: called RecordAnimationOption and result is expected.
     */
    RefPtr<FrameNode> trigger = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    AnimationOption option = AnimationOption();
    gt_->RecordAnimationOption(trigger, option);
    bool result = option.IsValid();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3.set animation option attribute and call OnReSync RecordAnimationOption.
     * @tc.expected: called RecordAnimationOption and cover branch animationOption is True.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto implicitAnimationOption = stack->GetImplicitAnimationOption();
    implicitAnimationOption.SetDuration(DURATION_TIMES);
    stack->SetImplicitAnimationOption(implicitAnimationOption);
    gt_->RecordAnimationOption(trigger, option);
    result = stack->GetImplicitAnimationOption().IsValid();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GeometryTransitionTest011
 * @tc.desc: Test GetFollowWithoutTransition()
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransitionTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with node.
     */
    Create(weakNode1, false, true);
    /**
     * @tc.steps: step2. test GetFollowWithoutTransition() result when state of followWithoutTransition_ changes.
     */
    EXPECT_FALSE(gt_->GetFollowWithoutTransition());
    gt_->followWithoutTransition_ = true;
    EXPECT_TRUE(gt_->GetFollowWithoutTransition());

}

/**
 * @tc.name: GeometryTransitionTest012
 * @tc.desc: Test GetDoRegisterSharedTransition()
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransitionTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with node.
     */
    Create(weakNode1, false, true);
    /**
     * @tc.steps: step2. test GetDoRegisterSharedTransition() result when state of doRegisterSharedTransition_ changes.
     */
    EXPECT_TRUE(gt_->GetDoRegisterSharedTransition());
    gt_->doRegisterSharedTransition_ = false;
    EXPECT_FALSE(gt_->GetDoRegisterSharedTransition());
}

/**
 * @tc.name: GeometryTransitionTest013
 * @tc.desc: Test SyncGeometryPropertiesAfterLayout()
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransitionTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with node.
     */
    Create(weakNode1, true, true);
    /**
     * @tc.steps: step2. test SyncGeometryPropertiesAfterLayout().
     * @tc.expected: pipeline not null
     */
    gt_->SyncGeometryPropertiesAfterLayout(weakNode1.Upgrade());
    EXPECT_TRUE(PipelineContext::GetCurrentContext() != nullptr);
}

/**
 * @tc.name: GeometryTransitionTest014
 * @tc.desc: Test GetWindowBoundaryNode()
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransitionTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with node.
     */
    Create(weakNode1, true, true);
    /**
     * @tc.steps: step2. test GetWindowBoundaryNode().
     * @tc.expected: pipeline not null
     */
    auto node = weakNode1.Upgrade();
    node->SetParent(node2);

    /**
     * @tc.steps: step3. Set window boundary to true and verify GetWindowBoundaryNode() returns the correct node.
     * @tc.expected: GetWindowBoundaryNode() should return the current node when window boundary is true.
     */
    node->SetWindowBoundary(true);
    EXPECT_TRUE(gt_->GetWindowBoundaryNode(node) == node);

    /**
     * @tc.steps: step4. Set window boundary to false and verify GetWindowBoundaryNode() returns the parent node.
     * @tc.expected: GetWindowBoundaryNode() should return the parent node when window boundary is false.
     */
    node->SetWindowBoundary(false);
    EXPECT_TRUE(gt_->GetWindowBoundaryNode(node) == node2);
}
 
/**
 * @tc.name: GeometryTransitionTest015
 * @tc.desc: Test HandleOcclusionScene()
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransitionTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with node.
     */
    Create(weakNode1, true, true);
    /**
     * @tc.steps: step2. test HandleOcclusionScene().
     * @tc.expected: pipeline not null
     */
    gt_->HandleOcclusionScene(weakNode1.Upgrade(), false);
    EXPECT_TRUE(PipelineContext::GetCurrentContext() != nullptr);
    std::string id = weakNode1.Upgrade()->GetInspectorId().value_or("");
    weakNode1.Upgrade()->UpdateInspectorId(id.append("_occlusion"));
    gt_->HandleOcclusionScene(weakNode1.Upgrade(), false);
    EXPECT_TRUE(PipelineContext::GetCurrentContext() != nullptr);
}
} // namespace OHOS::Ace::NG
