/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "adapter/preview/entrance/samples/event_adapter.h"

#include <GLFW/glfw3.h>
#include <map>
#include <memory>

#include "base/utils/utils.h"
#include "frameworks/base/log/log.h"

namespace OHOS::Ace::Sample {

namespace {
const std::map<int, KeyAction> ACTION_MAP = {
    { GLFW_RELEASE, KeyAction::UP },
    { GLFW_PRESS, KeyAction::DOWN },
    { GLFW_REPEAT, KeyAction::LONG_PRESS },
};

const std::map<int, KeyCode> CODE_MAP = {
    { GLFW_KEY_BACKSPACE, KeyCode::KEY_FORWARD_DEL },
    { GLFW_KEY_DELETE, KeyCode::KEY_DEL },
    { GLFW_KEY_ESCAPE, KeyCode::KEY_ESCAPE },
    { GLFW_KEY_ENTER, KeyCode::KEY_ENTER },
    { GLFW_KEY_CAPS_LOCK, KeyCode::KEY_CAPS_LOCK },
    { GLFW_KEY_UP, KeyCode::KEY_DPAD_UP },
    { GLFW_KEY_DOWN, KeyCode::KEY_DPAD_DOWN },
    { GLFW_KEY_LEFT, KeyCode::KEY_DPAD_LEFT },
    { GLFW_KEY_RIGHT, KeyCode::KEY_DPAD_RIGHT },
    { GLFW_KEY_GRAVE_ACCENT, KeyCode::KEY_GRAVE },
    { GLFW_KEY_MINUS, KeyCode::KEY_MINUS },
    { GLFW_KEY_EQUAL, KeyCode::KEY_EQUALS },
    { GLFW_KEY_TAB, KeyCode::KEY_TAB },
    { GLFW_KEY_LEFT_BRACKET, KeyCode::KEY_LEFT_BRACKET },
    { GLFW_KEY_RIGHT_BRACKET, KeyCode::KEY_RIGHT_BRACKET },
    { GLFW_KEY_BACKSLASH, KeyCode::KEY_BACKSLASH },
    { GLFW_KEY_SEMICOLON, KeyCode::KEY_SEMICOLON },
    { GLFW_KEY_APOSTROPHE, KeyCode::KEY_APOSTROPHE },
    { GLFW_KEY_COMMA, KeyCode::KEY_COMMA },
    { GLFW_KEY_PERIOD, KeyCode::KEY_PERIOD },
    { GLFW_KEY_SLASH, KeyCode::KEY_SLASH },
    { GLFW_KEY_SPACE, KeyCode::KEY_SPACE },
    { GLFW_KEY_KP_DIVIDE, KeyCode::KEY_NUMPAD_DIVIDE },
    { GLFW_KEY_KP_MULTIPLY, KeyCode::KEY_NUMPAD_MULTIPLY },
    { GLFW_KEY_KP_SUBTRACT, KeyCode::KEY_NUMPAD_SUBTRACT },
    { GLFW_KEY_KP_ADD, KeyCode::KEY_NUMPAD_ADD },
    { GLFW_KEY_KP_ENTER, KeyCode::KEY_NUMPAD_ENTER },
    { GLFW_KEY_KP_EQUAL, KeyCode::KEY_NUMPAD_EQUALS },
    { GLFW_KEY_NUM_LOCK, KeyCode::KEY_NUM_LOCK },
};
} // namespace

EventAdapter::EventAdapter()
{
    keyEvent_ = std::make_shared<KeyEvent>();
    pointerEvent_ = std::make_shared<PointerEvent>();
}

EventAdapter::~EventAdapter() = default;

void EventAdapter::Initialize(std::shared_ptr<GlfwRenderContext>& glfwRenderContext)
{
    // keyboard callback
    auto&& keyboardCbk = [this](int key, int scancode, int action, int mods) {
        if (RunSpecialOperations(key, action, mods)) {
            return;
        }
        if (keyEventCallback_ && RecognizeKeyEvent(key, action, mods)) {
            keyEventCallback_(keyEvent_);
        } else {
            LOGW("Unrecognized key type.");
        }
    };
    glfwRenderContext->OnKey(keyboardCbk);

    // mouse button callback
    auto&& mouseButtonCbk = [this](int button, bool pressed, int mods) {
        {
            std::lock_guard lock(mouseMutex_);
            isMousePressed_ = pressed;
        }
        if (pointerEventCallback_) {
            RecognizePointerEvent(pressed ? TouchType::DOWN : TouchType::UP);
            pointerEventCallback_(pointerEvent_);
        }
    };
    glfwRenderContext->OnMouseButton(mouseButtonCbk);

    // cursor position callback
    auto&& cursorPosCbk = [this](double x, double y) {
        {
            std::lock_guard lock(mouseMutex_);
            posX_ = x;
            posY_ = y;
        }
        if (isMousePressed_ && pointerEventCallback_) {
            RecognizePointerEvent(TouchType::MOVE);
            pointerEventCallback_(pointerEvent_);
        }
    };
    glfwRenderContext->OnCursorPos(cursorPosCbk);
}

void EventAdapter::RegisterKeyEventCallback(MMIKeyEventCallback&& callback)
{
    keyEventCallback_ = std::move(callback);
}

void EventAdapter::RegisterPointerEventCallback(MMIPointerEventCallback&& callback)
{
    pointerEventCallback_ = std::move(callback);
}

void EventAdapter::RegisterInspectorCallback(InspectorCallback&& callback)
{
    inspectorCallback_ = std::move(callback);
}

bool EventAdapter::RecognizeKeyEvent(int key, int action, int mods)
{
    auto iterAction = ACTION_MAP.find(action);
    if (iterAction == ACTION_MAP.end()) {
        return false;
    }
    keyEvent_->action = iterAction->second;

    keyEvent_->pressedCodes.clear();
    if (mods & GLFW_MOD_CONTROL) {
        keyEvent_->pressedCodes.push_back(KeyCode::KEY_CTRL_LEFT);
    }
    if (mods & GLFW_MOD_SUPER) {
        keyEvent_->pressedCodes.push_back(KeyCode::KEY_META_LEFT);
    }
    if (mods & GLFW_MOD_SHIFT) {
        keyEvent_->pressedCodes.push_back(KeyCode::KEY_SHIFT_LEFT);
    }
    if (mods & GLFW_MOD_ALT) {
        keyEvent_->pressedCodes.push_back(KeyCode::KEY_ALT_LEFT);
    }

    auto iterCode = CODE_MAP.find(key);
    if (iterCode == CODE_MAP.end() && !(key >= GLFW_KEY_A && key <= GLFW_KEY_Z) &&
        !(key >= GLFW_KEY_0 && key <= GLFW_KEY_9) && !(key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_9)) {
        return false;
    }
    if (iterCode != CODE_MAP.end()) {
        keyEvent_->code = iterCode->second;
    }
    if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
        keyEvent_->code = static_cast<KeyCode>(static_cast<int32_t>(KeyCode::KEY_A) + key - GLFW_KEY_A);
    }
    if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9) {
        keyEvent_->code = static_cast<KeyCode>(static_cast<int32_t>(KeyCode::KEY_0) + key - GLFW_KEY_0);
    }
    if (key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_9) {
        keyEvent_->code = static_cast<KeyCode>(static_cast<int32_t>(KeyCode::KEY_0) + key - GLFW_KEY_KP_0);
    }
    keyEvent_->key = "Test";
    keyEvent_->pressedCodes.push_back(keyEvent_->code);

    return true;
}

void EventAdapter::RecognizePointerEvent(const TouchType type)
{
    std::lock_guard lock(mouseMutex_);
    pointerEvent_->id = 1;
    pointerEvent_->x = posX_;
    pointerEvent_->y = posY_;
    pointerEvent_->screenX = 0;
    pointerEvent_->screenY = 0;
    pointerEvent_->type = type;
    pointerEvent_->time = std::chrono::high_resolution_clock::now();
    pointerEvent_->size = sizeof(PointerEvent);
    pointerEvent_->force = 0;
    pointerEvent_->deviceId = 0;
    pointerEvent_->sourceType = static_cast<int32_t>(OHOS::MMI::SourceType::TOUCH);
    pointerEvent_->pointers = {};
}

bool EventAdapter::RunSpecialOperations(int key, int action, int mods)
{
    // Add specific operations which driven by some special shortcut keys.
    if (inspectorCallback_ && (action == GLFW_PRESS) && (mods & GLFW_MOD_CONTROL) && (key == GLFW_KEY_I)) {
        inspectorCallback_();
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::Sample
