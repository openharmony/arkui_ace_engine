/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef _NATIVE_RENDER_CONTEXT_H_
#define _NATIVE_RENDER_CONTEXT_H_

#include <chrono>
#include <functional>

#define NATIVE_RENDER_TAG ("NativeRenderTag")

enum class TouchInfoType : size_t {
    DOWN = 0,
    UP,
    MOVE,
    CANCEL,
    UNKNOWN,
};

namespace OHOS::Ace {
using TimeStamp = std::chrono::high_resolution_clock::time_point;

struct TouchInfo final {
    // The ID is used to identify the point of contact between the finger and the screen. Different fingers have
    // different ids.
    int32_t id = 0;
    float x = 0.0f;
    float y = 0.0f;
    TouchInfoType type = TouchInfoType::UNKNOWN;
    double size = 0.0;
    float force = 0.0f;
    int64_t deviceId = 0;
    TimeStamp time;
};

class NativeRenderContext {
public:
    NativeRenderContext() = default;
    virtual ~NativeRenderContext() {}

    // Set Native Window
    virtual void OnNativeWindowInit(void* context) = 0;

    // Init GLSE Context
    virtual void OnGLContextInit() = 0;

    // Surface lifecycle
    virtual void OnSurfaceCreated(int x, int y, int width, int height) = 0;

    virtual void OnSurfaceChanged(int x, int y, int width, int height) = 0;

    virtual void OnSurfaceDestroyed() = 0;

    virtual void OnRenderDoneCallbackCreated(std::function<void()> callback) = 0;

    virtual void DispatchTouchEvent(TouchInfo& event) = 0;
};
} // namespace OHOS::Ace

#endif // _NATIVE_RENDER_CONTEXT_H_
