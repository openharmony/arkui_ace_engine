/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/implementation/click_event_peer.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/gesture_event_peer.h"
#include "core/interfaces/native/implementation/gesture_recognizer_peer_impl.h"
#include "core/interfaces/native/implementation/gesture_trigger_info_peer.h"
#include "core/interfaces/native/implementation/pan_recognizer_peer.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/gestures/gesture_event.h"

namespace OHOS::Ace::NG::GeneratedModifier {

namespace UIObserverGestureEventOpsAccessor {
Ark_Int32 SetOnBeforePanStartImpl(Ark_Int32 instanceId, const UIObserver_PanListenerCallback* callback)
{
    if (!callback) {
        return 0;
    }
    auto handleFunc = [event = CallbackHelper(*callback)](const GestureEvent& gestureEventInfo,
        const RefPtr<NG::PanRecognizer>& current, const RefPtr<NG::FrameNode>& frameNode) {
        CHECK_NULL_VOID(current);
        GestureEvent eventInfo = gestureEventInfo;
        const auto gestureEvent = Converter::SyncEvent<Ark_GestureEvent>(eventInfo);
        Ark_GestureRecognizer arkValRecognizer = Converter::ArkValue<Ark_PanRecognizer>(current);
        Ark_FrameNode arkFrameNode =
            FrameNodePeer::Create(frameNode ? OHOS::Ace::AceType::RawPtr(frameNode) : nullptr);
        auto optValue = Converter::ArkValue<Opt_FrameNode>(arkFrameNode);
        
        event.InvokeSync(gestureEvent.ArkValue(), arkValRecognizer, optValue);
    };
    int32_t resourceId = static_cast<int32_t>((*callback).resource.resourceId);
    NG::UIObserverHandler::AddBeforePanStartListenerCallback(
        static_cast<int32_t>(instanceId), resourceId, std::move(handleFunc));
    return resourceId;
}

Ark_Int32 SetOnBeforePanEndImpl(Ark_Int32 instanceId, const UIObserver_PanListenerCallback* callback)
{
    if (!callback) {
        return 0;
    }
    auto handleFunc = [event = CallbackHelper(*callback)](const GestureEvent& gestureEventInfo,
        const RefPtr<NG::PanRecognizer>& current, const RefPtr<NG::FrameNode>& frameNode) {
        CHECK_NULL_VOID(current);
        GestureEvent eventInfo = gestureEventInfo;
        const auto gestureEvent = Converter::SyncEvent<Ark_GestureEvent>(eventInfo);
        Ark_GestureRecognizer arkValRecognizer = Converter::ArkValue<Ark_PanRecognizer>(current);
        Ark_FrameNode arkFrameNode =
            FrameNodePeer::Create(frameNode ? OHOS::Ace::AceType::RawPtr(frameNode) : nullptr);
        auto optValue = Converter::ArkValue<Opt_FrameNode>(arkFrameNode);
        
        event.InvokeSync(gestureEvent.ArkValue(), arkValRecognizer, optValue);
    };
    int32_t resourceId = static_cast<int32_t>((*callback).resource.resourceId);
    NG::UIObserverHandler::AddBeforePanEndListenerCallback(
        static_cast<int32_t>(instanceId), resourceId, std::move(handleFunc));
    return resourceId;
}
Ark_Int32 SetOnAfterPanStartImpl(Ark_Int32 instanceId, const UIObserver_PanListenerCallback* callback)
{
    if (!callback) {
        return 0;
    }
    auto handleFunc = [event = CallbackHelper(*callback)](const GestureEvent& gestureEventInfo,
        const RefPtr<NG::PanRecognizer>& current, const RefPtr<NG::FrameNode>& frameNode) {
        CHECK_NULL_VOID(current);
        GestureEvent eventInfo = gestureEventInfo;
        const auto gestureEvent = Converter::SyncEvent<Ark_GestureEvent>(eventInfo);
        Ark_GestureRecognizer arkValRecognizer = Converter::ArkValue<Ark_PanRecognizer>(current);
        Ark_FrameNode arkFrameNode =
            FrameNodePeer::Create(frameNode ? OHOS::Ace::AceType::RawPtr(frameNode) : nullptr);
        auto optValue = Converter::ArkValue<Opt_FrameNode>(arkFrameNode);
        
        event.InvokeSync(gestureEvent.ArkValue(), arkValRecognizer, optValue);
    };
    int32_t resourceId = static_cast<int32_t>((*callback).resource.resourceId);
    NG::UIObserverHandler::AddAfterPanStartListenerCallback(
        static_cast<int32_t>(instanceId), resourceId, std::move(handleFunc));
    return resourceId;
}
Ark_Int32 SetOnAfterPanEndImpl(Ark_Int32 instanceId, const UIObserver_PanListenerCallback* callback)
{
    if (!callback) {
        return 0;
    }
    auto handleFunc = [event = CallbackHelper(*callback)](const GestureEvent& gestureEventInfo,
        const RefPtr<NG::PanRecognizer>& current, const RefPtr<NG::FrameNode>& frameNode) {
        CHECK_NULL_VOID(current);
        GestureEvent eventInfo = gestureEventInfo;
        const auto gestureEvent = Converter::SyncEvent<Ark_GestureEvent>(eventInfo);
        Ark_GestureRecognizer arkValRecognizer = Converter::ArkValue<Ark_PanRecognizer>(current);
        Ark_FrameNode arkFrameNode =
            FrameNodePeer::Create(frameNode ? OHOS::Ace::AceType::RawPtr(frameNode) : nullptr);
        auto optValue = Converter::ArkValue<Opt_FrameNode>(arkFrameNode);
        
        event.InvokeSync(gestureEvent.ArkValue(), arkValRecognizer, optValue);
    };
    int32_t resourceId = static_cast<int32_t>((*callback).resource.resourceId);
    NG::UIObserverHandler::AddAfterPanEndListenerCallback(
        static_cast<int32_t>(instanceId), resourceId, std::move(handleFunc));
    return resourceId;
}
Ark_Int32 SetOnWillClickImpl(Ark_Int32 instanceId, const UIObserver_ClickEventListenerCallback* callback)
{
    if (!callback) {
        return 0;
    }
    auto handleFunc = [event = CallbackHelper(*callback)](const GestureEvent& clickInfo,
        const RefPtr<NG::FrameNode>& frameNode) {
        GestureEvent eventInfo = clickInfo;
        const auto clickEvent = Converter::SyncEvent<Ark_ClickEvent>(eventInfo);
        Ark_FrameNode arkFrameNode =
            FrameNodePeer::Create(frameNode ? OHOS::Ace::AceType::RawPtr(frameNode) : nullptr);
        auto optValue = Converter::ArkValue<Opt_FrameNode>(arkFrameNode);

        event.InvokeSync(clickEvent.ArkValue(), optValue);
    };
    int32_t resourceId = static_cast<int32_t>((*callback).resource.resourceId);
    NG::UIObserverHandler::AddWillClickListenerCallback(
        static_cast<int32_t>(instanceId), resourceId, std::move(handleFunc));
    return resourceId;
}
Ark_Int32 SetOnDidClickImpl(Ark_Int32 instanceId, const UIObserver_ClickEventListenerCallback* callback)
{
    if (!callback) {
        return 0;
    }
    auto handleFunc = [event = CallbackHelper(*callback)](const GestureEvent& clickInfo,
        const RefPtr<NG::FrameNode>& frameNode) {
        GestureEvent eventInfo = clickInfo;
        const auto clickEvent = Converter::SyncEvent<Ark_ClickEvent>(eventInfo);
        Ark_FrameNode arkFrameNode =
            FrameNodePeer::Create(frameNode ? OHOS::Ace::AceType::RawPtr(frameNode) : nullptr);
        auto optValue = Converter::ArkValue<Opt_FrameNode>(arkFrameNode);

        event.InvokeSync(clickEvent.ArkValue(), optValue);
    };
    int32_t resourceId = static_cast<int32_t>((*callback).resource.resourceId);
    NG::UIObserverHandler::AddDidClickListenerCallback(
        static_cast<int32_t>(instanceId), resourceId, std::move(handleFunc));
    return resourceId;
}
Ark_Int32 SetOnWillTapImpl(Ark_Int32 instanceId, const UIObserver_GestureEventListenerCallback* callback)
{
    if (!callback) {
        return 0;
    }
    auto handleFunc = [event = CallbackHelper(*callback)](const GestureEvent& gestureEvent,
        const RefPtr<NG::FrameNode>& frameNode) {
        GestureEvent eventInfo = gestureEvent;
        const auto arkGestureEvent = Converter::SyncEvent<Ark_GestureEvent>(eventInfo);
        Ark_FrameNode arkFrameNode =
            FrameNodePeer::Create(frameNode ? OHOS::Ace::AceType::RawPtr(frameNode) : nullptr);
        auto optValue = Converter::ArkValue<Opt_FrameNode>(arkFrameNode);

        event.InvokeSync(arkGestureEvent.ArkValue(), optValue);
    };
    int32_t resourceId = static_cast<int32_t>((*callback).resource.resourceId);
    NG::UIObserverHandler::AddWillTapListenerCallback(
        static_cast<int32_t>(instanceId), resourceId, std::move(handleFunc));
    return resourceId;
}
Ark_Int32 SetOnDidTapImpl(Ark_Int32 instanceId, const UIObserver_GestureEventListenerCallback* callback)
{
    if (!callback) {
        return 0;
    }
    auto handleFunc = [event = CallbackHelper(*callback)](const GestureEvent& gestureEvent,
        const RefPtr<NG::FrameNode>& frameNode) {
        GestureEvent eventInfo = gestureEvent;
        const auto arkGestureEvent = Converter::SyncEvent<Ark_GestureEvent>(eventInfo);
        Ark_FrameNode arkFrameNode =
            FrameNodePeer::Create(frameNode ? OHOS::Ace::AceType::RawPtr(frameNode) : nullptr);
        auto optValue = Converter::ArkValue<Opt_FrameNode>(arkFrameNode);

        event.InvokeSync(arkGestureEvent.ArkValue(), optValue);
    };
    int32_t resourceId = static_cast<int32_t>((*callback).resource.resourceId);
    NG::UIObserverHandler::AddDidTapListenerCallback(
        static_cast<int32_t>(instanceId), resourceId, std::move(handleFunc));
    return resourceId;
}
Ark_Int32 AddGlobalGestureListenerImpl(Ark_GestureListenerType type,
                                       const Ark_InnerGestureObserverConfigs* option,
                                       const UIObserver_GestureListenerCallback* callback)
{
    if (!callback) {
        return 0;
    }

    // Create a GlobalGestureListenerCallback that receives GestureTriggerInfo directly
    auto handleFunc = [event = CallbackHelper(*callback)](const GestureTriggerInfo& triggerInfo) {
        // Convert GestureTriggerInfo to Ark_InnerGestureTriggerInfo
        const auto arkTriggerInfo = Converter::ArkValue<Ark_InnerGestureTriggerInfo>(triggerInfo);
        // Convert FrameNode to Opt_FrameNode
        Ark_FrameNode arkFrameNode =
            FrameNodePeer::Create(triggerInfo.node ? OHOS::Ace::AceType::RawPtr(triggerInfo.node) : nullptr);
        auto optFrameNode = Converter::ArkValue<Opt_FrameNode>(arkFrameNode);
        event.InvokeSync(arkTriggerInfo, optFrameNode);
    };

    int32_t resourceId = static_cast<int32_t>((*callback).resource.resourceId);

    // Parse option to get action phases
    std::unordered_set<Ark_GestureActionPhase> phases;
    if (option && option->actionPhases.array && option->actionPhases.length > 0) {
        // Parse actionPhases array to extract phase values
        auto phaseArray = option->actionPhases;
        for (int32_t i = 0; i < phaseArray.length; ++i) {
            auto phase = phaseArray.array[i];
            phases.insert(phase);
        }
    } else {
        // Default phase if not specified: WILL_END
        phases.insert(ARK_GESTURE_ACTION_PHASE_WILL_END);
    }

    // Register the callback for each phase
    for (const auto& phase : phases) {
        NG::UIObserverHandler::AddGlobalGestureListenerCallback(
            static_cast<NG::GestureListenerType>(type),
            static_cast<NG::GestureActionPhase>(phase),
            resourceId,
            GlobalGestureListenerCallback(handleFunc)  // Copy the callback for each phase
        );
    }

    return resourceId;
}
} // UIObserverGestureEventOpsAccessor
const GENERATED_ArkUIUIObserverGestureEventOpsAccessor* GetUIObserverGestureEventOpsAccessor()
{
    static const GENERATED_ArkUIUIObserverGestureEventOpsAccessor UIObserverGestureEventOpsAccessorImpl {
        UIObserverGestureEventOpsAccessor::SetOnBeforePanStartImpl,
        UIObserverGestureEventOpsAccessor::SetOnBeforePanEndImpl,
        UIObserverGestureEventOpsAccessor::SetOnAfterPanStartImpl,
        UIObserverGestureEventOpsAccessor::SetOnAfterPanEndImpl,
        UIObserverGestureEventOpsAccessor::SetOnWillClickImpl,
        UIObserverGestureEventOpsAccessor::SetOnDidClickImpl,
        UIObserverGestureEventOpsAccessor::SetOnWillTapImpl,
        UIObserverGestureEventOpsAccessor::SetOnDidTapImpl,
        UIObserverGestureEventOpsAccessor::AddGlobalGestureListenerImpl,
    };
    return &UIObserverGestureEventOpsAccessorImpl;
}

}
