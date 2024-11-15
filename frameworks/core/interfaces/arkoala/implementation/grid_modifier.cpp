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

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/interfaces/arkoala/implementation/scroller_peer_impl.h"

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
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GridInterfaceModifier {
void SetGridOptionsImpl(Ark_NativePointer node,
                        const Opt_Scroller* scroller,
                        const Opt_GridLayoutOptions* layoutOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (layoutOptions) {
        GridLayoutOptions options;
        std::optional<GridItemSize> regularSizeOpt = Converter::OptConvert<GridItemSize>(*layoutOptions);
        if (regularSizeOpt) {
            options.regularSize = regularSizeOpt.value();
        }
        std::optional<std::set<int32_t>> irregularIndexes = Converter::OptConvert<std::set<int32_t>>(*layoutOptions);
        if (irregularIndexes) {
            options.irregularIndexes = irregularIndexes.value();
        }
        // onGetIrregularSizeByIndex and onGetRectByIndex was not implemented
        // because GENERATED_ArkUIGridEventsReceiver doesn`t support these interfaces
        LOGE("ARKOALA onGetIrregularSizeByIndex callback need to be supported");
        LOGE("ARKOALA onGetRectByIndex callback need to be supported");
        GridModelNG::SetLayoutOptions(frameNode, options);
    }

    // Scroller
    CHECK_NULL_VOID(scroller);
    RefPtr<ScrollControllerBase> positionController = GridModelNG::GetOrCreateController(frameNode);
    RefPtr<ScrollProxy> scrollBarProxy = GridModelNG::GetOrCreateScrollBarProxy(frameNode);

     // obtain the external SwiperController peer
    auto abstPeerPtrOpt = Converter::OptConvert<Ark_NativePointer>(*scroller);
    CHECK_NULL_VOID(abstPeerPtrOpt);
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::ScrollerPeerImpl *>(*abstPeerPtrOpt);
    CHECK_NULL_VOID(peerImplPtr);
    peerImplPtr->SetController(positionController);
    peerImplPtr->SetScrollBarProxy(scrollBarProxy);
}
} // GridInterfaceModifier
namespace GridAttributeModifier {
void ColumnsTemplateImpl(Ark_NativePointer node,
                         const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetColumnsTemplate(frameNode, Converter::Convert<std::string>(*value));
}
void RowsTemplateImpl(Ark_NativePointer node,
                      const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetRowsTemplate(frameNode, Converter::Convert<std::string>(*value));
}
void ColumnsGapImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetColumnsGap(frameNode, Converter::Convert<Dimension>(*value));
}
void RowsGapImpl(Ark_NativePointer node,
                 const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetRowsGap(frameNode, Converter::Convert<Dimension>(*value));
}
void ScrollBarWidthImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetScrollBarWidth(frameNode, Converter::OptConvert<Dimension>(*value));
}
void ScrollBarColorImpl(Ark_NativePointer node,
                        const Ark_Union_Color_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetScrollBarColor(frameNode, Converter::OptConvert<Color>(*value));
}
void ScrollBarImpl(Ark_NativePointer node,
                   Ark_BarState value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollBarMode(frameNode, Converter::OptConvert<DisplayMode>(value));
}
void OnScrollBarUpdateImpl(Ark_NativePointer node,
                           const Callback_Number_Number_ComputedBarAttribute* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollBarUpdate = [frameNode](int32_t index, const Dimension& offset) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        auto arkOffset = Converter::ArkValue<Ark_Number>(offset);
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onScrollBarUpdate(
            frameNode->GetId(), arkIndex, arkOffset);
        // onScrollBarUpdate should return value [totalOffset, totalLength] but it is a void
        // that is a reason why we return [0, 0] pair value as the temporary stub
        LOGE("ARKOALA onScrollBarUpdate doesn`t handle ComputedBarAttribute returned values");
        return std::pair<float, float>(0, 0);
    };
    GridModelNG::SetOnScrollBarUpdate(frameNode, std::move(onScrollBarUpdate));
}
void OnScrollIndexImpl(Ark_NativePointer node,
                       const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollIndex = [frameNode](const int32_t first, const int32_t last) {
        auto arkFirst = Converter::ArkValue<Ark_Number>(first);
        auto arkLast = Converter::ArkValue<Ark_Number>(last);
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onScrollIndex(
            frameNode->GetId(), arkFirst, arkLast);
    };
    GridModelNG::SetOnScrollIndex(frameNode, std::move(onScrollIndex));
}
void CachedCountImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetCachedCount(frameNode, Converter::Convert<int32_t>(*value));
}
void EditModeImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEditable(frameNode, Converter::Convert<bool>(value));
}
void MultiSelectableImpl(Ark_NativePointer node,
                         Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMultiSelectable(frameNode, Converter::Convert<bool>(value));
}
void MaxCountImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetMaxCount(frameNode, Converter::Convert<int32_t>(*value));
}
void MinCountImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetMinCount(frameNode, Converter::Convert<int32_t>(*value));
}
void CellLengthImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetCellLength(frameNode, Converter::Convert<int32_t>(*value));
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         Ark_GridDirection value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetLayoutDirection(frameNode, Converter::OptConvert<FlexDirection>(value));
}
void SupportAnimationImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSupportAnimation(frameNode, Converter::Convert<bool>(value));
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
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onItemDragStart(
            frameNode->GetId(), arkDragInfo, arkItemIndex);
        // onItemDragStart should return value [builder] but it is a void
        LOGE("ARKOALA onItemDragStart doesn`t handle builder returned value");
    };
    GridModelNG::SetOnItemDragStart(frameNode, std::move(onItemDragStart));
}
void OnItemDragEnterImpl(Ark_NativePointer node,
                         const Callback_ItemDragInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onItemDragEnter = [frameNode](const ItemDragInfo& dragInfo) {
        auto arkDragInfo = Converter::ArkValue<Ark_ItemDragInfo>(dragInfo);
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onItemDragEnter(
            frameNode->GetId(), arkDragInfo);
    };
    GridModelNG::SetOnItemDragEnter(frameNode, std::move(onItemDragEnter));
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
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onItemDragMove(
            frameNode->GetId(), arkDragInfo, arkItemIndex, arkInsertIndex);
    };
    GridModelNG::SetOnItemDragMove(frameNode, std::move(onItemDragMove));
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
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onItemDragLeave(
            frameNode->GetId(), arkDragInfo, arkItemIndex);
    };
    GridModelNG::SetOnItemDragLeave(frameNode, std::move(onItemDragLeave));
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
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onItemDrop(
            frameNode->GetId(), arkDragInfo, arkItemIndex, arkInsertIndex, arkIsSuccess);
    };
    GridModelNG::SetOnItemDrop(frameNode, std::move(onItemDrop));
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_NestedScrollOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetNestedScroll(frameNode, Converter::Convert<NestedScrollOptions>(*value));
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollEnabled(frameNode, Converter::Convert<bool>(value));
}
void FrictionImpl(Ark_NativePointer node,
                  const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridModelNG::SetFriction(frameNode, Converter::OptConvert<float>(*value));
}
void AlignItemsImpl(Ark_NativePointer node,
                    const Ark_Union_GridItemAlignment_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetAlignItems(frameNode,
        value ? Converter::OptConvert<GridItemAlignment>(*value) : std::nullopt);
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
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onScroll(
            frameNode->GetId(), arkScrollOffset, arkScrollState);
    };
    GridModelNG::SetOnScroll(frameNode, std::move(onScroll));
}
void OnReachStartImpl(Ark_NativePointer node,
                      const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onReachStart = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onReachStart(frameNode->GetId());
    };
    GridModelNG::SetOnReachStart(frameNode, std::move(onReachStart));
}
void OnReachEndImpl(Ark_NativePointer node,
                    const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onReachEnd = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onReachEnd(frameNode->GetId());
    };
    GridModelNG::SetOnReachEnd(frameNode, std::move(onReachEnd));
}
void OnScrollStartImpl(Ark_NativePointer node,
                       const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollStart = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onScrollStart(frameNode->GetId());
    };
    GridModelNG::SetOnScrollStart(frameNode, std::move(onScrollStart));
}
void OnScrollStopImpl(Ark_NativePointer node,
                      const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onScrollStop = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onScrollStop(frameNode->GetId());
    };
    GridModelNG::SetOnScrollStop(frameNode, std::move(onScrollStop));
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
        GetFullAPI()->getEventsAPI()->getGridEventsReceiver()->onScrollFrameBegin(
            frameNode->GetId(), arkOffset, arkState);
        // onScrollFrameBegin should return value [offsetRemain] but it is a void
        // that is a reason why we return [offset] value as the temporary stub
        LOGE("ARKOALA onScrollFrameBegin doesn`t handle offsetRemain returned value");
        return scrollRes;
    };
    GridModelNG::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameBegin));
}
void EdgeEffectImpl(Ark_NativePointer node,
                    Ark_EdgeEffect value,
                    const Opt_EdgeEffectOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEdgeEffect(frameNode, Converter::OptConvert<EdgeEffect>(value),
        options ? Converter::OptConvert<bool>(*options) : std::nullopt);
}
} // GridAttributeModifier
const GENERATED_ArkUIGridModifier* GetGridModifier()
{
    static const GENERATED_ArkUIGridModifier ArkUIGridModifierImpl {
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
        GridAttributeModifier::CachedCountImpl,
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
