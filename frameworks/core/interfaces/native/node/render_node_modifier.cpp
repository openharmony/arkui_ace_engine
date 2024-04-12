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

namespace OHOS::Ace::NG {
constexpr int TOP_LEFT_X_VALUE = 0;
constexpr int TOP_LEFT_Y_VALUE = 1;
constexpr int TOP_RIGHT_X_VALUE = 2;
constexpr int TOP_RIGHT_Y_VALUE = 3;
constexpr int BOTTOM_LEFT_X_VALUE = 4;
constexpr int BOTTOM_LEFT_Y_VALUE = 5;
constexpr int BOTTOM_RIGHT_X_VALUE = 6;
constexpr int BOTTOM_RIGHT_Y_VALUE = 7;
constexpr int LEFT_VALUE = 8;
constexpr int TOP_VALUE = 9;
constexpr int WIDTH_VALUE = 10;
constexpr int HEIGHT_VALUE = 11;

RefPtr<RenderContext> GetRenderContext(UINode* node)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    CHECK_NULL_RETURN(node->GetTag() != "BuilderProxyNode", nullptr);
    auto context = frameNode->GetRenderContext();
    return context;
}

void AppendChild(ArkUINodeHandle node, ArkUINodeHandle child)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* childNode = reinterpret_cast<UINode*>(child);
    auto childRef = Referenced::Claim<UINode>(childNode);
    currentNode->AddChild(childRef);
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

void InsertChildAfter(ArkUINodeHandle node, ArkUINodeHandle child, ArkUINodeHandle sibling)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* childNode = reinterpret_cast<UINode*>(child);
    auto index = -1;
    auto* siblingNode = reinterpret_cast<UINode*>(sibling);
    index = currentNode->GetChildIndex(Referenced::Claim<UINode>(siblingNode));
    currentNode->AddChild(Referenced::Claim<UINode>(childNode), index + 1);
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

void RemoveChild(ArkUINodeHandle node, ArkUINodeHandle child)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* childNode = reinterpret_cast<UINode*>(child);
    currentNode->RemoveChild(Referenced::Claim<UINode>(childNode));
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

void ClearChildren(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    currentNode->Clean();
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

void SetClipToFrame(ArkUINodeHandle node, ArkUI_Bool useClip)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetClipToFrame(useClip);
    renderContext->RequestNextFrame();
}

void SetRotation(ArkUINodeHandle node, ArkUI_Float32 rotationX, ArkUI_Float32 rotationY, ArkUI_Float32 rotationZ)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    Dimension first = Dimension(rotationX, DimensionUnit::VP);
    Dimension second = Dimension(rotationY, DimensionUnit::VP);
    Dimension third = Dimension(rotationZ, DimensionUnit::VP);
    renderContext->SetRotation(first.ConvertToPx(), second.ConvertToPx(), third.ConvertToPx());
    renderContext->RequestNextFrame();
}

void SetShadowColor(ArkUINodeHandle node, uint32_t color)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowColor(color);
    renderContext->RequestNextFrame();
}

void SetShadowOffset(ArkUINodeHandle node, ArkUI_Float32 offsetX, ArkUI_Float32 offsetY)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    Dimension first = Dimension(offsetX, DimensionUnit::VP);
    Dimension second = Dimension(offsetY, DimensionUnit::VP);
    renderContext->SetShadowOffset(first.ConvertToPx(), second.ConvertToPx());
    renderContext->RequestNextFrame();
}

void SetShadowAlpha(ArkUINodeHandle node, ArkUI_Float32 alpha)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowAlpha(alpha);
    renderContext->RequestNextFrame();
}

void SetShadowElevation(ArkUINodeHandle node, ArkUI_Float32 elevation)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowElevation(elevation);
    renderContext->RequestNextFrame();
}

void SetShadowRadius(ArkUINodeHandle node, ArkUI_Float32 radius)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowRadius(radius);
    renderContext->RequestNextFrame();
}

void Invalidate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RenderNodePattern>();
    CHECK_NULL_VOID(pattern);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    pattern->Invalidate();
    renderContext->RequestNextFrame();
}

void SetScale(ArkUINodeHandle node, ArkUI_Float32 scaleX, ArkUI_Float32 scaleY)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetScale(scaleX, scaleY);
    renderContext->RequestNextFrame();
}

void SetRenderNodeBackgroundColor(ArkUINodeHandle node, uint32_t colorValue)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetBackgroundColor(colorValue);
    renderContext->RequestNextFrame();
}

void SetPivot(ArkUINodeHandle node, ArkUI_Float32 pivotX, ArkUI_Float32 pivotY)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetRenderPivot(pivotX, pivotY);
    renderContext->RequestNextFrame();
}

void SetFrame(ArkUINodeHandle node, ArkUI_Float32 positionX, ArkUI_Float32 positionY,
    ArkUI_Float32 width, ArkUI_Float32 height)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetFrame(positionX, positionY, width, height);
    renderContext->RequestNextFrame();
}

void SetSize(ArkUINodeHandle node, ArkUI_Float32 width, ArkUI_Float32 height)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(width, DimensionUnit::VP), CalcLength(height, DimensionUnit::VP)));
    frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
}

void SetOpacity(ArkUINodeHandle node, ArkUI_Float32 opacity)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetOpacity(opacity);
    renderContext->RequestNextFrame();
}

void SetTranslate(ArkUINodeHandle node, ArkUI_Float32 translateX, ArkUI_Float32 translateY, ArkUI_Float32 translateZ)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetTranslate(translateX, translateY, translateZ);
    renderContext->RequestNextFrame();
}

void SetBorderStyle(ArkUINodeHandle node, ArkUI_Int32 left, ArkUI_Int32 top, ArkUI_Int32 right, ArkUI_Int32 bottom)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    BorderStyleProperty borderStyleProperty {
        .styleLeft = static_cast<BorderStyle>(left),
        .styleRight = static_cast<BorderStyle>(right),
        .styleTop = static_cast<BorderStyle>(top),
        .styleBottom = static_cast<BorderStyle>(bottom),
        .multiValued = true
    };
    renderContext->UpdateBorderStyle(borderStyleProperty);
}

void SetBorderWidth(ArkUINodeHandle node, ArkUI_Float32 left, ArkUI_Float32 top, ArkUI_Float32 right,
    ArkUI_Float32 bottom)
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

void SetBorderColor(ArkUINodeHandle node, uint32_t left, uint32_t top, uint32_t right, uint32_t bottom)
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

void SetBorderRadius(ArkUINodeHandle node,
    ArkUI_Float32 topLeft, ArkUI_Float32 topRight, ArkUI_Float32 bottomLeft, ArkUI_Float32 bottomRight)
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

void SetRectMask(ArkUINodeHandle node,
    ArkUI_Float32 rectX, ArkUI_Float32 rectY, ArkUI_Float32 rectW, ArkUI_Float32 rectH,
    ArkUI_Uint32 fillColor, ArkUI_Uint32 strokeColor, ArkUI_Float32 strokeWidth)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    RectF rect(rectX, rectY, rectW, rectH);
    ShapeMaskProperty property { fillColor, strokeColor, strokeWidth };
    renderContext->SetRectMask(rect, property);
    renderContext->RequestNextFrame();
}

void SetCircleMask(ArkUINodeHandle node,
    ArkUI_Float32 centerXValue, ArkUI_Float32 centerYValue, ArkUI_Float32 radiusValue,
    ArkUI_Uint32 fillColor, ArkUI_Uint32 strokeColor, ArkUI_Float32 strokeWidth)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    Circle circle;
    Dimension centerX(centerXValue, DimensionUnit::VP);
    circle.SetAxisX(centerX);
    Dimension centerY(centerYValue, DimensionUnit::VP);
    circle.SetAxisY(centerY);
    Dimension radius(radiusValue, DimensionUnit::VP);
    circle.SetRadius(radius);

    ShapeMaskProperty property { fillColor, strokeColor, strokeWidth };

    renderContext->SetCircleMask(circle, property);
    renderContext->RequestNextFrame();
}

void SetRoundRectMask(ArkUINodeHandle node, const ArkUI_Float32* roundRect, const ArkUI_Uint32 roundRectSize,
    ArkUI_Uint32 fillColor, ArkUI_Uint32 strokeColor, ArkUI_Float32 strokeWidth)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    RoundRect roundRectInstance;
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS,
        roundRect[TOP_LEFT_X_VALUE], roundRect[TOP_LEFT_Y_VALUE]);
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS,
        roundRect[TOP_RIGHT_X_VALUE], roundRect[TOP_RIGHT_Y_VALUE]);
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS,
        roundRect[BOTTOM_LEFT_X_VALUE], roundRect[BOTTOM_LEFT_Y_VALUE]);
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS,
        roundRect[BOTTOM_RIGHT_X_VALUE], roundRect[BOTTOM_RIGHT_Y_VALUE]);

    RectF rect(roundRect[LEFT_VALUE], roundRect[TOP_VALUE], roundRect[WIDTH_VALUE], roundRect[HEIGHT_VALUE]);
    roundRectInstance.SetRect(rect);

    ShapeMaskProperty property { fillColor, strokeColor, strokeWidth };

    renderContext->SetRoundRectMask(roundRectInstance, property);
    renderContext->RequestNextFrame();
}

void SetOvalMask(ArkUINodeHandle node,
    ArkUI_Float32 rectX, ArkUI_Float32 rectY, ArkUI_Float32 rectW, ArkUI_Float32 rectH,
    ArkUI_Uint32 fillColor, ArkUI_Uint32 strokeColor, ArkUI_Float32 strokeWidth)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    RectF rect(rectX, rectY, rectW, rectH);
    ShapeMaskProperty property { fillColor, strokeColor, strokeWidth };
    renderContext->SetOvalMask(rect, property);
    renderContext->RequestNextFrame();
}

void SetCommandPathMask(
    ArkUINodeHandle node, ArkUI_CharPtr commands,
    ArkUI_Uint32 fillColor, ArkUI_Uint32 strokeColor, ArkUI_Float32 strokeWidth)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    ShapeMaskProperty property { fillColor, strokeColor, strokeWidth };
    renderContext->SetCommandPathMask(std::string(commands), property);
    renderContext->RequestNextFrame();
}

namespace NodeModifier {
const ArkUIRenderNodeModifier* GetRenderNodeModifier()
{
    static const ArkUIRenderNodeModifier modifier = { AppendChild, InsertChildAfter, RemoveChild, ClearChildren,
        SetClipToFrame, SetRotation, SetShadowColor, SetShadowOffset, SetShadowAlpha, SetShadowElevation,
        SetShadowRadius, Invalidate, SetScale, SetRenderNodeBackgroundColor, SetPivot, SetFrame, SetSize, SetOpacity,
        SetTranslate, SetBorderStyle, SetBorderWidth, SetBorderColor, SetBorderRadius, SetRectMask, SetCircleMask,
        SetRoundRectMask, SetOvalMask, SetCommandPathMask };

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
