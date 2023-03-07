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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_SAMPLES_TOUCH_EVENT_HANDLER_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_SAMPLES_TOUCH_EVENT_HANDLER_H

#include <mutex>

#ifndef ENABLE_ROSEN_BACKEND
#include "flutter/shell/platform/glfw/public/flutter_glfw.h"
#else
#include "glfw_render_context.h"
#endif

namespace OHOS::Ace::Platform {

class TouchEventHandler {
public:
#ifndef ENABLE_ROSEN_BACKEND
    using GlfwController = FlutterDesktopWindowControllerRef;
#else
    using GlfwController = std::shared_ptr<OHOS::Rosen::GlfwRenderContext>;
#endif
    static void InitialTouchEventCallback(const GlfwController &controller);
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_SAMPLES_TOUCH_EVENT_HANDLER_H
