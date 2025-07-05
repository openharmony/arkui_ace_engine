/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/shape/shape_container_pattern.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/shape_container_paint_method.h"

namespace OHOS::Ace::NG {
bool ShapeContainerPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent() || isShapeContainerInit_) {
        return false;
    }
    ViewPortTransform();
    return true;
}

void ShapeContainerPattern::ViewPortTransform()
{
    auto curFrameNode = GetHost();
    auto renderContext = curFrameNode->GetRenderContext();
    auto geoNode = curFrameNode->GetGeometryNode();
    CHECK_NULL_VOID(geoNode);
    auto contentSize = geoNode->GetContentSize();
    auto paintProperty = curFrameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    if (paintProperty->HasShapeViewBox() && paintProperty->GetShapeViewBoxValue().IsValid()) {
        double portWidth = paintProperty->GetShapeViewBoxValue().Width().ConvertToPx();
        double portHeight = paintProperty->GetShapeViewBoxValue().Height().ConvertToPx();
        double portLeft = paintProperty->GetShapeViewBoxValue().Left().ConvertToPx();
        double portTop = paintProperty->GetShapeViewBoxValue().Top().ConvertToPx();
        if (contentSize.IsPositive() && GreatNotEqual(portWidth, 0.0) && GreatNotEqual(portHeight, 0.0)) {
            double scale = std::min(contentSize.Width() / portWidth, contentSize.Height() / portHeight);
            double tx = contentSize.Width() * 0.5 - (portWidth * 0.5 + portLeft) * scale;
            double ty = contentSize.Height() * 0.5 - (portHeight * 0.5 + portTop) * scale;
            for (const auto& child : curFrameNode->GetChildren()) {
                auto node = AceType::DynamicCast<FrameNode>(child);
                CHECK_NULL_VOID(node);
                auto context = node->GetRenderContext();
                CHECK_NULL_VOID(context);
                context->UpdateTransformCenter(DimensionOffset(Offset(0.0, 0.0)));
                context->OnTransformTranslateUpdate({ tx, ty, 0 });
                context->OnTransformScaleUpdate({ scale, scale });

                if (context->HasOffset()) {
                    auto currentOffset = context->GetOffset();
                    auto newOffset = OffsetT(Dimension(currentOffset->GetX() * scale),
                        Dimension(currentOffset->GetY() * scale));
                    context->UpdateOffset(newOffset);
                    context->OnOffsetUpdate(newOffset);
                    node->MarkModifyDone();
                }
            }
        }
    }
    isShapeContainerInit_ = true;
}

void ShapeContainerPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<ShapeContainerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->HasStrokeMiterLimit()) {
        auto miterLimit = paintProperty->GetStrokeMiterLimitValue();
        if (Negative(miterLimit)) {
            paintProperty->UpdateStrokeMiterLimit(ShapePaintProperty::STROKE_MITERLIMIT_DEFAULT);
        } else if (NonNegative(miterLimit) &&
            LessNotEqual(miterLimit, ShapePaintProperty::STROKE_MITERLIMIT_MIN)) {
            paintProperty->UpdateStrokeMiterLimit(ShapePaintProperty::STROKE_MITERLIMIT_MIN);
        }
    }

    Pattern::OnModifyDone();
    for (auto childNode : ChildNodes_) {
        auto child = childNode.Upgrade();
        if (!child) {
            continue;
        }
        child->MarkNeedRenderOnly();
    }
    ChildNodes_.clear();
}

void ShapeContainerPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
    host->GetRenderContext()->SetClipToFrame(true);
}

RefPtr<NodePaintMethod> ShapeContainerPattern::CreateNodePaintMethod()
{
    if (!shapeContainerModifier_) {
        shapeContainerModifier_ = MakeRefPtr<ShapeContainerModifier>();
    }
    return MakeRefPtr<ShapeContainerPaintMethod>(shapeContainerModifier_);
}

#define DEFINE_PROP_HANDLER(KEY_TYPE, VALUE_TYPE, UPDATE_METHOD)                                                       \
    { #KEY_TYPE, [](ShapeContainerPaintProperty* prop, RefPtr<PropertyValueBase> value, RefPtr<FrameNode> frameNode) { \
         if (auto realValue = std::get_if<VALUE_TYPE>(&(value->GetValue()))) {                                         \
             prop->UPDATE_METHOD(*realValue);                                                                          \
         }                                                                                                             \
     } }

void ShapeContainerPattern::UpdatePropertyImpl(const std::string& key, RefPtr<PropertyValueBase> value)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetPaintPropertyPtr<ShapeContainerPaintProperty>();
    CHECK_NULL_VOID(property);
    using Handler = std::function<void(ShapeContainerPaintProperty*, RefPtr<PropertyValueBase>, RefPtr<FrameNode>)>;
    static const std::unordered_map<std::string, Handler> handlers = {
        DEFINE_PROP_HANDLER(ShapeStroke, Color, UpdateStroke),
        DEFINE_PROP_HANDLER(ShapeDashOffset, CalcDimension, UpdateStrokeDashOffset),
        DEFINE_PROP_HANDLER(ShapeMiterLimit, double, UpdateStrokeMiterLimit),
        { "ShapeFill",
            [](ShapeContainerPaintProperty* prop, RefPtr<PropertyValueBase> value, RefPtr<FrameNode> frameNode) {
                if (auto realValue = std::get_if<Color>(&(value->GetValue()))) {
                    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapeContainerPaintProperty, Fill, *realValue, frameNode);
                    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, *realValue, frameNode);
                    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
                }
            } },
        { "ShapeStrokeOpacity",
            [](ShapeContainerPaintProperty* prop, RefPtr<PropertyValueBase> value, RefPtr<FrameNode> frameNode) {
                if (auto realValue = std::get_if<double>(&(value->GetValue()))) {
                    auto strokeOpacity = std::clamp(*realValue, 0.0, 1.0);
                    prop->UpdateStrokeOpacity(strokeOpacity);
                }
            } },
        { "ShapeFillOpacity",
            [](ShapeContainerPaintProperty* prop, RefPtr<PropertyValueBase> value, RefPtr<FrameNode> frameNode) {
                if (auto realValue = std::get_if<double>(&(value->GetValue()))) {
                    auto fillOpacity = std::clamp(*realValue, 0.0, 1.0);
                    prop->UpdateFillOpacity(fillOpacity);
                }
            } },
        { "ShapeStrokeWidth",
            [](ShapeContainerPaintProperty* prop, RefPtr<PropertyValueBase> value, RefPtr<FrameNode> frameNode) {
                if (auto realValue = std::get_if<CalcDimension>(&(value->GetValue()))) {
                    auto strokeWidth = realValue->IsNegative() ? 1.0_vp : *realValue;
                    prop->UpdateStrokeWidth(strokeWidth);
                }
            } },
    };
    auto it = handlers.find(key);
    if (it != handlers.end()) {
        it->second(property, value, frameNode);
    }
    if (frameNode->GetRerenderable()) {
        for (auto childNode : ChildNodes_) {
            auto child = childNode.Upgrade();
            if (!child) {
                continue;
            }
            child->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }
}
} // namespace OHOS::Ace::NG
