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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_pattern.h"
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_property.h"
#include "ui/base/geometry/ng/size_t.h"
#include "ui/properties/dirty_flag.h"
#include "ui/view/frame_node.h"
#include "ui/view/layout/box_layout_algorithm.h"
#include "ui/view_factory/abstract_view_factory.h"

#include "core/components_ng/property/layout_constraint.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Kit;
namespace OHOS::Ace {
class BoxLayoutAlgorithmTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    }
    static void TearDownTestSuite()
    {
        MockContainer::Current()->pipelineContext_ = nullptr;
        NG::MockPipelineContext::TearDown();
    }
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: BoxLayoutAlgorithmTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, BoxLayoutAlgorithmTest001, TestSize.Level1)
{
    const std::string tag = "BOX_TEST1";
    const int32_t id = 1;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);
    auto* aceNode = frameNodeImpl->GetAceNodePtr();
    ASSERT_TRUE(aceNode);

    NG::LayoutConstraintF layoutConstraint { .maxSize = NG::SizeF(100, 100),
        .selfIdealSize = NG::OptionalSizeF(50, 50) };
    auto layoutProperty = aceNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    auto layoutAlgorithm = mockPattern->CreateLayoutAlgorithm();
    ASSERT_TRUE(layoutAlgorithm);
    LayoutConstraintInfo constraint { .maxWidth = 100.0f, .maxHeight = 100.0f };
    layoutAlgorithm->Measure(constraint);
    auto geometryNode = aceNode->GetGeometryNode();
    auto frameSize = geometryNode->GetFrameSize();
    EXPECT_TRUE(NearEqual(frameSize.Width(), layoutConstraint.selfIdealSize.Width().value()));
    EXPECT_TRUE(NearEqual(frameSize.Height(), layoutConstraint.selfIdealSize.Height().value()));
}

/**
 * @tc.name: BoxLayoutAlgorithmTest002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, BoxLayoutAlgorithmTest002, TestSize.Level1)
{
    const std::string tag = "BOX_TEST2";
    const int32_t id = 2;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);
    auto* aceNode = frameNodeImpl->GetAceNodePtr();
    ASSERT_TRUE(aceNode);

    NG::LayoutConstraintF layoutConstraint { .maxSize = NG::SizeF(100, 100),
        .selfIdealSize = NG::OptionalSizeF(50, 50) };
    auto layoutProperty = aceNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    auto layoutAlgorithm = mockPattern->CreateLayoutAlgorithm();
    ASSERT_TRUE(layoutAlgorithm);
    BoxLayoutAlgorithm::PerformMeasureSelf(nullptr);
    BoxLayoutAlgorithm::PerformMeasureSelf(AceType::RawPtr(frameNode));

    auto geometryNode = aceNode->GetGeometryNode();
    auto frameSize = geometryNode->GetFrameSize();
    EXPECT_TRUE(NearEqual(frameSize.Width(), layoutConstraint.selfIdealSize.Width().value()));
    EXPECT_TRUE(NearEqual(frameSize.Height(), layoutConstraint.selfIdealSize.Height().value()));

    BoxLayoutAlgorithm::PerformLayout(nullptr);
    BoxLayoutAlgorithm::PerformMeasureSelfWithChildList(nullptr);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, BoxLayoutAlgorithmTest003, TestSize.Level1)
{
    const std::string tag = "BOX_TEST3";
    const int32_t id = 3;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);
    auto* aceNode = frameNodeImpl->GetAceNodePtr();
    ASSERT_TRUE(aceNode);

    NG::LayoutConstraintF layoutConstraint { .maxSize = NG::SizeF(80, 90),
        .selfIdealSize = NG::OptionalSizeF(30, 40) };
    auto layoutProperty = aceNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    auto layoutAlgorithm = mockPattern->CreateLayoutAlgorithm();
    ASSERT_TRUE(layoutAlgorithm);
    LayoutConstraintInfo constraint { .maxWidth = 80.0f, .maxHeight = 90.0f };
    layoutAlgorithm->Measure(constraint);

    NG::LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize = NG::OptionalSizeF(30, 40);
    auto contentSize = layoutAlgorithm->MeasureContent(contentConstraint);
    ASSERT_TRUE(contentSize.has_value());
    EXPECT_TRUE(NearEqual(contentSize->Width(), 30.0f));
    EXPECT_TRUE(NearEqual(contentSize->Height(), 40.0f));
    layoutAlgorithm->Layout();
}

/**
 * @tc.name: BoxLayoutAlgorithmTest004
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, BoxLayoutAlgorithmTest004, TestSize.Level1)
{
    BoxLayoutAlgorithm layoutAlgorithm(WeakPtr<FrameNode> {});
    LayoutConstraintInfo constraint;
    layoutAlgorithm.Measure(constraint);
    layoutAlgorithm.Layout();

    NG::LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize = NG::OptionalSizeF(10, 20);
    auto contentSize = layoutAlgorithm.MeasureContent(contentConstraint);
    EXPECT_FALSE(contentSize.has_value());
}

/**
 * @tc.name: BoxLayoutAlgorithmTest005
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, BoxLayoutAlgorithmTest005, TestSize.Level1)
{
    auto nullFrameNode = AceType::MakeRefPtr<FrameNodeImpl>(static_cast<AceNode*>(nullptr));
    ASSERT_TRUE(nullFrameNode);
    BoxLayoutAlgorithm::PerformMeasureSelfWithChildList(AceType::RawPtr(nullFrameNode));

    const std::string tag = "BOX_TEST5";
    const int32_t id = 5;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    ASSERT_TRUE(frameNode);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);
    auto* aceNode = frameNodeImpl->GetAceNodePtr();
    ASSERT_TRUE(aceNode);

    NG::LayoutConstraintF layoutConstraint { .maxSize = NG::SizeF(60, 70),
        .selfIdealSize = NG::OptionalSizeF(20, 30) };
    auto layoutProperty = aceNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    BoxLayoutAlgorithm::PerformMeasureSelfWithChildList(AceType::RawPtr(frameNode));
}
} // namespace OHOS::Ace
