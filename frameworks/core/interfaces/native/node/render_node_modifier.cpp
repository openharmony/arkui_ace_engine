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

#include "core/common/builder_util.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"

namespace OHOS::Ace::NG {
namespace {
enum class LengthMetricsUnit : int32_t { DEFAULT = 0, PX };

DimensionUnit ConvertLengthMetricsUnitToDimensionUnit(int32_t unitValue, DimensionUnit defaultUnit)
{
    auto lengthMetricsUnit = static_cast<LengthMetricsUnit>(unitValue);
    switch (lengthMetricsUnit) {
        case LengthMetricsUnit::PX:
            return DimensionUnit::PX;
        default:
            return defaultUnit;
    }
    return defaultUnit;
}
} // namespace
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

void AddBuilderNode(ArkUINodeHandle node, ArkUINodeHandle child)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto* childNode = reinterpret_cast<UINode*>(child);
    CHECK_NULL_VOID(childNode);
    auto childRef = Referenced::Claim<UINode>(childNode);
    CHECK_NULL_VOID(childRef);
    auto parentNode = childRef->GetParent();
    CHECK_NULL_VOID(parentNode && parentNode == currentNode);
    std::list<RefPtr<UINode>> nodes;
    BuilderUtils::GetBuilderNodes(childRef, nodes);
    BuilderUtils::AddBuilderToParent(parentNode, nodes);
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

void RemoveBuilderNode(ArkUINodeHandle node, ArkUINodeHandle child)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto* childNode = reinterpret_cast<UINode*>(child);
    CHECK_NULL_VOID(childNode);
    auto childRef = Referenced::Claim<UINode>(childNode);
    CHECK_NULL_VOID(childRef);
    auto parentNode = childRef->GetParent();
    CHECK_NULL_VOID(parentNode && parentNode == currentNode);
    std::list<RefPtr<UINode>> nodes;
    BuilderUtils::GetBuilderNodes(childRef, nodes);
    BuilderUtils::RemoveBuilderFromParent(parentNode, nodes);
}

void RemoveChild(ArkUINodeHandle node, ArkUINodeHandle child)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* childNode = reinterpret_cast<UINode*>(child);
    currentNode->RemoveChild(Referenced::Claim<UINode>(childNode));
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

void ClearBuilderNode(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto currentRef = Referenced::Claim<UINode>(currentNode);
    std::list<RefPtr<NG::UINode>> nodes;
    CHECK_NULL_VOID(currentRef);
    for (const auto& child : currentRef->GetChildren()) {
        BuilderUtils::GetBuilderNodes(child, nodes);
    }
    BuilderUtils::RemoveBuilderFromParent(currentRef, nodes);
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

void SetRotation(ArkUINodeHandle node, ArkUI_Float32 rotationX, ArkUI_Float32 rotationY, ArkUI_Float32 rotationZ,
    ArkUI_Int32 unitValue)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    Dimension first = Dimension(rotationX, unit);
    Dimension second = Dimension(rotationY, unit);
    Dimension third = Dimension(rotationZ, unit);
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

void SetShadowOffset(ArkUINodeHandle node, ArkUI_Float32 offsetX, ArkUI_Float32 offsetY, ArkUI_Int32 unitValue)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    Dimension first = Dimension(offsetX, unit);
    Dimension second = Dimension(offsetY, unit);
    renderContext->SetShadowOffset(first.ConvertToPx(), second.ConvertToPx());
    renderContext->RequestNextFrame();
}

void SetLabel(ArkUINodeHandle node, ArkUI_CharPtr label)
{
    auto* currentNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(currentNode);
    auto pattern = currentNode->GetPattern<NG::RenderNodePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetLabel(std::string(label));
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

void SetFrame(
    ArkUINodeHandle node, ArkUI_Float32 positionX, ArkUI_Float32 positionY, ArkUI_Float32 width, ArkUI_Float32 height)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetFrame(Dimension(positionX, DimensionUnit::VP).ConvertToPx(),
        Dimension(positionY, DimensionUnit::VP).ConvertToPx(), Dimension(width, DimensionUnit::VP).ConvertToPx(),
        Dimension(height, DimensionUnit::VP).ConvertToPx());
    renderContext->RequestNextFrame();
}

void SetSize(ArkUINodeHandle node, ArkUI_Float32 width, ArkUI_Float32 height, ArkUI_Int32 unitValue)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(width, unit), CalcLength(height, unit)));
    frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
}

void SetPosition(ArkUINodeHandle node, ArkUI_Float32 xAxis, ArkUI_Float32 yAxis, ArkUI_Int32 unitValue)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    const auto& renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->ResetPosition();

    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    Dimension x = Dimension(xAxis, unit);
    Dimension y = Dimension(yAxis, unit);
    OffsetT<Dimension> value(x, y);
    renderContext->UpdatePosition(value);
    renderContext->RequestNextFrame();
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
    ArkUI_Float32 bottom, ArkUI_Int32 unitValue)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    auto* frameNode = reinterpret_cast<FrameNode*>(currentNode);
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    BorderWidthProperty borderWidthProperty {
        .leftDimen = Dimension(left, unit),
        .topDimen = Dimension(top, unit),
        .rightDimen = Dimension(right, unit),
        .bottomDimen = Dimension(bottom, unit),
        .multiValued = true
    };
    layoutProperty->UpdateBorderWidth(borderWidthProperty);
    frameNode->MarkDirtyNode();
    renderContext->SetBorderWidth(borderWidthProperty);
}

void SetBorderColor(ArkUINodeHandle node, uint32_t left, uint32_t top, uint32_t right, uint32_t bottom)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    BorderColorProperty borderColorProperty {
        .leftColor = Color(left),
        .rightColor = Color(right),
        .topColor = Color(top),
        .bottomColor = Color(bottom),
        .multiValued = true
    };
    renderContext->UpdateBorderColor(borderColorProperty);
}

void SetBorderRadius(ArkUINodeHandle node, ArkUI_Float32 topLeft, ArkUI_Float32 topRight, ArkUI_Float32 bottomLeft,
    ArkUI_Float32 bottomRight, ArkUI_Int32 unitValue)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    BorderRadiusProperty borderRadiusProperty(Dimension(topLeft, unit),
        Dimension(topRight, unit), Dimension(bottomRight, unit),
        Dimension(bottomLeft, unit));
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
    Dimension centerX(centerXValue, DimensionUnit::PX);
    circle.SetAxisX(centerX);
    Dimension centerY(centerYValue, DimensionUnit::PX);
    circle.SetAxisY(centerY);
    Dimension radius(radiusValue, DimensionUnit::PX);
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

void SetCommandPathMask(ArkUINodeHandle node, ArkUI_CharPtr commands, ArkUI_Uint32 fillColor, ArkUI_Uint32 strokeColor,
    ArkUI_Float32 strokeWidth)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    ShapeMaskProperty property { fillColor, strokeColor, strokeWidth };
    renderContext->SetCommandPathMask(std::string(commands), property);
    renderContext->RequestNextFrame();
}

void SetRectClip(
    ArkUINodeHandle node, ArkUI_Float32 rectX, ArkUI_Float32 rectY, ArkUI_Float32 rectW, ArkUI_Float32 rectH)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    RectF rect(rectX, rectY, rectW, rectH);
    renderContext->ClipWithRect(rect);
    renderContext->RequestNextFrame();
}

void SetCircleClip(
    ArkUINodeHandle node, ArkUI_Float32 centerXValue, ArkUI_Float32 centerYValue, ArkUI_Float32 radiusValue)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    Circle circle;
    Dimension centerX(centerXValue, DimensionUnit::PX);
    circle.SetAxisX(centerX);
    Dimension centerY(centerYValue, DimensionUnit::PX);
    circle.SetAxisY(centerY);
    Dimension radius(radiusValue, DimensionUnit::PX);
    circle.SetRadius(radius);

    renderContext->ClipWithCircle(circle);
    renderContext->RequestNextFrame();
}

void SetRoundRectClip(ArkUINodeHandle node, const ArkUI_Float32* roundRect, const ArkUI_Uint32 roundRectSize)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    RoundRect roundRectInstance;
    roundRectInstance.SetCornerRadius(
        RoundRect::CornerPos::TOP_LEFT_POS, roundRect[TOP_LEFT_X_VALUE], roundRect[TOP_LEFT_Y_VALUE]);
    roundRectInstance.SetCornerRadius(
        RoundRect::CornerPos::TOP_RIGHT_POS, roundRect[TOP_RIGHT_X_VALUE], roundRect[TOP_RIGHT_Y_VALUE]);
    roundRectInstance.SetCornerRadius(
        RoundRect::CornerPos::BOTTOM_LEFT_POS, roundRect[BOTTOM_LEFT_X_VALUE], roundRect[BOTTOM_LEFT_Y_VALUE]);
    roundRectInstance.SetCornerRadius(
        RoundRect::CornerPos::BOTTOM_RIGHT_POS, roundRect[BOTTOM_RIGHT_X_VALUE], roundRect[BOTTOM_RIGHT_Y_VALUE]);

    RectF rect(roundRect[LEFT_VALUE], roundRect[TOP_VALUE], roundRect[WIDTH_VALUE], roundRect[HEIGHT_VALUE]);
    roundRectInstance.SetRect(rect);

    renderContext->ClipWithRoundRect(roundRectInstance);
    renderContext->RequestNextFrame();
}

void SetOvalClip(
    ArkUINodeHandle node, ArkUI_Float32 rectX, ArkUI_Float32 rectY, ArkUI_Float32 rectW, ArkUI_Float32 rectH)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    RectF rect(rectX, rectY, rectW, rectH);
    renderContext->ClipWithOval(rect);
    renderContext->RequestNextFrame();
}

void SetCommandPathClip(ArkUINodeHandle node, ArkUI_CharPtr commands)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    renderContext->SetClipBoundsWithCommands(std::string(commands));
    renderContext->RequestNextFrame();
}

void SetMarkNodeGroup(ArkUINodeHandle node, ArkUI_Bool isNodeGroup)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    renderContext->SetMarkNodeGroup(isNodeGroup);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    if (frameNode) {
        frameNode->SetApplicationRenderGroupMarked(true);
    }
    renderContext->RequestNextFrame();
}

void SetTransformScale(ArkUINodeHandle node, ArkUI_Float32 xF, ArkUI_Float32 yF)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);

    VectorF scaleValue = VectorF(xF, yF);
    renderContext->UpdateTransformScale(scaleValue);
    renderContext->RequestNextFrame();
}

ArkUI_CharPtr GetNodeTypeInRenderNode(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, "");
    return currentNode->GetTag().c_str();
}

namespace NodeModifier {
const ArkUIRenderNodeModifier* GetRenderNodeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIRenderNodeModifier modifier = {
        .addBuilderNode = AddBuilderNode,
        .appendChild = AppendChild,
        .insertChildAfter = InsertChildAfter,
        .removeBuilderNode = RemoveBuilderNode,
        .removeChild = RemoveChild,
        .clearBuilderNode = ClearBuilderNode,
        .clearChildren = ClearChildren,
        .setClipToFrame = SetClipToFrame,
        .setRotation = SetRotation,
        .setShadowColor = SetShadowColor,
        .setShadowOffset = SetShadowOffset,
        .setLabel = SetLabel,
        .setShadowAlpha = SetShadowAlpha,
        .setShadowElevation = SetShadowElevation,
        .setShadowRadius = SetShadowRadius,
        .invalidate = Invalidate,
        .setScale = SetScale,
        .setRenderNodeBackgroundColor = SetRenderNodeBackgroundColor,
        .setPivot = SetPivot,
        .setFrame = SetFrame,
        .setSize = SetSize,
        .setOpacity = SetOpacity,
        .setTranslate = SetTranslate,
        .setBorderStyle = SetBorderStyle,
        .setBorderWidth = SetBorderWidth,
        .setBorderColor = SetBorderColor,
        .setBorderRadius = SetBorderRadius,
        .setRectMask = SetRectMask,
        .setCircleMask = SetCircleMask,
        .setRoundRectMask = SetRoundRectMask,
        .setOvalMask = SetOvalMask,
        .setCommandPathMask = SetCommandPathMask,
        .setRectClip = SetRectClip,
        .setCircleClip = SetCircleClip,
        .setRoundRectClip = SetRoundRectClip,
        .setOvalClip = SetOvalClip,
        .setCommandPathClip = SetCommandPathClip,
        .setPosition = SetPosition,
        .setMarkNodeGroup = SetMarkNodeGroup,
        .setTransformScale = SetTransformScale,
        .getNodeType = GetNodeTypeInRenderNode,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIRenderNodeModifier* GetCJUIRenderNodeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIRenderNodeModifier modifier = {
        .appendChild = AppendChild,
        .insertChildAfter = InsertChildAfter,
        .removeChild = RemoveChild,
        .clearChildren = ClearChildren,
        .setClipToFrame = SetClipToFrame,
        .setRotation = SetRotation,
        .setShadowColor = SetShadowColor,
        .setShadowOffset = SetShadowOffset,
        .setShadowAlpha = SetShadowAlpha,
        .setShadowElevation = SetShadowElevation,
        .setShadowRadius = SetShadowRadius,
        .invalidate = Invalidate,
        .setScale = SetScale,
        .setRenderNodeBackgroundColor = SetRenderNodeBackgroundColor,
        .setPivot = SetPivot,
        .setFrame = SetFrame,
        .setSize = SetSize,
        .setOpacity = SetOpacity,
        .setTranslate = SetTranslate,
        .setBorderStyle = SetBorderStyle,
        .setBorderWidth = SetBorderWidth,
        .setBorderColor = SetBorderColor,
        .setBorderRadius = SetBorderRadius,
        .setRectMask = SetRectMask,
        .setCircleMask = SetCircleMask,
        .setRoundRectMask = SetRoundRectMask,
        .setOvalMask = SetOvalMask,
        .setCommandPathMask = SetCommandPathMask,
        .setPosition = SetPosition,
        .setMarkNodeGroup = SetMarkNodeGroup,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
