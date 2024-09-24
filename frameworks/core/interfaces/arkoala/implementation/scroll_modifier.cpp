/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollInterfaceModifier {
void SetScrollOptionsImpl(Ark_NativePointer node,
                          const Opt_Scroller* scroller)
{
}
} // ScrollInterfaceModifier
namespace ScrollAttributeModifier {

namespace {
inline void AssignCast(OffsetT<CalcDimension>& dst, const Ark_OffsetOptions& value)
{
    std::optional<CalcDimension> xOffset;
    Converter::AssignOptionalTo(xOffset, value.xOffset);
    std::optional<CalcDimension> yOffset;
    Converter::AssignOptionalTo(yOffset, value.yOffset);
    if (xOffset.has_value())
    {
        dst.SetX(xOffset.value());
    }
    if (yOffset.has_value())
    {
        dst.SetY(yOffset.value());
    }
}
}

void ScrollableImpl(Ark_NativePointer node,
                    enum Ark_ScrollDirection value)
{
}
void OnScrollImpl(Ark_NativePointer node,
                  Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode](Dimension xOffset, Dimension yOffset) {
        Ark_Number _xOffset;
        Ark_Number _yOffset;
        Converter::AssignArkValue(_xOffset, xOffset);
        Converter::AssignArkValue(_yOffset, yOffset);
        GetFullAPI()->getEventsAPI()->getScrollEventsReceiver()->
            onScroll(frameNode->GetId(), _xOffset, _yOffset);
    };
    ScrollModelNG::SetOnScroll(frameNode, onEvent);
}
void OnWillScrollImpl(Ark_NativePointer node,
                      const Ark_CustomObject* stub_for_onWillScroll)
{
}
void OnDidScrollImpl(Ark_NativePointer node,
                     Ark_Function handler)
{
}
void OnScrollEdgeImpl(Ark_NativePointer node,
                      Ark_Function event)
{
}
void OnScrollStartImpl(Ark_NativePointer node,
                       Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getScrollEventsReceiver()->
            onScrollStart(frameNode->GetId());
    };
    ScrollModelNG::SetOnScrollStart(frameNode, onEvent);
}
void OnScrollEndImpl(Ark_NativePointer node,
                     Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getScrollEventsReceiver()->
            onScrollEnd(frameNode->GetId());
    };
    ScrollModelNG::SetOnScrollEnd(frameNode, onEvent);
}
void OnScrollStopImpl(Ark_NativePointer node,
                      Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getScrollEventsReceiver()->
            onScrollStop(frameNode->GetId());
    };
    ScrollModelNG::SetOnScrollStop(frameNode, onEvent);
}
void ScrollBarImpl(Ark_NativePointer node,
                   enum Ark_BarState barState)
{
}
void ScrollBarColorImpl(Ark_NativePointer node,
                        const Type_ScrollAttribute_scrollBarColor_Arg0* color)
{
}
void ScrollBarWidthImpl(Ark_NativePointer node,
                        const Type_ScrollAttribute_scrollBarWidth_Arg0* value)
{
}
void EdgeEffectImpl(Ark_NativePointer node,
                    enum Ark_EdgeEffect edgeEffect,
                    const Opt_EdgeEffectOptions* options)
{
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            Ark_Function event)
{
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_NestedScrollOptions* value)
{
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
}
void FrictionImpl(Ark_NativePointer node,
                  const Type_ScrollAttribute_friction_Arg0* value)
{
}
void ScrollSnapImpl(Ark_NativePointer node,
                    const Ark_ScrollSnapOptions* value)
{
}
void EnablePagingImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetEnablePaging(frameNode, value);
}
void InitialOffsetImpl(Ark_NativePointer node,
                       const Ark_OffsetOptions* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OffsetT<CalcDimension> offset;
    AssignCast(offset, *value);
    ScrollModelNG::SetInitialOffset(frameNode, offset);
}
} // ScrollAttributeModifier
const GENERATED_ArkUIScrollModifier* GetScrollModifier()
{
    static const GENERATED_ArkUIScrollModifier ArkUIScrollModifierImpl {
        ScrollInterfaceModifier::SetScrollOptionsImpl,
        ScrollAttributeModifier::ScrollableImpl,
        ScrollAttributeModifier::OnScrollImpl,
        ScrollAttributeModifier::OnWillScrollImpl,
        ScrollAttributeModifier::OnDidScrollImpl,
        ScrollAttributeModifier::OnScrollEdgeImpl,
        ScrollAttributeModifier::OnScrollStartImpl,
        ScrollAttributeModifier::OnScrollEndImpl,
        ScrollAttributeModifier::OnScrollStopImpl,
        ScrollAttributeModifier::ScrollBarImpl,
        ScrollAttributeModifier::ScrollBarColorImpl,
        ScrollAttributeModifier::ScrollBarWidthImpl,
        ScrollAttributeModifier::EdgeEffectImpl,
        ScrollAttributeModifier::OnScrollFrameBeginImpl,
        ScrollAttributeModifier::NestedScrollImpl,
        ScrollAttributeModifier::EnableScrollInteractionImpl,
        ScrollAttributeModifier::FrictionImpl,
        ScrollAttributeModifier::ScrollSnapImpl,
        ScrollAttributeModifier::EnablePagingImpl,
        ScrollAttributeModifier::InitialOffsetImpl,
    };
    return &ArkUIScrollModifierImpl;
}

}
