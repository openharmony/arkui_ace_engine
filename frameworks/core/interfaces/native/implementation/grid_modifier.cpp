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
namespace GridModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // GridModifier
namespace GridInterfaceModifier {
void SetGridOptionsImpl(Ark_NativePointer node,
                        const Opt_Scroller* scroller,
                        const Opt_GridLayoutOptions* layoutOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(scroller);
    //auto convValue = Converter::OptConvert<type>(scroller); // for enums
    //GridModelNG::SetSetGridOptions(frameNode, convValue);
}
} // GridInterfaceModifier
namespace GridAttributeModifier {
void SetColumnsTemplateImpl(Ark_NativePointer node,
                            const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetColumnsTemplate(frameNode, convValue);
}
void SetRowsTemplateImpl(Ark_NativePointer node,
                         const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetRowsTemplate(frameNode, convValue);
}
void SetColumnsGapImpl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetColumnsGap(frameNode, convValue);
}
void SetRowsGapImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetRowsGap(frameNode, convValue);
}
void SetOnScrollBarUpdateImpl(Ark_NativePointer node,
                              const Opt_Callback_Number_Number_ComputedBarAttribute* value)
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
        auto totalOffset = Convert<Dimension>(arkResult.totalOffset).ConvertToPx();
        auto totalLength = Convert<Dimension>(arkResult.totalLength).ConvertToPx();
        return ResType(totalOffset, totalLength);
    };
    GridModelStatic::SetOnScrollBarUpdate(frameNode, std::move(onScrollBarUpdate));
}
void OnScrollIndexImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetOnScrollIndex(frameNode, convValue);
}
void SetCachedCount0Impl(Ark_NativePointer node,
                         const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetCachedCount0(frameNode, convValue);
}
void SetEditModeImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetEditMode(frameNode, convValue);
}
void SetMultiSelectableImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetMultiSelectable(frameNode, convValue);
}
void SetMaxCountImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetMaxCount(frameNode, convValue);
}
void SetMinCountImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetMinCount(frameNode, convValue);
}
void SetCellLengthImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetCellLength(frameNode, convValue);
}
void SetLayoutDirectionImpl(Ark_NativePointer node,
                            const Opt_GridDirection* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetLayoutDirection(frameNode, convValue);
}
void SetSupportAnimationImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetSupportAnimation(frameNode, convValue);
}
void SetOnItemDragStartImpl(Ark_NativePointer node,
                            const Opt_OnItemDragStartCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetOnItemDragStart(frameNode, convValue);
}
void SetOnItemDragEnterImpl(Ark_NativePointer node,
                            const Opt_Callback_ItemDragInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetOnItemDragEnter(frameNode, convValue);
}
void SetOnItemDragMoveImpl(Ark_NativePointer node,
                           const Opt_Callback_ItemDragInfo_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetOnItemDragMove(frameNode, convValue);
}
void SetOnItemDragLeaveImpl(Ark_NativePointer node,
                            const Opt_Callback_ItemDragInfo_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetOnItemDragLeave(frameNode, convValue);
}
void SetOnItemDropImpl(Ark_NativePointer node,
                       const Opt_Callback_ItemDragInfo_Number_Number_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetOnItemDrop(frameNode, convValue);
}
void SetAlignItemsImpl(Ark_NativePointer node,
                       const Opt_GridItemAlignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetAlignItems(frameNode, convValue);
}
void SetOnScrollFrameBeginImpl(Ark_NativePointer node,
                               const Opt_OnScrollFrameBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetOnScrollFrameBegin(frameNode, convValue);
}
void SetOnWillScrollImpl(Ark_NativePointer node,
                         const Opt_OnWillScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetOnWillScroll(frameNode, convValue);
}
void SetOnDidScrollImpl(Ark_NativePointer node,
                        const Opt_OnScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridModelNG::SetSetOnDidScroll(frameNode, convValue);
}
void SetCachedCount1Impl(Ark_NativePointer node,
                         const Opt_Number* count,
                         const Opt_Boolean* show)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(count);
    //auto convValue = Converter::OptConvert<type>(count); // for enums
    //GridModelNG::SetSetCachedCount1(frameNode, convValue);
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
        GridAttributeModifier::SetAlignItemsImpl,
        GridAttributeModifier::SetOnScrollFrameBeginImpl,
        GridAttributeModifier::SetOnWillScrollImpl,
        GridAttributeModifier::SetOnDidScrollImpl,
        GridAttributeModifier::SetCachedCount1Impl,
    };
    return &ArkUIGridModifierImpl;
}

}
