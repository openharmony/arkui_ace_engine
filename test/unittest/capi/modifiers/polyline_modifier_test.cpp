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

class PolylineModifierTest : public ModifierTestBase<GENERATED_ArkUIPolylineModifier,
    &GENERATED_ArkUINodeModifiers::getPolylineModifier, GENERATED_ARKUI_POLYLINE> {
};

/*
 * @tc.name: setPolylineOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolylineModifierTest, setPolylineOptionsTestDefaultValues, TestSize.Level1)
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
HWTEST_F(PolylineModifierTest, setPointsTestValidValues, TestSize.Level1)
{
    auto arkPoints = std::array {
        Ark_Point{ .x = Converter::ArkValue<Ark_Number>(100), .y = Converter::ArkValue<Ark_Number>(100) },
        Ark_Point{ .x = Converter::ArkValue<Ark_Number>(200), .y = Converter::ArkValue<Ark_Number>(200) },
        Ark_Point{ .x = Converter::ArkValue<Ark_Number>(300), .y = Converter::ArkValue<Ark_Number>(100) },
        Ark_Point{ .x = Converter::ArkValue<Ark_Number>(300), .y = Converter::ArkValue<Ark_Number>(300) },
        Ark_Point{ .x = Converter::ArkValue<Ark_Number>(200), .y = Converter::ArkValue<Ark_Number>(300) },
        Ark_Point{ .x = Converter::ArkValue<Ark_Number>(100), .y = Converter::ArkValue<Ark_Number>(300) }
    };
    Converter::ArkArrayHolder<Array_Point> holderArg(arkPoints);
    Array_Point value = holderArg.ArkValue();
    modifier_->setPoints(node_, &value);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto points = paintProperty->GetPoints();
    ASSERT_TRUE(points.has_value());
    ASSERT_EQ(arkPoints.size(), points->size());
    for (int i = 0; i < points->size(); ++i) {
        EXPECT_EQ(Converter::Convert<Dimension>(arkPoints[i].x), (*points)[i].first);
        EXPECT_EQ(Converter::Convert<Dimension>(arkPoints[i].y), (*points)[i].second);
    }
}

/*
 * @tc.name: setPointsTestInalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolylineModifierTest, setPointsTestInalidValues, TestSize.Level1)
{
    auto arkPoints = std::array {
        Ark_Point{ .x = Converter::ArkValue<Ark_Number>(100), .y = Converter::ArkValue<Ark_Number>(100) },
    };
    Converter::ArkArrayHolder<Array_Point> holderArg(arkPoints);
    Array_Point value = holderArg.ArkValue();
    modifier_->setPoints(node_, &value);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto paintProperty = frameNode->GetPaintProperty<PolygonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto points = paintProperty->GetPoints();
    EXPECT_FALSE(points.has_value());
}

} // namespace OHOS::Ace::NG
