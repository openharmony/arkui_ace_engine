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
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/components_ng/pattern/scroll/scroll_model_static.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/interfaces/native/implementation/scroller_peer_impl.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // ScrollModifier
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
void SetScrollableImpl(Ark_NativePointer node,
                       const Opt_ScrollDirection* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetScrollable(frameNode, convValue);
}
void SetOnWillScrollImpl(Ark_NativePointer node,
                         const Opt_ScrollOnWillScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetOnWillScroll(frameNode, convValue);
}
void SetOnDidScrollImpl(Ark_NativePointer node,
                        const Opt_ScrollOnScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetOnDidScroll(frameNode, convValue);
}
void SetOnScrollEdgeImpl(Ark_NativePointer node,
                         const Opt_OnScrollEdgeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetOnScrollEdge(frameNode, convValue);
}
void SetOnScrollStartImpl(Ark_NativePointer node,
                          const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetOnScrollStart(frameNode, convValue);
}
void SetOnScrollStopImpl(Ark_NativePointer node,
                         const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetOnScrollStop(frameNode, convValue);
}
void SetScrollBarImpl(Ark_NativePointer node,
                      const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetScrollBar(frameNode, convValue);
}
void SetScrollBarColorImpl(Ark_NativePointer node,
                           const Opt_Union_Color_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetScrollBarColor(frameNode, convValue);
}
void SetScrollBarWidthImpl(Ark_NativePointer node,
                           const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetScrollBarWidth(frameNode, convValue);
}
void SetOnScrollFrameBeginImpl(Ark_NativePointer node,
                               const Opt_OnScrollFrameBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetOnScrollFrameBegin(frameNode, convValue);
}
void SetNestedScrollImpl(Ark_NativePointer node,
                         const Opt_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetNestedScroll(frameNode, convValue);
}
void SetEnableScrollInteractionImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetEnableScrollInteraction(frameNode, convValue);
}
void SetFrictionImpl(Ark_NativePointer node,
                     const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetFriction(frameNode, convValue);
}
void SetScrollSnapImpl(Ark_NativePointer node,
                       const Opt_ScrollSnapOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetScrollSnap(frameNode, convValue);
}
void SetEnablePagingImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetEnablePaging(frameNode, convValue);
}
void SetInitialOffsetImpl(Ark_NativePointer node,
                          const Opt_OffsetOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ScrollModelNG::SetSetInitialOffset(frameNode, convValue);
}
void SetEdgeEffectImpl(Ark_NativePointer node,
                       const Opt_EdgeEffect* edgeEffect,
                       const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto effect = Converter::OptConvert<EdgeEffect>(*edgeEffect);
    
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
    ScrollModelStatic::SetEdgeEffect(frameNode, effect, alwaysEnabled, edge);
}
} // ScrollAttributeModifier
const GENERATED_ArkUIScrollModifier* GetScrollModifier()
{
    static const GENERATED_ArkUIScrollModifier ArkUIScrollModifierImpl {
        ScrollModifier::ConstructImpl,
        ScrollInterfaceModifier::SetScrollOptionsImpl,
        ScrollAttributeModifier::SetScrollableImpl,
        ScrollAttributeModifier::SetOnWillScrollImpl,
        ScrollAttributeModifier::SetOnDidScrollImpl,
        ScrollAttributeModifier::SetOnScrollEdgeImpl,
        ScrollAttributeModifier::SetOnScrollStartImpl,
        ScrollAttributeModifier::SetOnScrollStopImpl,
        ScrollAttributeModifier::SetScrollBarImpl,
        ScrollAttributeModifier::SetScrollBarColorImpl,
        ScrollAttributeModifier::SetScrollBarWidthImpl,
        ScrollAttributeModifier::SetOnScrollFrameBeginImpl,
        ScrollAttributeModifier::SetNestedScrollImpl,
        ScrollAttributeModifier::SetEnableScrollInteractionImpl,
        ScrollAttributeModifier::SetFrictionImpl,
        ScrollAttributeModifier::SetScrollSnapImpl,
        ScrollAttributeModifier::SetEnablePagingImpl,
        ScrollAttributeModifier::SetInitialOffsetImpl,
        ScrollAttributeModifier::SetEdgeEffectImpl,
    };
    return &ArkUIScrollModifierImpl;
}

}
