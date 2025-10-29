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

#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"

#include "base/utils/utils.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"

namespace OHOS::Ace::NG {

void ShapeAbstractModelNG::SetStroke(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, Stroke, color);
}

void ShapeAbstractModelNG::SetStroke(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Stroke, color, frameNode);
}

void ShapeAbstractModelNG::SetFill(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, Fill, color);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, color);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}
void ShapeAbstractModelNG::SetForegroundColor(const Color& color)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, Fill, color);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, color);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}

void ShapeAbstractModelNG::SetFill(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Fill, color, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, color, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
}

void ShapeAbstractModelNG::SetStrokeDashOffset(const Ace::Dimension& dashOffset)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashOffset, dashOffset);
}

void ShapeAbstractModelNG::SetStrokeLineCap(int lineCapStyle)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineCap, lineCapStyle);
}

void ShapeAbstractModelNG::SetStrokeLineJoin(int lineJoinStyle)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineJoin, lineJoinStyle);
}

void ShapeAbstractModelNG::SetStrokeMiterLimit(double miterLimit)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeMiterLimit, miterLimit);
}

void ShapeAbstractModelNG::SetStrokeOpacity(double opacity)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeOpacity, opacity);
}

void ShapeAbstractModelNG::SetFillOpacity(double opacity)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, FillOpacity, std::clamp(opacity, 0.0, 1.0));
}

void ShapeAbstractModelNG::SetStrokeWidth(const Dimension& lineWidth)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeWidth, lineWidth);
}

void ShapeAbstractModelNG::SetStrokeWidth(FrameNode* frameNode, const Dimension& lineWidth)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeWidth, lineWidth, frameNode);
}

void ShapeAbstractModelNG::SetStrokeDashArray(const std::vector<Dimension>& segments)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashArray, segments);
}

void ShapeAbstractModelNG::SetAntiAlias(bool antiAlias)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, AntiAlias, antiAlias);
}

void ShapeAbstractModelNG::SetWidth(Dimension& width)
{
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    ViewAbstract::SetWidth(CalcLength(width));
}

void ShapeAbstractModelNG::SetHeight(Dimension& height)
{
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    ViewAbstract::SetHeight(CalcLength(height));
}

void ShapeAbstractModelNG::SetWidth(FrameNode* frameNode, Dimension& width)
{
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    ViewAbstract::SetWidth(frameNode, CalcLength(width));
}

void ShapeAbstractModelNG::SetHeight(FrameNode* frameNode, Dimension& height)
{
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    ViewAbstract::SetHeight(frameNode, CalcLength(height));
}

void ShapeAbstractModelNG::ResetWidth(FrameNode* frameNode)
{
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
}

void ShapeAbstractModelNG::ResetHeight(FrameNode* frameNode)
{
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}

void ShapeAbstractModelNG::SetStrokeDashArray(
    const std::vector<Ace::Dimension>& segments, const std::vector<RefPtr<ResourceObject>>& resObjArray)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetStrokeDashArray(frameNode, segments, resObjArray);
}

void ShapeAbstractModelNG::SetStrokeDashArray(FrameNode* frameNode, const std::vector<Ace::Dimension>& segments,
    const std::vector<RefPtr<ResourceObject>>& resObjArray)
{
    if (!SystemProperties::ConfigChangePerform() || frameNode == nullptr) {
        return;
    }
    auto pattern = frameNode->GetPattern<ShapePattern>();
    CHECK_NULL_VOID(pattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode), segments, resObjArray](
                            const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        if (segments.size() != resObjArray.size()) {
            return;
        }
        std::vector<Ace::Dimension> result;
        for (size_t i = 0; i < segments.size(); i++) {
            if (resObjArray[i]) {
                Dimension dim;
                if (!ResourceParseUtils::ConvertFromResObjNG(resObjArray[i], dim)) {
                    result.clear();
                    break;
                }
                result.emplace_back(dim);
            } else {
                result.emplace_back(segments[i]);
            }
        }
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashArray, result, frameNode);
        if (frameNode->GetRerenderable()) {
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    pattern->AddResObj("ShapeAbstractStrokeDashArray", resObj, std::move(updateFunc));
}

void ShapeAbstractModelNG::SetStroke(const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetStroke(frameNode, resObj);
}

void ShapeAbstractModelNG::SetFill(const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetFill(frameNode, resObj);
}

void ShapeAbstractModelNG::SetForegroundColor(const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetForegroundColor(frameNode, resObj);
}

void ShapeAbstractModelNG::SetStrokeOpacity(const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetStrokeOpacity(frameNode, resObj);
}

void ShapeAbstractModelNG::SetFillOpacity(const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetFillOpacity(frameNode, resObj);
}

void ShapeAbstractModelNG::SetStrokeWidth(const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetStrokeWidth(frameNode, resObj);
}

void ShapeAbstractModelNG::SetWidth(const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetWidth(frameNode, resObj);
}

void ShapeAbstractModelNG::SetHeight(const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetHeight(frameNode, resObj);
}

void ShapeAbstractModelNG::SetStroke(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform() || frameNode == nullptr) {
        return;
    }
    auto pattern = frameNode->GetPattern<ShapePattern>();
    CHECK_NULL_VOID(pattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        Color value;
        if (!ResourceParseUtils::ParseResColor(resObj, value)) {
            ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Stroke, Color::TRANSPARENT, frameNode);
            return;
        }
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Stroke, value, frameNode);
        if (frameNode->GetRerenderable()) {
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
    pattern->AddResObj("ShapeAbstractStroke", resObj, std::move(updateFunc));
}

void ShapeAbstractModelNG::SetFill(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform() || frameNode == nullptr) {
        return;
    }
    auto pattern = frameNode->GetPattern<ShapePattern>();
    CHECK_NULL_VOID(pattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        Color value = Color::BLACK;
        if (!ResourceParseUtils::ParseResColor(resObj, value)) {
            ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Fill, Color::BLACK, frameNode);
            ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, Color::BLACK, frameNode);
            ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
            return;
        }
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Fill, value, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, value, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
        if (frameNode->GetRerenderable()) {
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
    pattern->AddResObj("ShapeAbstractFill", resObj, std::move(updateFunc));
}

void ShapeAbstractModelNG::SetForegroundColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform() || frameNode == nullptr) {
        return;
    }
    auto pattern = frameNode->GetPattern<ShapePattern>();
    CHECK_NULL_VOID(pattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        Color value = Color::BLACK;
        if (!ResourceParseUtils::ParseResColor(resObj, value)) {
            ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Fill, Color::BLACK, frameNode);
            ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, Color::BLACK, frameNode);
            ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
            return;
        }
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Fill, value, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, value, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
        if (frameNode->GetRerenderable()) {
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
    pattern->AddResObj("ShapeAbstractForegroundColor", resObj, std::move(updateFunc));
}

void ShapeAbstractModelNG::SetStrokeOpacity(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform() || frameNode == nullptr) {
        return;
    }
    auto pattern = frameNode->GetPattern<ShapePattern>();
    CHECK_NULL_VOID(pattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        double value = 1.0;
        if (!ResourceParseUtils::ParseResDouble(resObj, value)) {
            ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeOpacity, 1.0, frameNode);
            return;
        }
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeOpacity, std::clamp(value, 0.0, 1.0), frameNode);
        if (frameNode->GetRerenderable()) {
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
    pattern->AddResObj("ShapeAbstractStrokeOpacity", resObj, std::move(updateFunc));
}

void ShapeAbstractModelNG::SetFillOpacity(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform() || frameNode == nullptr) {
        return;
    }
    auto pattern = frameNode->GetPattern<ShapePattern>();
    CHECK_NULL_VOID(pattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        double value = 1.0;
        if (!ResourceParseUtils::ParseResDouble(resObj, value)) {
            ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, FillOpacity, 1.0, frameNode);
            return;
        }
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, FillOpacity, std::clamp(value, 0.0, 1.0), frameNode);
        if (frameNode->GetRerenderable()) {
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
    pattern->AddResObj("ShapeAbstractFillOpacity", resObj, std::move(updateFunc));
}

void ShapeAbstractModelNG::SetStrokeWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform() || frameNode == nullptr) {
        return;
    }
    auto pattern = frameNode->GetPattern<ShapePattern>();
    CHECK_NULL_VOID(pattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CalcDimension value = 1.0_vp;
        if (!ResourceParseUtils::ParseResDimensionFpNG(resObj, value)) {
            ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeWidth, 1.0_vp, frameNode);
            return;
        }
        auto strokeWidth = value.IsNegative() ? 1.0_vp : value;
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeWidth, strokeWidth, frameNode);
        if (frameNode->GetRerenderable()) {
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
    pattern->AddResObj("ShapeAbstractStrokeWidth", resObj, std::move(updateFunc));
}

void ShapeAbstractModelNG::SetWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform() || frameNode == nullptr) {
        return;
    }
    auto pattern = frameNode->GetPattern<ShapePattern>();
    CHECK_NULL_VOID(pattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto layoutProperty = frameNode->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        CalcDimension value;
        if (!ResourceParseUtils::ParseResDimensionFpNG(resObj, value)) {
            layoutProperty->ClearUserDefinedIdealSize(true, false);
            return;
        }
        if (LessNotEqual(value.Value(), 0.0)) {
            value.SetValue(0.0);
        }
        // get previously user defined ideal height
        std::optional<CalcLength> height = std::nullopt;
        auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
        if (layoutConstraint && layoutConstraint->selfIdealSize) {
            height = layoutConstraint->selfIdealSize->Height();
        }
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(value), height));
        if (frameNode->GetRerenderable()) {
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
    pattern->AddResObj("ShapeAbstractWidth", resObj, std::move(updateFunc));
}

void ShapeAbstractModelNG::SetHeight(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::ConfigChangePerform() || frameNode == nullptr) {
        return;
    }
    auto pattern = frameNode->GetPattern<ShapePattern>();
    CHECK_NULL_VOID(pattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto layoutProperty = frameNode->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        CalcDimension height;
        if (!ResourceParseUtils::ParseResDimensionFpNG(resObj, height)) {
            layoutProperty->ClearUserDefinedIdealSize(false, true);
            return;
        }
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        // get previously user defined ideal height
        std::optional<CalcLength> width = std::nullopt;
        auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
        if (layoutConstraint && layoutConstraint->selfIdealSize) {
            width = layoutConstraint->selfIdealSize->Width();
        }
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(width, CalcLength(height)));
        if (frameNode->GetRerenderable()) {
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
    pattern->AddResObj("ShapeAbstractHeight", resObj, std::move(updateFunc));
}
} // namespace OHOS::Ace::NG