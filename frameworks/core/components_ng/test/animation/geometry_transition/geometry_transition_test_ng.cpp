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
auto node_1 = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
WeakPtr<FrameNode> inNode = AceType::WeakClaim(AceType::RawPtr(node_1));
RefPtr<LayoutWrapper> inNodeLayoutWrapper = inNode.Upgrade()->CreateLayoutWrapper(false, false);

auto node_2 = AceType::MakeRefPtr<FrameNode>("test2", 2, AceType::MakeRefPtr<Pattern>());
WeakPtr<FrameNode> outNode = AceType::WeakClaim(AceType::RawPtr(node_2));
RefPtr<LayoutWrapper> outNodeLayoutWrapper = outNode.Upgrade()->CreateLayoutWrapper(false, false);

auto node_3 = AceType::MakeRefPtr<FrameNode>("test3", 3, AceType::MakeRefPtr<Pattern>());
WeakPtr<FrameNode> otherNode = AceType::WeakClaim(AceType::RawPtr(node_3));
RefPtr<LayoutWrapper> otherNodeLayoutWrapper = outNode.Upgrade()->CreateLayoutWrapper(false, false);

} // namespace

class GeometryTransitionTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void GeometryTransitionTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    node_2->AddChild(node_1);
}

void GeometryTransitionTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void GeometryTransitionTestNg::SetUp() {}

void GeometryTransitionTestNg::TearDown() {}

/**
 * @tc.name: GeometryTransitionTest001
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransitionTest001, TestSize.Level1)
{
    GeometryTransition GT("test", inNode);
    GT.inNode_ = inNode;
    GT.outNode_ = outNode;
    GT.WillLayout(outNodeLayoutWrapper);
    GT.DidLayout(outNodeLayoutWrapper);
    outNodeLayoutWrapper->SetRootMeasureNode();
    inNodeLayoutWrapper->SetRootMeasureNode();
    GT.WillLayout(outNodeLayoutWrapper);
    GT.DidLayout(outNodeLayoutWrapper);
    GT.SyncGeometry(true);
    GT.hasOutAnim_ = true;
    GT.WillLayout(outNodeLayoutWrapper);
    outNodeLayoutWrapper->GetLayoutProperty()->UpdateAspectRatio(1.0f);
    GT.WillLayout(outNodeLayoutWrapper);
    GT.inNode_.Upgrade()->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
    GT.WillLayout(outNodeLayoutWrapper);
    GT.DidLayout(outNodeLayoutWrapper);
    GT.state_ = GeometryTransition::State::ACTIVE;
    GT.hasInAnim_ = true;
    GT.WillLayout(inNodeLayoutWrapper);
    GT.DidLayout(inNodeLayoutWrapper);
    GT.state_ = GeometryTransition::State::IDENTITY;
    GT.DidLayout(inNodeLayoutWrapper);
    GT.outNode_.Upgrade()->isRemoving_ = true;
    GT.SyncGeometry(true);
    GT.outNode_.Upgrade()->isRemoving_ = false;
    bool ret = GT.Update(inNode, inNode);
    EXPECT_TRUE(ret);
    ret = GT.Update(outNode, outNode);
    EXPECT_TRUE(ret);
    ret = GT.Update(nullptr, outNode);
    EXPECT_FALSE(ret);
    GT.SyncGeometry(false);
    inNode.Upgrade()->MarkRemoving();
    GT.SyncGeometry(false);
}

/**
 * @tc.name: GeometryTransitionTest002
 * @tc.desc: Test the Build function in the GeometryTransition
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransitionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with inNode.
     */
    GeometryTransition GT("test", inNode);
    /**
     * @tc.steps: step2. try build with some condition.
     * @tc.expected: inNode in the GeometryTransition swap to outNode.
     */
    GT.Build(inNode, false);
    GT.Build(inNode, false);
    GT.Build(outNode, false);
    EXPECT_EQ(inNode, GT.outNode_);
    /**
     * @tc.steps: step3. try change node status.
     * @tc.expected: the location of inNode and outNode meetings expectations.
     */
    GT.Build(inNode, true);
    EXPECT_EQ(GT.inNode_, GT.outNode_);
    GT.inNode_.Upgrade()->isRemoving_ = true;
    GT.outNode_ = outNode;
    GT.Build(outNode, true);
    EXPECT_EQ(outNode, GT.inNode_);
    GT.hasInAnim_ = false;
    GT.Build(outNode, false);
    GT.inNode_.Upgrade()->isRemoving_ = false;
    GT.inNode_.Upgrade()->onMainTree_ = true;
    GT.hasOutAnim_ = false;
    GT.Build(outNode, true);
    EXPECT_EQ(outNode, GT.inNode_);
    GT.outNode_.Upgrade()->onMainTree_ = false;
    GT.Build(inNode, true);
    GT.Build(inNode, true);
    EXPECT_EQ(inNode, GT.inNode_);
}

/**
 * @tc.name: GeometryTransitionTest003
 * @tc.desc: Test the OnReSync and OnAdditionalLayout function in the GeometryTransition
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, GeometryTransitionTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GeometryTransition with inNode.
     */
    GeometryTransition GT("test", inNode);
    GT.inNode_ = inNode;
    GT.outNode_ = outNode;
    /**
     * @tc.steps: step2. call OnReSync with some useless condition.
     * @tc.expected: hasOutAnim_ in GeometryTransition is false
     */
    GT.OnReSync();
    inNode.Upgrade()->GetRenderContext()->isSynced_ = true;
    GT.OnReSync();
    outNode.Upgrade()->MarkRemoving();
    GT.OnReSync();
    EXPECT_FALSE(GT.hasOutAnim_);
    /**
     * @tc.steps: step3. make outNodeTargetAbsRect_ and recall OnReSync.
     * @tc.expected: hasOutAnim_ in GeometryTransition is true
     */
    GT.outNodeTargetAbsRect_ = RectF(1.0f, 1.0f, 1.0f, 1.0f);
    GT.OnReSync();
    EXPECT_TRUE(GT.hasOutAnim_);
    /**
     * @tc.steps: step4. call OnAdditionalLayout with different condition.
     * @tc.expected: the result meetings expectations.
     */
    EXPECT_FALSE(GT.OnAdditionalLayout(inNode));
    EXPECT_TRUE(GT.OnAdditionalLayout(outNode));
    GT.hasInAnim_ = true;
    GT.state_ = GeometryTransition::State::ACTIVE;
    EXPECT_TRUE(GT.OnAdditionalLayout(inNode));
    inNode.Upgrade()->parent_ = nullptr;
    EXPECT_FALSE(GT.OnAdditionalLayout(inNode));
}
} // namespace OHOS::Ace::NG
