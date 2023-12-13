/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "interaction_impl.h"
#include "drag_data.h"
#include "core/common/interaction/interaction_data.h"
#include "core/gestures/gesture_info.h"

#ifdef ENABLE_DRAG_FRAMEWORK
#include "interaction_manager.h"
#include "start_drag_listener_impl.h"

using namespace OHOS::Msdp::DeviceStatus;

namespace OHOS::Ace {
    Msdp::DeviceStatus::DragCursorStyle TranslateDragCursorStyle(OHOS::Ace::DragCursorStyleCore style);
    Msdp::DeviceStatus::DragResult TranslateDragResult(DragRet dragResult);
    DragRet TranslateDragResult(Msdp::DeviceStatus::DragResult dragResult);

InteractionInterface* InteractionInterface::GetInstance()
{
    static InteractionImpl instance;
    return &instance;
}

int32_t InteractionImpl::UpdateShadowPic(const OHOS::Ace::ShadowInfoCore& shadowInfo)
{
    Msdp::DeviceStatus::ShadowInfo msdpShadowInfo { shadowInfo.pixelMap, shadowInfo.x,
        shadowInfo.y };
    return InteractionManager::GetInstance()->UpdateShadowPic(msdpShadowInfo);
}

int32_t InteractionImpl::SetDragWindowVisible(bool visible)
{
    return InteractionManager::GetInstance()->SetDragWindowVisible(visible);
}

int32_t InteractionImpl::StartDrag(const DragDataCore& dragData,
    std::function<void(const OHOS::Ace::DragNotifyMsg&)> callback)
{
    std::function<void(const Msdp::DeviceStatus::DragNotifyMsg&)> callbackCore
        = [=](const Msdp::DeviceStatus::DragNotifyMsg& dragNotifyMsg) {
        OHOS::Ace::DragNotifyMsg msg { dragNotifyMsg.displayX,
            dragNotifyMsg.displayY, dragNotifyMsg.targetPid, TranslateDragResult(dragNotifyMsg.result) };
        callback(msg);
    };
    Msdp::DeviceStatus::ShadowInfo shadowInfo { dragData.shadowInfo.pixelMap,
        dragData.shadowInfo.x, dragData.shadowInfo.y };
    Msdp::DeviceStatus::DragData msdpDragData { { shadowInfo },
        dragData.buffer, dragData.udKey, dragData.filterInfo, dragData.extraInfo,
        dragData.sourceType, dragData.dragNum, dragData.pointerId, dragData.displayX, dragData.displayY,
        dragData.displayId, dragData.hasCanceledAnimation, false, dragData.summary };
    return InteractionManager::GetInstance()->StartDrag(msdpDragData,
        std::make_shared<StartDragListenerImpl>(callbackCore));
}

int32_t InteractionImpl::UpdateDragStyle(OHOS::Ace::DragCursorStyleCore style)
{
    return InteractionManager::GetInstance()->UpdateDragStyle(TranslateDragCursorStyle(style));
}

int32_t InteractionImpl::StopDrag(DragDropRet result)
{
    if (SystemProperties::GetDebugEnabled()) {
        LOGI("InteractionImpl StopDrag, DragResult is %{public}d.", result.result);
    }
    Msdp::DeviceStatus::DragDropResult dragDropResult {
        TranslateDragResult(result.result), result.hasCustomAnimation, result.windowId };
    return InteractionManager::GetInstance()->StopDrag(dragDropResult);
}

int32_t InteractionImpl::GetUdKey(std::string& udKey)
{
    return InteractionManager::GetInstance()->GetUdKey(udKey);
}

int32_t InteractionImpl::GetShadowOffset(ShadowOffsetData& shadowOffsetData)
{
    return InteractionManager::GetInstance()->GetShadowOffset(
        shadowOffsetData.offsetX, shadowOffsetData.offsetY, shadowOffsetData.width, shadowOffsetData.height);
}

int32_t InteractionImpl::GetDragSummary(std::map<std::string, int64_t>& summary)
{
    return InteractionManager::GetInstance()->GetDragSummary(summary);
}

int32_t InteractionImpl::GetDragExtraInfo(std::string& extraInfo)
{
    return InteractionManager::GetInstance()->GetExtraInfo(extraInfo);
}

int32_t InteractionImpl::EnterTextEditorArea(bool enable)
{
    return InteractionManager::GetInstance()->EnterTextEditorArea(enable);
}

int32_t InteractionImpl::AddPrivilege()
{
    return InteractionManager::GetInstance()->AddPrivilege();
}

Msdp::DeviceStatus::DragCursorStyle TranslateDragCursorStyle(OHOS::Ace::DragCursorStyleCore style)
{
    switch (style) {
        case OHOS::Ace::DragCursorStyleCore::DEFAULT:
            return Msdp::DeviceStatus::DragCursorStyle::DEFAULT;
        case OHOS::Ace::DragCursorStyleCore::FORBIDDEN:
            return Msdp::DeviceStatus::DragCursorStyle::FORBIDDEN;
        case OHOS::Ace::DragCursorStyleCore::COPY:
            return Msdp::DeviceStatus::DragCursorStyle::COPY;
        case OHOS::Ace::DragCursorStyleCore::MOVE:
            return Msdp::DeviceStatus::DragCursorStyle::MOVE;
        default:
            return Msdp::DeviceStatus::DragCursorStyle::DEFAULT;
    }
}

Msdp::DeviceStatus::DragResult TranslateDragResult(DragRet dragResult)
{
    switch (dragResult) {
        case DragRet::DRAG_SUCCESS:
            return Msdp::DeviceStatus::DragResult::DRAG_SUCCESS;
        case DragRet::DRAG_FAIL:
            return Msdp::DeviceStatus::DragResult::DRAG_FAIL;
        case DragRet::DRAG_CANCEL:
            return Msdp::DeviceStatus::DragResult::DRAG_CANCEL;
        default:
            return Msdp::DeviceStatus::DragResult::DRAG_SUCCESS;
    }
}

DragRet TranslateDragResult(Msdp::DeviceStatus::DragResult dragResult)
{
    switch (dragResult) {
        case Msdp::DeviceStatus::DragResult::DRAG_SUCCESS:
            return DragRet::DRAG_SUCCESS;
        case Msdp::DeviceStatus::DragResult::DRAG_FAIL:
            return DragRet::DRAG_FAIL;
        case Msdp::DeviceStatus::DragResult::DRAG_CANCEL:
            return DragRet::DRAG_CANCEL;
        default:
            return DragRet::DRAG_SUCCESS;
    }
}

int32_t InteractionImpl::GetDragState(DragState& dragState) const
{
    Msdp::DeviceStatus::DragState state;
    int32_t ret = InteractionManager::GetInstance()->GetDragState(state);
    switch (state) {
        case Msdp::DeviceStatus::DragState::ERROR:
            dragState = DragState::ERROR;
            break;
        case Msdp::DeviceStatus::DragState::START:
            dragState = DragState::START;
            break;
        case Msdp::DeviceStatus::DragState::STOP:
            dragState = DragState::STOP;
            break;
        case Msdp::DeviceStatus::DragState::CANCEL:
            dragState = DragState::CANCEL;
            break;
        case Msdp::DeviceStatus::DragState::MOTION_DRAGGING:
            dragState = DragState::MOTION_DRAGGING;
            break;
        default:
            dragState = DragState::ERROR;
            LOGW("unknow msdp drag state: %d", state);
            break;
    }
    return ret;
}
} // namespace OHOS::Ace
#endif // ENABLE_DRAG_FRAMEWORK