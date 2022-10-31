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

#include <array>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/radius.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/rect_model_ng.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/test/pattern/shape/base_shape_pattern_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::array<std::array<float, 2>, 4> RADIUS = { { { 21, 4 }, { 3, 33 }, { 22, 44 }, { 0, 44 } } };
const Dimension RADIUS_WIDTH = Dimension(20);
const Dimension RADIUS_HEIGHT = Dimension(2);
} // namespace
class RectPatternTestNg : public BaseShapePatternTestNg {};

/**
 * @tc.name: Creator001
 * @tc.desc: create rect with width and height
 * @tc.type: FUNC
 */

HWTEST_F(RectPatternTestNg, Creator001, TestSize.Level1)
{
    RectModelNG().Create();
    CheckSize();
}

/**
 * @tc.name: Creator002
 * @tc.desc: create rect with no width or height
 * @tc.type: FUNC
 */

HWTEST_F(RectPatternTestNg, Creator002, TestSize.Level1)
{
    RectModelNG().Create();
    CheckNoSize();
}

/**
 * @tc.name: RectPaintProperty001
 * @tc.desc: create rect with radius
 * @tc.type: FUNC
 */

HWTEST_F(RectPatternTestNg, RectPaintProperty001, TestSize.Level1)
{
    RectModelNG().Create();
    for (int i = 0; i < RADIUS.size(); i++) {
        RectModelNG().SetRadiusValue(Dimension(RADIUS.at(i).at(0)), Dimension(RADIUS.at(i).at(1)), i);
    }
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    EXPECT_EQ(paintProperty == nullptr, false);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), true);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), true);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), RADIUS.at(0).at(0));
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), RADIUS.at(0).at(1));
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetX().ConvertToPx(), RADIUS.at(1).at(0));
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetY().ConvertToPx(), RADIUS.at(1).at(1));
    EXPECT_FLOAT_EQ(paintProperty->GetBottomRightRadiusValue().GetX().ConvertToPx(), RADIUS.at(2).at(0));
    EXPECT_FLOAT_EQ(paintProperty->GetBottomRightRadiusValue().GetY().ConvertToPx(), RADIUS.at(2).at(1));
    EXPECT_FLOAT_EQ(paintProperty->GetBottomLeftRadiusValue().GetX().ConvertToPx(), RADIUS.at(3).at(0));
    EXPECT_FLOAT_EQ(paintProperty->GetBottomLeftRadiusValue().GetY().ConvertToPx(), RADIUS.at(3).at(1));
}

/**
 * @tc.name: RectPaintProperty002
 * @tc.desc: create rect with radius width and radius height
 * @tc.type: FUNC
 */

HWTEST_F(RectPatternTestNg, RectPaintProperty002, TestSize.Level1)
{
    RectModelNG().Create();
    RectModelNG().SetRadiusWidth(RADIUS_WIDTH);
    RectModelNG().SetRadiusHeight(RADIUS_HEIGHT);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    EXPECT_EQ(paintProperty == nullptr, false);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), true);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), true);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), RADIUS_WIDTH.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), RADIUS_HEIGHT.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetX().ConvertToPx(), RADIUS_WIDTH.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetY().ConvertToPx(), RADIUS_HEIGHT.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetBottomRightRadiusValue().GetX().ConvertToPx(), RADIUS_WIDTH.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetBottomRightRadiusValue().GetY().ConvertToPx(), RADIUS_HEIGHT.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetBottomLeftRadiusValue().GetX().ConvertToPx(), RADIUS_WIDTH.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetBottomLeftRadiusValue().GetY().ConvertToPx(), RADIUS_HEIGHT.ConvertToPx());
}

} // namespace OHOS::Ace::NG