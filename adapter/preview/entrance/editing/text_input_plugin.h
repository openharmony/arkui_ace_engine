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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_EDITING_TEXT_INPUT_PLUGIN_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_EDITING_TEXT_INPUT_PLUGIN_H

#include "flutter/shell/platform/glfw/keyboard_hook_handler.h"
#include "core/event/key_event.h"

namespace OHOS::Ace::Platform {

using KeyboardHookCallback = std::function<bool(const KeyEvent& keyEvent)>;
using CharHookCallback = std::function<bool(unsigned int code_point)>;

class TextInputPlugin : public flutter::KeyboardHookHandler {
public:
    TextInputPlugin() = default;
    ~TextInputPlugin() override = default;

    // A function for hooking into keyboard input.
    void KeyboardHook(GLFWwindow* window, int key, int scancode, int action, int mods) override;

    // A function for hooking into unicode code point input.
    void CharHook(GLFWwindow* window, unsigned int code_point) override;

    // Register the dispatch function of the keyboard event
    void RegisterKeyboardHookCallback(KeyboardHookCallback&& keyboardHookCallback);

    // Register the dispatch function of the input method event
    void RegisterCharHookCallback(CharHookCallback&& charHookCallback);

private:
    bool RecognizeKeyEvent(int key, int action, int mods);
    KeyEvent keyEvent_;
    CharHookCallback charHookCallback_;
    KeyboardHookCallback keyboardHookCallback_;
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_EDITING_TEXT_INPUT_PLUGIN_H
