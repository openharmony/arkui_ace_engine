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

#include "base/geometry/axis.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "frameworks/core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "frameworks/core/components_v2/list/list_properties.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "list_scroller_peer_impl.h"
#include "children_main_size_peer.h"

namespace OHOS::Ace::NG {
using ListLanesType = std::variant<int, std::pair<Dimension, Dimension>>;
}

namespace OHOS::Ace::NG::Converter {
    struct ListOptions {
        std::optional<int> initialIndex;
        std::optional<Dimension> space;
        std::optional<Ark_NativePointer> scroller;
    };

    struct NestedScrollModeOptions {
        std::optional<NestedScrollMode> forward;
        std::optional<NestedScrollMode> backward;
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
    ListLanesType Convert(const Ark_Number& src) {
        return Converter::Convert<int>(src);
    }

    template<>
    ListLanesType Convert(const Ark_LengthConstrain& src) {
        return Converter::Convert<std::pair<Dimension, Dimension>>(src);
    }

    template<>
    ListOptions Convert(const Ark_ListOptions& src)
    {
        return {
            .initialIndex = OptConvert<int>(src.initialIndex),
            .space = OptConvert<Dimension>(src.space),
            .scroller = OptConvert<Ark_NativePointer>(src.scroller)
        };
    }
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListInterfaceModifier {
void SetListOptionsImpl(Ark_NativePointer node,
                        const Opt_ListOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);

    auto optionsOpt = Converter::OptConvert<Converter::ListOptions>(*options);
    if (!optionsOpt.has_value()) {
        return;
    }

    auto initialIndex = optionsOpt.value().initialIndex;
    ListModelNG::SetInitialIndex(frameNode, initialIndex);
    auto space = optionsOpt.value().space;
    ListModelNG::SetListSpace(frameNode, space);

    RefPtr<ScrollControllerBase> positionController = ListModelNG::GetOrCreateController(frameNode);
    RefPtr<ScrollProxy> scrollBarProxy = ListModelNG::GetOrCreateScrollBarProxy(frameNode);
    auto abstPeerPtrOpt = optionsOpt.value().scroller;
    CHECK_NULL_VOID(abstPeerPtrOpt);
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::ListScrollerPeerImpl *>(*abstPeerPtrOpt);
    CHECK_NULL_VOID(peerImplPtr);
    peerImplPtr->SetController(positionController);
    peerImplPtr->SetScrollBarProxy(scrollBarProxy);
}
} // ListInterfaceModifier
namespace ListAttributeModifier {
void AlignListItemImpl(Ark_NativePointer node,
                       Ark_ListItemAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListItemAlign(frameNode, Converter::OptConvert<V2::ListItemAlign>(value));
}
void ListDirectionImpl(Ark_NativePointer node,
                       Ark_Axis value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Axis> direction = Converter::OptConvert<Axis>(value);
    ListModelNG::SetListDirection(frameNode, EnumToInt(direction));
}
void ScrollBarImpl(Ark_NativePointer node,
                   Ark_BarState value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<DisplayMode> mode = Converter::OptConvert<DisplayMode>(value);
    ListModelNG::SetListScrollBar(frameNode, EnumToInt(mode));
}
void ContentStartOffsetImpl(Ark_NativePointer node,
                            const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ListModelNG::SetContentStartOffset(frameNode, Converter::Convert<float>(*value));
}
void ContentEndOffsetImpl(Ark_NativePointer node,
                          const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ListModelNG::SetContentEndOffset(frameNode, Converter::Convert<float>(*value));
}
void DividerImpl(Ark_NativePointer node,
                 const Ark_Union_ListDividerOptions_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto divider = Converter::OptConvert<V2::ItemDivider>(*value);
    ListModelNG::SetDivider(frameNode, divider);
}
void EditModeImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetEditMode(frameNode, Converter::Convert<bool>(value));
}
void MultiSelectableImpl(Ark_NativePointer node,
                         Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetMultiSelectable(frameNode, Converter::Convert<bool>(value));
}
void CachedCountImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ListModelNG::SetCachedCount(frameNode, Converter::Convert<int>(*value));
}
void ChainAnimationImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetChainAnimation(frameNode, Converter::Convert<bool>(value));
}
void ChainAnimationOptionsImpl(Ark_NativePointer node,
                               const Ark_ChainAnimationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::Convert<ChainAnimationOptions>(*value);
    ListModelNG::SetChainAnimationOptions(frameNode, options);
}
void StickyImpl(Ark_NativePointer node,
                Ark_StickyStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<V2::StickyStyle> style = Converter::OptConvert<V2::StickyStyle>(value);
    ListModelNG::SetSticky(frameNode, EnumToInt(style));
}
void ScrollSnapAlignImpl(Ark_NativePointer node,
                         Ark_ScrollSnapAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetScrollSnapAlign(frameNode, Converter::OptConvert<V2::ScrollSnapAlign>(value));
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto options = Converter::Convert<Converter::NestedScrollModeOptions>(*value);
    ListModelNG::SetListNestedScroll(frameNode, options.forward, options.backward);
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetScrollEnabled(frameNode, Converter::Convert<bool>(value));
}
void FrictionImpl(Ark_NativePointer node,
                  const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ListModelNG::SetListFriction(frameNode, Converter::OptConvert<float>(*value));
}
void ChildrenMainSizeImpl(Ark_NativePointer node,
                          const Ark_Materialized* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto peer = reinterpret_cast<ChildrenMainSizePeer *>(value->ptr);
    CHECK_NULL_VOID(peer);
    RefPtr<ListChildrenMainSize> handler = ListModelNG::GetOrCreateListChildrenMainSize(frameNode);
    peer->SetHandler(handler);
}
void MaintainVisibleContentPositionImpl(Ark_NativePointer node,
                                        Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelNG::SetListMaintainVisibleContentPosition(frameNode, Converter::Convert<bool>(value));
}
void OnScrollImpl(Ark_NativePointer node,
                  const Callback_Number_ScrollState_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScroll = [frameNode](const CalcDimension& scrollOffset, const ScrollState& scrollState) {
        auto arkScrollOffset = Converter::ArkValue<Ark_Number>(scrollOffset);
        auto arkScrollState = Converter::ArkValue<Ark_ScrollState>(scrollState);
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->
            onScroll(frameNode->GetId(), arkScrollOffset, arkScrollState);
    };
    ListModelNG::SetOnScroll(frameNode, std::move(onScroll));
}
void OnScrollIndexImpl(Ark_NativePointer node,
                       const Callback_Number_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollIndex = [frameNode](const int32_t start, const int32_t end, const int32_t center) {
        auto arkStart = Converter::ArkValue<Ark_Number>(start);
        auto arkEnd = Converter::ArkValue<Ark_Number>(end);
        auto arkCenter = Converter::ArkValue<Ark_Number>(center);
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->
            onScrollIndex(frameNode->GetId(), arkStart, arkEnd, arkCenter);
    };
    ListModelNG::SetOnScrollIndex(frameNode, std::move(onScrollIndex));
}
void OnScrollVisibleContentChangeImpl(Ark_NativePointer node,
                                      const OnScrollVisibleContentChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollVisibleContentChange = [frameNode](const ListItemIndex& start, const ListItemIndex& end) {
        auto startItemInfo = Converter::ArkValue<Ark_VisibleListContentInfo>(start);
        auto endItemInfo = Converter::ArkValue<Ark_VisibleListContentInfo>(end);
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->onScrollVisibleContentChange(
            frameNode->GetId(), startItemInfo, endItemInfo);
    };

    ListModelNG::SetOnScrollVisibleContentChange(frameNode, std::move(onScrollVisibleContentChange));
}
void OnReachStartImpl(Ark_NativePointer node,
                      const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onReachStart = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->onReachStart(frameNode->GetId());
    };
    ListModelNG::SetOnReachStart(frameNode, std::move(onReachStart));
}
void OnReachEndImpl(Ark_NativePointer node,
                    const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onReachEnd = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->onReachEnd(frameNode->GetId());
    };
    ListModelNG::SetOnReachEnd(frameNode, std::move(onReachEnd));
}
void OnScrollStartImpl(Ark_NativePointer node,
                       const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollStart = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->onScrollStart(frameNode->GetId());
    };
    ListModelNG::SetOnScrollStart(frameNode, std::move(onScrollStart));
}
void OnScrollStopImpl(Ark_NativePointer node,
                      const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollStop = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->onScrollStop(frameNode->GetId());
    };
    ListModelNG::SetOnScrollStop(frameNode, std::move(onScrollStop));
}
void OnItemDeleteImpl(Ark_NativePointer node,
                      const Callback_Number_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ListModelNG::SetOnItemDelete(frameNode, convValue);
    LOGE("ListModifier::OnItemDeleteImpl is not implemented yet!\n");
}
void OnItemMoveImpl(Ark_NativePointer node,
                    const Callback_Number_Number_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemMove = [frameNode](int32_t from, int32_t to) {
        auto arkFrom = Converter::ArkValue<Ark_Number>(from);
        auto arkTo = Converter::ArkValue<Ark_Number>(to);
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->onItemMove(frameNode->GetId(), arkFrom, arkTo);
        // onItemMove should return bool value but it is a void
        LOGE("ARKOALA onItemMove doesn`t handle bool returned value");
        return false;
    };
    ListModelNG::SetOnItemMove(frameNode, std::move(onItemMove));
}
void OnItemDragStartImpl(Ark_NativePointer node,
                         const Callback_ItemDragInfo_Number_Callback_Any* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemDragStart = [frameNode](const ItemDragInfo& dragInfo, int32_t itemIndex) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Number>(itemIndex);
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->onItemDragStart(
            frameNode->GetId(), arkDragInfo, arkItemIndex);
        // onItemDragStart should return value [builder] but it is a void
        LOGE("ARKOALA onItemDragStart doesn`t handle builder returned value");
        return nullptr;
    };
    ListModelNG::SetOnItemDragStart(frameNode, std::move(onItemDragStart));
}
void OnItemDragEnterImpl(Ark_NativePointer node,
                         const Callback_ItemDragInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemDragEnter = [frameNode](const ItemDragInfo& dragInfo) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->onItemDragEnter(frameNode->GetId(), arkDragInfo);
    };
    ListModelNG::SetOnItemDragEnter(frameNode, std::move(onItemDragEnter));
}
void OnItemDragMoveImpl(Ark_NativePointer node,
                        const Callback_ItemDragInfo_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemDragMove = [frameNode](const ItemDragInfo& dragInfo,
        int32_t itemIndex, int32_t insertIndex) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Number>(itemIndex);
        auto arkInsertIndex = Converter::ArkValue<Ark_Number>(insertIndex);
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->onItemDragMove(
            frameNode->GetId(), arkDragInfo, arkItemIndex, arkInsertIndex);
    };
    ListModelNG::SetOnItemDragMove(frameNode, std::move(onItemDragMove));
}
void OnItemDragLeaveImpl(Ark_NativePointer node,
                         const Callback_ItemDragInfo_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemDragLeave = [frameNode](const ItemDragInfo& dragInfo, int32_t itemIndex) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Number>(itemIndex);
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->onItemDragLeave(
            frameNode->GetId(), arkDragInfo, arkItemIndex);
    };
    ListModelNG::SetOnItemDragLeave(frameNode, std::move(onItemDragLeave));
}
void OnItemDropImpl(Ark_NativePointer node,
                    const Callback_ItemDragInfo_Number_Number_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemDrop = [frameNode](const ItemDragInfo& dragInfo,
        int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Number>(itemIndex);
        auto arkInsertIndex = Converter::ArkValue<Ark_Number>(insertIndex);
        auto arkIsSuccess = Converter::ArkValue<Ark_Boolean>(isSuccess);
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->onItemDrop(
            frameNode->GetId(), arkDragInfo, arkItemIndex, arkInsertIndex, arkIsSuccess);
    };
    ListModelNG::SetOnItemDrop(frameNode, std::move(onItemDrop));
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            const Callback_Number_ScrollState_Literal_Number_offsetRemain* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollFrameBegin = [frameNode](const Dimension& offset, const ScrollState& state) -> ScrollFrameResult {
        ScrollFrameResult scrollRes { .offset = offset };
        auto arkOffset = Converter::ArkValue<Ark_Number>(offset);
        auto arkState = Converter::ArkValue<Ark_ScrollState>(state);
        GetFullAPI()->getEventsAPI()->getListEventsReceiver()->onScrollFrameBegin(
            frameNode->GetId(), arkOffset, arkState);
        // onScrollFrameBegin should return value [offsetRemain] but it is a void
        // that is a reason why we return [offset] value as the temporary stub
        LOGE("ARKOALA onScrollFrameBegin doesn`t handle offsetRemain returned value");
        return scrollRes;
    };
    ListModelNG::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameBegin));
}
void LanesImpl(Ark_NativePointer node,
               const Ark_Union_Number_LengthConstrain* value,
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
void EdgeEffectImpl(Ark_NativePointer node,
                    Ark_EdgeEffect value,
                    const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<bool> alwaysEnabled;
    if (options != nullptr) {
        alwaysEnabled = Converter::OptConvert<bool>(*options);
    }
    std::optional<EdgeEffect> effect = Converter::OptConvert<EdgeEffect>(value);
    ListModelNG::SetEdgeEffect(frameNode, EnumToInt(effect), alwaysEnabled);
}
} // ListAttributeModifier
const GENERATED_ArkUIListModifier* GetListModifier()
{
    static const GENERATED_ArkUIListModifier ArkUIListModifierImpl {
        ListInterfaceModifier::SetListOptionsImpl,
        ListAttributeModifier::AlignListItemImpl,
        ListAttributeModifier::ListDirectionImpl,
        ListAttributeModifier::ScrollBarImpl,
        ListAttributeModifier::ContentStartOffsetImpl,
        ListAttributeModifier::ContentEndOffsetImpl,
        ListAttributeModifier::DividerImpl,
        ListAttributeModifier::EditModeImpl,
        ListAttributeModifier::MultiSelectableImpl,
        ListAttributeModifier::CachedCountImpl,
        ListAttributeModifier::ChainAnimationImpl,
        ListAttributeModifier::ChainAnimationOptionsImpl,
        ListAttributeModifier::StickyImpl,
        ListAttributeModifier::ScrollSnapAlignImpl,
        ListAttributeModifier::NestedScrollImpl,
        ListAttributeModifier::EnableScrollInteractionImpl,
        ListAttributeModifier::FrictionImpl,
        ListAttributeModifier::ChildrenMainSizeImpl,
        ListAttributeModifier::MaintainVisibleContentPositionImpl,
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
