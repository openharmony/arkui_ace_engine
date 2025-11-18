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
#include "core/interfaces/native/implementation/shape_clip_peer.h"
#include "core/interfaces/native/implementation/shape_mask_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/base/view_abstract_model_static.h"

namespace {
constexpr int32_t ERROR_CODE_NO_ERROR = 0;
constexpr int32_t ERROR_CODE_NODE_IS_ADOPTED = 106206;
constexpr int32_t ERROR_CODE_PARAM_INVALID = 401;
} // namespace

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
constexpr int32_t ARK_UNION_UNDEFINED = 1;

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
namespace RenderNodeExtenderAccessor {
Ark_NativePointer ConstructorRenderNodeImpl(Ark_Int32 nodeId)
{
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode(
        V2::RENDER_NODE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NG::RenderNodePattern>(); });
    frameNode->SetIsArkTsRenderNode(true);
    auto renderNodePeer = PeerUtils::CreatePeer<RenderNodePeer>(frameNode);
    return renderNodePeer;
}
void DestroyPeerImpl(Ark_RenderNode peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_NativePointer GetDestroyImpl()
{
    return reinterpret_cast<void*>(&DestroyPeerImpl);
}
void SetBackgroundColorImpl(Ark_RenderNode peer,
                            const Ark_Number* backgroundColor)
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
void SetClipToFrameImpl(Ark_RenderNode peer,
                        Ark_Boolean clipToFrame)
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
void SetOpacityImpl(Ark_RenderNode peer,
                    const Ark_Number* opacity)
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
void SetSizeImpl(Ark_RenderNode peer,
                 const Ark_Size* size,
                 Ark_Int32 unitValue)
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
void SetPositionImpl(Ark_RenderNode peer,
                     const Ark_Vector2* position,
                     Ark_Int32 unitValue)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetPosition !");
        return;
    }
    auto xValue = Converter::Convert<Dimension>(position->x);
    auto yValue = Converter::Convert<Dimension>(position->y);

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
void SetPivotImpl(Ark_RenderNode peer,
                  const Ark_Vector2* pivot)
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
void SetScaleImpl(Ark_RenderNode peer,
                  const Ark_Vector2* scale)
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
void SetTranslationImpl(Ark_RenderNode peer,
                        const Ark_Vector2* translation)
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
void SetRotationImpl(Ark_RenderNode peer,
                     const Ark_Vector3* rotation,
                     Ark_Int32 unitValue)
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
void SetTransformImpl(Ark_RenderNode peer,
                      const Ark_Matrix4* transform)
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
void SetShadowColorImpl(Ark_RenderNode peer,
                        const Ark_Number* shadowColor)
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
void SetShadowOffsetImpl(Ark_RenderNode peer,
                         const Ark_Vector2* shadowOffset,
                         Ark_Int32 unitValue)
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
void SetLabelImpl(Ark_RenderNode peer,
                  const Ark_String* label)
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
void SetShadowAlphaImpl(Ark_RenderNode peer,
                        const Ark_Number* shadowAlpha)
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
void SetShadowElevationImpl(Ark_RenderNode peer,
                            const Ark_Number* shadowElevation)
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
void SetShadowRadiusImpl(Ark_RenderNode peer,
                         const Ark_Number* shadowRadius)
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
void SetBorderStyleImpl(Ark_RenderNode peer,
                        const Ark_NodeEdgeStyles* borderStyle)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetBorderStyle !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto borderStyleProperty = Converter::Convert<BorderStyleProperty>(*borderStyle);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderStyle, borderStyleProperty, frameNode);
}
void SetBorderWidthImpl(Ark_RenderNode peer,
                        const Ark_EdgeNumber* borderWidth,
                        Ark_Int32 unitValue)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetBorderWidth !");
        return;
    }
    auto left = Converter::Convert<Dimension>(borderWidth->left);
    auto right = Converter::Convert<Dimension>(borderWidth->right);
    auto top = Converter::Convert<Dimension>(borderWidth->top);
    auto bottom = Converter::Convert<Dimension>(borderWidth->bottom);

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
void SetBorderColorImpl(Ark_RenderNode peer,
                        const Ark_EdgeNumber* borderColor)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetBorderColor !");
        return;
    }
    auto left = Converter::Convert<uint32_t>(borderColor->left);
    auto right = Converter::Convert<uint32_t>(borderColor->right);
    auto top = Converter::Convert<uint32_t>(borderColor->top);
    auto bottom = Converter::Convert<uint32_t>(borderColor->bottom);

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
void SetBorderRadiusImpl(Ark_RenderNode peer,
                         const Ark_BorderRadiuses_graphics* borderRadius,
                         Ark_Int32 unitValue)
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
void SetMarkNodeGroupImpl(Ark_RenderNode peer,
                          Ark_Boolean markNodeGroup)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetMarkNodeGroup !");
        return;
    }
    auto isNodeGroup = Converter::Convert<bool>(markNodeGroup);

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");

    frameNode->SetApplicationRenderGroupMarked(isNodeGroup);
    ViewAbstract::SetRenderGroup(Referenced::RawPtr(frameNode), isNodeGroup);
}
void SetRectMaskImpl(Ark_RenderNode peer,
                     const Ark_common2D_Rect* rect,
                     const Ark_Number* fillColor,
                     const Ark_Number* strokeColor,
                     const Ark_Number* strokeWidth)
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
void SetCircleMaskImpl(Ark_RenderNode peer,
                   const Ark_Circle* circle,
                   const Ark_Number* fillColor,
                   const Ark_Number* strokeColor,
                   const Ark_Number* strokeWidth)
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
void SetRoundRectMaskImpl(Ark_RenderNode peer,
                          const Ark_RoundRect* roundRect,
                          const Ark_Number* fillColor,
                          const Ark_Number* strokeColor,
                          const Ark_Number* strokeWidth)
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
void SetOvalMaskImpl(Ark_RenderNode peer,
                     const Ark_common2D_Rect* rect,
                     const Ark_Number* fillColor,
                     const Ark_Number* strokeColor,
                     const Ark_Number* strokeWidth)
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
void SetPathImpl(Ark_RenderNode peer,
                 const Ark_CommandPath* path,
                 const Ark_Number* fillColor,
                 const Ark_Number* strokeColor,
                 const Ark_Number* strokeWidth)
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
void SetRectClipImpl(Ark_RenderNode peer,
                     const Ark_common2D_Rect* rect)
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
void SetCircleClipImpl(Ark_RenderNode peer,
                       const Ark_Circle* circle)
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
void SetRoundRectClipImpl(Ark_RenderNode peer,
                          const Ark_RoundRect* roundRect)
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
void SetOvalClipImpl(Ark_RenderNode peer,
                     const Ark_common2D_Rect* rect)
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
void SetPathClipImpl(Ark_RenderNode peer,
                     const Ark_CommandPath* path)
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
Ark_Int32 AppendChildImpl(Ark_RenderNode peer,
                          Ark_RenderNode node)
{
    if (!peer || !node) {
        LOGW("This renderNode or child is nullptr when appendChild !");
        return ERROR_CODE_PARAM_INVALID;
    }
    auto parent = peer->GetFrameNode();
    auto child = node->GetFrameNode();
    if (parent && child) {
        if (child->IsAdopted()) {
            return ERROR_CODE_NODE_IS_ADOPTED;
        }
        parent->AddChild(child);
        parent->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
    }
    return ERROR_CODE_NO_ERROR;
}
Ark_Int32 InsertChildAfterImpl(Ark_RenderNode peer,
                               Ark_RenderNode child,
                               Ark_RenderNode sibling)
{
    if (!peer || !child) {
        LOGW("This renderNode or child is nullptr when InsertChildAfter !");
        return ERROR_CODE_PARAM_INVALID;
    }
    auto currentNode = peer->GetFrameNode();
    auto childNode = child->GetFrameNode();
    if (childNode && childNode->IsAdopted()) {
        return ERROR_CODE_NODE_IS_ADOPTED;
    }
    auto siblingNode = sibling->GetFrameNode();
    auto index = currentNode->GetChildIndex(siblingNode);
    currentNode->AddChild(childNode, index + 1);
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
    return ERROR_CODE_NO_ERROR;
}
void RemoveChildImpl(Ark_RenderNode peer,
                     Ark_RenderNode node)
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
} // RenderNodeExtenderAccessor
const GENERATED_ArkUIRenderNodeExtenderAccessor* GetRenderNodeExtenderAccessor()
{
    static const GENERATED_ArkUIRenderNodeExtenderAccessor RenderNodeExtenderAccessorImpl {
        RenderNodeExtenderAccessor::ConstructorRenderNodeImpl,
        RenderNodeExtenderAccessor::GetDestroyImpl,
        RenderNodeExtenderAccessor::DestroyPeerImpl,
        RenderNodeExtenderAccessor::SetBackgroundColorImpl,
        RenderNodeExtenderAccessor::SetClipToFrameImpl,
        RenderNodeExtenderAccessor::SetOpacityImpl,
        RenderNodeExtenderAccessor::SetSizeImpl,
        RenderNodeExtenderAccessor::SetPositionImpl,
        RenderNodeExtenderAccessor::SetPivotImpl,
        RenderNodeExtenderAccessor::SetScaleImpl,
        RenderNodeExtenderAccessor::SetTranslationImpl,
        RenderNodeExtenderAccessor::SetRotationImpl,
        RenderNodeExtenderAccessor::SetTransformImpl,
        RenderNodeExtenderAccessor::SetShadowColorImpl,
        RenderNodeExtenderAccessor::SetShadowOffsetImpl,
        RenderNodeExtenderAccessor::SetLabelImpl,
        RenderNodeExtenderAccessor::SetShadowAlphaImpl,
        RenderNodeExtenderAccessor::SetShadowElevationImpl,
        RenderNodeExtenderAccessor::SetShadowRadiusImpl,
        RenderNodeExtenderAccessor::SetBorderStyleImpl,
        RenderNodeExtenderAccessor::SetBorderWidthImpl,
        RenderNodeExtenderAccessor::SetBorderColorImpl,
        RenderNodeExtenderAccessor::SetBorderRadiusImpl,
        RenderNodeExtenderAccessor::SetMarkNodeGroupImpl,
        RenderNodeExtenderAccessor::SetRectMaskImpl,
        RenderNodeExtenderAccessor::SetCircleMaskImpl,
        RenderNodeExtenderAccessor::SetRoundRectMaskImpl,
        RenderNodeExtenderAccessor::SetOvalMaskImpl,
        RenderNodeExtenderAccessor::SetPathImpl,
        RenderNodeExtenderAccessor::SetRectClipImpl,
        RenderNodeExtenderAccessor::SetCircleClipImpl,
        RenderNodeExtenderAccessor::SetRoundRectClipImpl,
        RenderNodeExtenderAccessor::SetOvalClipImpl,
        RenderNodeExtenderAccessor::SetPathClipImpl,
        RenderNodeExtenderAccessor::AppendChildImpl,
        RenderNodeExtenderAccessor::InsertChildAfterImpl,
        RenderNodeExtenderAccessor::RemoveChildImpl,
        RenderNodeExtenderAccessor::ClearChildrenImpl,
        RenderNodeExtenderAccessor::InvalidateImpl,
    };
    return &RenderNodeExtenderAccessorImpl;
}

}
