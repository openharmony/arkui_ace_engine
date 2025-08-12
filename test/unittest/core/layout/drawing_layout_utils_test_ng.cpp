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

#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/drawing_layout_utils.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/property/layout_constraint.h"


#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class DrawingLayoutUtilsTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: MeasureLayoutPolicySizeTest001
 * @tc.desc: Test MeasureLayoutPolicySize
 * @tc.type: FUNC
 */
HWTEST_F(DrawingLayoutUtilsTestNg, MeasureLayoutPolicySizeTest001, TestSize.Level1)
{
    auto node = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 0, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutProperty> layoutProperty = node->GetLayoutProperty();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(node, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;

    /**
     * @tc.steps1: Width is matchParent
     * @tc.expected: the return size of MeasureLayoutPolicySize is (300, 1000)
     */
    SizeF size = SizeF(1000.0f, 1000.0f);
    layoutConstraint.parentIdealSize = OptionalSizeF(300.0f, 400.0f);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    MeasureLayoutPolicySize(layoutConstraint, &layoutWrapper, size);
    EXPECT_EQ(size.Width(), 300);
    EXPECT_EQ(size.Height(), 1000);

    /**
     * @tc.steps2: Height is matchParent
     * @tc.expected: the return size of MeasureLayoutPolicySize is (1000, 400)
     */
    size = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    MeasureLayoutPolicySize(layoutConstraint, &layoutWrapper, size);
    EXPECT_EQ(size.Width(), 1000);
    EXPECT_EQ(size.Height(), 400);

    /**
     * @tc.steps3: Width and Height are NO_MATCH
     * @tc.expected: the return size of MeasureLayoutPolicySize is (1000, 1000)
     */
    size = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    MeasureLayoutPolicySize(layoutConstraint, &layoutWrapper, size);
    EXPECT_EQ(size.Width(), 1000);
    EXPECT_EQ(size.Height(), 1000);

    /**
     * @tc.steps4: layoutPolicy has no value
     * @tc.expected: the return size of MeasureLayoutPolicySize is (1000, 1000)
     */
    layoutProperty->layoutPolicy_ = std::nullopt;
    MeasureLayoutPolicySize(layoutConstraint, &layoutWrapper, size);
    EXPECT_EQ(size.Width(), 1000);
    EXPECT_EQ(size.Height(), 1000);

    /**
     * @tc.steps5: layoutProperty is nullptr
     * @tc.expected: the return size of MeasureLayoutPolicySize is (1000, 1000)
     */
    layoutProperty.Reset();
    MeasureLayoutPolicySize(layoutConstraint, &layoutWrapper, size);
    EXPECT_EQ(size.Width(), 1000);
    EXPECT_EQ(size.Height(), 1000);
}

/**
 * @tc.name: MeasureLayoutPolicySizeTest002
 * @tc.desc: Test MeasureLayoutPolicySize
 * @tc.type: FUNC
 */
HWTEST_F(DrawingLayoutUtilsTestNg, MeasureLayoutPolicySizeTest002, TestSize.Level1)
{
    auto node = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 0, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutProperty> layoutProperty = node->GetLayoutProperty();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(node, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;

    /**
     * @tc.steps1: Width is WrapContent
     * @tc.expected: the return size of MeasureLayoutPolicySize is (0, 1000)
     */
    SizeF size = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    MeasureLayoutPolicySize(layoutConstraint, &layoutWrapper, size);
    EXPECT_EQ(size.Width(), 0);
    EXPECT_EQ(size.Height(), 1000);

    /**
     * @tc.steps2: Height is WrapContent
     * @tc.expected: the return size of MeasureLayoutPolicySize is (1000, 0)
     */
    size = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
    MeasureLayoutPolicySize(layoutConstraint, &layoutWrapper, size);
    EXPECT_EQ(size.Width(), 1000);
    EXPECT_EQ(size.Height(), 0);

    /**
     * @tc.steps3: Width is fixIdealSize
     * @tc.expected: the return size of MeasureLayoutPolicySize is (0, 1000)
     */
    size = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    MeasureLayoutPolicySize(layoutConstraint, &layoutWrapper, size);
    EXPECT_EQ(size.Width(), 0);
    EXPECT_EQ(size.Height(), 1000);

    /**
     * @tc.steps4: Height is fixIdealSize
     * @tc.expected: the return size of MeasureLayoutPolicySize is (1000, 0)
     */
    size = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
    MeasureLayoutPolicySize(layoutConstraint, &layoutWrapper, size);
    EXPECT_EQ(size.Width(), 1000);
    EXPECT_EQ(size.Height(), 0);

    /**
     * @tc.steps5: Width and Height are matchParent and parentIdealSize is null
     * @tc.expected: the return size of MeasureLayoutPolicySize is (1000, 1000)
     */
    size = SizeF(1000.0f, 1000.0f);
    layoutConstraint.parentIdealSize.Reset();
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    MeasureLayoutPolicySize(layoutConstraint, &layoutWrapper, size);
    EXPECT_EQ(size.Width(), 1000);
    EXPECT_EQ(size.Height(), 1000);
}
} // namespace OHOS::Ace::NG
