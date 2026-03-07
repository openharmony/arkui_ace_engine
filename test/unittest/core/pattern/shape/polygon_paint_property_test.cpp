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
#include "base/geometry/shape.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/shape/polygon_paint_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double FIRST_POINT_X = 10.0;
constexpr double FIRST_POINT_Y = 20.0;
constexpr double SECOND_POINT_X = 30.0;
constexpr double SECOND_POINT_Y = 40.0;
constexpr double THIRD_POINT_X = 50.0;
constexpr double THIRD_POINT_Y = 60.0;
constexpr double ZERO = 0.0;
constexpr double NEGATIVE_X1 = -10.0;
constexpr double NEGATIVE_Y1 = -20.0;
constexpr double NEGATIVE_X2 = -30.0;
constexpr double NEGATIVE_Y2 = -40.0;
constexpr double LARGE_X1 = 1000.0;
constexpr double LARGE_Y1 = 2000.0;
constexpr double LARGE_X2 = 3000.0;
constexpr double LARGE_Y2 = 4000.0;
} // namespace

class PolygonPaintPropertyToJsonValueTest : public testing::Test {
public:
    void SetUp() override
    {
        paintProperty_ = AceType::MakeRefPtr<PolygonPaintProperty>();
    }

    void TearDown() override
    {
        paintProperty_ = nullptr;
    }

    RefPtr<PolygonPaintProperty> paintProperty_;
};

/**
 * @tc.name: PolygonPaintPropertyToJsonValueWithFastFilter
 * @tc.desc: Test ToJsonValue when filter is fast filter
 * @tc.type: FUNC
 */
HWTEST_F(PolygonPaintPropertyToJsonValueTest, PolygonPaintPropertyToJsonValueWithFastFilter, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.AddFilterAttr("points");

    paintProperty_->ToJsonValue(json, filter);

    auto jsonString = json->ToString();
    EXPECT_TRUE(jsonString.find("points") == std::string::npos);
}

/**
 * @tc.name: PolygonPaintPropertyToJsonValueWithoutPoints
 * @tc.desc: Test ToJsonValue when no points are set
 * @tc.type: FUNC
 */
HWTEST_F(PolygonPaintPropertyToJsonValueTest, PolygonPaintPropertyToJsonValueWithoutPoints, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    paintProperty_->ToJsonValue(json, filter);

    auto jsonString = json->ToString();
    EXPECT_TRUE(jsonString.find("points") == std::string::npos);
}

/**
 * @tc.name: PolygonPaintPropertyToJsonValueWithSinglePoint
 * @tc.desc: Test ToJsonValue with single point
 * @tc.type: FUNC
 */
HWTEST_F(PolygonPaintPropertyToJsonValueTest, PolygonPaintPropertyToJsonValueWithSinglePoint, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set single point
     */
    ShapePoints points;
    points.emplace_back(Dimension(FIRST_POINT_X), Dimension(FIRST_POINT_Y));
    paintProperty_->UpdatePoints(points);

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify points array and coordinate values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto pointsArray = json->GetValue("points");
    EXPECT_NE(pointsArray, nullptr);
    EXPECT_EQ(pointsArray->GetArraySize(), 1);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(0)->GetArrayItem(0)->GetDouble(), FIRST_POINT_X);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(0)->GetArrayItem(1)->GetDouble(), FIRST_POINT_Y);
}

/**
 * @tc.name: PolygonPaintPropertyToJsonValueWithTwoPoints
 * @tc.desc: Test ToJsonValue with two points
 * @tc.type: FUNC
 */
HWTEST_F(PolygonPaintPropertyToJsonValueTest, PolygonPaintPropertyToJsonValueWithTwoPoints, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set two points
     */
    ShapePoints points;
    points.emplace_back(Dimension(FIRST_POINT_X), Dimension(FIRST_POINT_Y));
    points.emplace_back(Dimension(SECOND_POINT_X), Dimension(SECOND_POINT_Y));
    paintProperty_->UpdatePoints(points);

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify points array and coordinate values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto pointsArray = json->GetValue("points");
    EXPECT_NE(pointsArray, nullptr);
    EXPECT_EQ(pointsArray->GetArraySize(), 2);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(0)->GetArrayItem(0)->GetDouble(), FIRST_POINT_X);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(0)->GetArrayItem(1)->GetDouble(), FIRST_POINT_Y);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(1)->GetArrayItem(0)->GetDouble(), SECOND_POINT_X);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(1)->GetArrayItem(1)->GetDouble(), SECOND_POINT_Y);
}

/**
 * @tc.name: PolygonPaintPropertyToJsonValueWithThreePoints
 * @tc.desc: Test ToJsonValue with three points
 * @tc.type: FUNC
 */
HWTEST_F(PolygonPaintPropertyToJsonValueTest, PolygonPaintPropertyToJsonValueWithThreePoints, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set three points
     */
    ShapePoints points;
    points.emplace_back(Dimension(FIRST_POINT_X), Dimension(FIRST_POINT_Y));
    points.emplace_back(Dimension(SECOND_POINT_X), Dimension(SECOND_POINT_Y));
    points.emplace_back(Dimension(THIRD_POINT_X), Dimension(THIRD_POINT_Y));
    paintProperty_->UpdatePoints(points);

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify points array and coordinate values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto pointsArray = json->GetValue("points");
    EXPECT_NE(pointsArray, nullptr);
    EXPECT_EQ(pointsArray->GetArraySize(), 3);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(0)->GetArrayItem(0)->GetDouble(), FIRST_POINT_X);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(0)->GetArrayItem(1)->GetDouble(), FIRST_POINT_Y);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(1)->GetArrayItem(0)->GetDouble(), SECOND_POINT_X);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(1)->GetArrayItem(1)->GetDouble(), SECOND_POINT_Y);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(2)->GetArrayItem(0)->GetDouble(), THIRD_POINT_X);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(2)->GetArrayItem(1)->GetDouble(), THIRD_POINT_Y);
}

/**
 * @tc.name: PolygonPaintPropertyToJsonValueWithZeroCoordinates
 * @tc.desc: Test ToJsonValue with zero coordinates
 * @tc.type: FUNC
 */
HWTEST_F(PolygonPaintPropertyToJsonValueTest, PolygonPaintPropertyToJsonValueWithZeroCoordinates, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set points with zero coordinates
     */
    ShapePoints points;
    points.emplace_back(Dimension(ZERO), Dimension(ZERO));
    points.emplace_back(Dimension(ZERO), Dimension(ZERO));
    paintProperty_->UpdatePoints(points);

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify points array and all coordinates are zero
     */
    paintProperty_->ToJsonValue(json, filter);

    auto pointsArray = json->GetValue("points");
    EXPECT_NE(pointsArray, nullptr);
    EXPECT_EQ(pointsArray->GetArraySize(), 2);
    for (int i = 0; i < 2; ++i) {
        EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(i)->GetArrayItem(0)->GetDouble(), ZERO);
        EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(i)->GetArrayItem(1)->GetDouble(), ZERO);
    }
}

/**
 * @tc.name: PolygonPaintPropertyToJsonValueWithNegativeCoordinates
 * @tc.desc: Test ToJsonValue with negative coordinates
 * @tc.type: FUNC
 */
HWTEST_F(PolygonPaintPropertyToJsonValueTest, PolygonPaintPropertyToJsonValueWithNegativeCoordinates, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set points with negative coordinates
     */
    ShapePoints points;
    points.emplace_back(Dimension(NEGATIVE_X1), Dimension(NEGATIVE_Y1));
    points.emplace_back(Dimension(NEGATIVE_X2), Dimension(NEGATIVE_Y2));
    paintProperty_->UpdatePoints(points);

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify points array and negative coordinate values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto pointsArray = json->GetValue("points");
    EXPECT_NE(pointsArray, nullptr);
    EXPECT_EQ(pointsArray->GetArraySize(), 2);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(0)->GetArrayItem(0)->GetDouble(), NEGATIVE_X1);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(0)->GetArrayItem(1)->GetDouble(), NEGATIVE_Y1);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(1)->GetArrayItem(0)->GetDouble(), NEGATIVE_X2);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(1)->GetArrayItem(1)->GetDouble(), NEGATIVE_Y2);
}

/**
 * @tc.name: PolygonPaintPropertyToJsonValueWithLargeCoordinates
 * @tc.desc: Test ToJsonValue with large coordinates
 * @tc.type: FUNC
 */
HWTEST_F(PolygonPaintPropertyToJsonValueTest, PolygonPaintPropertyToJsonValueWithLargeCoordinates, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set points with large coordinates
     */
    ShapePoints points;
    points.emplace_back(Dimension(LARGE_X1), Dimension(LARGE_Y1));
    points.emplace_back(Dimension(LARGE_X2), Dimension(LARGE_Y2));
    paintProperty_->UpdatePoints(points);

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify points array and large coordinate values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto pointsArray = json->GetValue("points");
    EXPECT_NE(pointsArray, nullptr);
    EXPECT_EQ(pointsArray->GetArraySize(), 2);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(0)->GetArrayItem(0)->GetDouble(), LARGE_X1);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(0)->GetArrayItem(1)->GetDouble(), LARGE_Y1);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(1)->GetArrayItem(0)->GetDouble(), LARGE_X2);
    EXPECT_DOUBLE_EQ(pointsArray->GetArrayItem(1)->GetArrayItem(1)->GetDouble(), LARGE_Y2);
}
} // namespace OHOS::Ace::NG
