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

#include "core/components/scene_viewer/scene_viewer_touch_handler.h"

namespace OHOS::Ace {

bool SceneViewerTouchHandler::HandleEvent(const TouchEvent& event)
{
    if (eventCallback_) {
        eventCallback_(CreateSceneTouchEvent(event));
    }

    switch (event.type) {
        case TouchType::MOVE: {
            touches_[event.id] = event;
            break;
        }
        case TouchType::DOWN: {
            touches_.emplace(event.id, event);
            break;
        }
        case TouchType::UP: {
            touches_.erase(event.id);
            break;
        }
        case TouchType::CANCEL: {
            touches_.erase(event.id);
            break;
        }
        default:
            LOGW("unknown touch type");
            break;
    }

    return false;
}

bool SceneViewerTouchHandler::DispatchEvent(const TouchEvent& event)
{
    // consume event.
    return true;
}

OHOS::Render3D::SceneViewerTouchEvent SceneViewerTouchHandler::CreateSceneTouchEvent(const TouchEvent& point) const
{
    OHOS::Render3D::SceneViewerTouchEvent event(point.id);

    event.SetEventType(point.type);
    event.SetGlobalLocation(point.GetOffset());
    event.SetLocalLocation(point.GetOffset() - coordinateOffset_);

    Offset deltaChange(0.0, 0.0);
    auto touch = touches_.find(point.id);
    if (touch != touches_.end()) {
        auto oldPoint = touch->second;
        deltaChange.SetX(point.x - oldPoint.x);
        deltaChange.SetY(point.y - oldPoint.y);
    }
    event.SetDeltaChange(std::move(deltaChange));
    return event;
}

} // namespace OHOS::Ace
