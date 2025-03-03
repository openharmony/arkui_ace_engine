/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_HANDLER_H

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_machine.h"

namespace OHOS::Ace::NG {

class DragDropInitiatingHandler : public AceType {
    DECLARE_ACE_TYPE(DragDropInitiatingHandler, AceType);

public:
    DragDropInitiatingHandler(const RefPtr<FrameNode>& frameNode);
    ~DragDropInitiatingHandler() = default;

    DragDropInitiatingStatus GetDragDropInitiatingStatus();

    void NotifyLongPressOnAction(const GestureEvent& info);
    void NotifyLongPressOnActionEnd(const GestureEvent& info);
    void NotifyLongPressOnActionCancel(const GestureEvent& info);

    void NotifyPreviewLongPressOnAction(const GestureEvent& info);
    void NotifyPreviewLongPressOnActionEnd(const GestureEvent& info);
    void NotifyPreviewLongPressOnActionCancel(const GestureEvent& info);

    void NotifyPanOnActionStart(const GestureEvent& info);
    void NotifyPanOnActionUpdate(const GestureEvent& info);
    void NotifyPanOnActionEnd(const GestureEvent& info);
    void NotifyPanOnActionCancel(const GestureEvent& info);
    void NotifyPanOnReject();
    void NotifySequenceOnActionCancel(const GestureEvent& info);
    void NotifyHitTesting(const TouchEvent& touchEvent);
    void NotifyTouchEvent(const TouchEvent& touchEvent);
    void NotifyPullEvent(const DragPointerEvent& dragPointerEvent);
    void NotifyReStartDrag(const GestureEvent& info);

    RefPtr<PixelMap> GetPreScaledPixelMapForDragThroughTouch(float& preScale);
    void ResetPreScaledPixelMapForDragThroughTouch();
    void SetThumbnailCallback(std::function<void(Offset)>&& callback);

    void NotifyDragStart();
    void NotifyTransDragWindowToFwk();
    void NotifyMenuShow(bool isMenuShow);
    void NotifyDragEnd();

    bool IsNeedGather();

private:
    RefPtr<DragDropInitiatingStateMachine> initiatingFlow_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_HANDLER_H