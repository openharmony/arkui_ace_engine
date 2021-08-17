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

#ifndef FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_GESTURE_HANDLER_H
#define FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_GESTURE_HANDLER_H

#include "core/components/gesture_listener/gesture_listener_component.h"
#include "core/event/ace_event_handler.h"
#include "core/gestures/gesture_info.h"

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class JSGestureHandler : public virtual AceType {
    DECLARE_ACE_TYPE(JSGestureHandler, AceType);

public:
    JSGestureHandler() = default;
    ~JSGestureHandler() override = default;

    enum class JSGestureEvent { ACTION, START, UPDATE, END, CANCEL };

    static void JSBind(BindingTarget globalObj);

    RefPtr<Gesture> GetGesture()
    {
        return gesture_;
    }

protected:
    RefPtr<Gesture> gesture_;
}; // JSGestureHandler

class TapGestureHandler : public JSGestureHandler {
    DECLARE_ACE_TYPE(TapGestureHandler, JSGestureHandler);

public:
    TapGestureHandler(int32_t count, int32_t fingers);
    ~TapGestureHandler() override = default;

    static void ConstructorCallback(const JSCallbackInfo& args);
};

class LongPressGestureHandler : public JSGestureHandler {
    DECLARE_ACE_TYPE(LongPressGestureHandler, JSGestureHandler);

public:
    LongPressGestureHandler(int32_t fingers, bool repeat, int32_t duration);
    ~LongPressGestureHandler() override = default;

    static void ConstructorCallback(const JSCallbackInfo& args);
};

class PanGestureHandler : public JSGestureHandler {
    DECLARE_ACE_TYPE(PanGestureHandler, JSGestureHandler);

public:
    PanGestureHandler(int32_t fingers, Direction direction, double distance);
    ~PanGestureHandler() override = default;

    static void ConstructorCallback(const JSCallbackInfo& args);
};

class PinchGestureHandler : public JSGestureHandler {
    DECLARE_ACE_TYPE(PinchGestureHandler, JSGestureHandler);

public:
    PinchGestureHandler(int32_t fingers, double distance);
    ~PinchGestureHandler() override = default;

    static void ConstructorCallback(const JSCallbackInfo& args);
};

class RotationGestureHandler : public JSGestureHandler {
    DECLARE_ACE_TYPE(RotationGestureHandler, JSGestureHandler);

public:
    RotationGestureHandler(int32_t fingers, double angle);
    ~RotationGestureHandler() override = default;

    static void ConstructorCallback(const JSCallbackInfo& args);
};

class GestureGroupHandler : public JSGestureHandler {
    DECLARE_ACE_TYPE(GestureGroupHandler, JSGestureHandler);

public:
    GestureGroupHandler() = delete;
    GestureGroupHandler(GestureMode mode, std::vector<RefPtr<Gesture>>& gestures);
    ~GestureGroupHandler() override = default;

    static void ConstructorCallback(const JSCallbackInfo& args);
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_GESTURE_HANDLER_H
