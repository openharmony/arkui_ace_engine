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
}

void GeometryTransitionTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void GeometryTransitionTestNg::SetUp() {}

void GeometryTransitionTestNg::TearDown() {}

/**
 * @tc.name: Test001
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GeometryTransitionTestNg, Test001, TestSize.Level1)
{
    auto node_1 = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<FrameNode> inNode = AceType::WeakClaim(AceType::RawPtr(node_1));
    RefPtr<LayoutWrapper> inNodeLayoutWrapper = inNode.Upgrade()->CreateLayoutWrapper(false, false);

    auto node_2 = AceType::MakeRefPtr<FrameNode>("test", 2, AceType::MakeRefPtr<Pattern>());
    WeakPtr<FrameNode> outNode = AceType::WeakClaim(AceType::RawPtr(node_2));
    RefPtr<LayoutWrapper> outNodeLayoutWrapper = outNode.Upgrade()->CreateLayoutWrapper(false, false);
    node_2->AddChild(node_1);

    GeometryTransition GT(inNode);
    GT.inNode_ = inNode;
    GT.outNode_ = outNode;
    GT.Build(inNode, false);
    EXPECT_TRUE(GT.hasOutAnim_);
    GT.Build(outNode, false);
    EXPECT_TRUE(GT.hasOutAnim_);
    GT.WillLayout(outNodeLayoutWrapper);
    GT.DidLayout(outNodeLayoutWrapper);
    outNodeLayoutWrapper->SetRootMeasureNode();
    GT.WillLayout(outNodeLayoutWrapper); // IsNodeOutAndActive
    GT.DidLayout(outNodeLayoutWrapper);
    GT.SyncGeometry(true);

    GT.Build(inNode, true);
    EXPECT_EQ(GT.inNode_, inNode);
    GT.Build(outNode, true);
    EXPECT_EQ(GT.inNode_, outNode);
    GT.inNode_ = inNode;
    GT.outNode_ = outNode;
    GT.hasInAnim_ = true;
    GT.hasOutAnim_ = true;
    GT.state_ = GeometryTransition::State::IDENTITY;
    GT.WillLayout(inNodeLayoutWrapper);
    GT.DidLayout(inNodeLayoutWrapper);
    GT.SyncGeometry(true);
    inNodeLayoutWrapper->SetRootMeasureNode();
    GT.hasInAnim_ = true;
    GT.hasOutAnim_ = true;
    GT.state_ = GeometryTransition::State::ACTIVE;
    GT.WillLayout(inNodeLayoutWrapper); // IsNodeInAndActive
    GT.DidLayout(inNodeLayoutWrapper);

    GT.inNode_ = inNode;
    GT.outNode_ = outNode;
    bool ret = GT.Update(inNode, inNode);
    EXPECT_TRUE(ret);
    ret = GT.Update(outNode, outNode);
    EXPECT_TRUE(ret);
    ret = GT.Update(nullptr, outNode);
    EXPECT_FALSE(ret);

    GT.SyncGeometry(false);
    inNode.Upgrade()->MarkRemoving();
    GT.SyncGeometry(false);

    GT.OnReSync();
    outNode.Upgrade()->MarkRemoving();
    GT.OnReSync();

    bool ret_2 = GT.OnAdditionalLayout(inNode);
    EXPECT_FALSE(ret_2);
    GT.state_ = GeometryTransition::State::ACTIVE;
    ret_2 = GT.OnAdditionalLayout(inNode);
    EXPECT_TRUE(ret_2);
    ret_2 = GT.OnAdditionalLayout(outNode);
    EXPECT_TRUE(ret_2);
}
} // namespace OHOS::Ace::NG
