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
#include "ui/properties/property.h"
#include "ui/view/frame_node.h"
#include "ui/view_factory/abstract_view_factory.h"

#include "core/components_ng/property/property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Kit {
class PropertyTest : public testing::Test {
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
 * @tc.name: PropertyTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTest, PropertyTest001, TestSize.Level1)
{
    const std::string tag = "TEST1";
    const int32_t id = 1;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    auto layoutProperty = frameNodeImpl->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto propertyChangeFlag = layoutProperty->GetPropertyChangeFlag();
    EXPECT_EQ(propertyChangeFlag, NG::PROPERTY_UPDATE_MEASURE);
    auto property = frameNode->GetProperty();
    ASSERT_TRUE(property);
    property->CleanDirty();
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: PropertyTest002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTest, PropertyTest002, TestSize.Level1)
{
    const std::string tag = "TEST2";
    const int32_t id = 1;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    auto layoutProperty = frameNodeImpl->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto propertyChangeFlag = layoutProperty->GetPropertyChangeFlag();
    EXPECT_EQ(propertyChangeFlag, NG::PROPERTY_UPDATE_MEASURE);
    auto property = frameNode->GetProperty();
    ASSERT_TRUE(property);
    property->UpdateRender();
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_MEASURE | NG::PROPERTY_UPDATE_RENDER);
    auto aceNode = frameNodeImpl->GetAceNodePtr();
    ASSERT_TRUE(aceNode);
    auto paintProp = aceNode->GetPaintProperty<NG::Property>();
    ASSERT_TRUE(paintProp);
    EXPECT_EQ(paintProp->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_RENDER);
}

/**
 * @tc.name: PropertyTest003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTest, PropertyTest003, TestSize.Level1)
{
    const std::string tag = "TEST3";
    const int32_t id = 1;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    auto layoutProperty = frameNodeImpl->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto propertyChangeFlag = layoutProperty->GetPropertyChangeFlag();
    EXPECT_EQ(propertyChangeFlag, NG::PROPERTY_UPDATE_MEASURE);
    auto property = frameNode->GetProperty();
    ASSERT_TRUE(property);
    property->CleanDirty();
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_NORMAL);

    property->UpdateMeasure(true);
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_MEASURE_SELF);
    property->CleanDirty();
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_NORMAL);
    property->UpdateMeasure(false);
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: PropertyTest004
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTest, PropertyTest004, TestSize.Level1)
{
    const std::string tag = "TEST4";
    const int32_t id = 1;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    auto aceNode = frameNodeImpl->GetAceNodePtr();
    ASSERT_TRUE(aceNode);
    auto paintProp = aceNode->GetPaintProperty<NG::Property>();
    ASSERT_TRUE(paintProp);
    EXPECT_EQ(paintProp->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_NORMAL);
    auto property = frameNode->GetProperty();
    ASSERT_TRUE(property);
    property->UpdatePaintFlag(NG::PROPERTY_UPDATE_RENDER);
    EXPECT_EQ(paintProp->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_RENDER);
}

/**
 * @tc.name: PropertyTest005
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTest, PropertyTest005, TestSize.Level1)
{
    const std::string tag = "TEST5";
    const int32_t id = 1;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    auto layoutProperty = frameNodeImpl->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto propertyChangeFlag = layoutProperty->GetPropertyChangeFlag();
    EXPECT_EQ(propertyChangeFlag, NG::PROPERTY_UPDATE_MEASURE);
    auto property = frameNode->GetProperty();
    ASSERT_TRUE(property);
    property->CleanDirty();
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_NORMAL);

    property->UpdateLayoutFlag(NG::PROPERTY_UPDATE_MEASURE_SELF);
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_MEASURE_SELF);
    property->UpdateLayoutFlag(NG::PROPERTY_UPDATE_LAYOUT);
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_MEASURE_SELF | NG::PROPERTY_UPDATE_LAYOUT);
}
} // namespace OHOS::Ace::Kit
