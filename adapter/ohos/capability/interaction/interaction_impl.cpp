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

#include "interaction_manager.h"
#include "start_drag_listener_impl.h"
#include "core/components_ng/manager/drag_drop/drag_drop_behavior_reporter/drag_drop_behavior_reporter.h"

using namespace OHOS::Msdp::DeviceStatus;

namespace OHOS::Ace {
    Msdp::DeviceStatus::DragCursorStyle TranslateDragCursorStyle(OHOS::Ace::DragCursorStyleCore style);
    Msdp::DeviceStatus::DragResult TranslateDragResult(DragRet dragResult);
    Msdp::DeviceStatus::PreviewStyle TranslatePreviewStyle(const OHOS::Ace::PreviewStyle& previewStyle);
    DragRet TranslateDragResult(Msdp::DeviceStatus::DragResult dragResult);
    Msdp::DeviceStatus::DragBehavior TranslateDragBehavior(OHOS::Ace::DragBehavior dragBehavior);
    OHOS::Ace::DragBehavior TranslateDragBehavior(Msdp::DeviceStatus::DragBehavior dragBehavior);

InteractionInterface* InteractionInterface::GetInstance()
{
    static InteractionImpl instance;
    return &instance;
}

int32_t InteractionImpl::UpdateShadowPic(const OHOS::Ace::ShadowInfoCore& shadowInfo)
{
    auto pixelMap = shadowInfo.pixelMap;
    if (!pixelMap) {
        Msdp::DeviceStatus::ShadowInfo msdpShadowInfo { nullptr, shadowInfo.x, shadowInfo.y };
        return InteractionManager::GetInstance()->UpdateShadowPic(msdpShadowInfo);
    }
    Msdp::DeviceStatus::ShadowInfo msdpShadowInfo { shadowInfo.pixelMap->GetPixelMapSharedPtr(), shadowInfo.x,
        shadowInfo.y };
    return InteractionManager::GetInstance()->UpdateShadowPic(msdpShadowInfo);
}

int32_t InteractionImpl::SetDragWindowVisible(bool visible, const std::shared_ptr<Rosen::RSTransaction>& rSTransaction)
{
    return InteractionManager::GetInstance()->SetDragWindowVisible(visible, false, rSTransaction);
}

int32_t InteractionImpl::SetMouseDragMonitorState(bool state)
{
    return InteractionManager::GetInstance()->SetMouseDragMonitorState(state);
}

int32_t InteractionImpl::StartDrag(const DragDataCore& dragData,
    std::function<void(const OHOS::Ace::DragNotifyMsg&)> callback)
{
    std::function<void(const Msdp::DeviceStatus::DragNotifyMsg&)> callbackCore
        = [=](const Msdp::DeviceStatus::DragNotifyMsg& dragNotifyMsg) {
        OHOS::Ace::DragNotifyMsg msg { dragNotifyMsg.displayX, dragNotifyMsg.displayY, dragNotifyMsg.targetPid,
            TranslateDragResult(dragNotifyMsg.result), TranslateDragBehavior(dragNotifyMsg.dragBehavior) };
        if (callback) {
            callback(msg);
        }
    };
    Msdp::DeviceStatus::DragData msdpDragData { {}, dragData.buffer, dragData.udKey, dragData.extraInfo,
    dragData.filterInfo, dragData.sourceType, dragData.dragNum, dragData.pointerId, dragData.displayX,
    dragData.displayY, dragData.displayId, dragData.mainWindow, dragData.hasCanceledAnimation,
    dragData.hasCoordinateCorrected, dragData.summarys, dragData.isDragDelay, dragData.detailedSummarys };
    for (auto& shadowInfo: dragData.shadowInfos) {
        if (shadowInfo.pixelMap) {
            msdpDragData.shadowInfos.push_back({ shadowInfo.pixelMap->GetPixelMapSharedPtr(),
                shadowInfo.x, shadowInfo.y });
        } else {
            msdpDragData.shadowInfos.push_back({ nullptr, shadowInfo.x, shadowInfo.y });
        }
    }
    return InteractionManager::GetInstance()->StartDrag(msdpDragData,
        std::make_shared<StartDragListenerImpl>(callbackCore));
}

int32_t InteractionImpl::GetDragBundleInfo(DragBundleInfo& dragBundleInfo)
{
    Msdp::DeviceStatus::DragBundleInfo msdpDragBundleInfo;
    auto ret = InteractionManager::GetInstance()->GetDragBundleInfo(msdpDragBundleInfo);
    dragBundleInfo.bundleName = msdpDragBundleInfo.bundleName;
    dragBundleInfo.isRemoteDev = msdpDragBundleInfo.isCrossDevice;
    return ret;
}

int32_t InteractionImpl::UpdateDragStyle(OHOS::Ace::DragCursorStyleCore style, const int32_t eventId)
{
    return InteractionManager::GetInstance()->UpdateDragStyle(TranslateDragCursorStyle(style), eventId);
}

int32_t InteractionImpl::UpdatePreviewStyle(const OHOS::Ace::PreviewStyle& previewStyle)
{
    Msdp::DeviceStatus::PreviewStyle msdpPreviewStyle = TranslatePreviewStyle(previewStyle);
    return InteractionManager::GetInstance()->UpdatePreviewStyle(msdpPreviewStyle);
}

int32_t InteractionImpl::UpdatePreviewStyleWithAnimation(const OHOS::Ace::PreviewStyle& previewStyle,
    const OHOS::Ace::PreviewAnimation& animation)
{
    Msdp::DeviceStatus::PreviewStyle msdpPreviewStyle = TranslatePreviewStyle(previewStyle);
    Msdp::DeviceStatus::PreviewAnimation msdpAnimation { animation.duration, animation.curveName, animation.curve };
    return InteractionManager::GetInstance()->UpdatePreviewStyleWithAnimation(msdpPreviewStyle, msdpAnimation);
}

int32_t InteractionImpl::StopDrag(DragDropRet result)
{
    Msdp::DeviceStatus::DragDropResult dragDropResult { TranslateDragResult(result.result), result.hasCustomAnimation,
    result.mainWindow, TranslateDragBehavior(result.dragBehavior) };
    auto ret = InteractionManager::GetInstance()->StopDrag(dragDropResult);
    NG::DragDropBehaviorReporter::GetInstance().UpdateDragStopResult(
        ret ? NG::DragStopResult::DRAGFWK_STOP_FAIL : NG::DragStopResult::DRAG_SOTP_SUCCESS);
    NG::DragDropBehaviorReporter::GetInstance().Submit(NG::DragReporterPharse::DRAG_STOP, -1);
    return ret;
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

int32_t InteractionImpl::RegisterCoordinationListener(std::function<void()> dragOutCallback)
{
    std::function<void(Msdp::CoordinationMessage)> callback
        = [dragOutCallback](Msdp::CoordinationMessage dragNotifyMsg) {
        if (dragOutCallback && dragNotifyMsg == Msdp::CoordinationMessage::COORDINATION_SUCCESS) {
            dragOutCallback();
        }
    };
    if (consumer_) {
        UnRegisterCoordinationListener();
    }
    consumer_ = std::make_shared<CoordinationListenerImpl>(callback);
    return InteractionManager::GetInstance()->RegisterCoordinationListener(consumer_);
}

int32_t InteractionImpl::UnRegisterCoordinationListener()
{
    CHECK_NULL_RETURN(consumer_, 0);
    auto ret = InteractionManager::GetInstance()->UnregisterCoordinationListener(consumer_);
    consumer_ = nullptr;
    return ret;
}

int32_t InteractionImpl::SetDraggableState(bool state)
{
    return InteractionManager::GetInstance()->SetDraggableState(state);
}

int32_t InteractionImpl::GetAppDragSwitchState(bool& state)
{
    return InteractionManager::GetInstance()->GetAppDragSwitchState(state);
}

void InteractionImpl::SetDraggableStateAsync(bool state, int64_t downTime)
{
    InteractionManager::GetInstance()->SetDraggableStateAsync(state, downTime);
}

int32_t InteractionImpl::EnableInternalDropAnimation(const std::string& animationInfo)
{
    return InteractionManager::GetInstance()->EnableInternalDropAnimation(animationInfo);
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

Msdp::DeviceStatus::PreviewStyle TranslatePreviewStyle(const OHOS::Ace::PreviewStyle& previewStyle)
{
    Msdp::DeviceStatus::PreviewStyle msdpPreviewStyle;
    for (auto& previewType: previewStyle.types) {
        switch (previewType) {
            case OHOS::Ace::PreviewType::FOREGROUND_COLOR:
                msdpPreviewStyle.types.push_back(Msdp::DeviceStatus::PreviewType::FOREGROUND_COLOR);
                break;
            case OHOS::Ace::PreviewType::OPACITY:
                msdpPreviewStyle.types.push_back(Msdp::DeviceStatus::PreviewType::OPACITY);
                break;
            case OHOS::Ace::PreviewType::RADIUS:
                msdpPreviewStyle.types.push_back(Msdp::DeviceStatus::PreviewType::RADIUS);
                break;
            case OHOS::Ace::PreviewType::SCALE:
                msdpPreviewStyle.types.push_back(Msdp::DeviceStatus::PreviewType::SCALE);
                break;
            default:
                msdpPreviewStyle.types.push_back(Msdp::DeviceStatus::PreviewType::FOREGROUND_COLOR);
                break;
        }
    }
    msdpPreviewStyle.foregroundColor = previewStyle.foregroundColor;
    msdpPreviewStyle.opacity = previewStyle.opacity;
    msdpPreviewStyle.radius = previewStyle.radius;
    msdpPreviewStyle.scale = previewStyle.scale;
    return msdpPreviewStyle;
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
            return DragRet::DRAG_FAIL;
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

Msdp::DeviceStatus::DragBehavior TranslateDragBehavior(OHOS::Ace::DragBehavior dragBehavior)
{
    switch (dragBehavior) {
        case OHOS::Ace::DragBehavior::COPY:
            return Msdp::DeviceStatus::DragBehavior::COPY;
        case OHOS::Ace::DragBehavior::MOVE:
            return Msdp::DeviceStatus::DragBehavior::MOVE;
        default:
            return Msdp::DeviceStatus::DragBehavior::UNKNOWN;
    }
}
OHOS::Ace::DragBehavior TranslateDragBehavior(Msdp::DeviceStatus::DragBehavior dragBehavior)
{
    switch (dragBehavior) {
        case Msdp::DeviceStatus::DragBehavior::COPY:
            return OHOS::Ace::DragBehavior::COPY;
        case Msdp::DeviceStatus::DragBehavior::MOVE:
            return OHOS::Ace::DragBehavior::MOVE;
        default:
            return OHOS::Ace::DragBehavior::UNKNOWN;
    }
}

bool InteractionImpl::IsDragStart() const
{
    return InteractionManager::GetInstance()->IsDragStart();
}
} // namespace OHOS::Ace