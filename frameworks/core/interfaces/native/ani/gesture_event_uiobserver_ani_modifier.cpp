/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gesture_event_uiobserver_ani_modifier.h"

#include "base/log/log.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/node_render_status_monitor.h"
#include "core/components_ng/base/observer_handler.h"

namespace OHOS::Ace::NG {

void RemovePanListenerCallback(const std::string& tag, ani_int instanceId, ani_int resourceId, bool isRemoveAll)
{
    if (tag == "beforePanStart") {
        UIObserverHandler::RemoveBeforePanStartListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    } else if (tag == "beforePanEnd") {
        UIObserverHandler::RemoveBeforePanEndListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    } else if (tag == "afterPanStart") {
        UIObserverHandler::RemoveAfterPanStartListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    } else if (tag == "afterPanEnd") {
        UIObserverHandler::RemoveAfterPanEndListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    }
}

std::pair<bool, int32_t> GetNodeInfo(
    int32_t instanceId, int32_t nodeId, const std::string& nodeKey, bool isStr, bool isInt)
{
    std::pair<bool, bool> abnormal(false, 0);
    auto container = AceEngine::Get().GetContainer(static_cast<int32_t>(instanceId));
    CHECK_NULL_RETURN(container, abnormal);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, abnormal);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(pipelineContext, abnormal);

    RefPtr<NG::UINode> node = nullptr;
    if (isStr) {
        node = NG::Inspector::GetInspectorByKey(pipelineContext->GetRootElement(), nodeKey);
    }

    if (isInt) {
        node = OHOS::Ace::ElementRegister::GetInstance()->GetUINodeById(nodeId);
    }

    if (node) {
        return { true, node->GetId() };
    }
    return abnormal;
}

std::pair<bool, bool> IsNodeRenderStateRegisterLimited(int32_t instanceId, int32_t resourceId, int32_t nodeId)
{
    std::pair<bool, bool> abnormal(true, false);
    auto container = AceEngine::Get().GetContainer(static_cast<int32_t>(instanceId));
    CHECK_NULL_RETURN(container, abnormal);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, abnormal);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(pipelineContext, abnormal);
    auto monitor = pipelineContext->GetNodeRenderStatusMonitor();
    CHECK_NULL_RETURN(monitor, abnormal);
    return monitor->IsNodeRenderStateRegisterLimited(resourceId, nodeId);
}

void TriggerNodeRenderStateForFirstRegister(int32_t instanceId, int32_t resourceId, int32_t nodeId)
{
    auto container = AceEngine::Get().GetContainer(static_cast<int32_t>(instanceId));
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_VOID(pipelineContext);
    auto monitor = pipelineContext->GetNodeRenderStatusMonitor();
    CHECK_NULL_VOID(monitor);
    return monitor->TriggerCallbackForFirstRegister(nodeId, resourceId);
}

void RemoveNodeRenderStateCallback(int32_t instanceId, int32_t resourceId, int32_t nodeId, bool isRemoveAll)
{
    auto container = AceEngine::Get().GetContainer(static_cast<int32_t>(instanceId));
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_VOID(pipelineContext);
    auto monitor = pipelineContext->GetNodeRenderStatusMonitor();
    CHECK_NULL_VOID(monitor);
    monitor->RemoveNodeRenderStateCallbackByResourceId(nodeId, resourceId, isRemoveAll);
}

void RemoveClickListenerCallback(const std::string& tag, ani_int instanceId, ani_int resourceId, bool isRemoveAll)
{
    if (tag == "willClick") {
        UIObserverHandler::RemoveWillClickListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    } else if (tag == "didClick") {
        UIObserverHandler::RemoveDidClickListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    }
}

void RemoveTapListenerCallback(const std::string& tag, ani_int instanceId, ani_int resourceId, bool isRemoveAll)
{
    if (tag == "willTap") {
        UIObserverHandler::RemoveWillTapListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    } else if (tag == "didTap") {
        UIObserverHandler::RemoveDidTapListenerCallback(
            static_cast<int32_t>(instanceId), static_cast<int32_t>(resourceId), isRemoveAll);
    }
}

void RemoveGlobalGestureListenerCallback(ani_int type, ani_int resourceId, bool isRemoveAll)
{
    if (isRemoveAll) {
        // Remove all callbacks for this gestureType across all phases
        // Note: This is equivalent to removing by gestureType only
        GestureActionPhase phases[] = {
            GestureActionPhase::WILL_START,
            GestureActionPhase::WILL_END
        };
        for (const auto& phase : phases) {
            UIObserverHandler::RemoveGlobalGestureListenerCallback(
                static_cast<GestureListenerType>(type),
                phase);
        }
    } else {
        // Remove callbacks matching the gestureType and resourceId
        UIObserverHandler::RemoveGlobalGestureListenerCallback(
            static_cast<GestureListenerType>(type),
            static_cast<int32_t>(resourceId));
    }
}

const ArkUIAniGestureEventUIObserverModifier* GetArkUIAniGestureEventUIObserverModifier()
{
    static const ArkUIAniGestureEventUIObserverModifier impl = {
        .removePanListenerCallback = OHOS::Ace::NG::RemovePanListenerCallback,
        .getNodeInfo = OHOS::Ace::NG::GetNodeInfo,
        .isNodeRenderStateRegisterLimited = OHOS::Ace::NG::IsNodeRenderStateRegisterLimited,
        .triggerNodeRenderStateForFirstRegister = OHOS::Ace::NG::TriggerNodeRenderStateForFirstRegister,
        .removeNodeRenderStateCallback = OHOS::Ace::NG::RemoveNodeRenderStateCallback,
        .removeClickListenerCallback = OHOS::Ace::NG::RemoveClickListenerCallback,
        .removeTapListenerCallback = OHOS::Ace::NG::RemoveTapListenerCallback,
        .removeGlobalGestureListenerCallback = OHOS::Ace::NG::RemoveGlobalGestureListenerCallback,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG