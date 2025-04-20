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

namespace OHOS::Ace::NG {
using ListLanesType = std::variant<int, std::pair<Dimension, Dimension>>;
}

namespace OHOS::Ace::NG::Converter {
    struct ListOptions {
        std::optional<int> initialIndex;
        std::optional<Dimension> space;
        std::optional<Ark_Scroller> scroller;
    };

    struct NestedScrollModeOptions {
        std::optional<NestedScrollMode> forward;
        std::optional<NestedScrollMode> backward;
    };

    struct EdgeEffectOptions {
        std::optional<bool> alwaysEnabled;
        std::optional<EffectEdge> effectEdge;
    };

    template<>
    inline NestedScrollModeOptions Convert(const Ark_NestedScrollOptions& src)
    {
        NestedScrollModeOptions options;
        options.forward = Converter::OptConvert<NestedScrollMode>(src.scrollForward);
        options.backward = Converter::OptConvert<NestedScrollMode>(src.scrollBackward);
        return options;
    }

    template<>
    V2::ItemDivider Convert(const Ark_ListDividerOptions& src)
    {
        auto dst = V2::ItemDivider{}; // this struct is initialized by default
        dst.strokeWidth = Convert<Dimension>(src.strokeWidth);
        auto colorOpt = OptConvert<Color>(src.color);
        if (colorOpt.has_value()) {
            dst.color = colorOpt.value();
        }
        auto startMarginOpt = OptConvert<Dimension>(src.startMargin);
        if (startMarginOpt.has_value()) {
            dst.startMargin = startMarginOpt.value();
        }
        auto endMarginOpt = OptConvert<Dimension>(src.endMargin);
        if (endMarginOpt.has_value()) {
            dst.endMargin = endMarginOpt.value();
        }
        return dst;
    }

    template<>
    inline EdgeEffectOptions Convert(const Ark_EdgeEffectOptions& src)
    {
        EdgeEffectOptions options;
        options.alwaysEnabled = Converter::OptConvert<bool>(src.alwaysEnabled);
        options.effectEdge = Converter::OptConvert<EffectEdge>(src.effectEdge);
        return options;
    }

    template<>
    ChainAnimationOptions Convert(const Ark_ChainAnimationOptions& src)
    {
        auto options = ChainAnimationOptions{}; // this struct is initialized by default
        options.minSpace = Convert<Dimension>(src.minSpace);
        options.maxSpace = Convert<Dimension>(src.maxSpace);

        auto intensity = Converter::OptConvert<float>(src.intensity);
        if (intensity.has_value()) {
            options.intensity = intensity.value();
        }

        auto conductivity = Converter::OptConvert<float>(src.conductivity);
        if (conductivity.has_value()) {
            options.conductivity = conductivity.value();
        }

        auto stiffness = Converter::OptConvert<float>(src.stiffness);
        if (stiffness.has_value()) {
            options.stiffness = stiffness.value();
        }

        auto damping = Converter::OptConvert<float>(src.damping);
        if (damping.has_value()) {
            options.damping = damping.value();
        }

        auto edgeEffect = Converter::OptConvert<ChainEdgeEffect>(src.edgeEffect);
        if (edgeEffect.has_value()) {
            options.edgeEffect = static_cast<int32_t>(edgeEffect.value());
        }
        return options;
    }

    template<>
    ListLanesType Convert(const Ark_Number& src)
    {
        return Converter::Convert<int>(src);
    }

    template<>
    ListLanesType Convert(const Ark_LengthConstrain& src)
    {
        return Converter::Convert<std::pair<Dimension, Dimension>>(src);
    }

    template<>
    ListOptions Convert(const Ark_ListOptions& src)
    {
        return {
            .initialIndex = OptConvert<int>(src.initialIndex),
            .space = OptConvert<Dimension>(src.space),
            .scroller = OptConvert<Ark_Scroller>(src.scroller)
        };
    }

    template<>
    ScrollFrameResult Convert<ScrollFrameResult>(const Ark_ScrollResult& src)
    {
        return {
            .offset = Convert<Dimension>(src.offsetRemain)
        };
    }
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // ListModifier
namespace ListInterfaceModifier {
void SetListOptionsImpl(Ark_NativePointer node,
                        const Opt_ListOptions* options)
{
}
} // ListInterfaceModifier
namespace ListAttributeModifier {
void AlignListItemImpl(Ark_NativePointer node,
                       const Opt_ListItemAlign* value)
{
}
void ListDirectionImpl(Ark_NativePointer node,
                       const Opt_Axis* value)
{
}
void ScrollBarImpl(Ark_NativePointer node,
                   const Opt_BarState* value)
{
}
void ContentStartOffsetImpl(Ark_NativePointer node,
                            const Opt_Number* value)
{
}
void ContentEndOffsetImpl(Ark_NativePointer node,
                          const Opt_Number* value)
{
}
void DividerImpl(Ark_NativePointer node,
                 const Opt_ListDividerOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto divider = Converter::OptConvert<V2::ItemDivider>(*value);
    ListModelNG::SetDivider(frameNode, divider);
}
void EditModeImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void MultiSelectableImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
}
void CachedCount0Impl(Ark_NativePointer node,
                      const Opt_Number* value)
{
}
void CachedCount1Impl(Ark_NativePointer node,
                      const Opt_Number* count,
                      const Opt_Boolean* show)
{
}
void ChainAnimationImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
}
void ChainAnimationOptionsImpl(Ark_NativePointer node,
                               const Opt_ChainAnimationOptions* value)
{
}
void StickyImpl(Ark_NativePointer node,
                const Opt_StickyStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<V2::StickyStyle> style = Converter::OptConvert<V2::StickyStyle>(value);
    ListModelNG::SetSticky(frameNode, EnumToInt(style));
}
void ScrollSnapAlignImpl(Ark_NativePointer node,
                         const Opt_ScrollSnapAlign* value)
{
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Opt_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::Convert<Converter::NestedScrollModeOptions>(*value);
    ListModelNG::SetListNestedScroll(frameNode, options.forward, options.backward);
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
}
void FrictionImpl(Ark_NativePointer node,
                  const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ListModelNG::SetListFriction(frameNode, Converter::OptConvert<float>(*value));
}
void ChildrenMainSizeImpl(Ark_NativePointer node,
                          const Opt_ChildrenMainSize* value)
{
}
void MaintainVisibleContentPositionImpl(Ark_NativePointer node,
                                        const Opt_Boolean* value)
{
}
void StackFromEndImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
}
void OnScrollImpl(Ark_NativePointer node,
                  const Opt_Callback_Number_Number_Void* value)
{
}
void OnScrollIndexImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Number_Number_Void* value)
{
}
void OnScrollVisibleContentChangeImpl(Ark_NativePointer node,
                                      const Opt_OnScrollVisibleContentChangeCallback* value)
{
}
void OnReachStartImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
{
}
void OnReachEndImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
}
void OnScrollStartImpl(Ark_NativePointer node,
                       const Opt_Callback_Void* value)
{
}
void OnScrollStopImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
{
}
void OnItemDeleteImpl(Ark_NativePointer node,
                      const Opt_Callback_Number_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemDelete = [callback = CallbackHelper(*value)](int32_t index) -> bool {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        auto arkResult = callback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(arkIndex);
        return Converter::Convert<bool>(arkResult);
    };
    ListModelNG::SetOnItemDelete(frameNode, std::move(onItemDelete));
}
void OnItemMoveImpl(Ark_NativePointer node,
                    const Opt_Callback_Number_Number_Boolean* value)
{
}
void OnItemDragStartImpl(Ark_NativePointer node,
                         const Opt_ListAttribute_onItemDragStart_event_type* value)
{
}
void OnItemDragEnterImpl(Ark_NativePointer node,
                         const Opt_Callback_ItemDragInfo_Void* value)
{
}
void OnItemDragMoveImpl(Ark_NativePointer node,
                        const Opt_Callback_ItemDragInfo_Number_Number_Void* value)
{
}
void OnItemDragLeaveImpl(Ark_NativePointer node,
                         const Opt_Callback_ItemDragInfo_Number_Void* value)
{
}
void OnItemDropImpl(Ark_NativePointer node,
                    const Opt_Callback_ItemDragInfo_Number_Number_Boolean_Void* value)
{
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            const Opt_Callback_Number_ScrollState_Literal_Number_offsetRemain* value)
{
}
void LanesImpl(Ark_NativePointer node,
               const Opt_Union_Number_LengthConstrain* value,
               const Opt_Length* gutter)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    if (value != nullptr) {
        auto lanes = Converter::OptConvert<ListLanesType>(*value);
        if (lanes) {
            if (lanes.value().index() == 0) {
                int lane = std::get<0>(lanes.value());
                ListModelNG::SetLanes(frameNode, lane);
                ListModelNG::SetLaneConstrain(frameNode, Dimension(), Dimension());
            } else {
                auto dimensions = std::get<1>(lanes.value());
                ListModelNG::SetLanes(frameNode, 1);
                ListModelNG::SetLaneConstrain(frameNode, std::get<0>(dimensions), std::get<1>(dimensions));
            }
        }
    }

    if (gutter != nullptr) {
        std::optional<Dimension> gutterOpt;
        Converter::AssignOptionalTo(gutterOpt, *gutter);
        if (gutterOpt.has_value()) {
            ListModelNG::SetLaneGutter(frameNode, gutterOpt);
        }
    }
}
void EdgeEffectImpl(Ark_NativePointer node, Ark_EdgeEffect value, const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Converter::EdgeEffectOptions> edgeEffectOptions;
    if (options != nullptr) {
        edgeEffectOptions = Converter::OptConvert<Converter::EdgeEffectOptions>(*options);
    }
    std::optional<EdgeEffect> effect = Converter::OptConvert<EdgeEffect>(value);
    ListModelNG::SetEdgeEffect(
        frameNode, EnumToInt(effect), edgeEffectOptions->alwaysEnabled, edgeEffectOptions->effectEdge);
}
} // ListAttributeModifier
const GENERATED_ArkUIListModifier* GetListModifier()
{
    static const GENERATED_ArkUIListModifier ArkUIListModifierImpl {
        ListModifier::ConstructImpl,
        ListInterfaceModifier::SetListOptionsImpl,
        ListAttributeModifier::AlignListItemImpl,
        ListAttributeModifier::ListDirectionImpl,
        ListAttributeModifier::ScrollBarImpl,
        ListAttributeModifier::ContentStartOffsetImpl,
        ListAttributeModifier::ContentEndOffsetImpl,
        ListAttributeModifier::DividerImpl,
        ListAttributeModifier::EditModeImpl,
        ListAttributeModifier::MultiSelectableImpl,
        ListAttributeModifier::CachedCount0Impl,
        ListAttributeModifier::CachedCount1Impl,
        ListAttributeModifier::ChainAnimationImpl,
        ListAttributeModifier::ChainAnimationOptionsImpl,
        ListAttributeModifier::StickyImpl,
        ListAttributeModifier::ScrollSnapAlignImpl,
        ListAttributeModifier::NestedScrollImpl,
        ListAttributeModifier::EnableScrollInteractionImpl,
        ListAttributeModifier::FrictionImpl,
        ListAttributeModifier::ChildrenMainSizeImpl,
        ListAttributeModifier::MaintainVisibleContentPositionImpl,
        ListAttributeModifier::StackFromEndImpl,
        ListAttributeModifier::OnScrollImpl,
        ListAttributeModifier::OnScrollIndexImpl,
        ListAttributeModifier::OnScrollVisibleContentChangeImpl,
        ListAttributeModifier::OnReachStartImpl,
        ListAttributeModifier::OnReachEndImpl,
        ListAttributeModifier::OnScrollStartImpl,
        ListAttributeModifier::OnScrollStopImpl,
        ListAttributeModifier::OnItemDeleteImpl,
        ListAttributeModifier::OnItemMoveImpl,
        ListAttributeModifier::OnItemDragStartImpl,
        ListAttributeModifier::OnItemDragEnterImpl,
        ListAttributeModifier::OnItemDragMoveImpl,
        ListAttributeModifier::OnItemDragLeaveImpl,
        ListAttributeModifier::OnItemDropImpl,
        ListAttributeModifier::OnScrollFrameBeginImpl,
        ListAttributeModifier::LanesImpl,
        ListAttributeModifier::EdgeEffectImpl,
    };
    return &ArkUIListModifierImpl;
}

}
