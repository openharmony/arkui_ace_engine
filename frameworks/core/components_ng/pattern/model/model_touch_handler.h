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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_TOUCH_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_TOUCH_HANDLER_H

#include <functional>
#include <unordered_map>
#ifdef ARKUI_CAPI_UNITTEST
#include "test/unittest/capi/stubs/mock_custom_render_descriptor.h"
#else
#include "data_type/pointer_event.h"
#endif // ARKUI_CAPI_UNITTEST
#include "base/memory/referenced.h"
#include "core/components_ng/event/touch_event.h"

namespace OHOS::Ace::NG {

using ModelEventCallback = std::function<void(const Render3D::PointerEvent&)>;

class ModelTouchHandler : public Referenced {
public:
    explicit ModelTouchHandler() {}
    ~ModelTouchHandler() override = default;

    bool HandleTouchEvent(const TouchEventInfo& info, uint32_t viewWidth, uint32_t viewHeight);

    void SetCameraEventCallback(const ModelEventCallback& eventCallback)
    {
        cameraEventCallback_ = std::move(eventCallback);
    }

    void SetClickEventCallback(const ModelEventCallback& eventCallback)
    {
        clickEventCallback_ = std::move(eventCallback);
    }

    void SetCoordinateOffset(const Offset& coordinateOffset)
    {
        coordinateOffset_ = coordinateOffset;
    }

    void HandleCameraEvents(bool handle)
    {
        isHandleCameraMove_ = handle;
    }

private:
    Render3D::PointerEvent CreateSceneTouchEvent(const TouchEvent& event, uint32_t viewWidth,
        uint32_t viewHeight) const;
    TouchEvent CreateTouchEvent(const TouchEventInfo& info) const;
    ModelEventCallback cameraEventCallback_;
    ModelEventCallback clickEventCallback_;
    std::unordered_map<int32_t, TouchEvent> touches_;
    Offset coordinateOffset_;

    bool isClicked_ = false;
    int32_t touchCount_ = 0;
    bool isHandleCameraMove_ = true;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_TOUCH_HANDLER_H
