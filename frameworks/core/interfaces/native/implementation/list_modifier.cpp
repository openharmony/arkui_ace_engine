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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //ListModelNG::SetSetListOptions(frameNode, convValue);
}
} // ListInterfaceModifier
namespace ListAttributeModifier {
void SetAlignListItemImpl(Ark_NativePointer node,
                          const Opt_ListItemAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetAlignListItem(frameNode, convValue);
}
void SetListDirectionImpl(Ark_NativePointer node,
                          const Opt_Axis* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetListDirection(frameNode, convValue);
}
void SetContentStartOffsetImpl(Ark_NativePointer node,
                               const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetContentStartOffset(frameNode, convValue);
}
void SetContentEndOffsetImpl(Ark_NativePointer node,
                             const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetContentEndOffset(frameNode, convValue);
}
void SetDividerImpl(Ark_NativePointer node,
                    const Opt_ListDividerOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetDivider(frameNode, convValue);
}
void SetMultiSelectableImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetMultiSelectable(frameNode, convValue);
}
void SetCachedCount0Impl(Ark_NativePointer node,
                         const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetCachedCount0(frameNode, convValue);
}
void SetChainAnimationImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetChainAnimation(frameNode, convValue);
}
void SetChainAnimationOptionsImpl(Ark_NativePointer node,
                                  const Opt_ChainAnimationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetChainAnimationOptions(frameNode, convValue);
}
void SetStickyImpl(Ark_NativePointer node,
                   const Opt_StickyStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetSticky(frameNode, convValue);
}
void SetScrollSnapAlignImpl(Ark_NativePointer node,
                            const Opt_ScrollSnapAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetScrollSnapAlign(frameNode, convValue);
}
void SetChildrenMainSizeImpl(Ark_NativePointer node,
                             const Opt_ChildrenMainSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetChildrenMainSize(frameNode, convValue);
}
void SetMaintainVisibleContentPositionImpl(Ark_NativePointer node,
                                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetMaintainVisibleContentPosition(frameNode, convValue);
}
void SetStackFromEndImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetStackFromEnd(frameNode, convValue);
}
void SetOnScrollIndexImpl(Ark_NativePointer node,
                          const Opt_Callback_Number_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetOnScrollIndex(frameNode, convValue);
}
void SetOnScrollVisibleContentChangeImpl(Ark_NativePointer node,
                                         const Opt_OnScrollVisibleContentChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetOnScrollVisibleContentChange(frameNode, convValue);
}
void SetOnItemMoveImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Number_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetOnItemMove(frameNode, convValue);
}
void SetOnItemDragStartImpl(Ark_NativePointer node,
                            const Opt_OnItemDragStartCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetOnItemDragStart(frameNode, convValue);
}
void SetOnItemDragEnterImpl(Ark_NativePointer node,
                            const Opt_Callback_ItemDragInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetOnItemDragEnter(frameNode, convValue);
}
void SetOnItemDragMoveImpl(Ark_NativePointer node,
                           const Opt_Callback_ItemDragInfo_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetOnItemDragMove(frameNode, convValue);
}
void SetOnItemDragLeaveImpl(Ark_NativePointer node,
                            const Opt_Callback_ItemDragInfo_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetOnItemDragLeave(frameNode, convValue);
}
void SetOnItemDropImpl(Ark_NativePointer node,
                       const Opt_Callback_ItemDragInfo_Number_Number_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetOnItemDrop(frameNode, convValue);
}
void SetOnScrollFrameBeginImpl(Ark_NativePointer node,
                               const Opt_OnScrollFrameBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetOnScrollFrameBegin(frameNode, convValue);
}
void SetOnWillScrollImpl(Ark_NativePointer node,
                         const Opt_OnWillScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetOnWillScroll(frameNode, convValue);
}
void SetOnDidScrollImpl(Ark_NativePointer node,
                        const Opt_OnScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListModelNG::SetSetOnDidScroll(frameNode, convValue);
}
void SetLanesImpl(Ark_NativePointer node,
                  const Opt_Union_Number_LengthConstrain* value,
                  const Opt_Dimension* gutter)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //ListModelNG::SetSetLanes(frameNode, convValue);
}
void SetCachedCount1Impl(Ark_NativePointer node,
                         const Opt_Number* count,
                         const Opt_Boolean* show)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(count);
    //auto convValue = Converter::OptConvert<type>(count); // for enums
    //ListModelNG::SetSetCachedCount1(frameNode, convValue);
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
