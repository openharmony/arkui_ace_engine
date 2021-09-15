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

#include "frameworks/bridge/declarative_frontend/jsview/js_gesture_handler.h"

#include "frameworks/core/gestures/gesture_group.h"
#include "frameworks/core/gestures/long_press_gesture.h"
#include "frameworks/core/gestures/pan_gesture.h"
#include "frameworks/core/gestures/pinch_gesture.h"
#include "frameworks/core/gestures/rotation_gesture.h"
#include "frameworks/core/gestures/tap_gesture.h"

namespace OHOS::Ace::Framework {

namespace {
constexpr int32_t DEFAULT_TAP_FINGER = 1;
constexpr int32_t DEFAULT_TAP_COUNT = 1;
constexpr int32_t DEFAULT_LONG_PRESS_FINGER = 1;
constexpr int32_t DEFAULT_LONG_PRESS_DURATION = 500;
constexpr int32_t DEFAULT_PINCH_FINGER = 2;
constexpr double DEFAULT_PINCH_DISTANCE = 10.0;
constexpr int32_t DEFAULT_PAN_FINGER = 1;
constexpr double DEFAULT_PAN_DISTANCE = 15.0;
constexpr int32_t DEFAULT_ROTATION_FINGER = 2;
constexpr double DEFAULT_ROTATION_ANGLE = 1.0;
} // namespace

TapGestureHandler::TapGestureHandler(int32_t count, int32_t fingers)
{
    gesture_ = AceType::MakeRefPtr<OHOS::Ace::TapGesture>(count, fingers);
}

void TapGestureHandler::ConstructorCallback(const JSCallbackInfo& args)
{
    LOGD("TapGestureHandler ConstructorCallback");
    int32_t countNum = DEFAULT_TAP_COUNT;
    int32_t fingersNum = DEFAULT_TAP_FINGER;
    if (args.Length() > 0 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> count = obj->GetProperty("count");
        JSRef<JSVal> fingers = obj->GetProperty("fingers");

        if (count->IsNumber()) {
            int32_t countNumber = count->ToNumber<int32_t>();
            countNum = countNumber <= DEFAULT_TAP_COUNT ? DEFAULT_TAP_COUNT : countNumber;
        }

        if (fingers->IsNumber()) {
            int32_t fingersNumber = fingers->ToNumber<int32_t>();
            fingersNum = fingersNumber <= DEFAULT_TAP_FINGER ? DEFAULT_TAP_FINGER : fingersNumber;
        }
    }

    auto instance = new TapGestureHandler(countNum, fingersNum);
    args.SetReturnValue(instance);
}

LongPressGestureHandler::LongPressGestureHandler(int32_t fingers, bool repeat, int32_t duration)
{
    gesture_ = AceType::MakeRefPtr<OHOS::Ace::LongPressGesture>(fingers, repeat, duration);
}

void LongPressGestureHandler::ConstructorCallback(const JSCallbackInfo& args)
{
    LOGD("LongPressGestureHandler ConstructorCallback");

    int32_t fingersNum = DEFAULT_LONG_PRESS_FINGER;
    bool repeatResult = false;
    int32_t durationNum = DEFAULT_LONG_PRESS_DURATION;
    if (args.Length() > 0 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> fingers = obj->GetProperty("fingers");
        JSRef<JSVal> repeat = obj->GetProperty("repeat");
        JSRef<JSVal> duration = obj->GetProperty("duration");

        if (fingers->IsNumber()) {
            int32_t fingersNumber = fingers->ToNumber<int32_t>();
            fingersNum = fingersNumber <= DEFAULT_LONG_PRESS_FINGER ? DEFAULT_LONG_PRESS_FINGER : fingersNumber;
        }

        if (repeat->IsBoolean()) {
            repeatResult = repeat->ToBoolean();
        }

        if (duration->IsNumber()) {
            int32_t durationNumber = duration->ToNumber<int32_t>();
            durationNum = durationNumber <= 0 ? DEFAULT_LONG_PRESS_DURATION : durationNumber;
        }
    }

    auto instance = new LongPressGestureHandler(fingersNum, repeatResult, durationNum);
    args.SetReturnValue(instance);
}

PinchGestureHandler::PinchGestureHandler(int32_t fingers, double distance)
{
    gesture_ = AceType::MakeRefPtr<OHOS::Ace::PinchGesture>(fingers, distance);
}

void PinchGestureHandler::ConstructorCallback(const JSCallbackInfo& args)
{
    LOGD("PinchGestureHandler ConstructorCallback");

    int32_t fingersNum = DEFAULT_PINCH_FINGER;
    double distanceNum = DEFAULT_PINCH_DISTANCE;
    if (args.Length() > 0 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> fingers = obj->GetProperty("fingers");
        JSRef<JSVal> distance = obj->GetProperty("distance");

        if (fingers->IsNumber()) {
            int32_t fingersNumber = fingers->ToNumber<int32_t>();
            fingersNum = fingersNumber <= DEFAULT_PINCH_FINGER ? DEFAULT_PINCH_FINGER : fingersNumber;
        }
        if (distance->IsNumber()) {
            double distanceNumber = distance->ToNumber<double>();
            distanceNum = LessNotEqual(distanceNumber, 0.0) ? DEFAULT_PINCH_DISTANCE : distanceNumber;
        }
    }

    auto instance = new PinchGestureHandler(fingersNum, distanceNum);
    args.SetReturnValue(instance);
}

PanGestureHandler::PanGestureHandler(int32_t fingers, Direction direction, double distance)
{
    gesture_ = AceType::MakeRefPtr<OHOS::Ace::PanGesture>(fingers, direction, distance);
}

void PanGestureHandler::ConstructorCallback(const JSCallbackInfo& args)
{
    LOGD("PanGestureHandler ConstructorCallback");

    int32_t fingersNum = DEFAULT_PAN_FINGER;
    double distanceNum = DEFAULT_PAN_DISTANCE;
    Direction direction = Direction::ALL;
    if (args.Length() > 0 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> fingers = obj->GetProperty("fingers");
        JSRef<JSVal> distance = obj->GetProperty("distance");
        JSRef<JSVal> directionNum = obj->GetProperty("direction");

        if (fingers->IsNumber()) {
            int32_t fingersNumber = fingers->ToNumber<int32_t>();
            fingersNum = fingersNumber <= DEFAULT_PAN_FINGER ? DEFAULT_PAN_FINGER : fingersNumber;
        }

        if (distance->IsNumber()) {
            double distanceNumber = distance->ToNumber<double>();
            distanceNum = LessNotEqual(distanceNumber, 0.0) ? DEFAULT_PAN_DISTANCE : distanceNumber;
        }

        if (directionNum->IsNumber()) {
            int32_t directNum = directionNum->ToNumber<int32_t>();
            if (directNum > static_cast<int32_t>(Direction::BEGIN) &&
                directNum < static_cast<int32_t>(Direction::END)) {
                direction = static_cast<Direction>(directNum);
            }
        }
    }

    auto instance = new PanGestureHandler(fingersNum, direction, distanceNum);
    args.SetReturnValue(instance);
}

RotationGestureHandler::RotationGestureHandler(int32_t fingers, double angle)
{
    gesture_ = AceType::MakeRefPtr<OHOS::Ace::RotationGesture>(fingers, angle);
}

void RotationGestureHandler::ConstructorCallback(const JSCallbackInfo& args)
{
    LOGD("RotationGestureHandler ConstructorCallback");

    double angleNum = DEFAULT_ROTATION_ANGLE;
    int32_t fingersNum = DEFAULT_ROTATION_FINGER;
    if (args.Length() > 0 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> fingers = obj->GetProperty("fingers");
        JSRef<JSVal> angle = obj->GetProperty("angle");

        if (fingers->IsNumber()) {
            int32_t fingersNumber = fingers->ToNumber<int32_t>();
            fingersNum = fingersNumber <= DEFAULT_ROTATION_FINGER ? DEFAULT_ROTATION_FINGER : fingersNumber;
        }

        if (angle->IsNumber()) {
            double angleNumber = angle->ToNumber<double>();
            angleNum = LessNotEqual(angleNumber, 0.0) ? DEFAULT_ROTATION_ANGLE : angleNumber;
        }
    }

    auto instance = new RotationGestureHandler(fingersNum, angleNum);
    args.SetReturnValue(instance);
}

GestureGroupHandler::GestureGroupHandler(GestureMode mode, std::vector<RefPtr<Gesture>>& gestures)
{
    gesture_ = AceType::MakeRefPtr<OHOS::Ace::GestureGroup>(mode, gestures);
}

void GestureGroupHandler::ConstructorCallback(const JSCallbackInfo& args)
{
    if (args.Length() < 2) {
        JSException::Throw("%s", "Gesture group parameters must have gesture mode and sub gestures.");
        return;
    }

    if (!args[0]->IsNumber()) {
        JSException::Throw("%s", "Gesture group first parameter is not gesture mode.");
        return;
    }

    GestureMode mode = GestureMode::Sequence;
    int32_t modeInt = args[0]->ToNumber<int32_t>();
    if (modeInt > static_cast<int32_t>(GestureMode::Begin) && modeInt < static_cast<int32_t>(GestureMode::End)) {
        mode = static_cast<GestureMode>(modeInt);
    }

    std::vector<RefPtr<Gesture>> subGestures;
    for (int i = 1; i < args.Length(); i++) {
        if (!args[i]->IsObject()) {
            LOGW("Unsupported gesture group child. Skipping.");
            continue;
        }

        JSGestureHandler* handler = JSRef<JSObject>::Cast(args[i])->Unwrap<JSGestureHandler>();
        if (handler && handler->GetGesture()) {
            subGestures.emplace_back(handler->GetGesture());
        }
    }

    if (subGestures.empty()) {
        JSException::Throw("%s", "Cannot parse sub gestures in gesture group.");
        return;
    }

    auto instance = new GestureGroupHandler(mode, subGestures);
    args.SetReturnValue(instance);
}

#ifdef USE_V8_ENGINE
void JSGestureHandler::JsHandlerOnGestureEvent(JSGestureEvent action, const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ACE_DCHECK(gesture_);

    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        args.GetReturnValue().Set(args.This());
        return;
    }

    v8::Local<v8::Function> jsFunction = v8::Local<v8::Function>::Cast(args[0]);
    RefPtr<V8GestureFunction> handlerFunc = AceType::MakeRefPtr<V8GestureFunction>(jsFunction);

    if (action == JSGestureEvent::CANCEL) {
        auto onActionCancelFunc = [func = std::move(handlerFunc)]() { func->execute(); };
        gesture_->SetOnActionCancelId(onActionCancelFunc);
        args.GetReturnValue().Set(args.This());
        return;
    }

    auto onActionFunc = [func = std::move(handlerFunc)](const GestureEvent& info) { func->execute(info); };

    switch (action) {
        case JSGestureEvent::ACTION:
            gesture_->SetOnActionId(onActionFunc);
            break;
        case JSGestureEvent::START:
            gesture_->SetOnActionStartId(onActionFunc);
            break;
        case JSGestureEvent::UPDATE:
            gesture_->SetOnActionUpdateId(onActionFunc);
            break;
        case JSGestureEvent::END:
            gesture_->SetOnActionEndId(onActionFunc);
            break;
        default:
            LOGW("Unknown gesture action %{public}d", action);
            break;
    }

    args.GetReturnValue().Set(args.This());
}

void JSGestureHandler::JsHandlerOnAction(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSGestureHandler::JsHandlerOnGestureEvent(JSGestureEvent::ACTION, args);
}
void JSGestureHandler::JsHandlerOnActionStart(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSGestureHandler::JsHandlerOnGestureEvent(JSGestureEvent::START, args);
}
void JSGestureHandler::JsHandlerOnActionUpdate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSGestureHandler::JsHandlerOnGestureEvent(JSGestureEvent::UPDATE, args);
}
void JSGestureHandler::JsHandlerOnActionEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSGestureHandler::JsHandlerOnGestureEvent(JSGestureEvent::END, args);
}
void JSGestureHandler::JsHandlerOnActionCancel(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    JSGestureHandler::JsHandlerOnGestureEvent(JSGestureEvent::CANCEL, args);
}
#endif

void JSGestureHandler::JSBind(BindingTarget globalObj)
{
    JSClass<JSGestureHandler>::Declare("AbstractGesture");
    JSClass<JSGestureHandler>::Bind(globalObj);

    JSClass<TapGestureHandler>::Declare("TapGesture");
    JSClass<TapGestureHandler>::Inherit<JSGestureHandler>();
    JSClass<JSGestureHandler>::CustomMethod("onAction", &JSGestureHandler::JsHandlerOnAction);
    JSClass<TapGestureHandler>::Bind(globalObj, TapGestureHandler::ConstructorCallback);

    JSClass<LongPressGestureHandler>::Declare("LongPressGesture");
    JSClass<LongPressGestureHandler>::Inherit<JSGestureHandler>();
    JSClass<LongPressGestureHandler>::CustomMethod("onAction", &JSGestureHandler::JsHandlerOnAction);
    JSClass<LongPressGestureHandler>::CustomMethod("onActionEnd", &JSGestureHandler::JsHandlerOnActionEnd);
    JSClass<LongPressGestureHandler>::CustomMethod("onActionCancel", &JSGestureHandler::JsHandlerOnActionCancel);
    JSClass<LongPressGestureHandler>::Bind(globalObj, LongPressGestureHandler::ConstructorCallback);

    JSClass<PanGestureHandler>::Declare("PanGesture");
    JSClass<PanGestureHandler>::Inherit<JSGestureHandler>();
    JSClass<PanGestureHandler>::CustomMethod("onActionStart", &JSGestureHandler::JsHandlerOnActionStart);
    JSClass<PanGestureHandler>::CustomMethod("onActionUpdate", &JSGestureHandler::JsHandlerOnActionUpdate);
    JSClass<PanGestureHandler>::CustomMethod("onActionEnd", &JSGestureHandler::JsHandlerOnActionEnd);
    JSClass<PanGestureHandler>::CustomMethod("onActionCancel", &JSGestureHandler::JsHandlerOnActionCancel);
    JSClass<PanGestureHandler>::Bind(globalObj, PanGestureHandler::ConstructorCallback);

    JSClass<PinchGestureHandler>::Declare("PinchGesture");
    JSClass<PinchGestureHandler>::Inherit<JSGestureHandler>();
    JSClass<PinchGestureHandler>::CustomMethod("onActionStart", &JSGestureHandler::JsHandlerOnActionStart);
    JSClass<PinchGestureHandler>::CustomMethod("onActionUpdate", &JSGestureHandler::JsHandlerOnActionUpdate);
    JSClass<PinchGestureHandler>::CustomMethod("onActionEnd", &JSGestureHandler::JsHandlerOnActionEnd);
    JSClass<PinchGestureHandler>::CustomMethod("onActionCancel", &JSGestureHandler::JsHandlerOnActionCancel);
    JSClass<PinchGestureHandler>::Bind(globalObj, PinchGestureHandler::ConstructorCallback);

    JSClass<RotationGestureHandler>::Declare("RotationGesture");
    JSClass<RotationGestureHandler>::Inherit<JSGestureHandler>();
    JSClass<RotationGestureHandler>::CustomMethod("onActionStart", &JSGestureHandler::JsHandlerOnActionStart);
    JSClass<RotationGestureHandler>::CustomMethod("onActionUpdate", &JSGestureHandler::JsHandlerOnActionUpdate);
    JSClass<RotationGestureHandler>::CustomMethod("onActionEnd", &JSGestureHandler::JsHandlerOnActionEnd);
    JSClass<RotationGestureHandler>::CustomMethod("onActionCancel", &JSGestureHandler::JsHandlerOnActionCancel);
    JSClass<RotationGestureHandler>::Bind(globalObj, RotationGestureHandler::ConstructorCallback);

    JSClass<GestureGroupHandler>::Declare("GestureGroup");
    JSClass<GestureGroupHandler>::Inherit<JSGestureHandler>();
    JSClass<GestureGroupHandler>::CustomMethod("onCancel", &JSGestureHandler::JsHandlerOnActionCancel);
    JSClass<GestureGroupHandler>::Bind(globalObj, GestureGroupHandler::ConstructorCallback);
}

}; // namespace OHOS::Ace::Framework
