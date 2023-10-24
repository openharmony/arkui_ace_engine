/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

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

    void Create(const WeakPtr<FrameNode>& frameNode, bool followWithoutTransition = false);

    RefPtr<GeometryTransition> gt_;
};

void GeometryTransitionTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    node2->AddChild(node1);
}

void GeometryTransitionTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void GeometryTransitionTestNg::SetUp() {}

void GeometryTransitionTestNg::TearDown()
{
    gt_ = nullptr;
}

void GeometryTransitionTestNg::Create(const WeakPtr<FrameNode>& node, bool followWithoutTransition)
{
    gt_ = AceType::MakeRefPtr<GeometryTransition>("test", node, followWithoutTransition);
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

    Create(weakNode1, true);
    gt_->Build(weakNode1, false);
    gt_->WillLayout(node1);
    gt_->DidLayout(node1);
    gt_->Build(weakNode2, true);
    gt_->WillLayout(node2);
    gt_->DidLayout(node2);
    EXPECT_FALSE(gt_->hasInAnim_);
    EXPECT_TRUE(gt_->hasOutAnim_);

    Create(weakNode1, true);
    gt_->Build(weakNode1, true);
    gt_->WillLayout(node1);
    gt_->DidLayout(node1);
    EXPECT_FALSE(gt_->hasInAnim_);
    EXPECT_FALSE(gt_->hasOutAnim_);

    Create(weakNode1, true);
    gt_->Build(weakNode2, true);
    gt_->WillLayout(node2);
    gt_->DidLayout(node2);
    EXPECT_FALSE(gt_->hasInAnim_);
    EXPECT_FALSE(gt_->hasOutAnim_);
}

/**
 * @tc.name: GeometryTransition002
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransition002, TestSize.Level1)
{
    Create(weakNode1, true);
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
    Create(weakNode1, true);
    /**
     * @tc.steps: step2. try build with some condition.
     * @tc.expected: weakNode1 in the GeometryTransition swap to weakNode2.
     */
    gt_->Build(weakNode1, false);
    gt_->Build(weakNode1, false);
    gt_->Build(weakNode2, false);
    EXPECT_EQ(weakNode1, gt_->outNode_);
    /**
     * @tc.steps: step3. try change node status.
     * @tc.expected: the location of weakNode1 and weakNode2 meetings expectations.
     */
    gt_->Build(weakNode1, true);
    EXPECT_EQ(gt_->inNode_, gt_->outNode_);
    gt_->inNode_.Upgrade()->isRemoving_ = true;
    gt_->outNode_ = weakNode2;
    gt_->Build(weakNode2, true);
    EXPECT_EQ(weakNode2, gt_->inNode_);
    gt_->hasInAnim_ = false;
    gt_->Build(weakNode2, false);
    gt_->inNode_.Upgrade()->isRemoving_ = false;
    gt_->inNode_.Upgrade()->onMainTree_ = true;
    gt_->hasOutAnim_ = false;
    gt_->Build(weakNode2, true);
    EXPECT_EQ(weakNode2, gt_->inNode_);
    gt_->outNode_.Upgrade()->onMainTree_ = false;
    gt_->Build(weakNode1, true);
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
    Create(weakNode1, true);
    node2->AddChild(node1);
    gt_->inNode_ = weakNode1;
    gt_->outNode_ = weakNode2;
    /**
     * @tc.steps: step2. call OnReSync with some useless condition.
     * @tc.expected: hasOutAnim_ in GeometryTransition is false
     */
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
    Create(weakNode1, true);
    node2->AddChild(node1);
    gt_->inNode_ = weakNode1;
    gt_->outNode_ = weakNode2;

    /**
     * @tc.steps: step2. assign value to followWithoutTransition_ and call OnFollowWithoutTransition.
     * @tc.expected: called OnFollowWithoutTransition and result is expected
     */
    gt_->followWithoutTransition_ = true;
    bool result =gt_->OnFollowWithoutTransition(true);
    EXPECT_FALSE(result);

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
    Create(weakNode1, true);
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
}
} // namespace OHOS::Ace::NG
