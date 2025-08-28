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
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace Converter {
struct Circle {
    float centerX;
    float centerY;
    float radius;
};

template<>
Converter::Circle Convert(const Ark_Circle& src)
{
    return {
        Converter::Convert<float>(src.centerX),
        Converter::Convert<float>(src.centerY),
        Converter::Convert<float>(src.radius)
    };
}

template<>
OHOS::Ace::NG::RectF Convert(const Ark_Rect& value)
{
    auto left = Converter::Convert<float>(value.left);
    auto top = Converter::Convert<float>(value.top);
    auto right = Converter::Convert<float>(value.right);
    auto bottom = Converter::Convert<float>(value.bottom);
    return { left, top, right - left, bottom - top };
}

template<>
OHOS::Ace::NG::RoundRect Convert(const Ark_RoundRect& value)
{
    auto rect = Converter::Convert<RectF>(value.rect);
    auto corners = Converter::Convert<Corner>(value.corners);

    RoundRect roundRectInstance;
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS,
        corners.topLeftRadius.GetX().Value(),
        corners.topLeftRadius.GetY().Value());
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS,
        corners.topRightRadius.GetX().Value(),
        corners.topRightRadius.GetY().Value());
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS,
        corners.bottomLeftRadius.GetX().Value(),
        corners.bottomLeftRadius.GetY().Value());
    roundRectInstance.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS,
        corners.bottomRightRadius.GetX().Value(),
        corners.bottomRightRadius.GetY().Value());

    auto left = Converter::Convert<float>(rect.Left());
    auto top = Converter::Convert<float>(rect.Top());
    auto right = Converter::Convert<float>(rect.Right());
    auto bottom = Converter::Convert<float>(rect.Bottom());
    RectF rectValue(left, top, right - left, bottom - top);
    roundRectInstance.SetRect(rectValue);

    return roundRectInstance;
}

template<>
Size Convert(const Ark_Size& value)
{
    auto width = Converter::OptConvert<float>(value.width);
    auto height = Converter::OptConvert<float>(value.height);
    Validator::ValidateNonNegative(width);
    Validator::ValidateNonNegative(height);
    return Size { width.value_or(0), height.value_or(0) };
}

template<>
Rect Convert(const Ark_Frame& value)
{
    auto x = Converter::Convert<float>(value.x);
    auto y = Converter::Convert<float>(value.y);
    auto width = Converter::OptConvert<float>(value.width);
    auto height = Converter::OptConvert<float>(value.height);
    Validator::ValidateNonNegative(width);
    Validator::ValidateNonNegative(height);
    return Rect { x, y, width.value_or(0), height.value_or(0) };
}

template<>
VectorF Convert(const Ark_Vector2& value)
{
    return {
        Converter::Convert<float>(value.x),
        Converter::Convert<float>(value.y)
    };
}

template<>
Vector3F Convert(const Ark_Vector3& value)
{
    return {
        Converter::Convert<float>(value.x),
        Converter::Convert<float>(value.y),
        Converter::Convert<float>(value.z)
    };
}

template<>
Matrix4 Convert(const Ark_Matrix4& value)
{
    return {
        Converter::Convert<float>(value.value0),
        Converter::Convert<float>(value.value1),
        Converter::Convert<float>(value.value2),
        Converter::Convert<float>(value.value3),
        Converter::Convert<float>(value.value4),
        Converter::Convert<float>(value.value5),
        Converter::Convert<float>(value.value6),
        Converter::Convert<float>(value.value7),
        Converter::Convert<float>(value.value8),
        Converter::Convert<float>(value.value9),
        Converter::Convert<float>(value.value10),
        Converter::Convert<float>(value.value11),
        Converter::Convert<float>(value.value12),
        Converter::Convert<float>(value.value13),
        Converter::Convert<float>(value.value14),
        Converter::Convert<float>(value.value15)
    };
}

template<>
Offset Convert(const Ark_Vector2& value)
{
    return Offset{
        Converter::Convert<float>(value.x),
        Converter::Convert<float>(value.y)
    };
}

template<>
Color Convert(const Ark_Length& src)
{
    if (src.type == Ark_Tag::INTEROP_TAG_RESOURCE) {
        auto resource = ArkValue<Ark_Resource>(src);
        ResourceConverter converter(resource);
        return converter.ToColor().value_or(Color());
    } else {
        return Color(static_cast<uint32_t>(src.value));
    }
}

template<>
BorderWidthProperty Convert(const Ark_EdgesNumber& src)
{
    BorderWidthProperty property;
    property.leftDimen = OptConvert<Dimension>(src.left);
    property.topDimen = OptConvert<Dimension>(src.top);
    property.rightDimen = OptConvert<Dimension>(src.right);
    property.bottomDimen = OptConvert<Dimension>(src.bottom);
    property.multiValued = true;
    return property;
}

template<>
BorderRadiusProperty Convert(const Ark_BorderRadiuses_graphics& src)
{
    BorderRadiusProperty property;
    property.radiusTopLeft = OptConvert<Dimension>(src.topLeft);
    property.radiusTopRight = OptConvert<Dimension>(src.topRight);
    property.radiusBottomLeft = OptConvert<Dimension>(src.bottomLeft);
    property.radiusBottomRight = OptConvert<Dimension>(src.bottomRight);
    return property;
}

void AssignArkValue(Ark_Position& dst, const OffsetT<Dimension>& src, ConvContext *ctx)
{
    dst.x = Converter::ArkValue<Opt_Length>(src.GetX());
    dst.y = Converter::ArkValue<Opt_Length>(src.GetY());
}

void AssignArkValue(Ark_Vector2& dst, const DimensionOffset& src, ConvContext *ctx)
{
    dst.x = Converter::ArkValue<Ark_Number>(src.GetX());
    dst.y = Converter::ArkValue<Ark_Number>(src.GetY());
}

void AssignArkValue(Ark_Vector2& dst, const VectorF& src, ConvContext *ctx)
{
    dst.x = Converter::ArkValue<Ark_Number>(src.x);
    dst.y = Converter::ArkValue<Ark_Number>(src.y);
}

void AssignArkValue(Ark_Vector2& dst, const TranslateOptions& src, ConvContext *ctx)
{
    dst.x = Converter::ArkValue<Ark_Number>(src.x);
    dst.y = Converter::ArkValue<Ark_Number>(src.y);
}

void AssignArkValue(Ark_Vector3& dst, const Vector3F& src, ConvContext *ctx)
{
    dst.x = Converter::ArkValue<Ark_Number>(src.x);
    dst.y = Converter::ArkValue<Ark_Number>(src.y);
    dst.z = Converter::ArkValue<Ark_Number>(src.z);
}

void AssignArkValue(Ark_Matrix4& dst, const Matrix4& src, ConvContext *ctx)
{
    constexpr int32_t index0 = 0;
    constexpr int32_t index1 = 1;
    constexpr int32_t index2 = 2;
    constexpr int32_t index3 = 3;
    dst.value0 = Converter::ArkValue<Ark_Number>(src.Get(index0, index0));
    dst.value1 = Converter::ArkValue<Ark_Number>(src.Get(index0, index1));
    dst.value2 = Converter::ArkValue<Ark_Number>(src.Get(index0, index2));
    dst.value3 = Converter::ArkValue<Ark_Number>(src.Get(index0, index3));
    dst.value4 = Converter::ArkValue<Ark_Number>(src.Get(index1, index0));
    dst.value5 = Converter::ArkValue<Ark_Number>(src.Get(index1, index1));
    dst.value6 = Converter::ArkValue<Ark_Number>(src.Get(index1, index2));
    dst.value7 = Converter::ArkValue<Ark_Number>(src.Get(index1, index3));
    dst.value8 = Converter::ArkValue<Ark_Number>(src.Get(index2, index0));
    dst.value9 = Converter::ArkValue<Ark_Number>(src.Get(index2, index1));
    dst.value10 = Converter::ArkValue<Ark_Number>(src.Get(index2, index2));
    dst.value11 = Converter::ArkValue<Ark_Number>(src.Get(index2, index3));
    dst.value12 = Converter::ArkValue<Ark_Number>(src.Get(index3, index0));
    dst.value13 = Converter::ArkValue<Ark_Number>(src.Get(index3, index1));
    dst.value14 = Converter::ArkValue<Ark_Number>(src.Get(index3, index2));
    dst.value15 = Converter::ArkValue<Ark_Number>(src.Get(index3, index3));
}

void AssignArkValue(Ark_Vector2& dst, const Offset& src, ConvContext *ctx)
{
    dst.x = Converter::ArkValue<Ark_Number>(src.GetX());
    dst.y = Converter::ArkValue<Ark_Number>(src.GetY());
}

void AssignArkValue(Ark_BorderStyle& dst, const BorderStyle& src, ConvContext *ctx)
{
    switch (src) {
        case OHOS::Ace::BorderStyle::SOLID: dst = ARK_BORDER_STYLE_SOLID; break;
        case OHOS::Ace::BorderStyle::DASHED: dst = ARK_BORDER_STYLE_DASHED; break;
        case OHOS::Ace::BorderStyle::DOTTED: dst = ARK_BORDER_STYLE_DOTTED; break;
        default: dst = static_cast<Ark_BorderStyle>(-1);
    }
}

void AssignArkValue(Ark_EdgeStyles& dst, const BorderStyleProperty& src, ConvContext *ctx)
{
    if (src.styleTop.has_value()) {
        dst.top = Converter::ArkValue<Opt_BorderStyle>(src.styleTop.value());
    } else {
        dst.top = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
    }

    if (src.styleRight.has_value()) {
        dst.right = Converter::ArkValue<Opt_BorderStyle>(src.styleRight.value());
    } else {
        dst.right = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
    }

    if (src.styleBottom.has_value()) {
        dst.bottom = Converter::ArkValue<Opt_BorderStyle>(src.styleBottom.value());
    } else {
        dst.bottom = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
    }

    if (src.styleLeft.has_value()) {
        dst.left = Converter::ArkValue<Opt_BorderStyle>(src.styleLeft.value());
    } else {
        dst.left = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
    }
}

void AssignArkValue(Ark_EdgesNumber& dst, const BorderWidthProperty& src, ConvContext *ctx)
{
    if (src.topDimen.has_value()) {
        dst.top = Converter::ArkValue<Opt_Number>(src.topDimen.value());
    } else {
        dst.top = Converter::ArkValue<Opt_Number>(Ark_Empty());
    }

    if (src.rightDimen.has_value()) {
        dst.right = Converter::ArkValue<Opt_Number>(src.rightDimen.value());
    } else {
        dst.right = Converter::ArkValue<Opt_Number>(Ark_Empty());
    }

    if (src.bottomDimen.has_value()) {
        dst.bottom = Converter::ArkValue<Opt_Number>(src.bottomDimen.value());
    } else {
        dst.bottom = Converter::ArkValue<Opt_Number>(Ark_Empty());
    }

    if (src.leftDimen.has_value()) {
        dst.left = Converter::ArkValue<Opt_Number>(src.leftDimen.value());
    } else {
        dst.left = Converter::ArkValue<Opt_Number>(Ark_Empty());
    }
}

void AssignArkValue(Ark_EdgesNumber& dst, const BorderColorProperty& src, ConvContext *ctx)
{
    if (src.topColor.has_value()) {
        dst.top = Converter::ArkValue<Opt_Number>(static_cast<float>(src.topColor.value().GetValue()));
    } else {
        dst.top = Converter::ArkValue<Opt_Number>(Ark_Empty());
    }

    if (src.rightColor.has_value()) {
        dst.right = Converter::ArkValue<Opt_Number>(static_cast<float>(src.rightColor.value().GetValue()));
    } else {
        dst.right = Converter::ArkValue<Opt_Number>(Ark_Empty());
    }

    if (src.bottomColor.has_value()) {
        dst.bottom = Converter::ArkValue<Opt_Number>(static_cast<float>(src.bottomColor.value().GetValue()));
    } else {
        dst.bottom = Converter::ArkValue<Opt_Number>(Ark_Empty());
    }

    if (src.leftColor.has_value()) {
        dst.left = Converter::ArkValue<Opt_Number>(static_cast<float>(src.leftColor.value().GetValue()));
    } else {
        dst.left = Converter::ArkValue<Opt_Number>(Ark_Empty());
    }
}

void AssignArkValue(Ark_BorderRadiuses_graphics& dst, const BorderRadiusProperty& src, ConvContext *ctx)
{
    if (src.radiusTopLeft.has_value()) {
        dst.topLeft = Converter::ArkValue<Ark_Number>(src.radiusTopLeft.value());
    } else {
        dst.topLeft = Converter::ArkValue<Ark_Number>(0);
    }

    if (src.radiusTopRight.has_value()) {
        dst.topRight = Converter::ArkValue<Ark_Number>(src.radiusTopRight.value());
    } else {
        dst.topRight = Converter::ArkValue<Ark_Number>(0);
    }

    if (src.radiusBottomRight.has_value()) {
        dst.bottomRight = Converter::ArkValue<Ark_Number>(src.radiusBottomRight.value());
    } else {
        dst.bottomRight = Converter::ArkValue<Ark_Number>(0);
    }

    if (src.radiusBottomLeft.has_value()) {
        dst.bottomLeft = Converter::ArkValue<Ark_Number>(src.radiusBottomLeft.value());
    } else {
        dst.bottomLeft = Converter::ArkValue<Ark_Number>(0);
    }
}

template<>
void AssignCast(std::optional<LengthMetricsUnit>& dst, const Ark_LengthMetricsUnit& src)
{
    switch (src) {
        case ARK_LENGTH_METRICS_UNIT_DEFAULT: dst = LengthMetricsUnit::DEFAULT; break;
        case ARK_LENGTH_METRICS_UNIT_PX: dst = LengthMetricsUnit::PX; break;
        default: LOGE("Unexpected enum value in Ark_LengthMetricsUnit: %{public}d", src);
    }
}

void AssignArkValue(Ark_LengthMetricsUnit& dst, const LengthMetricsUnit& src, ConvContext *ctx)
{
    switch (src) {
        case LengthMetricsUnit::DEFAULT: dst = ARK_LENGTH_METRICS_UNIT_DEFAULT; break;
        case LengthMetricsUnit::PX: dst = ARK_LENGTH_METRICS_UNIT_PX; break;
        default: dst = static_cast<Ark_LengthMetricsUnit>(-1);
            LOGE("Unexpected enum value in LengthMetricsUnit: %{public}d", src);
    }
}
}

namespace GeneratedModifier {
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

RefPtr<OHOS::Ace::BasicShape> GetBasicShape(Ark_BaseShape peer)
{
    return peer ? peer->shape : nullptr;
}

RefPtr<FrameNode> GetParentNode(const RefPtr<FrameNode>& nodeRef)
{
    CHECK_NULL_RETURN(nodeRef, nullptr);
    auto parent = nodeRef->GetParent();
    while (parent != nullptr && !AceType::InstanceOf<FrameNode>(parent)) {
        parent = parent->GetParent();
    }
    return (parent == nullptr || parent->GetTag() == V2::PAGE_ETS_TAG || parent->GetTag() == V2::STAGE_ETS_TAG)
               ? nullptr : AceType::DynamicCast<FrameNode>(parent);
}

RefPtr<RenderContext> GetRenderContext(const RefPtr<FrameNode>& node, bool checkProxy = true)
{
    CHECK_NULL_RETURN(node, nullptr);
    if (checkProxy) {
        CHECK_NULL_RETURN(node->GetTag() != "BuilderProxyNode", nullptr);
    }
    return node->GetRenderContext();
}
} // namespace
namespace RenderNodeAccessor {
void DestroyPeerImpl(Ark_RenderNode peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_RenderNode CtorImpl(Ark_Int32 nodeId, const DrawCallbackFunc* value)
{
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode(
        V2::RENDER_NODE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NG::RenderNodePattern>(); });
    frameNode->SetIsArkTsRenderNode(true);
    auto renderNodePeer = PeerUtils::CreatePeer<RenderNodePeer>(frameNode);
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
    CHECK_NULL_VOID(parent && child && child->GetParent());

    parent->AddChild(child);
    parent->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void InsertChildAfterImpl(Ark_RenderNode peer, Ark_RenderNode child, const Ark_Union_RenderNode_Undefined* sibling)
{
    if (!peer || !child) {
        LOGW("This renderNode or child is nullptr when InsertChildAfter !");
        return;
    }
    if (!sibling) {
        LOGW("Sibling node is nullptr or undefined when InsertChildAfter !");
        return;
    }
    auto currentNode = peer->GetFrameNode();
    auto childNode = child->GetFrameNode();
    CHECK_NULL_VOID(currentNode && childNode && childNode->GetParent());

    auto siblingOpt = Converter::OptConvert<RenderNodePeer*>(*sibling);
    auto index = -1;
    if (siblingOpt.has_value()) {
        auto siblingNode = siblingOpt.value()->GetFrameNode();
        index = currentNode->GetChildIndex(siblingNode);
    }
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
    CHECK_NULL_VOID(currentNode && childNode);
    currentNode->RemoveChild(childNode);
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void ClearChildrenImpl(Ark_RenderNode peer)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when ClearChildren !");
        return;
    }
    auto currentNode = peer->GetFrameNode();
    CHECK_NULL_VOID(currentNode);
    currentNode->Clean();
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
Ark_Union_RenderNode_Undefined GetChildImpl(Ark_RenderNode peer, const Ark_Number* index)
{
    auto errorValue = Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_Undefined>(Ark_Undefined{});
    CHECK_NULL_RETURN(peer && index, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto indexInt = Converter::Convert<int32_t>(*index);
    CHECK_NULL_RETURN(indexInt >= 0, errorValue);
    LOGW("FrameNodeAccessor::GetChildImpl work only for case: IsExpanded is false");
    auto retValue = PeerUtils::CreatePeer<RenderNodePeer>(
        frameNode->GetFrameNodeChildByIndex(indexInt, false, false));
    return Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_RenderNode>(retValue);
}
Ark_Union_RenderNode_Undefined GetFirstChildImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_Undefined>(Ark_Undefined{});
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto child = frameNode->GetFirstChild();
    CHECK_NULL_RETURN(child, errorValue);
    auto retValue = PeerUtils::CreatePeer<RenderNodePeer>(AceType::DynamicCast<FrameNode>(child));
    return Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_RenderNode>(retValue);
}
Ark_Union_RenderNode_Undefined GetNextSiblingImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_Undefined>(Ark_Undefined{});
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto parent = GetParentNode(frameNode);
    CHECK_NULL_RETURN(parent, errorValue);
    LOGW("RenderNodeAccessor::GetNextSiblingImpl work only for case: IsExpanded is false");
    auto index = parent->GetFrameNodeIndex(frameNode, false);
    CHECK_NULL_RETURN(index >= 0, errorValue);
    auto sibling = parent->GetFrameNodeChildByIndex(index + 1, false, false);
    auto retValue = PeerUtils::CreatePeer<RenderNodePeer>(sibling);
    return Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_RenderNode>(retValue);
}
Ark_Union_RenderNode_Undefined GetPreviousSiblingImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_Undefined>(Ark_Undefined{});
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto parent = GetParentNode(frameNode);
    CHECK_NULL_RETURN(parent, errorValue);
    LOGW("RenderNodeAccessor::GetPreviousSiblingImpl work only for case: IsExpanded is false");
    auto index = parent->GetFrameNodeIndex(frameNode, false);
    CHECK_NULL_RETURN(index > 0, errorValue);
    auto sibling = parent->GetFrameNodeChildByIndex(index - 1, false, false);
    auto retValue = PeerUtils::CreatePeer<RenderNodePeer>(sibling);
    return Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_RenderNode>(retValue);
}
void DrawImpl(Ark_RenderNode peer, const Ark_DrawContext* context)
{
    LOGW("RenderNodeAccessor::DrawImpl is not implemented.");
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
    auto renderContext = GetRenderContext(frameNode);
    CHECK_NULL_VOID(renderContext);
    pattern->Invalidate();
    renderContext->RequestNextFrame();
}
void DisposeImpl(Ark_RenderNode peer)
{
    CHECK_NULL_VOID(peer);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto parent = GetParentNode(frameNode);
    CHECK_NULL_VOID(parent);
    parent->RemoveChild(frameNode);
    parent->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
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
    // The value is a floating point number in the range [0.0, 1.0], and the default value is 0.5.
    auto defaultPivot = DimensionOffset(Dimension(0.5f), Dimension(0.5f));
    auto errorValue = Converter::ArkValue<Ark_Vector2>(defaultPivot);
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto renderContext = GetRenderContext(frameNode, false);
    CHECK_NULL_RETURN(renderContext, errorValue);
    auto pivot = renderContext->GetTransformCenterValue(defaultPivot);
    return Converter::ArkValue<Ark_Vector2>(pivot);
}
void SetPivotImpl(Ark_RenderNode peer, const Ark_Vector2* pivot)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetPivot !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(pivot);

    auto pivotConv = Converter::Convert<VectorF>(*pivot);
    auto x = GreatOrEqual(pivotConv.x, 0.f) && LessOrEqual(pivotConv.x, 1.f) ? pivotConv.x : 0.5f;
    auto y = GreatOrEqual(pivotConv.y, 0.f) && LessOrEqual(pivotConv.y, 1.f) ? pivotConv.y : 0.5f;
    ViewAbstractModelStatic::SetPivot(Referenced::RawPtr(frameNode), DimensionOffset(Dimension(x), Dimension(y)));
}
Ark_Vector2 GetScaleImpl(Ark_RenderNode peer)
{
    // The default value is { x: 1, y: 1 }.
    auto errorValue = Converter::ArkValue<Ark_Vector2>(VectorF(1.f, 1.f));
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto scaleValue = ViewAbstract::GetScale(Referenced::RawPtr(frameNode));
    return Converter::ArkValue<Ark_Vector2>(scaleValue);
}
void SetScaleImpl(Ark_RenderNode peer, const Ark_Vector2* scale)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetScale !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(scale);

    auto scaleConv = Converter::Convert<VectorF>(*scale);
    auto x = GreatOrEqual(scaleConv.x, 0.f) ? scaleConv.x : 1.f;
    auto y = GreatOrEqual(scaleConv.y, 0.f) ? scaleConv.y : 1.f;
    ViewAbstract::SetScale(Referenced::RawPtr(frameNode), VectorF(x, y));
}
Ark_Vector2 GetTranslationImpl(Ark_RenderNode peer)
{
    // The default value is { x: 0, y: 0 }.
    auto errorValue = Converter::ArkValue<Ark_Vector2>(VectorF(0.f, 0.f));
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto translateValue = ViewAbstract::GetTranslate(Referenced::RawPtr(frameNode));
    return Converter::ArkValue<Ark_Vector2>(translateValue);
}
void SetTranslationImpl(Ark_RenderNode peer, const Ark_Vector2* translation)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetTranslation !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(translation);

    auto translateConv = Converter::Convert<VectorF>(*translation);
    auto x = GreatOrEqual(translateConv.x, 0.f) ? translateConv.x : 0.f;
    auto y = GreatOrEqual(translateConv.y, 0.f) ? translateConv.y : 0.f;
    ViewAbstract::SetTranslate(Referenced::RawPtr(frameNode),
        TranslateOptions(CalcDimension(x), CalcDimension(y), CalcDimension(0.f)));
}
Ark_Vector3 GetRotationImpl(Ark_RenderNode peer)
{
    // The default value is { x: 0, y: 0, z: 0}.
    auto errorValue = Converter::ArkValue<Ark_Vector3>(Vector3F(0.f, 0.f, 0.f));
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto rotateValue = ViewAbstract::GetRotate(Referenced::RawPtr(frameNode));
    return Converter::ArkValue<Ark_Vector3>(Vector3F(rotateValue.x, rotateValue.y, rotateValue.z));
}
void SetRotationImpl(Ark_RenderNode peer, const Ark_Vector3* rotation, const Ark_Int32 unitValue)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetRotation !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(rotation);

    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    auto rotationConv = Converter::Convert<Vector3F>(*rotation);
    auto x = Dimension(GreatOrEqual(rotationConv.x, 0.f) ? rotationConv.x : 0.f, unit);
    auto y = Dimension(GreatOrEqual(rotationConv.y, 0.f) ? rotationConv.y : 0.f, unit);
    auto z = Dimension(GreatOrEqual(rotationConv.z, 0.f) ? rotationConv.z : 0.f, unit);
    ViewAbstract::SetRotate(Referenced::RawPtr(frameNode),
        Vector5F(x.ConvertToPx(), y.ConvertToPx(), z.ConvertToPx(), 0.f, 0.f)
    );
}
Ark_Matrix4 GetTransformImpl(Ark_RenderNode peer)
{
    // The default value is [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1]
    auto errorValue = Converter::ArkValue<Ark_Matrix4>(
        Matrix4(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f));
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto transformValue = ViewAbstract::GetTransform(Referenced::RawPtr(frameNode));
    return Converter::ArkValue<Ark_Matrix4>(transformValue);
}
void SetTransformImpl(Ark_RenderNode peer, const Ark_Matrix4* transform)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetTransform !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(transform);

    auto transformConv = Converter::Convert<Matrix4>(*transform);
    ViewAbstractModelStatic::SetTransformMatrix(Referenced::RawPtr(frameNode), transformConv);
}
Ark_Number GetShadowColorImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_Number>(static_cast<int32_t>(Color::TRANSPARENT.GetValue()));
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto shadow = ViewAbstract::GetShadow(Referenced::RawPtr(frameNode));
    if (shadow.has_value()) {
        auto color = shadow.value().GetColor();
        return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(color.GetValue()));
    }
    return errorValue;
}
void SetShadowColorImpl(Ark_RenderNode peer, const Ark_Number* shadowColor)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetShadowColor !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(shadowColor);

    auto colorConv = Converter::Convert<int32_t>(*shadowColor);
    auto shadow = ViewAbstract::GetShadow(Referenced::RawPtr(frameNode));
    if (shadow.has_value()) {
        auto color = Color(colorConv);
        if (peer->shadowAlpha.has_value()) {
            color = color.ChangeAlpha(peer->shadowAlpha.value());
        }
        shadow->SetColor(color);
        std::vector<Shadow> shadows { shadow.value() };
        ViewAbstractModelStatic::SetBackShadow(Referenced::RawPtr(frameNode), shadows);
    }
}
Ark_Vector2 GetShadowOffsetImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_Vector2>(Offset(0, 0));
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto shadow = ViewAbstract::GetShadow(Referenced::RawPtr(frameNode));
    if (shadow.has_value()) {
        auto offset = shadow.value().GetOffset();
        return Converter::ArkValue<Ark_Vector2>(offset);
    }
    return errorValue;
}
void SetShadowOffsetImpl(Ark_RenderNode peer, const Ark_Vector2* shadowOffset, const Ark_Int32 unitValue)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetShadowOffset !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(shadowOffset);

    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    auto offsetConv = Converter::Convert<Offset>(*shadowOffset);
    auto shadow = ViewAbstract::GetShadow(Referenced::RawPtr(frameNode));
    if (shadow.has_value()) {
        Dimension first = Dimension(offsetConv.GetX(), unit);
        Dimension second = Dimension(offsetConv.GetY(), unit);
        shadow->SetOffset(Offset(first.ConvertToPx(), second.ConvertToPx()));
        std::vector<Shadow> shadows { shadow.value() };
        ViewAbstractModelStatic::SetBackShadow(Referenced::RawPtr(frameNode), shadows);
    }
}
Ark_String GetLabelImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_String>("", Converter::FC);
    CHECK_NULL_RETURN(peer, errorValue);
    return Converter::ArkValue<Ark_String>(peer->label, Converter::FC);
}
void SetLabelImpl(Ark_RenderNode peer, const Ark_String* label)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetLabel !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(label);
    auto labelConv = Converter::Convert<std::string>(*label);
    auto pattern = frameNode->GetPattern<NG::RenderNodePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetLabel(labelConv);
    peer->label = labelConv;
}
Ark_Number GetShadowAlphaImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errorValue);
    if (peer->shadowAlpha.has_value()) {
        return Converter::ArkValue<Ark_Number>(peer->shadowAlpha.value());
    }
    return errorValue;
}
void SetShadowAlphaImpl(Ark_RenderNode peer, const Ark_Number* shadowAlpha)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetShadowAlpha !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(shadowAlpha);

    auto alphaConv = Converter::Convert<uint32_t>(*shadowAlpha);
    peer->shadowAlpha = alphaConv;
    auto shadow = ViewAbstract::GetShadow(Referenced::RawPtr(frameNode));
    if (shadow.has_value()) {
        auto color = shadow.value().GetColor();
        if (peer->shadowAlpha.has_value()) {
            color = color.ChangeAlpha(peer->shadowAlpha.value());
        }
        shadow->SetColor(color);
        std::vector<Shadow> shadows { shadow.value() };
        ViewAbstractModelStatic::SetBackShadow(Referenced::RawPtr(frameNode), shadows);
    }
}
Ark_Number GetShadowElevationImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_Number>(0.f);
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto shadow = ViewAbstract::GetShadow(Referenced::RawPtr(frameNode));
    if (shadow.has_value()) {
        auto elevation = shadow.value().GetElevation();
        return Converter::ArkValue<Ark_Number>(elevation);
    }
    return errorValue;
}
void SetShadowElevationImpl(Ark_RenderNode peer, const Ark_Number* shadowElevation)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetShadowElevation !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(shadowElevation);

    auto elevationConv = Converter::Convert<float>(*shadowElevation);
    auto shadow = ViewAbstract::GetShadow(Referenced::RawPtr(frameNode));
    if (shadow.has_value()) {
        shadow->SetElevation(elevationConv);
        std::vector<Shadow> shadows { shadow.value() };
        ViewAbstractModelStatic::SetBackShadow(Referenced::RawPtr(frameNode), shadows);
    }
}
Ark_Number GetShadowRadiusImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_Number>(0.f);
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto shadow = ViewAbstract::GetShadow(Referenced::RawPtr(frameNode));
    if (shadow.has_value()) {
        auto radius = shadow.value().GetBlurRadius();
        return Converter::ArkValue<Ark_Number>(radius);
    }
    return errorValue;
}
void SetShadowRadiusImpl(Ark_RenderNode peer, const Ark_Number* shadowRadius)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetShadowRadius !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(shadowRadius);

    auto radiusConv = Converter::Convert<float>(*shadowRadius);
    auto shadow = ViewAbstract::GetShadow(Referenced::RawPtr(frameNode));
    if (shadow.has_value()) {
        shadow->SetBlurRadius(radiusConv);
        std::vector<Shadow> shadows { shadow.value() };
        ViewAbstractModelStatic::SetBackShadow(Referenced::RawPtr(frameNode), shadows);
    }
}
Ark_EdgeStyles GetBorderStyleImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_EdgeStyles>(BorderStyleProperty());
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto value = ViewAbstract::GetBorderStyle(Referenced::RawPtr(frameNode));
    return Converter::ArkValue<Ark_EdgeStyles>(value);
}
void SetBorderStyleImpl(Ark_RenderNode peer, const Ark_EdgeStyles* borderStyle)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetBorderStyle !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(borderStyle);

    auto value = Converter::Convert<BorderStyleProperty>(*borderStyle);
    ViewAbstractModelStatic::SetBorderStyle(Referenced::RawPtr(frameNode), value);
}
Ark_EdgesNumber GetBorderWidthImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_EdgesNumber>(BorderWidthProperty());
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto value = ViewAbstract::GetBorderWidth(Referenced::RawPtr(frameNode));
    return Converter::ArkValue<Ark_EdgesNumber>(value);
}
void SetBorderWidthImpl(Ark_RenderNode peer, const Ark_EdgesNumber* borderWidth, const Ark_Int32 unitValue)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetBorderWidth !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(borderWidth);

    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    auto value = Converter::Convert<BorderWidthProperty>(*borderWidth);
    if (value.leftDimen) {
        value.leftDimen->SetUnit(unit);
    }
    if (value.topDimen) {
        value.topDimen->SetUnit(unit);
    }
    if (value.rightDimen) {
        value.rightDimen->SetUnit(unit);
    }
    if (value.bottomDimen) {
        value.bottomDimen->SetUnit(unit);
    }
    ViewAbstractModelStatic::SetBorderWidth(Referenced::RawPtr(frameNode), value);
}
Ark_EdgesNumber GetBorderColorImpl(Ark_RenderNode peer)
{
    Color defaultColor(0xff000000);
    BorderColorProperty borderColors = {
        defaultColor, defaultColor, defaultColor, defaultColor, std::nullopt, std::nullopt
    };
    auto errorValue = Converter::ArkValue<Ark_EdgesNumber>(borderColors);
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto value = ViewAbstract::GetBorderColor(Referenced::RawPtr(frameNode));
    return Converter::ArkValue<Ark_EdgesNumber>(value);
}
void SetBorderColorImpl(Ark_RenderNode peer, const Ark_EdgesNumber* borderColor)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetBorderColor !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(borderColor);

    auto value = Converter::Convert<BorderColorProperty>(*borderColor);
    ViewAbstractModelStatic::SetBorderColor(Referenced::RawPtr(frameNode), value);
}
Ark_BorderRadiuses_graphics GetBorderRadiusImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_BorderRadiuses_graphics>(BorderRadiusProperty());
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto value = ViewAbstract::GetBorderRadius(Referenced::RawPtr(frameNode));
    return Converter::ArkValue<Ark_BorderRadiuses_graphics>(value);
}
void SetBorderRadiusImpl(Ark_RenderNode peer, const Ark_BorderRadiuses_graphics* borderRadius, Ark_Int32 unitValue)
{
    if (!peer) {
        LOGW("This renderNode is nullptr when SetBorderRadius !");
        return;
    }

    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    CHECK_NULL_VOID(borderRadius);

    DimensionUnit unit = ConvertLengthMetricsUnitToDimensionUnit(unitValue, DimensionUnit::VP);
    auto value = Converter::Convert<BorderRadiusProperty>(*borderRadius);
    if (value.radiusTopLeft) {
        value.radiusTopLeft->SetUnit(unit);
    }
    if (value.radiusTopRight) {
        value.radiusTopRight->SetUnit(unit);
    }
    if (value.radiusBottomRight) {
        value.radiusBottomRight->SetUnit(unit);
    }
    if (value.radiusBottomLeft) {
        value.radiusBottomLeft->SetUnit(unit);
    }
    ViewAbstractModelStatic::SetBorderRadius(Referenced::RawPtr(frameNode), value);
}
Ark_ShapeMask GetShapeMaskImpl(Ark_RenderNode peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto value = ViewAbstract::GetMask(Referenced::RawPtr(frameNode));
    return PeerUtils::CreatePeer<ShapeMaskPeer>(value);
}
void SetShapeMaskImpl(Ark_RenderNode peer, Ark_ShapeMask shapeMask)
{
    CHECK_NULL_VOID(peer && shapeMask);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    auto value = GetBasicShape(shapeMask);
    ViewAbstract::SetMask(Referenced::RawPtr(frameNode), value);
}
Ark_ShapeClip GetShapeClipImpl(Ark_RenderNode peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto value = ViewAbstract::GetClipShape(Referenced::RawPtr(frameNode));
    return PeerUtils::CreatePeer<ShapeClipPeer>(value);
}
void SetShapeClipImpl(Ark_RenderNode peer, Ark_ShapeClip shapeClip)
{
    CHECK_NULL_VOID(peer && shapeClip);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");
    auto value = GetBasicShape(shapeClip);
    ViewAbstract::SetClipShape(Referenced::RawPtr(frameNode), value);
}
Ark_Boolean GetMarkNodeGroupImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_Boolean>(false);
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    auto isRenderGroup = ViewAbstract::GetRenderGroup(Referenced::RawPtr(frameNode));
    return Converter::ArkValue<Ark_Boolean>(isRenderGroup);
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
    CHECK_NULL_VOID(frameNode->GetTag() != "BuilderProxyNode");

    frameNode->SetApplicationRenderGroupMarked(isNodeGroup);
    ViewAbstract::SetRenderGroup(Referenced::RawPtr(frameNode), isNodeGroup);
}
Ark_LengthMetricsUnit GetLengthMetricsUnitImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_LengthMetricsUnit>(OHOS::Ace::NG::LengthMetricsUnit::DEFAULT);
    CHECK_NULL_RETURN(peer, errorValue);
    auto frameNode = peer->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, errorValue);
    return Converter::ArkValue<Ark_LengthMetricsUnit>(peer->lengthMetricsUnit);
}
void SetLengthMetricsUnitImpl(Ark_RenderNode peer, Ark_LengthMetricsUnit lengthMetricsUnit)
{
    CHECK_NULL_VOID(peer);
    auto value = Converter::OptConvert<OHOS::Ace::NG::LengthMetricsUnit>(lengthMetricsUnit);
    peer->lengthMetricsUnit = value.has_value() ? value.value() : OHOS::Ace::NG::LengthMetricsUnit::DEFAULT;
}
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
