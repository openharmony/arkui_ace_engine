/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_SAMPLES_EVENT_ADAPTER_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_SAMPLES_EVENT_ADAPTER_H

#include <mutex>

#include "glfw_render_context.h"

#include "adapter/preview/external/multimodalinput/key_event.h"
#include "adapter/preview/external/multimodalinput/pointer_event.h"
#include "frameworks/base/utils/singleton.h"

using OHOS::MMI::KeyAction;
using OHOS::MMI::KeyCode;
using OHOS::MMI::KeyEvent;
using OHOS::MMI::PointerEvent;
using OHOS::MMI::SourceTool;
using OHOS::MMI::SourceType;
using OHOS::MMI::TouchPoint;
using OHOS::MMI::TouchType;
using OHOS::Rosen::GlfwRenderContext;

using MMIKeyEventCallback = std::function<void(const std::shared_ptr<KeyEvent>&)>;
using MMIPointerEventCallback = std::function<void(const std::shared_ptr<PointerEvent>&)>;
using InspectorCallback = std::function<void(void)>;

namespace OHOS::Ace::Sample {

class EventAdapter : public Singleton<EventAdapter> {
    DECLARE_SINGLETON(EventAdapter);

public:
    void Initialize(std::shared_ptr<GlfwRenderContext>& glfwRenderContext);
    bool RecognizeKeyEvent(int key, int action, int mods);
    void RecognizePointerEvent(const TouchType type);
    void RegisterKeyEventCallback(MMIKeyEventCallback&& callback);
    void RegisterPointerEventCallback(MMIPointerEventCallback&& callback);
    // Register the callback for inspector
    void RegisterInspectorCallback(InspectorCallback&& callback);
    // This function is used to perform specific operations, by recognize some special shortcut keys.
    bool RunSpecialOperations(int key, int action, int mods);

private:
    std::shared_ptr<KeyEvent> keyEvent_;
    std::shared_ptr<PointerEvent> pointerEvent_;
    MMIKeyEventCallback keyEventCallback_;
    MMIPointerEventCallback pointerEventCallback_;
    InspectorCallback inspectorCallback_;

    // for mouse event
    std::mutex mouseMutex_;
    bool isMousePressed_ = false;
    double posX_ = 0;
    double posY_ = 0;
};

} // namespace OHOS::Ace::Sample

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_SAMPLES_EVENT_ADAPTER_H
