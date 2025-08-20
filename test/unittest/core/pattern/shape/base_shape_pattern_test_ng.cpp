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

#include "base_shape_pattern_test_ng.h"

#include "gtest/gtest.h"

#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace::NG {

void BaseShapePatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void BaseShapePatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}
void BaseShapePatternTestNg::CheckSize(bool hasValue)
{
    auto frameNode = CreadFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    if (hasValue) {
        auto shapeAbstactModel = ShapeAbstractModelNG();
        SetSize(shapeAbstactModel);
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (hasValue) {
        auto mesureLayout = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
        EXPECT_TRUE(mesureLayout.has_value());
        EXPECT_TRUE(mesureLayout->Width().has_value());
        EXPECT_TRUE(mesureLayout->Height().has_value());
    } else {
        EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr);
    }
}

void BaseShapePatternTestNg::CheckFill(bool hasValue)
{
    auto frameNode = CreadFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    if (hasValue) {
        shapeAbstactModel.SetFill(Color::RED);
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_TRUE(shapeProperty != nullptr);
    if (hasValue) {
        EXPECT_TRUE(shapeProperty->HasFill());
        EXPECT_EQ(shapeProperty->GetFillValue(), Color::RED);
    } else {
        EXPECT_FALSE(shapeProperty->HasFill());
    }
    Draw(frameNode);
}

void BaseShapePatternTestNg::CheckFillOpacity(bool hasValue)
{
    auto frameNode = CreadFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    if (hasValue) {
        shapeAbstactModel.SetFillOpacity(OPACITY);
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_TRUE(shapeProperty != nullptr);
    if (hasValue) {
        EXPECT_TRUE(shapeProperty->HasFillOpacity());
        EXPECT_FLOAT_EQ(shapeProperty->GetFillOpacityValue(), OPACITY);
    } else {
        EXPECT_FALSE(shapeProperty->HasFillOpacity());
    }
    Draw(frameNode);
}

void BaseShapePatternTestNg::CheckStroke(bool hasValue)
{
    auto frameNode = CreadFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    if (hasValue) {
        shapeAbstactModel.SetStroke(Color::RED);
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_TRUE(shapeProperty != nullptr);
    if (hasValue) {
        EXPECT_TRUE(shapeProperty->HasStroke());
        EXPECT_EQ(shapeProperty->GetStrokeValue(), Color::RED);
    } else {
        EXPECT_FALSE(shapeProperty->HasStroke());
    }
    Draw(frameNode);
}

void BaseShapePatternTestNg::CheckStrokeWidth(bool hasValue)
{
    auto frameNode = CreadFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    if (hasValue) {
        shapeAbstactModel.SetStrokeWidth(Dimension(STROKE_WIDTH));
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_TRUE(shapeProperty != nullptr);
    if (hasValue) {
        EXPECT_TRUE(shapeProperty->HasStrokeWidth());
        EXPECT_FLOAT_EQ(shapeProperty->GetStrokeWidthValue().ConvertToPx(), STROKE_WIDTH);
    } else {
        EXPECT_FALSE(shapeProperty->HasStrokeWidth());
    }
    Draw(frameNode);
}

void BaseShapePatternTestNg::CheckStrokeOpacity(bool hasValue)
{
    auto frameNode = CreadFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    if (hasValue) {
        shapeAbstactModel.SetStrokeOpacity(OPACITY);
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_TRUE(shapeProperty != nullptr);
    if (hasValue) {
        EXPECT_TRUE(shapeProperty->HasStrokeOpacity());
        EXPECT_FLOAT_EQ(shapeProperty->GetStrokeOpacityValue(), OPACITY);
    } else {
        EXPECT_FALSE(shapeProperty->HasStrokeOpacity());
    }
    Draw(frameNode);
}

void BaseShapePatternTestNg::CheckStrokeDashArray(bool hasValue)
{
    auto frameNode = CreadFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    if (hasValue) {
        auto len = static_cast<int32_t>(STROKE_DASH_ARRAY.size());
        std::vector<Dimension> strokeDashArray(len);
        for (int32_t i = 0; i < len; i++) {
            strokeDashArray[i] = Dimension(STROKE_DASH_ARRAY.at(i));
        }
        shapeAbstactModel.SetStrokeDashArray(strokeDashArray);
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_TRUE(shapeProperty != nullptr);
    if (hasValue) {
        EXPECT_TRUE(shapeProperty->HasStrokeDashArray());
        EXPECT_EQ(shapeProperty->GetStrokeDashArrayValue().size(), STROKE_DASH_ARRAY.size());
        const std::vector<Dimension> propStrokeDashArray = shapeProperty->GetStrokeDashArrayValue();
        auto propLen = static_cast<int32_t>(propStrokeDashArray.size());
        for (int32_t i = 0; i < propLen; i++) {
            EXPECT_FLOAT_EQ(propStrokeDashArray[i].ConvertToPx(), STROKE_DASH_ARRAY.at(i));
        }
    } else {
        EXPECT_FALSE(shapeProperty->HasStrokeDashArray());
    }
    Draw(frameNode);
}

void BaseShapePatternTestNg::CheckStrokeDashOffset(bool hasValue)
{
    auto frameNode = CreadFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    if (hasValue) {
        shapeAbstactModel.SetStrokeDashOffset(Dimension(DASHOFFSET));
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_TRUE(shapeProperty != nullptr);
    if (hasValue) {
        EXPECT_TRUE(shapeProperty->HasStrokeDashOffset());
        EXPECT_FLOAT_EQ(shapeProperty->GetStrokeDashOffset()->ConvertToPx(), DASHOFFSET);
    } else {
        EXPECT_FALSE(shapeProperty->HasStrokeDashOffset());
    }
    Draw(frameNode);
}

void BaseShapePatternTestNg::CheckStrokeLineCap(bool hasValue)
{
    auto frameNode = CreadFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    if (hasValue) {
        shapeAbstactModel.SetStrokeLineCap(LINE_CAP);
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_TRUE(shapeProperty != nullptr);
    if (hasValue) {
        EXPECT_TRUE(shapeProperty->HasStrokeLineCap());
        EXPECT_EQ(shapeProperty->GetStrokeLineCap(), LINE_CAP);
    } else {
        EXPECT_FALSE(shapeProperty->HasStrokeLineCap());
    }
    Draw(frameNode);
}

void BaseShapePatternTestNg::CheckStrokeLineJoin(bool hasValue)
{
    auto frameNode = CreadFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    if (hasValue) {
        shapeAbstactModel.SetStrokeLineJoin(LINE_JOIN);
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_TRUE(shapeProperty != nullptr);
    if (hasValue) {
        EXPECT_TRUE(shapeProperty->HasStrokeLineJoin());
        EXPECT_EQ(shapeProperty->GetStrokeLineJoinValue(), LINE_JOIN);
    } else {
        EXPECT_FALSE(shapeProperty->HasStrokeLineJoin());
    }
    Draw(frameNode);
}

void BaseShapePatternTestNg::CheckStrokeMiterLimit(bool hasValue)
{
    auto frameNode = CreadFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    if (hasValue) {
        shapeAbstactModel.SetStrokeMiterLimit(STROKE_LIMIT);
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_TRUE(shapeProperty != nullptr);
    if (hasValue) {
        EXPECT_TRUE(shapeProperty->HasStrokeMiterLimit());
        EXPECT_FLOAT_EQ(static_cast<float>(shapeProperty->GetStrokeMiterLimitValue()), STROKE_LIMIT);
    } else {
        EXPECT_FALSE(shapeProperty->HasStrokeMiterLimit());
    }
    Draw(frameNode);
}

void BaseShapePatternTestNg::CheckAntiAlias(bool hasValue)
{
    auto frameNode = CreadFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    SetSize(shapeAbstactModel);
    if (hasValue) {
        shapeAbstactModel.SetAntiAlias(ANTIALIAS);
    }
    ViewStackProcessor::GetInstance()->Pop();
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_TRUE(shapeProperty != nullptr);
    if (hasValue) {
        EXPECT_TRUE(shapeProperty->HasAntiAlias());
        EXPECT_EQ(shapeProperty->GetAntiAliasValue(), ANTIALIAS);
    } else {
        EXPECT_FALSE(shapeProperty->HasAntiAlias());
    }
    Draw(frameNode);
}

void BaseShapePatternTestNg::SetSize(ShapeAbstractModelNG& shapeAbstractModelNG) const
{
    auto width = Dimension(WIDTH);
    auto height = Dimension(HEIGHT);
    shapeAbstractModelNG.SetWidth(width);
    shapeAbstractModelNG.SetHeight(height);
}

} // namespace OHOS::Ace::NG