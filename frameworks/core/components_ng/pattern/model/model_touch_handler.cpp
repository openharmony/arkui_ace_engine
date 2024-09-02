/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/model/model_touch_handler.h"

namespace OHOS::Ace::NG {

bool ModelTouchHandler::HandleTouchEvent(const TouchEventInfo& info, uint32_t viewWidth, uint32_t viewHeight)
{
    auto event = CreateTouchEvent(info);
    auto sceneEvent = CreateSceneTouchEvent(event, viewWidth, viewHeight);
    switch (event.type) {
        case TouchType::MOVE: {
            touches_[event.id] = event;
            break;
        }
        case TouchType::DOWN: {
            isClicked_ = true;
            touchCount_++;
            touches_.emplace(event.id, event);
            break;
        }
        case TouchType::UP: {
            touchCount_--;
            touches_.erase(event.id);
            break;
        }
        case TouchType::CANCEL: {
            touchCount_--;
            touches_.erase(event.id);
            break;
        }
        default:
            LOGW("unknown touch type");
            break;
    }

    if (!isHandleCameraMove_) {
        if (isClicked_ && touchCount_ == 0) {
            CHECK_NULL_RETURN(clickEventCallback_, false);
            clickEventCallback_(sceneEvent);
        }
        isClicked_ = touchCount_ > 0;
        return true;
    }

    CHECK_NULL_RETURN(cameraEventCallback_, false);
    cameraEventCallback_(sceneEvent);
    return true;
}

TouchEvent ModelTouchHandler::CreateTouchEvent(const TouchEventInfo& info) const
{
    auto point = info.GetChangedTouches().front();
    return TouchEvent {}
        .SetId(point.GetFingerId())
        .SetX(point.GetLocalLocation().GetX())
        .SetY(point.GetLocalLocation().GetY())
        .SetScreenX(point.GetGlobalLocation().GetX())
        .SetScreenY(point.GetGlobalLocation().GetY())
        .SetType(point.GetTouchType());
}

Render3D::PointerEvent ModelTouchHandler::CreateSceneTouchEvent(const TouchEvent& point,
    uint32_t viewWidth, uint32_t viewHeight) const
{
    if (viewWidth == 0U || viewHeight == 0U) {
        LOGE("CreateSceneTouchEvent error view width and height %d x %d", viewWidth, viewHeight);
        return {};
    }
    Render3D::PointerEvent pointerEvent;
    pointerEvent.buttonIndex_ = -1;

    pointerEvent.pointerId_ = point.id;
    pointerEvent.x_ = point.GetOffset().GetX() / viewWidth;
    pointerEvent.y_ = point.GetOffset().GetY() / viewHeight;

    Offset deltaChange(0.0, 0.0);
    auto touch = touches_.find(point.id);
    if (touch != touches_.end()) {
        auto oldPoint = touch->second;
        deltaChange.SetX(point.screenX - oldPoint.screenX);
        deltaChange.SetY(point.screenY - oldPoint.screenY);
    }

    pointerEvent.deltaX_ = deltaChange.GetX() / viewWidth;
    pointerEvent.deltaY_ = deltaChange.GetY() / viewHeight;
    switch (point.type) {
        case TouchType::DOWN:
            pointerEvent.eventType_ = Render3D::PointerEventType::PRESSED;
            break;
        case TouchType::UP:
            pointerEvent.eventType_ = Render3D::PointerEventType::RELEASED;
            break;
        case Ace::TouchType::MOVE:
            pointerEvent.eventType_ = Render3D::PointerEventType::MOVED;
            break;
        case Ace::TouchType::CANCEL:
            pointerEvent.eventType_ = Render3D::PointerEventType::CANCELLED;
            break;
        case TouchType::PULL_DOWN:
        case TouchType::PULL_UP:
        case TouchType::PULL_MOVE:
        case TouchType::PULL_IN_WINDOW:
        case TouchType::PULL_OUT_WINDOW:
        case TouchType::HOVER_ENTER:
        case TouchType::HOVER_MOVE:
        case TouchType::HOVER_EXIT:
        case TouchType::HOVER_CANCEL:
        case TouchType::PROXIMITY_IN:
        case TouchType::PROXIMITY_OUT:
        case TouchType::UNKNOWN:
            break;
    }

    return pointerEvent;
}
} // namespace OHOS::Ace::NG
