/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIDEO_CONTROLLER_BINDING_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIDEO_CONTROLLER_BINDING_H

#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/jsview/js_video_controller.h"

namespace OHOS::Ace::Framework {
class JSVideoControllerBinding : public JSVideoController {
public:
    JSVideoControllerBinding() = default;

    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSVideoController* controller);

    void Start(const JSCallbackInfo& args);
    void Pause(const JSCallbackInfo& args);
    void Stop(const JSCallbackInfo& args);
    void SetCurrentTime(const JSCallbackInfo& args);
    void RequestFullscreen(const JSCallbackInfo& args);
    void ExitFullscreen(const JSCallbackInfo& args);
    void Reset(const JSCallbackInfo& args);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSVideoControllerBinding);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIDEO_CONTROLLER_BINDING_H