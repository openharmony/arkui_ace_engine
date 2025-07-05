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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_ZOOM_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_ZOOM_CONTROLLER_H

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/gestures/pinch_gesture.h"

namespace OHOS::Ace::NG {
class ScrollPattern;

/**
 * @brief Controller for free scrolling behavior. It manages related gestures and animations.
 *
 */
class ZoomController final : public AceType {
    DECLARE_ACE_TYPE(ZoomController, AceType);
    ACE_DISALLOW_COPY_AND_MOVE(ZoomController);

public:
    explicit ZoomController(ScrollPattern& pattern);
    ~ZoomController() final;

private:
    void InitializePinchGesture();
    void DeinitializePinchGesture();
    void HandleZoomStart(GestureEvent& info);
    void HandleZoomUpdate(GestureEvent& info);
    void HandleZoomEnd(GestureEvent& info);
    OffsetF GetCenterPoint(GestureEvent& info);
    void UpdateOffset(float scale, float prevScale, OffsetF centerOffset);

    ScrollPattern& pattern_;
    RefPtr<PinchGesture> pinchGesture_;
    float zoomScaleStart_ = 1.0f;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_ZOOM_CONTROLLER_H
