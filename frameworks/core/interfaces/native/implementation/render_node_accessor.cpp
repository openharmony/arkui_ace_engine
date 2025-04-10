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

#include "base/geometry/size.h"
#include "core/interfaces/native/implementation/render_node_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
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
TranslateOptions Convert(const Ark_Vector2& value)
{
    return {
        Converter::Convert<CalcDimension>(value.x),
        Converter::Convert<CalcDimension>(value.y),
        CalcDimension(0.f)
    };
}

void AssignArkValue(Ark_Vector2& dst, const DimensionOffset& src)
{
    dst.x = Converter::ArkValue<Ark_Number>(src.GetX());
    dst.y = Converter::ArkValue<Ark_Number>(src.GetY());
}

void AssignArkValue(Ark_Vector2& dst, const VectorF& src)
{
    dst.x = Converter::ArkValue<Ark_Number>(src.x);
    dst.y = Converter::ArkValue<Ark_Number>(src.y);
}

void AssignArkValue(Ark_Vector2& dst, const TranslateOptions& src)
{
    dst.x = Converter::ArkValue<Ark_Number>(src.x);
    dst.y = Converter::ArkValue<Ark_Number>(src.y);
}

void AssignArkValue(Ark_Vector3& dst, const Vector3F& src)
{
    dst.x = Converter::ArkValue<Ark_Number>(src.x);
    dst.y = Converter::ArkValue<Ark_Number>(src.y);
    dst.z = Converter::ArkValue<Ark_Number>(src.z);
}

void AssignArkValue(Ark_Matrix4& dst, const Matrix4& src)
{
    constexpr int32_t index_0 = 0;
    constexpr int32_t index_1 = 1;
    constexpr int32_t index_2 = 2;
    constexpr int32_t index_3 = 3;
    dst.value0 = Converter::ArkValue<Ark_Number>(src.Get(index_0, index_0));
    dst.value1 = Converter::ArkValue<Ark_Number>(src.Get(index_0, index_1));
    dst.value2 = Converter::ArkValue<Ark_Number>(src.Get(index_0, index_2));
    dst.value3 = Converter::ArkValue<Ark_Number>(src.Get(index_0, index_3));
    dst.value4 = Converter::ArkValue<Ark_Number>(src.Get(index_1, index_0));
    dst.value5 = Converter::ArkValue<Ark_Number>(src.Get(index_1, index_1));
    dst.value6 = Converter::ArkValue<Ark_Number>(src.Get(index_1, index_2));
    dst.value7 = Converter::ArkValue<Ark_Number>(src.Get(index_1, index_3));
    dst.value8 = Converter::ArkValue<Ark_Number>(src.Get(index_2, index_0));
    dst.value9 = Converter::ArkValue<Ark_Number>(src.Get(index_2, index_1));
    dst.value10 = Converter::ArkValue<Ark_Number>(src.Get(index_2, index_2));
    dst.value11 = Converter::ArkValue<Ark_Number>(src.Get(index_2, index_3));
    dst.value12 = Converter::ArkValue<Ark_Number>(src.Get(index_3, index_0));
    dst.value13 = Converter::ArkValue<Ark_Number>(src.Get(index_3, index_1));
    dst.value14 = Converter::ArkValue<Ark_Number>(src.Get(index_3, index_2));
    dst.value15 = Converter::ArkValue<Ark_Number>(src.Get(index_3, index_3));
}

void AssignArkValue(Ark_BorderStyle& dst, const BorderStyle& src)
{
    switch (src) {
        case OHOS::Ace::BorderStyle::SOLID: dst = ARK_BORDER_STYLE_SOLID; break;
        case OHOS::Ace::BorderStyle::DASHED: dst = ARK_BORDER_STYLE_DASHED; break;
        case OHOS::Ace::BorderStyle::DOTTED: dst = ARK_BORDER_STYLE_DOTTED; break;
        default: dst = static_cast<Ark_BorderStyle>(-1);
    }
}

void AssignArkValue(Ark_EdgeStyles& dst, const BorderStyleProperty& src)
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
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RenderNodeAccessor {
RefPtr<FrameNode> GetParentNode(RefPtr<FrameNode>& nodeRef)
{
    CHECK_NULL_RETURN(nodeRef, nullptr);
    auto parent = nodeRef->GetParent();
    while (parent != nullptr && !AceType::InstanceOf<FrameNode>(parent)) {
        parent = parent->GetParent();
    }
    return (parent == nullptr || parent->GetTag() == V2::PAGE_ETS_TAG || parent->GetTag() == V2::STAGE_ETS_TAG)
               ? nullptr : AceType::DynamicCast<FrameNode>(parent);
}

RefPtr<RenderContext> GetRenderContext(RefPtr<FrameNode>& node, bool checkProxy = true)
{
    CHECK_NULL_RETURN(node, nullptr);
    if (checkProxy) {
        CHECK_NULL_RETURN(node->GetTag() != "BuilderProxyNode", nullptr);
    }
    return node->GetRenderContext();
}

void DestroyPeerImpl(Ark_RenderNode peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_RenderNode CtorImpl()
{
    return PeerUtils::CreatePeer<RenderNodePeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void AppendChildImpl(Ark_RenderNode peer,
                     Ark_RenderNode node)
{
    CHECK_NULL_VOID(peer && peer->node);
    auto currentNodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentNodeRef);

    CHECK_NULL_VOID(node);
    auto childNodeRef = AceType::DynamicCast<UINode>(node->node);
    CHECK_NULL_VOID(childNodeRef);
    if (childNodeRef->GetParent() != nullptr) {
        return;
    }

    currentNodeRef->AddChild(childNodeRef);
    currentNodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void InsertChildAfterImpl(Ark_RenderNode peer,
                          Ark_RenderNode child,
                          const Ark_Union_RenderNode_Undefined* sibling)
{
    CHECK_NULL_VOID(peer && peer->node);
    auto currentNodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentNodeRef);

    CHECK_NULL_VOID(child);
    auto childNode = AceType::DynamicCast<UINode>(child->node);
    CHECK_NULL_VOID(childNode);
    if (childNode->GetParent() != nullptr) {
        return;
    }
    CHECK_NULL_VOID(sibling);
    auto siblingOpt = Converter::OptConvert<RenderNodePeer*>(*sibling);
    auto index = -1;
    if (siblingOpt.has_value()) {
        auto siblingNode = AceType::DynamicCast<UINode>(siblingOpt.value()->node);
        index = currentNodeRef->GetChildIndex(siblingNode);
    }

    currentNodeRef->AddChild(childNode, index + 1);
    currentNodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void RemoveChildImpl(Ark_RenderNode peer,
                     Ark_RenderNode node)
{
    CHECK_NULL_VOID(peer && peer->node);
    auto currentNodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentNodeRef);

    CHECK_NULL_VOID(node);
    auto childNode = AceType::DynamicCast<UINode>(node->node);
    CHECK_NULL_VOID(childNode);

    currentNodeRef->RemoveChild(childNode);
    currentNodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void ClearChildrenImpl(Ark_RenderNode peer)
{
    CHECK_NULL_VOID(peer && peer->node);
    auto currentNodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentNodeRef);

    currentNodeRef->Clean();
    currentNodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
Ark_Union_RenderNode_Undefined GetChildImpl(Ark_RenderNode peer,
                                            const Ark_Number* index)
{
    auto errorValue = Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_Undefined>(Ark_Undefined{});
    CHECK_NULL_RETURN(peer && peer->node && index, errorValue);
    auto indexInt = Converter::Convert<int32_t>(*index);
    CHECK_NULL_RETURN(indexInt >= 0, errorValue);
    LOGW("FrameNodeAccessor::GetChildImpl work only for case: IsExpanded is false");
    auto retValue = PeerUtils::CreatePeer<RenderNodePeer>(
        peer->node->GetFrameNodeChildByIndex(indexInt, false, false));
    return Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_RenderNode>(retValue);
}
Ark_Union_RenderNode_Undefined GetFirstChildImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_Undefined>(Ark_Undefined{});
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto child = peer->node->GetFirstChild();
    CHECK_NULL_RETURN(child, errorValue);
    auto retValue = PeerUtils::CreatePeer<RenderNodePeer>(AceType::DynamicCast<FrameNode>(child));
    return Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_RenderNode>(retValue);
}
Ark_Union_RenderNode_Undefined GetNextSiblingImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_Undefined>(Ark_Undefined{});
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto parent = GetParentNode(peer->node);
    CHECK_NULL_RETURN(parent, errorValue);
    LOGW("RenderNodeAccessor::GetNextSiblingImpl work only for case: IsExpanded is false");
    auto index = parent->GetFrameNodeIndex(peer->node, false);
    CHECK_NULL_RETURN(index >= 0, errorValue);
    auto sibling = parent->GetFrameNodeChildByIndex(index + 1, false, false);
    auto retValue = PeerUtils::CreatePeer<RenderNodePeer>(sibling);
    return Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_RenderNode>(retValue);
}
Ark_Union_RenderNode_Undefined GetPreviousSiblingImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_Undefined>(Ark_Undefined{});
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto parent = GetParentNode(peer->node);
    CHECK_NULL_RETURN(parent, errorValue);
    LOGW("RenderNodeAccessor::GetPreviousSiblingImpl work only for case: IsExpanded is false");
    auto index = parent->GetFrameNodeIndex(peer->node, false);
    CHECK_NULL_RETURN(index > 0, errorValue);
    auto sibling = parent->GetFrameNodeChildByIndex(index - 1, false, false);
    auto retValue = PeerUtils::CreatePeer<RenderNodePeer>(sibling);
    return Converter::ArkUnion<Ark_Union_RenderNode_Undefined, Ark_RenderNode>(retValue);
}
void DrawImpl(Ark_RenderNode peer,
              const Ark_DrawContext* context)
{
    LOGW("RenderNodeAccessor::DrawImpl is not implemented.");
}
void InvalidateImpl(Ark_RenderNode peer)
{
    CHECK_NULL_VOID(peer && peer->node);
    auto pattern = peer->node->GetPattern<RenderNodePattern>();
    CHECK_NULL_VOID(pattern);
    auto renderContext = GetRenderContext(peer->node);
    CHECK_NULL_VOID(renderContext);
    pattern->Invalidate();
    renderContext->RequestNextFrame();
}
void DisposeImpl(Ark_RenderNode peer)
{
    CHECK_NULL_VOID(peer && peer->node);
    auto currentNodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentNodeRef);
    auto parent = GetParentNode(peer->node);
    CHECK_NULL_VOID(parent);
    parent->RemoveChild(currentNodeRef);
    parent->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
Ark_Number GetBackgroundColorImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_Number>(static_cast<int32_t>(Color::TRANSPARENT.GetValue()));
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto retValue = ViewAbstract::GetBackgroundColor(Referenced::RawPtr(peer->node));
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(retValue.GetValue()));
}
void SetBackgroundColorImpl(Ark_RenderNode peer,
                            const Ark_Number* backgroundColor)
{
    CHECK_NULL_VOID(peer && peer->node && backgroundColor);
    auto colorConv = Converter::Convert<int32_t>(*backgroundColor);
    ViewAbstract::SetBackgroundColor(Referenced::RawPtr(peer->node), Color(colorConv));
}
Ark_Boolean GetClipToFrameImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_Boolean>(true);
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto clipValue = ViewAbstract::GetClip(Referenced::RawPtr(peer->node)); // false by default
    return Converter::ArkValue<Ark_Boolean>(clipValue);
}
void SetClipToFrameImpl(Ark_RenderNode peer,
                        Ark_Boolean clipToFrame)
{
    CHECK_NULL_VOID(peer && peer->node);
    auto clipConv = Converter::Convert<bool>(clipToFrame);
    ViewAbstract::SetClipEdge(Referenced::RawPtr(peer->node), clipConv);
}
Ark_Number GetOpacityImpl(Ark_RenderNode peer)
{
     // 1.f by default
    auto errorValue = Converter::ArkValue<Ark_Number>(1.f);
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto opacityValue = ViewAbstract::GetOpacity(Referenced::RawPtr(peer->node));
    return Converter::ArkValue<Ark_Number>(static_cast<float>(opacityValue));
}
void SetOpacityImpl(Ark_RenderNode peer,
                    const Ark_Number* opacity)
{
    CHECK_NULL_VOID(peer && peer->node && opacity);
    auto opacityConv = Converter::Convert<float>(*opacity);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (GreatNotEqual(opacityConv, 1.0f) || LessNotEqual(opacityConv, 0.0f)) {
            opacityConv = 1.0f;
        }
    } else {
        opacityConv = std::clamp(opacityConv, 0.0f, 1.0f);
    }
    ViewAbstract::SetOpacity(Referenced::RawPtr(peer->node), opacityConv);
}
Ark_Size GetSizeImpl(Ark_RenderNode peer)
{
    Ark_Size retValue = {
        .width = Converter::ArkValue<Ark_Number>(0.f),
        .height = Converter::ArkValue<Ark_Number>(0.f),
    };

    CHECK_NULL_RETURN(peer && peer->node, retValue);
    auto currentNodeRef = AceType::DynamicCast<FrameNode>(peer->node);
    CHECK_NULL_RETURN(currentNodeRef, retValue);
    auto layoutProperty = currentNodeRef->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, retValue);

    auto calcSizeConv = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    if (calcSizeConv.has_value()) {
        auto width = calcSizeConv.value().Width().value_or(CalcLength()).GetDimension();
        auto height = calcSizeConv.value().Height().value_or(CalcLength()).GetDimension();
        retValue = {
            .width = Converter::ArkValue<Ark_Number>(width),
            .height = Converter::ArkValue<Ark_Number>(height)
        };
    }
    return retValue;
}
void SetSizeImpl(Ark_RenderNode peer,
                 const Ark_Size* size)
{
    CHECK_NULL_VOID(peer && peer->node && size);
    auto currentNodeRef = AceType::DynamicCast<FrameNode>(peer->node);
    CHECK_NULL_VOID(currentNodeRef);
    CHECK_NULL_VOID(currentNodeRef->GetTag() != "BuilderProxyNode");
    auto layoutProperty = currentNodeRef->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);

    auto sizeConv = Converter::Convert<Size>(*size);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(
        CalcLength(sizeConv.Width(), DimensionUnit::VP), CalcLength(sizeConv.Height(), DimensionUnit::VP)));
    currentNodeRef->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
}
Ark_Position GetPositionImpl(Ark_RenderNode peer)
{
    auto defaultPosition = OffsetT<Dimension>(Dimension(0, DimensionUnit::VP), Dimension(0, DimensionUnit::VP));
    auto errorValue = Converter::ArkValue<Ark_Position>(defaultPosition);
    CHECK_NULL_RETURN(peer && peer->node, errorValue);

    auto positionValue = ViewAbstract::GetPosition(Referenced::RawPtr(peer->node));
    return Converter::ArkValue<Ark_Position>(positionValue);
}
void SetPositionImpl(Ark_RenderNode peer,
                     const Ark_Position* position)
{
    CHECK_NULL_VOID(peer && peer->node && position);
    auto positionConv = Converter::Convert<std::pair<Dimension, Dimension>>(*position);
    auto x = std::get<0>(positionConv);
    x.SetUnit(DimensionUnit::VP);
    auto y = std::get<1>(positionConv);
    y.SetUnit(DimensionUnit::VP);
    OffsetT<Dimension> value(x, y);
    ViewAbstract::SetPosition(Referenced::RawPtr(peer->node), value);
}
Ark_Frame GetFrameImpl(Ark_RenderNode peer)
{
    // The default value is { x: 0, y: 0, width: 0, height: 0 }.
    // used as Position + Size
    Ark_Frame retValue = {
        .x = Converter::ArkValue<Ark_Number>(0),
        .y = Converter::ArkValue<Ark_Number>(0),
        .width = Converter::ArkValue<Ark_Number>(0),
        .height = Converter::ArkValue<Ark_Number>(0)
    };

    CHECK_NULL_RETURN(peer && peer->node, retValue);

    auto currentNodeRef = AceType::DynamicCast<FrameNode>(peer->node);
    CHECK_NULL_RETURN(currentNodeRef, retValue);
    auto layoutProperty = currentNodeRef->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, retValue);

    auto calcSizeConv = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    if (calcSizeConv.has_value()) {
        auto width = calcSizeConv.value().Width().value_or(CalcLength()).GetDimension();
        auto height = calcSizeConv.value().Height().value_or(CalcLength()).GetDimension();
        retValue.width = Converter::ArkValue<Ark_Number>(width);
        retValue.height = Converter::ArkValue<Ark_Number>(height);
    };

    auto positionValue = ViewAbstract::GetPosition(Referenced::RawPtr(peer->node));
    retValue.x = Converter::ArkValue<Ark_Number>(positionValue.GetX());
    retValue.y = Converter::ArkValue<Ark_Number>(positionValue.GetY());
    return retValue;
}
void SetFrameImpl(Ark_RenderNode peer,
                  const Ark_Frame* frame)
{
    CHECK_NULL_VOID(peer && peer->node && frame);
    auto currentNodeRef = AceType::DynamicCast<FrameNode>(peer->node);
    CHECK_NULL_VOID(currentNodeRef);
    CHECK_NULL_VOID(currentNodeRef->GetTag() != "BuilderProxyNode");
    auto layoutProperty = currentNodeRef->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);

    auto frameConv = Converter::Convert<Rect>(*frame);
    OffsetT<Dimension> offset(
        Dimension(frameConv.Left(), DimensionUnit::VP), Dimension(frameConv.Top(), DimensionUnit::VP));
    ViewAbstract::SetPosition(Referenced::RawPtr(peer->node), offset);

    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(
        CalcLength(frameConv.Width(), DimensionUnit::VP), CalcLength(frameConv.Height(), DimensionUnit::VP)));
    currentNodeRef->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
}
Ark_Vector2 GetPivotImpl(Ark_RenderNode peer)
{
    // The value is a floating point number in the range [0.0, 1.0], and the default value is 0.5.
    auto defaultPivot = DimensionOffset(Dimension(0.5f), Dimension(0.5f));
    auto errorValue = Converter::ArkValue<Ark_Vector2>(defaultPivot);
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto renderContext = GetRenderContext(peer->node, false);
    CHECK_NULL_RETURN(renderContext, errorValue);
    auto pivot = renderContext->GetTransformCenterValue(defaultPivot);
    return Converter::ArkValue<Ark_Vector2>(pivot);
}
void SetPivotImpl(Ark_RenderNode peer,
                  const Ark_Vector2* pivot)
{
    CHECK_NULL_VOID(peer && peer->node && pivot);
    auto pivotConv = Converter::Convert<VectorF>(*pivot);
    auto x = GreatOrEqual(pivotConv.x, 0.f) && LessOrEqual(pivotConv.x, 1.f) ? pivotConv.x : 0.5f;
    auto y = GreatOrEqual(pivotConv.x, 0.f) && LessOrEqual(pivotConv.x, 1.f) ? pivotConv.x : 0.5f;
    ViewAbstract::SetPivot(Referenced::RawPtr(peer->node), DimensionOffset(Dimension(x), Dimension(y)));
}
Ark_Vector2 GetScaleImpl(Ark_RenderNode peer)
{
    // The default value is { x: 1, y: 1 }.
    auto errorValue = Converter::ArkValue<Ark_Vector2>(VectorF(1.f, 1.f));
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto scaleValue = ViewAbstract::GetScale(Referenced::RawPtr(peer->node));
    return Converter::ArkValue<Ark_Vector2>(scaleValue);
}
void SetScaleImpl(Ark_RenderNode peer,
                  const Ark_Vector2* scale)
{
    CHECK_NULL_VOID(peer && peer->node && scale);
    auto scaleConv = Converter::Convert<VectorF>(*scale);
    auto x = GreatOrEqual(scaleConv.x, 0.f) ? scaleConv.x : 1.f;
    auto y = GreatOrEqual(scaleConv.y, 0.f) ? scaleConv.y : 1.f;
    ViewAbstract::SetScale(Referenced::RawPtr(peer->node), VectorF(x, y));
}
Ark_Vector2 GetTranslationImpl(Ark_RenderNode peer)
{
    // The default value is { x: 0, y: 0 }.
    auto errorValue = Converter::ArkValue<Ark_Vector2>(VectorF(0.f, 0.f));
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto translateValue = ViewAbstract::GetTranslate(Referenced::RawPtr(peer->node));
    return Converter::ArkValue<Ark_Vector2>(translateValue);
}
void SetTranslationImpl(Ark_RenderNode peer,
                        const Ark_Vector2* translation)
{
    CHECK_NULL_VOID(peer && peer->node && translation);
    auto translateConv = Converter::Convert<VectorF>(*translation);
    auto x = GreatOrEqual(translateConv.x, 0.f) ? translateConv.x : 0.f;
    auto y = GreatOrEqual(translateConv.y, 0.f) ? translateConv.y : 0.f;
    ViewAbstract::SetTranslate(Referenced::RawPtr(peer->node),
        TranslateOptions(CalcDimension(x), CalcDimension(y), CalcDimension(0.f)));
}
Ark_Vector3 GetRotationImpl(Ark_RenderNode peer)
{
    // The default value is { x: 0, y: 0, z: 0}.
    auto errorValue = Converter::ArkValue<Ark_Vector3>(Vector3F(0.f, 0.f, 0.f));
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto rotateValue = ViewAbstract::GetRotate(Referenced::RawPtr(peer->node));
    return Converter::ArkValue<Ark_Vector3>(Vector3F(rotateValue.x, rotateValue.y, rotateValue.z));
}
void SetRotationImpl(Ark_RenderNode peer,
                     const Ark_Vector3* rotation)
{
    CHECK_NULL_VOID(peer && peer->node && rotation);
    auto rotationConv = Converter::Convert<Vector3F>(*rotation);
    auto x = GreatOrEqual(rotationConv.x, 0.f) ? rotationConv.x : 0.f;
    auto y = GreatOrEqual(rotationConv.y, 0.f) ? rotationConv.y : 0.f;
    auto z = GreatOrEqual(rotationConv.z, 0.f) ? rotationConv.z : 0.f;
    ViewAbstract::SetRotate(Referenced::RawPtr(peer->node), Vector5F(x, y, z, 0.f, 0.f));
}
Ark_Matrix4 GetTransformImpl(Ark_RenderNode peer)
{
    // The default value is [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1]
    auto errorValue = Converter::ArkValue<Ark_Matrix4>(
        Matrix4(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f));
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto transformValue = ViewAbstract::GetTransform(Referenced::RawPtr(peer->node));
    return Converter::ArkValue<Ark_Matrix4>(transformValue);
}
void SetTransformImpl(Ark_RenderNode peer,
                      const Ark_Matrix4* transform)
{
    CHECK_NULL_VOID(peer && peer->node && transform);
    auto transformConv = Converter::Convert<Matrix4>(*transform);
    ViewAbstract::SetTransformMatrix(Referenced::RawPtr(peer->node), transformConv);
}
Ark_Number GetShadowColorImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowColorImpl(Ark_RenderNode peer,
                        const Ark_Number* shadowColor)
{
}
Ark_Vector2 GetShadowOffsetImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowOffsetImpl(Ark_RenderNode peer,
                         const Ark_Vector2* shadowOffset)
{
    CHECK_NULL_VOID(peer && peer->node && shadowOffset);
    auto shadowOffsetConv = Converter::Convert<VectorF>(*shadowOffset);
}
Ark_String GetLabelImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_String>("", Converter::FC);
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto currentNode = AceType::DynamicCast<FrameNode>(peer->node);
    CHECK_NULL_RETURN(currentNode, errorValue);
    auto pattern = currentNode->GetPattern<NG::RenderNodePattern>();
    CHECK_NULL_RETURN(pattern, errorValue);
    auto retValue = pattern->GetLabel();
    return Converter::ArkValue<Ark_String>(retValue, Converter::FC);
}
void SetLabelImpl(Ark_RenderNode peer,
                  const Ark_String* label)
{
    CHECK_NULL_VOID(peer && peer->node && label);
    auto labelConv = Converter::Convert<std::string>(*label);
    auto currentNode = AceType::DynamicCast<FrameNode>(peer->node);
    CHECK_NULL_VOID(currentNode);
    auto pattern = currentNode->GetPattern<NG::RenderNodePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetLabel(labelConv);
}
Ark_Number GetShadowAlphaImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowAlphaImpl(Ark_RenderNode peer,
                        const Ark_Number* shadowAlpha)
{
}
Ark_Number GetShadowElevationImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowElevationImpl(Ark_RenderNode peer,
                            const Ark_Number* shadowElevation)
{
}
Ark_Number GetShadowRadiusImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowRadiusImpl(Ark_RenderNode peer,
                         const Ark_Number* shadowRadius)
{
}
Ark_EdgeStyles GetBorderStyleImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_EdgeStyles>(BorderStyleProperty());
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto styleValue = ViewAbstract::GetBorderStyle(Referenced::RawPtr(peer->node));
    return Converter::ArkValue<Ark_EdgeStyles>(styleValue);
}
void SetBorderStyleImpl(Ark_RenderNode peer,
                        const Ark_EdgeStyles* borderStyle)
{
    CHECK_NULL_VOID(peer && peer->node && borderStyle);
    auto style = Converter::Convert<BorderStyleProperty>(*borderStyle);
    ViewAbstract::SetBorderStyle(Referenced::RawPtr(peer->node), style);
}
Ark_Edges GetBorderWidthImpl(Ark_RenderNode peer)
{
    return {};
}
void SetBorderWidthImpl(Ark_RenderNode peer,
                        const Ark_Edges* borderWidth)
{
}
Ark_Edges GetBorderColorImpl(Ark_RenderNode peer)
{
    return {};
}
void SetBorderColorImpl(Ark_RenderNode peer,
                        const Ark_Edges* borderColor)
{
}
Ark_BorderRadiuses_graphics GetBorderRadiusImpl(Ark_RenderNode peer)
{
    return {};
}
void SetBorderRadiusImpl(Ark_RenderNode peer,
                         const Ark_BorderRadiuses_graphics* borderRadius)
{
}
Ark_ShapeMask GetShapeMaskImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShapeMaskImpl(Ark_RenderNode peer,
                      Ark_ShapeMask shapeMask)
{
}
Ark_ShapeClip GetShapeClipImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShapeClipImpl(Ark_RenderNode peer,
                      Ark_ShapeClip shapeClip)
{
}
Ark_Boolean GetMarkNodeGroupImpl(Ark_RenderNode peer)
{
    auto errorValue = Converter::ArkValue<Ark_Boolean>(false);
    CHECK_NULL_RETURN(peer && peer->node, errorValue);
    auto isRenderGroup = ViewAbstract::GetRenderGroup(Referenced::RawPtr(peer->node));
    return Converter::ArkValue<Ark_Boolean>(isRenderGroup);
}
void SetMarkNodeGroupImpl(Ark_RenderNode peer,
                          Ark_Boolean markNodeGroup)
{
    CHECK_NULL_VOID(peer && peer->node);
    ViewAbstract::SetRenderGroup(Converter::Convert<bool>(markNodeGroup));
}
Ark_LengthMetricsUnit GetLengthMetricsUnitImpl(Ark_RenderNode peer)
{
    return {};
}
void SetLengthMetricsUnitImpl(Ark_RenderNode peer,
                              Ark_LengthMetricsUnit lengthMetricsUnit)
{
}
} // RenderNodeAccessor
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

}
