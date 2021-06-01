/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/gesture_listener/render_gesture_listener.h"

#include "core/components/box/render_box.h"
#include "core/components/gesture_listener/gesture_listener_component.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {

#define SET_DRAG_CALLBACK(recognizer, type, component)                                                                 \
    do {                                                                                                               \
        auto& onDragStartId = component->GetOn##type##StartId();                                                       \
        auto& onDragUpdateId = component->GetOn##type##UpdateId();                                                     \
        auto& onDragEndId = component->GetOn##type##EndId();                                                           \
        auto& onDragCancelId = component->GetOn##type##CancelId();                                                     \
        if (!(onDragStartId.IsEmpty() && onDragUpdateId.IsEmpty() && onDragEndId.IsEmpty() &&                          \
                onDragCancelId.IsEmpty())) {                                                                           \
            LOGD("RenderGestureListener: add %{public}s recognizer", #type);                                           \
            recognizer = AceType::MakeRefPtr<type##Recognizer>();                                                      \
            recognizer->SetOnDragStart(AceAsyncEvent<void(const DragStartInfo&)>::Create(onDragStartId, context_));    \
            recognizer->SetOnDragUpdate(AceAsyncEvent<void(const DragUpdateInfo&)>::Create(onDragUpdateId, context_)); \
            recognizer->SetOnDragEnd(AceAsyncEvent<void(const DragEndInfo&)>::Create(onDragEndId, context_));          \
            recognizer->SetOnDragCancel(AceAsyncEvent<void()>::Create(onDragCancelId, context_));                      \
        }                                                                                                              \
    } while (0)

RefPtr<RenderNode> RenderGestureListener::Create()
{
    return AceType::MakeRefPtr<RenderGestureListener>();
}

void RenderGestureListener::Update(const RefPtr<Component>& component)
{
    RenderProxy::Update(component);
    auto gestureComponent = AceType::DynamicCast<GestureListenerComponent>(component);
    ACE_DCHECK(gestureComponent);
    SetOnClickCallback(gestureComponent);
    SetOnLongPressCallback(gestureComponent);
    isVisible_ = gestureComponent->IsVisible();
    SET_DRAG_CALLBACK(freeDragRecognizer_, FreeDrag, gestureComponent);
    if (!freeDragRecognizer_) {
        // Horizontal and vertical gestures can only be enabled in the absence of free gesture.
        LOGD("No free drag, update corresponding horizontal and vertical drag!");
        SET_DRAG_CALLBACK(horizontalDragRecognizer_, HorizontalDrag, gestureComponent);
        SET_DRAG_CALLBACK(verticalDragRecognizer_, VerticalDrag, gestureComponent);
    }
}

bool RenderGestureListener::GetVisible() const
{
    return RenderNode::GetVisible() && isVisible_;
}

void RenderGestureListener::UpdateTouchRect()
{
    RenderNode::UpdateTouchRect();
    if (!GetChildren().empty()) {
        auto box = AceType::DynamicCast<RenderBox>(GetChildren().front());
        // For exclude the margin area from touch area and the margin must not be less than zero.
        if (box) {
            touchRect_.SetOffset(box->GetTouchArea().GetOffset() + GetPaintRect().GetOffset());
            touchRect_.SetSize(box->GetTouchArea().GetSize());
        }
    }
}

void RenderGestureListener::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (clickRecognizer_) {
        clickRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(clickRecognizer_);
    }
    if (longPressRecognizer_) {
        longPressRecognizer_->SetCoordinateOffset(coordinateOffset);
        longPressRecognizer_->SetTouchRestrict(touchRestrict);
        result.emplace_back(longPressRecognizer_);
    }
    if (freeDragRecognizer_) {
        freeDragRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(freeDragRecognizer_);
        return;
    }
    // Horizontal and vertical gestures can only be enabled in the absence of free gesture.
    if (verticalDragRecognizer_) {
        verticalDragRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(verticalDragRecognizer_);
    }
    if (horizontalDragRecognizer_) {
        horizontalDragRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(horizontalDragRecognizer_);
    }
}

void RenderGestureListener::SetOnClickCallback(const RefPtr<GestureListenerComponent>& component)
{
    const auto& onClickId = component->GetOnClickId();
    if (onClickId.IsEmpty()) {
        return;
    }
    SetOnClickCallback(AceAsyncEvent<void(const ClickInfo&)>::Create(onClickId, context_));
}

void RenderGestureListener::SetOnLongPressCallback(const RefPtr<GestureListenerComponent>& component)
{
    const auto& onLongPressId = component->GetOnLongPressId();
    if (onLongPressId.IsEmpty()) {
        return;
    }
    SetOnLongPressCallback(AceAsyncEvent<void(const LongPressInfo&)>::Create(onLongPressId, context_));
}

void RenderGestureListener::SetOnClickCallback(const ClickCallback& callback)
{
    if (callback) {
        if (!clickRecognizer_) {
            clickRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>();
        }
        clickRecognizer_->SetOnClick(callback);
    } else {
        LOGE("fail to set click callback due to callback is nullptr");
    }
}

void RenderGestureListener::SetOnLongPressCallback(const OnLongPress& callback)
{
    if (callback) {
        if (!longPressRecognizer_) {
            longPressRecognizer_ = AceType::MakeRefPtr<LongPressRecognizer>(context_);
        }
        longPressRecognizer_->SetOnLongPress(callback);
    } else {
        LOGE("fail to set long press callback due to callback is nullptr");
    }
}

} // namespace OHOS::Ace
