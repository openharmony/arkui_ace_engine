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
#define protected public
#define private public

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "frameworks/core/components_ng/layout/layout_algorithm.h"
#include "frameworks/core/components_ng/layout/layout_wrapper_node.h"
#include "frameworks/core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/flex/flex_model_ng.h"
#include "base/memory/ace_type.h"


namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class LayoutAlgorithmOverflowTestNg : public TestNG {
public:
    static void SetUpTestSuite()
    {
        TestNG::SetUpTestSuite();
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
        TestNG::TearDownTestSuite();
    }
    RefPtr<FrameNode> CreateFlex(const std::function<void(FlexModelNG)>& callback)
    {
        FlexModelNG model;
        model.CreateFlexRow();
        if (callback) {
            callback(model);
        }
        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
        ViewStackProcessor::GetInstance()->PopContainer();
        return AceType::DynamicCast<FrameNode>(element);
    }
};

/**
 * @tc.name: LayoutAlgorithmShouldDoOverflowWorkTest001
 * @tc.desc: Test ShouldDoOverflowWork method when isOverflowWarningEnabled is true
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmOverflowTestNg, LayoutAlgorithmShouldDoOverflowWorkTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    // isOverflowWarningEnabled_ defaults to true
    bool result = layoutAlgorithm->ShouldDoOverflowWork();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: LayoutAlgorithmShouldDoOverflowWorkTest002
 * @tc.desc: Test ShouldDoOverflowWork method when isOverflowWarningEnabled is false
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmOverflowTestNg, LayoutAlgorithmShouldDoOverflowWorkTest002, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = false;
    // In mock, IsPageOverflowEnabled returns false, so ShouldDoOverflowWork returns false
    bool result = layoutAlgorithm->ShouldDoOverflowWork();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LayoutAlgorithmIsContentOverflowNullLayoutWrapperTest001
 * @tc.desc: Test IsContentOverflow with null layout wrapper
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmOverflowTestNg, LayoutAlgorithmIsContentOverflowNullLayoutWrapperTest001, TestSize.Level0)
{
    OverflowCollector collector(false);
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    // Test with null layout wrapper - should return false early
    bool result = layoutAlgorithm->IsContentOverflow(nullptr, collector);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LayoutAlgorithmIsContentOverflowNullHostNodeTest001
 * @tc.desc: Test IsContentOverflow with null host node
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmOverflowTestNg, LayoutAlgorithmIsContentOverflowNullHostNodeTest001, TestSize.Level0)
{
    auto frameNode = FrameNode::CreateFrameNode("test", 10, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    OverflowCollector collector(false);

    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Test with null host node in layoutWrapper - should return false early
    bool result = layoutAlgorithm->IsContentOverflow(AceType::RawPtr(layoutWrapper), collector);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LayoutAlgorithmIsContentOverflowNonOverflowComponentTest001
 * @tc.desc: Test IsContentOverflow with non-overflow component
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmOverflowTestNg, LayoutAlgorithmIsContentOverflowNonOverflowComponentTest001, TestSize.Level0)
{
    // Button is not in OVERFLOW_ENABLED_COMPONENTS
    auto frameNode = FrameNode::CreateFrameNode("Button", 11, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    OverflowCollector collector(false);

    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Should return false because Button is not in OVERFLOW_ENABLED_COMPONENTS
    bool result = layoutAlgorithm->IsContentOverflow(AceType::RawPtr(layoutWrapper), collector);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LayoutAlgorithmIsContentOverflowStackComponentTest001
 * @tc.desc: Test IsContentOverflow with Stack component (overflow enabled)
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmOverflowTestNg, LayoutAlgorithmIsContentOverflowStackComponentTest001, TestSize.Level0)
{
    // Stack is in OVERFLOW_ENABLED_COMPONENTS
    auto frameNode = FrameNode::CreateFrameNode("Stack", 12, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    // Set up frame rect for the frame node using SetFrameSize and SetFrameOffset
    geometryNode->SetFrameSize(SizeF(200.f, 200.f));
    geometryNode->SetFrameOffset(OffsetF(0.f, 0.f));
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    OverflowCollector collector(false);

    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Stack is enabled, but without children there's no overflow
    // IsContentOverflow should return false (no overflow when children fit in content)
    bool result = layoutAlgorithm->IsContentOverflow(AceType::RawPtr(layoutWrapper), collector);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LayoutAlgorithmIsContentOverflowStackComponentWithOverflowTest002
 * @tc.desc: Test IsContentOverflow with Flex component that has overflowing children
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmOverflowTestNg,
         LayoutAlgorithmIsContentOverflowStackComponentWithOverflowTest002,
         TestSize.Level0)
{
    // Create Flex which has FlexLayoutPattern
    auto flex = CreateFlex([](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
    });
    ASSERT_NE(flex, nullptr);
    flex->GetGeometryNode()->SetFrameSize(SizeF(200.f, 200.f));
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(flex, flex->GetGeometryNode(), flex->GetLayoutProperty());
    OverflowCollector collector(false);

    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Get the pattern and handler to set up overflow condition
    auto pattern = flex->GetPattern();
    ASSERT_NE(pattern, nullptr);
    const auto& vOverflowHandler = pattern->GetOrCreateVerticalOverflowHandler(
        AceType::WeakClaim(AceType::RawPtr(flex)));
    ASSERT_NE(vOverflowHandler, nullptr);


    collector.overflowCollectResult_.totalChildFrameRect = RectF(0.f, 0.f, 200.f, 400.f);
    collector.overflowCollectResult_.overflowDisabled = false;

    bool result = layoutAlgorithm->IsContentOverflow(AceType::RawPtr(layoutWrapper), collector);
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace::NG