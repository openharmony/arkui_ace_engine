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

bool ModelTouchHandler::HandleTouchEvent(const TouchEventInfo& info)
{
    auto event = CreateTouchEvent(info);
    auto sceneEvent = CreateSceneTouchEvent(event);
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
    } else {
        CHECK_NULL_RETURN(cameraEventCallback_, false);
        cameraEventCallback_(sceneEvent);
        return true;
    }
    return false;
}

OHOS::Ace::TouchEvent ModelTouchHandler::CreateTouchEvent(const TouchEventInfo& info)
{
    auto point = info.GetChangedTouches().front();
    return {
        .id = point.GetFingerId(),
        .x = point.GetLocalLocation().GetX(),
        .y = point.GetLocalLocation().GetY(),
        .screenX = point.GetGlobalLocation().GetX(),
        .screenY = point.GetGlobalLocation().GetY(),
        .type = point.GetTouchType()
    };
}

OHOS::Render3D::SceneViewerTouchEvent ModelTouchHandler::CreateSceneTouchEvent(const TouchEvent& point) const
{
    OHOS::Render3D::SceneViewerTouchEvent event(point.id);

    event.SetEventType(point.type);
    event.SetGlobalLocation(point.GetScreenOffset());
    event.SetLocalLocation(point.GetOffset());

    Offset deltaChange(0.0, 0.0);
    auto touch = touches_.find(point.id);
    if (touch != touches_.end()) {
        auto oldPoint = touch->second;
        deltaChange.SetX(point.screenX - oldPoint.screenX);
        deltaChange.SetY(point.screenY - oldPoint.screenY);
    }
    event.SetDeltaChange(std::move(deltaChange));
    return event;
}

} // namespace OHOS::Ace
