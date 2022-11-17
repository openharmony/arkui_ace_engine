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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_SCENE_VIEWER_TOUCH_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_SCENE_VIEWER_TOUCH_HANDLER_H

#include <functional>
#include <unordered_map>

#include "core/event/touch_event.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/scene_viewer_touch_event.h"

namespace OHOS::Ace {

using SceneViewerEventCallback = std::function<void(const OHOS::Render3D::SceneViewerTouchEvent&)>;

class SceneViewerTouchHandler : public TouchEventTarget {
    DECLARE_ACE_TYPE(SceneViewerTouchHandler, TouchEventTarget);
public:
    bool DispatchEvent(const TouchEvent& event) override;
    bool HandleEvent(const TouchEvent& event) override;

    void SetEventCallback(const SceneViewerEventCallback& eventCallback)
    {
        eventCallback_ = eventCallback;
    }

    void SetCoordinateOffset(const Offset& coordinateOffset)
    {
        coordinateOffset_ - coordinateOffset_;
    }

private:
    OHOS::Render3D::SceneViewerTouchEvent CreateSceneTouchEvent(const TouchEvent& point) const;

private:
    SceneViewerEventCallback eventCallback_;
    std::unordered_map<int32_t, TouchEvent> touches_;
    Offset coordinateOffset_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_SCENE_VIEWER_TOUCH_HANDLER_H
