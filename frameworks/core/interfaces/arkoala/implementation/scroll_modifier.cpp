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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
inline OffsetT<CalcDimension> Convert(const Ark_OffsetOptions& value)
{
    auto xOffset = Converter::OptConvert<CalcDimension>(value.xOffset);
    auto yOffset = Converter::OptConvert<CalcDimension>(value.yOffset);
    OffsetT<CalcDimension> dst;
    if (xOffset.has_value()) {
        dst.SetX(xOffset.value());
    }
    if (yOffset.has_value()) {
        dst.SetY(yOffset.value());
    }
    return dst;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollInterfaceModifier {
void SetScrollOptionsImpl(Ark_NativePointer node,
                          const Opt_Scroller* scroller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = scroller ? Converter::OptConvert<type>(*scroller) : std::nullopt;
    //ScrollModelNG::SetSetScrollOptions(frameNode, convValue);
}
} // ScrollInterfaceModifier
namespace ScrollAttributeModifier {

void ScrollableImpl(Ark_NativePointer node,
                    Ark_ScrollDirection value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //ScrollModelNG::SetScrollable(frameNode, convValue);
}
void OnScrollImpl(Ark_NativePointer node,
                  const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode](Dimension xOffset, Dimension yOffset) {
        auto _xOffset = Converter::ArkValue<Ark_Number>(xOffset);
        auto _yOffset = Converter::ArkValue<Ark_Number>(yOffset);
        CHECK_NULL_VOID(GetFullAPI()->getEventsAPI()->getScrollEventsReceiver()->onScroll);
        GetFullAPI()->getEventsAPI()->getScrollEventsReceiver()->
            onScroll(frameNode->GetId(), _xOffset, _yOffset);
    };
    ScrollModelNG::SetOnScroll(frameNode, onEvent);
}
void OnWillScrollImpl(Ark_NativePointer node,
                      const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
}
void OnDidScrollImpl(Ark_NativePointer node,
                     const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ScrollModelNG::SetOnDidScroll(frameNode, convValue);
}
void OnScrollEdgeImpl(Ark_NativePointer node,
                      const OnScrollEdgeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ScrollModelNG::SetOnScrollEdge(frameNode, convValue);
}
void OnScrollStartImpl(Ark_NativePointer node,
                       const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getScrollEventsReceiver()->
            onScrollStart(frameNode->GetId());
    };
    ScrollModelNG::SetOnScrollStart(frameNode, onEvent);
}
void OnScrollEndImpl(Ark_NativePointer node,
                     const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getScrollEventsReceiver()->
            onScrollEnd(frameNode->GetId());
    };
    ScrollModelNG::SetOnScrollEnd(frameNode, onEvent);
}
void OnScrollStopImpl(Ark_NativePointer node,
                      const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getScrollEventsReceiver()->
            onScrollStop(frameNode->GetId());
    };
    ScrollModelNG::SetOnScrollStop(frameNode, onEvent);
}
void ScrollBarImpl(Ark_NativePointer node,
                   Ark_BarState value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //ScrollModelNG::SetScrollBar(frameNode, convValue);
}
void ScrollBarColorImpl(Ark_NativePointer node,
                        const Ark_Union_Color_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ScrollModelNG::SetScrollBarColor(frameNode, convValue);
}
void ScrollBarWidthImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ScrollModelNG::SetScrollBarWidth(frameNode, convValue);
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            const OnScrollFrameBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ScrollModelNG::SetOnScrollFrameBegin(frameNode, convValue);
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ScrollModelNG::SetNestedScroll(frameNode, convValue);
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //ScrollModelNG::SetEnableScrollInteraction(frameNode, convValue);
}
void FrictionImpl(Ark_NativePointer node,
                  const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ScrollModelNG::SetFriction(frameNode, convValue);
}
void ScrollSnapImpl(Ark_NativePointer node,
                    const Ark_ScrollSnapOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ScrollModelNG::SetScrollSnap(frameNode, convValue);
}
void EnablePagingImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ScrollModelNG::SetEnablePaging(frameNode, Converter::Convert<bool>(value));
}
void InitialOffsetImpl(Ark_NativePointer node,
                       const Ark_OffsetOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    OffsetT<CalcDimension> offset = Converter::Convert<OffsetT<CalcDimension>>(*value);
    ScrollModelNG::SetInitialOffset(frameNode, offset);
}
void EdgeEffectImpl(Ark_NativePointer node,
                    Ark_EdgeEffect edgeEffect,
                    const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(edgeEffect);
    //auto convValue = Converter::OptConvert<type>(edgeEffect); // for enums
    //ScrollModelNG::SetEdgeEffect(frameNode, convValue);
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
        ScrollAttributeModifier::OnScrollFrameBeginImpl,
        ScrollAttributeModifier::NestedScrollImpl,
        ScrollAttributeModifier::EnableScrollInteractionImpl,
        ScrollAttributeModifier::FrictionImpl,
        ScrollAttributeModifier::ScrollSnapImpl,
        ScrollAttributeModifier::EnablePagingImpl,
        ScrollAttributeModifier::InitialOffsetImpl,
        ScrollAttributeModifier::EdgeEffectImpl,
    };
    return &ArkUIScrollModifierImpl;
}

}
