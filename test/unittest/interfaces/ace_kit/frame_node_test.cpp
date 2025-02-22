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
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_pattern.h"
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_property.h"
#include "ui/properties/dirty_flag.h"
#include "ui/view/frame_node.h"
#include "ui/view_factory/abstract_view_factory.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Kit;
namespace OHOS::Ace {
class FrameNodeTest : public testing::Test {};

/**
 * @tc.name: FrameNodeTestTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest001, TestSize.Level1)
{
    const std::string tag = "TEST1";
    const int32_t id = 1;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);

    EXPECT_EQ(frameNode->GetId(), id);
    auto nodeTag = frameNode->GetTag();
    EXPECT_EQ(tag, nodeTag);
}

/**
 * @tc.name: FrameNodeTestTest002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest002, TestSize.Level1)
{
    const std::string tag = "TEST2";
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, 2, mockPattern);
    EXPECT_NE(frameNode, nullptr);

    auto property = frameNode->GetProperty();
    EXPECT_TRUE(property);

    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);
    auto* aceNodePtr = frameNodeImpl->GetAceNodePtr();
    EXPECT_TRUE(aceNodePtr);
    auto aceNode = frameNodeImpl->GetAceNode();
    EXPECT_TRUE(aceNode);
    auto pattern = frameNodeImpl->GetPattern();
    EXPECT_TRUE(pattern);

    frameNode->Reset();
    EXPECT_FALSE(frameNodeImpl->GetAceNodePtr());
    EXPECT_FALSE(frameNodeImpl->GetAceNode());
    EXPECT_FALSE(frameNodeImpl->GetPattern());
}

/**
 * @tc.name: FrameNodeTestTest003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest003, TestSize.Level1)
{
    const std::string tag = "TEST3";
    const int32_t id = 3;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    auto aceNode =
        NG::FrameNode::GetOrCreateFrameNode("TEST_ACE_NODE", 3, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_TRUE(aceNode);

    auto popAceNode = frameNodeImpl->PopAceNode();
    EXPECT_EQ(popAceNode->GetTag(), tag);
    EXPECT_EQ(popAceNode->GetId(), id);
    EXPECT_FALSE(frameNodeImpl->GetAceNode());
}

/**
 * @tc.name: FrameNodeTestTest004
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest004, TestSize.Level1)
{
    const std::string tag = "TEST4";
    const int32_t id = 4;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    frameNode->AddChild(nullptr);
    EXPECT_EQ(frameNode->GetChildren().size(), 0);

    const std::string childTag = "TEST4_CHILD";
    const int32_t childId = 4;
    auto mockPatternChild = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNodeChild = AbstractViewFactory::CreateFrameNode(childTag, childId, mockPatternChild);
    EXPECT_NE(frameNode, nullptr);
    frameNode->AddChild(frameNodeChild);
    EXPECT_EQ(frameNode->GetChildren().size(), 1);

    frameNode->RemoveChild(frameNodeChild);
    EXPECT_EQ(frameNode->GetChildren().size(), 0);
}

/**
 * @tc.name: FrameNodeTestTest005
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest005, TestSize.Level1)
{
    const std::string tag = "TEST5";
    const int32_t id = 5;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    LayoutConstraintInfo constraint { .maxWidth = 100.0f, .maxHeight = 100.0f };
    frameNode->Measure(constraint);
    auto* aceNode = frameNodeImpl->GetAceNodePtr();
    ASSERT_TRUE(aceNode);
    EXPECT_TRUE(aceNode->IsActive());
    auto geometryNode = aceNode->GetGeometryNode();
    auto parentConstraint = geometryNode->GetParentLayoutConstraint();
    EXPECT_TRUE(NearEqual(parentConstraint.value().maxSize.Width(), constraint.maxWidth));
    EXPECT_TRUE(NearEqual(parentConstraint.value().maxSize.Height(), constraint.maxHeight));

    frameNode->Layout();
    auto layoutProperty = aceNode->GetLayoutProperty();
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    EXPECT_TRUE(NearEqual(layoutConstraint.value().maxSize.Width(), constraint.maxWidth));
    EXPECT_TRUE(NearEqual(layoutConstraint.value().maxSize.Height(), constraint.maxHeight));

    auto propertyChangeFlag = layoutProperty->GetPropertyChangeFlag();
    EXPECT_EQ(propertyChangeFlag, NG::PROPERTY_UPDATE_MEASURE | NG::PROPERTY_UPDATE_LAYOUT);
    frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(),
        NG::PROPERTY_UPDATE_MEASURE | NG::PROPERTY_UPDATE_LAYOUT | NG::PROPERTY_UPDATE_MEASURE_SELF);
}
} // namespace OHOS::Ace
