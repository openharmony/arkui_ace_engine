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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListItemModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // ListItemModifier
namespace ListItemInterfaceModifier {
void SetListItemOptions0Impl(Ark_NativePointer node,
                             const Opt_ListItemOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListItemModelNG::SetSetListItemOptions0(frameNode, convValue);
}
void SetListItemOptions1Impl(Ark_NativePointer node,
                             const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListItemModelNG::SetSetListItemOptions1(frameNode, convValue);
}
} // ListItemInterfaceModifier
namespace ListItemAttributeModifier {
void StickyImpl(Ark_NativePointer node,
                Ark_Sticky value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //ListItemModelNG::SetSticky(frameNode, convValue);
}
void EditableImpl(Ark_NativePointer node,
                  const Ark_Union_Boolean_EditMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ListItemModelNG::SetEditable(frameNode, convValue);
}
void SelectableImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //ListItemModelNG::SetSelectable(frameNode, convValue);
}
void SelectedImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //ListItemModelNG::SetSelected(frameNode, convValue);
}
void SwipeActionImpl(Ark_NativePointer node,
                     const Ark_SwipeActionOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ListItemModelNG::SetSwipeAction(frameNode, convValue);
}
void OnSelectImpl(Ark_NativePointer node,
                  const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ListItemModelNG::SetOnSelect(frameNode, convValue);
}
} // ListItemAttributeModifier
const GENERATED_ArkUIListItemModifier* GetListItemModifier()
{
    static const GENERATED_ArkUIListItemModifier ArkUIListItemModifierImpl {
        ListItemModifier::ConstructImpl,
        ListItemInterfaceModifier::SetListItemOptions0Impl,
        ListItemInterfaceModifier::SetListItemOptions1Impl,
        ListItemAttributeModifier::StickyImpl,
        ListItemAttributeModifier::EditableImpl,
        ListItemAttributeModifier::SelectableImpl,
        ListItemAttributeModifier::SelectedImpl,
        ListItemAttributeModifier::SwipeActionImpl,
        ListItemAttributeModifier::OnSelectImpl,
    };
    return &ArkUIListItemModifierImpl;
}

}
