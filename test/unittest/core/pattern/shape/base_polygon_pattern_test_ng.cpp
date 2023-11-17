/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base_polygon_pattern_test_ng.h"

#include "core/components/shape/shape_component.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/polygon_model_ng.h"
#include "core/components_ng/pattern/shape/polygon_paint_property.h"

namespace OHOS::Ace::NG {

namespace {

const std::array<std::array<float, 2>, 5> POINTS = { { { 50, 0 }, { 0, 50 }, { 20, 100 }, { 80, 100 }, { 100, 50 } } };

} // namespace

void BasePolygonPatternTestNg::CheckPoints(RefPtr<FrameNode> frameNode, bool hasValue)
{
    EXPECT_EQ(frameNode == nullptr, false);
    if (hasValue) {
        ShapePoints shapePoints;
        auto size = static_cast<int32_t>(POINTS.size());
        for (int32_t i = 0; i < size; i++) {
            shapePoints.emplace_back(ShapePoint(Dimension(POINTS.at(i).at(0)), Dimension(POINTS.at(i).at(1))));
        }
        PolygonModelNG().SetPoints(shapePoints);
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto polygonPaintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    if (hasValue) {
        EXPECT_EQ(polygonPaintProperty->HasPoints(), true);
        auto propLen = static_cast<int32_t>(polygonPaintProperty->GetPointsValue().size());
        EXPECT_EQ(propLen, static_cast<int32_t>(POINTS.size()));
        auto propPoints = polygonPaintProperty->GetPointsValue();
        for (int32_t i = 0; i < propLen; i++) {
            EXPECT_FLOAT_EQ(propPoints[i].first.ConvertToPx(), POINTS[i][0]);
            EXPECT_FLOAT_EQ(propPoints[i].second.ConvertToPx(), POINTS[i][1]);
        }
    } else {
        EXPECT_EQ(polygonPaintProperty->HasPoints(), false);
    }
}
} // namespace OHOS::Ace::NG