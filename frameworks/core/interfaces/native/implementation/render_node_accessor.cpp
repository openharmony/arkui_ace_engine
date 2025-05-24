/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdint>
#include <optional>

#include "arkoala_api_generated.h"
#include "ui/base/utils/utils.h"

#include "bridge/arkts_frontend/arkts_frontend.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/interfaces/native/implementation/render_node_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/components_ng/base/view_abstract_model_static.h"

namespace OHOS::Ace::NG {
namespace GeneratedModifier {
namespace {
constexpr int32_t ARK_UNION_UNDEFINED = 1;
enum class LengthMetricsUnit : int32_t { DEFAULT = 0, PX };

DimensionUnit ConvertLengthMetricsUnitToDimensionUnit(Ark_Int32 unitValue, DimensionUnit defaultUnit)
{
    auto unit = Converter::Convert<int32_t>(unitValue);
    auto lengthMetricsUnit = static_cast<LengthMetricsUnit>(unit);
    switch (lengthMetricsUnit) {
        case LengthMetricsUnit::PX:
            return DimensionUnit::PX;
        default:
            return defaultUnit;
    }
    return defaultUnit;
}
} // namespace
namespace RenderNodeAccessor {
void DestroyPeerImpl(Ark_RenderNode peer) {}
Ark_RenderNode CtorImpl(Ark_Int32 nodeId, const DrawCallbackFunc* value)
{
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode(
        V2::RENDER_NODE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NG::RenderNodePattern>(); });
    frameNode->SetIsArkTsRenderNode(true);
    auto renderNodePeer = RenderNodePeer::Create(frameNode);
    return renderNodePeer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeerImpl);
}
void AppendChildImpl(Ark_RenderNode peer, Ark_RenderNode node)
{
    if (!peer || !node) {
        LOGW("This renderNode or child is nullptr when appendChild !");
        return;
    }
    auto parent = peer->GetFrameNode();
    auto child = node->GetFrameNode();
    if (parent && child) {
        parent->AddChild(child);
        parent->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
    }
}
void InsertChildAfterImpl(Ark_RenderNode peer, Ark_RenderNode child, const Ark_Union_RenderNode_Undefined* sibling)
{
    if (!peer || !child) {
        LOGW("This renderNode or child is nullptr when InsertChildAfter !");
        return;
    }
    if (!sibling || sibling->selector == ARK_UNION_UNDEFINED || !sibling->value0) {
        LOGW("Sibling node is nullptr or undefined when InsertChildAfter !");
        return;
    }
    auto currentNode = peer->GetFrameNode();
    auto childNode = child->GetFrameNode();
    auto siblingNode = sibling->value0->GetFrameNode();
    auto index = currentNode->GetChildIndex(siblingNode);
    currentNode->AddChild(childNode, index + 1);
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void RemoveChildImpl(Ark_RenderNode peer, Ark_RenderNode node)
{
    if (!peer || !node) {
        LOGW("This renderNode or child is nullptr when RemoveChild !");
        return;
    }
    auto currentNode = peer->GetFrameNode();
    auto childNode = node->GetFrameNode();
    if (currentNode && childNode) {
        currentNode->RemoveChild(childNode);
        currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
    }
}
void ClearChildrenImpl(Ark_RenderNode peer)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when ClearChildren !");
        return;
    }
    auto currentNode = peer->GetFrameNode();
    if (currentNode) {
        currentNode->Clean();
        currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
    }
}
Ark_Union_RenderNode_Undefined GetChildImpl(Ark_RenderNode peer, const Ark_Number* index)
{
    return {};
}
Ark_Union_RenderNode_Undefined GetFirstChildImpl(Ark_RenderNode peer)
{
    return {};
}
Ark_Union_RenderNode_Undefined GetNextSiblingImpl(Ark_RenderNode peer)
{
    return {};
}
Ark_Union_RenderNode_Undefined GetPreviousSiblingImpl(Ark_RenderNode peer)
{
    return {};
}
void DrawImpl(Ark_RenderNode peer, const Ark_DrawContext* context) {}
void InvalidateImpl(Ark_RenderNode peer)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when Invalidate !");
        return;
    }
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RenderNodePattern>();
    CHECK_NULL_VOID(pattern);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    pattern->Invalidate();
    renderContext->RequestNextFrame();
}
void DisposeImpl(Ark_RenderNode peer) {}
Ark_Number GetBackgroundColorImpl(Ark_RenderNode peer)
{
    return {};
}
void SetRectMaskImpl(Ark_RenderNode peer, const Ark_Rect* rect, const Ark_Number* fillColor,
    const Ark_Number* strokeColor, const Ark_Number* strokeWidth)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetRectMask !");
        return;
    }
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto left = Converter::Convert<float>(rect->left);
    auto top = Converter::Convert<float>(rect->top);
    auto right = Converter::Convert<float>(rect->right);
    auto bottom = Converter::Convert<float>(rect->bottom);
    RectF rectF(left, top, right - left, bottom - top);
    ShapeMaskProperty property { Converter::Convert<uint32_t>(*fillColor), Converter::Convert<uint32_t>(*strokeColor),
        Converter::Convert<float>(*strokeWidth) };
    renderContext->SetRectMask(rectF, property);
    renderContext->RequestNextFrame();
}
void SetCircleMaskImpl(Ark_RenderNode peer, const Ark_Circle* circle, const Ark_Number* fillColor,
    const Ark_Number* strokeColor, const Ark_Number* strokeWidth)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetCircleMask !");
        return;
    }
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto centerXValue = Converter::Convert<float>(circle->centerX);
    auto centerYValue = Converter::Convert<float>(circle->centerY);
    auto radiusValue = Converter::Convert<float>(circle->radius);

    Circle circleValue;
    Dimension centerX(centerXValue, DimensionUnit::PX);
    circleValue.SetAxisX(centerX);
    Dimension centerY(centerYValue, DimensionUnit::PX);
    circleValue.SetAxisY(centerY);
    Dimension radius(radiusValue, DimensionUnit::PX);
    circleValue.SetRadius(radius);

    ShapeMaskProperty property { Converter::Convert<uint32_t>(*fillColor), Converter::Convert<uint32_t>(*strokeColor),
        Converter::Convert<float>(*strokeWidth) };

    renderContext->SetCircleMask(circleValue, property);
    renderContext->RequestNextFrame();
}
void SetRoundRectMaskImpl(Ark_RenderNode peer, const Ark_RoundRect* roundRect, const Ark_Number* fillColor,
    const Ark_Number* strokeColor, const Ark_Number* strokeWidth)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetRoundRectMask !");
        return;
    }
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto rect = roundRect->rect;
    auto corners = roundRect->corners;

    RoundRect roundRectInstance;
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, Converter::Convert<float>(corners.topLeft.x),
        Converter::Convert<float>(corners.topLeft.y));
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS,
        Converter::Convert<float>(corners.topRight.x), Converter::Convert<float>(corners.topRight.y));
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS,
        Converter::Convert<float>(corners.bottomLeft.x), Converter::Convert<float>(corners.bottomLeft.y));
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS,
        Converter::Convert<float>(corners.bottomRight.x), Converter::Convert<float>(corners.bottomRight.y));

    auto left = Converter::Convert<float>(rect.left);
    auto top = Converter::Convert<float>(rect.top);
    auto right = Converter::Convert<float>(rect.right);
    auto bottom = Converter::Convert<float>(rect.bottom);
    RectF rectValue(left, top, right - left, bottom - top);
    roundRectInstance.SetRect(rectValue);

    ShapeMaskProperty property { Converter::Convert<uint32_t>(*fillColor), Converter::Convert<uint32_t>(*strokeColor),
        Converter::Convert<float>(*strokeWidth) };

    renderContext->SetRoundRectMask(roundRectInstance, property);
    renderContext->RequestNextFrame();
}
void SetOvalMaskImpl(Ark_RenderNode peer, const Ark_Rect* rect, const Ark_Number* fillColor,
    const Ark_Number* strokeColor, const Ark_Number* strokeWidth)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetOvalMask !");
        return;
    }
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto left = Converter::Convert<float>(rect->left);
    auto top = Converter::Convert<float>(rect->top);
    auto right = Converter::Convert<float>(rect->right);
    auto bottom = Converter::Convert<float>(rect->bottom);
    RectF rectValue(left, top, right - left, bottom - top);

    ShapeMaskProperty property { Converter::Convert<uint32_t>(*fillColor), Converter::Convert<uint32_t>(*strokeColor),
        Converter::Convert<float>(*strokeWidth) };

    renderContext->SetOvalMask(rectValue, property);
    renderContext->RequestNextFrame();
}
void SetPathImpl(Ark_RenderNode peer, const Ark_CommandPath* path, const Ark_Number* fillColor,
    const Ark_Number* strokeColor, const Ark_Number* strokeWidth)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetPath !");
        return;
    }
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto pathValue = Converter::Convert<std::string>(*path);

    ShapeMaskProperty property { Converter::Convert<uint32_t>(*fillColor), Converter::Convert<uint32_t>(*strokeColor),
        Converter::Convert<float>(*strokeWidth) };

    renderContext->SetCommandPathMask(pathValue, property);
    renderContext->RequestNextFrame();
}
void SetRectClipImpl(Ark_RenderNode peer, const Ark_Rect* rect)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetRectClip !");
        return;
    }
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto left = Converter::Convert<float>(rect->left);
    auto top = Converter::Convert<float>(rect->top);
    auto right = Converter::Convert<float>(rect->right);
    auto bottom = Converter::Convert<float>(rect->bottom);
    RectF rectValue(left, top, right - left, bottom - top);

    renderContext->ClipWithRect(rectValue);
    renderContext->RequestNextFrame();
}
void SetCircleClipImpl(Ark_RenderNode peer, const Ark_Circle* circle)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetCircleClip !");
        return;
    }
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto centerXValue = Converter::Convert<float>(circle->centerX);
    auto centerYValue = Converter::Convert<float>(circle->centerY);
    auto radiusValue = Converter::Convert<float>(circle->radius);

    Circle circleValue;
    Dimension centerX(centerXValue, DimensionUnit::PX);
    circleValue.SetAxisX(centerX);
    Dimension centerY(centerYValue, DimensionUnit::PX);
    circleValue.SetAxisY(centerY);
    Dimension radius(radiusValue, DimensionUnit::PX);
    circleValue.SetRadius(radius);

    renderContext->ClipWithCircle(circleValue);
    renderContext->RequestNextFrame();
}
void SetRoundRectClipImpl(Ark_RenderNode peer, const Ark_RoundRect* roundRect)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetRoundRectClip !");
        return;
    }
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto rect = roundRect->rect;
    auto corners = roundRect->corners;

    RoundRect roundRectInstance;
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, Converter::Convert<float>(corners.topLeft.x),
        Converter::Convert<float>(corners.topLeft.y));
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS,
        Converter::Convert<float>(corners.topRight.x), Converter::Convert<float>(corners.topRight.y));
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS,
        Converter::Convert<float>(corners.bottomLeft.x), Converter::Convert<float>(corners.bottomLeft.y));
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS,
        Converter::Convert<float>(corners.bottomRight.x), Converter::Convert<float>(corners.bottomRight.y));

    auto left = Converter::Convert<float>(rect.left);
    auto top = Converter::Convert<float>(rect.top);
    auto right = Converter::Convert<float>(rect.right);
    auto bottom = Converter::Convert<float>(rect.bottom);
    RectF rectValue(left, top, right - left, bottom - top);
    roundRectInstance.SetRect(rectValue);

    renderContext->ClipWithRoundRect(roundRectInstance);
    renderContext->RequestNextFrame();
}
void SetOvalClipImpl(Ark_RenderNode peer, const Ark_Rect* rect)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetOvalClip !");
        return;
    }
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto left = Converter::Convert<float>(rect->left);
    auto top = Converter::Convert<float>(rect->top);
    auto right = Converter::Convert<float>(rect->right);
    auto bottom = Converter::Convert<float>(rect->bottom);
    RectF rectValue(left, top, right - left, bottom - top);

    renderContext->ClipWithOval(rectValue);
    renderContext->RequestNextFrame();
}
void SetPathClipImpl(Ark_RenderNode peer, const Ark_CommandPath* path)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetPathClip !");
        return;
    }
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto pathValue = Converter::Convert<std::string>(*path);

    renderContext->SetClipBoundsWithCommands(pathValue);
    renderContext->RequestNextFrame();
}
void SetBackgroundColorImpl(Ark_RenderNode peer, const Ark_Number* backgroundColor)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetBackgroundColor !");
        return;
    }
    auto colorValue = Converter::Convert<uint32_t>(*backgroundColor);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetBackgroundColor(colorValue);
    renderContext->RequestNextFrame();
}
Ark_Boolean GetClipToFrameImpl(Ark_RenderNode peer)
{
    return {};
}
void SetClipToFrameImpl(Ark_RenderNode peer, Ark_Boolean clipToFrame)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetClipToFrame !");
        return;
    }
    auto useClip = Converter::Convert<bool>(clipToFrame);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetClipToFrame(useClip);
    renderContext->RequestNextFrame();
}
Ark_Number GetOpacityImpl(Ark_RenderNode peer)
{
    return {};
}
void SetOpacityImpl(Ark_RenderNode peer, const Ark_Number* opacity)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetOpacity !");
        return;
    }
    auto opacityValue = Converter::Convert<float>(*opacity);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetOpacity(opacityValue);
    renderContext->RequestNextFrame();
}
Ark_Size GetSizeImpl(Ark_RenderNode peer)
{
    return {};
}
void SetSizeImpl(Ark_RenderNode peer, const Ark_Size* size, const Ark_Int32 unitValue)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetSize !");
        return;
    }
    auto widthValue = Converter::Convert<float>(size->width);
    auto heightValue = Converter::Convert<float>(size->height);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(widthValue, unit), CalcLength(heightValue, unit)));
    frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
}
Ark_Position GetPositionImpl(Ark_RenderNode peer)
{
    return {};
}
void SetPositionImpl(Ark_RenderNode peer, const Ark_Position* position, const Ark_Int32 unitValue)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetPosition !");
        return;
    }
    auto xValue = Converter::Convert<Dimension>(position->x.value);
    auto yValue = Converter::Convert<Dimension>(position->y.value);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    const auto& renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->ResetPosition();

    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    Dimension x = Dimension(xValue.Value(), unit);
    Dimension y = Dimension(yValue.Value(), unit);
    OffsetT<Dimension> value(x, y);
    renderContext->UpdatePosition(value);
    renderContext->RequestNextFrame();
}
Ark_Frame GetFrameImpl(Ark_RenderNode peer)
{
    return {};
}
void SetFrameImpl(Ark_RenderNode peer, const Ark_Frame* frame)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetFrame !");
        return;
    }
    auto positionX = Converter::Convert<float>(frame->x);
    auto positionY = Converter::Convert<float>(frame->y);
    auto width = Converter::Convert<float>(frame->width);
    auto height = Converter::Convert<float>(frame->height);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    const auto& renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetFrame(Dimension(positionX, DimensionUnit::VP).ConvertToPx(),
        Dimension(positionY, DimensionUnit::VP).ConvertToPx(), Dimension(width, DimensionUnit::VP).ConvertToPx(),
        Dimension(height, DimensionUnit::VP).ConvertToPx());
    renderContext->RequestNextFrame();
}
Ark_Vector2 GetPivotImpl(Ark_RenderNode peer)
{
    return {};
}
void SetPivotImpl(Ark_RenderNode peer, const Ark_Vector2* pivot)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetPivot !");
        return;
    }
    auto pivotX = Converter::Convert<float>(pivot->x);
    auto pivotY = Converter::Convert<float>(pivot->y);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    const auto& renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetRenderPivot(pivotX, pivotY);
    renderContext->RequestNextFrame();
}
Ark_Vector2 GetScaleImpl(Ark_RenderNode peer)
{
    return {};
}
void SetScaleImpl(Ark_RenderNode peer, const Ark_Vector2* scale)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetScale !");
        return;
    }
    auto scaleX = Converter::Convert<float>(scale->x);
    auto scaleY = Converter::Convert<float>(scale->y);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    const auto& renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetScale(scaleX, scaleY);
    renderContext->RequestNextFrame();
}
Ark_Vector2 GetTranslationImpl(Ark_RenderNode peer)
{
    return {};
}
void SetTranslationImpl(Ark_RenderNode peer, const Ark_Vector2* translation)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetTranslation !");
        return;
    }
    auto translationX = Converter::Convert<float>(translation->x);
    auto translationY = Converter::Convert<float>(translation->y);
    float translateZ = 0.0f;

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    const auto& renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetTranslate(translationX, translationY, translateZ);
    renderContext->RequestNextFrame();
}
Ark_Vector3 GetRotationImpl(Ark_RenderNode peer)
{
    return {};
}
void SetRotationImpl(Ark_RenderNode peer, const Ark_Vector3* rotation, const Ark_Int32 unitValue)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetRotation !");
        return;
    }
    auto rotationX = Converter::Convert<float>(rotation->x);
    auto rotationY = Converter::Convert<float>(rotation->y);
    auto rotationZ = Converter::Convert<float>(rotation->z);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    const auto& renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    Dimension first = Dimension(rotationX, unit);
    Dimension second = Dimension(rotationY, unit);
    Dimension third = Dimension(rotationZ, unit);
    renderContext->SetRotation(first.ConvertToPx(), second.ConvertToPx(), third.ConvertToPx());
    renderContext->RequestNextFrame();
}
Ark_Matrix4 GetTransformImpl(Ark_RenderNode peer)
{
    return {};
}
void SetTransformImpl(Ark_RenderNode peer, const Ark_Matrix4* transform)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetTransform !");
        return;
    }
    auto value0 = Converter::Convert<float>(transform->value0);
    auto value1 = Converter::Convert<float>(transform->value1);
    auto value2 = Converter::Convert<float>(transform->value2);
    auto value3 = Converter::Convert<float>(transform->value3);
    auto value4 = Converter::Convert<float>(transform->value4);
    auto value5 = Converter::Convert<float>(transform->value5);
    auto value6 = Converter::Convert<float>(transform->value6);
    auto value7 = Converter::Convert<float>(transform->value7);
    auto value8 = Converter::Convert<float>(transform->value8);
    auto value9 = Converter::Convert<float>(transform->value9);
    auto value10 = Converter::Convert<float>(transform->value10);
    auto value11 = Converter::Convert<float>(transform->value11);
    auto value12 = Converter::Convert<float>(transform->value12);
    auto value13 = Converter::Convert<float>(transform->value13);
    auto value14 = Converter::Convert<float>(transform->value14);
    auto value15 = Converter::Convert<float>(transform->value15);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto matrix4 = std::make_optional<Matrix4>(value0, value4, value8, value12, value1, value5, value9, value13, value2,
        value6, value10, value14, value3, value7, value11, value15);
    NG::ViewAbstractModelStatic::SetTransformMatrix(AceType::RawPtr(frameNode), matrix4);
}
Ark_Number GetShadowColorImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowColorImpl(Ark_RenderNode peer, const Ark_Number* shadowColor)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetShadowColor !");
        return;
    }
    auto colorValue = Converter::Convert<uint32_t>(*shadowColor);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowColor(colorValue);
    renderContext->RequestNextFrame();
}
Ark_Vector2 GetShadowOffsetImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowOffsetImpl(Ark_RenderNode peer, const Ark_Vector2* shadowOffset, const Ark_Int32 unitValue)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetShadowOffset !");
        return;
    }
    auto offsetX = Converter::Convert<float>(shadowOffset->x);
    auto offsetY = Converter::Convert<float>(shadowOffset->y);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    const auto& renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    Dimension first = Dimension(offsetX, unit);
    Dimension second = Dimension(offsetY, unit);
    renderContext->SetShadowOffset(first.ConvertToPx(), second.ConvertToPx());
    renderContext->RequestNextFrame();
}
Ark_String GetLabelImpl(Ark_RenderNode peer)
{
    return {};
}
void SetLabelImpl(Ark_RenderNode peer, const Ark_String* label)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetLabel !");
        return;
    }
    auto labelValue = Converter::Convert<std::string>(*label);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<NG::RenderNodePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetLabel(std::string(labelValue));
}
Ark_Number GetShadowAlphaImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowAlphaImpl(Ark_RenderNode peer, const Ark_Number* shadowAlpha)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetShadowAlpha !");
        return;
    }
    auto alphaValue = Converter::Convert<float>(*shadowAlpha);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowAlpha(alphaValue);
    renderContext->RequestNextFrame();
}
Ark_Number GetShadowElevationImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowElevationImpl(Ark_RenderNode peer, const Ark_Number* shadowElevation)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetShadowElevation !");
        return;
    }
    auto elevationValue = Converter::Convert<float>(*shadowElevation);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowElevation(elevationValue);
    renderContext->RequestNextFrame();
}
Ark_Number GetShadowRadiusImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowRadiusImpl(Ark_RenderNode peer, const Ark_Number* shadowRadius)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetShadowRadius !");
        return;
    }
    auto radiusValue = Converter::Convert<float>(*shadowRadius);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowRadius(radiusValue);
    renderContext->RequestNextFrame();
}
Ark_EdgeStyles GetBorderStyleImpl(Ark_RenderNode peer)
{
    return {};
}
void SetBorderStyleImpl(Ark_RenderNode peer, const Ark_EdgeStyles* borderStyle)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetBorderStyle !");
        return;
    }
    auto left = borderStyle->left.value;
    auto right = borderStyle->right.value;
    auto top = borderStyle->top.value;
    auto bottom = borderStyle->bottom.value;

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto borderStyleProperty = Converter::Convert<BorderStyleProperty>(*borderStyle);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderStyle, borderStyleProperty, frameNode);
}
Ark_EdgesNumber GetBorderWidthImpl(Ark_RenderNode peer)
{
    return {};
}
void SetBorderWidthImpl(Ark_RenderNode peer, const Ark_EdgesNumber* borderWidth, const Ark_Int32 unitValue)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetBorderWidth !");
        return;
    }
    auto left = Converter::Convert<Dimension>(borderWidth->left.value);
    auto right = Converter::Convert<Dimension>(borderWidth->right.value);
    auto top = Converter::Convert<Dimension>(borderWidth->top.value);
    auto bottom = Converter::Convert<Dimension>(borderWidth->bottom.value);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    BorderWidthProperty borderWidthProperty { .leftDimen = Dimension(left.Value(), unit),
        .topDimen = Dimension(top.Value(), unit),
        .rightDimen = Dimension(right.Value(), unit),
        .bottomDimen = Dimension(bottom.Value(), unit),
        .multiValued = true };
    layoutProperty->UpdateBorderWidth(borderWidthProperty);
    frameNode->MarkDirtyNode();
    renderContext->SetBorderWidth(borderWidthProperty);
}
Ark_EdgesNumber GetBorderColorImpl(Ark_RenderNode peer)
{
    return {};
}
void SetBorderColorImpl(Ark_RenderNode peer, const Ark_EdgesNumber* borderColor)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetBorderColor !");
        return;
    }
    auto left = Converter::Convert<uint32_t>(borderColor->left.value);
    auto right = Converter::Convert<uint32_t>(borderColor->right.value);
    auto top = Converter::Convert<uint32_t>(borderColor->top.value);
    auto bottom = Converter::Convert<uint32_t>(borderColor->bottom.value);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderColorProperty borderColorProperty { .leftColor = Color(left),
        .rightColor = Color(right),
        .topColor = Color(top),
        .bottomColor = Color(bottom),
        .multiValued = true };
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderColor, borderColorProperty, frameNode);
}
Ark_BorderRadiuses_graphics GetBorderRadiusImpl(Ark_RenderNode peer)
{
    return {};
}
void SetBorderRadiusImpl(Ark_RenderNode peer, const Ark_BorderRadiuses_graphics* borderRadius, Ark_Int32 unitValue)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetBorderRadius !");
        return;
    }
    auto topLeft = Converter::Convert<float>(borderRadius->topLeft);
    auto topRight = Converter::Convert<float>(borderRadius->topRight);
    auto bottomLeft = Converter::Convert<float>(borderRadius->bottomLeft);
    auto bottomRight = Converter::Convert<float>(borderRadius->bottomRight);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    const auto& renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    BorderRadiusProperty borderRadiusProperty(
        Dimension(topLeft, unit), Dimension(topRight, unit), Dimension(bottomRight, unit), Dimension(bottomLeft, unit));
    renderContext->UpdateBorderRadius(borderRadiusProperty);
}
Ark_ShapeMask GetShapeMaskImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShapeMaskImpl(Ark_RenderNode peer, Ark_ShapeMask shapeMask) {}
Ark_ShapeClip GetShapeClipImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShapeClipImpl(Ark_RenderNode peer, Ark_ShapeClip shapeClip) {}
Ark_Boolean GetMarkNodeGroupImpl(Ark_RenderNode peer)
{
    return {};
}
void SetMarkNodeGroupImpl(Ark_RenderNode peer, Ark_Boolean markNodeGroup)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetMarkNodeGroup !");
        return;
    }
    auto isNodeGroup = Converter::Convert<bool>(markNodeGroup);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetMarkNodeGroup(isNodeGroup);
    frameNode->SetApplicationRenderGroupMarked(true);
    renderContext->RequestNextFrame();
}
Ark_LengthMetricsUnit GetLengthMetricsUnitImpl(Ark_RenderNode peer)
{
    return {};
}
void SetLengthMetricsUnitImpl(Ark_RenderNode peer, Ark_LengthMetricsUnit lengthMetricsUnit) {}
} // namespace RenderNodeAccessor
const GENERATED_ArkUIRenderNodeAccessor* GetRenderNodeAccessor()
{
    static const GENERATED_ArkUIRenderNodeAccessor RenderNodeAccessorImpl {
        RenderNodeAccessor::DestroyPeerImpl,
        RenderNodeAccessor::CtorImpl,
        RenderNodeAccessor::GetFinalizerImpl,
        RenderNodeAccessor::AppendChildImpl,
        RenderNodeAccessor::InsertChildAfterImpl,
        RenderNodeAccessor::RemoveChildImpl,
        RenderNodeAccessor::ClearChildrenImpl,
        RenderNodeAccessor::GetChildImpl,
        RenderNodeAccessor::GetFirstChildImpl,
        RenderNodeAccessor::GetNextSiblingImpl,
        RenderNodeAccessor::GetPreviousSiblingImpl,
        RenderNodeAccessor::DrawImpl,
        RenderNodeAccessor::InvalidateImpl,
        RenderNodeAccessor::DisposeImpl,
        RenderNodeAccessor::SetRectMaskImpl,
        RenderNodeAccessor::SetCircleMaskImpl,
        RenderNodeAccessor::SetRoundRectMaskImpl,
        RenderNodeAccessor::SetOvalMaskImpl,
        RenderNodeAccessor::SetPathImpl,
        RenderNodeAccessor::SetRectClipImpl,
        RenderNodeAccessor::SetCircleClipImpl,
        RenderNodeAccessor::SetRoundRectClipImpl,
        RenderNodeAccessor::SetOvalClipImpl,
        RenderNodeAccessor::SetPathClipImpl,
        RenderNodeAccessor::GetBackgroundColorImpl,
        RenderNodeAccessor::SetBackgroundColorImpl,
        RenderNodeAccessor::GetClipToFrameImpl,
        RenderNodeAccessor::SetClipToFrameImpl,
        RenderNodeAccessor::GetOpacityImpl,
        RenderNodeAccessor::SetOpacityImpl,
        RenderNodeAccessor::GetSizeImpl,
        RenderNodeAccessor::SetSizeImpl,
        RenderNodeAccessor::GetPositionImpl,
        RenderNodeAccessor::SetPositionImpl,
        RenderNodeAccessor::GetFrameImpl,
        RenderNodeAccessor::SetFrameImpl,
        RenderNodeAccessor::GetPivotImpl,
        RenderNodeAccessor::SetPivotImpl,
        RenderNodeAccessor::GetScaleImpl,
        RenderNodeAccessor::SetScaleImpl,
        RenderNodeAccessor::GetTranslationImpl,
        RenderNodeAccessor::SetTranslationImpl,
        RenderNodeAccessor::GetRotationImpl,
        RenderNodeAccessor::SetRotationImpl,
        RenderNodeAccessor::GetTransformImpl,
        RenderNodeAccessor::SetTransformImpl,
        RenderNodeAccessor::GetShadowColorImpl,
        RenderNodeAccessor::SetShadowColorImpl,
        RenderNodeAccessor::GetShadowOffsetImpl,
        RenderNodeAccessor::SetShadowOffsetImpl,
        RenderNodeAccessor::GetLabelImpl,
        RenderNodeAccessor::SetLabelImpl,
        RenderNodeAccessor::GetShadowAlphaImpl,
        RenderNodeAccessor::SetShadowAlphaImpl,
        RenderNodeAccessor::GetShadowElevationImpl,
        RenderNodeAccessor::SetShadowElevationImpl,
        RenderNodeAccessor::GetShadowRadiusImpl,
        RenderNodeAccessor::SetShadowRadiusImpl,
        RenderNodeAccessor::GetBorderStyleImpl,
        RenderNodeAccessor::SetBorderStyleImpl,
        RenderNodeAccessor::GetBorderWidthImpl,
        RenderNodeAccessor::SetBorderWidthImpl,
        RenderNodeAccessor::GetBorderColorImpl,
        RenderNodeAccessor::SetBorderColorImpl,
        RenderNodeAccessor::GetBorderRadiusImpl,
        RenderNodeAccessor::SetBorderRadiusImpl,
        RenderNodeAccessor::GetShapeMaskImpl,
        RenderNodeAccessor::SetShapeMaskImpl,
        RenderNodeAccessor::GetShapeClipImpl,
        RenderNodeAccessor::SetShapeClipImpl,
        RenderNodeAccessor::GetMarkNodeGroupImpl,
        RenderNodeAccessor::SetMarkNodeGroupImpl,
        RenderNodeAccessor::GetLengthMetricsUnitImpl,
        RenderNodeAccessor::SetLengthMetricsUnitImpl,
    };
    return &RenderNodeAccessorImpl;
}
} // namespace GeneratedModifier
} // namespace OHOS::Ace::NG
