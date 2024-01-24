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
#include "core/interfaces/native/node/render_node_modifier.h"

#include <cstdint>
#include <optional>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/shape.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/components_ng/pattern/render_node/render_node_properties.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/render/render_context.h"
#include "core/interfaces/native/node/api.h"

namespace OHOS::Ace::NG {

RefPtr<RenderContext> GetRenderContext(UINode* UiNode)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(UiNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto context = frameNode->GetRenderContext();
    return context;
}

void AppendChild(NodeHandle node, NodeHandle child)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* childNode = reinterpret_cast<UINode*>(child);
    auto childRef = Referenced::Claim<UINode>(childNode);
    currentNode->AddChild(childRef);
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

void InsertChildAfter(NodeHandle node, NodeHandle child, NodeHandle sibling)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* childNode = reinterpret_cast<UINode*>(child);
    auto index = -1;
    auto* siblingNode = reinterpret_cast<UINode*>(sibling);
    index = currentNode->GetChildIndex(Referenced::Claim<UINode>(siblingNode));
    currentNode->AddChild(Referenced::Claim<UINode>(childNode), index + 1);
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

void RemoveChild(NodeHandle node, NodeHandle child)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* childNode = reinterpret_cast<UINode*>(child);
    currentNode->RemoveChild(Referenced::Claim<UINode>(childNode));
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

void ClearChildren(NodeHandle node)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    currentNode->Clean();
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

void SetClipToFrame(NodeHandle node, bool useClip)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetClipToFrame(useClip);
}

void SetRotation(NodeHandle node, double rotationX, double rotationY, double rotationZ)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    Dimension first = Dimension(rotationX, DimensionUnit::VP);
    Dimension second = Dimension(rotationY, DimensionUnit::VP);
    Dimension third = Dimension(rotationZ, DimensionUnit::VP);
    renderContext->SetRotation(first.ConvertToPx(), second.ConvertToPx(), third.ConvertToPx());
}

void SetShadowColor(NodeHandle node, uint32_t color)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowColor(color);
}

void SetShadowOffset(NodeHandle node, double offsetX, double offsetY)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    Dimension first = Dimension(offsetX, DimensionUnit::VP);
    Dimension second = Dimension(offsetY, DimensionUnit::VP);
    renderContext->SetShadowOffset(first.ConvertToPx(), second.ConvertToPx());
}

void SetShadowAlpha(NodeHandle node, float alpha)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowAlpha(alpha);
}

void SetShadowElevation(NodeHandle node, float elevation)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowElevation(elevation);
}

void SetShadowRadius(NodeHandle node, float radius)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowRadius(radius);
}

void Invalidate(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RenderNodePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->Invalidate();
}

void SetScale(NodeHandle node, float scaleX, float scaleY)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetScale(scaleX, scaleY);
}

void SetRenderNodeBackgroundColor(NodeHandle node, uint32_t colorValue)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetBackgroundColor(colorValue);
}

void SetPivot(NodeHandle node, float pivotX, float pivotY)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetRenderPivot(pivotX, pivotY);
}

void SetFrame(NodeHandle node, float positionX, float positionY, float width, float height)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetFrame(positionX, positionY, width, height);
}

void SetSize(NodeHandle node, float width, float height)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(width, DimensionUnit::VP), CalcLength(height, DimensionUnit::VP)));
    frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
}

void SetOpacity(NodeHandle node, float opacity)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetOpacity(opacity);
}

void SetTranslate(NodeHandle node, float translateX, float translateY, float translateZ)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetTranslate(translateX, translateY, translateZ);
}

void SetBorderStyle(NodeHandle node, BorderStyle left, BorderStyle top, BorderStyle right, BorderStyle bottom)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    BorderStyleProperty borderStyleProperty {
        .styleLeft = left,
        .styleTop = top,
        .styleRight = right,
        .styleBottom = bottom,
        .multiValued = true
    };
    renderContext->UpdateBorderStyle(borderStyleProperty);
}

void SetBorderWidth(NodeHandle node, float left, float top, float right, float bottom)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    auto* frameNode = reinterpret_cast<FrameNode*>(currentNode);
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();

    BorderWidthProperty borderWidthProperty {
        .leftDimen = Dimension(left, DimensionUnit::VP),
        .topDimen = Dimension(top, DimensionUnit::VP),
        .rightDimen = Dimension(right, DimensionUnit::VP),
        .bottomDimen = Dimension(bottom, DimensionUnit::VP),
        .multiValued = true
    };
    renderContext->UpdateBorderWidth(borderWidthProperty);
    layoutProperty->UpdateBorderWidth(borderWidthProperty);
}

void SetBorderColor(NodeHandle node, uint32_t left, uint32_t top, uint32_t right, uint32_t bottom)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    BorderColorProperty borderColorProperty {
        .leftColor = Color(left),
        .topColor = Color(top),
        .rightColor = Color(right),
        .bottomColor = Color(bottom),
        .multiValued = true
    };
    renderContext->UpdateBorderColor(borderColorProperty);
}

void SetBorderRadius(NodeHandle node, double topLeft, double topRight, double bottomLeft, double bottomRight)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    BorderRadiusProperty borderRadiusProperty(Dimension(topLeft, DimensionUnit::VP),
        Dimension(topRight, DimensionUnit::VP), Dimension(bottomRight, DimensionUnit::VP),
        Dimension(bottomLeft, DimensionUnit::VP));
    renderContext->UpdateBorderRadius(borderRadiusProperty);
}

void SetRectMask(NodeHandle node, const RectF& rect, const ShapeMaskProperty& property)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetRectMask(rect, property);
}

void SetCircleMask(NodeHandle node, const Circle& circle, const ShapeMaskProperty& property)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetCircleMask(circle, property);
}

void SetRoundRectMask(
    NodeHandle node, const RoundRect& roundRect, const ShapeMaskProperty& property)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetRoundRectMask(roundRect, property);
}

void SetOvalMask(NodeHandle node, const RectF& rect, const ShapeMaskProperty& property)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetOvalMask(rect, property);
}

void SetCommandPathMask(
    NodeHandle node, const std::string& commands, const ShapeMaskProperty& property)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetCommandPathMask(commands, property);
}

ArkUIRenderNodeModifierAPI GetRenderNodeModifier()
{
    static const ArkUIRenderNodeModifierAPI modifier = { AppendChild, InsertChildAfter, RemoveChild, ClearChildren,
        SetClipToFrame, SetRotation, SetShadowColor, SetShadowOffset, SetShadowAlpha, SetShadowElevation,
        SetShadowRadius, Invalidate, SetScale, SetRenderNodeBackgroundColor, SetPivot, SetFrame, SetSize, SetOpacity,
        SetTranslate, SetBorderStyle, SetBorderWidth, SetBorderColor, SetBorderRadius, SetRectMask, SetCircleMask,
        SetRoundRectMask, SetOvalMask, SetCommandPathMask };

    return modifier;
}
} // namespace OHOS::Ace::NG
