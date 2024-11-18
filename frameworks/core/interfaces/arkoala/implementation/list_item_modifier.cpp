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
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {
using ListItemEditableType = std::variant<bool, uint32_t>;
}

namespace OHOS::Ace::NG::Converter {
struct SwipeActionOptions {
    std::optional<V2::SwipeEdgeEffect> edgeEffect;
};

template<>
inline Converter::SwipeActionOptions Convert(const Ark_SwipeActionOptions& src)
{
    return {
        .edgeEffect = OptConvert<V2::SwipeEdgeEffect>(src.edgeEffect)
    };
}

template<>
inline Converter::ListItemOptions Convert(const Ark_ListItemOptions& src)
{
    return {
        .style = OptConvert<V2::ListItemStyle>(src.style)
    };
}

template<>
inline ListItemEditableType Convert(const Ark_Boolean& src)
{
    return Converter::Convert<bool>(src);
}

template<>
inline ListItemEditableType Convert(const Ark_EditMode& src)
{
    return static_cast<uint32_t>(src);
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListItemInterfaceModifier {
void SetListItemOptions0Impl(Ark_NativePointer node,
                             const Opt_ListItemOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::OptConvert<Converter::ListItemOptions>(*value);
    if (options.has_value()) {
        ListItemModelNG::SetStyle(frameNode, options.value().style);
    }
}
void SetListItemOptions1Impl(Ark_NativePointer node,
                             const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optionsOpt = Converter::OptConvert<std::string>(*value);
    if (optionsOpt.has_value()) {
        LOGE("ListItemModifier::SetListItemOptions1Impl is not implemented yet!");
    }
}
} // ListItemInterfaceModifier
namespace ListItemAttributeModifier {
void StickyImpl(Ark_NativePointer node,
                Ark_Sticky value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemModelNG::SetSticky(frameNode, Converter::OptConvert<V2::StickyMode>(value));
}
void EditableImpl(Ark_NativePointer node,
                  const Ark_Union_Boolean_EditMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    // V2::EditMode non-standard enum so set default values in modifier
    auto editable = static_cast<uint32_t>(V2::EditMode::NONE);
    if (value != nullptr) {
        auto editableOpt = Converter::OptConvert<ListItemEditableType>(*value);
        if (editableOpt.has_value()) {
            if (editableOpt.value().index() == 0) {
                editable = std::get<0>(editableOpt.value()) == true ?
                    V2::EditMode::DELETABLE | V2::EditMode::MOVABLE : V2::EditMode::NONE;
            } else if (editableOpt.value().index() == 1) {
                editable = std::get<1>(editableOpt.value());
            }
        }
    }
    ListItemModelNG::SetEditMode(frameNode, editable);
}
void SelectableImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemModelNG::SetSelectable(frameNode, Converter::Convert<bool>(value));
}
void SelectedImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemModelNG::SetSelected(frameNode, Converter::Convert<bool>(value));
}
void SwipeActionImpl(Ark_NativePointer node,
                     const Ark_SwipeActionOptions* value)
{
    LOGE("ListItemModifier::SwipeActionImpl is not implemented yet!");
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::Convert<Converter::SwipeActionOptions>(*value);
    ListItemModelNG::SetSwiperAction(frameNode, nullptr, nullptr, nullptr, options.edgeEffect);
}
void OnSelectImpl(Ark_NativePointer node,
                  const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSelect = [frameNode](bool isSelected) {
        GetFullAPI()->getEventsAPI()->getListItemEventsReceiver()->onSelect(frameNode->GetId(), isSelected);
    };
    ListItemModelNG::SetSelectCallback(frameNode, onSelect);
}
} // ListItemAttributeModifier
const GENERATED_ArkUIListItemModifier* GetListItemModifier()
{
    static const GENERATED_ArkUIListItemModifier ArkUIListItemModifierImpl {
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
