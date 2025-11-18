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

#include "base/geometry/axis.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "frameworks/core/components/list/list_theme.h"
#include "frameworks/core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "frameworks/core/components_ng/pattern/scrollable/scrollable_model_static.h"
#include "frameworks/core/components_v2/list/list_properties.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "list_scroller_peer_impl.h"
#include "children_main_size_peer.h"
#include "scroll_result_peer.h"

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
        dst.strokeWidth = OptConvert<Dimension>(src.strokeWidth).value_or(dst.strokeWidth);
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
        options.minSpace = OptConvert<Dimension>(src.minSpace).value_or(options.minSpace);
        options.maxSpace = OptConvert<Dimension>(src.maxSpace).value_or(options.maxSpace);

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
    ListLanesType Convert(const Ark_Int32& src)
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
            .offset = Dimension(src->offsetRemain)
        };
    }

    template<>
    inline void AssignTo(std::optional<ScrollFrameResult>& dst, const Ark_OnScrollFrameBeginHandlerResult& from)
    {
        ScrollFrameResult ret;
        ret.offset = Converter::Convert<Dimension>(from.offsetRemain);
        dst = ret;
    }
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = ListModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

RefPtr<ListTheme> GetListTheme(FrameNode* node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto context = node->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    return context->GetTheme<ListTheme>();
}
} // ListModifier
namespace ListInterfaceModifier {
void SetListOptionsImpl(Ark_NativePointer node,
                        const Opt_ListOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    auto optionsOpt = Converter::OptConvertPtr<Converter::ListOptions>(options);
    if (!optionsOpt.has_value()) {
        return;
    }

    auto initialIndex = optionsOpt.value().initialIndex;
    ListModelStatic::SetInitialIndex(frameNode, initialIndex);
    auto space = optionsOpt.value().space;
    ListModelStatic::SetListSpace(frameNode, space);

    RefPtr<ScrollControllerBase> positionController = ListModelStatic::GetOrCreateController(frameNode);
    RefPtr<ScrollProxy> scrollBarProxy = ListModelStatic::GetOrCreateScrollBarProxy(frameNode);
    auto abstPeerPtrOpt = optionsOpt.value().scroller;
    CHECK_NULL_VOID(abstPeerPtrOpt);
    auto peerImplPtr = *abstPeerPtrOpt;
    CHECK_NULL_VOID(peerImplPtr);
    peerImplPtr->SetController(positionController);
    peerImplPtr->SetScrollBarProxy(scrollBarProxy);
}
} // ListInterfaceModifier
namespace ListAttributeModifier {
void SetAlignListItemImpl(Ark_NativePointer node,
                          const Opt_ListItemAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelStatic::SetListItemAlign(frameNode, Converter::OptConvertPtr<V2::ListItemAlign>(value));
}
void SetListDirectionImpl(Ark_NativePointer node,
                          const Opt_Axis* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Axis> direction = Converter::OptConvertPtr<Axis>(value);
    ListModelStatic::SetListDirection(frameNode, EnumToInt(direction));
}
void SetContentStartOffsetImpl(Ark_NativePointer node,
                               const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    if (!convValue) {
        ListModelStatic::SetContentStartOffset(frameNode, 0);
        return;
    }
    ListModelStatic::SetContentStartOffset(frameNode, *convValue);
}
void SetContentEndOffsetImpl(Ark_NativePointer node,
                             const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    if (!convValue) {
        ListModelStatic::SetContentEndOffset(frameNode, 0);
        return;
    }
    ListModelStatic::SetContentEndOffset(frameNode, *convValue);
}
void SetDividerImpl(Ark_NativePointer node,
                    const Opt_ListDividerOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto options = value ? Converter::OptConvert<Ark_ListDividerOptions>(*value) : std::nullopt;
    V2::ItemDivider dividerAns;
    bool needGetThemeColor = false;
    if (options.has_value()) {
        auto widthOpt = Converter::OptConvert<Dimension>(options->strokeWidth);
        dividerAns.strokeWidth = widthOpt.value_or(0.0_vp);
        auto startMarginOpt = Converter::OptConvert<Dimension>(options->startMargin);
        dividerAns.startMargin = startMarginOpt.value_or(0.0_vp);
        auto endMarginOpt = Converter::OptConvert<Dimension>(options->endMargin);
        dividerAns.endMargin = endMarginOpt.value_or(0.0_vp);
        auto colorOpt = Converter::OptConvert<Color>(options->color);
        if (colorOpt.has_value()) {
            dividerAns.color = colorOpt.value();
        } else {
            needGetThemeColor = true;
        }
        ListModelStatic::SetDivider(frameNode, dividerAns, needGetThemeColor);
    } else {
        ListModelStatic::SetDivider(frameNode, std::nullopt);
    }
}
void SetMultiSelectableImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ListModelStatic::SetMultiSelectable(frameNode, false);
        return;
    }
    ListModelStatic::SetMultiSelectable(frameNode, *convValue);
}
void SetCachedCount0Impl(Ark_NativePointer node,
                         const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int>(value);
    if (!convValue) {
        ListModelStatic::SetCachedCount(frameNode, std::nullopt);
        return;
    }
    ListModelStatic::SetCachedCount(frameNode, convValue);
}
void SetChainAnimationImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ListModelStatic::SetChainAnimation(frameNode, false);
        return;
    }
    ListModelStatic::SetChainAnimation(frameNode, *convValue);
}
void SetChainAnimationOptionsImpl(Ark_NativePointer node,
                                  const Opt_ChainAnimationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<ChainAnimationOptions>(value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    ListModelStatic::SetChainAnimationOptions(frameNode, *convValue);
}
void SetStickyImpl(Ark_NativePointer node,
                   const Opt_StickyStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto style = Converter::OptConvertPtr<V2::StickyStyle>(value);
    ListModelStatic::SetSticky(frameNode, EnumToInt(style));
}
void SetScrollSnapAlignImpl(Ark_NativePointer node,
                            const Opt_ScrollSnapAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListModelStatic::SetScrollSnapAlign(frameNode, Converter::OptConvertPtr<ScrollSnapAlign>(value));
}
void SetChildrenMainSizeImpl(Ark_NativePointer node,
                             const Opt_ChildrenMainSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ListModelStatic::ResetListChildrenMainSize(frameNode);
        return;
    }
    auto peer = *optValue;
    CHECK_NULL_VOID(peer);
    RefPtr<ListChildrenMainSize> handler = ListModelStatic::GetOrCreateListChildrenMainSize(frameNode);
    peer->SetHandler(handler);
}
void SetMaintainVisibleContentPositionImpl(Ark_NativePointer node,
                                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    ListModelStatic::SetListMaintainVisibleContentPosition(frameNode, convValue);
}
void SetStackFromEndImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    ListModelStatic::SetStackFromEnd(frameNode, convValue);
}
void SetOnScrollIndexImpl(Ark_NativePointer node,
                          const Opt_Callback_I32_I32_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ListModelStatic::SetOnScrollIndex(frameNode, nullptr);
        return;
    }
    auto onScrollIndex = [arkCallback = CallbackHelper(*optValue)]
            (const int32_t start, const int32_t end, const int32_t center) {
        auto arkStart = Converter::ArkValue<Ark_Int32>(start);
        auto arkEnd = Converter::ArkValue<Ark_Int32>(end);
        auto arkCenter = Converter::ArkValue<Ark_Int32>(center);
        arkCallback.Invoke(arkStart, arkEnd, arkCenter);
    };
    ListModelStatic::SetOnScrollIndex(frameNode, std::move(onScrollIndex));
}
void SetOnScrollVisibleContentChangeImpl(Ark_NativePointer node,
                                         const Opt_OnScrollVisibleContentChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ListModelStatic::SetOnScrollVisibleContentChange(frameNode, nullptr);
        return;
    }
    auto onScrollVisibleContentChange = [arkCallback = CallbackHelper(*optValue)]
            (const ListItemIndex& start, const ListItemIndex& end) {
        auto startItemInfo = Converter::ArkValue<Ark_VisibleListContentInfo>(start);
        auto endItemInfo = Converter::ArkValue<Ark_VisibleListContentInfo>(end);
        arkCallback.Invoke(startItemInfo, endItemInfo);
    };
    ListModelStatic::SetOnScrollVisibleContentChange(frameNode, std::move(onScrollVisibleContentChange));
}
void SetOnItemMoveImpl(Ark_NativePointer node,
                       const Opt_Callback_I32_I32_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ListModelStatic::SetOnItemMove(frameNode, nullptr);
        return;
    }
    auto onItemMove = [callback = CallbackHelper(*optValue)](int32_t from, int32_t to) {
        auto arkFrom = Converter::ArkValue<Ark_Int32>(from);
        auto arkTo = Converter::ArkValue<Ark_Int32>(to);
        auto arkResult = callback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(arkFrom, arkTo);
        return Converter::Convert<bool>(arkResult);
    };
    ListModelStatic::SetOnItemMove(frameNode, std::move(onItemMove));
}
void SetOnItemDragStartImpl(Ark_NativePointer node,
                            const Opt_OnItemDragStartCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ListModelStatic::ResetOnItemDragStart(frameNode);
        return;
    }
    auto onItemDragStart = [callback = CallbackHelper(*optValue), frameNode, node](
                               const ItemDragInfo& dragInfo, int32_t itemIndex) -> RefPtr<AceType> {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Int32>(itemIndex);
        auto builderOpt = callback.InvokeWithOptConvertResult<CustomNodeBuilder, Opt_CustomNodeBuilder,
            Callback_Opt_CustomBuilder_Void>(arkDragInfo, arkItemIndex);
        if (!builderOpt.has_value()) {
            return nullptr;
        }
        return CallbackHelper(builderOpt.value()).BuildSync(node);
    };
    ListModelStatic::SetOnItemDragStart(frameNode, std::move(onItemDragStart));
}
void SetOnItemDragEnterImpl(Ark_NativePointer node,
                            const Opt_Callback_ItemDragInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ListModelStatic::SetOnItemDragEnter(frameNode, nullptr);
        return;
    }
    auto onItemDragEnter = [arkCallback = CallbackHelper(*optValue)](const ItemDragInfo& dragInfo) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        arkCallback.Invoke(arkDragInfo);
    };
    ListModelStatic::SetOnItemDragEnter(frameNode, std::move(onItemDragEnter));
}
void SetOnItemDragMoveImpl(Ark_NativePointer node,
                           const Opt_Callback_ItemDragInfo_I32_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ListModelStatic::SetOnItemDragMove(frameNode, nullptr);
        return;
    }
    auto onItemDragMove = [arkCallback = CallbackHelper(*optValue)](const ItemDragInfo& dragInfo,
            int32_t itemIndex, int32_t insertIndex) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Int32>(itemIndex);
        auto arkInsertIndex = Converter::ArkValue<Ark_Int32>(insertIndex);
        arkCallback.Invoke(arkDragInfo, arkItemIndex, arkInsertIndex);
    };
    ListModelStatic::SetOnItemDragMove(frameNode, std::move(onItemDragMove));
}
void SetOnItemDragLeaveImpl(Ark_NativePointer node,
                            const Opt_Callback_ItemDragInfo_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ListModelStatic::SetOnItemDragLeave(frameNode, nullptr);
        return;
    }
    auto onItemDragLeave = [arkCallback = CallbackHelper(*optValue)](const ItemDragInfo& dragInfo, int32_t itemIndex) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Int32>(itemIndex);
        arkCallback.Invoke(arkDragInfo, arkItemIndex);
    };
    ListModelStatic::SetOnItemDragLeave(frameNode, std::move(onItemDragLeave));
}
void SetOnItemDropImpl(Ark_NativePointer node,
                       const Opt_Callback_ItemDragInfo_I32_I32_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ListModelStatic::SetOnItemDrop(frameNode, nullptr);
        return;
    }
    auto onItemDrop = [arkCallback = CallbackHelper(*optValue)](const ItemDragInfo& dragInfo,
            int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Int32>(itemIndex);
        auto arkInsertIndex = Converter::ArkValue<Ark_Int32>(insertIndex);
        auto arkIsSuccess = Converter::ArkValue<Ark_Boolean>(isSuccess);
        arkCallback.Invoke(arkDragInfo, arkItemIndex, arkInsertIndex, arkIsSuccess);
    };
    ListModelStatic::SetOnItemDrop(frameNode, std::move(onItemDrop));
}
void SetOnScrollFrameBeginImpl(Ark_NativePointer node,
                               const Opt_OnScrollFrameBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ListModelStatic::SetOnScrollFrameBegin(frameNode, nullptr);
        return;
    }
    auto onScrollFrameEvent = [callback = CallbackHelper(*optValue)](
        Dimension dimension, ScrollState state) -> ScrollFrameResult {
        Ark_Float64 arkValue = Converter::ArkValue<Ark_Float64>(dimension);
        Ark_ScrollState arkState = Converter::ArkValue<Ark_ScrollState>(state);
        ScrollFrameResult result { .offset = dimension};
        return callback.InvokeWithOptConvertResult<
            ScrollFrameResult, Ark_OnScrollFrameBeginHandlerResult,
            Callback_OnScrollFrameBeginHandlerResult_Void>(arkValue, arkState)
            .value_or(result);
    };
    ListModelStatic::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameEvent));
}
void SetOnWillScrollImpl(Ark_NativePointer node,
                         const Opt_OnWillScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<OnWillScrollCallback> arkCallback;
    if (value) {
        arkCallback = Converter::OptConvert<OnWillScrollCallback>(*value);
    }
    if (arkCallback) {
        auto modelCallback = [callback = CallbackHelper(arkCallback.value())]
            (const Dimension& scrollOffset, const ScrollState& scrollState, const ScrollSource& scrollSource) ->
                ScrollFrameResult {
            auto arkScrollOffset = Converter::ArkValue<Ark_Float64>(scrollOffset);
            auto arkScrollState = Converter::ArkValue<Ark_ScrollState>(scrollState);
            auto arkScrollSource = Converter::ArkValue<Ark_ScrollSource>(scrollSource);
            auto resultOpt = callback.InvokeWithOptConvertResult<ScrollFrameResult, Opt_ScrollResult,
                Callback_Opt_ScrollResult_Void>(arkScrollOffset, arkScrollState, arkScrollSource);
            ScrollFrameResult defaultResult { .offset = scrollOffset };
            return resultOpt.value_or(defaultResult);
        };
        ScrollableModelStatic::SetOnWillScroll(frameNode, std::move(modelCallback));
    } else {
        ScrollableModelStatic::SetOnWillScroll(frameNode, nullptr);
    }
}
void SetOnDidScrollImpl(Ark_NativePointer node,
                        const Opt_OnScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto callValue = Converter::OptConvert<OnScrollCallback>(*value);
    if (!callValue.has_value()) {
        ScrollableModelStatic::SetOnDidScroll(frameNode, nullptr);
        return;
    }
    auto onDidScroll = [arkCallback = CallbackHelper(callValue.value())](
        Dimension oIn, ScrollState stateIn) {
            auto state = Converter::ArkValue<Ark_ScrollState>(stateIn);
            auto scrollOffset = Converter::ArkValue<Ark_Float64>(oIn);
            arkCallback.Invoke(scrollOffset, state);
    };
    ScrollableModelStatic::SetOnDidScroll(frameNode, std::move(onDidScroll));
}
void SetLanesImpl(Ark_NativePointer node,
                  const Opt_Union_I32_LengthConstrain* value,
                  const Opt_Dimension* gutter)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    auto lanes = Converter::OptConvertPtr<ListLanesType>(value);
    if (lanes) {
        if (lanes.value().index() == 0) {
            int lane = std::get<0>(lanes.value());
            ListModelStatic::SetLanes(frameNode, lane);
            ListModelStatic::SetLaneConstrain(frameNode, Dimension(), Dimension());
        } else {
            auto dimensions = std::get<1>(lanes.value());
            ListModelStatic::SetLanes(frameNode, 1);
            ListModelStatic::SetLaneConstrain(frameNode, std::get<0>(dimensions), std::get<1>(dimensions));
        }
    } else {
        ListModelStatic::ResetLanes(frameNode);
    }

    auto gutterOpt = Converter::OptConvertPtr<Dimension>(gutter);
    if (gutterOpt.has_value()) {
        ListModelStatic::SetLaneGutter(frameNode, gutterOpt);
    } else {
        ListModelStatic::SetLaneGutter(frameNode, 0.0_vp);
    }
}
void SetCachedCount1Impl(Ark_NativePointer node,
                         const Opt_Int32* count,
                         const Opt_Boolean* show)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto countValue = Converter::OptConvertPtr<int>(count);
    auto showValue = Converter::OptConvertPtr<bool>(show);
    ListModelStatic::SetCachedCount(frameNode, countValue, showValue);
}
} // ListAttributeModifier
const GENERATED_ArkUIListModifier* GetListModifier()
{
    static const GENERATED_ArkUIListModifier ArkUIListModifierImpl {
        ListModifier::ConstructImpl,
        ListInterfaceModifier::SetListOptionsImpl,
        ListAttributeModifier::SetAlignListItemImpl,
        ListAttributeModifier::SetListDirectionImpl,
        ListAttributeModifier::SetContentStartOffsetImpl,
        ListAttributeModifier::SetContentEndOffsetImpl,
        ListAttributeModifier::SetDividerImpl,
        ListAttributeModifier::SetMultiSelectableImpl,
        ListAttributeModifier::SetCachedCount0Impl,
        ListAttributeModifier::SetChainAnimationImpl,
        ListAttributeModifier::SetChainAnimationOptionsImpl,
        ListAttributeModifier::SetStickyImpl,
        ListAttributeModifier::SetScrollSnapAlignImpl,
        ListAttributeModifier::SetChildrenMainSizeImpl,
        ListAttributeModifier::SetMaintainVisibleContentPositionImpl,
        ListAttributeModifier::SetStackFromEndImpl,
        ListAttributeModifier::SetOnScrollIndexImpl,
        ListAttributeModifier::SetOnScrollVisibleContentChangeImpl,
        ListAttributeModifier::SetOnItemMoveImpl,
        ListAttributeModifier::SetOnItemDragStartImpl,
        ListAttributeModifier::SetOnItemDragEnterImpl,
        ListAttributeModifier::SetOnItemDragMoveImpl,
        ListAttributeModifier::SetOnItemDragLeaveImpl,
        ListAttributeModifier::SetOnItemDropImpl,
        ListAttributeModifier::SetOnScrollFrameBeginImpl,
        ListAttributeModifier::SetOnWillScrollImpl,
        ListAttributeModifier::SetOnDidScrollImpl,
        ListAttributeModifier::SetLanesImpl,
        ListAttributeModifier::SetCachedCount1Impl,
    };
    return &ArkUIListModifierImpl;
}
}
