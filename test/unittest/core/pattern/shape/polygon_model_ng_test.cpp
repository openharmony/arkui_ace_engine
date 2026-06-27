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

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "base/utils/system_properties.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/polygon_model_ng.h"
#include "core/components_ng/pattern/shape/polygon_paint_property.h"
#include "core/components_ng/pattern/shape/polygon_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/common/resource/resource_object.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double POINT_X_FIRST = 10.0;
constexpr double POINT_Y_FIRST = 20.0;
constexpr double POINT_X_SECOND = 30.0;
constexpr double POINT_Y_SECOND = 40.0;
constexpr double POINT_X_THIRD = 50.0;
constexpr double POINT_Y_THIRD = 60.0;
constexpr size_t TEST_POINTS_COUNT = 3;
constexpr size_t UPDATED_POINTS_COUNT = 2;
constexpr float EXPECTED_POINT_X_FIRST = 10.0f;
constexpr float EXPECTED_POINT_Y_FIRST = 20.0f;
} // namespace

class PolygonModelNGTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }

    RefPtr<FrameNode> CreatePolygonNode()
    {
        PolygonModelNG().Create(true);
        return AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }

    RefPtr<FrameNode> CreatePolylineNode()
    {
        PolygonModelNG().Create(false);
        return AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }

    static ShapePoints MakeTestPoints()
    {
        return ShapePoints {
            { Dimension(POINT_X_FIRST), Dimension(POINT_Y_FIRST) },
            { Dimension(POINT_X_SECOND), Dimension(POINT_Y_SECOND) },
            { Dimension(POINT_X_THIRD), Dimension(POINT_Y_THIRD) },
        };
    }
};


/**
 * @tc.name: PolygonModel_CreatePolygonTrue
 * @tc.desc: When Create(true) is called, the created node should have the "Polygon" tag
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTest, PolygonModel_CreatePolygonTrue, TestSize.Level1)
{
    auto frameNode = CreatePolygonNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::POLYGON_ETS_TAG);

    auto pattern = frameNode->GetPattern<PolygonPattern>();
    EXPECT_NE(pattern, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);

    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModel_CreatePolygonFalse
 * @tc.desc: When Create(false) is called, the created node should have the "Polyline" tag
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTest, PolygonModel_CreatePolygonFalse, TestSize.Level1)
{
    auto frameNode = CreatePolylineNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::POLYLINE_ETS_TAG);

    auto pattern = frameNode->GetPattern<PolygonPattern>();
    EXPECT_NE(pattern, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);

    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModel_CreatePolygonTagDiffersFromPolyline
 * @tc.desc: Verify Polygon and Polyline node tags are different
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTest, PolygonModel_CreatePolygonTagDiffersFromPolyline, TestSize.Level1)
{
    EXPECT_STRNE(V2::POLYGON_ETS_TAG, V2::POLYLINE_ETS_TAG);
}


/**
 * @tc.name: PolygonModel_SetPointsValidPoints
 * @tc.desc: SetPoints updates PolygonPaintProperty with the exact points passed in
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTest, PolygonModel_SetPointsValidPoints, TestSize.Level1)
{
    auto frameNode = CreatePolygonNode();
    ASSERT_NE(frameNode, nullptr);

    ShapePoints points = MakeTestPoints();
    PolygonModelNG().SetPoints(points);

    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasPoints());

    auto retrievedPoints = paintProperty->GetPointsValue();
    ASSERT_EQ(retrievedPoints.size(), TEST_POINTS_COUNT);
    EXPECT_FLOAT_EQ(retrievedPoints[0].first.ConvertToPx(), EXPECTED_POINT_X_FIRST);
    EXPECT_FLOAT_EQ(retrievedPoints[0].second.ConvertToPx(), EXPECTED_POINT_Y_FIRST);

    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModel_SetPointsEmptyPoints
 * @tc.desc: SetPoints with empty vector should result in empty points, not null
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTest, PolygonModel_SetPointsEmptyPoints, TestSize.Level1)
{
    auto frameNode = CreatePolygonNode();
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
 * @tc.name: PolygonModel_SetPointsOverwrite
 * @tc.desc: Calling SetPoints multiple times should overwrite the previous value
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTest, PolygonModel_SetPointsOverwrite, TestSize.Level1)
{
    auto frameNode = CreatePolygonNode();
    ASSERT_NE(frameNode, nullptr);

    ShapePoints initialPoints = { { Dimension(POINT_X_FIRST), Dimension(POINT_Y_FIRST) } };
    PolygonModelNG().SetPoints(initialPoints);

    ShapePoints updatedPoints = {
        { Dimension(POINT_X_SECOND), Dimension(POINT_Y_SECOND) },
        { Dimension(POINT_X_THIRD), Dimension(POINT_Y_THIRD) },
    };
    PolygonModelNG().SetPoints(updatedPoints);

    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto retrievedPoints = paintProperty->GetPointsValue();
    EXPECT_EQ(retrievedPoints.size(), UPDATED_POINTS_COUNT);

    ViewStackProcessor::GetInstance()->Pop();
}


/**
 * @tc.name: PolygonModel_SetPointsNodeWithValidFrameNode
 * @tc.desc: Static SetPoints(frameNode, points) sets points on the given frameNode
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTest, PolygonModel_SetPointsNodeWithValidFrameNode, TestSize.Level1)
{
    auto frameNode = CreatePolygonNode();
    ASSERT_NE(frameNode, nullptr);

    ShapePoints points = MakeTestPoints();
    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points);

    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasPoints());

    auto retrievedPoints = paintProperty->GetPointsValue();
    ASSERT_EQ(retrievedPoints.size(), TEST_POINTS_COUNT);
    EXPECT_FLOAT_EQ(retrievedPoints[0].first.ConvertToPx(), EXPECTED_POINT_X_FIRST);
    EXPECT_FLOAT_EQ(retrievedPoints[0].second.ConvertToPx(), EXPECTED_POINT_Y_FIRST);

    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModel_SetPointsNodeWithNullFrameNode
 * @tc.desc: Static SetPoints(nullptr, points) should return early without crash
 *       (ACE_UPDATE_NODE_PAINT_PROPERTY macro's CHECK_NULL_VOID branch)
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTest, PolygonModel_SetPointsNodeWithNullFrameNode, TestSize.Level1)
{
    ShapePoints points = MakeTestPoints();
    PolygonModelNG::SetPoints(nullptr, points);
}


/**
 * @tc.name: PolygonModel_SetPointsResObjWithoutConfigChangePerform
 * @tc.desc: When ConfigChangePerform returns false (default in unit test env),
 *       the resource-objects SetPoints overload returns early
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTest, PolygonModel_SetPointsResObjWithoutConfigChangePerform, TestSize.Level1)
{
    // In unit test env, ConfigChangePerform() defaults to false (IsConfigChangePerform reads
    // system parameter "persist.sys.arkui.configchangeperform" which defaults to false)
    EXPECT_FALSE(SystemProperties::ConfigChangePerform());

    auto frameNode = CreatePolygonNode();
    ASSERT_NE(frameNode, nullptr);

    ShapePoints points = MakeTestPoints();
    std::vector<RefPtr<ResourceObject>> xResObjArray(TEST_POINTS_COUNT);
    std::vector<RefPtr<ResourceObject>> yResObjArray(TEST_POINTS_COUNT);

    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);

    // Method returned early - paint property should NOT have points set
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_FALSE(paintProperty->HasPoints());

    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModel_SetPointsResObjWithConfigChangePerformNullFrameNode
 * @tc.desc: When ConfigChangePerform is true but frameNode is nullptr,
 *       the method returns early without crash
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTest, PolygonModel_SetPointsResObjWithConfigChangePerformNullFrameNode, TestSize.Level1)
{
    SystemProperties::SetConfigChangePerform();
    ASSERT_TRUE(SystemProperties::ConfigChangePerform());

    ShapePoints points = MakeTestPoints();
    std::vector<RefPtr<ResourceObject>> xResObjArray(TEST_POINTS_COUNT);
    std::vector<RefPtr<ResourceObject>> yResObjArray(TEST_POINTS_COUNT);

    PolygonModelNG::SetPoints(nullptr, points, xResObjArray, yResObjArray);
    // No crash, method returned early
}

/**
 * @tc.name: PolygonModel_SetPointsResObjWithConfigChangePerformValidPattern
 * @tc.desc: When ConfigChangePerform is true and frameNode has a valid PolygonPattern,
 *       AddResObj is called to register the resource callback. Due to the mock
 *       implementation of Pattern::AddResObj, the points are not actually updated.
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTest, PolygonModel_SetPointsResObjWithConfigChangePerformValidPattern, TestSize.Level1)
{
    SystemProperties::SetConfigChangePerform();
    ASSERT_TRUE(SystemProperties::ConfigChangePerform());

    auto frameNode = CreatePolygonNode();
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<PolygonPattern>();
    ASSERT_NE(pattern, nullptr);

    ShapePoints points = MakeTestPoints();
    std::vector<RefPtr<ResourceObject>> xResObjArray(TEST_POINTS_COUNT);
    std::vector<RefPtr<ResourceObject>> yResObjArray(TEST_POINTS_COUNT);
    for (size_t i = 0; i < TEST_POINTS_COUNT; i++) {
        xResObjArray[i] = AceType::MakeRefPtr<ResourceObject>();
        yResObjArray[i] = AceType::MakeRefPtr<ResourceObject>();
    }

    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);

    // Mock AddResObj discards the callback, so points remain unset
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_FALSE(paintProperty->HasPoints());

    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: PolygonModel_SetPointsResObjWithEmptyResourceArrays
 * @tc.desc: With empty resource arrays and ConfigChangePerform=true,
 *       AddResObj is called (no-op via mock), method completes without error
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModelNGTest, PolygonModel_SetPointsResObjWithEmptyResourceArrays, TestSize.Level1)
{
    SystemProperties::SetConfigChangePerform();
    ASSERT_TRUE(SystemProperties::ConfigChangePerform());

    auto frameNode = CreatePolygonNode();
    ASSERT_NE(frameNode, nullptr);

    ShapePoints points;
    std::vector<RefPtr<ResourceObject>> xResObjArray;
    std::vector<RefPtr<ResourceObject>> yResObjArray;

    PolygonModelNG::SetPoints(AceType::RawPtr(frameNode), points, xResObjArray, yResObjArray);

    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_FALSE(paintProperty->HasPoints());

    ViewStackProcessor::GetInstance()->Pop();
}

} // namespace OHOS::Ace::NG
