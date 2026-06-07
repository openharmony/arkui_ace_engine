/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#define private public
#define protected public

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "base/utils/system_properties.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/state_attributes.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"
#include "core/common/resource/resource_object.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
using OHOS::Ace::g_isConfigChangePerform;

namespace OHOS::Ace::NG {
namespace {

constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t TEST_NODE_ID_SECOND = 101;
constexpr size_t TEST_DASH_ARRAY_SIZE = 2;
constexpr double TEST_DASH_ARRAY_FIRST = 3.0;
constexpr double TEST_DASH_ARRAY_SECOND = 5.0;

RefPtr<ShapePaintProperty> GetShapePaintProperty(const RefPtr<FrameNode>& frameNode)
{
    EXPECT_NE(frameNode, nullptr);
    return frameNode->GetPaintProperty<ShapePaintProperty>();
}

std::vector<Dimension> MakeTestDashArray()
{
    return { Dimension(TEST_DASH_ARRAY_FIRST), Dimension(TEST_DASH_ARRAY_SECOND) };
}

std::vector<RefPtr<ResourceObject>> MakeTestResObjArray(size_t count)
{
    std::vector<RefPtr<ResourceObject>> resObjArray(count);
    for (size_t i = 0; i < count; ++i) {
        resObjArray[i] = AceType::MakeRefPtr<ResourceObject>();
    }
    return resObjArray;
}
} // namespace

class ShapeAbstractModelNGTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }

    void TearDown() override
    {
        g_isConfigChangePerform = false;
        ViewStackProcessor::GetInstance()->ClearVisualState();
        auto* stack = ViewStackProcessor::GetInstance();
        if (stack->GetMainFrameNode()) {
            stack->Pop();
        }
    }

    RefPtr<FrameNode> CreateCircleNode()
    {
        CircleModelNG().Create();
        return AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }

    RefPtr<FrameNode> CreateCircleFrameNode(int32_t nodeId)
    {
        return CircleModelNG::CreateFrameNode(nodeId);
    }
};


/**
 * @tc.name: SetStrokeDashArrayResObj_ConfigChangePerformFalse
 * @tc.desc: SetStrokeDashArray with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeDashArrayResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto segments = MakeTestDashArray();
    auto resObjArray = MakeTestResObjArray(TEST_DASH_ARRAY_SIZE);
    ShapeAbstractModelNG().SetStrokeDashArray(segments, resObjArray);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStrokeDashArray());
}

/**
 * @tc.name: SetStrokeDashArrayResObj_ConfigChangePerformTrue
 * @tc.desc: SetStrokeDashArray with ResourceObject proceeds when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeDashArrayResObj_ConfigChangePerformTrue, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto segments = MakeTestDashArray();
    auto resObjArray = MakeTestResObjArray(TEST_DASH_ARRAY_SIZE);
    ShapeAbstractModelNG().SetStrokeDashArray(segments, resObjArray);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStrokeDashArray());
}

/**
 * @tc.name: SetStrokeResObj_ConfigChangePerformFalse
 * @tc.desc: SetStroke with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetStroke(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStroke());
}

/**
 * @tc.name: SetStrokeResObj_ConfigChangePerformTrue
 * @tc.desc: SetStroke with ResourceObject proceeds when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeResObj_ConfigChangePerformTrue, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetStroke(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStroke());
}

/**
 * @tc.name: SetFillResObj_ConfigChangePerformFalse
 * @tc.desc: SetFill with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetFillResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetFill(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasFill());
}

/**
 * @tc.name: SetFillResObj_ConfigChangePerformTrue
 * @tc.desc: SetFill with ResourceObject proceeds when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetFillResObj_ConfigChangePerformTrue, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetFill(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasFill());
}

/**
 * @tc.name: SetForegroundColorResObj_ConfigChangePerformFalse
 * @tc.desc: SetForegroundColor with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetForegroundColorResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetForegroundColor(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasFill());
}

/**
 * @tc.name: SetForegroundColorResObj_ConfigChangePerformTrue
 * @tc.desc: SetForegroundColor with ResourceObject proceeds when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetForegroundColorResObj_ConfigChangePerformTrue, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetForegroundColor(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasFill());
}

/**
 * @tc.name: SetStrokeOpacityResObj_ConfigChangePerformFalse
 * @tc.desc: SetStrokeOpacity with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeOpacityResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetStrokeOpacity(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStrokeOpacity());
}

/**
 * @tc.name: SetStrokeOpacityResObj_ConfigChangePerformTrue
 * @tc.desc: SetStrokeOpacity with ResourceObject proceeds when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeOpacityResObj_ConfigChangePerformTrue, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetStrokeOpacity(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStrokeOpacity());
}

/**
 * @tc.name: SetFillOpacityResObj_ConfigChangePerformFalse
 * @tc.desc: SetFillOpacity with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetFillOpacityResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetFillOpacity(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasFillOpacity());
}

/**
 * @tc.name: SetFillOpacityResObj_ConfigChangePerformTrue
 * @tc.desc: SetFillOpacity with ResourceObject proceeds when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetFillOpacityResObj_ConfigChangePerformTrue, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetFillOpacity(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasFillOpacity());
}

/**
 * @tc.name: SetStrokeWidthResObj_ConfigChangePerformFalse
 * @tc.desc: SetStrokeWidth with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeWidthResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetStrokeWidth(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStrokeWidth());
}

/**
 * @tc.name: SetStrokeWidthResObj_ConfigChangePerformTrue
 * @tc.desc: SetStrokeWidth with ResourceObject proceeds when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeWidthResObj_ConfigChangePerformTrue, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetStrokeWidth(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStrokeWidth());
}

/**
 * @tc.name: SetWidthResObj_ConfigChangePerformFalse
 * @tc.desc: SetWidth with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetWidthResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetWidth(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr);
}

/**
 * @tc.name: SetWidthResObj_ConfigChangePerformTrue
 * @tc.desc: SetWidth with ResourceObject proceeds when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetWidthResObj_ConfigChangePerformTrue, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetWidth(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr);
}

/**
 * @tc.name: SetHeightResObj_ConfigChangePerformFalse
 * @tc.desc: SetHeight with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetHeightResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetHeight(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr);
}

/**
 * @tc.name: SetHeightResObj_ConfigChangePerformTrue
 * @tc.desc: SetHeight with ResourceObject proceeds when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetHeightResObj_ConfigChangePerformTrue, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG().SetHeight(resObj);
    ViewStackProcessor::GetInstance()->Pop();
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr);
}


/**
 * @tc.name: SetStrokeDashArrayFrameNode_ConfigChangePerformFalse
 * @tc.desc: SetStrokeDashArray with FrameNode returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeDashArrayFrameNode_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto segments = MakeTestDashArray();
    auto resObjArray = MakeTestResObjArray(TEST_DASH_ARRAY_SIZE);
    ShapeAbstractModelNG::SetStrokeDashArray(
        AceType::RawPtr(frameNode), segments, resObjArray);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStrokeDashArray());
}

/**
 * @tc.name: SetStrokeDashArrayFrameNode_NullFrameNode
 * @tc.desc: SetStrokeDashArray with FrameNode returns early when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeDashArrayFrameNode_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto segments = MakeTestDashArray();
    auto resObjArray = MakeTestResObjArray(TEST_DASH_ARRAY_SIZE);
    auto otherNode = CreateCircleFrameNode(TEST_NODE_ID_SECOND);
    ShapeAbstractModelNG::SetStrokeDashArray(nullptr, segments, resObjArray);
    auto paintProperty = GetShapePaintProperty(otherNode);
    EXPECT_FALSE(paintProperty->HasStrokeDashArray());
}

/**
 * @tc.name: SetStrokeDashArrayFrameNode_ValidFrameNode
 * @tc.desc: SetStrokeDashArray with FrameNode proceeds when ConfigChangePerform is true and frameNode is valid
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeDashArrayFrameNode_ValidFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    size_t initialSize = pattern->resourceMgr_->resMap_.size();

    auto segments = MakeTestDashArray();
    auto resObjArray = MakeTestResObjArray(TEST_DASH_ARRAY_SIZE);
    ShapeAbstractModelNG::SetStrokeDashArray(
        AceType::RawPtr(frameNode), segments, resObjArray);

    EXPECT_GT(pattern->resourceMgr_->resMap_.size(), initialSize);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStrokeDashArray());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetStrokeFrameNode_ConfigChangePerformFalse
 * @tc.desc: SetStroke with FrameNode returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeFrameNode_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetStroke(AceType::RawPtr(frameNode), resObj);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStroke());
}

/**
 * @tc.name: SetStrokeFrameNode_NullFrameNode
 * @tc.desc: SetStroke with FrameNode returns early when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeFrameNode_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto otherNode = CreateCircleFrameNode(TEST_NODE_ID_SECOND);
    ShapeAbstractModelNG::SetStroke(nullptr, resObj);
    auto paintProperty = GetShapePaintProperty(otherNode);
    EXPECT_FALSE(paintProperty->HasStroke());
}

/**
 * @tc.name: SetStrokeFrameNode_ValidFrameNode
 * @tc.desc: SetStroke with FrameNode proceeds when ConfigChangePerform is true and frameNode is valid
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeFrameNode_ValidFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    size_t initialSize = pattern->resourceMgr_->resMap_.size();

    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetStroke(AceType::RawPtr(frameNode), resObj);

    EXPECT_GT(pattern->resourceMgr_->resMap_.size(), initialSize);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStroke());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetFillFrameNode_ConfigChangePerformFalse
 * @tc.desc: SetFill with FrameNode returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetFillFrameNode_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetFill(AceType::RawPtr(frameNode), resObj);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasFill());
}

/**
 * @tc.name: SetFillFrameNode_NullFrameNode
 * @tc.desc: SetFill with FrameNode returns early when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetFillFrameNode_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto otherNode = CreateCircleFrameNode(TEST_NODE_ID_SECOND);
    ShapeAbstractModelNG::SetFill(nullptr, resObj);
    auto paintProperty = GetShapePaintProperty(otherNode);
    EXPECT_FALSE(paintProperty->HasFill());
}

/**
 * @tc.name: SetFillFrameNode_ValidFrameNode
 * @tc.desc: SetFill with FrameNode proceeds when ConfigChangePerform is true and frameNode is valid
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetFillFrameNode_ValidFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    size_t initialSize = pattern->resourceMgr_->resMap_.size();

    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetFill(AceType::RawPtr(frameNode), resObj);

    EXPECT_GT(pattern->resourceMgr_->resMap_.size(), initialSize);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasFill());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetForegroundColorFrameNode_ConfigChangePerformFalse
 * @tc.desc: SetForegroundColor with FrameNode returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetForegroundColorFrameNode_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetForegroundColor(AceType::RawPtr(frameNode), resObj);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasFill());
}

/**
 * @tc.name: SetForegroundColorFrameNode_NullFrameNode
 * @tc.desc: SetForegroundColor with FrameNode returns early when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetForegroundColorFrameNode_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto otherNode = CreateCircleFrameNode(TEST_NODE_ID_SECOND);
    ShapeAbstractModelNG::SetForegroundColor(nullptr, resObj);
    auto paintProperty = GetShapePaintProperty(otherNode);
    EXPECT_FALSE(paintProperty->HasFill());
}

/**
 * @tc.name: SetForegroundColorFrameNode_ValidFrameNode
 * @tc.desc: SetForegroundColor with FrameNode proceeds when ConfigChangePerform is true and frameNode is valid
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetForegroundColorFrameNode_ValidFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    size_t initialSize = pattern->resourceMgr_->resMap_.size();

    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetForegroundColor(AceType::RawPtr(frameNode), resObj);

    EXPECT_GT(pattern->resourceMgr_->resMap_.size(), initialSize);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasFill());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetStrokeOpacityFrameNode_ConfigChangePerformFalse
 * @tc.desc: SetStrokeOpacity with FrameNode returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeOpacityFrameNode_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetStrokeOpacity(AceType::RawPtr(frameNode), resObj);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStrokeOpacity());
}

/**
 * @tc.name: SetStrokeOpacityFrameNode_NullFrameNode
 * @tc.desc: SetStrokeOpacity with FrameNode returns early when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeOpacityFrameNode_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto otherNode = CreateCircleFrameNode(TEST_NODE_ID_SECOND);
    ShapeAbstractModelNG::SetStrokeOpacity(nullptr, resObj);
    auto paintProperty = GetShapePaintProperty(otherNode);
    EXPECT_FALSE(paintProperty->HasStrokeOpacity());
}

/**
 * @tc.name: SetStrokeOpacityFrameNode_ValidFrameNode
 * @tc.desc: SetStrokeOpacity with FrameNode proceeds when ConfigChangePerform is true and frameNode is valid
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeOpacityFrameNode_ValidFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    size_t initialSize = pattern->resourceMgr_->resMap_.size();

    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetStrokeOpacity(AceType::RawPtr(frameNode), resObj);

    EXPECT_GT(pattern->resourceMgr_->resMap_.size(), initialSize);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStrokeOpacity());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetFillOpacityFrameNode_ConfigChangePerformFalse
 * @tc.desc: SetFillOpacity with FrameNode returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetFillOpacityFrameNode_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetFillOpacity(AceType::RawPtr(frameNode), resObj);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasFillOpacity());
}

/**
 * @tc.name: SetFillOpacityFrameNode_NullFrameNode
 * @tc.desc: SetFillOpacity with FrameNode returns early when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetFillOpacityFrameNode_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto otherNode = CreateCircleFrameNode(TEST_NODE_ID_SECOND);
    ShapeAbstractModelNG::SetFillOpacity(nullptr, resObj);
    auto paintProperty = GetShapePaintProperty(otherNode);
    EXPECT_FALSE(paintProperty->HasFillOpacity());
}

/**
 * @tc.name: SetFillOpacityFrameNode_ValidFrameNode
 * @tc.desc: SetFillOpacity with FrameNode proceeds when ConfigChangePerform is true and frameNode is valid
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetFillOpacityFrameNode_ValidFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    size_t initialSize = pattern->resourceMgr_->resMap_.size();

    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetFillOpacity(AceType::RawPtr(frameNode), resObj);

    EXPECT_GT(pattern->resourceMgr_->resMap_.size(), initialSize);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasFillOpacity());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetStrokeWidthFrameNode_ConfigChangePerformFalse
 * @tc.desc: SetStrokeWidth with FrameNode returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeWidthFrameNode_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetStrokeWidth(AceType::RawPtr(frameNode), resObj);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStrokeWidth());
}

/**
 * @tc.name: SetStrokeWidthFrameNode_NullFrameNode
 * @tc.desc: SetStrokeWidth with FrameNode returns early when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeWidthFrameNode_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto otherNode = CreateCircleFrameNode(TEST_NODE_ID_SECOND);
    ShapeAbstractModelNG::SetStrokeWidth(nullptr, resObj);
    auto paintProperty = GetShapePaintProperty(otherNode);
    EXPECT_FALSE(paintProperty->HasStrokeWidth());
}

/**
 * @tc.name: SetStrokeWidthFrameNode_ValidFrameNode
 * @tc.desc: SetStrokeWidth with FrameNode proceeds when ConfigChangePerform is true and frameNode is valid
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetStrokeWidthFrameNode_ValidFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    size_t initialSize = pattern->resourceMgr_->resMap_.size();

    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetStrokeWidth(AceType::RawPtr(frameNode), resObj);

    EXPECT_GT(pattern->resourceMgr_->resMap_.size(), initialSize);
    auto paintProperty = GetShapePaintProperty(frameNode);
    EXPECT_FALSE(paintProperty->HasStrokeWidth());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetWidthFrameNode_ConfigChangePerformFalse
 * @tc.desc: SetWidth with FrameNode returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetWidthFrameNode_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetWidth(AceType::RawPtr(frameNode), resObj);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr);
}

/**
 * @tc.name: SetWidthFrameNode_NullFrameNode
 * @tc.desc: SetWidth with FrameNode returns early when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetWidthFrameNode_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto otherNode = CreateCircleFrameNode(TEST_NODE_ID_SECOND);
    ShapeAbstractModelNG::SetWidth(nullptr, resObj);
    auto layoutProperty = otherNode->GetLayoutProperty();
    EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr);
}

/**
 * @tc.name: SetWidthFrameNode_ValidFrameNode
 * @tc.desc: SetWidth with FrameNode proceeds when ConfigChangePerform is true and frameNode is valid
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetWidthFrameNode_ValidFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    size_t initialSize = pattern->resourceMgr_->resMap_.size();

    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetWidth(AceType::RawPtr(frameNode), resObj);

    EXPECT_GT(pattern->resourceMgr_->resMap_.size(), initialSize);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetHeightFrameNode_ConfigChangePerformFalse
 * @tc.desc: SetHeight with FrameNode returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetHeightFrameNode_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetHeight(AceType::RawPtr(frameNode), resObj);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr);
}

/**
 * @tc.name: SetHeightFrameNode_NullFrameNode
 * @tc.desc: SetHeight with FrameNode returns early when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetHeightFrameNode_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto otherNode = CreateCircleFrameNode(TEST_NODE_ID_SECOND);
    ShapeAbstractModelNG::SetHeight(nullptr, resObj);
    auto layoutProperty = otherNode->GetLayoutProperty();
    EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr);
}

/**
 * @tc.name: SetHeightFrameNode_ValidFrameNode
 * @tc.desc: SetHeight with FrameNode proceeds when ConfigChangePerform is true and frameNode is valid
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelNGTest, SetHeightFrameNode_ValidFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateCircleFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    size_t initialSize = pattern->resourceMgr_->resMap_.size();

    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeAbstractModelNG::SetHeight(AceType::RawPtr(frameNode), resObj);

    EXPECT_GT(pattern->resourceMgr_->resMap_.size(), initialSize);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr);
    g_isConfigChangePerform = false;
}

} // namespace OHOS::Ace::NG
