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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/implementation/scroller_peer_impl.h"

namespace OHOS::Ace::NG::Converter {

template<>
inline void AssignCast(std::optional<GridItemSize>& dst, const Ark_GridLayoutOptions& src)
{
    dst->rows = Converter::Convert<int32_t>(src.regularSize.value0);
    dst->columns = Converter::Convert<int32_t>(src.regularSize.value1);
}

template<>
inline void AssignCast(std::optional<std::set<int32_t>>& dst, const Array_Int32& src)
{
    auto length = static_cast<int32_t>(src.length);
    std::set<int32_t> indexesSet;
    for (int i = 0; i < length; i++) {
        auto currentValue = Converter::Convert<int32_t>(src.array[i]);
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
inline void AssignCast(std::optional<GridItemSize>& dst, const Ark_Tuple_I32_I32& src)
{
    auto rows = Converter::Convert<int32_t>(src.value0);
    auto columns = Converter::Convert<int32_t>(src.value1);
    dst = {.rows = rows, .columns = columns};
}

template<>
inline void AssignCast(std::optional<GridItemRect>& dst, const Ark_Tuple_I32_I32_I32_I32& src)
{
    auto rowStart = Converter::Convert<int32_t>(src.value0);
    auto columnStart = Converter::Convert<int32_t>(src.value1);
    auto rowSpan = Converter::Convert<int32_t>(src.value2);
    auto columnSpan = Converter::Convert<int32_t>(src.value3);
    dst = {.rowStart = rowStart, .rowSpan = rowSpan, .columnStart = columnStart, .columnSpan = columnSpan};
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
    auto abstPeerPtrOpt = Converter::OptConvertPtr<Ark_Scroller>(scroller);
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
    auto layoutOptionsOpt = Converter::OptConvertPtr<Ark_GridLayoutOptions>(layoutOptions);
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
        auto onGetIrregularSizeByIndex = Converter::OptConvert<::Callback_I32_Tuple_I32_I32>
                                    (layoutOptionsOpt.value().onGetIrregularSizeByIndex);
        if (onGetIrregularSizeByIndex) {
            auto modelCallback = [callback = CallbackHelper(*onGetIrregularSizeByIndex)]
                                            (int32_t value) -> GridItemSize {
                Ark_Int32 param = Converter::ArkValue<Ark_Int32>(value);
                auto resultOpt = callback.InvokeWithOptConvertResult
                                    <GridItemSize, Ark_Tuple_I32_I32, Callback_Tuple_I32_I32_Void>(param);
                return resultOpt.value_or(GridItemSize());
            };
            options.getSizeByIndex = modelCallback;
        }
        auto onGetRectByIndex = Converter::OptConvert<::Callback_I32_Tuple_I32_I32_I32_I32>
                                    (layoutOptionsOpt.value().onGetRectByIndex);
        if (onGetRectByIndex) {
            auto modelCallback = [callback = CallbackHelper(*onGetRectByIndex)](int32_t value) -> GridItemRect {
                Ark_Int32 param = Converter::ArkValue<Ark_Int32>(value);
                auto resOpt = callback.InvokeWithOptConvertResult<GridItemRect, Ark_Tuple_I32_I32_I32_I32,
                                     Callback_Tuple_I32_I32_I32_I32_Void>(param);
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
void SetColumnsTemplateImpl(Ark_NativePointer node,
                            const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        GridModelStatic::SetColumnsTemplate(frameNode, std::nullopt);
        return;
    }
    GridModelStatic::SetColumnsTemplate(frameNode, *convValue);
}
void SetRowsTemplateImpl(Ark_NativePointer node,
                         const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        GridModelStatic::SetRowsTemplate(frameNode, std::nullopt);
        return;
    }
    GridModelStatic::SetRowsTemplate(frameNode, *convValue);
}
void SetColumnsGapImpl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
    GridModelStatic::SetColumnsGap(frameNode, convValue);
}
void SetRowsGapImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
    GridModelStatic::SetRowsGap(frameNode, convValue);
}
void SetScrollBarWidthImpl(Ark_NativePointer node,
                           const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    ScrollableModelStatic::SetScrollBarWidth(frameNode, convValue);
}
void SetScrollBarColorImpl(Ark_NativePointer node,
                           const Opt_Union_Color_I32_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    ScrollableModelStatic::SetScrollBarColor(frameNode, convValue);
}
void SetScrollBarImpl(Ark_NativePointer node,
                      const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<DisplayMode>(value);
    ScrollableModelStatic::SetScrollBarMode(frameNode, convValue);
}
void SetOnScrollBarUpdateImpl(Ark_NativePointer node,
                              const Opt_Callback_I32_F64_ComputedBarAttribute* value)
{
    using namespace Converter;
    using ResType = std::pair<std::optional<float>, std::optional<float>>;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        GridModelStatic::SetOnScrollBarUpdate(frameNode, nullptr);
        return;
    }
    auto onScrollBarUpdate =
        [callback = CallbackHelper(*optValue)](int32_t index, const Dimension& offset) -> ResType {
        auto arkIndex = ArkValue<Ark_Int32>(index);
        auto arkOffset = ArkValue<Ark_Float64>(offset);
        auto arkResult = callback.InvokeWithObtainResult<Ark_ComputedBarAttribute, Callback_ComputedBarAttribute_Void>(
            arkIndex, arkOffset);
        auto totalOffset = Convert<Dimension>(arkResult.totalOffset).ConvertToPx();
        auto totalLength = Convert<Dimension>(arkResult.totalLength).ConvertToPx();
        return ResType(totalOffset, totalLength);
    };
    GridModelStatic::SetOnScrollBarUpdate(frameNode, std::move(onScrollBarUpdate));
}
void SetOnScrollIndexImpl(Ark_NativePointer node,
                          const Opt_Callback_I32_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        GridModelStatic::SetOnScrollIndex(frameNode, nullptr);
        return;
    }
    auto onScrollIndex = [arkCallback = CallbackHelper(*optValue)](const int32_t first, const int32_t last) {
        auto arkFirst = Converter::ArkValue<Ark_Int32>(first);
        auto arkLast = Converter::ArkValue<Ark_Int32>(last);
        arkCallback.Invoke(arkFirst, arkLast);
    };
    GridModelStatic::SetOnScrollIndex(frameNode, std::move(onScrollIndex));
}
void SetCachedCount0Impl(Ark_NativePointer node,
                         const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        GridModelStatic::SetCachedCount(frameNode, std::nullopt);
        return;
    }
    GridModelStatic::SetCachedCount(frameNode, *convValue);
}
void SetEditModeImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        GridModelStatic::SetEditable(frameNode, std::nullopt);
        return;
    }
    GridModelStatic::SetEditable(frameNode, *convValue);
}
void SetMultiSelectableImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        GridModelStatic::SetMultiSelectable(frameNode, false);
        return;
    }
    GridModelStatic::SetMultiSelectable(frameNode, *convValue);
}
void SetMaxCountImpl(Ark_NativePointer node,
                     const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        GridModelStatic::SetMaxCount(frameNode, std::nullopt);
        return;
    }
    GridModelStatic::SetMaxCount(frameNode, *convValue);
}
void SetMinCountImpl(Ark_NativePointer node,
                     const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        GridModelStatic::SetMinCount(frameNode, std::nullopt);
        return;
    }
    GridModelStatic::SetMinCount(frameNode, *convValue);
}
void SetCellLengthImpl(Ark_NativePointer node,
                       const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        GridModelStatic::SetCellLength(frameNode, std::nullopt);
        return;
    }
    GridModelStatic::SetCellLength(frameNode, *convValue);
}
void SetLayoutDirectionImpl(Ark_NativePointer node,
                            const Opt_GridDirection* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelStatic::SetLayoutDirection(frameNode, Converter::OptConvertPtr<FlexDirection>(value));
}
void SetSupportAnimationImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        GridModelStatic::SetSupportAnimation(frameNode, false);
        return;
    }
    GridModelStatic::SetSupportAnimation(frameNode, *convValue);
}
void SetOnItemDragStartImpl(Ark_NativePointer node,
                            const Opt_OnItemDragStartCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        GridModelStatic::ResetOnItemDragStart(frameNode);
        return;
    }
    auto onItemDragStart = [callback = CallbackHelper(*optValue), frameNode, node](
                               const ItemDragInfo& dragInfo, int32_t itemIndex) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Int32>(itemIndex);
        auto builderOpt = callback.InvokeWithOptConvertResult<CustomNodeBuilder, Opt_CustomNodeBuilder,
            Callback_Opt_CustomBuilder_Void>(arkDragInfo, arkItemIndex);
        if (builderOpt.has_value()) {
            auto uiNode = CallbackHelper(builderOpt.value()).BuildSync(node);
            ViewStackProcessor::GetInstance()->Push(uiNode);
        }
    };
    GridModelStatic::SetOnItemDragStart(frameNode, std::move(onItemDragStart));
}
void SetOnItemDragEnterImpl(Ark_NativePointer node,
                            const Opt_Callback_ItemDragInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        GridModelStatic::SetOnItemDragEnter(frameNode, nullptr);
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
void SetOnItemDragMoveImpl(Ark_NativePointer node,
                           const Opt_Callback_ItemDragInfo_I32_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        GridModelStatic::SetOnItemDragMove(frameNode, nullptr);
        return;
    }
    auto onItemDragMove = [arkCallback = CallbackHelper(*optValue)](
        const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Int32>(itemIndex);
        auto arkInsertIndex = Converter::ArkValue<Ark_Int32>(insertIndex);
        arkCallback.Invoke(arkDragInfo, arkItemIndex, arkInsertIndex);
    };
    GridModelStatic::SetOnItemDragMove(frameNode, std::move(onItemDragMove));
}
void SetOnItemDragLeaveImpl(Ark_NativePointer node,
                            const Opt_Callback_ItemDragInfo_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        GridModelStatic::SetOnItemDragLeave(frameNode, nullptr);
        return;
    }
    auto onItemDragLeave = [arkCallback = CallbackHelper(*optValue)](
        const ItemDragInfo& dragInfo, int32_t itemIndex
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Int32>(itemIndex);
        arkCallback.Invoke(arkDragInfo, arkItemIndex);
    };

    GridModelStatic::SetOnItemDragLeave(frameNode, std::move(onItemDragLeave));
}
void SetOnItemDropImpl(Ark_NativePointer node,
                       const Opt_Callback_ItemDragInfo_I32_I32_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        GridModelStatic::SetOnItemDrop(frameNode, nullptr);
        return;
    }
    auto onItemDrop = [arkCallback = CallbackHelper(*optValue), frameNode](
        const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Int32>(itemIndex);
        auto arkInsertIndex = Converter::ArkValue<Ark_Int32>(insertIndex);
        auto arkIsSuccess = Converter::ArkValue<Ark_Boolean>(isSuccess);
        arkCallback.Invoke(arkDragInfo, arkItemIndex, arkInsertIndex, arkIsSuccess);
    };
    GridModelStatic::SetOnItemDrop(frameNode, std::move(onItemDrop));
}
void SetNestedScrollImpl(Ark_NativePointer node,
                         const Opt_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::GetOptPtr(value);
    if (!convValue) {
        ScrollableModelStatic::SetNestedScroll(frameNode, std::nullopt, std::nullopt);
        return;
    }
    auto forward = Converter::OptConvert<NestedScrollMode>(convValue->scrollForward);
    auto backward = Converter::OptConvert<NestedScrollMode>(convValue->scrollBackward);
    ScrollableModelStatic::SetNestedScroll(frameNode, forward, backward);
}
void SetEnableScrollInteractionImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        GridModelStatic::SetScrollEnabled(frameNode, std::nullopt);
        return;
    }
    auto scrollEnabled = *convValue;
    GridModelStatic::SetScrollEnabled(frameNode, scrollEnabled);
}
void SetFrictionImpl(Ark_NativePointer node,
                     const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    ScrollableModelStatic::SetFriction(frameNode, convValue);
}
void SetAlignItemsImpl(Ark_NativePointer node,
                       const Opt_GridItemAlignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelStatic::SetAlignItems(frameNode, Converter::OptConvertPtr<GridItemAlignment>(value));
}
void SetOnScrollFrameBeginImpl(Ark_NativePointer node,
                               const Opt_OnScrollFrameBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        GridModelStatic::SetOnScrollFrameBegin(frameNode, nullptr);
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
    GridModelStatic::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameEvent));
}
void SetOnWillScrollImpl(Ark_NativePointer node,
                         const Opt_OnWillScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SetOnDidScrollImpl(Ark_NativePointer node,
                        const Opt_OnScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto callValue = Converter::OptConvertPtr<OnScrollCallback>(value);
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
void SetCachedCount1Impl(Ark_NativePointer node,
                         const Opt_Int32* count,
                         const Opt_Boolean* show)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(count);
    if (!convValue) {
        GridModelStatic::SetCachedCount(frameNode, std::nullopt);
    } else {
        GridModelStatic::SetCachedCount(frameNode, *convValue);
    }

    auto showValue = Converter::OptConvertPtr<bool>(show);
    if (!showValue) {
        GridModelStatic::SetShowCached(frameNode, std::nullopt);
    } else {
        GridModelStatic::SetShowCached(frameNode, *showValue);
    }
}
void SetEdgeEffectImpl(Ark_NativePointer node, const Opt_EdgeEffect* value, const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convEdgeEffect = Converter::OptConvert<EdgeEffect>(*value);

    bool alwaysEnabled = false;
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
} // GridAttributeModifier
const GENERATED_ArkUIGridModifier* GetGridModifier()
{
    static const GENERATED_ArkUIGridModifier ArkUIGridModifierImpl {
        GridModifier::ConstructImpl,
        GridInterfaceModifier::SetGridOptionsImpl,
        GridAttributeModifier::SetColumnsTemplateImpl,
        GridAttributeModifier::SetRowsTemplateImpl,
        GridAttributeModifier::SetColumnsGapImpl,
        GridAttributeModifier::SetRowsGapImpl,
        GridAttributeModifier::SetScrollBarWidthImpl,
        GridAttributeModifier::SetScrollBarColorImpl,
        GridAttributeModifier::SetScrollBarImpl,
        GridAttributeModifier::SetOnScrollBarUpdateImpl,
        GridAttributeModifier::SetOnScrollIndexImpl,
        GridAttributeModifier::SetCachedCount0Impl,
        GridAttributeModifier::SetEditModeImpl,
        GridAttributeModifier::SetMultiSelectableImpl,
        GridAttributeModifier::SetMaxCountImpl,
        GridAttributeModifier::SetMinCountImpl,
        GridAttributeModifier::SetCellLengthImpl,
        GridAttributeModifier::SetLayoutDirectionImpl,
        GridAttributeModifier::SetSupportAnimationImpl,
        GridAttributeModifier::SetOnItemDragStartImpl,
        GridAttributeModifier::SetOnItemDragEnterImpl,
        GridAttributeModifier::SetOnItemDragMoveImpl,
        GridAttributeModifier::SetOnItemDragLeaveImpl,
        GridAttributeModifier::SetOnItemDropImpl,
        GridAttributeModifier::SetNestedScrollImpl,
        GridAttributeModifier::SetEnableScrollInteractionImpl,
        GridAttributeModifier::SetFrictionImpl,
        GridAttributeModifier::SetAlignItemsImpl,
        GridAttributeModifier::SetOnScrollFrameBeginImpl,
        GridAttributeModifier::SetOnWillScrollImpl,
        GridAttributeModifier::SetOnDidScrollImpl,
        GridAttributeModifier::SetCachedCount1Impl,
        GridAttributeModifier::SetEdgeEffectImpl,
    };
    return &ArkUIGridModifierImpl;
}
}
