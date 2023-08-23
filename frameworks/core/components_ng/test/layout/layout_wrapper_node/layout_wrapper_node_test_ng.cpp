/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include <memory>
#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/grid_layout_info.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/property/grid_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ID_0 = 0;
constexpr int32_t NODE_ID_1 = 1;
constexpr int32_t NODE_ID_2 = 2;
constexpr int32_t NODE_ID_3 = 3;
const std::string ROW_FRAME_NODE = "rowFrameNode";
// const std::string FIRST_FRAME_NODE = "TabContent";
const std::string FIRST_CHILD_FRAME_NODE = "firstChildFrameNode";
const std::string SECOND_CHILD_FRAME_NODE = "secondChildFrameNode";
const std::string THIRD_CHILD_FRAME_NODE = "thirdChildFrameNode";
const int32_t INDEX = 1;

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateNodeAndWrapper(const std::string& tag, int32_t nodeId)
{
    auto node = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(node, geometryNode, node->GetLayoutProperty());

    return std::make_pair(node, layoutWrapper);
}

RefPtr<LazyLayoutWrapperBuilder> CreateWrapperBuilder()
{
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    RefPtr<LazyForEachNode> host = AceType::MakeRefPtr<LazyForEachNode>(INDEX, builder);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);
    return wrapperBuilder;
}
} // namespace

class LayoutWrapperNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void LayoutWrapperNodeTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
}

void LayoutWrapperNodeTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: LayoutWrapperNodeTestNg001
 * @tc.desc: Test Update.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperNodeTestNg, LayoutWrapperNodeTestNg001, TestSize.Level1)
{
    auto [node, wrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);
    auto [newNode, newWrapper] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    wrapper->Update(newNode, newWrapper->GetGeometryNode(), newNode->GetLayoutProperty());
    EXPECT_EQ(wrapper->GetHostNode()->GetTag(), FIRST_CHILD_FRAME_NODE);
}

/**
 * @tc.name: LayoutWrapperNodeTestNg002
 * @tc.desc: Test AppendChild.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperNodeTestNg, LayoutWrapperNodeTestNg002, TestSize.Level1)
{
    auto [node, wrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);
    auto [child, childWrapper] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);

    wrapper->AppendChild(childWrapper, true);
    EXPECT_EQ(wrapper->overlayChild_->GetHostNode()->GetTag(), FIRST_CHILD_FRAME_NODE);
}

/**
 * @tc.name: LayoutWrapperNodeTestNg003
 * @tc.desc: Test GetAllChildrenWithBuild.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperNodeTestNg, LayoutWrapperNodeTestNg003, TestSize.Level1)
{
    auto [node, wrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);
    auto [child, childWrapper] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    auto [child2, childWrapper2] = CreateNodeAndWrapper(SECOND_CHILD_FRAME_NODE, NODE_ID_2);
    auto [child3, childWrapper3] = CreateNodeAndWrapper(THIRD_CHILD_FRAME_NODE, NODE_ID_3);

    wrapper->AppendChild(childWrapper, false);
    wrapper->AppendChild(childWrapper2, false);
    wrapper->AppendChild(childWrapper3, true);
    wrapper->GetAllChildrenWithBuild(true);

    EXPECT_TRUE(wrapper->overlayChild_->IsActive());
}

/**
 * @tc.name: LayoutWrapperNodeTestNg004
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperNodeTestNg, LayoutWrapperNodeTestNg004, TestSize.Level1)
{
    auto [node, wrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);

    auto layoutAlgorithmT = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithmT, false, false);
    wrapper->SetLayoutAlgorithm(layoutAlgorithm);

    wrapper->Layout();
    EXPECT_TRUE(wrapper->layoutProperty_->GetLayoutConstraint());

    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize = OptionalSizeF(768, 1024);
    wrapper->layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    EXPECT_EQ(wrapper->layoutProperty_->layoutConstraint_->parentIdealSize, OptionalSizeF(768, 1024));
}

/**
 * @tc.name: LayoutWrapperNodeTestNg005
 * @tc.desc: Test SetLongPredictTask.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperNodeTestNg, LayoutWrapperNodeTestNg005, TestSize.Level1)
{
    auto [node, wrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);
    wrapper->layoutWrapperBuilder_ = CreateWrapperBuilder();
    EXPECT_TRUE(wrapper->layoutWrapperBuilder_);

    wrapper->SetLongPredictTask();
    EXPECT_TRUE(wrapper->layoutWrapperBuilder_->useLongPredictTask_);
}

/**
 * @tc.name: LayoutWrapperNodeTestNg006
 * @tc.desc: Test SwapDirtyLayoutWrapperOnMainThread.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperNodeTestNg, LayoutWrapperNodeTestNg006, TestSize.Level1)
{
    auto [child, childWrapper] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    childWrapper->isActive_ = true;
    childWrapper->layoutProperty_->gridProperty_ = std::make_unique<GridProperty>();
    childWrapper->layoutProperty_->UpdateGridProperty(DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET, GridSizeType::UNDEFINED);

    auto [node, wrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);
    wrapper->AppendChild(childWrapper, true);
    wrapper->isActive_ = true;
    wrapper->SwapDirtyLayoutWrapperOnMainThread();
    EXPECT_EQ(child->layoutProperty_->gridProperty_->GetOffset(), Dimension(0.0, DimensionUnit::PX));
}

/**
 * @tc.name: LayoutWrapperNodeTestNg007
 * @tc.desc: Test LayoutOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperNodeTestNg, LayoutWrapperNodeTestNg007, TestSize.Level1)
{
    auto [node, wrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);
    auto frameSize = SizeF(100, 200);
    wrapper->geometryNode_->SetFrameSize(frameSize);

    auto [child, childWrapper] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    auto frameSizeChild = SizeF(50, 100);
    childWrapper->geometryNode_->SetFrameSize(frameSizeChild);
    childWrapper->layoutProperty_->overlayOffsetX_ = Dimension::FromString("1px");
    childWrapper->layoutProperty_->overlayOffsetY_ = Dimension::FromString("1px");

    wrapper->AppendChild(childWrapper, true);
    wrapper->LayoutOverlay();
    EXPECT_EQ(childWrapper->GetGeometryNode()->GetFrameRect().GetOffset(), OffsetF(1, 1));
}
} // namespace OHOS::Ace::NG
