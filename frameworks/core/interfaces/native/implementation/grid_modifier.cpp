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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

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
void SetGridOptionsImpl(
    Ark_NativePointer node, const Opt_Scroller* scroller, const Opt_GridLayoutOptions* layoutOptions)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<GridLayoutOptions> layoutOptionsOpt;
    if (layoutOptions && layoutOptions->tag != ARK_TAG_UNDEFINED) {
        GridLayoutOptions options;
        std::optional<GridItemSize> regularSizeOpt = Converter::OptConvert<GridItemSize>(layoutOptions->value);
        if (regularSizeOpt) {
            options.regularSize = regularSizeOpt.value();
        }
        std::optional<std::set<int32_t>> irrIndex = Converter::OptConvert<std::set<int32_t>>(layoutOptions->value);
        if (irrIndex) {
            options.irregularIndexes = irrIndex.value();
        }
        GridModelNG::SetLayoutOptions(frameNode, options);
    }
}
} // namespace GridInterfaceModifier
namespace GridAttributeModifier {
void ColumnsTemplateImpl(Ark_NativePointer node, const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag != ARK_TAG_UNDEFINED) {
        GridModelNG::SetColumnsTemplate(frameNode, Converter::Convert<std::string>(value->value));
    }
}
void RowsTemplateImpl(Ark_NativePointer node,
                      const Opt_String* value)
{
}
void ColumnsGapImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
}
void RowsGapImpl(Ark_NativePointer node,
                 const Opt_Length* value)
{
}
void ScrollBarWidthImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String* value)
{
}
void ScrollBarColorImpl(Ark_NativePointer node,
                        const Opt_Union_Color_Number_String* value)
{
}
void ScrollBarImpl(Ark_NativePointer node,
                   const Opt_BarState* value)
{
}
void OnScrollBarUpdateImpl(Ark_NativePointer node,
                           const Opt_Callback_Number_Number_ComputedBarAttribute* value)
{
}
void OnScrollIndexImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Number_Void* value)
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
void EditModeImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void MultiSelectableImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
}
void MaxCountImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
}
void MinCountImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
}
void CellLengthImpl(Ark_NativePointer node,
                    const Opt_Number* value)
{
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         const Opt_GridDirection* value)
{
}
void SupportAnimationImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
}
void OnItemDragStartImpl(Ark_NativePointer node,
                         const Opt_GridAttribute_onItemDragStart_event_type* value)
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
void NestedScrollImpl(Ark_NativePointer node,
                      const Opt_NestedScrollOptions* value)
{
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
}
void FrictionImpl(Ark_NativePointer node,
                  const Opt_Union_Number_Resource* value)
{
}
void AlignItemsImpl(Ark_NativePointer node,
                    const Opt_GridItemAlignment* value)
{
}
void OnScrollImpl(Ark_NativePointer node,
                  const Opt_Callback_Number_Number_Void* value)
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
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            const Opt_Callback_Number_ScrollState_Literal_Number_offsetRemain* value)
{
}
void EdgeEffectImpl(Ark_NativePointer node,
                    const Opt_EdgeEffect* value,
                    const Opt_EdgeEffectOptions* options)
{
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
