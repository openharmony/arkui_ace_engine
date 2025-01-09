/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/dom/dom_document.h"

namespace OHOS::Ace {

namespace {

constexpr int32_t DOUBLE_CLICK = 2;
constexpr int32_t DEFAULT_PINCH_FINGER = 2;
constexpr double DEFAULT_PINCH_DISTANCE = 1.0;
constexpr int32_t BUBBLE_MODE_VERSION = 6;

}
#if !defined(PREVIEW)
void RenderGestureListener::SetDragCallBack(RefPtr<FreeDragRecognizer>& recognizer,
    RefPtr<GestureListenerComponent> component)
{
    auto& onDragStartId = component->GetOnFreeDragStartId();
    auto& onDragUpdateId = component->GetOnFreeDragUpdateId();
    auto& onDragEndId = component->GetOnFreeDragEndId();
    auto& onDragCancelId = component->GetOnFreeDragCancelId();
    GestureItemInfo dragInfo;
    OnGestureFunc onDragStart = component->GetOnDragStartId();

    if (!(onDragStartId.IsEmpty() && onDragUpdateId.IsEmpty() && onDragEndId.IsEmpty() &&
        onDragCancelId.IsEmpty())) {
        recognizer = AceType::MakeRefPtr<FreeDragRecognizer>();
        auto pipelineContext = context_.Upgrade();
        if (!pipelineContext) {
            LOGE("Context is null.");
            return;
        }
        auto funcStart = AceAsyncEvent<void(const DragStartInfo&)>::Create(onDragStartId, context_);
        auto funcDragStart = [pipelineContext, weak = AceType::WeakClaim<>(this), funcStart, onDragStart]
            (const DragStartInfo& info)->void {
            if (funcStart) {
                funcStart(info);
            }
            GestureItemInfo dragInfo;
            if (onDragStart) {
                dragInfo = onDragStart();
            }
            if (dragInfo.pixelMap) {
                auto renderNode = weak.Upgrade();
                if (!renderNode->dragWindow_) {
                    auto rect = pipelineContext->GetCurrentWindowRect();
                    renderNode->dragWindow_ = DragWindow::CreateDragWindow("APP_DRAG_WINDOW",
                        static_cast<int32_t>(info.GetGlobalLocation().GetX()) + rect.Left(),
                        static_cast<int32_t>(info.GetGlobalLocation().GetY()) + rect.Top(),
                        dragInfo.pixelMap->GetWidth(), dragInfo.pixelMap->GetHeight());
                    renderNode->dragWindow_->SetOffset(rect.Left(), rect.Top());
                    renderNode->dragWindow_->DrawPixelMap(dragInfo.pixelMap);
                }
            }
        };
        auto funcUpdate = AceAsyncEvent<void(const DragUpdateInfo&)>::Create(onDragUpdateId, context_);
        auto funcDragUpdate = [pipelineContext, weak = AceType::WeakClaim<>(this), funcUpdate, onDragStart]
            (const DragUpdateInfo& info)->void {
            if (funcUpdate) {
                funcUpdate(info);
            }
            GestureItemInfo dragInfo;
            if (onDragStart) {
                dragInfo = onDragStart();
            }
            if (dragInfo.pixelMap) {
                auto renderNode = weak.Upgrade();
                if (!renderNode->dragWindow_) {
                    auto rect = pipelineContext->GetCurrentWindowRect();
                    renderNode->dragWindow_ = DragWindow::CreateDragWindow("APP_DRAG_WINDOW",
                        static_cast<int32_t>(info.GetGlobalLocation().GetX()) + rect.Left(),
                        static_cast<int32_t>(info.GetGlobalLocation().GetY()) + rect.Top(),
                        dragInfo.pixelMap->GetWidth(), dragInfo.pixelMap->GetHeight());
                    renderNode->dragWindow_->SetOffset(rect.Left(), rect.Top());
                    renderNode->dragWindow_->DrawPixelMap(dragInfo.pixelMap);
                } else {
                    int32_t x = static_cast<int32_t>(info.GetGlobalLocation().GetX());
                    int32_t y = static_cast<int32_t>(info.GetGlobalLocation().GetY());
                    int32_t offsetX = x + dragInfo.pixelMap->GetWidth() / 2
                        - dragInfo.offsetX;
                    int32_t offsetY = y + dragInfo.pixelMap->GetHeight()
                        - dragInfo.offsetY;
                    renderNode->dragWindow_->MoveTo(offsetX, offsetY);
                }
            }
        };
        auto funcEnd = AceAsyncEvent<void(const DragEndInfo&)>::Create(onDragEndId, context_);
        auto funcDragEnd = [pipelineContext, weak = AceType::WeakClaim<>(this), funcEnd, onDragStart]
            (const DragEndInfo& info)->void {
            if (funcEnd) {
                funcEnd(info);
            }
            auto renderNode = weak.Upgrade();
            GestureItemInfo dragInfo;
            if (onDragStart) {
                dragInfo = onDragStart();
            }
            if (dragInfo.pixelMap && renderNode->dragWindow_) {
                if (renderNode->dragWindow_) {
                    renderNode->dragWindow_->Destroy();
                    renderNode->dragWindow_ = nullptr;
                }
            }
        };
        recognizer->SetOnDragStart(funcDragStart);
        recognizer->SetOnDragUpdate(funcDragUpdate);
        recognizer->SetOnDragEnd(funcDragEnd);
        recognizer->SetOnDragCancel(AceAsyncEvent<void()>::Create(onDragCancelId, context_));
    }
}
#endif

#define SET_DRAG_CALLBACK(recognizer, type, component)                                                                 \
    do {                                                                                                               \
        auto& onDragStartId = component->GetOn##type##StartId();                                                       \
        auto& onDragUpdateId = component->GetOn##type##UpdateId();                                                     \
        auto& onDragEndId = component->GetOn##type##EndId();                                                           \
        auto& onDragCancelId = component->GetOn##type##CancelId();                                                     \
        if (!(onDragStartId.IsEmpty() && onDragUpdateId.IsEmpty() && onDragEndId.IsEmpty() &&                          \
                onDragCancelId.IsEmpty())) {                                                                           \
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
    if (!gestureComponent) {
        LOGE("gestureComponent is null");
        return;
    }
    ACE_DCHECK(gestureComponent);
    SetRemoteMessageCallback(gestureComponent);
    SetOnClickCallback(gestureComponent);
    SetOnDoubleClickCallback(gestureComponent);
    SetOnLongPressCallback(gestureComponent);
    SetOnPinchStartCallback(gestureComponent);
    SetOnPinchUpdateCallback(gestureComponent);
    SetOnPinchEndCallback(gestureComponent);
    SetOnPinchCancelCallback(gestureComponent);
    isVisible_ = gestureComponent->IsVisible();
    responseRegion_ = gestureComponent->GetResponseRegion();
    isResponseRegion_ = gestureComponent->IsResponseRegion();
#if !defined(PREVIEW)
    SetDragCallBack(freeDragRecognizer_, gestureComponent);
#else
    SET_DRAG_CALLBACK(freeDragRecognizer_, FreeDrag, gestureComponent);
#endif
    if (!freeDragRecognizer_) {
        // Horizontal and vertical gestures can only be enabled in the absence of free gesture.
        SET_DRAG_CALLBACK(horizontalDragRecognizer_, HorizontalDrag, gestureComponent);
        SET_DRAG_CALLBACK(verticalDragRecognizer_, VerticalDrag, gestureComponent);
        return;
    }

    freeDragRecognizer_->SetDragUpdateNotify([&](double x, double y, const DragUpdateInfo& updateInfo) {
        auto context = context_.Upgrade();
        if (!context) {
            return;
        }
        TouchEvent point;
        point.x = x;
        point.y = y;
        if (dragTarget_ == nullptr) {
            RefPtr<RenderBox> renderBox = AceType::DynamicCast<RenderBox>(context->DragTestAll(point));
            if (renderBox) {
                dragTarget_ = renderBox;
                dragTarget_->onDomDragEnter_(updateInfo);
            }
        } else {
            if (dragTarget_->IsPointInBox(point)) {
                if (dragTarget_->onDomDragOver_) {
                    dragTarget_->onDomDragOver_(updateInfo);
                }
            } else {
                if (dragTarget_->onDomDragLeave_) {
                    dragTarget_->onDomDragLeave_(updateInfo);
                }
                dragTarget_ = nullptr;
            }
        }
    });

    freeDragRecognizer_->SetDragEndNotify([&](double x, double y, const DragEndInfo& endInfo) {
        if (dragTarget_ != nullptr) {
            if (dragTarget_->onDomDragDrop_) {
                dragTarget_->onDomDragDrop_(endInfo);
            }
            dragTarget_ = nullptr;
        }
    });
}

bool RenderGestureListener::GetVisible() const
{
    return RenderNode::GetVisible() && isVisible_;
}

void RenderGestureListener::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (clickRecognizer_) {
        clickRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(clickRecognizer_);
    }
    if (doubleClickRecognizer_) {
        doubleClickRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(doubleClickRecognizer_);
    }
    if (longPressRecognizer_) {
        longPressRecognizer_->SetCoordinateOffset(coordinateOffset);
        longPressRecognizer_->SetTouchRestrict(touchRestrict);
        result.emplace_back(longPressRecognizer_);
    }
    if (pinchRecognizer_) {
        pinchRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(pinchRecognizer_);
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
    if (!onClickId.GetCatchMode()) {
        static const int32_t bubbleModeVersion = 6;
        auto pipeline = context_.Upgrade();
        if (pipeline && pipeline->GetMinPlatformVersion() >= bubbleModeVersion) {
            clickRecognizer_->SetUseCatchMode(false);
            return;
        }
    }
    clickRecognizer_->SetUseCatchMode(true);
    clickRecognizer_->SetIsExternalGesture(true);
}

void RenderGestureListener::SetRemoteMessageCallback(const RefPtr<GestureListenerComponent>& component)
{
    const auto& remoteMessageId = component->GetRemoteMessageId();
    if (remoteMessageId.IsEmpty()) {
        return;
    }
    SetRemoteMessageCallback(AceAsyncEvent<void(const ClickInfo&)>::Create(remoteMessageId, context_));
    if (!remoteMessageId.GetCatchMode()) {
        static const int32_t bubbleModeVersion = 6;
        auto pipeline = context_.Upgrade();
        if (pipeline && pipeline->GetMinPlatformVersion() >= bubbleModeVersion) {
            clickRecognizer_->SetUseCatchMode(false);
            return;
        }
    }
    clickRecognizer_->SetUseCatchMode(true);
    clickRecognizer_->SetIsExternalGesture(true);
}

void RenderGestureListener::SetOnDoubleClickCallback(const RefPtr<GestureListenerComponent>& component)
{
    const auto& onDoubleClickId = component->GetOnDoubleClickId();
    if (onDoubleClickId.IsEmpty()) {
        return;
    }
    SetOnDoubleClickCallback(AceAsyncEvent<void(const ClickInfo&)>::Create(onDoubleClickId, context_));
    if (!onDoubleClickId.GetCatchMode()) {
        auto pipeline = context_.Upgrade();
        if (pipeline && pipeline->GetMinPlatformVersion() >= BUBBLE_MODE_VERSION) {
            doubleClickRecognizer_->SetUseCatchMode(false);
            return;
        }
    }
    doubleClickRecognizer_->SetUseCatchMode(true);
    doubleClickRecognizer_->SetIsExternalGesture(true);
}

void RenderGestureListener::SetOnLongPressCallback(const RefPtr<GestureListenerComponent>& component)
{
    const auto& onLongPressId = component->GetOnLongPressId();
    if (onLongPressId.IsEmpty()) {
        return;
    }
    SetOnLongPressCallback(AceAsyncEvent<void(const LongPressInfo&)>::Create(onLongPressId, context_));
    if (!onLongPressId.GetCatchMode()) {
        auto pipeline = context_.Upgrade();
        if (pipeline && pipeline->GetMinPlatformVersion() >= BUBBLE_MODE_VERSION) {
            longPressRecognizer_->SetUseCatchMode(false);
            return;
        }
    }
    longPressRecognizer_->SetUseCatchMode(true);
    longPressRecognizer_->SetIsExternalGesture(true);
}

void RenderGestureListener::SetOnPinchStartCallback(const RefPtr<GestureListenerComponent>& component)
{
    const auto& onPinchStartId = component->GetOnPinchStartId();
    if (onPinchStartId.IsEmpty()) {
        return;
    }
    SetOnPinchStartCallback(AceAsyncEvent<void(const GestureEvent&)>::Create(onPinchStartId, context_));
}

void RenderGestureListener::SetOnPinchUpdateCallback(const RefPtr<GestureListenerComponent>& component)
{
    const auto& onPinchUpdateId = component->GetOnPinchUpdateId();
    if (onPinchUpdateId.IsEmpty()) {
        return;
    }
    SetOnPinchUpdateCallback(AceAsyncEvent<void(const GestureEvent&)>::Create(onPinchUpdateId, context_));
}

void RenderGestureListener::SetOnPinchEndCallback(const RefPtr<GestureListenerComponent>& component)
{
    const auto& onPinchEndId = component->GetOnPinchEndId();
    if (onPinchEndId.IsEmpty()) {
        return;
    }
    SetOnPinchEndCallback(AceAsyncEvent<void(const GestureEvent&)>::Create(onPinchEndId, context_));
}

void RenderGestureListener::SetOnPinchCancelCallback(const RefPtr<GestureListenerComponent>& component)
{
    const auto& onPinchCancelId = component->GetOnPinchCancelId();
    if (onPinchCancelId.IsEmpty()) {
        return;
    }
    SetOnPinchCancelCallback(AceAsyncEvent<void(const GestureEvent&)>::Create(onPinchCancelId, context_));
}

void RenderGestureListener::SetRemoteMessageCallback(const ClickCallback& callback)
{
    if (callback) {
        if (!clickRecognizer_) {
            clickRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>();
        }
        clickRecognizer_->SetRemoteMessage(callback);
    } else {
        LOGE("fail to set remote message callback due to callback is nullptr");
    }
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

void RenderGestureListener::SetOnDoubleClickCallback(const ClickCallback& callback)
{
    if (callback) {
        if (!doubleClickRecognizer_) {
            doubleClickRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>(GetContext(), 1, DOUBLE_CLICK);
        }
        doubleClickRecognizer_->SetOnClick(callback);
    } else {
        LOGE("fail to set double click callback due to callback is nullptr");
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

void RenderGestureListener::SetOnPinchStartCallback(const GestureEventFunc& onPinchStart)
{
    if (onPinchStart) {
        if (!pinchRecognizer_) {
            pinchRecognizer_ = AceType::MakeRefPtr<PinchRecognizer>(DEFAULT_PINCH_FINGER, DEFAULT_PINCH_DISTANCE);
        }
        pinchRecognizer_->SetOnActionStart(onPinchStart);
    } else {
        LOGE("fail to set pinch start callback due to callback is nullptr");
    }
}

void RenderGestureListener::SetOnPinchUpdateCallback(const GestureEventFunc& onPinchUpdate)
{
    if (onPinchUpdate) {
        if (!pinchRecognizer_) {
            pinchRecognizer_ = AceType::MakeRefPtr<PinchRecognizer>(DEFAULT_PINCH_FINGER, DEFAULT_PINCH_DISTANCE);
        }
        pinchRecognizer_->SetOnActionUpdate(onPinchUpdate);
    } else {
        LOGE("fail to set pinch update callback due to callback is nullptr");
    }
}

void RenderGestureListener::SetOnPinchEndCallback(const GestureEventFunc& onPinchEnd)
{
    if (onPinchEnd) {
        if (!pinchRecognizer_) {
            pinchRecognizer_ = AceType::MakeRefPtr<PinchRecognizer>(DEFAULT_PINCH_FINGER, DEFAULT_PINCH_DISTANCE);
        }
        pinchRecognizer_->SetOnActionEnd(onPinchEnd);
    } else {
        LOGE("fail to set pinch end callback due to callback is nullptr");
    }
}

void RenderGestureListener::SetOnPinchCancelCallback(const GestureEventFunc& onPinchCancel)
{
    if (onPinchCancel) {
        if (!pinchRecognizer_) {
            pinchRecognizer_ = AceType::MakeRefPtr<PinchRecognizer>(DEFAULT_PINCH_FINGER, DEFAULT_PINCH_DISTANCE);
        }
        pinchRecognizer_->SetOnActionCancel(onPinchCancel);
    } else {
        LOGE("fail to set pinch cancel callback due to callback is nullptr");
    }
}

void RenderGestureListener::UpdateTouchRect()
{
    const auto& children = GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        for (auto& rect : child->GetTouchRectList()) {
            // unified coordinate system
            Rect newRect = rect;
            newRect.SetOffset(rect.GetOffset() + GetPaintRect().GetOffset());
            touchRectList_.emplace_back(newRect);
        }
    }
}

} // namespace OHOS::Ace
