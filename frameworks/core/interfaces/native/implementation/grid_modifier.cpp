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
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/grid/grid_model_static.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/implementation/scroller_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::Converter {

template<>
inline void AssignCast(std::optional<GridItemSize>& dst, const Ark_GridLayoutOptions& src)
{
    dst->rows = Converter::Convert<int32_t>(src.regularSize.value0);
    dst->columns = Converter::Convert<int32_t>(src.regularSize.value1);
}

template<>
inline void AssignCast(std::optional<std::set<int32_t>>& dst, const Array_Number& src)
{
    auto length = static_cast<int32_t>(src.length);
    std::set<int32_t> indexesSet;
    for (int i = 0; i < length; i++) {
        auto currentValue = Converter::Convert<int32_t>(*(src.array + i));
        indexesSet.insert(currentValue);
    }
    dst = std::make_optional(indexesSet);
}

template<>
inline void AssignCast(std::optional<std::set<int32_t>>& dst, const Ark_GridLayoutOptions& src)
{
    dst = Converter::OptConvert<std::set<int32_t>>(src.irregularIndexes);
}

template<>
inline void AssignCast(std::optional<GridItemAlignment>& dst, const Ark_GridItemAlignment& src)
{
    switch (src) {
        case ARK_GRID_ITEM_ALIGNMENT_DEFAULT: dst = GridItemAlignment::DEFAULT; break;
        case ARK_GRID_ITEM_ALIGNMENT_STRETCH: dst = GridItemAlignment::STRETCH; break;
        default: LOGE("Unexpected enum value in Ark_GridItemAlignment: %{public}d", src);
    }
}

template<>
inline void AssignCast(std::optional<GridItemSize>& dst, const Ark_Tuple_Number_Number& src)
{
    auto rows = Converter::Convert<int32_t>(src.value0);
    auto columns = Converter::Convert<int32_t>(src.value1);
    dst = {.rows = rows, .columns = columns};
}

template<>
inline void AssignCast(std::optional<GridItemRect>& dst, const Ark_Tuple_Number_Number_Number_Number& src)
{
    auto rowStart = Converter::Convert<int32_t>(src.value0);
    auto columnStart = Converter::Convert<int32_t>(src.value1);
    auto rowSpan = Converter::Convert<int32_t>(src.value2);
    auto columnSpan = Converter::Convert<int32_t>(src.value3);
    dst = {.rowStart = rowStart, .columnStart = columnStart, .rowSpan = rowSpan, .columnSpan = columnSpan};
}

template<>
inline void AssignTo(std::optional<ScrollFrameResult>& dst, const Ark_OnScrollFrameBeginHandlerResult& from)
{
    ScrollFrameResult ret;
    ret.offset = Converter::Convert<Dimension>(from.offsetRemain);
    dst = ret;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GridModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = GridModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // GridModifier
namespace GridInterfaceModifier {
void SetScroll(FrameNode* frameNode, const Opt_Scroller* scroller)
{
    CHECK_NULL_VOID(scroller);
    RefPtr<ScrollControllerBase> positionController = GridModelStatic::GetOrCreateController(frameNode);
    RefPtr<ScrollProxy> scrollBarProxy = GridModelStatic::GetOrCreateScrollBarProxy(frameNode);
    auto abstPeerPtrOpt = Converter::OptConvert<Ark_Scroller>(*scroller);
    CHECK_NULL_VOID(abstPeerPtrOpt);
    auto peerImplPtr = *abstPeerPtrOpt;
    CHECK_NULL_VOID(peerImplPtr);
    peerImplPtr->SetController(positionController);
    peerImplPtr->SetScrollBarProxy(scrollBarProxy);
}
void SetGridOptionsImpl(Ark_NativePointer node,
                        const Opt_Scroller* scroller,
                        const Opt_GridLayoutOptions* layoutOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Ark_GridLayoutOptions> layoutOptionsOpt = layoutOptions ?
        Converter::OptConvert<Ark_GridLayoutOptions>(*layoutOptions) : std::nullopt;
    if (layoutOptionsOpt) {
        GridLayoutOptions options;
        std::optional<GridItemSize> regularSizeOpt = Converter::OptConvert<GridItemSize>(layoutOptionsOpt.value());
        if (regularSizeOpt) {
            options.regularSize = regularSizeOpt.value();
        }
        std::optional<std::set<int32_t>> irrIndex = Converter::OptConvert<std::set<int32_t>>(layoutOptionsOpt.value());
        if (irrIndex) {
            options.irregularIndexes = irrIndex.value();
        }
        auto onGetIrregularSizeByIndex = Converter::OptConvert<::Callback_Number_Tuple_Number_Number>
                                    (layoutOptionsOpt.value().onGetIrregularSizeByIndex);
        if (onGetIrregularSizeByIndex) {
            auto modelCallback = [callback = CallbackHelper(*onGetIrregularSizeByIndex)]
                                            (int32_t value) -> GridItemSize {
                Ark_Number param = Converter::ArkValue<Ark_Number>(value);
                auto resultOpt = callback.InvokeWithOptConvertResult
                                    <GridItemSize, Ark_Tuple_Number_Number, Callback_Tuple_Number_Number_Void>(param);
                return resultOpt.value_or(GridItemSize());
            };
            options.getSizeByIndex = modelCallback;
        }
        auto onGetRectByIndex = Converter::OptConvert<::Callback_Number_Tuple_Number_Number_Number_Number>
                                    (layoutOptionsOpt.value().onGetRectByIndex);
        if (onGetRectByIndex) {
            auto modelCallback = [callback = CallbackHelper(*onGetRectByIndex)](int32_t value) -> GridItemRect {
                Ark_Number param = Converter::ArkValue<Ark_Number>(value);
                auto resOpt = callback.InvokeWithOptConvertResult<GridItemRect, Ark_Tuple_Number_Number_Number_Number,
                                     Callback_Tuple_Number_Number_Number_Number_Void>(param);
                return resOpt.value_or(GridItemRect());
            };
            options.getRectByIndex = modelCallback;
        }
        GridModelStatic::SetLayoutOptions(frameNode, options);
    }
    SetScroll(frameNode, scroller);
}
} // GridInterfaceModifier
namespace GridAttributeModifier {
void ColumnsTemplateImpl(Ark_NativePointer node,
                         const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    GridModelStatic::SetColumnsTemplate(frameNode, *convValue);
}
void RowsTemplateImpl(Ark_NativePointer node,
                      const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    GridModelStatic::SetRowsTemplate(frameNode, *convValue);
}
void ColumnsGapImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    if (!convValue) {
        GridModelStatic::SetColumnsGap(frameNode, std::optional<Dimension>(0));
        return;
    }
    if (convValue.value().Value() < 0) {
        convValue = std::optional<Dimension>(0);
    }
    GridModelStatic::SetColumnsGap(frameNode, *convValue);
}
void RowsGapImpl(Ark_NativePointer node,
                 const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    if (!convValue) {
        GridModelStatic::SetRowsGap(frameNode, std::optional<Dimension>(0));
        return;
    }
    if (convValue.value().Value() < 0) {
        convValue = std::optional<Dimension>(0);
    }
    GridModelStatic::SetRowsGap(frameNode, *convValue);
}
void ScrollBarWidthImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelStatic::SetScrollBarWidth(frameNode, Converter::OptConvert<Dimension>(*value));
}
void ScrollBarColorImpl(Ark_NativePointer node,
                        const Opt_Union_Color_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelStatic::SetScrollBarColor(frameNode, Converter::OptConvert<Color>(*value));
}
void ScrollBarImpl(Ark_NativePointer node,
                   const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelStatic::SetScrollBarMode(frameNode, Converter::OptConvert<DisplayMode>(*value));
}
void OnScrollBarUpdateImpl(Ark_NativePointer node,
                           const Opt_Callback_Number_Number_ComputedBarAttribute* value)
{
    using namespace Converter;
    using ResType = std::pair<std::optional<float>, std::optional<float>>;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onScrollBarUpdate =
        [callback = CallbackHelper(*optValue)](int32_t index, const Dimension& offset) -> ResType {
        auto arkIndex = ArkValue<Ark_Number>(index);
        auto arkOffset = ArkValue<Ark_Number>(offset);
        auto arkResult = callback.InvokeWithObtainResult<Ark_ComputedBarAttribute, Callback_ComputedBarAttribute_Void>(
            arkIndex, arkOffset);
        return ResType(Convert<float>(arkResult.totalOffset), Convert<float>(arkResult.totalLength));
    };
    GridModelStatic::SetOnScrollBarUpdate(frameNode, std::move(onScrollBarUpdate));
}
void OnScrollIndexImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onScrollIndex = [arkCallback = CallbackHelper(*optValue)](const int32_t first, const int32_t last) {
        auto arkFirst = Converter::ArkValue<Ark_Number>(first);
        auto arkLast = Converter::ArkValue<Ark_Number>(last);
        arkCallback.Invoke(arkFirst, arkLast);
    };
    GridModelStatic::SetOnScrollIndex(frameNode, std::move(onScrollIndex));
}
void CachedCount0Impl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    GridModelStatic::SetCachedCount(frameNode, *convValue);
}
void CachedCount1Impl(Ark_NativePointer node,
                      const Opt_Number* count,
                      const Opt_Boolean* show)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*count).value_or(1);
    if (convValue < 0) {
        convValue = 1;
    }
    GridModelStatic::SetCachedCount(frameNode, convValue);
    auto showValue = Converter::OptConvert<bool>(*show).value_or(false);
    GridModelStatic::SetShowCached(frameNode, showValue);
}
void EditModeImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    GridModelStatic::SetEditable(frameNode, *convValue);
}
void MultiSelectableImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    GridModelStatic::SetMultiSelectable(frameNode, *convValue);
}
void MaxCountImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    GridModelStatic::SetMaxCount(frameNode, *convValue);
}
void MinCountImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    GridModelStatic::SetMinCount(frameNode, *convValue);
}
void CellLengthImpl(Ark_NativePointer node,
                    const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    GridModelStatic::SetCellLength(frameNode, *convValue);
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         const Opt_GridDirection* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelStatic::SetLayoutDirection(frameNode, Converter::OptConvert<FlexDirection>(*value));
}
void SupportAnimationImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    GridModelStatic::SetSupportAnimation(frameNode, *convValue);
}
void OnItemDragStartImpl(Ark_NativePointer node,
                         const Opt_GridAttribute_onItemDragStart_event_type* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onItemDragStart = [callback = CallbackHelper(*optValue), frameNode, node](
        const ItemDragInfo& dragInfo, int32_t itemIndex
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Number>(itemIndex);
        auto builder =
            callback.InvokeWithObtainCallback<CustomNodeBuilder, Callback_CustomBuilder_Void>(
                arkDragInfo, arkItemIndex);
        auto uiNode = builder->BuildSync(node);
        ViewStackProcessor::GetInstance()->Push(uiNode);
    };
    GridModelStatic::SetOnItemDragStart(frameNode, std::move(onItemDragStart));
}
void OnItemDragEnterImpl(Ark_NativePointer node,
                         const Opt_Callback_ItemDragInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onItemDragEnter = [arkCallback = CallbackHelper(*optValue)](
        const ItemDragInfo& dragInfo
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        arkCallback.Invoke(arkDragInfo);
    };
    GridModelStatic::SetOnItemDragEnter(frameNode, std::move(onItemDragEnter));
}
void OnItemDragMoveImpl(Ark_NativePointer node,
                        const Opt_Callback_ItemDragInfo_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onItemDragMove = [arkCallback = CallbackHelper(*optValue)](
        const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Number>(itemIndex);
        auto arkInsertIndex = Converter::ArkValue<Ark_Number>(insertIndex);
        arkCallback.Invoke(arkDragInfo, arkItemIndex, arkInsertIndex);
    };
    GridModelStatic::SetOnItemDragMove(frameNode, std::move(onItemDragMove));
}
void OnItemDragLeaveImpl(Ark_NativePointer node,
                         const Opt_Callback_ItemDragInfo_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onItemDragLeave = [arkCallback = CallbackHelper(*optValue)](
        const ItemDragInfo& dragInfo, int32_t itemIndex
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Number>(itemIndex);
        arkCallback.Invoke(arkDragInfo, arkItemIndex);
    };

    GridModelStatic::SetOnItemDragLeave(frameNode, std::move(onItemDragLeave));
}
void OnItemDropImpl(Ark_NativePointer node,
                    const Opt_Callback_ItemDragInfo_Number_Number_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onItemDrop = [arkCallback = CallbackHelper(*optValue), frameNode](
        const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Number>(itemIndex);
        auto arkInsertIndex = Converter::ArkValue<Ark_Number>(insertIndex);
        auto arkIsSuccess = Converter::ArkValue<Ark_Boolean>(isSuccess);
        arkCallback.Invoke(arkDragInfo, arkItemIndex, arkInsertIndex, arkIsSuccess);
    };
    GridModelStatic::SetOnItemDrop(frameNode, std::move(onItemDrop));
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Opt_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<NestedScrollOptions>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    GridModelStatic::SetNestedScroll(frameNode, *convValue);
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    GridModelStatic::SetScrollEnabled(frameNode, *convValue);
}
void FrictionImpl(Ark_NativePointer node,
                  const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelStatic::SetFriction(frameNode, Converter::OptConvert<float>(*value));
}
void AlignItemsImpl(Ark_NativePointer node,
                    const Opt_GridItemAlignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelStatic::SetAlignItems(frameNode,
        value ? Converter::OptConvert<GridItemAlignment>(*value) : std::nullopt);
}
void OnScrollImpl(Ark_NativePointer node,
                  const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onScroll = [arkCallback = CallbackHelper(*optValue)]
    (const CalcDimension& scrollOffset, const ScrollState& scrollState) {
        auto arkScrollOffset = Converter::ArkValue<Ark_Number>(scrollOffset);
        auto arkScrollState = Converter::ArkValue<Ark_Number>(static_cast<int>(scrollState));
        arkCallback.Invoke(arkScrollOffset, arkScrollState);
    };
    GridModelStatic::SetOnScroll(frameNode, std::move(onScroll));
}
void OnReachStartImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onReachStart = [arkCallback = CallbackHelper(*optValue), frameNode]() {
        arkCallback.Invoke();
    };
    GridModelStatic::SetOnReachStart(frameNode, std::move(onReachStart));
}
void OnReachEndImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onReachEnd = [arkCallback = CallbackHelper(*optValue), frameNode]() {
        arkCallback.Invoke();
    };
    GridModelStatic::SetOnReachEnd(frameNode, std::move(onReachEnd));
}
void OnScrollStartImpl(Ark_NativePointer node,
                       const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onScrollStart = [arkCallback = CallbackHelper(*optValue), frameNode]() {
        arkCallback.Invoke();
    };
    GridModelStatic::SetOnScrollStart(frameNode, std::move(onScrollStart));
}
void OnScrollStopImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onScrollStop = [arkCallback = CallbackHelper(*optValue), frameNode]() {
        arkCallback.Invoke();
    };
    GridModelStatic::SetOnScrollStop(frameNode, std::move(onScrollStop));
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            const Opt_OnScrollFrameBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onScrollFrameEvent = [callback = CallbackHelper(*optValue)](
        Dimension dimension, ScrollState state) -> ScrollFrameResult {
        Ark_Number arkValue = Converter::ArkValue<Ark_Number>(dimension);
        Ark_ScrollState arkState = Converter::ArkValue<Ark_ScrollState>(state);
        ScrollFrameResult result { .offset = dimension};
        return callback.InvokeWithOptConvertResult<
            ScrollFrameResult, Ark_OnScrollFrameBeginHandlerResult,
            Callback_OnScrollFrameBeginHandlerResult_Void>(arkValue, arkState)
            .value_or(result);
    };
    GridModelStatic::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameEvent));
}
void OnWillScrollImpl(Ark_NativePointer node,
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
            auto arkScrollOffset = Converter::ArkValue<Ark_Number>(scrollOffset);
            auto arkScrollState = Converter::ArkValue<Ark_ScrollState>(scrollState);
            auto arkScrollSource = Converter::ArkValue<Ark_ScrollSource>(scrollSource);
            auto resultOpt =
                callback.InvokeWithOptConvertResult<ScrollFrameResult, Ark_ScrollResult, Callback_ScrollResult_Void>(
                    arkScrollOffset, arkScrollState, arkScrollSource);
            return resultOpt.value_or(ScrollFrameResult());
        };
        ScrollableModelStatic::SetOnWillScroll(frameNode, std::move(modelCallback));
    } else {
        ScrollableModelStatic::SetOnWillScroll(frameNode, nullptr);
    }
}
void OnDidScrollImpl(Ark_NativePointer node,
                     const Opt_OnScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto callValue = Converter::OptConvert<OnScrollCallback>(*value);
    if (!callValue.has_value()) {
        return;
    }
    auto onDidScroll = [arkCallback = CallbackHelper(callValue.value())](
        Dimension oIn, ScrollState stateIn) {
            auto state = Converter::ArkValue<Ark_ScrollState>(stateIn);
            auto scrollOffset = Converter::ArkValue<Ark_Number>(oIn);
            arkCallback.Invoke(scrollOffset, state);
    };
    ScrollableModelStatic::SetOnDidScroll(frameNode, std::move(onDidScroll));
}
void EdgeEffectImpl(Ark_NativePointer node,
                    const Opt_EdgeEffect* value,
                    const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelStatic::SetEdgeEffect(frameNode, Converter::OptConvert<EdgeEffect>(*value),
        options ? Converter::OptConvert<bool>(*options) : std::nullopt);
}
} // GridAttributeModifier
const GENERATED_ArkUIGridModifier* GetGridModifier()
{
    static const GENERATED_ArkUIGridModifier ArkUIGridModifierImpl {
        GridModifier::ConstructImpl,
        GridInterfaceModifier::SetGridOptionsImpl,
        GridAttributeModifier::ColumnsTemplateImpl,
        GridAttributeModifier::RowsTemplateImpl,
        GridAttributeModifier::ColumnsGapImpl,
        GridAttributeModifier::RowsGapImpl,
        GridAttributeModifier::ScrollBarWidthImpl,
        GridAttributeModifier::ScrollBarColorImpl,
        GridAttributeModifier::ScrollBarImpl,
        GridAttributeModifier::OnScrollBarUpdateImpl,
        GridAttributeModifier::OnScrollIndexImpl,
        GridAttributeModifier::CachedCount0Impl,
        GridAttributeModifier::CachedCount1Impl,
        GridAttributeModifier::EditModeImpl,
        GridAttributeModifier::MultiSelectableImpl,
        GridAttributeModifier::MaxCountImpl,
        GridAttributeModifier::MinCountImpl,
        GridAttributeModifier::CellLengthImpl,
        GridAttributeModifier::LayoutDirectionImpl,
        GridAttributeModifier::SupportAnimationImpl,
        GridAttributeModifier::OnItemDragStartImpl,
        GridAttributeModifier::OnItemDragEnterImpl,
        GridAttributeModifier::OnItemDragMoveImpl,
        GridAttributeModifier::OnItemDragLeaveImpl,
        GridAttributeModifier::OnItemDropImpl,
        GridAttributeModifier::NestedScrollImpl,
        GridAttributeModifier::EnableScrollInteractionImpl,
        GridAttributeModifier::FrictionImpl,
        GridAttributeModifier::AlignItemsImpl,
        GridAttributeModifier::OnScrollImpl,
        GridAttributeModifier::OnReachStartImpl,
        GridAttributeModifier::OnReachEndImpl,
        GridAttributeModifier::OnScrollStartImpl,
        GridAttributeModifier::OnScrollStopImpl,
        GridAttributeModifier::OnScrollFrameBeginImpl,
        GridAttributeModifier::OnWillScrollImpl,
        GridAttributeModifier::OnDidScrollImpl,
        GridAttributeModifier::EdgeEffectImpl,
    };
    return &ArkUIGridModifierImpl;
}
}
