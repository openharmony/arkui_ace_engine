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

#include <vector>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/container_paint_property.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"
#include "core/components_ng/test/pattern/shape/base_shape_pattern_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const float LEFT = -20.0f;
const float TOP = -30.0f;
const int32_t COLUMN = 2;
const int32_t ROW = 3;
std::vector<double> MESH = { 1, 2, 4, 6, 4, 2, 1, 3, 5, 1, 3, 5, 6, 3, 2, 2, 4, 5, 5, 3, 2, 2, 2, 4 };
} // namespace

class ShapePatternTestNg : public BaseShapePatternTestNg {};

/**
 * @tc.name: Creator001
 * @tc.desc: create rect with width and height
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, Creator001, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckSize();
}

/**
 * @tc.name: Creator002
 * @tc.desc: create shape with no width or height
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, Creator002, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckNoSize();
}

/**
 * @tc.name: ContainerPaintProperty001
 * @tc.desc: create shape with viewport
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty001, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetViewPort(Dimension(LEFT), Dimension(TOP), Dimension(WIDTH), Dimension(HEIGHT));
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto paintProperty = frameNode->GetPaintProperty<ContainerPaintProperty>();
    EXPECT_EQ(paintProperty == nullptr, false);
    EXPECT_EQ(paintProperty->HasShapeViewBox(), true);
    EXPECT_EQ(paintProperty->GetShapeViewBoxValue().Left().ConvertToPx(), LEFT);
    EXPECT_EQ(paintProperty->GetShapeViewBoxValue().Top().ConvertToPx(), TOP);
    EXPECT_EQ(paintProperty->GetShapeViewBoxValue().Width().ConvertToPx(), WIDTH);
    EXPECT_EQ(paintProperty->GetShapeViewBoxValue().Height().ConvertToPx(), HEIGHT);
}

/**
 * @tc.name: ContainerPaintProperty002
 * @tc.desc: create shape with mesh
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty002, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto paintProperty = frameNode->GetPaintProperty<ContainerPaintProperty>();
    EXPECT_EQ(paintProperty == nullptr, false);
    EXPECT_EQ(paintProperty->HasImageMesh(), true);
    EXPECT_EQ(paintProperty->GetImageMeshValue().GetColumn(), COLUMN);
    EXPECT_EQ(paintProperty->GetImageMeshValue().GetRow(), ROW);
    auto mesh = paintProperty->GetImageMeshValue().GetMesh();
    auto size = mesh.size();
    EXPECT_EQ(size, (COLUMN + 1) * (ROW + 1) * 2);
    EXPECT_EQ(size, MESH.size());
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(mesh.at(i), MESH.at(i));
    }
}

/**
 * @tc.name: ContainerPaintProperty003
 * @tc.desc: set fill and check
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty003, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckFill();
}

/**
 * @tc.name: ContainerPaintProperty004
 * @tc.desc: set fill opacity and check
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty004, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckFillOpacity();
}

/**
 * @tc.name: ContainerPaintProperty005
 * @tc.desc: set stroke and check
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty005, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckStroke();
}

/**
 * @tc.name: ContainerPaintProperty006
 * @tc.desc: set stroke width and check
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty006, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckStrokeWidth();
}

/**
 * @tc.name: ContainerPaintProperty007
 * @tc.desc: set stroke opacity and check
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty007, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckStrokeOpacity();
}

/**
 * @tc.name: ContainerPaintProperty008
 * @tc.desc: set stroke dash array and check
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty008, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckStrokeDashArray();
}

/**
 * @tc.name: ContainerPaintProperty009
 * @tc.desc: set stroke dash offset and check
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty009, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckStrokeDashOffset();
}

/**
 * @tc.name: ContainerPaintProperty010
 * @tc.desc: set stroke line cap and check
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty010, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckStrokeLineCap();
}

/**
 * @tc.name: ContainerPaintProperty011
 * @tc.desc: set stroke line join and check
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty011, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckStrokeLineJoin();
}

/**
 * @tc.name: ContainerPaintProperty012
 * @tc.desc: set stroke miter and check
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty012, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckStrokeMiterLimit();
}

/**
 * @tc.name: ContainerPaintProperty013
 * @tc.desc: set antialias and check
 * @tc.type: FUNC
 */

HWTEST_F(ShapePatternTestNg, ContainerPaintProperty013, TestSize.Level1)
{
    ShapeModelNG().Create();
    CheckAntiAlias();
}
} // namespace OHOS::Ace::NG