/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_TEST_UNITTEST_LAYOUT_WRAPPER_TEST_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_TEST_UNITTEST_LAYOUT_WRAPPER_TEST_NG_H

#include <algorithm>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

#undef private
#undef protected

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
namespace {
constexpr int32_t INDEX_NUM_0 = 0;
constexpr int32_t INDEX_ERROR_NUM = -1;
constexpr int32_t NODE_ID_0 = 0;
constexpr int32_t CHILD_COUNT = 1;
constexpr int32_t NODE_ID_1 = 1;
constexpr int32_t NODE_ID_2 = 2;
constexpr int32_t NODE_ID_3 = 3;
constexpr int32_t CACHE_COUNT = 1;
constexpr int32_t ERROR_HOST_DEPTH = -1;
const std::pair<int32_t, int32_t> RANGE { -1, 0 };
const std::pair<int32_t, int32_t> RANGE_0 { 0, 0 };

constexpr float RK356_WIDTH = 720.0f;
constexpr float RK356_HEIGHT = 1136.0f;
constexpr float ROW_HEIGHT = 120.0f;

const SizeF CONTAINER_SIZE { RK356_WIDTH, RK356_HEIGHT };
SizeF SELF_IDEAL_SIZE { RK356_WIDTH, ROW_HEIGHT };
SizeF FRAME_SIZE { 0, 0 };
const SizeF TEST_FRAME_SIZE { 0, 0 };
OptionalSize IDEAL_SIZE { 0, 0 };

const std::string TEST_TAG = "";
const std::string ROW_FRAME_NODE = "rowFrameNode";
const std::string FIRST_FRAME_NODE = "TabContent";
const std::string FIRST_CHILD_FRAME_NODE = "firstChildFrameNode";
const std::string SECOND_CHILD_FRAME_NODE = "secondChildFrameNode";
const std::string THIRD_CHILD_FRAME_NODE = "thirdChildFrameNode";

constexpr bool TEST_TRUE = true;
constexpr bool TEST_FALSE = false;

inline std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateNodeAndWrapper(const std::string& tag, int32_t nodeId)
{
    auto node = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(node, geometryNode, node->GetLayoutProperty());

    return std::make_pair(node, layoutWrapper);
}
inline RefPtr<LayoutWrapperNode> CreateLayoutWrapper(const std::string& tag, int32_t nodeId)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    return layoutWrapper;
}

inline RefPtr<LayoutWrapperNode> CreateChildLayoutWrapper(const std::string& tag, int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    return layoutWrapper;
}

inline RefPtr<LazyLayoutWrapperBuilder> CreateLayoutWrapperBuilder()
{
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    RefPtr<LazyForEachNode> host_ = AceType::MakeRefPtr<LazyForEachNode>(NODE_ID_1, builder);
    WeakPtr<LazyForEachNode> host(host_);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);

    return wrapperBuilder;
}

inline void UpdateParentConstraint(RefPtr<LayoutWrapperNode> layoutWrapper, LayoutConstraintF& parentConstraint)
{
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);
}
} // namespace

class LayoutWrapperTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

inline void LayoutWrapperTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

inline void LayoutWrapperTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_TEST_UNITTEST_LAYOUT_WRAPPER_TEST_NG_H