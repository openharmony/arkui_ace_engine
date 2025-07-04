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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollableCommonMethodModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
void SetScrollBarImpl(Ark_NativePointer node,
                      const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetScrollBar(frameNode, convValue);
}
void SetScrollBarColorImpl(Ark_NativePointer node,
                           const Opt_Union_Color_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetScrollBarColor(frameNode, convValue);
}
void SetScrollBarWidthImpl(Ark_NativePointer node,
                           const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetScrollBarWidth(frameNode, convValue);
}
void SetNestedScrollImpl(Ark_NativePointer node,
                         const Opt_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetNestedScroll(frameNode, convValue);
}
void SetEnableScrollInteractionImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetEnableScrollInteraction(frameNode, convValue);
}
void SetFrictionImpl(Ark_NativePointer node,
                     const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetFriction(frameNode, convValue);
}
void SetOnReachStartImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetOnReachStart(frameNode, convValue);
}
void SetOnReachEndImpl(Ark_NativePointer node,
                       const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetOnReachEnd(frameNode, convValue);
}
void SetOnScrollStartImpl(Ark_NativePointer node,
                          const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetOnScrollStart(frameNode, convValue);
}
void SetOnScrollStopImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetOnScrollStop(frameNode, convValue);
}
void SetFlingSpeedLimitImpl(Ark_NativePointer node,
                            const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetFlingSpeedLimit(frameNode, convValue);
}
void SetClipContentImpl(Ark_NativePointer node,
                        const Opt_Union_ContentClipMode_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetClipContent(frameNode, convValue);
}
void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                    const Opt_CrownSensitivity* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetDigitalCrownSensitivity(frameNode, convValue);
}
void SetBackToTopImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollableCommonMethodModelNG::SetSetBackToTop(frameNode, convValue);
}
void SetEdgeEffectImpl(Ark_NativePointer node,
                       const Opt_EdgeEffect* edgeEffect,
                       const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convEdgeEffect = Converter::OptConvert<EdgeEffect>(*edgeEffect);
        
    bool alwaysEnabled = true;
    EffectEdge edge = EffectEdge::ALL;
    auto edgeEffectOptions = options ? Converter::GetOpt(*options) : std::nullopt;
    if (edgeEffectOptions) {
        alwaysEnabled = Converter::Convert<bool>(edgeEffectOptions.value().alwaysEnabled);
        auto value = Converter::OptConvert<int32_t>(edgeEffectOptions.value().effectEdge);
        if (value.has_value()) {
            edge = static_cast<EffectEdge>(value.value());
        }
    }
    ScrollableModelStatic::SetEdgeEffect(frameNode, convEdgeEffect, alwaysEnabled, edge);
}
void SetFadingEdgeImpl(Ark_NativePointer node,
                       const Opt_Boolean* enabled,
                       const Opt_FadingEdgeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(enabled);
    //auto convValue = Converter::OptConvert<type>(enabled); // for enums
    //ScrollableCommonMethodModelNG::SetSetFadingEdge(frameNode, convValue);
}
} // ScrollableCommonMethodModifier
const GENERATED_ArkUIScrollableCommonMethodModifier* GetScrollableCommonMethodModifier()
{
    static const GENERATED_ArkUIScrollableCommonMethodModifier ArkUIScrollableCommonMethodModifierImpl {
        ScrollableCommonMethodModifier::ConstructImpl,
        ScrollableCommonMethodModifier::SetScrollBarImpl,
        ScrollableCommonMethodModifier::SetScrollBarColorImpl,
        ScrollableCommonMethodModifier::SetScrollBarWidthImpl,
        ScrollableCommonMethodModifier::SetNestedScrollImpl,
        ScrollableCommonMethodModifier::SetEnableScrollInteractionImpl,
        ScrollableCommonMethodModifier::SetFrictionImpl,
        ScrollableCommonMethodModifier::SetOnReachStartImpl,
        ScrollableCommonMethodModifier::SetOnReachEndImpl,
        ScrollableCommonMethodModifier::SetOnScrollStartImpl,
        ScrollableCommonMethodModifier::SetOnScrollStopImpl,
        ScrollableCommonMethodModifier::SetFlingSpeedLimitImpl,
        ScrollableCommonMethodModifier::SetClipContentImpl,
        ScrollableCommonMethodModifier::SetDigitalCrownSensitivityImpl,
        ScrollableCommonMethodModifier::SetBackToTopImpl,
        ScrollableCommonMethodModifier::SetEdgeEffectImpl,
        ScrollableCommonMethodModifier::SetFadingEdgeImpl,
    };
    return &ArkUIScrollableCommonMethodModifierImpl;
}

}
