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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_DRAG_DROP_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_DRAG_DROP_EVENT_H

#include "core/components_ng/event/drag_event.h"

namespace OHOS::Ace::NG {

class DragDropInitiatingHandler;
class DragEvent;
class GestureEventHub;
class PanRecognizer;
class LongPressRecognizer;

class ACE_EXPORT DragDropEventActuator : public DragEventActuator {
    DECLARE_ACE_TYPE(DragDropEventActuator, DragEventActuator)
public:
    DragDropEventActuator(const WeakPtr<GestureEventHub>& gestureEventHub);
    ~DragDropEventActuator() override = default;

    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result,
        ResponseLinkResult& responseLinkResult) override;
    void CopyEvent(const RefPtr<DragDropEventActuator>& dragDropEventActuator);
    RefPtr<PixelMap> GetPreScaledPixelMapForDragThroughTouch(float& preScale) override;
    void ResetPreScaledPixelMapForDragThroughTouch() override;
    void RestartDragTask(const GestureEvent& info) override;
    bool GetIsNotInPreviewState() const override;
    bool IsNeedGather() const override;
    void SetThumbnailCallback(std::function<void(Offset)>&& callback) override;
    void HandleTouchEvent(const TouchEventInfo& info, bool isRestartDrag = false) override;

    void NotifyDragStart() override;
    void NotifyTransDragWindowToFwk() override;
    void NotifyMenuShow(bool isMenuShow) override;
    void NotifyDragEnd() override;

private:
    void InitPanAction();
    void InitLongPressAction();

private:
    WeakPtr<GestureEventHub> gestureEventHub_;
    RefPtr<PanRecognizer> panRecognizer_;
    RefPtr<LongPressRecognizer> longPressRecognizer_;
    RefPtr<LongPressRecognizer> previewLongPressRecognizer_;
    RefPtr<SequencedRecognizer> SequencedRecognizer_;
    RefPtr<DragDropInitiatingHandler> dragDropInitiatingHandler_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_DRAG_DROP_EVENT_H