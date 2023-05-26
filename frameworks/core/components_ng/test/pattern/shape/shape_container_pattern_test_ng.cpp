/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#define private public
#define protected public

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/pattern/shape/circle_pattern.h"
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_container_layout_algorithm.h"
#include "core/components_ng/pattern/shape/shape_container_paint_property.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"
#include "core/components_ng/test/pattern/shape/base_shape_pattern_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const int32_t COLUMN = 2;
const int32_t ROW = 3;
std::vector<double> MESH = { 1, 2, 4, 6, 4, 2, 1, 3, 5, 1, 3, 5, 6, 3, 2, 2, 4, 5, 5, 3, 2, 2, 2, 4 };
} // namespace

class ShapeContainerPatternTestNg : public BaseShapePatternTestNg {
public:
    RefPtr<FrameNode> CreadFrameNode() override
    {
        return nullptr;
    }

    void Draw(RefPtr<FrameNode> frameNode) override {}
};

/**
 * @tc.name: OnDirtyLayoutWrapperSwap
 * @tc.desc: check ShapeContainerPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */

HWTEST_F(ShapeContainerPatternTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto shapeModel = ShapeModelNG();
    shapeModel.Create();
    shapeModel.SetBitmapMesh(MESH, COLUMN, ROW);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_TRUE(frameNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    auto layoutAlgorithm = AceType::DynamicCast<ShapeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    /**
     * @tc.desc: Call OnDirtyLayoutWrapperSwap(skipMeasure = true; dirty->SkipMeasureContent() = false;
     *           isShapeContainerInit_ = false)
     */
    auto flag01 = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_FALSE(flag01);
    /**
     * @tc.desc: Call OnDirtyLayoutWrapperSwap(skipMeasure = false; dirty->SkipMeasureContent() = false;
     *           isShapeContainerInit_ = false)
     */
    auto flag02 = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, true);
    EXPECT_TRUE(flag02);
    /**
     * @tc.desc: Call OnDirtyLayoutWrapperSwap(skipMeasure = false; dirty->SkipMeasureContent() = true;
     *           isShapeContainerInit_ = true)
     */
    layoutWrapper->skipMeasureContent_ = std::make_optional<bool>(true);
    EXPECT_TRUE(layoutWrapper);
    auto flag03 = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, true);
    EXPECT_FALSE(flag03);
    /**
     * @tc.desc: Call ViewPortTransform(false)
     */
    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    EXPECT_TRUE(paintProperty);
    pattern->ViewPortTransform();
    paintProperty->propShapeViewBox_ = std::nullopt;
    pattern->ViewPortTransform();
    EXPECT_EQ(pattern->isShapeContainerInit_, true);
    /**
     * @tc.desc: Call OnModifyDone(false)
     */
    pattern->OnModifyDone();
}
}