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

// NOLINTBEGIN
#define private public
#define protected public
// NOLINTEND

#include <memory>

#include "gtest/gtest.h"
#include "include/core/SkCanvas.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_resource_adapter_v2.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/common/resource/pattern_resource_manager.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/shape/polygon_model_ng.h"
#include "core/components_ng/pattern/shape/polygon_paint_property.h"
#include "core/components_ng/pattern/shape/polygon_pattern.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"
#include "core/components_ng/pattern/shape/shape_layout_algorithm.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
using OHOS::Ace::g_isConfigChangePerform;

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t ID_P0_X = 3001;
constexpr int32_t ID_P0_Y = 3002;
constexpr int32_t ID_P1_X = 3003;
constexpr int32_t ID_P1_Y = 3004;
constexpr Dimension MOCK_DIM_X1 = Dimension(10.0f);
constexpr Dimension MOCK_DIM_Y1 = Dimension(20.0f);
constexpr Dimension MOCK_DIM_X2 = Dimension(30.0f);
constexpr Dimension MOCK_DIM_Y2 = Dimension(40.0f);
constexpr float ORIGINAL_POINT_X1 = 5.0f;
constexpr float ORIGINAL_POINT_Y1 = 15.0f;
constexpr float ORIGINAL_POINT_X2 = 25.0f;
constexpr float ORIGINAL_POINT_Y2 = 35.0f;
constexpr float ORIGINAL_POINT_X3 = 45.0f;
constexpr float ORIGINAL_POINT_Y3 = 55.0f;
constexpr size_t POINTS_COUNT_THREE = 3;
constexpr size_t POINTS_COUNT_TWO = 2;

RefPtr<FrameNode> CreatePolygonFrameNode()
{
    PolygonModelNG().Create(true);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    return frameNode;
}

RefPtr<FrameNode> CreatePolylineFrameNode()
{
    PolygonModelNG().Create(false);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    return frameNode;
}

RefPtr<ResourceObject> CreateInvalidResObj()
{
    return AceType::MakeRefPtr<ResourceObject>("", "", 0);
}

RefPtr<ResourceObject> CreateValidResObj(int32_t resId)
{
    std::vector<ResourceObjectParams> params;
    return AceType::MakeRefPtr<ResourceObject>(
        resId, static_cast<int32_t>(ResourceType::FLOAT), params, "", "", Container::CurrentIdSafely());
}

ShapePoints MakeOriginalPoints3()
{
    return {
        { Dimension(ORIGINAL_POINT_X1), Dimension(ORIGINAL_POINT_Y1) },
        { Dimension(ORIGINAL_POINT_X2), Dimension(ORIGINAL_POINT_Y2) },
        { Dimension(ORIGINAL_POINT_X3), Dimension(ORIGINAL_POINT_Y3) },
    };
}

ShapePoints MakeOriginalPoints2()
{
    return {
        { Dimension(ORIGINAL_POINT_X1), Dimension(ORIGINAL_POINT_Y1) },
        { Dimension(ORIGINAL_POINT_X2), Dimension(ORIGINAL_POINT_Y2) },
    };
}
} // namespace

class PolygonModelNGTddTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        frameNode_ = CreatePolygonFrameNode();
    }

    void TearDown() override
    {
        g_isConfigChangePerform = false;
        auto* stack = ViewStackProcessor::GetInstance();
        if (stack->GetMainFrameNode()) {
            stack->Pop();
        }
    }

protected:
    RefPtr<FrameNode> frameNode_;
};

/**
 * @tc.name: PolygonModelNG_CreatePolygonTrue
 * @tc.desc: Create(true) produces a node with POLYGON_ETS_TAG and PolygonPattern
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_CreatePolygonTrue, TestSize.Level1)
{
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::POLYGON_ETS_TAG);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_CreatePolygonFalse
 * @tc.desc: Create(false) produces a node with POLYLINE_ETS_TAG
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_CreatePolygonFalse, TestSize.Level1)
{
    auto frameNode = CreatePolylineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::POLYLINE_ETS_TAG);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsValid
 * @tc.desc: Non-static SetPoints updates PolygonPaintProperty with exact points
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsValid, TestSize.Level1)
{
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    ShapePoints points = MakeOriginalPoints3();
    PolygonModelNG().SetPoints(points);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasPoints());
    auto retrieved = paintProperty->GetPointsValue();
    ASSERT_EQ(retrieved.size(), POINTS_COUNT_THREE);
    EXPECT_FLOAT_EQ(retrieved[0].first.ConvertToPx(), ORIGINAL_POINT_X1);
    EXPECT_FLOAT_EQ(retrieved[0].second.ConvertToPx(), ORIGINAL_POINT_Y1);
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsEmpty
 * @tc.desc: Non-static SetPoints with empty vector sets property to empty
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsEmpty, TestSize.Level1)
{
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    ShapePoints emptyPoints;
    PolygonModelNG().SetPoints(emptyPoints);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasPoints());
    EXPECT_TRUE(paintProperty->GetPointsValue().empty());
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsOverwrite
 * @tc.desc: Calling SetPoints twice overwrites the previous value
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsOverwrite, TestSize.Level1)
{
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    ShapePoints initial = { { Dimension(ORIGINAL_POINT_X1), Dimension(ORIGINAL_POINT_Y1) } };
    PolygonModelNG().SetPoints(initial);
    ShapePoints updated = MakeOriginalPoints2();
    PolygonModelNG().SetPoints(updated);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetPointsValue().size(), POINTS_COUNT_TWO);
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsStaticValid
 * @tc.desc: Static SetPoints(frameNode, points) updates the paint property
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsStaticValid, TestSize.Level1)
{
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    ShapePoints points = MakeOriginalPoints3();
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasPoints());
    auto retrieved = paintProperty->GetPointsValue();
    ASSERT_EQ(retrieved.size(), POINTS_COUNT_THREE);
    EXPECT_FLOAT_EQ(retrieved[0].first.ConvertToPx(), ORIGINAL_POINT_X1);
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsStaticNullFrameNode
 * @tc.desc: Static SetPoints(nullptr, points) returns early without crash
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsStaticNullFrameNode, TestSize.Level1)
{
    ShapePoints points = MakeOriginalPoints3();
    PolygonModelNG::SetPoints(nullptr, points);
    // No crash - method returned early
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_Static_ConfigChangePerformFalse
 * @tc.desc: Static SetPoints with resObj returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_Static_ConfigChangePerformFalse, TestSize.Level1)
{
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    if (pattern->resourceMgr_ == nullptr) {
        pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    }
    auto initialSize = pattern->resourceMgr_->resMap_.size();

    g_isConfigChangePerform = false;
    ShapePoints points = MakeOriginalPoints3();
    std::vector<RefPtr<ResourceObject>> xResObjArray(POINTS_COUNT_THREE);
    std::vector<RefPtr<ResourceObject>> yResObjArray(POINTS_COUNT_THREE);
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);

    EXPECT_EQ(pattern->resourceMgr_->resMap_.size(), initialSize);
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_Static_NullFrameNode
 * @tc.desc: Static SetPoints with resObj returns early when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreatePolygonFrameNode();
    ASSERT_NE(observerNode, nullptr);
    auto paintProperty = observerNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints3();
    std::vector<RefPtr<ResourceObject>> xResObjArray(POINTS_COUNT_THREE);
    std::vector<RefPtr<ResourceObject>> yResObjArray(POINTS_COUNT_THREE);
    PolygonModelNG::SetPoints(nullptr, points, xResObjArray, yResObjArray);

    EXPECT_FALSE(paintProperty->HasPoints());
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_Static_NullPattern
 * @tc.desc: Static SetPoints with resObj returns early when frameNode has no PolygonPattern
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_Static_NullPattern, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    RefPtr<FrameNode> nonShapeNode = FrameNode::GetOrCreateFrameNode(
        "DummyTag", nodeId, []() { return AceType::MakeRefPtr<ShapeContainerPattern>(); });
    ASSERT_NE(nonShapeNode, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints3();
    std::vector<RefPtr<ResourceObject>> xResObjArray(POINTS_COUNT_THREE);
    std::vector<RefPtr<ResourceObject>> yResObjArray(POINTS_COUNT_THREE);
    PolygonModelNG::SetPoints(AceType::RawPtr(nonShapeNode), points, xResObjArray, yResObjArray);

    auto paintProperty = nonShapeNode->GetPaintProperty<PolygonPaintProperty>();
    EXPECT_EQ(paintProperty, nullptr);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_SizeMismatchX
 * @tc.desc: Lambda returns early when points.size() != xResObjArray.size()
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_SizeMismatchX, TestSize.Level1)
{
    ResetMockResourceData();
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints3();
    // xResObjArray has size 2, mismatching points.size()=3
    std::vector<RefPtr<ResourceObject>> xResObjArray = { CreateInvalidResObj(), CreateInvalidResObj() };
    std::vector<RefPtr<ResourceObject>> yResObjArray(POINTS_COUNT_THREE);
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    // Size mismatch -> lambda returns early, property not set
    EXPECT_FALSE(paintProperty->HasPoints());
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_SizeMismatchY
 * @tc.desc: Lambda returns early when points.size() != yResObjArray.size() (x matches)
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_SizeMismatchY, TestSize.Level1)
{
    ResetMockResourceData();
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints3();
    std::vector<RefPtr<ResourceObject>> xResObjArray(POINTS_COUNT_THREE);
    // yResObjArray has size 2, mismatching points.size()=3
    std::vector<RefPtr<ResourceObject>> yResObjArray = { CreateInvalidResObj(), CreateInvalidResObj() };
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_FALSE(paintProperty->HasPoints());
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_AllXNull_AllYNull
 * @tc.desc: All resObj are null -> result equals original points
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_AllXNull_AllYNull, TestSize.Level1)
{
    ResetMockResourceData();
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints3();
    // All entries null -> use original point values
    std::vector<RefPtr<ResourceObject>> xResObjArray(POINTS_COUNT_THREE);
    std::vector<RefPtr<ResourceObject>> yResObjArray(POINTS_COUNT_THREE);
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasPoints());
    auto retrieved = paintProperty->GetPointsValue();
    ASSERT_EQ(retrieved.size(), POINTS_COUNT_THREE);
    EXPECT_FLOAT_EQ(retrieved[0].first.ConvertToPx(), ORIGINAL_POINT_X1);
    EXPECT_FLOAT_EQ(retrieved[0].second.ConvertToPx(), ORIGINAL_POINT_Y1);
    EXPECT_FLOAT_EQ(retrieved[2].first.ConvertToPx(), ORIGINAL_POINT_X3);
    EXPECT_FLOAT_EQ(retrieved[2].second.ConvertToPx(), ORIGINAL_POINT_Y3);
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_XInvalidFirst_YValid
 * @tc.desc: X[0] is invalid -> ConvertFromResObjNG returns false -> result cleared and break
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_XInvalidFirst_YValid, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_P0_Y, MOCK_DIM_Y1);
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints2();
    std::vector<RefPtr<ResourceObject>> xResObjArray = { CreateInvalidResObj(), CreateValidResObj(ID_P1_X) };
    std::vector<RefPtr<ResourceObject>> yResObjArray = { CreateValidResObj(ID_P0_Y), CreateValidResObj(ID_P1_Y) };
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    // X[0] invalid -> result.clear() + break -> property set to empty
    EXPECT_TRUE(paintProperty->HasPoints());
    EXPECT_TRUE(paintProperty->GetPointsValue().empty());
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_XValid_YInvalidFirst
 * @tc.desc: X[0] valid, Y[0] invalid -> ConvertFromResObjNG(Y) returns false -> result cleared and break
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_XValid_YInvalidFirst, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_P0_X, MOCK_DIM_X1);
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints2();
    std::vector<RefPtr<ResourceObject>> xResObjArray = { CreateValidResObj(ID_P0_X), CreateValidResObj(ID_P1_X) };
    std::vector<RefPtr<ResourceObject>> yResObjArray = { CreateInvalidResObj(), CreateValidResObj(ID_P1_Y) };
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    // Y[0] invalid -> result.clear() + break -> property set to empty
    EXPECT_TRUE(paintProperty->HasPoints());
    EXPECT_TRUE(paintProperty->GetPointsValue().empty());
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_XInvalidMid_YValid
 * @tc.desc: X[0] valid, X[1] invalid -> result cleared at index 1, break
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_XInvalidMid_YValid, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_P0_X, MOCK_DIM_X1);
    AddMockResourceData(ID_P0_Y, MOCK_DIM_Y1);
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints2();
    std::vector<RefPtr<ResourceObject>> xResObjArray = { CreateValidResObj(ID_P0_X), CreateInvalidResObj() };
    std::vector<RefPtr<ResourceObject>> yResObjArray = { CreateValidResObj(ID_P0_Y), nullptr };
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    // X[1] invalid -> result.clear() (was 1 element) + break -> empty
    EXPECT_TRUE(paintProperty->HasPoints());
    EXPECT_TRUE(paintProperty->GetPointsValue().empty());
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_XValid_YInvalidMid
 * @tc.desc: Y[0] valid, Y[1] invalid -> result cleared at index 1, break
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_XValid_YInvalidMid, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_P0_X, MOCK_DIM_X1);
    AddMockResourceData(ID_P0_Y, MOCK_DIM_Y1);
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints2();
    std::vector<RefPtr<ResourceObject>> xResObjArray = { CreateValidResObj(ID_P0_X), nullptr };
    std::vector<RefPtr<ResourceObject>> yResObjArray = { CreateValidResObj(ID_P0_Y), CreateInvalidResObj() };
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    // Y[1] invalid -> result.clear() + break -> empty
    EXPECT_TRUE(paintProperty->HasPoints());
    EXPECT_TRUE(paintProperty->GetPointsValue().empty());
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_XNull_YValid
 * @tc.desc: X[i] null -> use original X; Y[i] valid -> use converted Y
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_XNull_YValid, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_P0_Y, MOCK_DIM_Y1);
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints2();
    std::vector<RefPtr<ResourceObject>> xResObjArray = { nullptr, nullptr };
    std::vector<RefPtr<ResourceObject>> yResObjArray = { CreateValidResObj(ID_P0_Y), nullptr };
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasPoints());
    auto retrieved = paintProperty->GetPointsValue();
    ASSERT_EQ(retrieved.size(), POINTS_COUNT_TWO);
    // Point 0: X keeps original, Y converted
    EXPECT_FLOAT_EQ(retrieved[0].first.ConvertToPx(), ORIGINAL_POINT_X1);
    EXPECT_FLOAT_EQ(retrieved[0].second.ConvertToPx(), MOCK_DIM_Y1.ConvertToPx());
    // Point 1: both keep original
    EXPECT_FLOAT_EQ(retrieved[1].first.ConvertToPx(), ORIGINAL_POINT_X2);
    EXPECT_FLOAT_EQ(retrieved[1].second.ConvertToPx(), ORIGINAL_POINT_Y2);
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_XValid_YNull
 * @tc.desc: X[i] valid -> use converted X; Y[i] null -> use original Y
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_XValid_YNull, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_P0_X, MOCK_DIM_X1);
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints2();
    std::vector<RefPtr<ResourceObject>> xResObjArray = { CreateValidResObj(ID_P0_X), nullptr };
    std::vector<RefPtr<ResourceObject>> yResObjArray = { nullptr, nullptr };
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasPoints());
    auto retrieved = paintProperty->GetPointsValue();
    ASSERT_EQ(retrieved.size(), POINTS_COUNT_TWO);
    // Point 0: X converted, Y keeps original
    EXPECT_FLOAT_EQ(retrieved[0].first.ConvertToPx(), MOCK_DIM_X1.ConvertToPx());
    EXPECT_FLOAT_EQ(retrieved[0].second.ConvertToPx(), ORIGINAL_POINT_Y1);
    // Point 1: both keep original
    EXPECT_FLOAT_EQ(retrieved[1].first.ConvertToPx(), ORIGINAL_POINT_X2);
    EXPECT_FLOAT_EQ(retrieved[1].second.ConvertToPx(), ORIGINAL_POINT_Y2);
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_AllValid
 * @tc.desc: All X and Y resObj valid -> all points converted from mock data
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_AllValid, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_P0_X, MOCK_DIM_X1);
    AddMockResourceData(ID_P0_Y, MOCK_DIM_Y1);
    AddMockResourceData(ID_P1_X, MOCK_DIM_X2);
    AddMockResourceData(ID_P1_Y, MOCK_DIM_Y2);
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints2();
    std::vector<RefPtr<ResourceObject>> xResObjArray = { CreateValidResObj(ID_P0_X), CreateValidResObj(ID_P1_X) };
    std::vector<RefPtr<ResourceObject>> yResObjArray = { CreateValidResObj(ID_P0_Y), CreateValidResObj(ID_P1_Y) };
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasPoints());
    auto retrieved = paintProperty->GetPointsValue();
    ASSERT_EQ(retrieved.size(), POINTS_COUNT_TWO);
    EXPECT_FLOAT_EQ(retrieved[0].first.ConvertToPx(), MOCK_DIM_X1.ConvertToPx());
    EXPECT_FLOAT_EQ(retrieved[0].second.ConvertToPx(), MOCK_DIM_Y1.ConvertToPx());
    EXPECT_FLOAT_EQ(retrieved[1].first.ConvertToPx(), MOCK_DIM_X2.ConvertToPx());
    EXPECT_FLOAT_EQ(retrieved[1].second.ConvertToPx(), MOCK_DIM_Y2.ConvertToPx());
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_RerenderableFalse
 * @tc.desc: SetPoints resObj updates property when frameNode is not rerenderable
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_RerenderableFalse, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_P0_X, MOCK_DIM_X1);
    AddMockResourceData(ID_P0_Y, MOCK_DIM_Y1);
    AddMockResourceData(ID_P1_X, MOCK_DIM_X2);
    AddMockResourceData(ID_P1_Y, MOCK_DIM_Y2);
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->SetRerenderable(false);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints2();
    std::vector<RefPtr<ResourceObject>> xResObjArray = { CreateValidResObj(ID_P0_X), CreateValidResObj(ID_P1_X) };
    std::vector<RefPtr<ResourceObject>> yResObjArray = { CreateValidResObj(ID_P0_Y), CreateValidResObj(ID_P1_Y) };
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    // Property still updated even when not rerenderable (MarkDirtyNode is skipped)
    EXPECT_TRUE(paintProperty->HasPoints());
    auto retrieved = paintProperty->GetPointsValue();
    ASSERT_EQ(retrieved.size(), POINTS_COUNT_TWO);
    EXPECT_FLOAT_EQ(retrieved[0].first.ConvertToPx(), MOCK_DIM_X1.ConvertToPx());
    EXPECT_FLOAT_EQ(retrieved[0].second.ConvertToPx(), MOCK_DIM_Y1.ConvertToPx());
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_WeakExpired
 * @tc.desc: Lambda returns early when frameNode weak reference has expired
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_WeakExpired, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_P0_X, MOCK_DIM_X1);
    AddMockResourceData(ID_P0_Y, MOCK_DIM_Y1);
    AddMockResourceData(ID_P1_X, MOCK_DIM_X2);
    AddMockResourceData(ID_P1_Y, MOCK_DIM_Y2);

    RefPtr<PatternResourceManager> savedResourceMgr;
    size_t initialResMapSize = 0;
    {
        auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
        RefPtr<FrameNode> scopedNode = FrameNode::GetOrCreateFrameNode(
            V2::POLYGON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<PolygonPattern>(true); });
        ASSERT_NE(scopedNode, nullptr);

        auto pattern = scopedNode->GetPattern<PolygonPattern>();
        ASSERT_NE(pattern, nullptr);

        g_isConfigChangePerform = true;
        ShapePoints points = MakeOriginalPoints2();
        std::vector<RefPtr<ResourceObject>> xResObjArray = { CreateValidResObj(ID_P0_X), CreateValidResObj(ID_P1_X) };
        std::vector<RefPtr<ResourceObject>> yResObjArray = { CreateValidResObj(ID_P0_Y), CreateValidResObj(ID_P1_Y) };
        PolygonModelNG::SetPoints(AceType::RawPtr(scopedNode), points, xResObjArray, yResObjArray);

        savedResourceMgr = pattern->resourceMgr_;
        ASSERT_NE(savedResourceMgr, nullptr);
        initialResMapSize = savedResourceMgr->resMap_.size();
        EXPECT_GT(initialResMapSize, static_cast<size_t>(0));

        g_isConfigChangePerform = false;
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
    }

    // ReloadResources completes without crash when weak reference has expired
    savedResourceMgr->ReloadResources();
    EXPECT_EQ(savedResourceMgr->resMap_.size(), initialResMapSize);
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_Static_ConfigChangePerformTrue
 * @tc.desc: Static SetPoints with valid ConfigChangePerform registers callback and ReloadResources invokes it
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_Static_ConfigChangePerformTrue, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_P0_X, MOCK_DIM_X1);
    AddMockResourceData(ID_P0_Y, MOCK_DIM_Y1);
    AddMockResourceData(ID_P1_X, MOCK_DIM_X2);
    AddMockResourceData(ID_P1_Y, MOCK_DIM_Y2);

    auto pattern = frameNode_->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    if (pattern->resourceMgr_ == nullptr) {
        pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    }
    auto initialSize = pattern->resourceMgr_->resMap_.size();

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints2();
    std::vector<RefPtr<ResourceObject>> xResObjArray = { CreateValidResObj(ID_P0_X), CreateValidResObj(ID_P1_X) };
    std::vector<RefPtr<ResourceObject>> yResObjArray = { CreateValidResObj(ID_P0_Y), CreateValidResObj(ID_P1_Y) };
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode_), points, xResObjArray, yResObjArray);

    EXPECT_GT(pattern->resourceMgr_->resMap_.size(), initialSize);

    pattern->resourceMgr_->ReloadResources();
    auto paintProperty = frameNode_->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasPoints());
    auto retrieved = paintProperty->GetPointsValue();
    ASSERT_EQ(retrieved.size(), POINTS_COUNT_TWO);
    EXPECT_FLOAT_EQ(retrieved[0].first.ConvertToPx(), MOCK_DIM_X1.ConvertToPx());
    EXPECT_FLOAT_EQ(retrieved[0].second.ConvertToPx(), MOCK_DIM_Y1.ConvertToPx());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_EmptyPoints
 * @tc.desc: Empty points with matching empty resObj arrays -> property set to empty
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_EmptyPoints, TestSize.Level1)
{
    ResetMockResourceData();
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points;
    std::vector<RefPtr<ResourceObject>> xResObjArray;
    std::vector<RefPtr<ResourceObject>> yResObjArray;
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    // Empty points -> loop body never executes -> result is empty -> property set to empty
    EXPECT_TRUE(paintProperty->HasPoints());
    EXPECT_TRUE(paintProperty->GetPointsValue().empty());
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModelNG_SetPointsResObj_MixedNullAndValid
 * @tc.desc: Mixed null and valid resObj across points -> partial conversion
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTddTest, PolygonModelNG_SetPointsResObj_MixedNullAndValid, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_P0_X, MOCK_DIM_X1);
    AddMockResourceData(ID_P1_Y, MOCK_DIM_Y2);
    auto frameNode = CreatePolygonFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoints points = MakeOriginalPoints2();
    // P0: X valid (converted), Y null (original)
    // P1: X null (original), Y valid (converted)
    std::vector<RefPtr<ResourceObject>> xResObjArray = { CreateValidResObj(ID_P0_X), nullptr };
    std::vector<RefPtr<ResourceObject>> yResObjArray = { nullptr, CreateValidResObj(ID_P1_Y) };
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasPoints());
    auto retrieved = paintProperty->GetPointsValue();
    ASSERT_EQ(retrieved.size(), POINTS_COUNT_TWO);
    EXPECT_FLOAT_EQ(retrieved[0].first.ConvertToPx(), MOCK_DIM_X1.ConvertToPx());
    EXPECT_FLOAT_EQ(retrieved[0].second.ConvertToPx(), ORIGINAL_POINT_Y1);
    EXPECT_FLOAT_EQ(retrieved[1].first.ConvertToPx(), ORIGINAL_POINT_X2);
    EXPECT_FLOAT_EQ(retrieved[1].second.ConvertToPx(), MOCK_DIM_Y2.ConvertToPx());
    g_isConfigChangePerform = false;
    ViewStackProcessor::GetInstance()->Pop();
}

} // namespace OHOS::Ace::NG
