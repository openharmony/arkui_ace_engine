/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/components_ng/pattern/shape/polygon_pattern.h"
#include "core/components_ng/pattern/shape/polygon_paint_property.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class PolygonModifierTest : public ModifierTestBase<GENERATED_ArkUIPolygonModifier,
    &GENERATED_ArkUINodeModifiers::getPolygonModifier, GENERATED_ARKUI_POLYGON> {
};

/*
 * @tc.name: setPolylineOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModifierTest, setPolylineOptionsTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto points = paintProperty->GetPoints();
    EXPECT_FALSE(points.has_value());
}

/*
 * @tc.name: setPointsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModifierTest, setPointsTestValidValues, TestSize.Level1)
{
    auto arkPoints = std::array {
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(100.0_vp), .value1 = Converter::ArkValue<Ark_Length>(100.0_vp) },
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(200.0_vp), .value1 = Converter::ArkValue<Ark_Length>(200.0_vp) },
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(300.0_vp), .value1 = Converter::ArkValue<Ark_Length>(100.0_vp) },
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(300.0_vp), .value1 = Converter::ArkValue<Ark_Length>(300.0_vp) },
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(200.0_vp), .value1 = Converter::ArkValue<Ark_Length>(300.0_vp) },
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(100.0_vp), .value1 = Converter::ArkValue<Ark_Length>(300.0_vp) },
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(100.0_px), .value1 = Converter::ArkValue<Ark_Length>(100.0_px) },
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(200.0_px), .value1 = Converter::ArkValue<Ark_Length>(200.0_px) },
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(300.0_px), .value1 = Converter::ArkValue<Ark_Length>(100.0_px) },
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(100.0_pct),
            .value1 = Converter::ArkValue<Ark_Length>(100.0_pct) },
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(13.0_pct), .value1 = Converter::ArkValue<Ark_Length>(26.0_pct) },
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(1.23_vp), .value1 = Converter::ArkValue<Ark_Length>(4.56_vp) }
    };
    Converter::ArkArrayHolder<Array_ShapePoint> holderArg(arkPoints);
    Opt_Array_ShapePoint value = holderArg.OptValue<Opt_Array_ShapePoint>();
    modifier_->setPoints(node_, &value);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto points = paintProperty->GetPoints();
    ASSERT_TRUE(points.has_value());
    ASSERT_EQ(arkPoints.size(), points->size());
    for (int i = 0; i < points->size(); ++i) {
        EXPECT_EQ(Converter::OptConvert<Dimension>(arkPoints[i].value0), (*points)[i].first);
        EXPECT_EQ(Converter::OptConvert<Dimension>(arkPoints[i].value1), (*points)[i].second);
    }
}

/*
 * @tc.name: setPointsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolygonModifierTest, setPointsTestInvalidValues, TestSize.Level1)
{
    auto arkPoints = std::array {
        Ark_ShapePoint {
            .value0 = Converter::ArkValue<Ark_Length>(100.0_vp), .value1 = Converter::ArkValue<Ark_Length>(100.0_vp) },
    };
    Converter::ArkArrayHolder<Array_ShapePoint> holderArg(arkPoints);
    Opt_Array_ShapePoint value = holderArg.OptValue<Opt_Array_ShapePoint>();
    modifier_->setPoints(node_, &value);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto points = paintProperty->GetPoints();
    EXPECT_FALSE(points.has_value());
}

} // namespace OHOS::Ace::NG
