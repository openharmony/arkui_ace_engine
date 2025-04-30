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

#include "arkoala_api_generated.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/interfaces/native/implementation/scroller_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

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
        case ARK_GRID_ITEM_ALIGNMENT_DEFAULT:
            dst = GridItemAlignment::DEFAULT;
            break;
        case ARK_GRID_ITEM_ALIGNMENT_STRETCH:
            dst = GridItemAlignment::STRETCH;
            break;
        default:
            LOGE("Unexpected enum value in Ark_GridItemAlignment: %{public}d", src);
    }
}

template<>
inline void AssignCast(std::optional<GridItemSize>& dst, const Ark_Tuple_Number_Number& src)
{
    dst->rows = Converter::Convert<int32_t>(src.value0);
    dst->columns = Converter::Convert<int32_t>(src.value1);
}

template<>
inline void AssignCast(std::optional<GridItemRect>& dst, const Ark_Tuple_Number_Number_Number_Number& src)
{
    dst->rowStart = Converter::Convert<int32_t>(src.value0);
    dst->rowSpan = Converter::Convert<int32_t>(src.value1);
    dst->columnStart = Converter::Convert<int32_t>(src.value2);
    dst->columnSpan = Converter::Convert<int32_t>(src.value3);
}

} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GridModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = GridModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // namespace GridModifier
namespace GridInterfaceModifier {
void SetScroll(FrameNode* frameNode, const Opt_Scroller* scroller)
{
    CHECK_NULL_VOID(scroller);
    RefPtr<ScrollControllerBase> positionController = GridModelNG::GetOrCreateController(frameNode);
    RefPtr<ScrollProxy> scrollBarProxy = GridModelNG::GetOrCreateScrollBarProxy(frameNode);
    auto abstPeerPtrOpt = Converter::OptConvert<Ark_Scroller>(*scroller);
    CHECK_NULL_VOID(abstPeerPtrOpt);
    auto peerImplPtr = *abstPeerPtrOpt;
    CHECK_NULL_VOID(peerImplPtr);
    peerImplPtr->SetController(positionController);
    peerImplPtr->SetScrollBarProxy(scrollBarProxy);
}
void SetGridOptionsImpl(
    Ark_NativePointer node, const Opt_Scroller* scroller, const Opt_GridLayoutOptions* layoutOptions)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Ark_GridLayoutOptions> layoutOptionsOpt;
    if (layoutOptions->tag != ARK_TAG_UNDEFINED) {
        layoutOptionsOpt = Converter::OptConvert<Ark_GridLayoutOptions>(layoutOptions->value);
    }
    if (layoutOptionsOpt) {
        GridLayoutOptions options;
        std::optional<GridItemSize> regularSizeOpt = Converter::OptConvert<GridItemSize>(layoutOptions->value);
        if (regularSizeOpt) {
            options.regularSize = regularSizeOpt.value();
        }
        std::optional<std::set<int32_t>> irrIndex = Converter::OptConvert<std::set<int32_t>>(layoutOptions->value);
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
        GridModelNG::SetLayoutOptions(frameNode, options);
    }
    SetScroll(frameNode, scroller);
}
} // namespace GridInterfaceModifier
namespace GridAttributeModifier {
void ColumnsTemplateImpl(Ark_NativePointer node, const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetColumnsTemplate(frameNode, Converter::Convert<std::string>(value->value));
}
void RowsTemplateImpl(Ark_NativePointer node, const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetRowsTemplate(frameNode, Converter::Convert<std::string>(value->value));
}
void ColumnsGapImpl(Ark_NativePointer node, const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        GridModelNG::SetColumnsGap(frameNode, std::optional<Dimension>(0));
        return;
    }
    GridModelNG::SetColumnsGap(frameNode, Converter::OptConvert<Dimension>(*value));
}
void RowsGapImpl(Ark_NativePointer node, const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        GridModelNG::SetRowsGap(frameNode, std::optional<Dimension>(0));
        return;
    }
    GridModelNG::SetRowsGap(frameNode, Converter::OptConvert<Dimension>(*value));
}
void ScrollBarWidthImpl(Ark_NativePointer node, const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetScrollBarWidth(frameNode, Converter::OptConvert<Dimension>(*value));
}
void ScrollBarColorImpl(Ark_NativePointer node, const Opt_Union_Color_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetScrollBarColor(frameNode, Converter::OptConvert<Color>(*value));
}
void ScrollBarImpl(Ark_NativePointer node, const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        GridModelNG::SetScrollBarMode(frameNode, std::make_optional<DisplayMode>(DisplayMode::AUTO));
        return;
    }
    GridModelNG::SetScrollBarMode(frameNode, Converter::OptConvert<DisplayMode>(value->value));
}
void OnScrollBarUpdateImpl(Ark_NativePointer node, const Opt_Callback_Number_Number_ComputedBarAttribute* value)
{
    using namespace Converter;
    using ResType = std::pair<std::optional<float>, std::optional<float>>;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollBarUpdate =
        [callback = CallbackHelper(value->value)](int32_t index, const Dimension& offset) -> ResType {
        auto arkIndex = ArkValue<Ark_Number>(index);
        auto arkOffset = ArkValue<Ark_Number>(offset);
        auto arkResult = callback.InvokeWithObtainResult<Ark_ComputedBarAttribute, Callback_ComputedBarAttribute_Void>(
            arkIndex, arkOffset);
        return ResType(Convert<float>(arkResult.totalOffset), Convert<float>(arkResult.totalLength));
    };
    GridModelNG::SetOnScrollBarUpdate(frameNode, std::move(onScrollBarUpdate));
}
void OnScrollIndexImpl(Ark_NativePointer node, const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollIndex = [arkCallback = CallbackHelper(value->value)](const int32_t first, const int32_t last) {
        auto arkFirst = Converter::ArkValue<Ark_Number>(first);
        auto arkLast = Converter::ArkValue<Ark_Number>(last);
        arkCallback.Invoke(arkFirst, arkLast);
    };
    GridModelNG::SetOnScrollIndex(frameNode, std::move(onScrollIndex));
}
void CachedCount0Impl(Ark_NativePointer node, const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag != ARK_TAG_UNDEFINED) {
        GridModelNG::SetCachedCount(frameNode, Converter::Convert<int32_t>(value->value));
    }
}
void CachedCount1Impl(Ark_NativePointer node, const Opt_Number* count, const Opt_Boolean* show)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    // auto countValue = Converter::Convert<int32_t>(count->value);
    // auto showValue = Converter::OptConvert<bool>(*show);
    // GridModelNG::SetCachedCount(frameNode, countValue, showValue);
}
void EditModeImpl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto editModeValue = Converter::OptConvert<bool>(*value);
    GridModelNG::SetEditable(frameNode, editModeValue.value_or(false));
}
void MultiSelectableImpl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto multiSelectableValue = Converter::OptConvert<bool>(*value);
    GridModelNG::SetMultiSelectable(frameNode, multiSelectableValue.value_or(false));
}
void MaxCountImpl(Ark_NativePointer node, const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetMaxCount(frameNode, Converter::OptConvert<int32_t>(value->value).value_or(0));
}
void MinCountImpl(Ark_NativePointer node, const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetMinCount(frameNode, Converter::OptConvert<int32_t>(value->value).value_or(1));
}
void CellLengthImpl(Ark_NativePointer node, const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetCellLength(frameNode, Converter::OptConvert<int32_t>(value->value).value_or(-1));
}
void LayoutDirectionImpl(Ark_NativePointer node, const Opt_GridDirection* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetLayoutDirection(frameNode, Converter::OptConvert<FlexDirection>(value->value));
}
void SupportAnimationImpl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto supportAnimationValue = Converter::OptConvert<bool>(*value);
    GridModelNG::SetSupportAnimation(frameNode, supportAnimationValue.value_or(false));
}
void OnItemDragStartImpl(Ark_NativePointer node, const Opt_GridAttribute_onItemDragStart_event_type* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemDragStart = [callback = CallbackHelper(value->value), frameNode, node](
        const ItemDragInfo& dragInfo, int32_t itemIndex
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Number>(itemIndex);
        auto builder =
            callback.InvokeWithObtainResult<CustomNodeBuilder, Callback_CustomBuilder_Void>(arkDragInfo, arkItemIndex);
        auto uiNode = CallbackHelper(builder).BuildSync(node);
        ViewStackProcessor::GetInstance()->Push(uiNode);
    };
    GridModelNG::SetOnItemDragStart(frameNode, std::move(onItemDragStart));
}
void OnItemDragEnterImpl(Ark_NativePointer node, const Opt_Callback_ItemDragInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemDragEnter = [arkCallback = CallbackHelper(value->value)](
        const ItemDragInfo& dragInfo
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        arkCallback.Invoke(arkDragInfo);
    };
    GridModelNG::SetOnItemDragEnter(frameNode, std::move(onItemDragEnter));
}
void OnItemDragMoveImpl(Ark_NativePointer node, const Opt_Callback_ItemDragInfo_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemDragMove = [arkCallback = CallbackHelper(value->value)](
        const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Number>(itemIndex);
        auto arkInsertIndex = Converter::ArkValue<Ark_Number>(insertIndex);
        arkCallback.Invoke(arkDragInfo, arkItemIndex, arkInsertIndex);
    };
    GridModelNG::SetOnItemDragMove(frameNode, std::move(onItemDragMove));
}
void OnItemDragLeaveImpl(Ark_NativePointer node, const Opt_Callback_ItemDragInfo_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemDragLeave = [arkCallback = CallbackHelper(value->value)](
        const ItemDragInfo& dragInfo, int32_t itemIndex
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Number>(itemIndex);
        arkCallback.Invoke(arkDragInfo, arkItemIndex);
    };

    GridModelNG::SetOnItemDragLeave(frameNode, std::move(onItemDragLeave));
}
void OnItemDropImpl(Ark_NativePointer node,
                    const Opt_Callback_ItemDragInfo_Number_Number_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemDrop = [arkCallback = CallbackHelper(value->value), frameNode](
        const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess
    ) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        auto arkItemIndex = Converter::ArkValue<Ark_Number>(itemIndex);
        auto arkInsertIndex = Converter::ArkValue<Ark_Number>(insertIndex);
        auto arkIsSuccess = Converter::ArkValue<Ark_Boolean>(isSuccess);
        arkCallback.Invoke(arkDragInfo, arkItemIndex, arkInsertIndex, arkIsSuccess);
    };
    GridModelNG::SetOnItemDrop(frameNode, std::move(onItemDrop));
}
void NestedScrollImpl(Ark_NativePointer node, const Opt_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetNestedScroll(frameNode, Converter::Convert<NestedScrollOptions>(value->value));
}
void EnableScrollInteractionImpl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollEnabled(frameNode, Converter::OptConvert<bool>(*value).value_or(true));
}
void FrictionImpl(Ark_NativePointer node, const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetFriction(frameNode, Converter::OptConvert<float>(value->value));
}
void AlignItemsImpl(Ark_NativePointer node, const Opt_GridItemAlignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetAlignItems(frameNode,
        value ? Converter::OptConvert<GridItemAlignment>(value->value) : std::nullopt);
}
void OnScrollImpl(Ark_NativePointer node, const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScroll = [frameNode](const CalcDimension& scrollOffset, const ScrollState& scrollState) {
#ifdef WRONG_INTERFACE
        auto arkScrollOffset = Converter::ArkValue<Ark_Number>(scrollOffset);
        auto arkScrollState = Converter::ArkValue<Ark_ScrollState>(scrollState);
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onScroll(
            frameNode->GetId(), arkScrollOffset, arkScrollState);
#endif
    };
    GridModelNG::SetOnScroll(frameNode, std::move(onScroll));
}
void OnReachStartImpl(Ark_NativePointer node, const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onReachStart = [arkCallback = CallbackHelper(value->value), frameNode]() {
        arkCallback.Invoke();
    };
    GridModelNG::SetOnReachStart(frameNode, std::move(onReachStart));
}
void OnReachEndImpl(Ark_NativePointer node, const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onReachEnd = [arkCallback = CallbackHelper(value->value), frameNode]() {
        arkCallback.Invoke();
    };
    GridModelNG::SetOnReachEnd(frameNode, std::move(onReachEnd));
}
void OnScrollStartImpl(Ark_NativePointer node, const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollStart = [arkCallback = CallbackHelper(value->value), frameNode]() {
        arkCallback.Invoke();
    };
    GridModelNG::SetOnScrollStart(frameNode, std::move(onScrollStart));
}
void OnScrollStopImpl(Ark_NativePointer node, const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollStop = [arkCallback = CallbackHelper(value->value), frameNode]() {
        arkCallback.Invoke();
    };
    GridModelNG::SetOnScrollStop(frameNode, std::move(onScrollStop));
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            const Opt_Callback_Number_ScrollState_Literal_Number_offsetRemain* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollFrameBegin = [callback = CallbackHelper(value->value)](
            const Dimension& offset, const ScrollState& state
        ) -> ScrollFrameResult {
        auto arkOffset = Converter::ArkValue<Ark_Number>(offset);
        auto arkState = Converter::ArkValue<Ark_ScrollState>(state);
        auto arkResult = callback.InvokeWithObtainResult<Ark_Literal_Number_offsetRemain,
            Callback_Literal_Number_offsetRemain_Void>(arkOffset, arkState);
        return {
            .offset = Converter::Convert<Dimension>(arkResult.offsetRemain)
        };
    };
    GridModelNG::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameBegin));
}
void EdgeEffectImpl(Ark_NativePointer node, const Opt_EdgeEffect* value, const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<EdgeEffect> edgeEffectValue = std::make_optional<EdgeEffect>(EdgeEffect::NONE);
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        edgeEffectValue = Converter::OptConvert<EdgeEffect>(value->value);
    }
    std::optional<bool> optionsValue = std::nullopt;
    if (options) {
        optionsValue = Converter::OptConvert<bool>(options->value);
    }
    GridModelNG::SetEdgeEffect(frameNode, edgeEffectValue, optionsValue);
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
        GridAttributeModifier::EdgeEffectImpl,
    };
    return &ArkUIGridModifierImpl;
}
}
