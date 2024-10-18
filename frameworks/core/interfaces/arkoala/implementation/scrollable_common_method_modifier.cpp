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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollableCommonMethodModifier {
void ScrollBarImpl(Ark_NativePointer node,
                   Ark_BarState barState)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(barState);
    //auto convValue = Converter::OptConvert<type>(barState); // for enums
    //ScrollableCommonMethodModelNG::SetScrollBar(frameNode, convValue);
}
void ScrollBarColorImpl(Ark_NativePointer node,
                        const Ark_Union_Color_Number_String* color)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(color);
    //auto convValue = Converter::OptConvert<type_name>(*color);
    //ScrollableCommonMethodModelNG::SetScrollBarColor(frameNode, convValue);
}
void ScrollBarWidthImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ScrollableCommonMethodModelNG::SetScrollBarWidth(frameNode, convValue);
}
void EdgeEffectImpl(Ark_NativePointer node,
                    Ark_EdgeEffect edgeEffect,
                    const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(edgeEffect);
    //auto convValue = Converter::OptConvert<type>(edgeEffect); // for enums
    //ScrollableCommonMethodModelNG::SetEdgeEffect(frameNode, convValue);
}
void FadingEdgeImpl(Ark_NativePointer node,
                    const Opt_Boolean* enabled,
                    const Opt_FadingEdgeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(enabled);
    //auto convValue = Converter::OptConvert<type>(enabled); // for enums
    //ScrollableCommonMethodModelNG::SetFadingEdge(frameNode, convValue);
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ScrollableCommonMethodModelNG::SetNestedScroll(frameNode, convValue);
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //ScrollableCommonMethodModelNG::SetEnableScrollInteraction(frameNode, convValue);
}
void FrictionImpl(Ark_NativePointer node,
                  const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ScrollableCommonMethodModelNG::SetFriction(frameNode, convValue);
}
void OnScrollImpl(Ark_NativePointer node,
                  Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //ScrollableCommonMethodModelNG::SetOnScroll(frameNode, convValue);
}
void OnDidScrollImpl(Ark_NativePointer node,
                     Ark_Function handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //ScrollableCommonMethodModelNG::SetOnDidScroll(frameNode, convValue);
}
void OnReachStartImpl(Ark_NativePointer node,
                      Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //ScrollableCommonMethodModelNG::SetOnReachStart(frameNode, convValue);
}
void OnReachEndImpl(Ark_NativePointer node,
                    Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //ScrollableCommonMethodModelNG::SetOnReachEnd(frameNode, convValue);
}
void OnScrollStartImpl(Ark_NativePointer node,
                       Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //ScrollableCommonMethodModelNG::SetOnScrollStart(frameNode, convValue);
}
void OnScrollStopImpl(Ark_NativePointer node,
                      Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //ScrollableCommonMethodModelNG::SetOnScrollStop(frameNode, convValue);
}
void FlingSpeedLimitImpl(Ark_NativePointer node,
                         const Ark_Number* speedLimit)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(speedLimit);
    //auto convValue = Converter::OptConvert<type_name>(*speedLimit);
    //ScrollableCommonMethodModelNG::SetFlingSpeedLimit(frameNode, convValue);
}
} // ScrollableCommonMethodModifier
const GENERATED_ArkUIScrollableCommonMethodModifier* GetScrollableCommonMethodModifier()
{
    static const GENERATED_ArkUIScrollableCommonMethodModifier ArkUIScrollableCommonMethodModifierImpl {
        ScrollableCommonMethodModifier::ScrollBarImpl,
        ScrollableCommonMethodModifier::ScrollBarColorImpl,
        ScrollableCommonMethodModifier::ScrollBarWidthImpl,
        ScrollableCommonMethodModifier::EdgeEffectImpl,
        ScrollableCommonMethodModifier::FadingEdgeImpl,
        ScrollableCommonMethodModifier::NestedScrollImpl,
        ScrollableCommonMethodModifier::EnableScrollInteractionImpl,
        ScrollableCommonMethodModifier::FrictionImpl,
        ScrollableCommonMethodModifier::OnScrollImpl,
        ScrollableCommonMethodModifier::OnDidScrollImpl,
        ScrollableCommonMethodModifier::OnReachStartImpl,
        ScrollableCommonMethodModifier::OnReachEndImpl,
        ScrollableCommonMethodModifier::OnScrollStartImpl,
        ScrollableCommonMethodModifier::OnScrollStopImpl,
        ScrollableCommonMethodModifier::FlingSpeedLimitImpl,
    };
    return &ArkUIScrollableCommonMethodModifierImpl;
}

}
