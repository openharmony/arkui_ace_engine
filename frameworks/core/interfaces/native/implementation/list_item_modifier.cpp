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
#include "core/components_ng/pattern/list/list_item_model_static.h"
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
            CallbackHelper(value).BuildAsync([isStartArea, frameNode](const RefPtr<UINode>& uiNode) {
                CHECK_NULL_VOID(uiNode);
                ListItemModelStatic::SetDeleteArea(
                    frameNode, Referenced::RawPtr(uiNode), nullptr, nullptr, nullptr, nullptr,
                    Dimension(0, DimensionUnit::VP), isStartArea);
                }, node);
        },
        [isStartArea, frameNode, node](const Ark_SwipeActionItem& value) {
            auto length = Converter::OptConvert<Dimension>(value.actionAreaDistance);
            auto builder = Converter::OptConvert<CustomNodeBuilder>(value.builder);
            OnDeleteEvent onActionCallback;
            AssignVoidCallback(onActionCallback, value.onAction);

            OnEnterDeleteAreaEvent onEnterActionAreaCallback;
            AssignVoidCallback(onEnterActionAreaCallback, value.onEnterActionArea);

            OnExitDeleteAreaEvent onExitActionAreaCallback;
            AssignVoidCallback(onExitActionAreaCallback, value.onExitActionArea);

            OnStateChangedEvent onStateChangeCallback;
            AssignOnStateChangedEventCallback(onStateChangeCallback, value.onStateChange);
            if (builder.has_value()) {
                CallbackHelper(builder.value()).BuildAsync([
                    frameNode, length, isStartArea,
                    onAction = std::move(onActionCallback),
                    onEnterActionArea = std::move(onEnterActionAreaCallback),
                    onExitActionArea = std::move(onExitActionAreaCallback),
                    onStateChange = std::move(onStateChangeCallback)
                ](const RefPtr<UINode>& uiNode) mutable {
                    ListItemModelStatic::SetDeleteArea(frameNode, Referenced::RawPtr(uiNode), std::move(onAction),
                        std::move(onEnterActionArea), std::move(onExitActionArea), std::move(onStateChange),
                        length, isStartArea);
                    }, node);
            } else {
                ListItemModelStatic::SetDeleteArea(frameNode, nullptr, std::move(onActionCallback),
                    std::move(onEnterActionAreaCallback), std::move(onExitActionAreaCallback),
                    std::move(onStateChangeCallback), length, isStartArea);
            }
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
    auto frameNode = ListItemModelStatic::CreateFrameNode(id);
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
        ListItemModelStatic::SetStyle(frameNode, options.value().style);
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
                const Opt_Sticky* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemModelStatic::SetSticky(frameNode, Converter::OptConvert<V2::StickyMode>(*value));
}
void EditableImpl(Ark_NativePointer node,
                  const Opt_Union_Boolean_EditMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
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
    ListItemModelStatic::SetEditMode(frameNode, editable);
}
void SelectableImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    ListItemModelStatic::SetSelectable(frameNode, *convValue);
}
void SelectedImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    ListItemModelStatic::SetSelected(frameNode, *convValue);
}
void SwipeActionImpl(Ark_NativePointer node,
                     const Opt_SwipeActionOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }

    SetDeleteArea(optValue->start, true, frameNode, node);
    SetDeleteArea(optValue->end, false, frameNode, node);

    using OnOffsetChangeType = std::function<void(int32_t)>;
    OnOffsetChangeType onOffsetChangeCallback;
    auto arkOnOffsetChange = Converter::OptConvert<Callback_Number_Void>(optValue->onOffsetChange);
    if (arkOnOffsetChange) {
        onOffsetChangeCallback = [arkCallback = CallbackHelper(*arkOnOffsetChange)](int32_t offset) {
            auto arkOffset = Converter::ArkValue<Ark_Number>(offset);
            arkCallback.Invoke(arkOffset);
        };
    }

    auto edgeEffect = Converter::OptConvert<V2::SwipeEdgeEffect>(optValue->edgeEffect);
    ListItemModelStatic::SetSwiperAction(frameNode, nullptr, nullptr,
        std::move(onOffsetChangeCallback), edgeEffect);
}
void OnSelectImpl(Ark_NativePointer node,
                  const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onSelect = [arkCallback = CallbackHelper(*optValue)](bool param) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(param));
    };
    ListItemModelStatic::SetSelectCallback(frameNode, onSelect);
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Opt_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const bool value) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Opt_Boolean>(value));
    };
    ListItemModelStatic::SetSelectChangeEvent(frameNode, std::move(onEvent));
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
