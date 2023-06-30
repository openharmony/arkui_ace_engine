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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_SAMPLES_KEY_INPUT_HANDLER_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_SAMPLES_KEY_INPUT_HANDLER_H

#include "adapter/preview/external/multimodalinput/key_event.h"

#ifndef ENABLE_ROSEN_BACKEND
#include "flutter/shell/platform/glfw/keyboard_hook_handler.h"
#include "flutter/shell/platform/glfw/public/flutter_glfw.h"
#else
#include "GLFW/glfw3.h"
#include "glfw_render_context.h"
#endif

namespace OHOS::Ace::Platform {

#ifndef ENABLE_ROSEN_BACKEND
class KeyInputHandler : public flutter::KeyboardHookHandler {
public:
    KeyInputHandler() = default;
    ~KeyInputHandler() override = default;

    static void InitialTextInputCallback(FlutterDesktopWindowControllerRef controller);
    // A function for hooking into keyboard input.
    void KeyboardHook(GLFWwindow* window, int key, int scancode, int action, int mods) override;

    // A function for hooking into unicode code point input.
    void CharHook(GLFWwindow* window, unsigned int code_point) override;

private:
    bool RecognizeKeyEvent(int key, int action, int mods);
    static std::shared_ptr<OHOS::MMI::KeyEvent> keyEvent_;
};
#else
class KeyInputHandler {
public:
    static void InitialTextInputCallback(const std::shared_ptr<OHOS::Rosen::GlfwRenderContext>& controller);
    static void KeyboardHook(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void CharHook(GLFWwindow* window, unsigned int code_point);

private:
    static bool RecognizeKeyEvent(int key, int action, int mods);
    static std::shared_ptr<OHOS::MMI::KeyEvent> keyEvent_;
};
#endif

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_SAMPLES_KEY_INPUT_HANDLER_H
