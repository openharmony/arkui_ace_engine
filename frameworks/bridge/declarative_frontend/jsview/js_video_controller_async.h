/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIDEO_CONTROLLER_ASYNC_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIDEO_CONTROLLER_ASYNC_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "core/components_ng/pattern/video/video_controller_async.h"

namespace OHOS::Ace::Framework {

class JSVideoControllerAsync : public Referenced {
public:
    JSVideoControllerAsync() = default;
    ~JSVideoControllerAsync() override = default;

    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSVideoControllerAsync* controller);

    void StartAsync(const JSCallbackInfo& args);
    void PauseAsync(const JSCallbackInfo& args);
    void StopAsync(const JSCallbackInfo& args);
    void ResetAsync(const JSCallbackInfo& args);

    void SetCurrentTime(const JSCallbackInfo& args);
    void RequestFullscreen(const JSCallbackInfo& args);
    void ExitFullscreen(const JSCallbackInfo& args);

    RefPtr<VideoControllerAsync> GetController() const
    {
        return videoControllerAsync_;
    }

    void SetController(const RefPtr<VideoControllerAsync>& videoControllerAsync)
    {
        videoControllerAsync_ = videoControllerAsync;
    }

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

private:
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    RefPtr<VideoControllerAsync> videoControllerAsync_;
    ACE_DISALLOW_COPY_AND_MOVE(JSVideoControllerAsync);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIDEO_CONTROLLER_ASYNC_H
