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

#include "core/components_ng/test/pattern/shape/base_shape_pattern_test_ng.h"

#include <vector>

#include "gtest/gtest.h"

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
namespace {
const float OPACITY = 0.5f;
float STROKE_WIDTH = 3.0f;
const bool ANTIALIAS = false;
const float STROKE_LIMIT = 5.0f;
const float DASHOFFSET = 3;
const int32_t LINE_JOIN = 1;
const int32_t LINE_CAP = 1;
const std::vector<float> STROK_DASH_ARRAY = { 3, 5 };
} // namespace
void BaseShapePatternTestNg::CheckSize()
{
    auto width = Dimension(WIDTH);
    auto height = Dimension(HEIGHT);
    auto shapeAbstactModel = ShapeAbstractModelNG();
    shapeAbstactModel.SetWidth(width);
    shapeAbstactModel.SetHeight(height);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto layoutProperty = frameNode->GetLayoutProperty();
    auto mesureLayout = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(mesureLayout.has_value(), true);
    EXPECT_EQ(mesureLayout->Width().has_value(), true);
    EXPECT_STREQ(mesureLayout->Width()->ToString().c_str(), width.ToString().c_str());
    EXPECT_EQ(mesureLayout->Height().has_value(), true);
    EXPECT_STREQ(mesureLayout->Height()->ToString().c_str(), height.ToString().c_str());
}

void BaseShapePatternTestNg::CheckNoSize()
{
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty->GetCalcLayoutConstraint() == nullptr, true);
}

void BaseShapePatternTestNg::CheckFill()
{
    ShapeAbstractModelNG().SetFill(Color::RED);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_EQ(shapeProperty == nullptr, false);
    EXPECT_EQ(shapeProperty->HasFill(), true);
    EXPECT_EQ(shapeProperty->GetFillValue(), Color::RED);
}

void BaseShapePatternTestNg::CheckFillOpacity()
{
    ShapeAbstractModelNG().SetFillOpacity(OPACITY);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_EQ(shapeProperty == nullptr, false);
    EXPECT_FLOAT_EQ(shapeProperty->GetFillOpacityValue(), OPACITY);
}

void BaseShapePatternTestNg::CheckStroke()
{
    ShapeAbstractModelNG().SetStroke(Color::RED);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_EQ(shapeProperty == nullptr, false);
    EXPECT_EQ(shapeProperty->HasStroke(), true);
    EXPECT_EQ(shapeProperty->GetStrokeValue(), Color::RED);
}

void BaseShapePatternTestNg::CheckStrokeWidth()
{
    ShapeAbstractModelNG().SetStrokeWidth(Dimension(STROKE_WIDTH));
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_EQ(shapeProperty == nullptr, false);
    EXPECT_EQ(shapeProperty->HasStrokeWidth(), true);
    EXPECT_FLOAT_EQ(shapeProperty->GetStrokeWidthValue().ConvertToPx(), STROKE_WIDTH);
}

void BaseShapePatternTestNg::CheckStrokeOpacity()
{
    ShapeAbstractModelNG().SetStrokeOpacity(OPACITY);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_EQ(shapeProperty == nullptr, false);
    EXPECT_EQ(shapeProperty->HasStrokeOpacity(), true);
    EXPECT_FLOAT_EQ(shapeProperty->GetStrokeOpacityValue(), OPACITY);
}

void BaseShapePatternTestNg::CheckStrokeDashArray()
{
    auto len = static_cast<int32_t>(STROK_DASH_ARRAY.size());
    std::vector<Dimension> strokeDashArray(len);
    for (int32_t i = 0; i < len; i++) {
        strokeDashArray[i] = Dimension(STROK_DASH_ARRAY.at(i));
    }
    ShapeAbstractModelNG().SetStrokeDashArray(strokeDashArray);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_EQ(shapeProperty == nullptr, false);
    EXPECT_EQ(shapeProperty->HasStrokeDashArray(), true);
    EXPECT_EQ(shapeProperty->GetStrokeDashArrayValue().size(), STROK_DASH_ARRAY.size());
    const std::vector<Dimension> propStrokeDashArray = shapeProperty->GetStrokeDashArrayValue();
    auto propLen = static_cast<int32_t>(propStrokeDashArray.size());
    for (int32_t i = 0; i < propLen; i++) {
        EXPECT_FLOAT_EQ(propStrokeDashArray[i].ConvertToPx(), STROK_DASH_ARRAY.at(i));
    }
}

void BaseShapePatternTestNg::CheckStrokeDashOffset()
{
    ShapeAbstractModelNG().SetStrokeDashOffset(Dimension(DASHOFFSET));
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_EQ(shapeProperty == nullptr, false);
    EXPECT_EQ(shapeProperty->HasStrokeDashOffset(), true);
    EXPECT_FLOAT_EQ(shapeProperty->GetStrokeDashOffset()->ConvertToPx(), DASHOFFSET);
}

void BaseShapePatternTestNg::CheckStrokeLineCap()
{
    ShapeAbstractModelNG().SetStrokeLineCap(LINE_CAP);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_EQ(shapeProperty == nullptr, false);
    EXPECT_EQ(shapeProperty->HasStrokeLineCap(), true);
    EXPECT_EQ(shapeProperty->GetStrokeLineCap(), 1);
}

void BaseShapePatternTestNg::CheckStrokeLineJoin()
{
    ShapeAbstractModelNG().SetStrokeLineJoin(LINE_JOIN);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_EQ(shapeProperty == nullptr, false);
    EXPECT_EQ(shapeProperty->HasStrokeLineJoin(), true);
    EXPECT_EQ(shapeProperty->GetStrokeLineJoinValue(), 1);
}

void BaseShapePatternTestNg::CheckStrokeMiterLimit()
{
    ShapeAbstractModelNG().SetStrokeMiterLimit(STROKE_LIMIT);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_EQ(shapeProperty == nullptr, false);
    EXPECT_EQ(shapeProperty->HasStrokeMiterLimit(), true);
    EXPECT_FLOAT_EQ(static_cast<float>(shapeProperty->GetStrokeMiterLimitValue()), STROKE_LIMIT);
}

void BaseShapePatternTestNg::CheckAntiAlias()
{
    ShapeAbstractModelNG().SetAntiAlias(ANTIALIAS);
    RefPtr<UINode> uiNode = ViewStackProcessor::GetInstance()->Finish();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    EXPECT_EQ(frameNode == nullptr, false);
    auto shapeProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    EXPECT_EQ(shapeProperty == nullptr, false);
    EXPECT_EQ(shapeProperty->HasAntiAlias(), true);
    EXPECT_EQ(shapeProperty->GetAntiAliasValue(), ANTIALIAS);
}

} // namespace OHOS::Ace::NG