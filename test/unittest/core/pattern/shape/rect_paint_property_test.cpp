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
#include "base/geometry/ng/radius.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double DEFAULT_RADIUS_WIDTH = 10.0;
constexpr double DEFAULT_RADIUS_HEIGHT = 5.0;
constexpr double DIFFERENT_RADIUS_WIDTH = 15.0;
constexpr double DIFFERENT_RADIUS_HEIGHT = 8.0;
constexpr double ZERO = 0.0;
} // namespace

class RectPaintPropertyToJsonValueTest : public testing::Test {
public:
    void SetUp() override
    {
        paintProperty_ = AceType::MakeRefPtr<RectPaintProperty>();
    }

    void TearDown() override
    {
        paintProperty_ = nullptr;
    }

    RefPtr<RectPaintProperty> paintProperty_;
};

/**
 * @tc.name: RectPaintPropertyToJsonValueWithFastFilter
 * @tc.desc: Test ToJsonValue when filter is fast filter
 * @tc.type: FUNC
 */
HWTEST_F(RectPaintPropertyToJsonValueTest, RectPaintPropertyToJsonValueWithFastFilter, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set a fixed attribute filter (e.g., "id")
     * @tc.expected: step1. IsFastFilter returns true since "id" is a fixed attr
     */
    filter.AddFilterAttr("id");

    /**
     * @tc.steps: step2. Call ToJsonValue with fast filter
     * @tc.expected: step2. Radius is not serialized since fast filter skips extended attrs
     */
    paintProperty_->ToJsonValue(json, filter);

    auto jsonString = json->ToString();
    EXPECT_TRUE(jsonString.find("radius") == std::string::npos);
}

/**
 * @tc.name: RectPaintPropertyToJsonValueWithoutTopLeftRadius
 * @tc.desc: Test ToJsonValue when top left radius is missing
 * @tc.type: FUNC
 */
HWTEST_F(RectPaintPropertyToJsonValueTest, RectPaintPropertyToJsonValueWithoutTopLeftRadius, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set topRight, bottomRight, bottomLeft radius
     */
    paintProperty_->UpdateTopRightRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomRightRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify radius array and dimension values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto radiusArray = json->GetValue("radius");
    EXPECT_NE(radiusArray, nullptr);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(0)->GetArrayItem(0)->GetDouble(), ZERO);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(0)->GetArrayItem(1)->GetDouble(), ZERO);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(1)->GetArrayItem(0)->GetDouble(), DEFAULT_RADIUS_WIDTH);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(1)->GetArrayItem(1)->GetDouble(), DEFAULT_RADIUS_HEIGHT);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusWidth"), ZERO);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusHeight"), ZERO);
}

/**
 * @tc.name: RectPaintPropertyToJsonValueWithoutTopRightRadius
 * @tc.desc: Test ToJsonValue when top right radius is missing
 * @tc.type: FUNC
 */
HWTEST_F(RectPaintPropertyToJsonValueTest, RectPaintPropertyToJsonValueWithoutTopRightRadius, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set topLeft, bottomRight, bottomLeft radius
     */
    paintProperty_->UpdateTopLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomRightRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify radius array and dimension values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto radiusArray = json->GetValue("radius");
    EXPECT_NE(radiusArray, nullptr);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(0)->GetArrayItem(0)->GetDouble(), DEFAULT_RADIUS_WIDTH);
    // topRight not set, uses default [0,0]
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(1)->GetArrayItem(0)->GetDouble(), ZERO);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusWidth"), ZERO);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusHeight"), ZERO);
}

/**
 * @tc.name: RectPaintPropertyToJsonValueWithoutBottomRightRadius
 * @tc.desc: Test ToJsonValue when bottom right radius is missing
 * @tc.type: FUNC
 */
HWTEST_F(RectPaintPropertyToJsonValueTest, RectPaintPropertyToJsonValueWithoutBottomRightRadius, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set topLeft, topRight, bottomLeft radius
     */
    paintProperty_->UpdateTopLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateTopRightRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify radius array and dimension values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto radiusArray = json->GetValue("radius");
    EXPECT_NE(radiusArray, nullptr);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(2)->GetArrayItem(0)->GetDouble(), ZERO);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusWidth"), ZERO);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusHeight"), ZERO);
}

/**
 * @tc.name: RectPaintPropertyToJsonValueWithoutBottomLeftRadius
 * @tc.desc: Test ToJsonValue when bottom left radius is missing
 * @tc.type: FUNC
 */
HWTEST_F(RectPaintPropertyToJsonValueTest, RectPaintPropertyToJsonValueWithoutBottomLeftRadius, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set topLeft, topRight, bottomRight radius
     */
    paintProperty_->UpdateTopLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateTopRightRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomRightRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify radius array and dimension values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto radiusArray = json->GetValue("radius");
    EXPECT_NE(radiusArray, nullptr);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(3)->GetArrayItem(0)->GetDouble(), ZERO);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusWidth"), ZERO);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusHeight"), ZERO);
}

/**
 * @tc.name: RectPaintPropertyToJsonValueWithAllRadiiSameWidthAndHeight
 * @tc.desc: Test ToJsonValue when all radii have same width and height
 * @tc.type: FUNC
 */
HWTEST_F(RectPaintPropertyToJsonValueTest, RectPaintPropertyToJsonValueWithAllRadiiSameWidthAndHeight, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set all four corners with same radius
     */
    paintProperty_->UpdateTopLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateTopRightRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomRightRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify radius array values and dimension values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto radiusArray = json->GetValue("radius");
    EXPECT_NE(radiusArray, nullptr);
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(i)->GetArrayItem(0)->GetDouble(), DEFAULT_RADIUS_WIDTH);
        EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(i)->GetArrayItem(1)->GetDouble(), DEFAULT_RADIUS_HEIGHT);
    }
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusWidth"), DEFAULT_RADIUS_WIDTH);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusHeight"), DEFAULT_RADIUS_HEIGHT);
}

/**
 * @tc.name: RectPaintPropertyToJsonValueWithDifferentWidths
 * @tc.desc: Test ToJsonValue when radii have different widths
 * @tc.type: FUNC
 */
HWTEST_F(RectPaintPropertyToJsonValueTest, RectPaintPropertyToJsonValueWithDifferentWidths, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set radius with different widths
     */
    paintProperty_->UpdateTopLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateTopRightRadius(Radius(Dimension(DIFFERENT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomRightRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify radius array values and dimension values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto radiusArray = json->GetValue("radius");
    EXPECT_NE(radiusArray, nullptr);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(0)->GetArrayItem(0)->GetDouble(), DEFAULT_RADIUS_WIDTH);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(1)->GetArrayItem(0)->GetDouble(), DIFFERENT_RADIUS_WIDTH);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(2)->GetArrayItem(0)->GetDouble(), DEFAULT_RADIUS_WIDTH);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(3)->GetArrayItem(0)->GetDouble(), DEFAULT_RADIUS_WIDTH);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusWidth"), ZERO);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusHeight"), DEFAULT_RADIUS_HEIGHT);
}

/**
 * @tc.name: RectPaintPropertyToJsonValueWithDifferentHeights
 * @tc.desc: Test ToJsonValue when radii have different heights
 * @tc.type: FUNC
 */
HWTEST_F(RectPaintPropertyToJsonValueTest, RectPaintPropertyToJsonValueWithDifferentHeights, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set radius with different heights
     */
    paintProperty_->UpdateTopLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateTopRightRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomRightRadius(
        Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DIFFERENT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify radius array values and dimension values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto radiusArray = json->GetValue("radius");
    EXPECT_NE(radiusArray, nullptr);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(0)->GetArrayItem(1)->GetDouble(), DEFAULT_RADIUS_HEIGHT);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(1)->GetArrayItem(1)->GetDouble(), DEFAULT_RADIUS_HEIGHT);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(2)->GetArrayItem(1)->GetDouble(), DIFFERENT_RADIUS_HEIGHT);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(3)->GetArrayItem(1)->GetDouble(), DEFAULT_RADIUS_HEIGHT);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusWidth"), DEFAULT_RADIUS_WIDTH);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusHeight"), ZERO);
}

/**
 * @tc.name: RectPaintPropertyToJsonValueWithAllDifferentRadii
 * @tc.desc: Test ToJsonValue when all radii are different
 * @tc.type: FUNC
 */
HWTEST_F(RectPaintPropertyToJsonValueTest, RectPaintPropertyToJsonValueWithAllDifferentRadii, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set all corners with different radius values
     */
    paintProperty_->UpdateTopLeftRadius(Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateTopRightRadius(Radius(Dimension(DIFFERENT_RADIUS_WIDTH), Dimension(DEFAULT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomRightRadius(
        Radius(Dimension(DEFAULT_RADIUS_WIDTH), Dimension(DIFFERENT_RADIUS_HEIGHT)));
    paintProperty_->UpdateBottomLeftRadius(
        Radius(Dimension(DIFFERENT_RADIUS_WIDTH), Dimension(DIFFERENT_RADIUS_HEIGHT)));

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify all radius array values
     */
    paintProperty_->ToJsonValue(json, filter);

    auto radiusArray = json->GetValue("radius");
    EXPECT_NE(radiusArray, nullptr);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(0)->GetArrayItem(0)->GetDouble(), DEFAULT_RADIUS_WIDTH);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(0)->GetArrayItem(1)->GetDouble(), DEFAULT_RADIUS_HEIGHT);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(1)->GetArrayItem(0)->GetDouble(), DIFFERENT_RADIUS_WIDTH);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(1)->GetArrayItem(1)->GetDouble(), DEFAULT_RADIUS_HEIGHT);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(2)->GetArrayItem(0)->GetDouble(), DEFAULT_RADIUS_WIDTH);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(2)->GetArrayItem(1)->GetDouble(), DIFFERENT_RADIUS_HEIGHT);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(3)->GetArrayItem(0)->GetDouble(), DIFFERENT_RADIUS_WIDTH);
    EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(3)->GetArrayItem(1)->GetDouble(), DIFFERENT_RADIUS_HEIGHT);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusWidth"), ZERO);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusHeight"), ZERO);
}

/**
 * @tc.name: RectPaintPropertyToJsonValueWithZeroRadius
 * @tc.desc: Test ToJsonValue with zero radius values
 * @tc.type: FUNC
 */
HWTEST_F(RectPaintPropertyToJsonValueTest, RectPaintPropertyToJsonValueWithZeroRadius, TestSize.Level1)
{
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step1. Set all corners with zero radius
     */
    paintProperty_->UpdateTopLeftRadius(Radius(Dimension(ZERO), Dimension(ZERO)));
    paintProperty_->UpdateTopRightRadius(Radius(Dimension(ZERO), Dimension(ZERO)));
    paintProperty_->UpdateBottomRightRadius(Radius(Dimension(ZERO), Dimension(ZERO)));
    paintProperty_->UpdateBottomLeftRadius(Radius(Dimension(ZERO), Dimension(ZERO)));

    /**
     * @tc.steps: step2. Call ToJsonValue to serialize property
     * @tc.expected: step2. Verify all radius values are zero
     */
    paintProperty_->ToJsonValue(json, filter);

    auto radiusArray = json->GetValue("radius");
    EXPECT_NE(radiusArray, nullptr);
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(i)->GetArrayItem(0)->GetDouble(), ZERO);
        EXPECT_DOUBLE_EQ(radiusArray->GetArrayItem(i)->GetArrayItem(1)->GetDouble(), ZERO);
    }
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusWidth"), ZERO);
    EXPECT_DOUBLE_EQ(json->GetDouble("radiusHeight"), ZERO);
}
} // namespace OHOS::Ace::NG
