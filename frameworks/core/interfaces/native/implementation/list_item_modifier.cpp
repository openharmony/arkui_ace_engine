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
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {
using ListItemEditableType = std::variant<bool, uint32_t>;

namespace {
void AssignVoidCallback(std::function<void()>& dst, const Opt_Callback_Void& src)
{
    auto arkCallback = Converter::OptConvert<Callback_Void>(src);
    if (arkCallback) {
        dst = [callback = CallbackHelper(arkCallback.value())]() {
            callback.Invoke();
        };
    }
}

void AssignOnStateChangedEventCallback(OnStateChangedEvent& dst, const Opt_Callback_SwipeActionState_Void& src)
{
    auto arkCallback = Converter::OptConvert<Callback_SwipeActionState_Void>(src);
    if (arkCallback) {
        dst = [callback = CallbackHelper(arkCallback.value())](SwipeActionState state) {
            auto arkState = Converter::ArkValue<Ark_SwipeActionState>(state);
            callback.Invoke(arkState);
        };
    }
}

void SetDeleteArea(const Opt_Union_CustomBuilder_SwipeActionItem& arg, bool isStartArea, FrameNode* frameNode,
    Ark_NativePointer node)
{
    CHECK_NULL_VOID(frameNode);

    Converter::VisitUnion(arg,
        [isStartArea, frameNode, node](const CustomNodeBuilder& value) {
            auto customNode = CallbackHelper(value).BuildSync(node);
            CHECK_NULL_VOID(customNode);
            // ListItemModelNG::SetDeleteArea(
            //     frameNode, customNode.GetRawPtr(), nullptr, nullptr, nullptr, nullptr,
            //     Dimension(0, DimensionUnit::VP), isStartArea);
        },
        [isStartArea, frameNode, node](const Ark_SwipeActionItem& value) {
            auto builder = Converter::OptConvert<CustomNodeBuilder>(value.builder);
            RefPtr<UINode> customNode;
            if (builder) {
                customNode = CallbackHelper(builder.value()).BuildSync(node);
            }

            OnDeleteEvent onActionCallback;
            AssignVoidCallback(onActionCallback, value.onAction);

            OnEnterDeleteAreaEvent onEnterActionAreaCallback;
            AssignVoidCallback(onEnterActionAreaCallback, value.onEnterActionArea);

            OnExitDeleteAreaEvent onExitActionAreaCallback;
            AssignVoidCallback(onExitActionAreaCallback, value.onExitActionArea);

            OnStateChangedEvent onStateChangeCallback;
            AssignOnStateChangedEventCallback(onStateChangeCallback, value.onStateChange);

            auto length = Converter::OptConvert<Dimension>(value.actionAreaDistance);

            // ListItemModelNG::SetDeleteArea(frameNode, customNode.GetRawPtr(), std::move(onActionCallback),
            //     std::move(onEnterActionAreaCallback), std::move(onExitActionAreaCallback),
            //     std::move(onStateChangeCallback), length, isStartArea);
        },
        []() {}
    );
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
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
namespace ListItemModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = ListItemModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // ListItemModifier
namespace ListItemInterfaceModifier {
void SetListItemOptions0Impl(Ark_NativePointer node,
                             const Opt_ListItemOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::OptConvert<Converter::ListItemOptions>(*value);
    if (options.has_value()) {
        // ListItemModelNG::SetStyle(frameNode, options.value().style);
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
    // ListItemModelNG::SetSticky(frameNode, Converter::OptConvert<V2::StickyMode>(value));
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
    // ListItemModelNG::SetEditMode(frameNode, editable);
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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    SetDeleteArea(value->start, true, frameNode, node);
    SetDeleteArea(value->end, false, frameNode, node);

    using OnOffsetChangeType = std::function<void(int32_t)>;
    OnOffsetChangeType onOffsetChangeCallback;
    auto arkOnOffsetChange = Converter::OptConvert<Callback_Number_Void>(value->onOffsetChange);
    if (arkOnOffsetChange) {
        onOffsetChangeCallback = [arkCallback = CallbackHelper(*arkOnOffsetChange)](int32_t offset) {
            auto arkOffset = Converter::ArkValue<Ark_Number>(offset);
            arkCallback.Invoke(arkOffset);
        };
    }

    auto edgeEffect = Converter::OptConvert<V2::SwipeEdgeEffect>(value->edgeEffect);
    // ListItemModelNG::SetSwiperAction(frameNode, nullptr, nullptr,
    //     std::move(onOffsetChangeCallback), edgeEffect);
}
void OnSelectImpl(Ark_NativePointer node,
                  const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSelect = [arkCallback = CallbackHelper(*value)](bool param) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(param));
    };
    ListItemModelNG::SetSelectCallback(frameNode, onSelect);
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const bool value) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(value));
    };
    // ListItemModelNG::SetSelectChangeEvent(frameNode, std::move(onEvent));
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
        ListItemAttributeModifier::_onChangeEvent_selectedImpl,
    };
    return &ArkUIListItemModifierImpl;
}
}
