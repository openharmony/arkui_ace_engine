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
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/lazy_build_accessor.h"
#include "core/components_ng/pattern/list/list_properties.h"

namespace OHOS::Ace::NG {
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
            auto builderComponent = value.builderComponent.value;
            OnDeleteEvent onActionCallback;
            AssignVoidCallback(onActionCallback, value.onAction);

            OnEnterDeleteAreaEvent onEnterActionAreaCallback;
            AssignVoidCallback(onEnterActionAreaCallback, value.onEnterActionArea);

            OnExitDeleteAreaEvent onExitActionAreaCallback;
            AssignVoidCallback(onExitActionAreaCallback, value.onExitActionArea);

            OnStateChangedEvent onStateChangeCallback;
            AssignOnStateChangedEventCallback(onStateChangeCallback, value.onStateChange);
            if (builderComponent) {
                auto contentPeer = reinterpret_cast<FrameNodePeer*>(builderComponent);
                CHECK_NULL_VOID(contentPeer);
                auto componentNode = FrameNodePeer::GetFrameNodeByPeer(contentPeer);
                if (componentNode) {
                    ListItemModelStatic::SetDeleteArea(frameNode, static_cast<UINode*>(AceType::RawPtr(componentNode)),
                        std::move(onActionCallback), std::move(onEnterActionAreaCallback),
                        std::move(onExitActionAreaCallback), std::move(onStateChangeCallback), length, isStartArea);
                }
            } else if (builder.has_value()) {
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

std::optional<bool> ProcessBindableSelected(FrameNode* frameNode, const Opt_Union_Boolean_Bindable *value)
{
    std::optional<bool> result;
    Converter::VisitUnionPtr(value,
        [&result](const Ark_Boolean& src) {
            result = Converter::OptConvert<bool>(src);
        },
        [&result, frameNode](const Ark_Bindable_Boolean& src) {
            result = Converter::OptConvert<bool>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](const bool value) {
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(value));
            };
            ListItemModelStatic::SetSelectChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
struct ListItemOptions {
    std::optional<V2::ListItemStyle> style;
};
template<>
inline Converter::ListItemOptions Convert(const Ark_ListItemOptions& src)
{
    return {
        .style = OptConvert<V2::ListItemStyle>(src.style)
    };
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListItemModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = ListItemModelStatic::CreateFrameNode(id, false, LazyBuild::IsLazyBuild());
    LazyBuild::ResetLazyBuild();
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // ListItemModifier
namespace ListItemInterfaceModifier {
void SetListItemOptionsImpl(Ark_NativePointer node,
                            const Opt_ListItemOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto options = Converter::OptConvertPtr<Converter::ListItemOptions>(value);
    if (options.has_value()) {
        ListItemModelStatic::SetStyle(frameNode, options.value().style);
    }
}
} // ListItemInterfaceModifier
namespace ListItemAttributeModifier {
void SetSelectableImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        convValue = true;
    }
    ListItemModelStatic::SetSelectable(frameNode, *convValue);
}
void SetSelectedImpl(Ark_NativePointer node,
                     const Opt_Union_Boolean_Bindable* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = ProcessBindableSelected(frameNode, value);
    if (!convValue) {
        convValue = false;
    }
    ListItemModelStatic::SetSelected(frameNode, *convValue);
}
void SetSwipeActionImpl(Ark_NativePointer node,
                        const Opt_SwipeActionOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ListItemModelStatic::SetDeleteArea(frameNode, nullptr, nullptr, nullptr, nullptr, nullptr,
            Dimension(0, DimensionUnit::VP), true);
        ListItemModelStatic::SetDeleteArea(frameNode, nullptr, nullptr, nullptr, nullptr, nullptr,
            Dimension(0, DimensionUnit::VP), false);
        ListItemModelStatic::SetSwiperAction(frameNode, nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::None);
        return;
    }

    SetDeleteArea(optValue->start, true, frameNode, node);
    SetDeleteArea(optValue->end, false, frameNode, node);

    using OnOffsetChangeType = std::function<void(int32_t)>;
    OnOffsetChangeType onOffsetChangeCallback;
    auto arkOnOffsetChange = Converter::OptConvert<Callback_F64_Void>(optValue->onOffsetChange);
    if (arkOnOffsetChange) {
        onOffsetChangeCallback = [arkCallback = CallbackHelper(*arkOnOffsetChange)](int32_t offset) {
            auto arkOffset = Converter::ArkValue<Ark_Float64>(offset);
            arkCallback.Invoke(arkOffset);
        };
    }

    auto edgeEffect = Converter::OptConvert<V2::SwipeEdgeEffect>(optValue->edgeEffect);
    ListItemModelStatic::SetSwiperAction(frameNode, nullptr, nullptr,
        std::move(onOffsetChangeCallback), edgeEffect);
}
void SetOnSelectImpl(Ark_NativePointer node,
                     const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        ListItemModelStatic::SetSelectCallback(frameNode, nullptr);
        return;
    }
    auto onSelect = [arkCallback = CallbackHelper(*optValue)](bool param) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(param));
    };
    ListItemModelStatic::SetSelectCallback(frameNode, onSelect);
}
} // ListItemAttributeModifier
const GENERATED_ArkUIListItemModifier* GetListItemModifier()
{
    static const GENERATED_ArkUIListItemModifier ArkUIListItemModifierImpl {
        ListItemModifier::ConstructImpl,
        ListItemInterfaceModifier::SetListItemOptionsImpl,
        ListItemAttributeModifier::SetSelectableImpl,
        ListItemAttributeModifier::SetSelectedImpl,
        ListItemAttributeModifier::SetSwipeActionImpl,
        ListItemAttributeModifier::SetOnSelectImpl,
    };
    return &ArkUIListItemModifierImpl;
}

}
